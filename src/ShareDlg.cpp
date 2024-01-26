//----------------------------------------------------------------------//
// NyanFi																//
//  共有フォルダ/ライブラリ/検索設定/ディレクトリ選択					//
//----------------------------------------------------------------------//
#include "UserFunc.h"
#include "UserMdl.h"
#include "Global.h"
#include "EditItem.h"
#include "MainFrm.h"
#include "ShareDlg.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TNetShareDlg *NetShareDlg;

//---------------------------------------------------------------------------
int __fastcall sort_comp_DirIcon(TStringList *List, int Index1, int Index2)
{
	UnicodeString dnam0 = List->Strings[Index1];
	UnicodeString dnam1 = List->Strings[Index2];
	UnicodeString inam0 = get_FolderIconName(dnam0);
	UnicodeString inam1 = get_FolderIconName(dnam1);
	dnam0 = ExtractFileName(ExcludeTrailingPathDelimiter(dnam0));
	dnam1 = ExtractFileName(ExcludeTrailingPathDelimiter(dnam1));

	if (SameText(inam0, inam1)) return CompNameFN(dnam0, dnam1);
	if (inam0.IsEmpty()) return 1;
	if (inam1.IsEmpty()) return -1;
	return CompNameFN(inam0, inam1);
}

//---------------------------------------------------------------------------
__fastcall TNetShareDlg::TNetShareDlg(TComponent* Owner)
	: TForm(Owner)
{
	rqRetPath = false;
	isShare = isOnlySub = isLibrary = isFindSet = false;
	isPC = isUNC = false;
}
//---------------------------------------------------------------------------
void __fastcall TNetShareDlg::FormCreate(TObject *Sender)
{
	ListScrPanel = new UsrScrollPanel(ListPanel, ShareListBox, USCRPNL_FLAG_P_WP | USCRPNL_FLAG_L_WP);
}
//---------------------------------------------------------------------------
void __fastcall TNetShareDlg::FormShow(TObject *Sender)
{
	isPC = isUNC = false;

	if (isShare)
		IniFile->LoadPosInfo(this, DialogCenter);
	else if (isLibrary)
		IniFile->LoadPosInfo(this, DialogCenter, "Library");
	else if (isFindSet)
		IniFile->LoadPosInfo(this, DialogCenter, "FindSet");
	else
		IniFile->LoadPosInfo(this, DialogCenter, isOnlySub? "SelSub" : "SelDir");

	//中央揃え
	TControl *cp = (TControl *)((CurListTag==0)? NyanFiForm->L_Panel : NyanFiForm->R_Panel);
	TPoint p = cp->ClientToScreen(cp->ClientRect.CenteredRect(BoundsRect).Location);
	Left = p.x;
	Top  = p.y;

	//はみ出し修正
	cp = (TControl *)NyanFiForm->ListPanel;
	TPoint p0 = cp->ClientToScreen(Point(0, 0));
	TPoint p1 = cp->ClientToScreen(Point(0, cp->Height));
	if (Top < p0.y)			 	Top  = p0.y;
	if ((Top + Height) > p1.y)	Top  = p1.y - Height;
	if (Left < p0.x)			Left = p0.x;

	set_StdListBox(ShareListBox);
	set_UsrScrPanel(ListScrPanel);
	ShareListBox->Clear();

	::PostMessage(Handle, WM_FORM_SHOWED, 0, 0);
}
//---------------------------------------------------------------------------
void __fastcall TNetShareDlg::WmFormShowed(TMessage &msg)
{
	PathTabControl->Repaint();

	//共有フォルダ
	if (isShare) {
		if (!ComputerName.IsEmpty() && !StartsStr("\\\\", ComputerName)) ComputerName.Insert("\\\\", 1);
		ComputerName = ExcludeTrailingPathDelimiter(ComputerName);
		PathName     = ComputerName;
		UpdateShareList(ComputerName);
	}
	//ライブラリ
	else if (isLibrary) {
		Caption = "ライブラリ";
		std::unique_ptr<TStringList> l_lst(new TStringList());
		get_files(LibraryPath, "*.library-ms", l_lst.get());
		ShareListBox->Items->Assign(l_lst.get());
		ListBoxSetIndex(ShareListBox, 0);
	}
	//検索設定
	else if (isFindSet) {
		Caption = "検索設定";
		std::unique_ptr<TStringList> l_lst(new TStringList());
		std::unique_ptr<TStringList> s_lst(new TStringList());
		get_files(ExePath, "*.ini", l_lst.get(), true);
		for (int i=0,n=0; i<l_lst->Count; i++) {
			UnicodeString fnam = l_lst->Strings[i];
			std::unique_ptr<UsrIniFile> set_file(new UsrIniFile(fnam));
			UnicodeString sct = "FindSettings";
			if (set_file->SectionExists(sct)) {
				//ファイル名 [TAB] 表示色 [TAB] リストファイル名
				s_lst->Add(fnam + "\t" + set_file->ReadString(sct, "Color") + "\t" + set_file->ReadString(sct, "DirList"));
			}
		}
		s_lst->Sort();
		ShareListBox->Items->Assign(s_lst.get());
		ListBoxSetIndex(ShareListBox, 0);
		FileName = EmptyStr;
	}
	//ディレクトリの選択
	else {
		PathName = IncludeTrailingPathDelimiter(PathName);
		UpdatePathList(PathName);
	}

	ListScrPanel->UpdateKnob();

	UpdateBreadcrumb(PathName);
}
//---------------------------------------------------------------------------
void __fastcall TNetShareDlg::FormClose(TObject *Sender, TCloseAction &Action)
{
	if (isShare)
		IniFile->SavePosInfo(this);
	else if (isLibrary)
		IniFile->SavePosInfo(this, "Library");
	else if (isFindSet)
		IniFile->SavePosInfo(this, "FindSet");
	else
		IniFile->SavePosInfo(this, isOnlySub? "SelSub" : "SelDir");

	rqRetPath = false;
	isShare = isOnlySub = isLibrary = isFindSet = false;
	isPC  = false;
	Title = EmptyStr;
}
//---------------------------------------------------------------------------
void __fastcall TNetShareDlg::FormDestroy(TObject *Sender)
{
	delete ListScrPanel;
}

