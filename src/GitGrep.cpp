//----------------------------------------------------------------------//
// NyanFi																//
//  GitGrep																//
//----------------------------------------------------------------------//
#include "UserMdl.h"
#include "UserFunc.h"
#include "Global.h"
#include "GenInfDlg.h"
#include "GitGrep.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TGitGrepForm *GitGrepForm = NULL;

//---------------------------------------------------------------------------
__fastcall TGitGrepForm::TGitGrepForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TGitGrepForm::FormCreate(TObject *Sender)
{
	DlgInitialized = false;
	ResultScrPanel = new UsrScrollPanel(ResultPanel,   ResultListBox,   USCRPNL_FLAG_P_WP | USCRPNL_FLAG_L_WP);

	PathComboBox->Tag = CBTAG_HISTORY;
	UserModule->SetUsrPopupMenu(this);

	MsgHint = new UsrHintWindow(this);
	AssignScaledFont(MsgHint->Font, HintFont, this);

	ResultBuff = new TStringList();

	KeyHandled = false;
}
//---------------------------------------------------------------------------
void __fastcall TGitGrepForm::FormShow(TObject *Sender)
{
	Caption = yen_to_delimiter(WorkDir) + (!CommitID.IsEmpty()? ":" + CommitID.SubString(1, 7) : EmptyStr ) + " - Git GREP";

	IniFile->LoadPosInfo(this, DialogCenter);
	RegExCheckBox->Checked = IniFile->ReadBoolGen(_T("GitGrepRegEx"),	false);
	CaseCheckBox->Checked  = IniFile->ReadBoolGen(_T("GitGrepCase"),	false);

	IniFile->LoadComboBoxItems(FindComboBox, RegExCheckBox->Checked? _T("GitGrepPtnHistory") : _T("GitGrepFindHistory"));
	IniFile->LoadComboBoxItems(PathComboBox, _T("GitGrepPathHistory"));
	PathComboBox->Text = IniFile->ReadStrGen(_T("GitGrepLastPath"));

	set_ListBoxItemHi(ResultListBox, GrepResFont);
	set_UsrScrPanel(ResultScrPanel);

	FindComboBox->SetFocus();
	CloseIME(Handle);
	DlgInitialized = true;
}
//---------------------------------------------------------------------------
void __fastcall TGitGrepForm::FormClose(TObject *Sender, TCloseAction &Action)
{
	IniFile->SavePosInfo(this);
	IniFile->WriteBoolGen(_T("GitGrepRegEx"),	RegExCheckBox);
	IniFile->WriteBoolGen(_T("GitGrepCase"),	CaseCheckBox);

	IniFile->SaveComboBoxItems(FindComboBox, RegExCheckBox->Checked? _T("GitGrepPtnHistory") : _T("GitGrepFindHistory"));
	IniFile->SaveComboBoxItems(PathComboBox, _T("GitGrepPathHistory"));
	IniFile->WriteStrGen(_T("GitGrepLastPath"), PathComboBox->Text);
}
//---------------------------------------------------------------------------
void __fastcall TGitGrepForm::FormDestroy(TObject *Sender)
{
	delete ResultScrPanel;
	delete MsgHint;
	delete ResultBuff;
}
//---------------------------------------------------------------------------
void __fastcall TGitGrepForm::FormResize(TObject *Sender)
{
	TopLeftPanel->Width = ClientWidth/2;
	OptLeftPanel->Width = ClientWidth/2;
}

