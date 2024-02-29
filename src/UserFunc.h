/**
 * @file UserFunc.h
 * @brief �ėp���ʊ֐�
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
#define URL_MATCH_PTN	_T("h?ttps?://[\\w/:%#$&?()~.=+-]+[\\w/]")		//!< URL�p���K�\��
#define MAIL_MATCH_PTN	_T("mailto:[a-zA-Z0-9]+[\\w.-]*@[\\w.-]+")		//!< ���[���p���K�\��
#define LOCAL_FILE_PTN	_T("file:///[^*?\"<>|)�j]+\\.[a-zA-Z0-9]+")		//!< ���[�J���t�@�C���̐��K�\��

#define LISTBOX_SCRMGN	2

//---------------------------------------------------------------------------
bool is_SnapToDefBtn();

/** @brief �}�E�X�J�[�\���ʒu�̃E�B���h�E���擾 */
HWND get_window_from_pos();

/** @brief Vista�ȍ~�̊g���t���[���ɑΉ������E�B���h�E�����`�̎擾 */
TRect get_window_rect(HWND hWnd);

/** @brief Vista�ȍ~�̊g���t���[���ɑΉ������T�C�Y�ݒ� */
void set_window_pos_ex(HWND hWnd, TRect rc);

/** @brief �t�H�[�����\�����j�^����͂ݏo���Ă�������܂�悤�ɒ��� */
void adjust_form_pos(TForm *frm);

