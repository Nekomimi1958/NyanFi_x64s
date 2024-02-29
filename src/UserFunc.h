/**
 * @file UserFunc.h
 * @brief 汎用共通関数
 */
//---------------------------------------------------------------------------
#ifndef UsrFuncH
#define UsrFuncH

//---------------------------------------------------------------------------
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.CheckLst.hpp>
#include "usr_str.h"
#include "usr_key.h"
#include "usr_msg.h"
#include "usr_color.h"
#include "usr_file_ex.h"
#include "usr_file_inf.h"

//---------------------------------------------------------------------------
#define URL_MATCH_PTN	_T("h?ttps?://[\\w/:%#$&?()~.=+-]+[\\w/]")		//!< URL用正規表現
#define MAIL_MATCH_PTN	_T("mailto:[a-zA-Z0-9]+[\\w.-]*@[\\w.-]+")		//!< メール用正規表現
#define LOCAL_FILE_PTN	_T("file:///[^*?\"<>|)）]+\\.[a-zA-Z0-9]+")		//!< ローカルファイルの正規表現

#define LISTBOX_SCRMGN	2

//---------------------------------------------------------------------------
bool is_SnapToDefBtn();

/** @brief マウスカーソル位置のウィンドウを取得 */
HWND get_window_from_pos();

/** @brief Vista以降の拡張フレームに対応したウィンドウ長方形の取得 */
TRect get_window_rect(HWND hWnd);

/** @brief Vista以降の拡張フレームに対応したサイズ設定 */
void set_window_pos_ex(HWND hWnd, TRect rc);

/** @brief フォームが表示モニタからはみ出していたら収まるように調整 */
void adjust_form_pos(TForm *frm);

/** @brief ダイアログを呼び出し元フォームの中央に表示 */
int  show_ModalDlg(TForm *dlg);

void show_PopupMenu(TPopupMenu *mp, TControl *cp);
void show_PopupMenu(TListBox *cp);
void show_PopupMenu(TCheckListBox *cp);
void show_PopupMenu(TStringGrid *gp);

void set_ListBoxText(TListBox *lp, const _TCHAR *s);
void set_ComboBoxText(TComboBox *cp, const _TCHAR *s);

void add_ComboBox_history(TComboBox *cp, UnicodeString kwd = EmptyStr);
int  del_ComboBox_history(TComboBox *cp, UnicodeString kwd = EmptyStr);

/**
 * @brief クリップボード・テキストを取得
 * @param top_sw 一行目のみ取得
 * @return UnicodeString
 */
UnicodeString GetClipboardText(bool top_sw = false);

bool is_IME_Open(HWND hWnd);
bool is_IME_Typing(HWND hWnd);
bool is_IME_Empty(HWND hWnd);
void CloseIME(HWND hWnd);

TPoint get_ListItemPos(TListBox *lp, int xp = 0);

/** @brief リストボックスの項目位置にマウスカーソルを移動 */
void pos_ListBoxItem(TListBox *lp, int xp = 0);

//---------------------------------------------------------------------------
/** @brief 指定キャンバスのフォントが内部レディングを持っているか？ */
bool has_Leading(TCanvas *cv);

/** @brief 指定フォントによる描画幅を取得 */
int  get_CharWidth_Font(TFont *font, int n);

int  EditToInt(TLabeledEdit *ep, int def = 0);
int  EditToInt(TEdit *ep, int def = 0);

/** @brief ファイル名入力欄の選択状態を順に切り替える */
void ChangeSelFileNameEdit(TCustomEdit *ep, bool is_dir = false);

/** @brief コマンド入力欄の選択状態を順に切り替える */
void ChangeSelCmdComboBox(TComboBox *cp);

void ChangeSelCmdEdit(TCustomEdit *ep);

//年月日から TDate を取得 (月末補正)
/**
 * @brief 年月日から TDate を取得 (月末補正)
 * @param y 年
 * @param m 月
 * @param d 日
 * @return TDate
 * @exception 不正な年/月を指定すると例外を送出
 */
TDate set_NormDay(unsigned short y, unsigned short m, unsigned short d);

/** @brief 文字列を TDateTime に変換 */
bool ToDateTime(UnicodeString s, TDateTime *dt);

/**
 * @brief 日時文字列を取得
 * @param dt 日時
 * @param omit 同日なら日付を省略
 * @return UnicodeString
 */
UnicodeString format_DateTime(TDateTime dt, bool omit = false);