//---------------------------------------------------------------------------
void __fastcall TNetShareDlg::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	UnicodeString topic = HELPTOPIC_FL;
	if		(isShare)	topic += "#ShareList";
	else if (isLibrary)	topic += "#Library";
	else if (isFindSet)	topic += "#LoadFindSet";
	else if (rqRetPath)	topic  = EmptyStr;
	else				topic += "#SubDirList";

	if (!topic.IsEmpty())
		SpecialKeyProc(this, Key, Shift, topic.c_str());
	else
		SpecialKeyProc(this, Key, Shift);
}

//---------------------------------------------------------------------------
//共有フォルダ一覧の取得
//---------------------------------------------------------------------------
NET_API_STATUS __fastcall TNetShareDlg::GetShareList(
	UnicodeString cnam,		//\\コンピュータ名
	TListBox *lp)
{
	lp->Clear();
	static PSHARE_INFO_1 p_si = NULL;
	DWORD entry_cnt, total_cnt;
	cursor_HourGlass();
	NET_API_STATUS res = ::NetShareEnum(cnam.c_str(), 1, (LPBYTE *)&p_si, MAX_PREFERRED_LENGTH, &entry_cnt, &total_cnt, NULL);
	if (res==NERR_Success) {
		for (DWORD i=0; i<entry_cnt; i++) {
			if (p_si[i].shi1_type==STYPE_DISKTREE) {
				UnicodeString nnam = p_si[i].shi1_netname;
				if (!EndsStr("$", nnam)) lp->Items->Add(IncludeTrailingPathDelimiter(cnam) + nnam);
			}
		}
	}
	if (p_si) ::NetApiBufferFree(p_si);
	cursor_Default();
	return res;
}
//---------------------------------------------------------------------------
//共有フォルダ一覧の更新
//---------------------------------------------------------------------------
void __fastcall TNetShareDlg::UpdateShareList(
	UnicodeString cnam)	//\\コンピュータ名
{
	cnam = ExcludeTrailingPathDelimiter(cnam);
	Caption = yen_to_delimiter(cnam) + " - 共有フォルダ一覧";

	TListBox *lp = ShareListBox;
	NET_API_STATUS res = GetShareList(cnam, lp);
	if (res!=NERR_Success) {
		//コンピュータに接続
		NETRESOURCEW nr = {};
		nr.dwType		= RESOURCETYPE_ANY;
		nr.lpRemoteName = (LPWSTR)cnam.c_str();
		DWORD n_res = WNetAddConnection3W(this->Handle, &nr, NULL, NULL, CONNECT_INTERACTIVE);
		if (n_res==NO_ERROR) {
			res = GetShareList(cnam, lp);
		}
		else if (n_res==ERROR_CANCELLED) {
			Close();
			return;
		}
	}
	if (res!=NERR_Success) {
		beep_Warn();
		Caption = Caption + " - " + SysErrorMessage(res);
	}
	ListScrPanel->UpdateKnob();

	ListBoxSetIndex(lp, lp->Items->IndexOf(ExcludeTrailingPathDelimiter(CurPathName)));
}

