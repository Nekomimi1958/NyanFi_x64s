/**
 * @file SrtModDlg.h
 * @brief ソートダイアログ
 */
//---------------------------------------------------------------------------
#ifndef SrtModDlgH
#define SrtModDlgH

//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.Actions.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.Mask.hpp>
#include <Vcl.AppEvnts.hpp>

//---------------------------------------------------------------------------
/**
 * @brief ソートダイアログ
 */
class TSortModeDlg : public TForm
{
__published:	// IDE で管理されるコンポーネント
	TAction *ExOptAction;
	TAction *OkAction;
	TActionList *ActionList1;
	TApplicationEvents *ApplicationEvents1;
	TButton *CanButton;
	TButton *OkButton;
	TButton *OptBtn;
	TCheckBox *AccDtoTCheckBox;
	TCheckBox *DscAttrCheckBox;
	TCheckBox *DscNameCheckBox;
	TCheckBox *ExOptCheckBox;
	TCheckBox *NaturalCheckBox;
	TCheckBox *OldCheckBox;
	TCheckBox *SameCloseCheckBox;
	TCheckBox *SmallCheckBox;
	TCheckBox *SortBothCheckBox;
	TCheckBox *SortLogicalCheckBox;
	TComboBox *DirSortModeComboBox;
	TComboBox *PrimeComboBox;
	TGroupBox *DirSortModeGroupBox;
	TGroupBox *GroupBox1;
	TGroupBox *PrimeGroupBox;
	TLabeledEdit *ExtListEdit;
	TPanel *BtnPanel;
	TPanel *DirOptPanel;
	TPanel *MainPanel;
	TPanel *ModePanel;
	TPanel *OptPanel;
	TRadioGroup *SortModeRadioGroup;
	TRadioGroup *SubModeRadioGroup;

	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall ApplicationEvents1Message(TMsg &Msg, bool &Handled);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall SortBothCheckBoxClick(TObject *Sender);
	void __fastcall OptCheckBoxClick(TObject *Sender);
	void __fastcall SortModeRadioGroupClick(TObject *Sender);
	void __fastcall SortModeRadioGroupEnter(TObject *Sender);
	void __fastcall SortModeRadioGroupExit(TObject *Sender);
	void __fastcall ExOptActionExecute(TObject *Sender);
	void __fastcall ExOptActionUpdate(TObject *Sender);
	void __fastcall OkActionUpdate(TObject *Sender);
	void __fastcall PrimeComboBoxClick(TObject *Sender);
	void __fastcall SubModeRadioGroupClick(TObject *Sender);
	void __fastcall AccDtoTCheckBoxClick(TObject *Sender);

private:	// ユーザー宣言
	bool Changed;
	bool SelByKey;

	void __fastcall WmMenuChar(TMessage &msg)
	{
		if (msg.WParamHi==MF_POPUP) TForm::Dispatch(&msg); else msg.Result = MAKELONG(0, MNC_CLOSE);
	}

	void __fastcall SetAccDT();

public:		// ユーザー宣言
	bool DlgInitialized;
	bool InhOk;

	__fastcall TSortModeDlg(TComponent* Owner);

	BEGIN_MESSAGE_MAP
		VCL_MESSAGE_HANDLER(WM_MENUCHAR,	TMessage,	WmMenuChar)
	END_MESSAGE_MAP(TForm)
};
//---------------------------------------------------------------------------
extern PACKAGE TSortModeDlg *SortModeDlg;
//---------------------------------------------------------------------------
#endif
