//----------------------------------------------------------------------//
// 汎用共通関数															//
//																		//
//----------------------------------------------------------------------//
#include <wininet.h>
#include <setupapi.h>
#include <cfgmgr32.h>
#include "usr_scale.h"
#include "usr_shell.h"
#include "usr_color.h"
#include "UserFunc.h"

#pragma link "win64\\release\\psdk\\wininet.a"

//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
//「ポインターを自動的に規定のボタン上に移動」が有効化?
//---------------------------------------------------------------------------
bool is_SnapToDefBtn()
{
	BOOL sw;
	return (::SystemParametersInfo(SPI_GETSNAPTODEFBUTTON, 0, &sw, 0) && sw);
}

//---------------------------------------------------------------------------
//マウスカーソル位置のウィンドウを取得
//---------------------------------------------------------------------------
HWND get_window_from_pos()
{
	POINT p;
	::GetCursorPos(&p);
	return ::WindowFromPoint(p);
}

//---------------------------------------------------------------------------
//Vista以降の拡張フレームに対応したウィンドウ長方形の取得
//---------------------------------------------------------------------------
TRect get_window_rect(HWND hWnd)
{
	TRect rc = Rect(0, 0, 0, 0);
	if (::DwmGetWindowAttribute(hWnd, DWMWA_EXTENDED_FRAME_BOUNDS, &rc, sizeof(rc))!=S_OK) ::GetWindowRect(hWnd, &rc);
	if ((rc.Top > rc.Bottom) || (rc.Left > rc.Right)) rc = Rect(0, 0, 0, 0);
	return rc;
}
//---------------------------------------------------------------------------
//Vista以降の拡張フレームに対応したサイズ設定
//---------------------------------------------------------------------------
void set_window_pos_ex(HWND hWnd, TRect rc)
{
	TRect rc1, rc2;
	::GetWindowRect(hWnd, &rc1);
	if (::DwmGetWindowAttribute(hWnd, DWMWA_EXTENDED_FRAME_BOUNDS, &rc2, sizeof(rc2))!=S_OK) rc2 = rc1;
	rc.Left   += (rc1.Left   - rc2.Left);
	rc.Right  += (rc1.Right  - rc2.Right);
	rc.Top	  += (rc1.Top    - rc2.Top);
	rc.Bottom += (rc1.Bottom - rc2.Bottom);

	if (::IsIconic(hWnd)) ::ShowWindow(hWnd, SW_RESTORE);
	::SetWindowPos(hWnd, HWND_TOP, rc.Left, rc.Top, rc.Width(), rc.Height(), SWP_SHOWWINDOW);
}

//---------------------------------------------------------------------------
//フォームが表示モニタからはみ出していたら収まるように調整
//---------------------------------------------------------------------------
void adjust_form_pos(TForm *frm)
{
	TRect frm_rc = frm->BoundsRect;
	TRect mon_rc = frm->Monitor->BoundsRect;
	int dx = 0, dy = 0;
	if (frm_rc.Right > mon_rc.Right)	dx = mon_rc.Right - frm_rc.Right;
	if (frm_rc.Bottom > mon_rc.Bottom)	dy = mon_rc.Bottom - frm_rc.Bottom;
	if (frm_rc.Left < mon_rc.Left)		dx = mon_rc.Left - frm_rc.Left;
	if (frm_rc.Top < mon_rc.Top)		dy = mon_rc.Top - frm_rc.Top;
	if (dx!=0 || dy!=0) {
		OffsetRect(frm_rc, dx, dy);
		frm->BoundsRect = frm_rc;
	}
}

//---------------------------------------------------------------------------
//ダイアログを呼び出し元フォームの中央に表示
//	モニタからはみ出したら収まるように調整
//	対象は Position = poDesigned
//---------------------------------------------------------------------------
int show_ModalDlg(TForm *dlg)
{
	TForm *frm = (Screen->ActiveForm && Screen->ActiveForm!=Application->MainForm)?
						Screen->ActiveForm : Application->MainForm;
	dlg->Left = frm->Left;
	dlg->Top  = frm->Top;
	dlg->BoundsRect = frm->BoundsRect.CenteredRect(dlg->BoundsRect);
	adjust_form_pos(dlg);
	return dlg->ShowModal();
}

//---------------------------------------------------------------------------
//コントロールに右クリックメニューを表示
//---------------------------------------------------------------------------
void show_PopupMenu(TPopupMenu *mp, TControl *cp)
{
	if (mp && cp) {
		TPoint p = cp->ClientToScreen(Point(16, 16));
		ClearKeyBuff(true);
		mp->Popup(p.x, p.y);
	}
}
//---------------------------------------------------------------------------
void show_PopupMenu(TListBox *lp)
{
	show_PopupMenu(lp->PopupMenu, lp);
}
//---------------------------------------------------------------------------
void show_PopupMenu(TCheckListBox *lp)
{
	show_PopupMenu(lp->PopupMenu, lp);
}
//---------------------------------------------------------------------------
void show_PopupMenu(TStringGrid *gp)
{
	show_PopupMenu(gp->PopupMenu, gp);
}

//---------------------------------------------------------------------------
//ListBox にテキストを設定
//---------------------------------------------------------------------------
void set_ListBoxText(TListBox *lp, const _TCHAR *s)
{
	lp->Items->Text = s;
}
//---------------------------------------------------------------------------
//ComboBox にテキストを設定
//---------------------------------------------------------------------------
void set_ComboBoxText(TComboBox *cp, const _TCHAR *s)
{
	cp->Items->Text = s;
}

//---------------------------------------------------------------------------
//ComboBox に履歴を追加
//---------------------------------------------------------------------------
void add_ComboBox_history(TComboBox *cp, UnicodeString kwd)
{
	if (!cp) return;

	if (kwd.IsEmpty()) kwd = cp->Text;
	if (!kwd.IsEmpty()) {
		TStrings *lp = cp->Items;
		int idx = lp->IndexOf(kwd);
		if (idx!=-1) lp->Delete(idx);
		lp->Insert(0, kwd);

		if (cp->Style==csDropDownList)
			cp->ItemIndex = 0;
		else
			cp->Text = kwd;
	}
}
//---------------------------------------------------------------------------
//ComboBox から履歴を削除
//---------------------------------------------------------------------------
int del_ComboBox_history(TComboBox *cp, UnicodeString kwd)
{
	int idx = -1;
	if (cp) {
		if (kwd.IsEmpty()) kwd = cp->Text;
		if (!kwd.IsEmpty()) {
			TStrings *lp = cp->Items;
			idx = lp->IndexOf(kwd);
			if (idx!=-1) lp->Delete(idx);
			cp->Text = EmptyStr;
		}
	}
	return idx;
}

//---------------------------------------------------------------------------
//クリップボード・テキストを取得
//---------------------------------------------------------------------------
UnicodeString GetClipboardText(
	bool top_sw)	//一行目のみ取得	(default = false)
{
	UnicodeString ret_str;
	if (Clipboard()->HasFormat(CF_TEXT)) {
		if (top_sw) {
			std::unique_ptr<TStringList> sbuf(new TStringList());
			sbuf->Text = Clipboard()->AsText;
			if (sbuf->Count>0) ret_str = sbuf->Strings[0];
		}
		else {
			ret_str = Clipboard()->AsText;
		}
	}
	return ret_str;
}