//---------------------------------------------------------------------------
void __fastcall TGitGrepForm::RegExCheckBoxClick(TObject *Sender)
{
	if (DlgInitialized) {
		change_ComboBoxHistory(FindComboBox, _T("GitGrepFindHistory"), _T("GitGrepPtnHistory"), RegExCheckBox->Checked);
	}
}
//---------------------------------------------------------------------------
void __fastcall TGitGrepForm::FindComboBoxKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	UnicodeString KeyStr = get_KeyStr(Key, Shift);

	if (contained_wd_i(KeysStr_ToList, KeyStr) && ResultListBox->Count>0) {
		ResultListBox->SetFocus();
	}
	else return;

	KeyHandled = true;
	Key = 0;
}
//---------------------------------------------------------------------------
void __fastcall TGitGrepForm::FindComboBoxKeyPress(TObject *Sender, System::WideChar &Key)
{
	if (KeyHandled) {
		KeyHandled = false;
		Key = 0;
	}
}
//---------------------------------------------------------------------------
//GREP開始
//---------------------------------------------------------------------------
void __fastcall TGitGrepForm::GrepStartActionExecute(TObject *Sender)
{
	Keyword = Trim(FindComboBox->Text);
	UnicodeString prm = "grep -n";
	if (!CaseCheckBox->Checked) prm += " -i";
	if (RegExCheckBox->Checked) prm += " -E";

	if (StartsStr("-e ", Keyword))
		prm += (" " + Keyword);
	else
		prm += (" \"" + Keyword + "\"");

	if (!CommitID.IsEmpty()) prm += (" " + CommitID);

	if (!PathComboBox->Text.IsEmpty()) {
		UnicodeString mask = PathComboBox->Text;
		prm += " -- \"" + mask +  "\"";
	}

	ResultListBox->Count = 0;
	ResultBuff->Clear();
	StatusBar1->Panels->Items[0]->Text = "検索中...";
	StatusBar1->Panels->Items[1]->Text = "git " + prm;
	unsigned int start_cnt = GetTickCount();

	GitBusy = true;
	FindComboBox->Enabled = false;
	bool ok = (GitShellExe(prm, WorkDir, ResultBuff));
	FindComboBox->Enabled = true;
	GitBusy = false;

	if (ok) {
		if (ResultBuff->Count) {
			add_ComboBox_history(FindComboBox, Keyword);
			IniFile->SaveComboBoxItems(FindComboBox, RegExCheckBox->Checked? _T("GitGrepPtnHistory") : _T("GitGrepFindHistory"));
			add_ComboBox_history(PathComboBox);

			//ファイル数をカウント
			UnicodeString fnam;
			int f_cnt = 0;
			TRegExOptions opt; opt << roIgnoreCase;
			for (int i=0; i<ResultBuff->Count; i++) {
				TMatch mt = TRegEx::Match(ResultBuff->Strings[i], "^(?:[0-9a-f]{7,}:)?(?:.+/)?(?:[^:]+):", opt);
				if (!mt.Success) continue;
				if (!SameText(fnam, mt.Value)) {
					fnam = mt.Value;
					f_cnt++;
				}
			}

			ResultListBox->Count = ResultBuff->Count;
			ResultScrPanel->UpdateKnob();
			ResultListBox->ItemIndex = 0;
			ResultListBox->SetFocus();
			StatusBar1->Panels->Items[0]->Text =
				UnicodeString().sprintf(_T("%uファイルで %u行発見 (%.1f秒)"),
					f_cnt, ResultListBox->Count, (GetTickCount() - start_cnt)/1000.0);
		}
		else {
			StatusBar1->Panels->Items[0]->Text = "見つかりません";
			beep_Warn();
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TGitGrepForm::GrepStartActionUpdate(TObject *Sender)
{
	TAction *ap = (TAction *)Sender;

	FindComboBox->Tag = CBTAG_HISTORY |
						(FindComboBox->Focused()? CBTAG_RGEX_V : 0) |
						(RegExCheckBox->Checked? (CBTAG_RGEX_E | CBTAG_RGEX_P) : 0);

	bool reg_ng = RegExCheckBox->Checked && !FindComboBox->Text.IsEmpty() && !chk_RegExPtn(FindComboBox->Text);
	ErrMarkList->SetErrFrame(this, FindComboBox, reg_ng);

	ap->Enabled = !FindComboBox->Text.IsEmpty() && !reg_ng;
}
//---------------------------------------------------------------------------
void __fastcall TGitGrepForm::ResultListBoxData(TWinControl *Control, int Index, UnicodeString &Data)
{
	Data = (Index>=0 && Index<ResultBuff->Count)? ResultBuff->Strings[Index] : EmptyStr;
}
//---------------------------------------------------------------------------
void __fastcall TGitGrepForm::ResultListBoxDrawItem(TWinControl *Control, int Index,
	TRect &Rect, TOwnerDrawState State)
{
	TListBox *lp = (TListBox*)Control;
	TCanvas  *cv = lp->Canvas;
	cv->Brush->Color = lp->Color;
	cv->FillRect(Rect);

	int xp = Rect.Left + SCALED_THIS(4);
	int yp = Rect.Top  + SCALED_THIS(2);
	TRect rc = Rect;

	UnicodeString pnam_prv, pnam_nxt;
	if (Index>0) {
		TMatch mt = TRegEx::Match(lp->Items->Strings[Index - 1], RESLINE_MATCH_PTN);
		if (mt.Success && mt.Groups.Count==6) {
			pnam_prv = mt.Groups.Item[1].Value + mt.Groups.Item[2].Value + mt.Groups.Item[3].Value;
		}
	}
	if (Index<lp->Count-1) {
		TMatch mt = TRegEx::Match(lp->Items->Strings[Index + 1], RESLINE_MATCH_PTN);
		if (mt.Success && mt.Groups.Count==6) {
			pnam_nxt = mt.Groups.Item[1].Value + mt.Groups.Item[2].Value + mt.Groups.Item[3].Value;
		}
	}

	TMatch mt = TRegEx::Match(lp->Items->Strings[Index], RESLINE_MATCH_PTN);
	if (mt.Success && mt.Groups.Count==6) {
		UnicodeString hash = mt.Groups.Item[1].Value;
		UnicodeString pnam = hash + mt.Groups.Item[2].Value + mt.Groups.Item[3].Value;
		if (!hash.IsEmpty()) hash = hash.SubString(1, 7) + ":";

		if (!SameText(pnam, pnam_prv)) {
			if (!hash.IsEmpty()) out_TextEx(cv, xp, yp, hash, col_GitHash);
			out_TextEx(cv, xp, yp, mt.Groups.Item[2].Value, col_Folder);
			out_TextEx(cv, xp, yp, mt.Groups.Item[3].Value, get_ListFgCol());
		}
		else {
			xp += cv->TextWidth(hash + mt.Groups.Item[2].Value + mt.Groups.Item[3].Value);
		}
		xp += SCALED_THIS(8);

		//行番号
		int ln_wd = cv->TextWidth("000000 ");
		xp += ln_wd;
		int cwd = abs(cv->Font->Height);
		int wdn = 16;
		for (;;) {
			if (xp<cwd*wdn) { xp = cwd*wdn;  break; }
			wdn += 4;
			if (cwd*wdn > ClientWidth/2) break;
		}
		rc.Left = xp - ln_wd;
		LineNoOut(cv, rc, mt.Groups.Item[4].Value);
		cv->Brush->Color = get_ListBgCol();
		xp += SCALED_THIS(4);

		//ファイル境界
		if (!SameText(pnam, pnam_nxt)) {
			cv->Pen->Style = psSolid;
			cv->Pen->Width = ScaledInt(1);
			cv->Pen->Color = col_bgLineNo;
			cv->MoveTo(Rect.Left, Rect.Bottom - 1);
			cv->LineTo(rc.Left, Rect.Bottom - 1);
		}
		//マッチ語のリストを作成
		UnicodeString lbuf = mt.Groups.Item[5].Value;
		std::unique_ptr<TStringList> wlist(new TStringList());
		SearchOption opt;
		opt << soGitGrep;
		if (RegExCheckBox->Checked) opt << soRegEx;
		if (CaseCheckBox->Checked)	opt << soCaseSens;
		get_MatchWordList(lbuf, Keyword, opt, wlist.get());
		//マッチ語の強調表示
		cv->Font->Color = get_ListFgCol();
		EmphasisTextOut(lbuf, wlist.get(), cv, xp, yp, opt.Contains(soCaseSens));
	}

	cv->Brush->Color = lp->Color;
	draw_ListCursor2(lp, Rect, Index, State);
}

//---------------------------------------------------------------------------
void __fastcall TGitGrepForm::ResultListBoxEnter(TObject *Sender)
{
	CloseIME(Handle);
}

//---------------------------------------------------------------------------
void __fastcall TGitGrepForm::ResultListBoxKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	TListBox *lp = (TListBox*)Sender;
	UnicodeString KeyStr = get_KeyStr(Key, Shift);
	UnicodeString cmd_F  = Key_to_CmdF(KeyStr);

	if (ExeCmdListBox(lp, cmd_F) || ExeCmdListBox(lp, Key_to_CmdV(KeyStr)))
		;
	else if	(SameText(cmd_F, "FileEdit"))	EditFileAction->Execute();
	else if (SameText(cmd_F, "TextViewer"))	ViewFileAction->Execute();
	else if (equal_TAB(KeyStr) || SameText(KeyStr, "Ctrl+S")) {
		FindComboBox->SetFocus();
	}
	else if (contained_wd_i(KeysStr_Popup, KeyStr)) {
		show_PopupMenu(PopupMenu1, lp);
	}
	else return;

	Key = 0;
}
//---------------------------------------------------------------------------
void __fastcall TGitGrepForm::ResultListBoxKeyPress(TObject *Sender, System::WideChar &Key)
{
	Key = 0;
}

//---------------------------------------------------------------------------
//検索結果をクリップボードにコピー
//---------------------------------------------------------------------------
void __fastcall TGitGrepForm::ClipCopyActionExecute(TObject *Sender)
{
	copy_to_Clipboard(ResultBuff->Text);
}
//---------------------------------------------------------------------------
//カーソル行をクリップボードにコピー
//---------------------------------------------------------------------------
void __fastcall TGitGrepForm::LineCopyActionExecute(TObject *Sender)
{
	if (ResultListBox->ItemIndex!=-1) copy_to_Clipboard(ResultListBox->Items->Strings[ResultListBox->ItemIndex]);
}
//---------------------------------------------------------------------------
//検索結果に名前を付けて保存
//---------------------------------------------------------------------------
void __fastcall TGitGrepForm::SaveAsActionExecute(TObject *Sender)
{
	UserModule->SaveTxtDlg->Title		  = LoadUsrMsg(USTR_SaveAs, _T("検索結果"));
	UserModule->SaveTxtDlg->InitialDir    = ExcludeTrailingPathDelimiter(SaveTxtPath);
	UserModule->SaveTxtDlg->EncodingIndex = SaveEncIndex;
	if (UserModule->SaveTxtDlg->Execute()) {
		SaveTxtPath  = ExtractFilePath(UserModule->SaveTxtDlg->FileName);
		SaveEncIndex = UserModule->SaveTxtDlg->EncodingIndex;
		if (!saveto_TextFile(UserModule->SaveTxtDlg->FileName, ResultBuff, SaveEncIndex)) msgbox_ERR(USTR_FaildSave);
	}
}
//---------------------------------------------------------------------------
void __fastcall TGitGrepForm::ResultActionUpdate(TObject *Sender)
{
	((TAction*)Sender)->Enabled = !GitBusy && ResultListBox->Count>0;
}

//---------------------------------------------------------------------------
//テキストエディタで開く
//---------------------------------------------------------------------------
void __fastcall TGitGrepForm::EditFileActionExecute(TObject *Sender)
{
	if (ResultListBox->ItemIndex!=-1) {
		TMatch mt = TRegEx::Match(ResultListBox->Items->Strings[ResultListBox->ItemIndex], RESLINE_MATCH_PTN);
		if (mt.Success && mt.Groups.Count==6) {
			UnicodeString hash = get_tkn(mt.Groups.Item[1].Value, ":");
			UnicodeString fnam = mt.Groups.Item[2].Value + mt.Groups.Item[3].Value;
			int lno = mt.Groups.Item[4].Value.ToIntDef(1);
			if (hash.IsEmpty()) {
				fnam = IncludeTrailingPathDelimiter(WorkDir) + slash_to_yen(fnam);
			}
			else {
				MsgHint->ShowMsgHint("ファイル抽出中...", this, col_bgHint);
				GitBusy = true;
				fnam = save_GitRevAsTemp(hash, fnam, WorkDir);
				GitBusy = false;
				MsgHint->ReleaseHandle();
			}
			if (!fnam.IsEmpty() && !open_by_TextEditor(fnam, lno)) msgbox_ERR(GlobalErrMsg);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TGitGrepForm::EditFileActionUpdate(TObject *Sender)
{
	TAction *ap = (TAction *)Sender;
	UnicodeString s = "テキストエディタで開く";
	s += (CommitID.IsEmpty()? "(&E)" : " - Temp (&E)");
	ap->Caption = s;
	ap->Enabled = (ResultListBox->ItemIndex != -1);
}

//---------------------------------------------------------------------------
//このファイルの内容を表示
//---------------------------------------------------------------------------
void __fastcall TGitGrepForm::ViewFileActionExecute(TObject *Sender)
{
	if (ResultListBox->ItemIndex!=-1) {
		TMatch mt = TRegEx::Match(ResultListBox->Items->Strings[ResultListBox->ItemIndex], "^([0-9a-f]{7,}:)?(.+/)?(.+):(\\d+):(.+)");
		if (mt.Success && mt.Groups.Count==6) {
			UnicodeString hash = get_tkn(mt.Groups.Item[1].Value, ":");
			UnicodeString fnam = mt.Groups.Item[2].Value + mt.Groups.Item[3].Value;
			int idx = mt.Groups.Item[4].Value.ToIntDef(1) - 1;

			std::unique_ptr<TStringList> o_lst(new TStringList());
			bool ok;
			if (hash.IsEmpty()) {
				fnam = IncludeTrailingPathDelimiter(WorkDir) + slash_to_yen(fnam);
				ok = load_text_ex(fnam, o_lst.get())!=0;
			}
			else {
				MsgHint->ShowMsgHint("ファイル抽出中...", this, col_bgHint);
				GitBusy = true;
				UnicodeString prm;
				prm.sprintf(_T("cat-file -p %s:%s"), hash.c_str(), fnam.c_str());
				DWORD exit_code;
				ok = (GitShellExe(prm, WorkDir, o_lst.get(), &exit_code) && exit_code==0);
				GitBusy = false;
				MsgHint->ReleaseHandle();
			}

			if (ok) {
				GeneralInfoDlg->Caption     = UnicodeString().sprintf(_T("ファイル内容 - %s"), fnam.c_str());
				GeneralInfoDlg->FileName    = fnam;
				GeneralInfoDlg->isNonFile   = !hash.IsEmpty();
				GeneralInfoDlg->fromPopWnd  = true;
				GeneralInfoDlg->GenInfoList->Assign(o_lst.get());
				GeneralInfoDlg->LineIndex   = idx;
				GeneralInfoDlg->ShowModal();
			}
		}
		else {
			beep_Warn();
		}
	}
 }
//---------------------------------------------------------------------------
void __fastcall TGitGrepForm::ViewFileActionUpdate(TObject *Sender)
{
	TAction *ap = (TAction*)Sender;
	ap->Enabled = (ResultListBox->ItemIndex != -1);
}
//---------------------------------------------------------------------------
void __fastcall TGitGrepForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	UnicodeString KeyStr = get_KeyStr(Key, Shift);
	SpecialKeyProc(this, Key, Shift, _T(HELPTOPIC_GIT) _T("#GitGrep"));
}
//---------------------------------------------------------------------------
