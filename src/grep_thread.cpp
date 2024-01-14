//----------------------------------------------------------------------//
// GREP スレッド														//
//----------------------------------------------------------------------//
#include "usr_str.h"
#include "usr_file_ex.h"
#include "usr_xd2tx.h"
#include "file_filter.h"
#include "grep_thread.h"
#include "Global.h"

#pragma package(smart_init)

//---------------------------------------------------------------------------
__fastcall TGrepThread::TGrepThread(bool CreateSuspended, int id,
		int idx_tag, UnicodeString fnam, UnicodeString kwd, GrepOption opt, UnicodeString filter)
			: TThread(CreateSuspended)
{
	Priority		= tpNormal;
	FreeOnTerminate = true;

	ID       = id;
	IndexTag = idx_tag;
	FileName = fnam;
	Keyword  = kwd;
	Options  = opt;
	Filter   = filter;

	ResultList = new TStringList();
}

//---------------------------------------------------------------------------
void __fastcall TGrepThread::AddResult()
{
	GrepResultBuff->AddStrings(ResultList);
}

//---------------------------------------------------------------------------
void __fastcall TGrepThread::Execute()
{
	try {
		if (!file_exists(FileName)) Abort();
		std::unique_ptr<TStringList> f_buf(new TStringList());
		UnicodeString fext = get_extension(FileName);
		if (xd2tx_TestExt(fext)) {
			if (!xd2tx_Extract(FileName, f_buf.get()))  Abort();
		}
		else {
			if (load_text_ex(FileName, f_buf.get())==0) Abort();
		}

		//フィルタの初期化
		std::unique_ptr<FileFilter> FLT(new FileFilter());
		FilterOption opt;
		opt << foIsGrep;
		if (Options.Contains(goExcludeTag)) opt << foExcludeTag;
		FLT->Initialize(FileName, f_buf.get(), Filter, opt);

		TRegExOptions re_opt;
		if (!Options.Contains(goCaseSens)) re_opt << roIgnoreCase;

		//DFMオブジェクト
		if (!FLT->objType.IsEmpty() && !FLT->propName.IsEmpty()) {
			conv_DfmText(f_buf.get());

			int lp = 0;
			while (lp<f_buf->Count) {
				UnicodeString lbuf = Trim(f_buf->Strings[lp++]);
				if (StartsStr("object", lbuf)) {
					lbuf = Trim(get_tkn_r(lbuf, "object"));
					OutputDebugString(lbuf.c_str());
					UnicodeString onam = lbuf.Pos(":")? get_tkn(lbuf, ":") : UnicodeString("<anonymous>");
					UnicodeString otyp = lbuf.Pos(":")? get_tkn_r(lbuf, ": ") : lbuf;
					if (FLT->objType=="*" || str_match(FLT->objType, otyp)) {
						while (lp<f_buf->Count) {
							lbuf = Trim(f_buf->Strings[lp++]);
							if (SameText(lbuf, "end") || !lbuf.Pos("=")) break;
							if (FLT->propName=="*" || str_match(FLT->propName, Trim(get_tkn(lbuf, "=")))) {
								int lno = lp;
								UnicodeString vbuf = Trim(get_tkn_r(lbuf, "="));
								if (vbuf=="(") {
									for (;lp<f_buf->Count; lp++) {
										if (vbuf!="(") vbuf += ", ";
										vbuf += f_buf->Strings[lp];
										if (EndsStr(")", vbuf)) break;
									}
								}
								else if (vbuf=="{") {
									for (;lp<f_buf->Count; lp++) {
										if (vbuf!="{") vbuf += ", ";
										vbuf += f_buf->Strings[lp];
										if (EndsStr("}", vbuf)) break;
									}
								}

								bool found = false;
								if (Options.Contains(goRegEx)) {
									TMatch mt = TRegEx::Match(vbuf, Keyword, re_opt);
									if (mt.Success) {
										found = Options.Contains(goWord)? is_word(vbuf, mt.Index, mt.Length) : true;
									}
								}
								else {
									found = find_mlt(Keyword, vbuf, Options.Contains(goAnd), false,
												Options.Contains(goCaseSens), Options.Contains(goWord));
								}
								if (found) {
									UnicodeString itmstr;	//ファイル名 [TAB] 行番号:Idx:0 [TAB] マッチ行
									UnicodeString s = otyp + "." + onam + "." + get_tkn(lbuf, "=") + "= ";
									itmstr.sprintf(_T("%s\t%d:%d:0\t%s\n"),
										FileName.c_str(), lp, s.Length() + 1, (s + vbuf).c_str());
									ResultList->AddObject(itmstr, (TObject*)(NativeInt)IndexTag);
									if (Options.Contains(goOneMatch)) break;
								}
							}
						}
					}
				}
			}
			if (ResultList->Count>0) Synchronize(&AddResult);
		}
		//通常
		else {
			for (int lp=FLT->topLine; lp<=FLT->endLine; lp++) {
				int r_idx, r_len;
				UnicodeString lbuf;
				UnicodeString sbuf = FLT->GetLinePart(lp, r_idx, r_len, lbuf);

				bool found = false;
				if (Options.Contains(goRegEx)) {
					TMatch mt = TRegEx::Match(sbuf, Keyword, re_opt);
					if (mt.Success) {
						found = Options.Contains(goWord)? is_word(sbuf, mt.Index, mt.Length) : true;
					}
				}
				else {
					found = find_mlt(Keyword, sbuf,
								Options.Contains(goAnd), false, Options.Contains(goCaseSens), Options.Contains(goWord));
				}

				if (found) {
					UnicodeString itmstr;	//ファイル名 [TAB] 行番号:Idx:Len [TAB] マッチ行\n次3行
					itmstr.sprintf(_T("%s\t%d:%d:%d\t%s\n"), FileName.c_str(), lp + 1, r_idx, r_len, lbuf.c_str());
					//次3行分(空行は除く)を付加
					int p = lp + 1;
					int lcnt = 0;
					while (p<f_buf->Count && lcnt<3) {
						UnicodeString tmp = FLT->GetDispLine(p++);
						if (tmp.IsEmpty()) continue;
						itmstr.cat_sprintf(_T("%s\n"), tmp.c_str());
						lcnt++;
					}

					ResultList->AddObject(itmstr, (TObject*)(NativeInt)IndexTag);
					if (Options.Contains(goOneMatch)) break;
				}
			}
			if (ResultList->Count>0) Synchronize(&AddResult);
		}
	}
	catch (...) {
		;
	}

	::SendMessage(Application->MainFormHandle, WM_NYANFI_GREP_END, (WPARAM)ID, (LPARAM)ResultList->Count);

	delete ResultList;
}
//---------------------------------------------------------------------------