//---------------------------------------------------------------------------
//IMEを開いているか?
//---------------------------------------------------------------------------
bool is_IME_Open(HWND hWnd)
{
	bool ret  = false;
	HIMC hIMC = ::ImmGetContext(hWnd);
	if (hIMC) {
		ret = ::ImmGetOpenStatus(hIMC);
		::ImmReleaseContext(hWnd, hIMC);
	}
	return ret;
}
//---------------------------------------------------------------------------
//IME入力中?
//---------------------------------------------------------------------------
bool is_IME_Typing(HWND hWnd)
{
	bool ret = false;
	HIMC hIMC = ::ImmGetContext(hWnd);
	if (hIMC) {
		ret = ::ImmGetOpenStatus(hIMC) && ::ImmGetCompositionString(hIMC, GCS_COMPSTR, NULL, 0)>0;
		::ImmReleaseContext(hWnd, hIMC);
	}
	return ret;
}
//---------------------------------------------------------------------------
//IME入力なし
//---------------------------------------------------------------------------
bool is_IME_Empty(HWND hWnd)
{
	bool ret = false;
	HIMC hIMC = ::ImmGetContext(hWnd);
	if (hIMC) {
		ret = ::ImmGetOpenStatus(hIMC) && ::ImmGetCompositionString(hIMC, GCS_COMPSTR, NULL, 0)==0;
		::ImmReleaseContext(hWnd, hIMC);
	}
	return ret;
}
//---------------------------------------------------------------------------
//IMEを閉じる
//---------------------------------------------------------------------------
void CloseIME(HWND hWnd)
{
	HIMC hIMC = ::ImmGetContext(hWnd);
	if (hIMC) {
		if (::ImmGetOpenStatus(hIMC)) ::ImmSetOpenStatus(hIMC, FALSE);
		::ImmReleaseContext(hWnd, hIMC);
	}
}

//---------------------------------------------------------------------------
//リストボックスの項目位置にマウスカーソルを移動
//---------------------------------------------------------------------------
TPoint get_ListItemPos(TListBox *lp, int xp)
{
	if (xp==0) xp = lp->ClientWidth/3;
	return lp->ClientToScreen(Point(xp, (lp->ItemIndex - lp->TopIndex) * lp->ItemHeight + lp->ItemHeight/2));
}

//---------------------------------------------------------------------------
void pos_ListBoxItem(TListBox *lp, int xp)
{
	if (xp==0) xp = lp->ClientWidth/3;
	Mouse->CursorPos = get_ListItemPos(lp, xp);
}

//---------------------------------------------------------------------------
//指定キャンバスのフォントが内部レディングを持っているか？
//---------------------------------------------------------------------------
bool has_Leading(TCanvas *cv)
{
	return (cv->TextHeight("Q")>abs(cv->Font->Height));
}

//---------------------------------------------------------------------------
//指定フォントによる描画幅を取得
//---------------------------------------------------------------------------
int get_CharWidth_Font(
	TFont *font,
	int n)			//半角単位の文字数
{
	std::unique_ptr<Graphics::TBitmap> bmp(new Graphics::TBitmap());
	TCanvas *cv = bmp->Canvas;
	cv->Font->Assign(font);
	return get_CharWidth(cv, n);
}

//---------------------------------------------------------------------------
//入力欄の文字列を数値に
//---------------------------------------------------------------------------
int EditToInt(TLabeledEdit *ep,
	int def)	//デフォルト値 (default = 0);
{
	return ep->Text.ToIntDef(def);
}
//---------------------------------------------------------------------------
int EditToInt(TEdit *ep, int def)
{
	return ep->Text.ToIntDef(def);
}

//---------------------------------------------------------------------------
//ファイル名入力欄の選択状態を順に切り替える
//---------------------------------------------------------------------------
void ChangeSelFileNameEdit(TCustomEdit *ep,
	bool is_dir)	// (default = false)
{
	int p = !is_dir? (pos_r(".", ep->Text) - 1) : -1;
	if (p<0) p = ep->Text.Length();
	int idx = (ep->SelStart==0 && ep->SelLength==0)? 1 :
			  (ep->SelStart==0 && ep->SelLength==p
				&& ep->SelLength<ep->Text.Length())? 2 :
			  (ep->SelStart==0 && ep->SelLength>=p)? 3 : 0;
	idx = (idx + 1)%4;
	switch (idx) {
	case 1:		//名前の先頭
		ep->SelStart = 0;
		break;
	case 2:		//ファイル名主部を選択
		ep->SelStart  = 0;
		ep->SelLength = p;
		break;
	case 3:		//ファイル名全体を選択
		ep->SelectAll();
		break;
	default:	//末尾
		ep->SelStart = p;
	}
}

//---------------------------------------------------------------------------
//コマンド入力欄の選択状態を順に切り替える
//---------------------------------------------------------------------------
void ChangeSelCmdComboBox(TComboBox *cp)
{
	int pos = -1;
	int len = -1;
	TMatch mt = TRegEx::Match(cp->Text, "[^_]+_(?:\"(.+)\"|(.+))");
	if (mt.Success && mt.Groups.Count>1) {
		for (int i=1; i<mt.Groups.Count; i++) {
			if (mt.Groups.Item[i].Success && mt.Groups.Item[i].Length>0) {
				pos = mt.Groups.Item[i].Index - 1;
				len = mt.Groups.Item[i].Length;
				break; 
			}
		}
	}

	int idx = (cp->SelStart==0 && cp->SelLength==cp->Text.Length())? 1 :
			  			  (cp->SelStart==pos && cp->SelLength==len)? 2 : 0;
	idx = (idx + 1)%(len>0? 3 : 2);
	switch (idx) {
	case 1:		//全体を選択
		cp->SelectAll();
		break;
	case 2:		//パラメータを選択
		cp->SelStart  = pos;
		cp->SelLength = len;
		break;
	default:	//末尾
		cp->SelStart = cp->Text.Length();
	}
}
//---------------------------------------------------------------------------
void ChangeSelCmdEdit(TCustomEdit *ep)
{
	int pos = -1;
	int len = -1;
	TMatch mt = TRegEx::Match(ep->Text, "[^_]+_(?:\"(.+)\"|(.+))");
	if (mt.Success && mt.Groups.Count>1) {
		for (int i=1; i<mt.Groups.Count; i++) {
			if (mt.Groups.Item[i].Success && mt.Groups.Item[i].Length>0) {
				pos = mt.Groups.Item[i].Index - 1;
				len = mt.Groups.Item[i].Length;
				break; 
			}
		}
	}

	int idx = (ep->SelStart==0 && ep->SelLength==ep->Text.Length())? 1 :
			  			  (ep->SelStart==pos && ep->SelLength==len)? 2 : 0;
	idx = (idx + 1)%(len>0? 3 : 2);
	switch (idx) {
	case 1:		//全体を選択
		ep->SelectAll();
		break;
	case 2:		//パラメータを選択
		ep->SelStart  = pos;
		ep->SelLength = len;
		break;
	default:	//末尾
		ep->SelStart = ep->Text.Length();
	}
}

//---------------------------------------------------------------------------
//年月日から TDate を取得 (月末補正)
//！不正な年/月を指定すると例外を送出
//---------------------------------------------------------------------------
TDate set_NormDay(unsigned short y, unsigned short m, unsigned short d)
{
	unsigned short d_max = DaysInMonth(TDate(y, m, 1));
	return TDate(y, m, (d>d_max)? d_max : d);
}

//---------------------------------------------------------------------------
//文字列を TDateTime に変換
//---------------------------------------------------------------------------
bool ToDateTime(UnicodeString s, TDateTime *dt)
{
	try {
		*dt = str_to_DateTime(to_HalfWidth(Trim(s)));
		return true;
	}
	catch (...) {
		return false;
	}
}

//---------------------------------------------------------------------------
//日時文字列を取得
//---------------------------------------------------------------------------
UnicodeString format_DateTime(
	TDateTime dt,	//日時
	bool omit)		//同日なら日付を省略 (default = false)
{
	if (dt==(TDateTime)0) {
		return UnicodeString("???\?/?\?/?? ??:??:??");
	}
	else {
		if (omit && IsToday(dt))
			return FormatDateTime("hh:nn:ss", dt);
		else
			return FormatDateTime("yyyy'/'mm'/'dd hh:nn:ss", dt);
	}
}
//---------------------------------------------------------------------------
//日付文字列を取得
//---------------------------------------------------------------------------
UnicodeString format_Date(TDateTime dt)
{
	return FormatDateTime("yyyy'/'mm'/'dd", dt);
}

