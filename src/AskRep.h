/**
 * @file AskRep.h
 * @brief 置換確認ダイアログ
 */
//----------------------------------------------------------------------------
#ifndef AskRepH
#define AskRepH

//----------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include "usr_scrpanel.h"

//----------------------------------------------------------------------------
/**
 * @brief 置換確認ダイアログ
 */
class TAskRepDlg : public TForm
{
__published:
	TButton *AllBtn;
	TButton *CanBtn;
	TButton *OKBtn;
	TButton *SkipBtn;
	TListBox *RepListBox;
	TPanel *ListPanel;
	TPanel *OpPanel;
	TStatusBar *StatusBar1;

	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall StatusBar1DrawPanel(TStatusBar *StatusBar, TStatusPanel *Panel, const TRect &Rect);
	void __fastcall RepListBoxDrawItem(TWinControl *Control, int Index, TRect &Rect, TOwnerDrawState State);
	void __fastcall RepListBoxEnter(TObject *Sender);

private:
	UsrScrollPanel *ListScrPanel;	//シンプルスクロールバー

public:
	UnicodeString FileName;
	UnicodeString KeyWord;

	int FoundLine;
	int FoundPos;

	int CurIndex;
	int FileCount;
	int FileIndex;

	int TopIndex;
	int EndIndex;

	virtual __fastcall TAskRepDlg(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TAskRepDlg *AskRepDlg;
//----------------------------------------------------------------------------
#endif