/** @brief �_�C�A���O���Ăяo�����t�H�[���̒����ɕ\�� */
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
 * @brief �N���b�v�{�[�h�E�e�L�X�g���擾
 * @param top_sw ��s�ڂ̂ݎ擾
 * @return UnicodeString
 */
UnicodeString GetClipboardText(bool top_sw = false);

bool is_IME_Open(HWND hWnd);
bool is_IME_Typing(HWND hWnd);
bool is_IME_Empty(HWND hWnd);
void CloseIME(HWND hWnd);

TPoint get_ListItemPos(TListBox *lp, int xp = 0);

/** @brief ���X�g�{�b�N�X�̍��ڈʒu�Ƀ}�E�X�J�[�\�����ړ� */
void pos_ListBoxItem(TListBox *lp, int xp = 0);

//---------------------------------------------------------------------------
/** @brief �w��L�����o�X�̃t�H���g���������f�B���O�������Ă��邩�H */
bool has_Leading(TCanvas *cv);

/** @brief �w��t�H���g�ɂ��`�敝���擾 */
int  get_CharWidth_Font(TFont *font, int n);

int  EditToInt(TLabeledEdit *ep, int def = 0);
int  EditToInt(TEdit *ep, int def = 0);

/** @brief �t�@�C�������͗��̑I����Ԃ����ɐ؂�ւ��� */
void ChangeSelFileNameEdit(TCustomEdit *ep, bool is_dir = false);

/** @brief �R�}���h���͗��̑I����Ԃ����ɐ؂�ւ��� */
void ChangeSelCmdComboBox(TComboBox *cp);

void ChangeSelCmdEdit(TCustomEdit *ep);

//�N�������� TDate ���擾 (�����␳)
/**
 * @brief �N�������� TDate ���擾 (�����␳)
 * @param y �N
 * @param m ��
 * @param d ��
 * @return TDate
 * @exception �s���ȔN/�����w�肷��Ɨ�O�𑗏o
 */
TDate set_NormDay(unsigned short y, unsigned short m, unsigned short d);

/** @brief ������� TDateTime �ɕϊ� */
bool ToDateTime(UnicodeString s, TDateTime *dt);

/**
 * @brief ������������擾
 * @param dt ����
 * @param omit �����Ȃ���t���ȗ�
 * @return UnicodeString
 */
UnicodeString format_DateTime(TDateTime dt, bool omit = false);

/** @brief ���t��������擾 */
UnicodeString format_Date(TDateTime dt);

/** @brief ������������擾 (FormatDateTime �̊g��) */
UnicodeString format_DateTimeEx(UnicodeString fmt, TDateTime dt);

//�@���Ύw��: {<|=|>}-n{D|M|Y}�@�@(D:���AM:���AY:�N)
//�@��Ύw��: {<|=|>}yyyy/mm/dd
//	  	  �����t: TD
//  �J�[�\���ʒu: CP (= ct)
//
//  �߂�l : 1: < ���Â�/ 2: = ����/ 3: > ���V����
//			 0: �����Ȃ�/ -1: �G���[

/** @brief ���t�������擾 */
int  get_DateCond(UnicodeString prm, TDateTime &dt, TDateTime ct = 0);

bool test_DateCond(int cnd, TDateTime dt, TDateTime dt_r);

int  format_res_list(TStringList *lst, int mgn = 2, int min_wd = 16);

void ShowPropertyDialog(UnicodeString fnam);

void delete_ListItem(TCustomListBox *lp);
void draw_ListItemLine(TCustomListBox *lp, int idx);

/** @brief �[�_���t���b�g�Ȑ���`�� */
void draw_Line(TCanvas *cv, int x0, int y0, int x1, int y1, int w, TColor col, TPenStyle = psSolid);

/** @brief �w�i�F�̋P�x���l�����ăZ�p���[�^��`�� */
void draw_Separator(TCanvas *cv, TRect rc, TColor bg = Graphics::clNone);

/** @brief �w�i�F���l�����ĕ�������`�� */
void draw_separateLine(TCanvas *cv, TRect rc, int pos = 0);

/** @brief �k���䗦���擾 */
double get_ZoomRatio(int vw, int vh, int iw, int ih, int mgn = 0, double limit = 1.0);

void alpha_blend_Rect(TCanvas *cv, int x, int y, int w, int h, TColor col, int alpha);
void alpha_blend_Rect(TCanvas *cv, TRect rc, TColor col, int alpha);

void init_UpDown(TUpDown *udp, int n);

/** @brief �O���b�h�̃Z�������w�b�_�ɍ��킹�� */
void set_GridFromHeader(THeaderControl *hp, TStringGrid *gp);

/** @brief �w�b�_�̗񕝂��O���b�h�̃Z�����ɍ��킹�� */
void set_HeaderFromGrid(TStringGrid *gp, THeaderControl *hp);

/** @brief �w�b�_�̗񕝂�ݒ�(�Œ�) */
void set_HeaderSecWidth(THeaderControl *hp, int cnt, ...);

void adjust_HeaderSecWidth(THeaderControl *hp, int idx);

int  set_SttBarPanelWidth(TStatusBar *sp, int idx, int n);
int  set_SttBarPanelWidth(TStatusBar *sp, int idx, UnicodeString s);

/** @brief �O���b�h�̍s���N���A */
void clear_GridRow(TStringGrid *gp, int row, int col = 0);

/** @brief �O���b�h�̌��݈ʒu���C���f�b�N�X�� */
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

/** @brief ���X�g�{�b�N�X�œ������T�[�` */
int  ListBoxInitialSearch(TListBox *lp, UnicodeString kptn, bool fnam_sw = false);

/** @brief ���X�g�{�b�N�X�̌��ݍs�̕�������擾 */
UnicodeString ListBoxGetStr(TListBox *lp);

/** @brief ���X�g�{�b�N�X�̌��ݍs�̃I�u�W�F�N�g���擾 */
TObject * ListBoxGetObj(TListBox *lp);

/** @brief ���X�g�{�b�N�X�̌��ݍs����f�B���N�g�������擾 */
UnicodeString InfListBoxGetDir(TListBox *lp);

/** @brief ���X�g�{�b�N�X�̌��ݍs����URL���擾 */
UnicodeString ListBoxGetURL(TListBox *lp);

/** @brief ���X�g�{�b�N�X�� Objects �𐮐��l�Ƃ��ă`�F�b�N���A���ژA�Ԃ�ݒ� */
void set_ListBox_ItemNo(TListBox *lp);

void set_Strings_ItemNo(TStringList *lst);

/** @brief �`�F�b�N����Ă��鍀�ڐ����擾 */
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

/** @brief �����񂩂�URL(���[�J���t�@�C�����܂�)�𒊏o */
UnicodeString extract_URL(UnicodeString s);

/** @brief �C���^�[�l�b�g�ڑ������邩? */
bool InternetConnected();

/**
 * @brief �I�����C����̃t�@�C�����擾
 * @param url
 * @param fnam
 * @param cancel
 * @param prg_box �i���o�[
 * @param prg_ratio �i����
 * @return int �t�@�C���T�C�Y
 */
int  get_OnlineFile(UnicodeString url, UnicodeString fnam, bool *cancel = NULL,
		TPaintBox *prg_box = NULL, double *prg_ratio = NULL);

/** @brief �X�v���b�^����ݒ� */
void set_SplitterWidht(TSplitter *sp, int sp_wd);

/** @brief �p�l���̔z�u */
void set_PanelAlign(TPanel *pp, TSplitter *sp, int mode,  int sp_wd);
void set_PanelAlign(TPanel *pp, TSplitter *sp, TAlign al, int sp_wd);

/** @brief �R���g���[�����E�����ɔz�u */
void set_ControlRBCorner(TControl *cp0, TControl *cp1);

/** @brief �o�b�e���c��(%)��������擾 */
UnicodeString get_BatteryPercentStr();

/** @brief �o�b�e���c��(����)��������擾 */
UnicodeString get_BatteryTimeStr();

/** @brief �h���C�u�̎��O�� */
bool EjectDrive(UnicodeString drvnam, bool eject);

/** @brief �����[�o�u��/CD-ROM �ȊO�̎��O�� */
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

/** @brief ���j���[�̗]�v�ȃZ�p���[�^���\���ɂ��� */
void reduction_MenuLine(TMenuItem *mp);

//---------------------------------------------------------------------------
extern UnicodeString WebSeaUrl;		//!< Web�����p�̌����G���W��URL

/** @brief Web�����\����������擾 */
UnicodeString get_WebSeaCaption(UnicodeString kwd = EmptyStr, bool with_ak = true);

/** @brief Web���������s */
bool exe_WebSearch(UnicodeString kwd);

//---------------------------------------------------------------------------
#endif