//---------------------------------------------------------------------------
//日時文字列を取得 (FormatDateTime の拡張)
// $EN がある場合ロケールを en-US にする
//---------------------------------------------------------------------------
UnicodeString format_DateTimeEx(UnicodeString fmt, TDateTime dt)
{
	TFormatSettings fs = remove_text(fmt, "$EN")? TFormatSettings::Create("en-US") : TFormatSettings::Create();
	fmt = ReplaceStr(ReplaceStr(fmt, "\'/\'", "/"), "/", "\'/\'");
	return FormatDateTime(fmt, dt, fs);
}

//---------------------------------------------------------------------------
//日付条件を取得
//　相対指定: {<|=|>}-n{D|M|Y}　　(D:日、M:月、Y:年)
//　絶対指定: {<|=|>}yyyy/mm/dd
//	  	  今日付: TD
//  カーソル位置: CP (= ct)
//
//  戻り値 : 1: < より古い/ 2: = 同じ/ 3: > より新しい 
//			 0: 条件なし/ -1: エラー
//---------------------------------------------------------------------------
int get_DateCond(UnicodeString prm, TDateTime &dt, TDateTime ct)
{
	try {
		int cnd = 0;
		if (!prm.IsEmpty()) {
			if		(SameText(prm, "TD")) prm = "=" + format_Date(Date());
			else if (SameText(prm, "CP")) prm = "=" + format_Date(ct);

			cnd = UnicodeString("<=>").Pos(prm[1]);
			if (cnd>0) {
				prm.Delete(1, 1);
				//絶対指定
				if (TRegEx::IsMatch(prm, "^\\d{4}/\\d{2}/\\d{2}$")) {
					dt = str_to_DateTime(prm);
				}
				//相対指定
				else {
					UnicodeString ut_str = prm.SubString(prm.Length(), 1).UpperCase();
					if (!ContainsText("DMY", ut_str)) Abort();
					delete_end(prm);
					dt = Date();
					int dn = prm.ToIntDef(0);
					if (dn!=0) {
						switch (idx_of_word_i("D|M|Y", ut_str)) {
						case 0: dt = IncDay(  dt, dn); break;
						case 1: dt = IncMonth(dt, dn); break;
						case 2: dt = IncYear( dt, dn); break;
						}
					}
				}
			}
			else {
				cnd = -1;
			}
		}

		return cnd;
	}
	catch (...) {
		return -1;
	}
}

//---------------------------------------------------------------------------
//日付条件のチェック
//---------------------------------------------------------------------------
bool test_DateCond(
	int cnd,			//日付条件
	TDateTime dt,		//チェック対象の日付
	TDateTime dt_r)		//日付条件の日付
{
	bool ok = false;
	TValueRelationship res = System::Dateutils::CompareDate(dt, dt_r);
	switch (cnd) {
	case 1: ok = (res==LessThanValue);		break;
	case 2: ok = (res==EqualsValue);		break;
	case 3: ok = (res==GreaterThanValue);	break;
	}
	return ok;
}

//---------------------------------------------------------------------------
//結果リストの整形
//  "ファイル名\t内容" --> "ファイル名   内容"
//  内容に TAB が含まれていたら削除
//  戻り値: ファイル名部分の最大幅
//---------------------------------------------------------------------------
int format_res_list(TStringList *lst, int mgn, int min_wd)
{
	//ファイル名の最大幅を取得
	int max_len = 0;
	for (int i=0; i<lst->Count; i++) max_len_half(max_len, get_pre_tab(lst->Strings[i]));
	max_len += mgn;
	if (max_len<min_wd) max_len = min_wd;

	//結果を整形
	for (int i=0; i<lst->Count; i++) {
		UnicodeString lbuf = lst->Strings[i];
		lst->Strings[i] = align_l_str(get_pre_tab(lbuf), max_len, ReplaceStr(get_post_tab(lbuf), "\t", EmptyStr));
	}

	return max_len;
}

//---------------------------------------------------------------------------
//ファイルのプロパティを表示
//---------------------------------------------------------------------------
void ShowPropertyDialog(UnicodeString fnam)
{
	if (fnam.IsEmpty()) return;

	SHELLEXECUTEINFO sei = {sizeof(SHELLEXECUTEINFO)};
	sei.lpFile = ExcludeTrailingPathDelimiter(fnam).c_str();
	sei.lpVerb = _T("properties");
	sei.fMask  = SEE_MASK_INVOKEIDLIST | SEE_MASK_NOCLOSEPROCESS | SEE_MASK_FLAG_NO_UI;
	::ShellExecuteEx(&sei);
}

//---------------------------------------------------------------------------
//現在位置のリスト項目を削除
//---------------------------------------------------------------------------
void delete_ListItem(TCustomListBox *lp)
{
	if (lp) {
		int idx = lp->ItemIndex;
		if (idx!=-1) {
			lp->Items->Delete(idx);
			lp->ItemIndex = (idx<lp->Count)? idx : lp->Count - 1;
		}
	}
}

//---------------------------------------------------------------------------
//リストボックスの項目に罫線を描画 (背景の反転色)
//---------------------------------------------------------------------------
void draw_ListItemLine(TCustomListBox *lp, int idx)
{
	TPenMode org_md = lp->Canvas->Pen->Mode;
	int		 org_wd = lp->Canvas->Pen->Width;
	lp->Canvas->Pen->Mode  = pmNot;
	lp->Canvas->Pen->Width = 2;
	if (idx!=-1) {
		TRect r = lp->ItemRect(idx);
		int   y = (lp->ItemIndex<idx)? r.Bottom : r.Top;
		lp->Canvas->MoveTo(0, y);
		lp->Canvas->LineTo(lp->Width, y);
	}
	lp->Canvas->Pen->Mode  = org_md;
	lp->Canvas->Pen->Width = org_wd;
}

//---------------------------------------------------------------------------
//端点がフラットな線を描画 (w=1 の場合はそのまま)
//---------------------------------------------------------------------------
void draw_Line(
	TCanvas *cv,
	int x0, int y0, int x1, int y1,
	int w,				//線幅
	TColor col, 		//色
	TPenStyle style)	// (default = psSolid)
{
	if (w>1) {
		int c = ColorToRGB(col);
		LOGBRUSH l_brush;
		l_brush.lbStyle = BS_SOLID;
		l_brush.lbColor = RGB(GetRValue(c), GetGValue(c), GetBValue(c));
		l_brush.lbHatch = 0;
		DWORD p_style = PS_GEOMETRIC|PS_ENDCAP_FLAT|PS_JOIN_MITER;

		switch (style) {
		case psDot:  p_style |= PS_DOT;  break;
		case psDash: p_style |= PS_DASH; break;
		default:     p_style |= PS_SOLID;
		}

		HPEN hPen = ::ExtCreatePen(p_style, w, &l_brush, 0, 0);
		HPEN hOldPen = (HPEN)::SelectObject(cv->Handle, hPen);
		cv->Pen->Handle = hPen;
		cv->MoveTo(x0, y0);  cv->LineTo(x1, y1);
		::SelectObject(cv->Handle, hOldPen);
		::DeleteObject(hPen);
	}
	else {
		cv->Pen->Mode  = pmCopy;
		cv->Pen->Style = style;
		cv->Pen->Color = col;
		cv->Pen->Width = w;
		cv->MoveTo(x0, y0);  cv->LineTo(x1, y1);
	}

	cv->Pen->Style = psSolid;
}

