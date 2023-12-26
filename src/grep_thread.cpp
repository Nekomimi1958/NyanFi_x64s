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
		int idx_tag, UnicodeString fnam, UnicodeString kwd,
		bool sw_regex, bool sw_and, bool sw_case, bool sw_one, bool sw_xtag)
			: TThread(CreateSuspended)
{
	Priority		= tpNormal;
	FreeOnTerminate = true;

	ID		  = id;
	IndexTag  = idx_tag;
	FileName  = fnam;
	Keyword   = kwd;

	opt_regex = sw_regex;
	opt_and   = sw_and;
	opt_case  = sw_case;
	opt_one   = sw_one;
	opt_xtag  = sw_xtag;

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

		TRegExOptions opt;
		if (!opt_case) opt << roIgnoreCase;

		for (int lp=0; lp<f_buf->Count; lp++) {
			UnicodeString lbuf = f_buf->Strings[lp];
			if (opt_xtag) lbuf = TRegEx::Replace(lbuf, "<[^<>]+>", EmptyStr);	//HTML文書のタグ部分を除外
			if (lbuf.IsEmpty()) continue;

			bool found = opt_regex ? TRegEx::IsMatch(lbuf, Keyword, opt)
								   : find_mlt(Keyword, lbuf, opt_and, false, opt_case);
			if (found) {
				UnicodeString itmstr;	//ファイル名 [TAB] 行番号 [TAB] マッチ行\n次3行
				itmstr.sprintf(_T("%s\t%u\t%s\n"), FileName.c_str(), lp + 1, lbuf.c_str());
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
				if (opt_one) break;
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