//---------------------------------------------------------------------------
//ディレクトリ一覧の更新
//---------------------------------------------------------------------------
void __fastcall TNetShareDlg::UpdatePathList(
	UnicodeString pnam)	//基準ディレクトリ (EmptyStr ならドライブ選択)
{
	Caption = (!Title.IsEmpty()? (Title + " - ") : EmptyStr) +
				(pnam.IsEmpty()? UnicodeString("PC") : yen_to_delimiter(ExcludeTrailingPathDelimiter(pnam))) ;

	cursor_HourGlass();
	LibIdxBase = -1;
	std::unique_ptr<TStringList> d_lst(new TStringList());
	//ドライブ
	if (pnam.IsEmpty()) {
		isPC = true;
		for (int i=0; i<DriveInfoList->Count; i++) {
			drive_info *dp = (drive_info *)DriveInfoList->Objects[i];
			if (!dp->accessible) continue;
			d_lst->Add(UnicodeString().sprintf(_T("%s %s"), get_tkn(dp->drive_str, '\\').c_str(), dp->volume.c_str()));
		}
		//ライブラリ
		std::unique_ptr<TStringList> l_lst(new TStringList());
		get_files(LibraryPath, "*.library-ms", l_lst.get());
		if (l_lst->Count>0) {
			d_lst->Add("-");
			LibIdxBase = d_lst->Count;
			d_lst->AddStrings(l_lst.get());
		}
		else {
			LibIdxBase = d_lst->Count;
		}
	}
	//ディレクトリ
	else {
		isPC = false;
		pnam = IncludeTrailingPathDelimiter(pnam);
		TSearchRec sr;
		if (FindFirst(cv_ex_filename(pnam + "*"), faAnyFile, sr)==0) {
			do {
				if ((sr.Attr & faDirectory)==0) continue;
				if (!ShowHideAtr   && (sr.Attr & faHidden))  continue;
				if (!ShowSystemAtr && (sr.Attr & faSysFile)) continue;
				if (ContainsStr("..", sr.Name)) continue;
				d_lst->AddObject(pnam + sr.Name, (TObject*)(NativeInt)sr.Attr);
			} while(FindNext(sr)==0);
			FindClose(sr);
		}
		d_lst->CustomSort((DirSortMode[CurListTag]==6)? sort_comp_DirIcon : comp_NaturalOrder);
		if (!is_root_dir(pnam) && isOnlySub) d_lst->Insert(0, pnam + "..");
	}
	TListBox *lp = ShareListBox;
	lp->Items->Assign(d_lst.get());
	ListScrPanel->UpdateKnob();

	int idx = -1;
	for (int i=0; i<lp->Count && idx==-1; i++) {
		UnicodeString lbuf = lp->Items->Strings[i];
		if (pnam.IsEmpty()) lbuf = get_tkn(lbuf, ' ');
		if (StartsStr(IncludeTrailingPathDelimiter(lbuf), IncludeTrailingPathDelimiter(CurPathName))) idx = i;
	}
	ListBoxSetIndex(lp, idx);
	cursor_Default();
}
//---------------------------------------------------------------------------
//パンくずリストの更新
//---------------------------------------------------------------------------
void __fastcall TNetShareDlg::UpdateBreadcrumb(UnicodeString pnam)
{
	OutDebugStr(pnam);
	PathTabControl->Visible = false;
	PathTabControl->Height = get_FontHeightMgnS(PathTabControl->Font, 8, 8) + 2;
	PathTabControl->Tabs->Clear();
	isUNC = false;
	if (!isOnlySub && !isFindSet && !isLibrary) {
		isUNC = StartsStr("\\\\", pnam);
		if (!isUNC) PathTabControl->Tabs->Add("PC");
		TStringDynArray plst = split_path(pnam);
		for (int i=0; i<plst.Length; i++) PathTabControl->Tabs->Add(plst[i] + " >");
		PathTabControl->Visible  = true;
		PathTabControl->TabIndex = PathTabControl->Tabs->Count - 1;
	}
}
//---------------------------------------------------------------------------
//パンくずリストの処理
//---------------------------------------------------------------------------
void __fastcall TNetShareDlg::PathTabControlDrawTab(TCustomTabControl *Control, int TabIndex,
	const TRect &Rect, bool Active)
{
	TTabControl *tp = (TTabControl*)Control;
	TCanvas *cv = tp->Canvas;
	cv->Brush->Color = Active? col_bgOptTab : get_PanelColor();
	cv->Font->Color  = Active? col_fgOptTab : get_LabelColor();
	cv->FillRect(Rect);

	int yp = (Rect.Height() - cv->TextHeight("Q")) /2;
	int xp = Rect.Left + SCALED_THIS(4);
	UnicodeString s = get_tkn(PathTabControl->Tabs->Strings[TabIndex], " >");
	bool is_dir = (TabIndex>0 || StartsStr("\\\\", s));
	s = ReplaceStr(s, "\\", " ");
	cv->TextOut(xp, yp, s);
	if (is_dir) {
		xp += cv->TextWidth(s);
		cv->Brush->Style = bsClear;
		cv->Font->Color  = AdjustColor(get_LabelColor(), ADJCOL_LIGHT);
		cv->TextOut(xp, yp, " >");
	}
}
//---------------------------------------------------------------------------
void __fastcall TNetShareDlg::PathTabControlChange(TObject *Sender)
{
	int idx = PathTabControl->TabIndex;
	if (idx!=-1) {
		UnicodeString pnam = GetBreadcrumbStr(idx);
		if (is_computer_name(pnam)) {
			ComputerName = ExcludeTrailingPathDelimiter(pnam);
			UpdateShareList(ComputerName);
		}
		else {
			UpdatePathList(pnam);
		}
	}
}

