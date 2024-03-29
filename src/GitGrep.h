/**
 * @file GitGrep.h
 * @brief Git GREP ダイアログ
 */
//---------------------------------------------------------------------------
#ifndef GitGrepH
#define GitGrepH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.Actions.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Menus.hpp>
#include "usr_hintwin.h"

//---------------------------------------------------------------------------
#define RESLINE_MATCH_PTN	"^([0-9a-f]{7,}:)?(.+/)?(.+):(\\d+):(.+)"

//---------------------------------------------------------------------------
/**
 * @brief Git GREP ダイアログ
 */
class TGitGrepForm : public TForm
{
__published:	// IDE で管理されるコンポーネント
	TAction *ClipCopyAction;
	TAction *EditFileAction;
	TAction *GrepStartAction;
	TAction *LineCopyAction;
	TAction *SaveAsAction;
	TAction *ViewFileAction;
	TActionList *ActionList1;
	TButton *HiddenCanBtn;
	TButton *StartBtn;
	TCheckBox *CaseCheckBox;
	TCheckBox *RegExCheckBox;
	TCheckBox *WordCheckBox;
	TComboBox *FindComboBox;
	TComboBox *PathComboBox;
	TLabel *Label1;
	TLabel *Label2;
	TListBox *ResultListBox;
	TMenuItem *ClipCopyItem;
	TMenuItem *EdieFileItem;
	TMenuItem *LineCopyItem;
	TMenuItem *SaveAsItem;
	TMenuItem *Sep_1;
	TMenuItem *ViewFileItem;
	TPanel *OptLeftPanel;
	TPanel *OptPanel;
	TPanel *ResultPanel;
	TPanel *TopLeftPanel;
	TPanel *TopPanel;
	TPanel *TopRightPanel;
	TPopupMenu *PopupMenu1;
	TStatusBar *StatusBar1;

	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall RegExCheckBoxClick(TObject *Sender);
	void __fastcall GrepStartActionExecute(TObject *Sender);
	void __fastcall GrepStartActionUpdate(TObject *Sender);
	void __fastcall ResultListBoxData(TWinControl *Control, int Index, UnicodeString &Data);
	void __fastcall ResultListBoxDrawItem(TWinControl *Control, int Index, TRect &Rect, TOwnerDrawState State);
	void __fastcall ResultListBoxEnter(TObject *Sender);
	void __fastcall ResultListBoxKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall ResultListBoxKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall ClipCopyActionExecute(TObject *Sender);
	void __fastcall LineCopyActionExecute(TObject *Sender);
	void __fastcall SaveAsActionExecute(TObject *Sender);
	void __fastcall ResultActionUpdate(TObject *Sender);
	void __fastcall EditFileActionExecute(TObject *Sender);
	void __fastcall EditFileActionUpdate(TObject *Sender);
	void __fastcall ViewFileActionExecute(TObject *Sender);
	void __fastcall ViewFileActionUpdate(TObject *Sender);
	void __fastcall HiddenCanBtnClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormKeyPress(TObject *Sender, System::WideChar &Key);

private:	// ユーザー宣言
	bool DlgInitialized;

	UsrScrollPanel *ResultScrPanel;
	UsrHintWindow *MsgHint;

	bool KeyHandled;

	UnicodeString Keyword;
	TStringList *ResultBuff;

	int MaxFileWd;				//マッチファイル名の最大幅

	TPanel *StickyPanel;			//GREPスティッキー
	TPaintBox *StickyBox;
	int LastTopIndex;

	void __fastcall UpdateSticky();
	void __fastcall onStickyPaint(TObject *Sender);
	void __fastcall onStickyClick(TObject *Sender);

	void __fastcall WmMenuChar(TMessage &msg)
	{
		if (msg.WParamHi==MF_POPUP) TForm::Dispatch(&msg); else msg.Result = MAKELONG(0, MNC_CLOSE);
	}

public:		// ユーザー宣言
	UnicodeString WorkDir;		//!< Gitトップディレクトリ
	UnicodeString CommitID;

	bool FGitBusy;
	void __fastcall SetGitBusy(bool Value)
	{
		FGitBusy = Value;
		Enabled  = !Value;
		if (Value) {
			GitGrepAborted = false;
			cursor_HourGlass();
		}
		else {
			cursor_Default();
		}
	}
	/** @brief git grep 検索中 */
	__property bool GitBusy = {read = FGitBusy,  write = SetGitBusy};

	__fastcall TGitGrepForm(TComponent* Owner);

	BEGIN_MESSAGE_MAP
		VCL_MESSAGE_HANDLER(WM_MENUCHAR,	TMessage,	WmMenuChar)
	END_MESSAGE_MAP(TForm)
};
//---------------------------------------------------------------------------
extern PACKAGE TGitGrepForm *GitGrepForm;
//---------------------------------------------------------------------------
#endif