/** @brief 日付文字列を取得 */
UnicodeString format_Date(TDateTime dt);

/** @brief 日時文字列を取得 (FormatDateTime の拡張) */
UnicodeString format_DateTimeEx(UnicodeString fmt, TDateTime dt);

//　相対指定: {<|=|>}-n{D|M|Y}　　(D:日、M:月、Y:年)
//　絶対指定: {<|=|>}yyyy/mm/dd
//	  	  今日付: TD
//  カーソル位置: CP (= ct)
//
//  戻り値 : 1: < より古い/ 2: = 同じ/ 3: > より新しい
//			 0: 条件なし/ -1: エラー

/** @brief 日付条件を取得 */
int  get_DateCond(UnicodeString prm, TDateTime &dt, TDateTime ct = 0);

bool test_DateCond(int cnd, TDateTime dt, TDateTime dt_r);

int  format_res_list(TStringList *lst, int mgn = 2, int min_wd = 16);

void ShowPropertyDialog(UnicodeString fnam);

void delete_ListItem(TCustomListBox *lp);
void draw_ListItemLine(TCustomListBox *lp, int idx);

/** @brief 端点がフラットな線を描画 */
void draw_Line(TCanvas *cv, int x0, int y0, int x1, int y1, int w, TColor col, TPenStyle = psSolid);

/** @brief 背景色の輝度を考慮してセパレータを描画 */
void draw_Separator(TCanvas *cv, TRect rc, TColor bg = Graphics::clNone);

/** @brief 背景色を考慮して分割線を描画 */
void draw_separateLine(TCanvas *cv, TRect rc, int pos = 0);

/** @brief 縮小比率を取得 */
double get_ZoomRatio(int vw, int vh, int iw, int ih, int mgn = 0, double limit = 1.0);

void alpha_blend_Rect(TCanvas *cv, int x, int y, int w, int h, TColor col, int alpha);
void alpha_blend_Rect(TCanvas *cv, TRect rc, TColor col, int alpha);

void init_UpDown(TUpDown *udp, int n);

/** @brief グリッドのセル幅をヘッダに合わせる */
void set_GridFromHeader(THeaderControl *hp, TStringGrid *gp);

/** @brief ヘッダの列幅をグリッドのセル幅に合わせる */
void set_HeaderFromGrid(TStringGrid *gp, THeaderControl *hp);

/** @brief ヘッダの列幅を設定(固定) */
void set_HeaderSecWidth(THeaderControl *hp, int cnt, ...);

void adjust_HeaderSecWidth(THeaderControl *hp, int idx);

int  set_SttBarPanelWidth(TStatusBar *sp, int idx, int n);
int  set_SttBarPanelWidth(TStatusBar *sp, int idx, UnicodeString s);

/** @brief グリッドの行をクリア */
void clear_GridRow(TStringGrid *gp, int row, int col = 0);

/** @brief グリッドの現在位置をインデックス化 */
int  get_GridIndex(TStringGrid *gp, int max_count);

void ListBoxCursorDown(TListBox *lp);
void ListBoxCursorDown(TListBox *lp, int n);
void ListBoxCursorUp(TListBox *lp);
void ListBoxCursorUp(TListBox *lp, int n);
void ListBoxPageDown(TListBox *lp);
void ListBoxPageUp(TListBox *lp);
void ListBoxTop(TListBox *lp);
void ListBoxEnd(TListBox *lp);
void ListBoxSetIndex(TListBox *lp, int idx, bool top_sw = false);
bool ListBoxCsrToVisible(TListBox *lp);
void ListBoxScrollDown(TListBox *lp, int n, bool move_csr = false);
void ListBoxScrollDown(TListBox *lp, UnicodeString prm);
void ListBoxScrollUp(TListBox *lp, int n, bool move_csr = false);
void ListBoxScrollUp(TListBox *lp, UnicodeString prm);
void ListBoxSelectAll(TListBox *lp, bool sw = true);

/** @brief リストボックスで頭文字サーチ */
int  ListBoxInitialSearch(TListBox *lp, UnicodeString kptn, bool fnam_sw = false);

/** @brief リストボックスの現在行の文字列を取得 */
UnicodeString ListBoxGetStr(TListBox *lp);

/** @brief リストボックスの現在行のオブジェクトを取得 */
TObject * ListBoxGetObj(TListBox *lp);

/** @brief リストボックスの現在行からディレクトリ名を取得 */
UnicodeString InfListBoxGetDir(TListBox *lp);