//---------------------------------------------------------------------------
void __fastcall TNetShareDlg::ListPanelResize(TObject *Sender)
{
	ShareListBox->Invalidate();
}

//---------------------------------------------------------------------------
//リスト項目の描画
//---------------------------------------------------------------------------
void __fastcall TNetShareDlg::ShareListBoxDrawItem(TWinControl *Control, int Index,
	TRect &Rect, TOwnerDrawState State)
{
	TListBox *lp = (TListBox*)Control;
	TCanvas *cv = lp->Canvas;
	cv->Font->Assign(ListFont);
	cv->Brush->Color = get_ListBgCol();
	cv->FillRect(Rect);

	UnicodeString lbuf = lp->Items->Strings[Index];
	if (SameStr(lbuf, "-")) {
		draw_Separator(cv, Rect, get_ListBgCol());
	}
	else {
		int xp = Rect.Left + SCALED_THIS(2);
		int yp = Rect.Top  + get_TopMargin2(cv);

		//アクセスキー
		cv->Font->Color = get_ListFgCol();
		cv->Font->Style = cv->Font->Style << fsUnderline;
		if (isPC) {
			if (Index<LibIdxBase) {
				cv->TextOut(xp, yp, lbuf.SubString(1, 1));
			}
			else {
				int idx = Index - LibIdxBase;
				if (idx<10) cv->TextOut(xp, yp, UnicodeString().sprintf(_T("%u"), (idx + 1)%10));
			}
		}
		else if (Index<10) {
			cv->TextOut(xp, yp, UnicodeString().sprintf(_T("%u"), (Index + 1)%10));
		}

		cv->Font->Style = cv->Font->Style >> fsUnderline;
		xp += get_CharWidth(cv, 2);

		//ライブラリ
		if (isLibrary || (isPC && Index>=LibIdxBase)) {
			draw_SmallIcon2(lbuf, cv, xp, std::max(yp + (cv->TextHeight("Q") - SCALED_THIS(16))/2, 0), this);
			xp += SCALED_THIS(20);
			cv->Font->Color = col_Folder;
			cv->TextOut(xp, yp, get_base_name(lbuf));
		}
		//検索設定
		else if (isFindSet) {
			TStringDynArray itm_buf = split_strings_tab(lbuf);
			cv->Font->Color = TColor(get_array_item(itm_buf, 1).ToIntDef((int)col_Folder));
			cv->TextOut(xp, yp, get_base_name(get_array_item(itm_buf, 0)));
		}
		//ドライブ
		else if (isPC) {
			drive_info *dp = get_DriveInfo(lbuf);
			if (dp) {
				TIcon *ip = dp->small_ico;
				if (ip && ip->Handle) {
					::DrawIconEx(cv->Handle, xp, yp + 1, ip->Handle,
									SCALED_THIS(16), SCALED_THIS(16), 0, NULL, DI_NORMAL);
				}
			}
			xp += SCALED_THIS(20);
			cv->Font->Color = get_ListFgCol();
			cv->TextOut(xp, yp, get_tkn_r(lbuf, ' '));
		}
		//ディレクトリ、その他
		else {
			if (IconMode==1 || IconMode==2) {
				HICON hIcon = get_folder_icon(lbuf);
				if (hIcon) {
					::DrawIconEx(cv->Handle, xp, yp + 1, hIcon,
									SCALED_THIS(16), SCALED_THIS(16), 0, NULL, DI_NORMAL);
				}
				xp += SCALED_THIS(20);
			}
			int attr = (int)lp->Items->Objects[Index];
			cv->Font->Color =
				(attr & faSysFile) ? col_System :
				(attr & faHidden)  ? col_Hidden :
				(attr & faReadOnly)? col_ReadOnly :
				(attr & faSymLink) ? col_SymLink : col_Folder;
			cv->TextOut(xp, yp, ExtractFileName(lbuf));
			xp += cv->TextWidth(ExtractFileName(lbuf));
		}

		//ディレクトリのタイムスタンプ
		if (!isPC && !isLibrary && !isFindSet) {
			TDateTime dt = get_file_age(lbuf);
			if (dt!=(TDateTime)0) {
				UnicodeString s = get_TimeStampStr(dt);
				int x_t = ListPanel->ClientWidth - cv->TextWidth(s + "X");
				x_t -= ((ScrBarStyle>0)? ListScrPanel->KnobWidth : get_SysMetricsForPPI(SM_CXVSCROLL, CurrentPPI));
				if (x_t > xp) {
					cv->Font->Color = get_TimeColor(dt, get_ListFgCol());
					cv->TextOut(x_t, yp, s);
				} 
			}
		}
	}

	//カーソル
	draw_ListCursor(lp, Rect, Index, State);
}

