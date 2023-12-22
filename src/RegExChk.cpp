//----------------------------------------------------------------------//
// NyanFi																//
//  正規表現チェッカー													//
//----------------------------------------------------------------------//
#include "UserFunc.h"
#include "UserMdl.h"
#include "Global.h"
#include "RegExChk.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TRegExChecker *RegExChecker = NULL;

//---------------------------------------------------------------------------
__fastcall TRegExChecker::TRegExChecker(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TRegExChecker::FormCreate(TObject *Sender)
{
	UserModule->SetUsrPopupMenu(this);

	ResultList = new TStringList();
	DetailList = new TStringList();

	//正規表現の説明を設定
	TStringList *lst = UserModule->RefRegExList;
	for (int i=0; i<lst->Count; i++) {
		UnicodeString lbuf = lst->Strings[i];
		if (!lbuf.IsEmpty()) ReferListBox->Items->Add((lbuf[1]=='-')? EmptyStr : lbuf);
	}
	
	PtnComboBox->Tag = CBTAG_HISTORY;

	ObjComboBox   = NULL;
	ObjCustomEdit = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TRegExChecker::FormShow(TObject *Sender)
{
	set_ComboBox_AutoComp(this);

	IniFile->LoadPosInfo(this, DialogCenter);

	int mp_wd = IniFile->ReadScaledIntGen( _T("RegExMainWidth"), 380, this);
	ReferPanel->Width       = ClientWidth - mp_wd - Splitter1->Width;
	OpePanel->Height        = IniFile->ReadScaledIntGen( _T("RegExOpeHeight"), 240, this);
	ReferListBox->Height	= IniFile->ReadScaledIntGen( _T("RegExRefHeight"), 320, this);
	ReplaceEdit->Text       = IniFile->ReadStrGen( _T("RegExChkRepStr"));
	CaseCheckBox->Checked   = IniFile->ReadBoolGen(_T("RegExChkCase"),		false);
	UpdtCheckBox->Checked   = IniFile->ReadBoolGen(_T("RegExChkUpdate"),	false);
	DetailCheckBox->Checked = IniFile->ReadBoolGen(_T("RegExChkDetail"),	false);

	//フォントの設定
	std::unique_ptr<TFont> ttFont(new TFont());
	ttFont->Assign(ViewerFont);
	ttFont->Size  = Font->Size;
	ttFont->Color = get_TextColor();
	AssignScaledFont(PtnComboBox, ttFont.get());
	AssignScaledFont(ReplaceEdit, ttFont.get());

	ttFont->Color = get_ViewFgCol();
	AssignScaledFont(ObjMemo, 		 ttFont.get());
	set_ListBoxItemHi(ResListBox,	 ttFont.get());
	set_ListBoxItemHi(ReferListBox,  ttFont.get());
	set_ListBoxItemHi(SampleListBox, ttFont.get());
	ObjMemo->Color       = get_ViewBgCol();
	ResListBox->Color    = get_ViewBgCol();
	ReferListBox->Color  = get_ViewBgCol();
	SampleListBox->Color = get_ViewBgCol();

	StxPaintBox->Top = PtnComboBox->Top + PtnComboBox->Height;

	//検索対象の設定
	ObjMemo->Clear();
	bool ok = false;
	FileEdit->Text = IniFile->ReadStrGen(_T("RegExChkFile"));
	UnicodeString fnam = to_absolute_name(FileEdit->Text);
	if (file_exists(fnam)) {
		std::unique_ptr<TStringList> fbuf(new TStringList());
		if (load_text_ex(fnam, fbuf.get())) {
			ObjMemo->Text = fbuf->Text;
			ok = true;
		}
		else {
			msgbox_ERR(USTR_FileNotOpen);
		}
	}
	if (!ok) {
		TStringDynArray ibuf = get_csv_array(IniFile->ReadStrGen(_T("RegExChkText"), EmptyStr, false), 20);
		for (int i=0; i<ibuf.Length; i++) ObjMemo->Lines->Add(ibuf[i]);
	}

	//サンプルの設定
	std::unique_ptr<TStringList> s_lst(new TStringList());
	SampleFile = to_absolute_name(IniFile->ReadStrGen(_T("RegExChkSample")));
	if (load_text_ex(SampleFile, s_lst.get())) {
		SampleTime = get_file_age(SampleFile);
	}
	if (Trim(s_lst->Text).IsEmpty()) {
		s_lst->Text =
			"【 サンプル 】\n"
			"日付\t[12]\\d{3}/(0?[1-9]|1[0-2])/([12][0-9]|3[01]|0?[1-9])\n"
			"時刻\t([01]?[0-9]|2[0-3])(:[0-5][0-9]){1,2}\n"
			"URL\thttps?://[\\w/:%#$&?()~.=+-]+\n"
			"偶数\t\\d*[02468]\n"
			"奇数\t\\d*[13579]\n"
			"全角\t[^ -~｡-ﾟ\\t]+\n"
			"半角ｶﾅ\t[｡-ﾟ]+\n";
	}
	AssignSample(s_lst.get());

	IniFile->LoadComboBoxItems(PtnComboBox, _T("RegExChkHistory"));
	if (PtnComboBox->Items->Count>0) PtnComboBox->ItemIndex = 0;

	with_Slash = is_regex_slash(PatternStr);
	if (!PatternStr.IsEmpty()) {
		if (with_Slash) PatternStr = exclude_top_end(PatternStr);
		PtnComboBox->Text = PatternStr;
	}

	PtnSelStart  = PtnComboBox->SelStart;
	PtnSelLength = PtnComboBox->SelLength;

	ResultLabel->Caption = "結果";
	ResListBox->Clear();
	ResultList->Clear();
	DetailList->Clear();
	MatchCount = MatchLines = 0;
}
//---------------------------------------------------------------------------
void __fastcall TRegExChecker::FormClose(TObject *Sender, TCloseAction &Action)
{
	ObjComboBox   = NULL;
	ObjCustomEdit = NULL;
	PatternStr	  = EmptyStr;

	IniFile->SavePosInfo(this);

	//検索対象の保存
	UnicodeString lbuf;
	for (int i=0; i<ObjMemo->Lines->Count && i<20; i++) {
		if (i>0) lbuf += ",";
		lbuf += make_csv_str(ObjMemo->Lines->Strings[i]);
	}
	IniFile->WriteStrGen( _T("RegExChkText"),	lbuf);
	//検索対象ファイルの更新
	IniFile->WriteStrGen( _T("RegExChkFile"),	FileEdit->Text);
	if (!FileEdit->Text.IsEmpty() && UpdtCheckBox->Checked && ObjMemo->Modified) {
		UnicodeString fnam = to_absolute_name(FileEdit->Text);
		if (!saveto_TextFile(fnam, ObjMemo->Lines)) msgbox_ERR(USTR_FaildSave);
	}

	IniFile->WriteStrGen( _T("RegExChkSample"), to_relative_name(SampleFile));

	IniFile->WriteScaledIntGen(_T("RegExMainWidth"), MainPanel->Width, 		this);
	IniFile->WriteScaledIntGen(_T("RegExOpeHeight"), OpePanel->Height, 		this);
	IniFile->WriteScaledIntGen(_T("RegExRefHeight"), ReferListBox->Height,	this);

	IniFile->WriteStrGen( _T("RegExChkRepStr"),	ReplaceEdit->Text);
	IniFile->WriteBoolGen(_T("RegExChkCase"),	CaseCheckBox->Checked);

	IniFile->WriteBoolGen(_T("RegExChkUpdate"),	UpdtCheckBox->Checked);
	IniFile->WriteBoolGen(_T("RegExChkDetail"),	DetailCheckBox->Checked);

	IniFile->SaveComboBoxItems(PtnComboBox, _T("RegExChkHistory"));

}
//---------------------------------------------------------------------------
void __fastcall TRegExChecker::FormDestroy(TObject *Sender)
{
	delete ResultList;
	delete DetailList;
}
//---------------------------------------------------------------------------
void __fastcall TRegExChecker::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	SpecialKeyProc(this, Key, Shift);
}

//---------------------------------------------------------------------------
//テスト
//---------------------------------------------------------------------------
void __fastcall TRegExChecker::TestActionExecute(TObject *Sender)
{
	try {
		cursor_HourGlass();
		ResListBox->Clear();
		ResultList->Clear();
		DetailList->Clear();
		MatchCount = MatchLines = 0;

		UnicodeString ptnstr = PtnComboBox->Text;
		TRegExOptions opt;
		if (!CaseCheckBox->Checked) opt<<roIgnoreCase;
		std::unique_ptr<TStringList> slst(new TStringList());
		slst->Text = ObjMemo->Lines->Text;
		int max_wd = 0;
		for (int i=0; i<slst->Count; i++) {
			UnicodeString lbuf = slst->Strings[i];
			TMatchCollection mts = TRegEx::Matches(lbuf, ptnstr, opt);
			if (mts.Count>0) {
				MatchLines++;
				UnicodeString mbuf;
				for (int j=0; j<mts.Count; j++) {
					if (mts.Item[j].Success) {
						if (j>0) mbuf += "\t";
						mbuf.cat_sprintf(_T("%u,%u"), mts.Item[j].Index, mts.Item[j].Length);
						MatchCount++;
					}
				}
				max_wd = std::max(max_wd, get_TabTextWidth(lbuf, ResListBox->Canvas, 8));
				lbuf += ("\f" + mbuf);
				ResultList->AddObject(lbuf, (TObject*)0);
				DetailList->AddObject(lbuf, (TObject*)0);
				//詳細
				for (int j=0; j<mts.Count; j++) {
					if (mts.Item[j].Success) {
						//Match
						DetailList->AddObject("Match " + IntToStr(j + 1) + ":" + mts.Item[j].Value, (TObject*)1);
						//Group
						if (mts.Item[j].Groups.Count>1) {
							for (int k=1; k<mts.Item[j].Groups.Count; k++) {
								DetailList->AddObject(
									"Group " + IntToStr(k) + ":" + mts.Item[j].Groups.Item[k].Value, (TObject*)2);
							}
						}
					}
				}
				DetailList->AddObject("-", (TObject*)9);
			}
		}
		ResListBox->Items->Assign(DetailCheckBox->Checked? DetailList : ResultList);
		ResListBox->ScrollWidth = max_wd + ResListBox->Font->Size * 2;
		cursor_Default();

		//結果
		if (ResListBox->Count>0) {
			add_ComboBox_history(PtnComboBox);
			ResultLabel->Caption = UnicodeString().sprintf(_T("%u行、%u箇所でマッチしました"), MatchLines, MatchCount);
			ResultLabel->Font->Color = get_TextColor();
		}
		else {
			ResultLabel->Caption = "マッチしません";
			ResultLabel->Font->Color = col_Error;
			beep_Warn();
		}
	}
	catch (...) {
		cursor_Default();
		ResultLabel->Caption = "失敗しました";
		ResultLabel->Font->Color = col_Error;
		beep_Warn();
	}
}
//---------------------------------------------------------------------------
void __fastcall TRegExChecker::TestActionUpdate(TObject *Sender)
{
	bool reg_ok = chk_RegExPtn(PtnComboBox->Text);
	((TAction *)Sender)->Enabled = !ObjMemo->Lines->Text.IsEmpty() && reg_ok;

	ErrMarkList->SetErrFrame(this, PtnComboBox, !PtnComboBox->Text.IsEmpty() && !reg_ok);

	if (PtnComboBox->Focused()) {
		PtnSelStart  = PtnComboBox->SelStart;
		PtnSelLength = PtnComboBox->SelLength;
	}
}
//---------------------------------------------------------------------------
//置換
//---------------------------------------------------------------------------
void __fastcall TRegExChecker::ReplaceActionExecute(TObject *Sender)
{
	try {
		cursor_HourGlass();
		ResListBox->Clear();
		ResultList->Clear();
		DetailList->Clear();
		MatchCount = MatchLines = 0;

		UnicodeString ptnstr = PtnComboBox->Text;
		TRegExOptions opt;
		if (!CaseCheckBox->Checked) opt<<roIgnoreCase;
		std::unique_ptr<TStringList> slst(new TStringList());
		slst->Text = ObjMemo->Lines->Text;
		int max_wd = 0;
		for (int i=0; i<slst->Count; i++) {
			UnicodeString lbuf = slst->Strings[i];
			TMatchCollection mts = TRegEx::Matches(lbuf, ptnstr, opt);
			if (mts.Count>0) {
				MatchLines++;
				UnicodeString rbuf = replace_regex_2(lbuf, ptnstr, ReplaceEdit->Text, opt);
				UnicodeString mbuf;
				int ofs = 0;
				for (int j=0; j<mts.Count; j++) {
					if (mts.Item[j].Success) {
						if (j>0) mbuf += "\t";
						UnicodeString rwd = TRegEx::Replace(mts.Item[j].Value, ptnstr, ReplaceEdit->Text, opt);
						int p = mts.Item[j].Index + ofs;
						int n = rwd.Length();
						ofs += n - mts.Item[j].Value.Length();
						mbuf.cat_sprintf(_T("%u,%u"), p, n);
						MatchCount++;
					}
				}
				max_wd = std::max(max_wd, get_TabTextWidth(rbuf, ResListBox->Canvas, 8));
				rbuf += ("\f" + mbuf);
				ResultList->AddObject(rbuf, (TObject*)0);
				DetailList->AddObject(rbuf, (TObject*)0);
				//詳細
				for (int j=0; j<mts.Count; j++) {
					if (mts.Item[j].Success) {
						//Replace
						DetailList->AddObject("Replace " + IntToStr(j + 1) + ":" + mts.Item[j].Value, (TObject*)1);
						UnicodeString rwd = TRegEx::Replace(mts.Item[j].Value, ptnstr, ReplaceEdit->Text, opt);
						DetailList->AddObject(
							"→:" + TRegEx::Replace(mts.Item[j].Value, ptnstr, ReplaceEdit->Text, opt), (TObject*)2);
						//Group
						if (mts.Item[j].Groups.Count>1) {
							for (int k=1; k<mts.Item[j].Groups.Count; k++) {
								DetailList->AddObject(
									"Group " + IntToStr(k) + ":" + mts.Item[j].Groups.Item[k].Value, (TObject*)2);
							}
						}
					}
				}
				DetailList->AddObject("-", (TObject*)9);
			}
		}
		ResListBox->Items->Assign(DetailCheckBox->Checked? DetailList : ResultList);
		ResListBox->ScrollWidth = max_wd + ResListBox->Font->Size * 2;
		cursor_Default();

		//結果
		if (ResListBox->Count>0) {
			ResultLabel->Caption	 = UnicodeString().sprintf(_T("%u行、%u箇所を置換しました"), MatchLines, MatchCount);
			ResultLabel->Font->Color = get_TextColor();
		}
		else {
			ResultLabel->Caption	 = "マッチしません";
			ResultLabel->Font->Color = col_Error;
			beep_Warn();
		}
	}
	catch (...) {
		cursor_Default();
		ResultLabel->Caption	 = "失敗しました";
		ResultLabel->Font->Color = col_Error;
		beep_Warn();
	}
}
//---------------------------------------------------------------------------
void __fastcall TRegExChecker::ReplaceActionUpdate(TObject *Sender)
{
	((TAction *)Sender)->Enabled = TestAction->Enabled;
}

//---------------------------------------------------------------------------
//貼り付け
//---------------------------------------------------------------------------
void __fastcall TRegExChecker::PasteActionExecute(TObject *Sender)
{
	UnicodeString s = PtnComboBox->Text;
	if (with_Slash) s = "/" + s + "/";

	if (ObjComboBox) {
		ObjComboBox->Text = s;
		ObjComboBox->SelStart = s.Length();
	}
	else if (ObjCustomEdit) {
		ObjCustomEdit->Text = s;
		ObjCustomEdit->SelStart = s.Length();
	}
}
//---------------------------------------------------------------------------
void __fastcall TRegExChecker::PasteActionUpdate(TObject *Sender)
{
	((TAction*)Sender)->Enabled = !PtnComboBox->Text.IsEmpty() && (ObjComboBox || ObjCustomEdit);
}

//---------------------------------------------------------------------------
//コピー
//---------------------------------------------------------------------------
void __fastcall TRegExChecker::CopyActionExecute(TObject *Sender)
{
	UnicodeString ptn = PtnComboBox->Text;
	if (((TAction*)Sender)->Tag==1) {
		ptn = ReplaceStr(ptn, "\\", "\\\\");
		ptn = ReplaceStr(ptn, "\"", "\\\"");
		ptn = "\"" + ptn + "\"";
	}
	copy_to_Clipboard(ptn);
}
//---------------------------------------------------------------------------
void __fastcall TRegExChecker::CopyActionUpdate(TObject *Sender)
{
	((TAction*)Sender)->Enabled = !PtnComboBox->Text.IsEmpty();
}

//---------------------------------------------------------------------------
void __fastcall TRegExChecker::ReferListBoxDblClick(TObject *Sender)
{
	TListBox *lp = (TListBox *)Sender;
	int idx = lp->ItemIndex;
	if (idx!=-1) {
		UnicodeString s = lp->Items->Strings[idx];
		if (s.Pos('\t')) {
			s = (lp->Tag==0)? get_pre_tab(s) : get_post_tab(s);
			PtnComboBox->SetFocus();
			PtnComboBox->SelStart  = PtnSelStart;
			PtnComboBox->SelLength = PtnSelLength;
			PtnComboBox->SelText   = s;
		}
	}
}

//---------------------------------------------------------------------------
//検索対象ファイルの指定
//---------------------------------------------------------------------------
void __fastcall TRegExChecker::RefFileBtnClick(TObject *Sender)
{
	UserModule->PrepareOpenDlg(_T("検索対象の指定"), F_FILTER_TXT, _T("*.txt"));
	if (UserModule->OpenDlgToEdit(FileEdit, true)) {
		UnicodeString fnam = to_absolute_name(FileEdit->Text);
		if (file_exists(fnam)) {
			std::unique_ptr<TStringList> fbuf(new TStringList());
			if (load_text_ex(fnam, fbuf.get()))
				ObjMemo->Text = fbuf->Text;
			else
				msgbox_ERR(USTR_FileNotOpen);
		}
	}
}

//---------------------------------------------------------------------------
//結果の描画
//---------------------------------------------------------------------------
void __fastcall TRegExChecker::ResListBoxDrawItem(TWinControl *Control, int Index,
	TRect &Rect, TOwnerDrawState State)
{
	TListBox *lp = (TListBox*)Control;
	TCanvas *cv  = lp->Canvas;
	cv->Font->Assign(lp->Font);

	cv->Brush->Color = get_ViewBgCol();
	TRect rc = Rect;
	cv->FillRect(rc);

	UnicodeString lbuf = lp->Items->Strings[Index];
	int	flag  = (int)lp->Items->Objects[Index];

	//セパレータ
	if (flag==9) {
		draw_Separator(cv, Rect);
		return;
	}

	//マッチ行
	if (flag==0) {
		TStringDynArray mbuf = split_strings_tab(get_tkn_r(lbuf, "\f"));
		lbuf = get_tkn(lbuf, "\f");
		int l_len = lbuf.Length();

		std::unique_ptr<TColor[]> FgCol(new TColor[l_len + 1]);
		std::unique_ptr<TColor[]> BgCol(new TColor[l_len + 1]);
		for (int i=0; i<=l_len; i++) {
			FgCol[i] = get_ViewFgCol();
			BgCol[i] = get_ViewBgCol();
		}

		for (int i=0; i<mbuf.Length; i++) {
			UnicodeString ibuf = mbuf[i];
			int p = split_tkn(ibuf, ',').ToIntDef(0);
			int n = ibuf.ToIntDef(0);
			if (p>0 && n>0) {
				for (int j=0; j<n; j++) {
					FgCol[p + j] = clHighlightText;
					BgCol[p + j] = (i%2==0)? clHighlight : ComplementaryCol(clHighlight);
				}
			}
		}

		//描画
		cv->Font->Color  = FgCol[1];
		cv->Brush->Color = BgCol[1];
		rc.Left += SCALED_THIS(4);
		rc.Top  += 1; rc.Bottom -= 1;
		int cp = 0;
		for (int i=1; i<=l_len; i++) {
			UnicodeString sbuf;
			if (lbuf[i]=='\t') {
				int n = 8 - cp%8;
				sbuf = StringOfChar(_T(' '), n);
				cp += n;
			}
			else {
				sbuf = lbuf[i];
				cp += str_len_half(sbuf);
			}
			rc.Right = rc.Left + cv->TextWidth(sbuf);
			out_TextRect(cv, rc, sbuf, FgCol[i], BgCol[i]); 
		}
	}
	else {
		//詳細
		if (lbuf.Pos(":")) {
			UnicodeString t = get_tkn(lbuf, ":");
			if (!SameStr(t, "→")) t += ":";
			UnicodeString s = get_tkn_r(lbuf, ":");
			//項目名
			rc.Left += SCALED_THIS(8);
			int wd = cv->TextWidth("WWWWWWWWWW");
			cv->Font->Color = (flag==1)? col_Headline : col_Reserved;
			cv->TextRect(rc, rc.Left + wd - cv->TextWidth(t), rc.Top, t);
			rc.Left += (wd + SCALED_THIS(8));
			//文字列
			out_TextRect(cv, rc, "\"", col_Symbol); 
			if (s.Pos("\t")) {
				int ofs = 1;
				for (;;) {
					int p = PosEx("\t", s, ofs);
					if (p>0) {
						out_TextRect(cv, rc, s.SubString(ofs, p - ofs), col_Strings); 
						out_TextRect(cv, rc, "\\t", col_TAB); 
						ofs = p + 1;
					}
					else {
						out_TextRect(cv, rc, s.SubString(ofs, s.Length() - ofs + 1), col_Strings); 
						break;
					}
				}
			}
			else {
				out_TextRect(cv, rc, s, col_Strings); 
			}
			out_TextRect(cv, rc, "\"", col_Symbol); 
		}
		//その他
		else {
			out_TextRect(cv, rc, lbuf, get_ViewFgCol()); 
		}
	}
}

//---------------------------------------------------------------------------
//構文カラーバーの描画
//---------------------------------------------------------------------------
void __fastcall TRegExChecker::PtnComboBoxChange(TObject *Sender)
{
	StxPaintBox->Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TRegExChecker::StxPaintBoxPaint(TObject *Sender)
{
	TPaintBox *pp = (TPaintBox*)Sender;
	TRect rc = pp->ClientRect;
	TCanvas *cv  = pp->Canvas;
	cv->Brush->Color = get_ViewBgCol();
	cv->FillRect(rc);

	UnicodeString ptn = PtnComboBox->Text;
	cv->Font->Assign(PtnComboBox->Font);

	bool is_cls = false;
	bool is_brk = false;

	int grp_n = 0, grp_l = 0;
	UnicodeString grp_s;

	TColor grp_col[10];
	for (int i=0; i<10; i++) grp_col[i] = HslToCol(36 * i, 100, 70);

	int xp = 0, wd = 0;
	int cp = 1;
	while (cp<=ptn.Length()) {
		WideChar c = ptn[cp++];
		UnicodeString s, cc;
		TColor col = col_None;
		bool grp_f = false;
		wd = cv->TextWidth(c);
		if (c=='\\') {
			cc = ptn.SubString(cp, 1);
			col = is_cls? col_Strings :
					(cc=="r" || cc=="n")? col_CR : (cc=="t")? col_TAB :
					UnicodeString("wWsSdDbB").Pos(cc)? col_Reserved : get_ViewFgCol();
			wd += cv->TextWidth(cc);
			cp++;
		}
		else if (!is_cls && c=='[') {
			is_cls = true;
			col = col_Strings;
		}
		else if (is_cls && c==']') {
			is_cls = false;
			col = col_Strings;
		}
		else if (!is_cls && c=='(') {
			grp_l++;
			grp_f = true;
			if (ptn.SubString(cp, 2)=="?:") {
				grp_s += " ";
				wd += cv->TextWidth("?:");
				col = grp_col[0];
				cp+=2;
			}
			else {
				grp_n++;
				if (grp_n<10) {
					s.sprintf(_T("%1d"), grp_n);
					grp_s += s;
					col = grp_col[grp_n];
				}
				else {
					grp_s += " ";
					col = grp_col[0];
				}
			}
		}
		else if (!is_cls && c==')') {
			grp_f = true;
			if (grp_s.Length()>=1) {
				s = grp_s.SubString(grp_s.Length(), 1);
				grp_s.Delete(grp_s.Length(), 1);
				col = grp_col[s.ToIntDef(0)%10];
			}
			else {
				col = col_Error;
			}
			grp_l--;
		}
		else if (!is_cls && (c=='{' || c=='}')) {
			is_brk = (c=='{');
			col = col_Numeric;
		}
		else if (!is_cls && (c=='*' || c=='+' || c=='?')) {
			col = col_Numeric;
		}
		else if (!is_cls && (c=='^' || c=='$' || c=='|')) {
			col = col_Symbol;
		}
		else {
			col = (col!=col_None)? col :
							is_cls? col_Strings :
							is_brk? col_Numeric : get_ViewFgCol();
		}

		rc.Left  = xp;
		rc.Right = xp + wd;
		if (!grp_f) col  = AdjustColor(col, ADJCOL_BGMID);
		cv->Brush->Color = col;
		cv->Brush->Style = bsSolid;
		cv->FillRect(rc);

		if (grp_l>0) {
			int yp = rc.Bottom;
			for (int i=1; i<=grp_s.Length(); i++) {
				int n = UnicodeString(grp_s[i]).ToIntDef(0);
				int h = SCALED_THIS((i<5)? 2 : 1);
				TRect b_rc = rc;
				b_rc.Bottom = yp;
				b_rc.Top = yp - h;
				cv->Brush->Color = grp_col[n];
				cv->FillRect(b_rc);
				yp -= h;
			}
		}

		if (!s.IsEmpty()) {
			cv->Brush->Style = bsClear;
			cv->Font->Color  = SelectWorB(cv->Brush->Color);
			cv->TextOut(xp, 0, s);
		}

		xp += wd;
	}
}
//---------------------------------------------------------------------------
void __fastcall TRegExChecker::DetailCheckBoxClick(TObject *Sender)
{
	ResListBox->Items->Assign(DetailCheckBox->Checked? DetailList : ResultList);
}

//---------------------------------------------------------------------------
void __fastcall TRegExChecker::AssignSample(TStringList *lst)
{
	SampleListBox->Items->Assign(lst);
	int tw = 9;
	for (int i=0; i<SampleListBox->Count; i++) {
		UnicodeString s = SampleListBox->Items->Strings[i];
		if (s.Pos('\t')) tw = std::max(tw, str_len_half(get_pre_tab(s)) + 2);
	}
	SampleListBox->TabWidth = tw * 4;
}
//---------------------------------------------------------------------------
void __fastcall TRegExChecker::ReloadSample()
{
	if (file_exists(SampleFile)) {
		TDateTime dt = get_file_age(SampleFile);
		if (dt!=SampleTime) {
			std::unique_ptr<TStringList> s_lst(new TStringList());
			if (load_text_ex(RegExChecker->SampleFile, s_lst.get())) {
				SampleTime = dt;
				AssignSample(s_lst.get());
			}
		}
	}
}

//---------------------------------------------------------------------------
//ファイルからサンプルを読み込む
//---------------------------------------------------------------------------
void __fastcall TRegExChecker::LoadSamplActionExecute(TObject *Sender)
{
	UserModule->PrepareOpenDlg(_T("サンプルを開く"), F_FILTER_TXT, _T("*.txt"), ExtractFilePath(SampleFile));
	UnicodeString fnam;
	if (UserModule->OpenDlgToStr(fnam)) {
		std::unique_ptr<TStringList> s_lst(new TStringList());
		if (load_text_ex(fnam, s_lst.get())) {
			SampleFile = fnam;
			SampleTime = get_file_age(SampleFile);
			AssignSample(s_lst.get());
		}
	}
}
//---------------------------------------------------------------------------
//編集
//---------------------------------------------------------------------------
void __fastcall TRegExChecker::EditSampleActionExecute(TObject *Sender)
{
	open_by_TextEditor(SampleFile);
}
//---------------------------------------------------------------------------
void __fastcall TRegExChecker::EditSampleActionUpdate(TObject *Sender)
{
	((TAction*)Sender)->Enabled = file_exists(SampleFile);
}
//---------------------------------------------------------------------------