//---------------------------------------------------------------------------
//背景色(Brush)の輝度を考慮してセパレータを描画
//---------------------------------------------------------------------------
void draw_Separator(
	TCanvas *cv, TRect rc,
	TColor bg)	//背景色	(default = clNone : cv->Brush->Color)
{
	int yp = rc.Top + rc.Height()/2;
	int x0 = rc.Left  + 4;
	int x1 = rc.Right - 4;

	double v  = GetLuminance((bg==Graphics::clNone)? cv->Brush->Color : bg);
	TColor c0 = TColor((v>0.5)? RGB(0x77, 0x77, 0x77) : RGB(0x33, 0x33, 0x33));	//***
	TColor c1 = TColor((v>0.5)? RGB(0xdd, 0xdd, 0xdd) : RGB(0x99, 0x99, 0x99));	//***

	cv->Pen->Style = psSolid;
	cv->Pen->Width = 1;
	cv->Pen->Color = c0;	cv->MoveTo(x0, yp);  cv->LineTo(x1, yp++);
	cv->Pen->Color = c1;	cv->MoveTo(x0, yp);  cv->LineTo(x1, yp);
}
//---------------------------------------------------------------------------
//背景色(Brush)を考慮して分割線を描画
//---------------------------------------------------------------------------
void draw_separateLine(TCanvas *cv, TRect rc,
	int pos)	//位置 0=上辺/ 1=中央/ 2=下辺 (default = 0)
{
	cv->Pen->Color = SelectWorB(cv->Brush->Color, 0.25);	//***
	cv->Pen->Style = psSolid;
	cv->Pen->Width = 1;

	switch (pos) {
	case 1:
		cv->MoveTo(rc.Left  + 2, rc.Top + rc.Height()/2);
		cv->LineTo(rc.Right - 2, rc.Top + rc.Height()/2);
		break;
	case 2:
		cv->MoveTo(rc.Left  + 2, rc.Bottom - 1);
		cv->LineTo(rc.Right - 2, rc.Bottom - 1);
		break;
	default:
		cv->MoveTo(rc.Left,      rc.Top);
		cv->LineTo(rc.Right + 1, rc.Top);
	}
}

//---------------------------------------------------------------------------
//縮小比率を取得
//---------------------------------------------------------------------------
double get_ZoomRatio(int vw, int vh, int iw, int ih, int mgn, double limit)
{
	if (iw==0 || ih==0) return 1.0;

	if (mgn>0) {
		vw -= mgn*2;
		vh -= mgn*2;
	}

	double r;
	bool v_is_v = (vh>vw);
	bool i_is_v = (ih>iw);
	if ((v_is_v && i_is_v) || (!v_is_v && !i_is_v))
		//縦横関係が同じ
		r = std::max(std::min(1.0 * vw/ih, 1.0 * vh/iw), std::min(1.0 * vw/iw, 1.0 * vh/ih));
	else
		//縦横関係が違う
		r = std::min(std::min(1.0 * vw/ih, 1.0 * vh/iw), std::min(1.0 * vw/iw, 1.0 * vh/ih));

	if (r>limit) r = 1.0;

	return r;
}

//---------------------------------------------------------------------------
//長方形にアルファブレンド
//---------------------------------------------------------------------------
void alpha_blend_Rect(TCanvas *cv, int x, int y, int w, int h, TColor col, int alpha)
{
	BLENDFUNCTION blend_f;
	blend_f.BlendOp				= AC_SRC_OVER;
	blend_f.BlendFlags			= 0;
	blend_f.SourceConstantAlpha = alpha;
	blend_f.AlphaFormat			= 0;

	std::unique_ptr<Graphics::TBitmap> bp_b(new Graphics::TBitmap());
	bp_b->SetSize(8, 8);
	bp_b->Canvas->Brush->Style = bsSolid;
	bp_b->Canvas->Brush->Color = col;
	bp_b->Canvas->FillRect(TRect(0, 0, 8, 8));
	::AlphaBlend(cv->Handle, x, y, w, h, bp_b->Canvas->Handle, 0, 0, 8, 8, blend_f);
}
//---------------------------------------------------------------------------
void alpha_blend_Rect(TCanvas *cv, TRect rc, TColor col, int alpha)
{
	alpha_blend_Rect(cv, rc.Left, rc.Top, rc.Width(), rc.Height(), col, alpha);
}

//---------------------------------------------------------------------------
//TUpDown の初期化
//---------------------------------------------------------------------------
void init_UpDown(TUpDown *udp, int n)
{
	udp->Position = n;
	TCustomEdit *ep = dynamic_cast<TCustomEdit *>(udp->Associate);
	if (ep) ep->Text = udp->Position;
}

//---------------------------------------------------------------------------
//グリッドのセル幅をヘッダに合わせる
//---------------------------------------------------------------------------
void set_GridFromHeader(THeaderControl *hp, TStringGrid *gp)
{
	int cnt = std::min(hp->Sections->Count, gp->ColCount);
	int wd = 0;
	for (int i=0; i<cnt; i++) {
		gp->ColWidths[i] = hp->Sections->Items[i]->Width - ScaledInt(gp->GridLineWidth);
		wd += hp->Sections->Items[i]->Width;
	}

	//余りのセクションは残り幅に合わせる
	if (hp->Sections->Count>gp->ColCount) {
		hp->Sections->Items[gp->ColCount]->Width = std::max(hp->Width - wd, 0);
	}
}
//---------------------------------------------------------------------------
//ヘッダの列幅をグリッドのセル幅に合わせる
//---------------------------------------------------------------------------
void set_HeaderFromGrid(TStringGrid *gp, THeaderControl *hp)
{
	int cnt = std::min(hp->Sections->Count, gp->ColCount);
	int wd = 0;
	for (int i=0; i<cnt; i++) {
		hp->Sections->Items[i]->Width = gp->ColWidths[i] + ScaledInt(gp->GridLineWidth + ((i==0)? 1 : 0), gp);
		wd += hp->Sections->Items[i]->Width;
	}

	//余りのセクションは残り幅に合わせる
	if (hp->Sections->Count>gp->ColCount) {
		hp->Sections->Items[gp->ColCount]->Width = std::max(hp->Width - wd, 0);
	}
}

//---------------------------------------------------------------------------
//ヘッダの列幅を設定(固定)
//---------------------------------------------------------------------------
void set_HeaderSecWidth(THeaderControl *hp, int cnt, ...)
{
	THeaderSections *sp = hp->Sections;

	//一旦、固定を解除
	for (int i=0; i<sp->Count; i++) {
		sp->Items[i]->MinWidth = 0;
		sp->Items[i]->MaxWidth = 10000;
	}

	va_list ap;
	va_start(ap, cnt);
	for (int i=0; i<cnt; i++) {
		int w = va_arg(ap, int);
		if (i<sp->Count) sp->Items[i]->Width = w;
	}
	va_end(ap);

	//末尾列が未指定なら残り幅に設定
	if (cnt == sp->Count-1) {
		int w = hp->ClientWidth;
		for (int i=0; i<sp->Count-1; i++) w -= sp->Items[i]->Width;
		sp->Items[sp->Count - 1]->Width = std::max(w, 0);
	}

	//列幅を固定
	for (int i=0; i<sp->Count; i++) {
		int w = sp->Items[i]->Width;
		sp->Items[i]->MinWidth = w;
		sp->Items[i]->MaxWidth = w;
	}
}
//---------------------------------------------------------------------------
void adjust_HeaderSecWidth(THeaderControl *hp, int idx)
{
	THeaderSections *sp = hp->Sections;
	int wd = hp->Width;
	for (int i=0; i<sp->Count; i++) if (i!=idx) wd -= sp->Items[i]->Width;
	sp->Items[idx]->Width = wd;
}

