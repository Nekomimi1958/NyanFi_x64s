/**
 * @file MaskDlg.h
 * @brief パスマスク・ダイアログ
 */
//---------------------------------------------------------------------------
#ifndef MaskDlgH
#define MaskDlgH

//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.Actions.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include "usr_scrpanel.h"

//---------------------------------------------------------------------------
/**
 * @brief パスマスク・ダイアログ
 */
class TPathMaskDlg : public TForm
{
__published:	// IDE で管理されるコンポーネント
	TAction *AddItemAction;
	TAction *EditItemAction;
	TActionList *ActionList1;
	TButton *AddButton;
	TButton *DelButton;
	TButton *DowButton;
	TButton *EditButton;
	TButton *HiddenCanBtn;
	TButton *UpButton;
	TEdit *DescEdit;
	TEdit *KeyEdit;
	TEdit *MaskEdit;
	THeaderControl *PathMaskHeader;
	TListBox *PathMaskListBox;
	TPanel *BlankPanel;
	TPanel *ListPanel;
	TPanel *OptPanel;
	TSpeedButton *HideOptBtn;
	TSpeedButton *ShowOptBtn;

	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall PathMaskHeaderResize(TObject *Sender);
	void __fastcall PathMaskHeaderDrawSection(THeaderControl *HeaderControl, THeaderSection *Section,
		const TRect &Rect, bool Pressed);
	void __fastcall PathMaskHeaderSectionResize(THeaderControl *HeaderControl, THeaderSection *Section);
	void __fastcall PathMaskListBoxDrawItem(TWinControl *Control, int Index, TRect &Rect, TOwnerDrawState State);
	void __fastcall PathMaskListBoxKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall PathMaskListBoxClick(TObject *Sender);
	void __fastcall PathMaskListBoxDblClick(TObject *Sender);
	void __fastcall EditItemActionExecute(TObject *Sender);
	void __fastcall EditItemActionUpdate(TObject *Sender);
	void __fastcall AddItemActionExecute(TObject *Sender);
	void __fastcall AddItemActionUpdate(TObject *Sender);
	void __fastcall ChgOptBtnClick(TObject *Sender);

private:	// ユーザー宣言
	UsrScrollPanel *ListScrPanel;	//シンプルスクロールバー

	void __fastcall WmMenuChar(TMessage &msg)
	{
		if (msg.WParamHi==MF_POPUP) TForm::Dispatch(&msg); else msg.Result = MAKELONG(0, MNC_CLOSE);
	}

	void __fastcall SetOptBtn();

public:		// ユーザー宣言
	__fastcall TPathMaskDlg(TComponent* Owner);

	BEGIN_MESSAGE_MAP
		VCL_MESSAGE_HANDLER(WM_MENUCHAR,	TMessage,	WmMenuChar)
	END_MESSAGE_MAP(TForm)
};
//---------------------------------------------------------------------------
extern PACKAGE TPathMaskDlg *PathMaskDlg;
//---------------------------------------------------------------------------
#endif
