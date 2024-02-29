/**
 * @file FindKey.h
 * @brief キー検索
 */
//---------------------------------------------------------------------------
#ifndef FindKeyH
#define FindKeyH

//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.AppEvnts.hpp>

//---------------------------------------------------------------------------
/**
 * @brief キー検索
 * 
 * オプション設定 - キー設定 で一覧からキーを検索する際に用います。
 *  
 */
class TFindKeyDlg : public TForm
{
__published:	// IDE で管理されるコンポーネント
	TButton *DummyBtn;
	TLabel *KeyLabel;
	TLabel *Label1;
	TPanel *CanInPanel;
	TPanel *CanOutPanel;
	TSpeedButton *CancelBtn;
	TApplicationEvents *ApplicationEvents1;

	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall ApplicationEvents1Message(TMsg &Msg, bool &Handled);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall DummyBtnClick(TObject *Sender);
	void __fastcall CancelBtnClick(TObject *Sender);

private:	// ユーザー宣言
	void __fastcall WmMenuChar(TMessage &msg)
	{
		if (msg.WParamHi==MF_POPUP) TForm::Dispatch(&msg); else msg.Result = MAKELONG(0, MNC_CLOSE);
	}

	bool __fastcall IsFirstCmdKey(UnicodeString keystr);

public:		// ユーザー宣言
	TStringList *KeyList;
	UnicodeString KeyStr;

	__fastcall TFindKeyDlg(TComponent* Owner);

	BEGIN_MESSAGE_MAP
		VCL_MESSAGE_HANDLER(WM_MENUCHAR,	TMessage,	WmMenuChar)
	END_MESSAGE_MAP(TForm)
};
//---------------------------------------------------------------------------
extern PACKAGE TFindKeyDlg *FindKeyDlg;
//---------------------------------------------------------------------------
#endif