//---------------------------------------------------------------------------
//ステータスバーのパネル幅を設定
//---------------------------------------------------------------------------
int set_SttBarPanelWidth(TStatusBar *sp, int idx,
	int n)	//文字数(半角単位)
{
	TCanvas *cv = sp->Canvas;
	cv->Font->Assign(sp->Font);
	int wd = (n>0)? get_CharWidth(cv, n + 2, 16) : 0;
	sp->Panels->Items[idx]->Width = wd;
	return wd;
}
//---------------------------------------------------------------------------
int set_SttBarPanelWidth(TStatusBar *sp, int idx,
	UnicodeString s)	//文字列
{
	TCanvas *cv = sp->Canvas;
	cv->Font->Assign(sp->Font);
	int wd = cv->TextWidth(s + "__");
	sp->Panels->Items[idx]->Width = wd;
	return wd;
}

//---------------------------------------------------------------------------
//グリッドの行をクリア
//---------------------------------------------------------------------------
void clear_GridRow(TStringGrid *gp, int row, int col)
{
	if (row>=0 && row<gp->RowCount) {
		for (int i=col; i<gp->ColCount; i++) gp->Cells[i][row] = EmptyStr;
	}
}

//---------------------------------------------------------------------------
//グリッドの現在位置をインデックス化
//---------------------------------------------------------------------------
int get_GridIndex(TStringGrid *gp, int max_count)
{
	int idx = (gp->ColCount * gp->Row) + gp->Col;
	if (idx>=max_count) idx = -1;
	return idx;
}

//---------------------------------------------------------------------------
//ListBox のカーソル移動
//---------------------------------------------------------------------------
void ListBoxCursorDown(TListBox *lp)
{
	int idx = lp->ItemIndex + 1;
	if (idx<lp->Count) ListBoxSetIndex(lp, idx);
}
//---------------------------------------------------------------------------
void ListBoxCursorDown(TListBox *lp, int n)
{
	ListBoxSetIndex(lp, std::min(lp->ItemIndex + n, lp->Count - 1));
}
//---------------------------------------------------------------------------
void ListBoxCursorUp(TListBox *lp)
{
	int idx = lp->ItemIndex - 1;
	if (idx>=0) ListBoxSetIndex(lp, idx);
}
//---------------------------------------------------------------------------
void ListBoxCursorUp(TListBox *lp, int n)
{
	ListBoxSetIndex(lp, std::max(lp->ItemIndex - n, 0));
}
//---------------------------------------------------------------------------
void ListBoxPageDown(TListBox *lp)
{
	ListBoxCursorDown(lp, lp->ClientHeight/lp->ItemHeight - 1);
}
//---------------------------------------------------------------------------
void ListBoxPageUp(TListBox *lp)
{
	ListBoxCursorUp(lp, lp->ClientHeight/lp->ItemHeight - 1);
}
//---------------------------------------------------------------------------
void ListBoxTop(TListBox *lp)
{
	ListBoxSetIndex(lp, 0);
}
//---------------------------------------------------------------------------
void ListBoxEnd(TListBox *lp)
{
	if (lp->Count>0) ListBoxSetIndex(lp, lp->Count - 1);
}

//---------------------------------------------------------------------------
void ListBoxSetIndex(TListBox *lp, int idx,
	bool top_sw)	//マージン付きでトップにスクロール	(default = false)
{
	if (lp->Count==0) return;

	if (idx<0) {
		lp->ItemIndex = 0;
	}
	else if (top_sw) {
		lp->TopIndex  = std::max(idx - LISTBOX_SCRMGN, 0);
		lp->ItemIndex = idx;
	}
	else if (idx==lp->ItemIndex) {
		//可視領域外だったらスクロール
		int pn = lp->ClientHeight/lp->ItemHeight;
		if (lp->ItemIndex<lp->TopIndex)
			lp->TopIndex = std::max(lp->ItemIndex - LISTBOX_SCRMGN, 0);
		else if (lp->ItemIndex > lp->TopIndex + pn - 1)
			lp->TopIndex = std::max(lp->ItemIndex - pn + 1 + LISTBOX_SCRMGN, 0);
	}
	else {
		if (idx>=lp->Count) idx = lp->Count - 1;
		//上へ
		if (idx<lp->ItemIndex) {
			if (idx < lp->TopIndex+LISTBOX_SCRMGN)
				lp->TopIndex = std::max(idx - LISTBOX_SCRMGN, 0);
		}
		//下へ
		else {
			int pn = lp->ClientHeight/lp->ItemHeight;
			if (idx > (lp->TopIndex + pn - 1 - LISTBOX_SCRMGN))
				lp->TopIndex = std::max(idx - pn + 1 + LISTBOX_SCRMGN, 0);
		}
		lp->ItemIndex = idx;
	}
}
//---------------------------------------------------------------------------
//ListBox のカーソルを可視領域へ
//---------------------------------------------------------------------------
bool ListBoxCsrToVisible(TListBox *lp)
{
	int lst_idx = lp->ItemIndex;
	if (lp->ItemIndex < lp->TopIndex)
		lp->ItemIndex = lp->TopIndex;
	else {
		int idx_btm = lp->TopIndex + lp->ClientHeight/lp->ItemHeight - 1;
		if (lp->ItemIndex > idx_btm) lp->ItemIndex = idx_btm;
	}
	return (lst_idx != lp->ItemIndex);
}
//---------------------------------------------------------------------------
//ListBox のスクロール
//---------------------------------------------------------------------------
void ListBoxScrollDown(TListBox *lp, int n,
	bool move_csr)	//カーソルも移動 (default = false)
{
	int idx = lp->TopIndex;
	lp->TopIndex = idx + n;
	n = lp->TopIndex - idx;
	if (move_csr) lp->ItemIndex += n;
}
//---------------------------------------------------------------------------
void ListBoxScrollDown(TListBox *lp, UnicodeString prm)
{
	if (!prm.IsEmpty()) {
		int pn = lp->ClientHeight/lp->ItemHeight;

		switch (idx_of_word_i("HP|FP|ED", prm)) {
		case 0:  ListBoxScrollDown(lp, pn/2);					break;
		case 1:  ListBoxScrollDown(lp, pn);						break;
		case 2:  lp->TopIndex = std::max(lp->Count - pn, 0);	break;
		default: ListBoxScrollDown(lp, prm.ToIntDef(1));
		}
	}
}

//---------------------------------------------------------------------------
void ListBoxScrollUp(TListBox *lp, int n,
	bool move_csr)	//カーソルも移動 (default = false)
{
	int idx = lp->TopIndex;
	if (n>lp->TopIndex) lp->TopIndex = 0; else lp->TopIndex = idx - n;
	n = lp->TopIndex - idx;
	if (move_csr) lp->ItemIndex += n;
}
//---------------------------------------------------------------------------
void ListBoxScrollUp(TListBox *lp, UnicodeString prm)
{
	if (!prm.IsEmpty()) {
		int pn = lp->ClientHeight/lp->ItemHeight;

		switch (idx_of_word_i("HP|FP|TP", prm)) {
		case 0:  ListBoxScrollUp(lp, pn/2);	break;
		case 1:  ListBoxScrollUp(lp, pn);	break;
		case 2:  lp->TopIndex = 0;			break;
		default: ListBoxScrollUp(lp, prm.ToIntDef(1));
		}
	}
}

//---------------------------------------------------------------------------
//ListBox ですべての項目を選択
//---------------------------------------------------------------------------
void ListBoxSelectAll(TListBox *lp, bool sw)
{
	if (lp) lp->Perform(LB_SETSEL, (BOOL)sw, (NativeInt)-1);
}

//---------------------------------------------------------------------------
//ListBox で頭文字サーチ
//---------------------------------------------------------------------------
int ListBoxInitialSearch(
	TListBox *lp,
	UnicodeString kptn,		//検索パターン
	bool fnam_sw)			//ファイル名部分に対して適用 (default = false)
{
	int idx0 = -1, idx1 = -1;
	try {
		TRegExOptions opt; opt << roIgnoreCase;
		for (int i=0; i<lp->Count && idx1==-1; i++) {
			if (i<=lp->ItemIndex && idx0!=-1) continue;
			UnicodeString lbuf = lp->Items->Strings[i];
			if (fnam_sw) lbuf = ExtractFileName(lbuf);
			if (TRegEx::IsMatch(lbuf, kptn, opt)) ((i<=lp->ItemIndex)? idx0 : idx1) = i;
		}
	}
	catch (...) {
		;
	}
	int idx = (idx1!=-1)? idx1 : idx0;
	if (idx!=-1) lp->ItemIndex = idx;
	return idx;
}

