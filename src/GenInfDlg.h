/**
 * @file GenInfDlg.h
 * @brief 汎用一覧ダイアログ
 */
//---------------------------------------------------------------------------
#ifndef GenInfDlgH
#define GenInfDlgH

//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtDlgs.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.AppEvnts.hpp>
#include <Vcl.ToolWin.hpp>
#include "usr_scrpanel.h"
#include "Global.h"

//---------------------------------------------------------------------------
/**
 * @brief 汎用一覧ダイアログ
 */
class TGeneralInfoDlg : public TForm
{
__published:	// IDE で管理されるコンポーネント
	TAction *AndOrAction;
	TAction *ClrCmdHistoryAction;
	TAction *CopyAction;
	TAction *CopyCmdAction;
	TAction *CopyValAction;
	TAction *DelDuplAction;
	TAction *EditFileAction;
	TAction *ErrOnlyAction;
	TAction *FileName1stAction;
	TAction *HighlightAction;
	TAction *KeepIndexAction;
	TAction *MigemoAction;
	TAction *NotifyAction;
	TAction *OmitComPathAction;
	TAction *OpenUrlAction;
	TAction *OrgOrderAction;
	TAction *PlayNextAction;
	TAction *PlayPauseAction;
	TAction *PlayPrevAction;
	TAction *PropertyAction;
	TAction *RestoreListAction;
	TAction *SaveAsAction;
	TAction *SaveAsNbtAction;
	TAction *SelAllAction;
	TAction *ShowFileInfoAction;
	TAction *ShowLineNoAction;
	TAction *SortAscAction;
	TAction *SortDesAction;
	TAction *ViewFileAction;
	TAction *ViewListAction;
	TAction *WatchAction;
	TActionList *ActionList1;
	TEdit *FilterEdit;
	TListBox *GenListBox;
	TMenuItem *ClrCmdHistoryItem;
	TMenuItem *CopyCmdItem;
	TMenuItem *DelDuplItem;
	TMenuItem *EditFileItem;
	TMenuItem *ErrOnlyItem;
	TMenuItem *FileName1stItem;
	TMenuItem *FindTextItem;
	TMenuItem *FitSizePosItem;
	TMenuItem *InfEditCopyItem;
	TMenuItem *InfEditCopyValItem;
	TMenuItem *InfEditSelectAllItem;
	TMenuItem *KeepIndexItem;
	TMenuItem *OmitComPathItem;
	TMenuItem *OpenUrlItem;
	TMenuItem *OrgOrderItem;
	TMenuItem *PropertyItem;
	TMenuItem *RestoreListItem;
	TMenuItem *SaveAsItem;
	TMenuItem *SaveAsNbtItem;
	TMenuItem *Sep_1;
	TMenuItem *Sep_2;
	TMenuItem *Sep_3;
	TMenuItem *Sep_4;
	TMenuItem *Sep_5;
	TMenuItem *Sep_6;
	TMenuItem *ShowFileInfoItem;
	TMenuItem *ShowLineNoItem;
	TMenuItem *SortAscItem;
	TMenuItem *SortDesItem;
	TMenuItem *SortItem;
	TMenuItem *ViewFileItem;
	TMenuItem *ViewListItem;
	TPanel *ListPanel;
	TPanel *MianPanel;
	TPopupMenu *InfPopupMenu;
	TSplitter *FilterSplitter;
	TStatusBar *StatusBar1;
	TTimer *Timer1;
	TToolBar *OpeToolBar;
	TToolButton *AndOrBtn;
	TToolButton *FilterBtn;
	TToolButton *HighlightBtn;
	TToolButton *MigemoBtn;
	TToolButton *NotifyBtn;
	TToolButton *PlayNextBtn;
	TToolButton *PlayPauseBtn;
	TToolButton *PlayPrevBtn;
	TToolButton *ToolButton5;
	TToolButton *WatchBtn;

	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall StatusBar1DrawPanel(TStatusBar *StatusBar, TStatusPanel *Panel, const TRect &Rect);
	void __fastcall FilterEditChange(TObject *Sender);
	void __fastcall FilterEditKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FilterEditKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall FilterEditEnter(TObject *Sender);
	void __fastcall FilterEditExit(TObject *Sender);
	void __fastcall FilterBtnClick(TObject *Sender);
	void __fastcall GenListBoxDrawItem(TWinControl *Control, int Index, TRect &Rect, TOwnerDrawState State);
	void __fastcall GenListBoxData(TWinControl *Control, int Index, UnicodeString &Data);
	void __fastcall GenListBoxDataObject(TWinControl *Control, int Index, TObject *&DataObject);
	void __fastcall GenListBoxClick(TObject *Sender);
	void __fastcall GenListBoxKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall GenListBoxKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall GenListBoxDblClick(TObject *Sender);
	void __fastcall GenListBoxExit(TObject *Sender);
	void __fastcall CopyActionExecute(TObject *Sender);
	void __fastcall CopyActionUpdate(TObject *Sender);
	void __fastcall CopyValActionExecute(TObject *Sender);
	void __fastcall CopyValActionUpdate(TObject *Sender);
	void __fastcall CopyCmdActionExecute(TObject *Sender);
	void __fastcall CopyCmdActionUpdate(TObject *Sender);
	void __fastcall SaveAsNbtActionExecute(TObject *Sender);
	void __fastcall ClrCmdHistoryActionExecute(TObject *Sender);
	void __fastcall ClrCmdHistoryActionUpdate(TObject *Sender);
	void __fastcall SelAllActionExecute(TObject *Sender);
	void __fastcall FindTextItemClick(TObject *Sender);
	void __fastcall SaveAsActionExecute(TObject *Sender);
	void __fastcall ViewListActionExecute(TObject *Sender);
	void __fastcall ViewListActionUpdate(TObject *Sender);
	void __fastcall ViewFileActionExecute(TObject *Sender);
	void __fastcall ViewFileActionUpdate(TObject *Sender);
	void __fastcall EditFileActionExecute(TObject *Sender);
	void __fastcall EditFileActionUpdate(TObject *Sender);
	void __fastcall ShowFileInfoActionExecute(TObject *Sender);
	void __fastcall PropertyActionExecute(TObject *Sender);
	void __fastcall PropertyActionUpdate(TObject *Sender);
	void __fastcall OpenUrlActionExecute(TObject *Sender);
	void __fastcall OpenUrlActionUpdate(TObject *Sender);
	void __fastcall ShowLineNoActionExecute(TObject *Sender);
	void __fastcall FileName1stActionExecute(TObject *Sender);
	void __fastcall FileName1stActionUpdate(TObject *Sender);
	void __fastcall OmitComPathActionExecute(TObject *Sender);
	void __fastcall OmitComPathActionUpdate(TObject *Sender);
	void __fastcall KeepIndexActionExecute(TObject *Sender);
	void __fastcall KeepIndexActionUpdate(TObject *Sender);
	void __fastcall ErrOnlyActionExecute(TObject *Sender);
	void __fastcall ErrOnlyActionUpdate(TObject *Sender);
	void __fastcall InfPopupMenuPopup(TObject *Sender);
	void __fastcall SortAscActionExecute(TObject *Sender);
	void __fastcall SortDesActionExecute(TObject *Sender);
	void __fastcall OrgOrderActionExecute(TObject *Sender);
	void __fastcall DelDuplActionExecute(TObject *Sender);
	void __fastcall RestoreListActionExecute(TObject *Sender);
	void __fastcall ListActionUpdate(TObject *Sender);
	void __fastcall ToggleActionExecute(TObject *Sender);
	void __fastcall TailActionUpdate(TObject *Sender);
	void __fastcall PlayPauseActionExecute(TObject *Sender);
	void __fastcall PlayPauseActionUpdate(TObject *Sender);
	void __fastcall PlayNextActionExecute(TObject *Sender);
	void __fastcall PlayPrevActionExecute(TObject *Sender);
	void __fastcall PlayActionUpdate(TObject *Sender);

private:	// ユーザー宣言
	int  MaxNameWidth;
	int  TabWidth;
	UnicodeString SavePath;
	bool isFiltered;
	int  LastIndex;
	int  LastTopIndex;
	int  ListWidth;				//リスト幅