//---------------------------------------------------------------------------
void __fastcall TNetShareDlg::ShareListBoxKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	TListBox *lp = (TListBox*)Sender;
	UnicodeString KeyStr = get_KeyStr(Key, Shift);
	UnicodeString cmd_F  = Key_to_CmdF(KeyStr);

	//ドライブ確定
	UnicodeString dstr;
	if (isPC && (equal_ENTER(KeyStr) || (!KeyStr.IsEmpty() && isalpha(KeyStr[1])))) {
		if (equal_ENTER(KeyStr)) {
			int idx = lp->ItemIndex;
			if (idx!=-1 && idx<LibIdxBase-1) dstr = IncludeTrailingPathDelimiter(get_tkn(lp->Items->Strings[idx], ' '));
		}
		else {
			for (int i=0; i<LibIdxBase; i++) {
				if (StartsText(KeyStr, lp->Items->Strings[i])) {
					dstr.sprintf(_T("%c:\\"), KeyStr[1]);
					break;
				}
			}
		}
	}
	if (!dstr.IsEmpty()) {
		if (is_drive_accessible(dstr)) {
			NyanFiForm->RecoverFileList();
			NyanFiForm->UpdateCurDrive(dstr);
			ModalResult = mrOk;
		}
		else {
			beep_Warn();
		}
		Key = 0;
		return;
	}

	//確定
	bool handled = true;
	if (is_Num0to9(KeyStr) || equal_ENTER(KeyStr)) {
		int idx;
		if (is_Num0to9(KeyStr)) {
			idx = (KeyStr.ToIntDef(0) + 9)%10;
			if (isPC) idx += LibIdxBase;
		}
		else {
			idx = lp->ItemIndex;
		}

		if (idx!=-1) {
			UnicodeString lbuf = lp->Items->Strings[idx];
			if (!SameStr(lbuf, "-")) {
				//ライブラリ
				if (isLibrary || (isPC && idx>=LibIdxBase)) {
					NyanFiForm->PopSelLibrary(lbuf, CurListTag, lp);
				}
				//検索設定
				else if (isFindSet) {
					FileName = get_pre_tab(lp->Items->Strings[idx]);
				}
				//ディレクトリ、共有
				else {
					UnicodeString pnam = GetListPathName(idx);
					if (rqRetPath) {
						PathName = pnam;
					}
					else {
						cursor_HourGlass();
						NyanFiForm->UpdateCurPath(pnam);
						cursor_Default();
					}
				}
				ModalResult = mrOk;
			}
		}
	}
	//パンくずリストを進む
	else if (PathTabControl->Visible && is_ToRightOpe(KeyStr, cmd_F)) {
		int p_idx = PathTabControl->TabIndex;
		int idx = lp->ItemIndex;
		UnicodeString s = (idx!=-1)? lp->Items->Strings[idx] : EmptyStr;
		if (EndsText(".library-ms", s) || s=="-") s = EmptyStr;
		if (!s.IsEmpty()) {
			if (p_idx==PathTabControl->Tabs->Count-1) {
				UpdateBreadcrumb(GetListPathName(idx));
				PathTabControlChange(PathTabControl);
			}
			else {
				PathTabControl->TabIndex = p_idx + 1;
				PathTabControlChange(PathTabControl);
				if (PathTabControl->TabIndex<PathTabControl->Tabs->Count - 1) {
					UnicodeString pnam = GetBreadcrumbStr(PathTabControl->TabIndex + 1);
					lp->ItemIndex = lp->Items->IndexOf(ExcludeTrailingPathDelimiter(pnam));
				}
			}
		}
	}
	//パンくずリストを戻る
	else if (PathTabControl->Visible && (is_ToLeftOpe(KeyStr, cmd_F) || SameText(get_CmdStr(cmd_F), "ToParent"))) {
		int p_idx = PathTabControl->TabIndex;
		if (p_idx>0) {
			UnicodeString pnam = GetBreadcrumbStr(p_idx);
			PathTabControl->TabIndex = p_idx -1;
			PathTabControlChange(PathTabControl);
			pnam = ExcludeTrailingPathDelimiter(pnam);
			if (PathTabControl->TabIndex==0) {
				for (int i=0; i<lp->Count; i++) {
					if (SameText(get_tkn(lp->Items->Strings[i], ' '), pnam)) {
						lp->ItemIndex = i;
						break;
					}
				}
			}
			else {
				lp->ItemIndex = lp->Items->IndexOf(ExcludeTrailingPathDelimiter(pnam));
			}
		}
	}
	//ポップアップメニュー
	else if (contained_wd_i(KeysStr_Popup, KeyStr)) {
		show_PopupMenu(lp);
	}
	//カーソル移動
	else if	(ExeCmdListBox(lp, cmd_F)) {
		if (PathTabControl->TabIndex<PathTabControl->Tabs->Count-1) {
			int n = PathTabControl->Tabs->Count - PathTabControl->TabIndex - 1;
			for (int i=0; i<n; i++) PathTabControl->Tabs->Delete(PathTabControl->Tabs->Count - 1);
		}
	}
	//頭文字サーチ
	else if ((isOnlySub || PathTabControl->Visible) && is_IniSeaKey(KeyStr)) {
		ListBoxInitialSearch(lp, KeyStr, true);
	}
	//コピー
	else if (SameText(KeyStr, KeyStr_Copy) || SameText(cmd_F, "CopyFileName")) {
		if (lp->ItemIndex!=-1) {
			UnicodeString lbuf = lp->Items->Strings[lp->ItemIndex];
			if (isPC) lbuf = IncludeTrailingPathDelimiter(get_tkn(lbuf, ' '));
			copy_to_Clipboard(lbuf);
		}
	}
	//プロパティ
	else if (SameText(cmd_F, "PropertyDlg")) {
		PropertyAction->Execute();
	}
	//閉じる
	else if (SameText(cmd_F, "ReturnList")) {
		ModalResult = mrCancel;
	}
	else {
		handled = false;
	}

	if (!is_DialogKey(Key) || handled) Key = 0;
}
//---------------------------------------------------------------------------
void __fastcall TNetShareDlg::ShareListBoxKeyPress(TObject *Sender, System::WideChar &Key)
{
	//インクリメンタルサーチを回避
	if (_istalnum(Key)) Key = 0;
}
//---------------------------------------------------------------------------
void __fastcall TNetShareDlg::ShareListBoxClick(TObject *Sender)
{
	if (PathTabControl->TabIndex<PathTabControl->Tabs->Count-1) {
		int n = PathTabControl->Tabs->Count - PathTabControl->TabIndex - 1;
		for (int i=0; i<n; i++) PathTabControl->Tabs->Delete(PathTabControl->Tabs->Count - 1);
	}
}
//---------------------------------------------------------------------------
void __fastcall TNetShareDlg::ShareListBoxDblClick(TObject *Sender)
{
	perform_Key_RETURN((TControl*)Sender);
}

