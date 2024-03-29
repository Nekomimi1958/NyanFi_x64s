/**
 * @file DrvGraph.h
 * @brief ドライブ使用率推移
 */
//---------------------------------------------------------------------------
#ifndef DrvGraphH
#define DrvGraphH

//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.Actions.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.ToolWin.hpp>
#include <Vcl.Menus.hpp>

//---------------------------------------------------------------------------
/**
 * @brief ドライブ使用率推移
 */
class TDriveGraph : public TForm
{
__published:	// IDE で管理されるコンポーネント
	TAction *CursorAction;
	TAction *MinMaxAction;
	TAction *OldOdrAction;
	TActionList *ActionList1;
	TButton *HiddenCanBtn;
	TComboBox *DriveComboBox;
	TComboBox *SizeComboBox;
	TEdit *HiddenEdit;			//キー取得用隠しコントロール
	TPaintBox *PaintBox1;
	TPopupMenu *PopupMenu1;
	TScrollBox *GraphScrollBox;
	TSplitter *OptSplitter;
	TStatusBar *StatusBar1;
	TToolBar *OptToolBar;
	TToolButton *SizeBtn;
	TToolButton *ToolButton1;
	TToolButton *ToolButton3;
	TToolButton *ToolButton4;
	TToolButton *ToolButton5;

	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, TPoint &MousePos, bool &Handled);
	void __fastcall PaintBox1Paint(TObject *Sender);
	void __fastcall PaintBox1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall DriveComboBoxChange(TObject *Sender);
	void __fastcall OptComboBoxKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall SizeComboBoxChange(TObject *Sender);
	void __fastcall SizeBtnClick(TObject *Sender);
	void __fastcall ToggleActionExecute(TObject *Sender);
	void __fastcall HiddenEditKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall HiddenEditEnterExit(TObject *Sender);

private:	// ユーザー宣言
	bool DlgInitialized;
	TStringList *DataList;
	int  GraphTopX;
	int  BarSize;
	int  SttIndex;
	double MinUsed, MaxUsed;

	void __fastcall SetStatus(int idx);

public:		// ユーザー宣言
	UnicodeString DriveName;

	__fastcall TDriveGraph(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TDriveGraph *DriveGraph;
//---------------------------------------------------------------------------
#endif
