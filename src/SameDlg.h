/**
 * @file SameDlg.h
 * @brief 同名ファイルの処理ダイアログ
 */
//---------------------------------------------------------------------------
#ifndef SameDlgH
#define SameDlgH

//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>

//---------------------------------------------------------------------------
/**
 * @brief 同名ファイルの処理ダイアログ
 */
class TSameNameDlg : public TForm
{
__published:	// IDE で管理されるコンポーネント
	TButton *CanButton;
	TButton *OkButton;
	TCheckBox *AllCheckBox;
	TEdit *RenameEdit;
	TGroupBox *ModeGroupBox;
	TListBox *InfoListBox;
	TPanel *InfoPanel;
	TRadioButton *Mode0Btn;
	TRadioButton *Mode1Btn;
	TRadioButton *Mode2Btn;
	TRadioButton *Mode3Btn;
	TRadioButton *Mode4Btn;

	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall ModeBtnClick(TObject *Sender);
	void __fastcall AllCheckBoxClick(TObject *Sender);
	void __fastcall InfoListBoxDrawItem(TWinControl *Control, int Index, TRect &Rect, TOwnerDrawState State);
	void __fastcall RenameEditKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall RenameEditKeyPress(TObject *Sender, System::WideChar &Key);

private:	// ユーザー宣言
	bool InhAllChk;
	bool KeyHandled;

	void __fastcall WmMenuChar(TMessage &msg)
	{
		if (msg.WParamHi==MF_POPUP) TForm::Dispatch(&msg); else msg.Result = MAKELONG(0, MNC_CLOSE);
	}

	void __fastcall UpdateBtnLabel();

public:		// ユーザー宣言
	bool CopyAll;
	int  CopyMode;
	bool IsSamePath;
	int  TaskNo;

	UnicodeString CurSrcName;
	UnicodeString CurDstName;
	int CurSrcSize;
	int CurDstSize;
	TDateTime CurSrcTime;
	TDateTime CurDstTime;

	__fastcall TSameNameDlg(TComponent* Owner);

	BEGIN_MESSAGE_MAP
		VCL_MESSAGE_HANDLER(WM_MENUCHAR,	TMessage,	WmMenuChar)
	END_MESSAGE_MAP(TForm)
};
//---------------------------------------------------------------------------
extern PACKAGE TSameNameDlg *SameNameDlg;
//---------------------------------------------------------------------------
#endif
