/**
 * @file DriveDlg.h
 * @brief ドライブ一覧
 */
//---------------------------------------------------------------------------
#ifndef DriveDlgH
#define DriveDlgH

//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.Actions.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include "usr_scrpanel.h"

//---------------------------------------------------------------------------
#define COL_WD_HIDE	16

//---------------------------------------------------------------------------
/**
 * @brief ドライブ一覧
 */
class TSelDriveDlg : public TForm
{
__published:	// IDE で管理されるコンポーネント
	TAction *EjectDriveAction;
	TAction *EjectTrayAction;
	TAction *PropertyAction;
	TActionList *ActionList1;
	TButton *DrivePropBtn;
	TButton *EjectDrvBtn;
	TButton *EjectTrayBtn;
	TButton *HiddenCanBtn;
	TCheckBox *LargeIconCheckBox;
	TCheckBox *OnlyAccCheckBox;
	TCheckBox *ShowIconCheckBox;
	TCheckBox *ToRootCheckBox;
	THeaderControl *DriveHeader;
	TMenuItem *EjectDrvItem;
	TMenuItem *EjectTryItem;
	TMenuItem *NetConItem;
	TMenuItem *NetDisItem;
	TMenuItem *OpenExpItem;
	TMenuItem *PropertyItem;
	TMenuItem *Sep_1;
	TMenuItem *Sep_2;
	TPanel *BlankPanel;
	TPanel *GridPanel;
	TPanel *OptPanel;
	TPopupMenu *PopupMenu1;
	TSpeedButton *HideOptBtn;
	TSpeedButton *ShowOptBtn;
	TStringGrid *DriveGrid;

	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall DriveHeaderResize(TObject *Sender);
	void __fastcall DriveHeaderSectionResize(THeaderControl *HeaderControl, THeaderSection *Section);
	void __fastcall DriveHeaderDrawSection(THeaderControl *HeaderControl, THeaderSection *Section,
		const TRect &Rect, bool Pressed);
	void __fastcall ToRootCheckBoxClick(TObject *Sender);
	void __fastcall DriveGridDrawCell(TObject *Sender, System::LongInt ACol, System::LongInt ARow, TRect &Rect, TGridDrawState State);
	void __fastcall DriveGridKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall DriveGridMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall DriveGridDblClick(TObject *Sender);
	void __fastcall OptCheckBoxClick(TObject *Sender);
	void __fastcall DrivePropBtnClick(TObject *Sender);
	void __fastcall EjectDriveActionExecute(TObject *Sender);
	void __fastcall EjectDriveActionUpdate(TObject *Sender);
	void __fastcall EjectTrayActionExecute(TObject *Sender);
	void __fastcall EjectTrayActionUpdate(TObject *Sender);
	void __fastcall OpenExpItemClick(TObject *Sender);
	void __fastcall PropertyActionExecute(TObject *Sender);
	void __fastcall ChgOptBtnClick(TObject *Sender);

private:	// ユーザー宣言
	void __fastcall WmMenuChar(TMessage &msg)
	{
		if (msg.WParamHi==MF_POPUP) TForm::Dispatch(&msg); else msg.Result = MAKELONG(0, MNC_CLOSE);
	}

	UnicodeString __fastcall getCurDrvStr(const _TCHAR *suf = NULL);
	void __fastcall SetOptBtn();
	void __fastcall ShowDriveMenu();
	void __fastcall ShowDriveGraph();

public:		// ユーザー宣言
	UsrScrollPanel *GridScrPanel;	//!< シンプルスクロールバー

	__fastcall TSelDriveDlg(TComponent* Owner);
	void __fastcall UpdateDriveList();

	BEGIN_MESSAGE_MAP
		VCL_MESSAGE_HANDLER(WM_MENUCHAR,	TMessage,	WmMenuChar)
	END_MESSAGE_MAP(TForm)
};
//---------------------------------------------------------------------------
extern PACKAGE TSelDriveDlg *SelDriveDlg;
//---------------------------------------------------------------------------
#endif