//---------------------------------------------------------------------------
//ListBox の現在行文字列を取得
//---------------------------------------------------------------------------
UnicodeString ListBoxGetStr(TListBox *lp)
{
	return (lp->ItemIndex!=-1)? lp->Items->Strings[lp->ItemIndex] : EmptyStr;
} 
//---------------------------------------------------------------------------
//ListBox の現在行のオブジェクトを取得
//---------------------------------------------------------------------------
TObject * ListBoxGetObj(TListBox *lp)
{
	return (lp->ItemIndex!=-1)? lp->Items->Objects[lp->ItemIndex] : NULL;
} 

//---------------------------------------------------------------------------
//ListBox の現在行からディレクトリ名を取得
//---------------------------------------------------------------------------
UnicodeString InfListBoxGetDir(TListBox *lp)
{
	int idx = lp->ItemIndex;
	return (idx!=-1 && ((int)lp->Items->Objects[idx] & LBFLG_PATH_FIF))?
						  get_tkn_r(lp->Items->Strings[idx], ": ") : EmptyStr;
}
//---------------------------------------------------------------------------
//ListBox の現在行からURLを取得
//---------------------------------------------------------------------------
UnicodeString ListBoxGetURL(TListBox *lp)
{
	return extract_URL(ListBoxGetStr(lp));
}

//---------------------------------------------------------------------------
//ListBox の Objects を整数値としてチェックし、項目連番を設定
//---------------------------------------------------------------------------
void set_ListBox_ItemNo(TListBox *lp)
{
	int itm_no	 = 0;
	int last_tag = -1;
	for (int i=0; i<lp->Count; i++) {
		int tag = (int)lp->Items->Objects[i];
		if (last_tag!=tag) {
			itm_no++;
			last_tag = tag;
		}
		lp->Items->Objects[i] = (TObject*)(NativeInt)itm_no;
	}

	lp->Invalidate();
}
//---------------------------------------------------------------------------
void set_Strings_ItemNo(TStringList *lst)
{
	int itm_no	 = 0;
	int last_tag = -1;
	for (int i=0; i<lst->Count; i++) {
		int tag = (int)lst->Objects[i];
		if (last_tag!=tag) {
			itm_no++;
			last_tag = tag;
		}
		lst->Objects[i] = (TObject*)(NativeInt)itm_no;
	}
}

//---------------------------------------------------------------------------
//TCheckListBox でチェックされている項目数を取得
//---------------------------------------------------------------------------
int get_CheckListCount(TCheckListBox *lp)
{
	int cnt = 0;
	for (int i=0; i<lp->Count; i++) if (lp->Checked[i]) cnt++;
	return cnt;
}

//---------------------------------------------------------------------------
//TStringGrid でのカーソル移動
//---------------------------------------------------------------------------
void GridCursorLeft(TStringGrid *gp)
{
	if (gp->Col>0) gp->Col = gp->Col - 1;
}
//---------------------------------------------------------------------------
void GridCursorRight(TStringGrid *gp)
{
	if (gp->Col < gp->ColCount - 1) gp->Col = gp->Col + 1;
}
//---------------------------------------------------------------------------
void GridCursorDown(TStringGrid *gp)
{
	if (gp->Row < gp->RowCount - 1) gp->Row = gp->Row + 1;
}
//---------------------------------------------------------------------------
void GridCursorUp(TStringGrid *gp)
{
	if (gp->Row>gp->FixedRows) gp->Row = gp->Row - 1;
}
//---------------------------------------------------------------------------
void GridPageDown(TStringGrid *gp)
{
	int pn  = gp->VisibleRowCount - 1;
	int row = std::min(gp->Row + pn, gp->RowCount - 1);
	gp->Row = row;
}
//---------------------------------------------------------------------------
void GridPageUp(TStringGrid *gp)
{
	int pn  = gp->VisibleRowCount - 1;
	int row = std::max(gp->Row - pn, gp->FixedRows);
	gp->Row = row;
}
//---------------------------------------------------------------------------
bool GridCursorMove(UnicodeString cmd , TStringGrid *gp)
{
	switch (idx_of_word_i("CursorDown|CursorUp|PageDown|PageUp", cmd)) {
	case  0: GridCursorDown(gp);	break;
	case  1: GridCursorUp(gp);		break;
	case  2: GridPageDown(gp);		break;
	case  3: GridPageUp(gp);		break;
	default:						return false;
	}

	return true;
}

//---------------------------------------------------------------------------
//TStringList の項目を１つ上へ移動
//---------------------------------------------------------------------------
int up_StrListItem(TStringList *lst, int idx)
{
	if (idx>=1 && idx<lst->Count) {
		lst->Move(idx, idx - 1);
		idx--;
	}
	return idx;
}
//---------------------------------------------------------------------------
//TStringList の項目を１つ下へ移動
//---------------------------------------------------------------------------
int down_StrListItem(TStringList *lst, int idx)
{
	if (idx>=0 && idx<lst->Count - 1) {
		lst->Move(idx, idx + 1);
		idx++;
	}
	return idx;
}

//---------------------------------------------------------------------------
//アクセラレータキーの一致するリスト項目のインデックスを取得
//---------------------------------------------------------------------------
int get_IndexFromAccKey(TStringList *lst, UnicodeString key)
{
	if (key.Length()!=1) return -1;
	key.Insert("&", 1);
	int idx = -1;
	for (int i=0; i<lst->Count; i++)
		if (ContainsText(get_csv_item(lst->Strings[i], 0), key)) { idx = i; break; }
	return idx;
}

//---------------------------------------------------------------------------
//文字列からURL(ローカルファイルを含む)を抽出
//---------------------------------------------------------------------------
UnicodeString extract_URL(UnicodeString s)
{
	if (s.Pos(':')==0) return EmptyStr;

	UnicodeString url;
	TMatch mt = TRegEx::Match(s, URL_MATCH_PTN);
	if (mt.Success) {
		url = mt.Value;
		if (!StartsStr('h', url)) url.Insert("h", 1);	//先頭に h がなかったら補う
	}
	else {
		mt = TRegEx::Match(s, MAIL_MATCH_PTN);
		if (mt.Success) {
			url = mt.Value;
		}
		else {
			mt = TRegEx::Match(s, LOCAL_FILE_PTN);
			if (mt.Success) url = mt.Value;
		}
	}
	return url;
}

//---------------------------------------------------------------------------
//インターネット接続があるか?
//---------------------------------------------------------------------------
bool InternetConnected()
{
	DWORD flag;
	return InternetGetConnectedState(&flag, 0);
}