/** @brief リストボックスの現在行からURLを取得 */
UnicodeString ListBoxGetURL(TListBox *lp);

/** @brief リストボックスの Objects を整数値としてチェックし、項目連番を設定 */
void set_ListBox_ItemNo(TListBox *lp);

void set_Strings_ItemNo(TStringList *lst);

/** @brief チェックされている項目数を取得 */
int get_CheckListCount(TCheckListBox *lp);

void GridCursorLeft(TStringGrid *gp);
void GridCursorRight(TStringGrid *gp);
void GridCursorDown(TStringGrid *gp);
void GridCursorUp(TStringGrid *gp);
void GridPageDown(TStringGrid *gp);
void GridPageUp(TStringGrid *gp);
bool GridCursorMove(UnicodeString cmd , TStringGrid *gp);

int up_StrListItem(TStringList *lst, int idx);
int down_StrListItem(TStringList *lst, int idx);

int get_IndexFromAccKey(TStringList *lst, UnicodeString key);

/** @brief 文字列からURL(ローカルファイルを含む)を抽出 */
UnicodeString extract_URL(UnicodeString s);

/** @brief インターネット接続があるか? */
bool InternetConnected();

/**
 * @brief オンライン上のファイルを取得
 * @param url
 * @param fnam
 * @param cancel
 * @param prg_box 進捗バー
 * @param prg_ratio 進捗率
 * @return int ファイルサイズ
 */
int  get_OnlineFile(UnicodeString url, UnicodeString fnam, bool *cancel = NULL,
		TPaintBox *prg_box = NULL, double *prg_ratio = NULL);

/** @brief スプリッタ幅を設定 */
void set_SplitterWidht(TSplitter *sp, int sp_wd);

/** @brief パネルの配置 */
void set_PanelAlign(TPanel *pp, TSplitter *sp, int mode,  int sp_wd);
void set_PanelAlign(TPanel *pp, TSplitter *sp, TAlign al, int sp_wd);

/** @brief コントロールを右下隅に配置 */
void set_ControlRBCorner(TControl *cp0, TControl *cp1);

/** @brief バッテリ残量(%)文字列を取得 */
UnicodeString get_BatteryPercentStr();

/** @brief バッテリ残量(時間)文字列を取得 */
UnicodeString get_BatteryTimeStr();

/** @brief ドライブの取り外し */
bool EjectDrive(UnicodeString drvnam, bool eject);

/** @brief リムーバブル/CD-ROM 以外の取り外し */
bool EjectDrive2(UnicodeString drvnam, bool eject);

inline bool class_is_LabeledEdit(TObject *op)
{
	return (op && op->ClassNameIs("TLabeledEdit"));
}

inline bool class_is_MaskEdit(TObject *op){
	return (op && op->ClassNameIs("TMaskEdit"));
}

inline bool class_is_CustomEdit(TObject *op)
{
	return (op && op->InheritsFrom(__classid(TCustomEdit)));
}

inline bool class_is_Edit(TObject *op)
{
	return (op && op->ClassNameIs("TEdit"));
}

inline bool class_is_CheckBox(TObject *op)
{
	return (op && op->ClassNameIs("TCheckBox"));
}
inline bool class_is_ComboBox(TObject *op)
{
	return (op && op->ClassNameIs("TComboBox"));
}

inline bool class_is_ListBox(TObject *op)
{
	return (op && op->ClassNameIs("TListBox"));
}

inline bool class_is_CheckListBox(TObject *op)
{
	return (op && op->ClassNameIs("TCheckListBox"));
}

inline bool class_is_RadioGroup(TObject *op)
{
	return (op && op->ClassNameIs("TRadioGroup"));
}

inline void cursor_HourGlass()
{
	Screen->Cursor = crHourGlass;
}

inline void cursor_Default()
{
	Screen->Cursor = crDefault;
}

/** @brief メニューの余計なセパレータを非表示にする */
void reduction_MenuLine(TMenuItem *mp);

//---------------------------------------------------------------------------
extern UnicodeString WebSeaUrl;		//!< Web検索用の検索エンジンURL

/** @brief Web検索表示文字列を取得 */
UnicodeString get_WebSeaCaption(UnicodeString kwd = EmptyStr, bool with_ak = true);

/** @brief Web検索を実行 */
bool exe_WebSearch(UnicodeString kwd);

//---------------------------------------------------------------------------
#endif
