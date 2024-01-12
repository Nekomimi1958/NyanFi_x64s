//----------------------------------------------------------------------//
// GREP スレッド														//
//----------------------------------------------------------------------//
#include "usr_str.h"
#include "usr_file_ex.h"
#include "usr_xd2tx.h"
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

		int top_lp = 0;
		int end_lp = f_buf->Count - 1;
		int ss_idx = 0;
		int ss_len = 0;
		//フィルタ
		if (!Filter.IsEmpty()) {
			TStringDynArray flts = SplitString(Filter, '|');
			TRegExOptions fl_opt; fl_opt << roIgnoreCase;
			for (int i=0; i<flts.Length; i++) {
				UnicodeString f = Trim(flts[i]);
				//Head
				TMatch mt = TRegEx::Match(f, "Head\\((\\d+)\\)", fl_opt);
				if (mt.Success && mt.Groups.Count==2) {
					int head_n = mt.Groups.Item[1].Value.ToIntDef(0);
					if (head_n>0) {
						end_lp = std::clamp(top_lp + head_n - 1, 0, f_buf->Count - 1);
						continue;
					}
				}
				//Tail
				mt = TRegEx::Match(f, "Tail\\((\\d+)\\)", fl_opt);
				if (mt.Success && mt.Groups.Count==2) {
					int tail_n = mt.Groups.Item[1].Value.ToIntDef(0);
					if (tail_n>0) {
						top_lp = std::clamp(end_lp - tail_n + 1, 0, f_buf->Count - 1);
						continue;
					}
				}
				//HtmlHead
				if (SameText(f, "HtmlHead")) {
					int top_h = -1, end_h = -1;
					for (int lp=top_lp; lp<=end_lp; lp++) {
						UnicodeString lbuf = f_buf->Strings[lp];
						if (ContainsText(lbuf, "<head>")) {
							top_h = lp;
						}
						if (top_h!=-1 && ContainsText(lbuf, "</head>")) {
							end_h = lp;
							break;
						}
					}
					if (top_h>=0 && end_h>=0) {
						top_lp = top_h; 
						end_lp = end_h; 
						continue;
					}
				}
				//SubStr
				mt = TRegEx::Match(f, "SubStr\\((\\d+)(?:,\\s?(\\d+))?\\)", fl_opt);
				if (mt.Success && mt.Groups.Count>1) {
					int idx = mt.Groups.Item[1].Value.ToIntDef(0);
					int len = (mt.Success && mt.Groups.Count==3)? mt.Groups.Item[2].Value.ToIntDef(0) : 0;
					if (idx>0) {
						ss_idx = idx;
						ss_len = len;
						continue;
					}
				}
			}
		}

		TRegExOptions re_opt;
		if (!Options.Contains(goCaseSens)) re_opt << roIgnoreCase;
		for (int lp=top_lp; lp<=end_lp; lp++) {
			UnicodeString lbuf = f_buf->Strings[lp];
			if (ss_idx>0) lbuf = lbuf.SubString(ss_idx, (ss_len>0)? ss_len : lbuf.Length() - ss_idx + 1);

			if (Options.Contains(goExcludeTag)) lbuf = TRegEx::Replace(lbuf, "<[^<>]+>", EmptyStr);
			if (lbuf.IsEmpty()) continue;

			bool found = false;
			if (Options.Contains(goRegEx)) {
				TMatch mt = TRegEx::Match(lbuf, Keyword, re_opt);
				if (mt.Success) {
					found = Options.Contains(goWord)? is_word(lbuf, mt.Index, mt.Length) : true;
				}
			}
			else {
				found = find_mlt(Keyword, lbuf,
							Options.Contains(goAnd), false, Options.Contains(goCaseSens), Options.Contains(goWord));
			}

			if (found) {
				UnicodeString itmstr;	//ファイル名 [TAB] 行番号 [TAB] マッチ行\n次3行
				itmstr.sprintf(_T("%s\t%u\t%s\n"), FileName.c_str(), lp + 1, f_buf->Strings[lp].c_str());
				//次3行分(空行は除く)を付加
				int p	 = lp + 1;
				int lcnt = 0;
				while (p<f_buf->Count && lcnt<3) {
					UnicodeString tmp = f_buf->Strings[p++];
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
	catch (...) {
		;
	}

	::SendMessage(Application->MainFormHandle, WM_NYANFI_GREP_END, (WPARAM)ID, (LPARAM)ResultList->Count);

	delete ResultList;
}
//---------------------------------------------------------------------------