//---------------------------------------------------------------------------
//UNCパスをコピー
//---------------------------------------------------------------------------
void __fastcall TNetShareDlg::CopyUncActionExecute(TObject *Sender)
{
	TListBox *lp = ShareListBox;
	if (lp->ItemIndex!=-1) copy_to_Clipboard(lp->Items->Strings[lp->ItemIndex]);
}
//---------------------------------------------------------------------------
void __fastcall TNetShareDlg::CopyUncActionUpdate(TObject *Sender)
{
	TAction *ap = (TAction *)Sender;
	ap->Visible = isUNC;
	ap->Enabled = ap->Visible && (ShareListBox->ItemIndex!=-1);
}
//---------------------------------------------------------------------------
//すべてのUNCパスをコピー
//---------------------------------------------------------------------------
void __fastcall TNetShareDlg::CopyUncAllActionExecute(TObject *Sender)
{
	TListBox *lp = ShareListBox;
	std::unique_ptr<TStringList> lst(new TStringList());
	for (int i=0; i<lp->Count; i++) {
		lst->Add(IncludeTrailingPathDelimiter(ComputerName) + lp->Items->Strings[i]);
	}
	copy_to_Clipboard(lst->Text);
}
//---------------------------------------------------------------------------
void __fastcall TNetShareDlg::CopyUncAllActionUpdate(TObject *Sender)
{
	TAction *ap = (TAction *)Sender;
	ap->Visible = isUNC;
	ap->Enabled = ap->Visible && (ShareListBox->Count>0);
}
//---------------------------------------------------------------------------
//ディレクトリ・パスをコピー
//---------------------------------------------------------------------------
void __fastcall TNetShareDlg::CopyPathActionExecute(TObject *Sender)
{
	TListBox *lp = ShareListBox;
	if (lp->ItemIndex!=-1) {
		UnicodeString lbuf = lp->Items->Strings[lp->ItemIndex];
		if (isPC) lbuf = IncludeTrailingPathDelimiter(get_tkn(lbuf, ' '));
		copy_to_Clipboard(lbuf);
	}
}
//---------------------------------------------------------------------------
void __fastcall TNetShareDlg::CopyPathActionUpdate(TObject *Sender)
{
	TAction *ap = (TAction *)Sender;
	ap->Visible = isOnlySub || (PathTabControl->Visible && !isUNC);
	ap->Enabled = ap->Visible && (ShareListBox->ItemIndex!=-1);
}
//---------------------------------------------------------------------------
//すべてのディレクトリ・パスをコピー
//---------------------------------------------------------------------------
void __fastcall TNetShareDlg::CopyPathAllActionExecute(TObject *Sender)
{
	TListBox *lp = ShareListBox;
	std::unique_ptr<TStringList> lst(new TStringList());
	bool is_drv = isPC;
	for (int i=0; i<lp->Count; i++) {
		UnicodeString lbuf = lp->Items->Strings[i];
		if (is_drv && is_separator(lbuf)) is_drv = false;
		if (is_drv) lbuf = IncludeTrailingPathDelimiter(get_tkn(lbuf, ' '));
		lst->Add(lbuf);
	}
	copy_to_Clipboard(lst->Text);
}
//---------------------------------------------------------------------------
void __fastcall TNetShareDlg::CopyPathAllActionUpdate(TObject *Sender)
{
	TAction *ap = (TAction *)Sender;
	ap->Visible = isOnlySub || (PathTabControl->Visible && !isUNC);
	ap->Enabled = ap->Visible && (ShareListBox->Count>0);
}
//---------------------------------------------------------------------------
//表示色の設定
//---------------------------------------------------------------------------
void __fastcall TNetShareDlg::SetColorActionExecute(TObject *Sender)
{
	TListBox *lp = ShareListBox;
	int idx = lp->ItemIndex;
	if (idx!=-1) {
		TStringDynArray itm_buf = split_strings_tab(lp->Items->Strings[idx]);
		UnicodeString fnam = get_array_item(itm_buf, 0);
		UnicodeString col  = get_array_item(itm_buf, 1);
		UserModule->ColorDlg->Color = !col.IsEmpty()? TColor(col.ToIntDef((int)col_Folder)) : col_Folder;
		if (UserModule->ColorDlg->Execute()) {
			col = IntToStr((int)UserModule->ColorDlg->Color);
			std::unique_ptr<UsrIniFile> set_file(new UsrIniFile(fnam));
			UnicodeString sct = "FindSettings";
			set_file->WriteString(sct, "Color", col);
			set_file->UpdateFile(true);
			lp->Items->Strings[idx] = fnam + "\t" + col + "\t" + set_file->ReadString(sct, "DirList");
			lp->Repaint();
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TNetShareDlg::SetColorActionUpdate(TObject *Sender)
{
	TAction *ap = (TAction *)Sender;
	ap->Visible = isFindSet;
	ap->Enabled = ap->Visible && (ShareListBox->ItemIndex!=-1);
}
//---------------------------------------------------------------------------
//リストファイルの編集
//---------------------------------------------------------------------------
void __fastcall TNetShareDlg::EditListActionExecute(TObject *Sender)
{
	TListBox *lp = ShareListBox;
	if (lp->ItemIndex!=-1) {
		if (!open_by_TextEditor(get_tsv_item(lp->Items->Strings[lp->ItemIndex], 2))) msgbox_ERR(GlobalErrMsg);
	}
}
//---------------------------------------------------------------------------
void __fastcall TNetShareDlg::EditListActionUpdate(TObject *Sender)
{
	TAction *ap = (TAction *)Sender;
	ap->Visible = isFindSet;
	TListBox *lp = ShareListBox;
	ap->Enabled = (ap->Visible && lp->ItemIndex!=-1 && !get_tsv_item(lp->Items->Strings[lp->ItemIndex], 2).IsEmpty());
}
//---------------------------------------------------------------------------
//除外ディレクトリの設定
//---------------------------------------------------------------------------
void __fastcall TNetShareDlg::SetSkipDirActionExecute(TObject *Sender)
{
	TListBox *lp = ShareListBox;
	int idx = lp->ItemIndex;
	if (idx!=-1) {
		std::unique_ptr<UsrIniFile> set_file(new UsrIniFile(get_tsv_item(lp->Items->Strings[idx], 0)));
		UnicodeString sct = "FindSettings";
		if (!EditItemDlg) EditItemDlg = new TEditItemDlg(this);	//初回に動的作成
		EditItemDlg->AssignText("除外ディレクトリ", set_file->ReadString(sct, "SkipDir"));
		if (show_ModalDlg(EditItemDlg)==mrOk) {
			set_file->WriteString(sct, "SkipDir", EditItemDlg->RetStr);
			set_file->UpdateFile(true);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TNetShareDlg::SetSkipDirActionUpdate(TObject *Sender)
{
	TAction *ap = (TAction *)Sender;
	ap->Visible = isFindSet;
	ap->Enabled = ap->Visible && (ShareListBox->ItemIndex!=-1);
}

//---------------------------------------------------------------------------
//プロパティ
//---------------------------------------------------------------------------
void __fastcall TNetShareDlg::PropertyActionExecute(TObject *Sender)
{
	TListBox *lp = ShareListBox;
	if (lp->ItemIndex!=-1) ShowPropertyDialog(lp->Items->Strings[lp->ItemIndex]);
}
//---------------------------------------------------------------------------
void __fastcall TNetShareDlg::PropertyActionUpdate(TObject *Sender)
{
	TAction *ap = (TAction *)Sender;
	ap->Visible = isOnlySub || PathTabControl->Visible;
	ap->Enabled = ap->Visible && (ShareListBox->ItemIndex!=-1);
}
//---------------------------------------------------------------------------