//---------------------------------------------------------------------------
//オンライン上のファイルを取得
//---------------------------------------------------------------------------
int get_OnlineFile(UnicodeString url, UnicodeString fnam, bool *cancel,
	TPaintBox *prg_box,		//進捗バー	(default = NULL)
	double *prg_ratio)		//進捗率	(default = NULL)
{
	int f_size = -1;
	if (cancel) *cancel = false;

	if (!url.IsEmpty() && InternetConnected()) {
		HINTERNET hSession = InternetOpen(_T("NyanFi"), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
		if (hSession) {
			HINTERNET hConnect = InternetOpenUrl(hSession, url.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
			if (hConnect) {
				DWORD dwFsize = 0;
				DWORD dwBufLen = sizeof(dwFsize);
				HttpQueryInfo(hConnect, HTTP_QUERY_CONTENT_LENGTH|HTTP_QUERY_FLAG_NUMBER,
						 (LPVOID)&dwFsize, &dwBufLen, 0);

				std::unique_ptr<BYTE[]> ldbuf(new BYTE[FILE_RBUF_SIZE]);
				DWORD dwSize;
				f_size = 0;

				std::unique_ptr<TMemoryStream> ms(new TMemoryStream());
				for (;;) {
					if (!InternetReadFile(hConnect, ldbuf.get(), FILE_RBUF_SIZE, &dwSize)) break;
					if (dwSize==0) break;
					ms->Write(ldbuf.get(), (System::LongInt)dwSize);
					f_size += dwSize;
					//進捗バー
					if (prg_box && prg_ratio && dwFsize>0) {
						*prg_ratio = 1.0 * f_size / dwFsize;
						prg_box->Repaint();
					}
					if (cancel) {
						Application->ProcessMessages();
						if (*cancel) break;
					}
				}

				if (prg_box && prg_ratio) {
					*prg_ratio = 1.0;
					prg_box->Repaint(); Sleep(500);
				}

				if (!cancel || !*cancel) {
					//favicon なら形式チェック
					if (EndsText(":favicon", fnam) && f_size>64) {
						//.ico ?
						int tag = 0;
						unsigned short us_buf;
						ms->Seek(0, soFromBeginning);
						ms->ReadBuffer(&us_buf, 2);  if (us_buf==0) tag++;
						ms->ReadBuffer(&us_buf, 2);  if (us_buf==1) tag++;
						ms->ReadBuffer(&us_buf, 2);  if (us_buf>0)  tag++;
						if (tag<3) {
							//.png?
							tag = 0;
							BYTE b_buf;
							ms->Seek(0, soFromBeginning);
							ms->ReadBuffer(&b_buf, 1);  if (b_buf==0x89) tag++;
							ms->ReadBuffer(&b_buf, 1);  if (b_buf==0x50) tag++;
							ms->ReadBuffer(&b_buf, 1);  if (b_buf==0x4e) tag++;
							ms->ReadBuffer(&b_buf, 1);  if (b_buf==0x47) tag++;
							if (tag<4) f_size = -1;
						}
					}

					if (f_size>=0) {
						chk_cre_dir(ExtractFileDir(fnam));
						ms->SaveToFile(fnam);
					}
				}

				InternetCloseHandle(hConnect);
			}
		    InternetCloseHandle(hSession);
		}
	}
	return f_size;
}

//---------------------------------------------------------------------------
//スプリッタ幅を設定
//---------------------------------------------------------------------------
void set_SplitterWidht(TSplitter *sp, int sp_wd)
{
	int sz = ScaledInt(sp_wd, sp);
	if (sp->Align==alLeft || sp->Align==alRight) sp->Width = sz; else sp->Height = sz;
	sp->Repaint();
}

//---------------------------------------------------------------------------
//パネルの配置
//---------------------------------------------------------------------------
void set_PanelAlign(TPanel *pp, TSplitter *sp, int mode, int sp_wd)
{
	int sz = ScaledInt(sp_wd, sp);
	switch (mode) {
	case 1:	//右
		sp->Align = alLeft;
		pp->Align = alRight;
		sp->Align = alRight;
		sp->Width = pp->Visible? sz : 0;
		break;
	case 2:	//左
		sp->Align = alRight;
		pp->Align = alLeft;
		sp->Align = alLeft;
		sp->Width = pp->Visible? sz : 0;
		break;
	case 3: //上
		sp->Align  = alBottom;
		pp->Align  = alTop;
		sp->Align  = alTop;
		sp->Height = pp->Visible? sz : 0;
		break;
	default:	//0: 下
		sp->Align  = alTop;
		pp->Align  = alBottom;
		sp->Align  = alBottom;
		sp->Height = pp->Visible? sz : 0;
	}
}
//---------------------------------------------------------------------------
void set_PanelAlign(TPanel *pp, TSplitter *sp, TAlign al, int sp_wd)
{
	switch (al) {
	case alTop:		set_PanelAlign(pp, sp, 3, sp_wd);	break;
	case alBottom:	set_PanelAlign(pp, sp, 0, sp_wd);	break;
	case alLeft:	set_PanelAlign(pp, sp, 2, sp_wd);	break;
	case alRight:	set_PanelAlign(pp, sp, 1, sp_wd);	break;
	default:
		;
	}
}

//---------------------------------------------------------------------------
//コントロールを右下隅に配置
//---------------------------------------------------------------------------
void set_ControlRBCorner(TControl *cp0, TControl *cp1)
{
	if (cp0->Visible && cp1->Visible) {
		cp1->Left = cp0->Left + cp0->ClientWidth  - cp1->Width;
		cp1->Top  = cp0->Top  + cp0->ClientHeight - cp1->Height;
		cp1->BringToFront();
	}
}

//---------------------------------------------------------------------------
//バッテリ残量(%)の文字列取得
//---------------------------------------------------------------------------
UnicodeString get_BatteryPercentStr()
{
	SYSTEM_POWER_STATUS ps;
	::GetSystemPowerStatus(&ps);
	if (ps.BatteryLifePercent==255) return "---";
	return UnicodeString().sprintf(_T("%3u"), ps.BatteryLifePercent);
}
//---------------------------------------------------------------------------
//バッテリ残量(時間)の文字列取得
//---------------------------------------------------------------------------
UnicodeString get_BatteryTimeStr()
{
	SYSTEM_POWER_STATUS ps;
	::GetSystemPowerStatus(&ps);

	UnicodeString ret;
	if (ps.ACLineStatus==1) {
		ret = "ONLINE";
	}
	else {
		int s = ps.BatteryLifeTime;
		if (s==-1)
			ret = "--:--";
		else
			ret.sprintf(_T("%u:%02u"), s/3600, (s%3600)/60);
	}
	return ret;
}

//---------------------------------------------------------------------------
//ドライブの取り外し
//  戻り値: 取り外せた/取り外し可能 の場合 true
//---------------------------------------------------------------------------
bool EjectDrive(
	UnicodeString drvnam,	//ドライブ名
	bool eject)				//true=取り外し/ false=確認のみ
{
	if (EjectDrive2(drvnam, eject)) return true;

	drvnam = ExtractFileDrive(drvnam);
	if (drvnam.IsEmpty()) return false;
	drvnam = IncludeTrailingPathDelimiter(drvnam);

	int typ = ::GetDriveType(drvnam.c_str());
	DWORD dwAccessFlags;
	switch(typ) {
	case DRIVE_REMOVABLE:	dwAccessFlags = GENERIC_READ|GENERIC_WRITE;	break;
	case DRIVE_CDROM:		dwAccessFlags = GENERIC_READ;				break;
	default:				return false;
	}

	bool ret = false;
	UnicodeString drv = "\\\\.\\" + ExtractFileDrive(drvnam);
	HANDLE hDrive = ::CreateFile(drv.c_str(), dwAccessFlags,
		FILE_SHARE_READ|FILE_SHARE_WRITE, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (hDrive!=INVALID_HANDLE_VALUE) {
		if (eject) {
			if (typ==DRIVE_CDROM) {
				//ID=37: 「取り出し」を直接実行
				ret = usr_SH->DriveContextMenu(Application->ActiveFormHandle, drvnam, NULL, 37).IsEmpty();
			}
			else {
				//ボリュームをロック
				bool locked = false;
				DWORD dwBytesReturned;
				for (int i = 0; i<20; i++) {
					if (::DeviceIoControl(hDrive, FSCTL_LOCK_VOLUME, NULL, 0, NULL, 0, &dwBytesReturned, NULL)) {
						locked = true; break;
					}
					Sleep(10000/20);	//10秒/20回リトライ
				}
				if (locked) {
					//マウント解除
					if (::DeviceIoControl(hDrive, FSCTL_DISMOUNT_VOLUME, NULL, 0, NULL, 0, &dwBytesReturned, NULL)) {
						//削除を妨げるからデバイスを停止
						PREVENT_MEDIA_REMOVAL PMRBuffer;
						PMRBuffer.PreventMediaRemoval = FALSE;
						if (::DeviceIoControl(hDrive, IOCTL_STORAGE_MEDIA_REMOVAL,
							&PMRBuffer, sizeof(PREVENT_MEDIA_REMOVAL), NULL, 0, &dwBytesReturned, NULL))
						{
							//取り外し
							::DeviceIoControl(hDrive, IOCTL_STORAGE_EJECT_MEDIA, NULL, 0, NULL, 0, &dwBytesReturned, NULL);
						}
						ret = true;
					}
				}
			}
		}
		else ret = true;

		::CloseHandle(hDrive);
	}

	return ret;
}
//---------------------------------------------------------------------------
//リムーバブル/CD-ROM 以外の取り外し
//---------------------------------------------------------------------------
bool EjectDrive2(UnicodeString drvnam, bool eject)
{
	drvnam = ExtractFileDrive(drvnam);
	if (drvnam.IsEmpty()) return false;
	drvnam = IncludeTrailingPathDelimiter(drvnam);

	//ドライブのボリューム名を取得
	_TCHAR pszVolName[MAX_PATH];
	if (!::GetVolumeNameForVolumeMountPoint(drvnam.c_str(), pszVolName, MAX_PATH)) return false;
	UnicodeString vol_name = pszVolName;

	//ボリューム名の一致するデバイスを検索
	bool res = false;
	HDEVINFO hDevInfo = ::SetupDiGetClassDevs(NULL, 0, 0, DIGCF_PRESENT|DIGCF_ALLCLASSES);
	if (hDevInfo!=INVALID_HANDLE_VALUE) {
		bool found = false;
		SP_DEVINFO_DATA DevInfoData = {sizeof(SP_DEVINFO_DATA)};

		for (DWORD i=0; !found && SetupDiEnumDeviceInfo(hDevInfo, i, &DevInfoData); i++) {
			ULONG status  = 0;
			ULONG problem = 0;
			if (::CM_Get_DevNode_Status(&status, &problem, DevInfoData.DevInst, 0)!=CR_SUCCESS) continue;
			if ((status & DN_DISABLEABLE)==0 || (status & DN_REMOVABLE)==0) continue;

			DEVINST devInstChild;
			if (CM_Get_Child(&devInstChild, DevInfoData.DevInst, 0)==CR_SUCCESS) {
				_TCHAR pszDevInstanceId[MAX_PATH];
				if (CM_Get_Device_ID(devInstChild, pszDevInstanceId, MAX_PATH, 0)==CR_SUCCESS) {
					UnicodeString strDiList;
					ULONG ulSize;
					if (CM_Get_Device_Interface_List_Size(&ulSize, (LPGUID)&VolumeClassGuid,
							pszDevInstanceId, 0)==CR_SUCCESS)
					{
						std::unique_ptr<_TCHAR[]> pszList(new _TCHAR[ulSize + 1]);
						if (CM_Get_Device_Interface_List((LPGUID)&VolumeClassGuid,
							pszDevInstanceId, pszList.get(), ulSize, 0)==CR_SUCCESS)
								strDiList = UnicodeString(pszList.get());
					}
					if (strDiList.IsEmpty()) {
						if (CM_Get_Device_ID_List_Size(&ulSize, pszDevInstanceId,
								CM_GETIDLIST_FILTER_REMOVALRELATIONS )==CR_SUCCESS)
						{
							std::unique_ptr<_TCHAR[]> pDeviceIDsList(new _TCHAR[ulSize]);
							if (CM_Get_Device_ID_List(pszDevInstanceId, pDeviceIDsList.get(),
									ulSize, CM_GETIDLIST_FILTER_REMOVALRELATIONS)==CR_SUCCESS)
							{
								if (CM_Get_Device_Interface_List_Size(&ulSize, (LPGUID)&VolumeClassGuid,
										pDeviceIDsList.get(), 0)==CR_SUCCESS)
								{
									std::unique_ptr<_TCHAR[]> pDeviceInterfacesList(new _TCHAR[ulSize]);
									if (CM_Get_Device_Interface_List((LPGUID)&VolumeClassGuid, pDeviceIDsList.get(),
										 pDeviceInterfacesList.get(), ulSize, 0) == CR_SUCCESS)
											strDiList = pDeviceInterfacesList.get();
								}
							}
						}
					}
					if (!strDiList.IsEmpty()) {
						strDiList = IncludeTrailingPathDelimiter(strDiList);
						if (!GetVolumeNameForVolumeMountPoint(strDiList.c_str(), pszVolName, MAX_PATH)) continue;
						if (SameText(vol_name, pszVolName)) {
							found = true;
							//取り外し
							res = eject? (CM_Request_Device_Eject(DevInfoData.DevInst, NULL, NULL, 0, 0)==CR_SUCCESS) : true;
						}
					}
				}
			}
		}
		::SetupDiDestroyDeviceInfoList(hDevInfo);
	}
	return res;
}

//---------------------------------------------------------------------------
//メニューの余計なセパレータを非表示にする
//※最初の表示で AutoLineReduction が効かない問題に対処
//---------------------------------------------------------------------------
void reduction_MenuLine(TMenuItem *mp)
{
	if (!mp) return;

	bool is_sp = false;
	TMenuItem *ip_0 = NULL;		//最初の表示項目
	TMenuItem *ip_1 = NULL;		//最後の表示項目

	for (int i=0; i<mp->Count; i++) {
		TMenuItem *ip = mp->Items[i];
		if (ip->Action) ip->Action->Update();
		if (SameStr(ip->Caption, "-")) {
			ip->Visible = !is_sp;
			is_sp = true;
		}
		else if (ip->Visible) {
			is_sp = false;
		}

		if (ip->Visible) {
			if (!ip_0) ip_0 = ip;
			ip_1 = ip;
		}
	}

	if (ip_0 && SameStr(ip_0->Caption, "-")) ip_0->Visible = false;
	if (ip_1 && SameStr(ip_1->Caption, "-")) ip_1->Visible = false;
}

//---------------------------------------------------------------------------
//Web検索
//---------------------------------------------------------------------------
UnicodeString WebSeaUrl;		//WebSearch:  検索エンジンURL

//---------------------------------------------------------------------------
//Web検索表示文字列を取得
//---------------------------------------------------------------------------
UnicodeString get_WebSeaCaption(
	UnicodeString kwd,	//検索語				(default = EmptyStr)
	bool with_ak)		//アクセラレータを付加	(default = true)
{
	UnicodeString ret_str;
	if (!kwd.IsEmpty()) {
		kwd = Trim(get_first_line(kwd));
		kwd = ReplaceStr(kwd, "&", "&&");
		if (kwd.Length()>20) kwd = kwd.SubString(1, 20) + "…";
		if (!kwd.IsEmpty()) ret_str.sprintf(_T("「%s」を "), kwd.c_str());
	}

	UnicodeString url = get_tkn_m(WebSeaUrl, "//", "/");
	remove_top_text(url, "www.");
	if (url.IsEmpty()) url = "Web";
	ret_str.cat_sprintf(_T("%s で検索"), url.c_str());
	if (with_ak) ret_str += "(&S)";

	return ret_str;
}

//---------------------------------------------------------------------------
//Web検索を実行
//---------------------------------------------------------------------------
bool exe_WebSearch(UnicodeString kwd)
{
	UnicodeString url;
	if (!kwd.IsEmpty()) {
		kwd = System::Netencoding::TURLEncoding::URL->Encode(kwd);
		url = ReplaceStr(WebSeaUrl, "\\S", kwd);
	}

	return (!url.IsEmpty()?
			(::ShellExecute(NULL, _T("open"), url.c_str(), NULL, NULL, SW_SHOWNORMAL) > (HINSTANCE)32) : false);
}
//---------------------------------------------------------------------------