	UnicodeString FirstKey;		//2ストローク開始キー
	bool Wait2ndKey;			//2ストローク目待ち状態
	bool KeyHandled;

	__int64   FileSize;
	TDateTime FileTime;

	int  SortMode;				//ソートモード 1:昇順/ -1:降順/ 0:解除
	bool Found;					//検索結果

	void __fastcall WmFormShowed(TMessage &msg);
	void __fastcall WmNyanFiPlayList(TMessage &msg);

	void __fastcall WmMenuChar(TMessage &msg)
	{
		if (msg.WParamHi==MF_POPUP) TForm::Dispatch(&msg); else msg.Result = MAKELONG(0, MNC_CLOSE);
	}

	TWndMethod org_GenListWndProc;
	void __fastcall GenListWndProc(TMessage &msg);

	bool __fastcall UpdateList(bool reload = false);
	UnicodeString __fastcall GetBuffText();

	UnicodeString __fastcall TwoStrokeSeq(WORD &Key, TShiftState Shift);
	void __fastcall CancelKeySeq();

	void __fastcall SortGenList(int mode);

	UnicodeString __fastcall GetSelcetedCmd(TStringList *lst = NULL);

public:		// ユーザー宣言
	UsrScrollPanel *ListScrPanel;	//!< シンプルスクロールバー

