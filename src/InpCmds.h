/**
 * @file InpCmds.h
 * @brief コマンドの入力ダイアログ
 */
//---------------------------------------------------------------------------
#ifndef InpCmdsH
#define InpCmdsH

//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>

//---------------------------------------------------------------------------
/**
 * @brief コマンドの入力ダイアログ
 */
class TInpCmdsDlg : public TForm
{
__published:	// IDE で管理されるコンポーネント
	TButton *HiddenCanBtn;
	TCheckBox *MigemoCheckBox;
	TComboBox *CmdsComboBox;
	TComboBox *SubComboBox;
	TPanel *MainPanel;
	TPanel *ModePanel;
	TTabControl *ModeTabControl;

	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall ModeTabControlChange(TObject *Sender);
	void __fastcall ModeTabControlDrawTab(TCustomTabControl *Control, int TabIndex, const TRect &Rect, bool Active);
	void __fastcall MigemoCheckBoxClick(TObject *Sender);
	void __fastcall CmdsComboBoxChange(TObject *Sender);
	void __fastcall CmdsComboBoxKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall CmdsComboBoxKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall CmdsComboBoxSelect(TObject *Sender);
	void __fastcall SubComboBoxDrawItem(TWinControl *Control, int Index, TRect &Rect, TOwnerDrawState State);
	void __fastcall SubComboBoxClick(TObject *Sender);
	void __fastcall SubComboBoxCloseUp(TObject *Sender);

private:	// ユーザー宣言
	TStringList *ItemList;		//候補リスト
	TStringList *SubCmdList;	//補助コマンドリスト
	TStringList *HistoryList;
	UnicodeString IdChar;
	bool InhFilter;
	bool IsRef;

	void __fastcall WmMenuChar(TMessage &msg)
	{
		if (msg.WParamHi==MF_POPUP) TForm::Dispatch(&msg); else msg.Result = MAKELONG(0, MNC_CLOSE);
	}

	void __fastcall SetList();
	void __fastcall Filter();

public:		// ユーザー宣言
	bool toCopy;
	bool toRefer;
	bool isFuzzy;

	__fastcall TInpCmdsDlg(TComponent* Owner);

	BEGIN_MESSAGE_MAP
		VCL_MESSAGE_HANDLER(WM_MENUCHAR,	TMessage,	WmMenuChar)
	END_MESSAGE_MAP(TForm)
};
//---------------------------------------------------------------------------
extern PACKAGE TInpCmdsDlg *InpCmdsDlg;
//---------------------------------------------------------------------------
#endif
