//----------------------------------------------------------------------//
// NyanFi																//
//  共有フォルダ/ライブラリ/検索設定/ディレクトリ選択					//
//----------------------------------------------------------------------//
#ifndef ShareDlgH
#define ShareDlgH

//---------------------------------------------------------------------------
#include <lm.h>
#include <System.Classes.hpp>
#include <System.Actions.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Tabs.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.Dialogs.hpp>
#include "usr_scrpanel.h"

//-----------------------------------------------
class TNetShareDlg : public TForm
{
__published:	// IDE で管理されるコンポーネント
	TAction *CopyPathAction;
	TAction *CopyPathAllAction;
	TAction *CopyUncAction;
	TAction *CopyUncAllAction;
	TAction *EditListAction;
	TAction *PropertyAction;
	TAction *SetColorAction;
	TAction *SetSkipDirAction;
	TActionList *ActionList1;
	TButton *HiddenCanBtn;
	TListBox *ShareListBox;
	TMenuItem *CopyPathAllItem;
	TMenuItem *CopyPathItem;
	TMenuItem *CopyUncAllItem;
	TMenuItem *CopyUncItem;
	TMenuItem *EditListItem;
	TMenuItem *PropertyItem;
	TMenuItem *SetColorItem;
	TMenuItem *SetSkipDirItem;
	TPanel *ListPanel;
	TPopupMenu *PopupMenu1;
	TTabControl *PathTabControl;

	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall PathTabControlDrawTab(TCustomTabControl *Control, int TabIndex, const TRect &Rect, bool Active);
	void __fastcall PathTabControlChange(TObject *Sender);
	void __fastcall ListPanelResize(TObject *Sender);
	void __fastcall ShareListBoxDrawItem(TWinControl *Control, int Index, TRect &Rect, TOwnerDrawState State);
	void __fastcall ShareListBoxKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall ShareListBoxKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall ShareListBoxClick(TObject *Sender);
	void __fastcall ShareListBoxDblClick(TObject *Sender);
	void __fastcall CopyUncActionExecute(TObject *Sender);
	void __fastcall CopyUncActionUpdate(TObject *Sender);
	void __fastcall CopyUncAllActionExecute(TObject *Sender);
	void __fastcall CopyUncAllActionUpdate(TObject *Sender);
	void __fastcall CopyPathActionExecute(TObject *Sender);
	void __fastcall CopyPathActionUpdate(TObject *Sender);
	void __fastcall CopyPathAllActionExecute(TObject *Sender);
	void __fastcall CopyPathAllActionUpdate(TObject *Sender);
	void __fastcall SetColorActionExecute(TObject *Sender);
	void __fastcall SetColorActionUpdate(TObject *Sender);
	void __fastcall EditListActionExecute(TObject *Sender);
	void __fastcall EditListActionUpdate(TObject *Sender);
	void __fastcall SetSkipDirActionExecute(TObject *Sender);
	void __fastcall SetSkipDirActionUpdate(TObject *Sender);
	void __fastcall PropertyActionExecute(TObject *Sender);
	void __fastcall PropertyActionUpdate(TObject *Sender);

private:	// ユーザー宣言
	UsrScrollPanel *ListScrPanel;	//シンプルスクロールバー

	bool isPC;
	int  LibIdxBase;

	void __fastcall WmFormShowed(TMessage &msg);

	void __fastcall WmMenuChar(TMessage &msg)
	{
		if (msg.WParamHi==MF_POPUP) TForm::Dispatch(&msg); else msg.Result = MAKELONG(0, MNC_CLOSE);
	}

	NET_API_STATUS __fastcall GetShareList(UnicodeString cnam, TListBox *lp);
	void __fastcall UpdateShareList(UnicodeString cnam);
	void __fastcall UpdatePathList(UnicodeString pnam);
	void __fastcall UpdateBreadcrumb(UnicodeString pnam);

	UnicodeString __fastcall GetBreadcrumbStr(int idx = -1)
	{
		UnicodeString pnam;
		if (idx==-1) idx = PathTabControl->TabIndex;
		int top = StartsStr("\\\\", PathTabControl->Tabs->Strings[0])? 0 : 1;
		for (int i=top; i<PathTabControl->Tabs->Count && i<=idx; i++) {
			pnam += IncludeTrailingPathDelimiter(get_tkn(PathTabControl->Tabs->Strings[i], " >"));
		}
		return pnam;
	}

	UnicodeString __fastcall GetListPathName(int idx)
	{
		UnicodeString pnam = ShareListBox->Items->Strings[idx];
		if (isPC)
			pnam = get_tkn(pnam, ' ');
		else if (SameStr(ExtractFileName(pnam), ".."))
			pnam = get_parent_path(ExtractFilePath(pnam));
		return IncludeTrailingPathDelimiter(pnam);
	}

public:		// ユーザー宣言
	UnicodeString ComputerName;
	UnicodeString PathName;
	UnicodeString FileName;
	UnicodeString Title;

	bool isShare;		//共有フォルダ
	bool isOnlySub;		//サブディレクトリ選択のみ
	bool isLibrary;		//ライブラリ
	bool isFindSet;		//検索設定

	bool isUNC;
	bool rqRetPath;		//選択したパスを返す(ディレクトリ変更は行わない)

	__fastcall TNetShareDlg(TComponent* Owner);

	BEGIN_MESSAGE_MAP
		VCL_MESSAGE_HANDLER(WM_FORM_SHOWED,	TMessage,	WmFormShowed)
		VCL_MESSAGE_HANDLER(WM_MENUCHAR,	TMessage,	WmMenuChar)
	END_MESSAGE_MAP(TForm)
};
//---------------------------------------------------------------------------
extern PACKAGE TNetShareDlg *NetShareDlg;
//---------------------------------------------------------------------------
#endif