	bool isVarList;		//!< 「名前=値」形式
	bool isLog;			//!< ログ
	bool isGit;			//!< git の出力 (先頭行が "$ git ")
	bool isFileList;	//!< ファイル名一覧
	bool isPlayList;	//!< プレイリスト
	bool isDirs;		//!< ディレクトリ一覧
	bool isTree;		//!< ディレクトリツリー表示
	bool isCmdHistory;	//!< コマンド履歴
	bool isFTP;			//!< FTP
	bool isTail;		//!< 末尾表示
	bool isReverse;		//!< 逆順表示
	bool fromGitView;	//!< GitViewerから表示
	bool isNonFile;		//!< ファイルは存在しない
	bool fromPopWnd;	//!< ポップアップ画面から表示
	bool ErrOnly;		//!< エラー部分のみ(ログ)
	bool ToEnd;			//!< 最後に移動
	bool ToFilter;		//!< フィルタ欄にフォーカス

	UnicodeString ComPathName;

	UnicodeString FileName;
	UnicodeString RetStr;
	int  LineIndex;				//!< 行インデックス(0ベース)
	int  TailLine;				//!< 末尾表示行数
	int  CodePage;				//!< コードページ
	bool HasBOM;				//!< BOM
	UnicodeString LineBreakStr;	//!< 改行コード
	UnicodeString FindWord;		//!< 検索文字列
	UnicodeString RegExPtn;		//!< 正規表現パターン
	UnicodeString HdrLnStr;		//!< 見出し行開始文字列(/〜/ の場合正規表現)
	UnicodeString ErrMsg;

	TStringList *GenInfoList;
	TStringList *GenInfoBuff;
	TStringList *GenSelList;

	__fastcall TGeneralInfoDlg(TComponent* Owner);
	void __fastcall SetStatusBar(UnicodeString msg = EmptyStr);

	void __fastcall ResetListWidth() { ListWidth = 0; }

	bool __fastcall FindText(bool down);

	BEGIN_MESSAGE_MAP
		VCL_MESSAGE_HANDLER(WM_FORM_SHOWED,		TMessage,	WmFormShowed)
		VCL_MESSAGE_HANDLER(WM_NYANFI_PLAYLIST, TMessage,	WmNyanFiPlayList)
		VCL_MESSAGE_HANDLER(WM_MENUCHAR,		TMessage,	WmMenuChar)
	END_MESSAGE_MAP(TForm)
};
//---------------------------------------------------------------------------
extern PACKAGE TGeneralInfoDlg *GeneralInfoDlg;
//---------------------------------------------------------------------------
#endif
