/**
 * @file Global.h
 * @brief グローバル変数/関数
 */
//---------------------------------------------------------------------------
#ifndef GlobalH
#define GlobalH

//---------------------------------------------------------------------------
#include <Vcl.BaseImageCollection.hpp>
#include <Vcl.ImageCollection.hpp>
#include <Vcl.VirtualImageList.hpp>

#include <htmlhelp.h>
#include <mmsystem.h>
#include "usr_scale.h"
#include "usr_file_ex.h"
#include "usr_shell.h"
#include "usr_arc.h"
#include "usr_migemo.h"
#include "usr_cmdlist.h"
#include "usr_scrpanel.h"
#include "usr_highlight.h"
#include "usr_tag.h"
#include "htmconv.h"
#include "UIniFile.h"
#include "UserFunc.h"
#include "MarkList.h"
#include "task_thread.h"
#include "imgv_thread.h"
#include "icon_thread.h"
#include "thumb_thread.h"

//---------------------------------------------------------------------------
/** @defgroup DEFINE 定義 */
/** @{ */
//---------------------------------------------------------------------------
#define SUPPORT_URL	"https://github.com/Nekomimi1958/NyanFi_x64s"
#define RELEASE_URL	"https://api.github.com/repos/Nekomimi1958/NyanFi_x64s/releases/latest"

//---------------------------------------------------------------------------
#define WM_FORM_SHOWED		(WM_APP + 1)	//!< フォームが表示された
#define WM_NYANFI_APPEAR	(WM_APP + 100)	//!< デザイン、フォント、配色が変更された
#define WM_NYANFI_FLICON	(WM_APP + 101)	//!< アイコンを取得した
#define WM_NYANFI_THUMBNAIL	(WM_APP + 102)	//!< サムネイルを取得した
#define WM_NYANFI_CLPCOPIED	(WM_APP + 103)	//!< クリップボードにコピーした
#define WM_NYANFI_PLAYLIST	(WM_APP + 104)	//!< プレイリスト通知
#define WM_NYANFI_LOCKKEY	(WM_APP + 105)	//!< LockKeyMouse 動作中のキー処理
#define WM_NYANFI_CLSEDITM	(WM_APP + 106)	//!< 設定項目の編集ダイアログを閉じた
#define WM_NYANFI_GREP_END	(WM_APP + 110)	//!< GREP完了

//---------------------------------------------------------------------------
//WM_COPYDATA メッセージの識別番号
#define CPYDTID_OPTIONS	1		//!< 起動オプション
#define CPYDTID_DPL_INF	2		//!< 二重起動側からの画面情報
#define CPYDTID_DPL_MSG	3		//!< 二重起動側からの通知メッセージ
#define CPYDTID_TXTVIEW	4		//!< テキストビューアで開く
#define CPYDTID_IMGVIEW	5		//!< イメージビューアで開く
#define CPYDTID_EXECMDS	6		//!< コマンドを実行
/** @} */

//---------------------------------------------------------------------------
//起動用バッチファイル
extern UnicodeString RstBatName;		//!< 再起動用バッチファイル名

//---------------------------------------------------------------------------
//HTMLヘルプ
extern bool CancelHelp;					//!< [F1]にコマンドが割り当てられていたらヘルプを抑止

/**
 * @brief ヘルプトピックを開く
 * @param topic トピック
 */
void HtmlHelpTopic(const _TCHAR *topic);

/**
 * @brief ヘルプを開く
 * @param idx コンテキスト
 */
void HtmlHelpContext(int idx);

/**
 * @brief ファイル/キーワードを指定してヘルプを開く(hhh.exe)
 * @param fnam ヘルプファイル名
 * @param kwd キーワード
 */
void HtmlHelpKeyword(UnicodeString fnam, UnicodeString kwd);

/** @brief ヘルプを閉じる */
void CloseHelpWnd();

#define HELPTOPIC_TOP	"hid00001.htm"		//!< 表紙
#define HELPTOPIC_FL	"hid00005.htm"		//!< ファイラー - コマンド
#define HELPTOPIC_TV	"hid00006.htm"		//!< テキストビューア
#define HELPTOPIC_IV	"hid00007.htm"		//!< イメージビューア
#define HELPTOPIC_IS	"hid00050.htm"		//!< インクリメンタルサーチ
#define HELPTOPIC_CI	"hid00100.htm"		//!< コマンドの索引
#define HELPTOPIC_CILW	"hid00100.htm#LW"	//!< コマンドの索引(ログウィンドウ)
#define HELPTOPIC_FI	"hid00101.htm"		//!< コマンドの索引(機能別)
#define HELPTOPIC_XC	"hid00063.htm"		//!< ExeCommands コマンド
#define HELPTOPIC_GR	"hid00056.htm"		//!< 文字列検索(GREP)
#define HELPTOPIC_RP	"hid00061.htm"		//!< 文字列置換
#define HELPTOPIC_GIT	"hid00090.htm"		//!< Gitの利用
#define HELPTOPIC_CH	"hid00109.htm"		//!< 変更履歴

//---------------------------------------------------------------------------
//非公開API
typedef BOOL (WINAPI *FUNC_GetFontResourceInfo)(LPCWSTR, DWORD*, LPVOID, DWORD);
extern  HMODULE hGdi32;
extern  FUNC_GetFontResourceInfo	lpfGetFontResourceInfo;

//---------------------------------------------------------------------------
/** @addtogroup DEFINE */
/** @{ */

#define DEF_WIN_WIDTH	800
#define DEF_WIN_HEIGHT	600

/** @defgroup DEF_SCR_MODE 画面モード(ScrMode) */
/** @{ */
#define SCMD_FLIST	1					//!< ファイラー
#define SCMD_TVIEW	2					//!< テキストビューア
#define SCMD_IVIEW	4					//!< イメージビューア
#define SCMD_GREP	8					//!< GREP
/** @} */

#define MAX_FILELIST	 2				//!< ファイルリスト数 (左右)
#define MAX_TASK_THREAD	 6				//!< 最大タスク数 = 4 + 2(割込実行用)

#define MAX_BGIMAGE		 6				//!< 背景画像数(背景*2/ 境界*2/ ノブ*2)
#define BGIMGID_KNOB_V	 4
#define BGIMGID_KNOB_H	 5

#define MAX_TABLIST	 	30				//!< 最大タブ数

#define MAX_FNTZOOM_SZ	72				//!< 最大フォントサイズ
#define MIN_FNTZOOM_SZ	2				//!< 最小フォントサイズ

#define MAX_WORKHISTORY 50				//!< 最大ワークリスト履歴数
#define MAX_CMD_HISTORY 1000			//!< 最大コマンド履歴数
#define MAX_FNCPY_HISTORY 50			//!< コピーしたファイル名の最大履歴数

#define CMPDEL_BUFF_SIZE 2048			//!< 完全削除のバッファサイズ
#define CRLF_DETECT_LINE 1000			//!< 改行コード判定の行数

#define ID_CALL_HOTKEY	101
#define ID_APP_HOTKEY	102

#define TMP_ARC_F	"ARC~%04u"			//!< アーカイブ用一時ディレクトリの書式
#define TMP_ARC_P	"ARC~????"			//!< アーカイブ用一時ディレクトリの検索パターン
#define TMP_FTP_D	"FTP~0000"			//!< FTP用一時ディレクトリ

#define FICO_INI_FILE "FolderIcon.INI"	//!< フォルダアイコン定義
#define HILT_INI_FILE "Highlight.INI"	//!< 構文強調表示定義
#define DIR_HIST_FILE "DirHistory.INI"	//!< ディレクトリ全体履歴
#define CALC_INI_FILE "Calculator.INI"	//!< 電卓の定義
#define TAGDATA_FILE  "TAGDATA.TXT"		//!< タグデータ
#define DRVLOG_FILE   "DriveLog.csv"	//!< ドライブ容量ログ
#define RENLOG_FILE   "renamelog.txt"	//!< 改名ログ
#define RENLIST_FILE  "renamelist.txt"	//!< 改名リスト
#define CLIP_BMP_FILE "CLIPBOARD.BMP"	//!< クリップボードの一時保存

#define WEBMAP_FILE	  "$~WEBMAP.HTM"	//!< Webマップ表示用ファイル
#define WEBMAP_TPLT	  "WEBMAP.HTM"		//!< Webマップ表示用テンプレート

#define RESPONSE_FILE "$~LISTFILE.TXT"	//!< レスポンスファイル名
#define RESPONSE_ERR  "ERROR"

#define DISTR_FILE	  "Distribute.INI"	//!< 振り分け登録ファイル

#define FONTSMPL_FILE "FontSample.INI"	//!< フォント見本

#define SFX_AUTOREN   "_\\SN(1)"		//!< デフォルトの自動改名書式(サフィックス)
#define FMT_AUTO_REN  "\\N" SFX_AUTOREN	//!< デフォルトの自動改名書式

#define LOG_ALL_TASK_RDY	"All Task Ready"

/** @defgroup DEF_CSVITMCNT CSVの項目数 */
/** @{ */
#define EXTMENU_CSVITMCNT	6			//!< caption,cmd,prm,alias,show,icon
#define EXTTOOL_CSVITMCNT	6			//!< caption,exe,prm,wk_dir,alias,show
#define TABLIST_CSVITMCNT	9			//!< path0,path1,caption,icon,home0,home1,nwl_mode,nwl,sync_lr
#define DISTRLS_CSVITMCNT	4			//!< title,enable,mask,dist
#define REGDIR_CSVITMCNT	4			//!< key,title,path,user_name
#define MAX_CSV_ITEM	  255
/** @} */

/** @defgroup DEF_LISTBOX_TAG リストボックス用オプションフラグ
 * @details ListBox->Tag に設定します。@n
 * 下位2バイト = ファイル情報:項目名最大幅/ 登録ディレクトリ:「場所」の表示位置@n
 * 上位4ビットは UserMdl で使用
 */
/** @{ */
#define LBTAG_OPT_FIF1	0x00010000		//!< ファイル情報(最初の3行は基本情報)
#define LBTAG_OPT_FIF2	0x00020000		//!< ファイル情報
#define LBTAG_OPT_SDIR	0x00040000		//!< 特殊フォルダ一覧(環境変数使用時)
#define LBTAG_OPT_TREE	0x00080000		//!< ツリー表示
#define LBTAG_OPT_ZOOM	0x00100000		//!< ズーム可能
#define LBTAG_OPT_LNNO	0x00200000		//!< 行番号表示
#define LBTAG_OPT_LCPY	0x00400000		//!< 1行コピー可能
#define LBTAG_OPT_LOOP	0x00800000		//!< ループ移動
#define LBTAG_GEN_LIST	0x01000000		//!< 一覧ダイアログ
#define LBTAG_FIF_LIST	0x02000000		//!< ファイル情報ダイアログ
#define LBTAG_TAB_FNAM	0x04000000		//!< タブ以降にファイル名を持つ
#define LBTAG_VAR_LIST	0x08000000		//!< 「名前=値」形式
/** @} */

//---------------------------------------------------------------------------
#define SHOW_WARN_TAG	-1

//---------------------------------------------------------------------------
//検索中に受け付けるコマンド
#define ONFIND_CMD	"CursorUp|CursorDown|PageUp|PageDown|CurrToOpp|FileEdit|BinaryEdit|OpenByApp|OpenByWin|OpenStandard|Select"

//---------------------------------------------------------------------------
//load_ImageFile の戻り値
#define LOADED_BY_STD	1		//!< WIC標準
#define LOADED_BY_WIC	2		//!< WICその他

//---------------------------------------------------------------------------
enum SeaOpt {soMigemo, soRegEx, soAndOr, soFuzzy, soCaseSens, soWord, soBytes, soFromPos,
			 soCSV, soTSV, soTree, soGitGrep, soGrep, soGrepS, soGrepF};
typedef Set <SeaOpt, soMigemo, soGrepF> SearchOption;	//!< 検索用オプション

/** @} */

//---------------------------------------------------------------------------
/** @brief 二重起動終了時の画面情報 */
struct win_dat {
//メインウィンドウ
	int WinTop;
	int WinLeft;
	int WinWidth;
	int WinHeight;
	TWindowState WinState;
	int WinPPI;
//サブパネル
	int SubHeight;
	int SubWidth;
	int InfWidth;
	int InfHeight;
	int ImageWidth;
	int ImageHeight;
	int TailHeight;
//その他
	bool ShowFileListOnly;
};

//---------------------------------------------------------------------------
extern TCursor crTmpPrev;		//!< カーソルのプレビュー用

//---------------------------------------------------------------------------
extern UnicodeString KeyStr_SELECT;

extern UnicodeString KeyStr_Copy;
extern UnicodeString KeyStr_Cut;
extern UnicodeString KeyStr_Migemo;
extern UnicodeString KeyStr_RegEx;
extern UnicodeString KeyStr_Word;
extern UnicodeString KeyStr_Case;

extern UnicodeString KeysStr_Filter;
extern UnicodeString KeysStr_ToList;
extern UnicodeString KeysStr_ToKeywd;
extern UnicodeString KeysStr_ToMask;

extern UnicodeString KeysStr_CsrDown;
extern UnicodeString KeysStr_CsrUp;
extern UnicodeString KeysStr_PgDown;
extern UnicodeString KeysStr_PgUp;
extern UnicodeString KeysStr_Popup;

extern UnicodeString TabPinMark;		//!< タブ固定ピンマーク
extern UnicodeString HEAD_Mark;			//!< git HEAD マーク
extern UnicodeString PLAY_Mark;			//!< 再生中マーク

extern UnicodeString SortIdStr;

//---------------------------------------------------------------------------
extern HWND   MainHandle;				//!< メインウィンドウのハンドル
extern DWORD  ProcessId;				//!< プロセスID
extern bool   IsAdmin;					//!< 管理者権限
extern bool   IsPrimary;				//!< 最初に起動された
extern bool   GitExists;				//!< Git がインストールされている
extern bool   GrepExists;				//!< grep.exe がインストールされている
extern bool   IsMuted;					//!< 音量ミュート
extern int    StartedCount;				//!< 実行開始カウント(m秒)
extern int    NyanFiIdNo;				//!< 多重 NyanFi 識別ID
extern bool   NoRoundWin;				//!< 角丸ウィンドウ抑止

extern int    ScrMode;					//!< 画面モード

extern UnicodeString VclStyle;			//!< VCLスタイル

extern MarkList *ErrMarkList;

extern TRect  FileListRect;

extern TRichEdit *TempRichEdit;

extern TTaskThread *TaskThread[MAX_TASK_THREAD];	//!< タスク処理スレッド
extern bool gTaskCancel[MAX_TASK_THREAD];
extern bool gTaskPause[MAX_TASK_THREAD];
extern int  MaxTasks;						//!< 最大タスク数
extern bool RsvSuspended;					//!< 予約の保留
extern TaskConfigList *TaskReserveList;		//!< タスク予約リスト
extern int  LastOpCount;					//!< 最後に操作したときのカウント値

extern TImgViewThread   *ImgViewThread;		//!< 画像ビュー処理スレッド
extern TThumbnailThread *ThumbnailThread;	//!< サムネイル取得スレッド
extern TGetIconThread   *GetIconThread;		//!< アイコン取得スレッド

extern UserArcUnit *usr_ARC;				//!< アーカイブ処理ユニット
extern UnicodeString FExt7zDll;				//!< 7z.dll で対応する拡張子

extern MigemoUnit  *usr_Migemo;				//!< Migemo 処理ユニット
extern UnicodeString MigemoPath;			//!< Migemo ディレクトリ
extern bool LastMigemoMode;
extern bool LastMigemoModeF;

extern int  WicScaleOpt;			//!< WICの縮小・拡大アルゴリズム
extern UnicodeString WicFextStr;	//!< WICが対応している拡張子

extern bool gCopyAll;
extern bool gCopyCancel;

extern int  gCopyMode;				//!< 左右が別ディレクトリの場合のコピーモード
extern int  gCopyMode2;				//!< 左右が同一ディレクトリの場合のコピーモード
extern int  xCopyMode;				//!< ExeCommand 内で用いる強制モード

#define CPYMD_OW			0
#define CPYMD_NEW			1
#define CPYMD_SKIP			2
#define CPYMD_AUT_REN		3
#define CPYMD_MAN_REN		4
#define CPYMD_REN_CLONE		5
#define CPYMD_NEW_BACKUP	10

extern UnicodeString gCopyFmt;

extern int OptionPageIndex;			//!< オプション設定ダイアログのページインデックス

extern bool SyncLR;					//!< 左右のディレクトリ変更を同期

extern UnicodeString GlobalErrMsg;

extern bool Initialized;			//!< 初期化が完了した
extern bool UnInitializing;			//!< 終了処理が開始された
extern bool Closing;				//!< 終了処理中

extern int  InhReload;				//!< Reload の抑止
extern bool DisReload;				//!< Reload の無効化

extern bool InhUpdate;			  	//!< UpdateList 抑止
extern bool InhCmdHistory;  		//!< コマンド履歴の抑止

extern UnicodeString FindPath;
extern bool FindAborted;			//!< 検索中断要求
extern bool FindDiff;				//!< DiffDir 実行中
extern int  FindTag;
extern int  FindCount;				//!< マッチ数

extern bool CalcAborted;			//!< 計算中断要求
extern int  CalcTag;

extern bool GitGrepAborted;			//!< GitGrep の中断要求

//---------------------------------------------------------------------------
extern bool MultiInstance;			//!< 二重起動を許す
extern bool CloseOthers;			//!< 他のNyanFiを終了
extern bool StoreTaskTray;			//!< 最小化時にタスクトレイに格納
extern bool ShowDirType;			//!< DIR種別を表示
extern bool ShowSpace;				//!< 空白を表示
extern bool UseIndIcon;				//!< ファイル固有のアイコンを使用
extern bool ShowHideAtr;			//!< 隠しファイルを表示
extern bool ShowSystemAtr;			//!< システムファイルを表示
extern bool DispRegName;			//!< パスの表示に登録名を用いる
extern bool UncToNetDrive;			//!< UNCをネットワークドライブ名に
extern bool CompInTitleBar;			//!< タイトルバーにコンピュータ名を表示
extern bool PathInTitleBar;			//!< タイトルバーにカレントパスを表示
extern bool TabGrInTitleBar;		//!< タイトルバーにタググループ名を表示
extern bool OmitEndOfName;			//!< 長い名前は末尾を省略
extern bool ShowAdsInf;				//!< 代替データストリーム情報を表示
extern bool ShowUseProcInf;			//!< プロセス使用情報を表示
extern bool ShowDirJumboIco;		//!< ディレクトリは特大アイコンを表示
extern bool ShowInZipImg;			//!< ZIP内の画像を表示
extern bool PreviewAniGif;			//!< アニメーションGIFのプレビュー
extern bool SetPrvCursor;			//!< プレビュー内でマウスカーソルを設定
extern bool ForceDel;				//!< 読込専用ファイルも強制的に上書き・削除
extern bool RemoveCdReadOnly;		//!< CD-ROMからのコピー時に読込専用属性を解除
extern bool CopyTags;				//!< タグをコピー
extern bool CopyNoBuffering;		//!< バッファーなしI/Oを使用してコピー
extern bool ShowArcCopyProg;
extern bool DelUseTrash;			//!< ファイルの削除にゴミ箱を使う
extern bool EditNewText;			//!< 新規テキスト作成後にエディタで開く
extern bool ViewArcInf;				//!< アーカイブ内のファイル情報を表示
extern bool CheckTS;				//!< 拡張子 .ts (MPEG2-TS/TypeScript)の判別を行う
extern bool ReloadOnActive;			//!< アクティブ時に最新の情報に
extern bool OpenAddedDrive;			//!< ドライブが追加されたらカレントに表示
extern bool CheckUnc;				//!< UNCパスをチェック
extern bool ShowMsgHint;			//!< 警告などをヒント表示
extern bool ShowKeyHint;			//!< 2ストローク操作のヒント表示
extern bool ShowNoKeyHint;			//!< 無効な2ストローク操作の警告を出す
extern bool ShowCopyHint;			//!< クリップボードへのコピー情報をヒント表示
extern bool ShowDuplNotify;			//!< 二重起動されたNyanFiからの通知を表示
extern bool ShowTooltip;			//!< ツールチップを表示
extern bool LogErrOnly;				//!< タスクでエラー箇所のみをログ表示
extern bool LogErrMsg;				//!< ログにエラーメッセージを出力
extern bool LogDebugInf;			//!< ログにデバッグ情報を出力
extern bool LogHideSkip;			//!< ログにスキップ項目を出力しない
extern bool LogFullPath;			//!< ログの処理内容をフルパスで表示
extern bool LogDestination;			//!< ログに処理先を表示
extern bool SaveLog;				//!< 終了時にログを保存
extern bool AppendLog;				//!< 同日のログは追記保存
extern bool NotSortWorkList;		//!< ワークリスト項目をソートしない
extern bool RegWorkCsrPos;			//!< カーソル位置に登録
extern bool AutoDelWorkList;		//!< 存在しない項目を自動削除
extern bool NoCheckWorkUnc;			//!< ワークリストのUNCをチェックしない
extern bool AddToRecent;			//!< 最近使った項目に追加
extern bool NoCheckRecentUnc;		//!< UNCパスをチェックしない
extern bool DirHistCsrPos;			//!< ディレクトリ履歴でカーソル位置を記憶
extern bool DirHistSortMode;		//!< ディレクトリ履歴でソート方法を記憶
extern bool DelDplDirHist;			//!< 重複するディレクトリ履歴を削除
extern bool WorkToDirHist;			//!< ワークリストを履歴に含める
extern bool NoCheckDirHist;			//!< ディレクトリ履歴の存在チェックを行わない
extern bool ExtSaveDirHist;			//!< 全体履歴を別ファイルに保存
extern bool LoopFilerCursor;		//!< ファイラーでカーソルをループ移動
extern bool FlCursorVisible;		//!< ファイラーでカーソルを常に可視領域に
extern bool AutoCompComboBox;		//!< コンボボックス入力を自動補完
extern bool DialogCenter;			//!< ダイアログをメイン画面の中央に
extern bool InhbitAltMenu;			//!< ALTキーでメニューにフォーカスしない
extern bool SelectByMouse;			//!< マウスでファイラーの項目を選択
extern bool SelectBaseOnly;			//!< ファイル名主部でのみ選択
extern bool SelectIconSngl;			//!< アイコン部分で個別に選択
extern bool TimColEnabled;			//!< タイムスタンプの配色を有効
extern bool PriorFExtCol;			//!< 拡張子部分は属性色より優先
extern bool ColorOnlyFExt;			//!< 拡張子別配色は拡張子部分のみに適用
extern bool SymColorToName;			//!< ファイル名主部にシンボリックリンク色を適用
extern bool RevTagColor;			//!< タグ色の反転表示
extern bool InactiveGray;			//!< 非アクティブなメイン画面の一部をグレー化
extern bool ShowMainMenu;			//!< メインメニューを表示
extern bool ShowImgPreview;			//!< イメージプレビューを表示
extern bool ShowProperty;			//!< ファイル情報を表示
extern bool ShowLogWin;				//!< ログウィンドウを表示
extern bool ShowFileListOnly;		//!< ファイルリストのみを表示
extern bool ShowFileListOnly2;
extern bool ShowSttBar;				//!< ステータスバーを表示
extern bool ShowToolBar;			//!< ツールバーを表示(ファイラー)
extern bool ShowToolBarV;			//!< ツールバーを表示(テキストビューア)
extern bool ShowToolBarI;			//!< ツールバーを表示(イメージビューア)
extern bool ToolBarISide;			//!< ツールバーをサイドバー上に表示(イメージビューア)
extern bool ShowTabBar;				//!< タブバーを表示
extern bool ShowFKeyBar;			//!< ファンクションキーバーを表示
extern bool ShowClsTabBtn;			//!< タブの閉じるボタンを表示
extern bool ShowPopTabBtn;			//!< タブの▼ボタンを表示
extern bool ShowPopDirBtn;			//!< ディレクトリ情報の▼ボタンを表示
extern bool HideScrBar;				//!< 縦スクロールバーを隠す
extern bool ShowByteSize;			//!< バイト単位表示
extern bool ShowTargetInf;			//!< 実体の情報で表示
extern bool ShowHeader;				//!< ヘッダを表示
extern bool FixListWidth;			//!< リスト幅を固定
extern bool KeepOnResize;			//!< ウィンドウサイズ変更時に比率を維持
extern bool KeepCurListWidth;		//!< カレント側のリスト幅を維持
extern bool NoSpaceFExt;			//!< 拡張子を分離しない
extern bool HideTitleMenu;			//!< 最大化時にタイトルバーとメニューを隠す
extern bool ShowLineNo;				//!< 行番号を表示
extern bool ShowLineCursor;			//!< 行カーソルを表示
extern bool ShowTAB;				//!< タブを表示
extern bool ShowCR;					//!< 改行を表示
extern bool ShowIndent;				//!< インデントガイドを表示
extern bool ShowTextRuler;			//!< ルーラを表示
extern bool ShowSticky;				//!< スティッキーを表示
extern bool ScrBarToFoldPos;		//!< スクロールバーを折り返し位置に表示
extern bool TxtSttIsBottom;			//!< 情報ヘッダを下部に表示(TV)
extern bool ChkAozora;				//!< 青空文庫形式を考慮する
extern bool UseXd2tx;				//!< xd2txlib.dll でテキスト表示
extern bool ClickableUrl;			//!< ダブルクリックでURLを開く
extern bool RestoreViewLine;		//!< ビューアでカーソルの行位置を復元
extern bool EmpComment;				//!< コメントを強調表示
extern bool EmpStrings;				//!< 文字列を強調表示
extern bool EmpReserved;			//!< 予約語を強調表示
extern bool EmpSymbol;				//!< シンボルを強調表示
extern bool EmpNumeric;				//!< 数値を強調表示
extern bool EmpHeadline;			//!< 見出しを強調表示
extern bool EmpRuby;				//!< ルビを強調表示
extern bool RotViewImg;				//!< Exif情報にしたがって画像を回転
extern bool KeepZoomRatio;			//!< 別の画像に移った時にズーム倍率を維持する
extern bool ShowThumbName;			//!< サムネイルにファイル名を表示
extern bool ShowThumbExif;			//!< サムネイルに簡易Exif情報を表示
extern bool ShowThumbTags;			//!< サムネイルにタグを表示
extern bool ShowThumbFExt;			//!< サムネイルに拡張子を強調表示
extern bool NotThumbIfArc;			//!< アーカイブ内は一括取得しない
extern bool CacheThumbADS;			//!< サムネイルをADSにキャッシュする
extern bool LoopViewCursor;			//!< イメージビューアでカーソルをループ移動
extern bool HintTopEndImg;			//!< 先頭・最後でヒント表示
extern bool BeepTopEndImg;			//!< 警告音
extern bool ImgSttIsBottom;			//!< 情報ヘッダを下部に表示(IV)
extern bool SeekBindDir;			//!< シークバーの始点を綴じ方向に合わせる
extern bool SeekSwapNxtPrv;			//!< 右綴じでNext/PrevFile入替
extern bool HideCsrInFull;			//!< 全画面表示でマウスカーソルを隠す
extern bool HideThumbInFull;		//!< 全画面表示でサムネイルを隠す
extern bool AnimateGif;				//!< イメージビューアでアニメーションGIFを表示
extern bool ShowThumbScroll;		//!< サムネイルのスクロールバーを表示
extern bool ShowHistogram;			//!< ヒストグラムを表示
extern bool ShowLoupe;				//!< ルーペを表示
extern bool ShowSubViewer;			//!< GIFビューアを表示
extern bool ShowSeekBar;			//!< シークバーを表示
extern bool WarnHighlight;			//!< 白飛び警告
extern bool DoublePage;				//!< 見開き表示
extern bool RightBind;				//!< 右綴じ

extern UnicodeString JpWrapChar1;	//!< 行頭禁則文字
extern UnicodeString JpWrapChar2;	//!< 行末禁則文字
extern bool WordWrap;				//!< ワードラップ

extern bool PermitDotCmds;			//!< .nyanfi でコマンド実行を許可
extern bool InheritDotNyan;			//!< 上位ディレクトリから .nyanfi を継承
extern bool DotNyanPerUser;			//!< ユーザ名別に .nyanfi を作成
extern int  InitialModeI;			//!< イメージビューアを開いた時の初期状態
extern int  LastZoomRatio;			//!< 前回のズーム

extern bool MarkImgClose;			//!< イメージビューアを閉じる時に栞マークを設定
extern UnicodeString MarkImgPath;	//!< マークするパス
extern UnicodeString MarkImgFExt;	//!< マークする拡張子
extern UnicodeString MarkImgMemo;

extern int  IconMode;				//!< アイコンの表示モード		0:非表示/ 1:表示/ 2:ディレクトリのみ表示
extern int  ScrBarStyle;			//!< スクロールバー・スタイル	0:標準/ 1:シンプル/ 2:3/4幅/ 3:1/2幅/ 4:画像

extern bool ModalScreen;			//!< モーダル表示効果
extern int  ModalScrAlpha;			//!< スクリーンの透明度
extern TColor col_ModalScr;			//!< モーダル表示効果色

extern TColor col_bgOptTab;			//!< アクティブな設定タブの背景色
extern TColor col_fgOptTab;			//!< アクティブな設定タブの文字色

extern int TlWinBorderWidth;		//!< ツールウインドウの境界線幅

extern UnicodeString DlgMoveShift;	//!< ダイアログ移動のシフトキー
extern UnicodeString DlgSizeShift;	//!< ダイアログのサイズ変更のシフトキー
extern int DlgMovePrm;
extern int DlgSizePrm;

extern int DblClickFlMode;				//!< ファイルリストでのダブルクリック

extern UnicodeString WheelCmdF[4];		//!< ホイールコマンド
extern UnicodeString WheelCmdV[4];
extern UnicodeString WheelCmdI[4];

extern UnicodeString WheelBtnCmdF[4];	//!< ホイールボタンを押したときのコマンド
extern UnicodeString WheelBtnCmdV;
extern UnicodeString WheelBtnCmdI;

extern UnicodeString X1BtnCmdF;			//!< X1ボタンを押したときのコマンド
extern UnicodeString X2BtnCmdF;			//!< X2ボタンを押したときのコマンド
extern UnicodeString X1BtnCmdV;
extern UnicodeString X2BtnCmdV;
extern UnicodeString X1BtnCmdI;
extern UnicodeString X2BtnCmdI;

extern UnicodeString EmpBinPtn1;		//!< バイナリ強調パターン1
extern UnicodeString EmpBinPtn2;		//!< バイナリ強調パターン2
extern UnicodeString EmpBinPtn3;		//!< バイナリ強調パターン3

extern UnicodeString HtmInsHrCls;		//!< ブロックの前に罫線を挿入するクラス
extern UnicodeString HtmHdrStr;			//!< 見出し文字
extern bool HtmInsHrSct;				//!< <section>の前に罫線挿入
extern bool HtmInsHrArt;				//!< <article>の前に罫線挿入
extern bool HtmInsHrNav;				//!< <nav>の前に罫線挿入
extern bool ToMarkdown;					//!< Markdown記法に変換
extern UnicodeString HtmDelBlkCls;		//!< 削除するブロックの class
extern UnicodeString HtmDelBlkId;		//!< 削除するブロックの id

extern UnicodeString NoWatchPath;		//!< ディレクトリ監視から除外するパス

extern UnicodeString FExtGetInf;		//!< ファイル情報を取得する拡張子
extern UnicodeString FExtNoInf;			//!< ファイル情報を取得しない拡張子
extern UnicodeString NoInfPath;			//!< ファイル情報を取得しないパス
extern UnicodeString EmpInfItems;		//!< 強調表示するファイル情報項目(|区切り)
extern TStringList  *HideInfItems;		//!< 隠すファイル情報項目(拡張子=|区切り形式のリスト)

extern UnicodeString FExtImgPrv;		//!< イメージプレビューを行う拡張子
extern UnicodeString FExtNoImgPrv;		//!< イメージプレビューを行わない拡張子
extern UnicodeString NoImgPrvPath;		//!< イメージプレビューを行わないパスリスト

extern UnicodeString FExtNoIView;		//!< イメージビューアで閲覧しない拡張子
extern UnicodeString NoCachePath;		//!< サムネイルキャッシュしないパス

extern UnicodeString DrvInfFmtR;		//!< ドライブ情報の書式 : ルート
extern UnicodeString DrvInfFmtS;		//!< ドライブ情報の書式 : 選択時
extern UnicodeString DrvInfFmtN;		//!< ドライブ情報の書式 : その他

extern UnicodeString SttBarFmt;			//!< ステータスバーの書式
extern UnicodeString SttClockFmt;		//!< 時計の書式

extern int  MaxLogFiles;				//!< ログファイルの保存世代数
extern int  MaxDirHistory;				//!< ディレクトリ履歴の保存数

extern int  ProtectDirMode;				//!< ディレクトリの削除制限モード
extern bool ProtectSubDir;				//!< 下位ディレクトリも制限
extern bool ProtectFile;				//!< ファイルも制限

extern bool WarnPowerFail;				//!< 電源切断警告
extern bool WarnDisconnect;				//!< インターネット接続切れ
extern bool WarnLowBattery;				//!< バッテリー低下
extern int  BatLowerLimit;

extern int  BorderMoveWidth;			//!< BorderLeft、BorderRight: １回の移動幅
extern UnicodeString AutoRenFmt;		//!< Copy、Move: 同名時の自動改名書式
extern int  RemoteWaitTime;				//!< コールバック時のウェイトタイム
extern int  NormalWaitTime;
extern int  NopDtctTime;				//!< 無操作だとみなす時間
extern int  TimeTolerance;				//!< タイムスタンプの許容誤差

extern bool AppListChgMin;				//!< AppList:   他アプリに切り替えたときに最小化
extern bool CreDirChg;					//!< CreateDir: ディレクトリ作成後にカレント変更
extern bool CreDirCnvChar;				//!< CreateDir: 文字置換を適用
extern UnicodeString FExtExeFile;		//!< ExeCommandLine: 実行ファイルとみなす拡張子
extern bool OpenOnlyCurEdit;			//!< FileEdit:  選択状態にかかわらずカーソル位置のみを開く
extern bool DontClrSelEdit;				//!< FileEdit:  選択を解除しない
extern int  OpenByMode;					//!< OpenByApp:  関連付けされていない場合の動作モード
extern bool OpenDirByStd;				//!< OpenByApp:  ディレクトリでは標準 Enter キー動作
extern bool OpenOnlyCurApp;				//!< OpenByApp:  選択状態にかかわらずカーソル位置のみを開く
extern bool DontClrSelApp;				//!< OpenByApp:  選択を解除しない
extern bool OpenOnlyCurWin;				//!< OpenByWin:  選択状態にかかわらずカーソル位置のみを開く
extern bool DontClrSelWin;				//!< OpenByWin:  選択を解除しない
extern bool OpenStdTabGroup;			//!< OpenStandard: タブグループを開く
extern bool OpenStdMenuFile;			//!< OpenStandard: メニューファイルを開く
extern bool OpenStdResultList;			//!< OpenStandard: 結果リストを開く
extern bool OpenStdFindSet;				//!< OpenStandard: 検索設定を開く
extern bool DownAfterOpenStd;			//!< OpenStandard: 実行後にカーソルを下に移動
extern bool OpenStdOnResList;			//!< OpenStandard: 結果リストでも通常動作
extern UnicodeString IniSeaShift;		//!< IniSearch:  頭文字サーチのシフトキー
extern bool IniSeaByNum;				//!<   数字キーでも頭文字サーチ
extern bool IniSeaBySign;				//!<   Shift+数字キーの記号もサーチ
extern bool IncSeaCaseSens;				//!< IncSearch: 大小文字を区別
extern bool IncSeaFuzzy;				//!< IncSearch: あいまい検索
extern bool IncSeaLoop;					//!< IncSearch: 上下端でループ
extern bool IncSeaMatch1Exit;			//!< IncSearch: マッチ数1で抜ける
extern int  IncSeaMigemoMin;			//!< IncSearch: Migemo の検索開始文字数
extern bool SyncItem;					//!< SyncLR : 項目位置も同期
extern bool NotShowNoTask;				//!< TaskMan: タスクを実行していないときはマネージャを表示しない
extern UnicodeString GetFaviconUrl;		//!< favicon 取得API

extern bool FindPathColumn;				//!< 結果リストに「場所」列を表示
extern int  FindPathWidth;				//!< 「場所」の最小列幅
extern bool FindTagsColumn;				//!< 結果リストに「タグ」列を表示
extern int  FindTagsWidth;				//!< 「タグ」の最小列幅

extern bool GrepNotUpdList;				//!< GREP検索中に結果リストを更新しない
extern bool RepNotUpdList;				//!< 一括置換中に結果リストを更新しない
extern bool GrepShowItemNo;				//!< GREP結果に項目番号を表示
extern bool GrepFileItemNo;				//!< 項目番号をファイル単位で表示
extern bool GrepShowSubDir;				//!< GREP結果にサブディレクトリ名を表示
extern bool GrepTrimTop;				//!< GREP結果で行頭のタブや空白を削除
extern bool GrepOmitTop;				//!< GREP結果でマッチ語が見えないとき前部分を省略
extern bool GrepEmFilter;				//!< GREP結果でフィルタの語を強調表示
extern bool GrepAdjNextLn;				//!< GREP結果で次行表示部分の明度を加減
extern int  GrepOutMode;				//!< GREP 出力先	0:無し/ 1:ファイル/ 2:クリップボード
extern UnicodeString GrepFileName;		//!< 出力ファイル名
extern UnicodeString GrepAppName;		//!< 起動アプリ名
extern UnicodeString GrepAppParam;		//!< アプリの起動パラメータ
extern UnicodeString GrepAppDir;		//!< アプリの作業ディレクトリ
extern bool GrepAppEnabled;				//!< アプリ有効
extern bool GrepAppend;					//!< 既存ファイルに追加
extern UnicodeString GrepFileFmt;		//!< ファイル情報の書式
extern UnicodeString GrepInsStrW;		//!< マッチ語前の挿入文字列
extern UnicodeString GrepInsStrW2;		//!< マッチ語後の挿入文字列
extern bool GrepTrimLeft;				//!< 行頭のタブや空白を削除
extern bool GrepReplaceTab;				//!< タブを空白1文字に置換
extern bool GrepReplaceCr;				//!< 改行を文字列に置換
extern UnicodeString GrepRepCrStr;		//!< 改行の置換文字列
extern bool BackupReplace;				//!< 置換バックアップ作成
extern UnicodeString FExtRepBackup;		//!< 置換バックアップの拡張子
extern UnicodeString RepBackupDir;		//!< 置換バックアップ先
extern UnicodeString ReplaceLogName;	//!< 置換ログファイル名
extern bool SaveReplaceLog;				//!< 置換ログを保存
extern bool ReplaceAppend;				//!< 既存ファイルに追加
extern bool OpenReplaceLog;				//!< ログをテキストエディタで開く

extern UnicodeString UserName;			//!< ユーザ名
extern UnicodeString TempPath;			//!< 一時ディレクトリ
extern UnicodeString TempPathA;			//!< 一時ディレクトリ(絶対)
extern UnicodeString TempPathFTP;		//!< FTP用一時ディレクトリ(絶対)

extern UnicodeString DownloadPath;		//!< ダウンロード用
extern UnicodeString LibraryPath;		//!< ライブラリ
extern UnicodeString WorkListPath;		//!< ワークリスト参照パス
extern UnicodeString ResultListPath;	//!< 結果リスト参照パス
extern UnicodeString ListFilePath;		//!< リストファイル参照パス
extern UnicodeString FindSetPath;		//!< 検索結果参照パス
extern UnicodeString RefParamPath;		//!< パラメータ参照パス
extern UnicodeString CmdFilePath;		//!< コマンドファイル参照パス
extern UnicodeString CmdGitExe;			//!< git.exe
extern UnicodeString GitBashExe;		//!< git-bash.exe
extern UnicodeString GitGuiExe;			//!< git-gui.exe
extern UnicodeString CmdGrepExe;		//!< grep.exe

extern int VersionNo;
extern UnicodeString VersionStr;		//!< バージョン表示
extern UnicodeString OSVerInfStr;		//!< OSバージョン情報
extern bool IsWin11;					//!< Windows 11 か？

extern UnicodeString DirBraStr;			//!< ディレクトリ括弧文字
extern UnicodeString DirKetStr;
extern UnicodeString TimeStampFmt;		//!< タイムスタンプの表示書式

extern UnicodeString CallHotKey;		//!< 呼び出しホットキー
extern UnicodeString AppListHotKey;		//!< アプリ一覧ホットキー
extern UnicodeString AppListHotPrm;		//!< アプリ一覧パラメータ

extern UnicodeString SaveTxtPath;		//!< テキスト保存パス
extern int SaveEncIndex;				//!< エンコーディングのインデックス

extern UnicodeString NoDirHistPath;		//!< ディレクトリ履歴に入れないパス
extern UnicodeString NoEditHistPath;	//!< 編集履歴に入れないパス
extern UnicodeString NoViewHistPath;	//!< 閲覧履歴に入れないパス
extern UnicodeString NoRepoListPath;	//!< リポジトリ一覧に表示しないパス

extern UnicodeString DirDelimiter;		//!< ディレクトリ区切りの表示文字

extern bool NoCheckUncRPT;				//!< UNCパスのリパースポイント情報をチェックしない

extern int  InactiveAdjust;				//!< 非アクティブ時グレー化の最の加減値

extern int CurTabIndex;					//!< タブインデックス(0～)

extern UnicodeString CurPathName;
extern int CurListTag;					//!< カレント側タグ  0:左/ 1:右
extern int OppListTag;					//!< 反対側タグ
extern int LastCurTag;					//!< 前回終了時のカレント
extern int WorkingTag;					//!< 作業側のタグ(CurWorking = true 時)

extern UnicodeString FTPTextModeFExt;	//!< テキストモードで転送する拡張子
extern bool FTPDlKeepTime;				//!< ダウンロードファイルのタイムスタンプを維持
extern bool FTPUpKeepTime;				//!< アップロードファイルのタイムスタンプを維持
extern bool FTPUpToLower;				//!< ファイル名を小文字化してアップロードする
extern bool FTPLogResponse;				//!< 応答メッセージをログに表示
extern int  FTPRemoteSide;				//!< リモート側 0:カレント/ 1:左/ 2:右
extern int  FTPDisconTimeout;			//!< FTPが無操作の場合切断する時間

extern UnicodeString FTPSndConnect;		//!< 接続時の通知音
extern UnicodeString FTPSndDiscon;		//!< 切断時の通知音
extern UnicodeString FTPSndTransfer;	//!< 転送完了時の通知音

extern UnicodeString FTPPathName;

extern TListBox *FileListBox[MAX_FILELIST];		//!< ファイルリストボックス
extern TPanel	*FileListPanel[MAX_FILELIST];

extern UnicodeString ViewFileName;		//!< 表示中のファイル名
extern UnicodeString ViewFileName2;
extern bool ViewFromArc;				//!< アーカイブから表示

//---------------------------------------------------------------------------
#define GENLST_FILELIST	1
#define GENLST_DRIVE	2
#define GENLST_CMDSLIST	3
#define GENLST_TABLIST	4
#define GENLST_ICON		5
#define GENLST_FONT		6

extern TStringList *GeneralList;		//!< TStringList のリスト(一括破棄用)

//---------------------------------------------------------------------------
/** @defgroup FILELIST ファイルリストの操作 */
/** @{ */
extern TStringList *FileList[MAX_FILELIST];			//!< ファイルリスト
extern TStringList *ArcFileList[MAX_FILELIST];		//!< 仮想ディレクトリのファイルリスト
extern TStringList *AdsFileList[MAX_FILELIST];		//!< 代替データストリームのファイルリスト
extern TStringList *ResultList[MAX_FILELIST];		//!< 検索結果リスト
extern TStringList *SelMaskList[MAX_FILELIST];		//!< 選択マスクリスト
extern TStringList *TmpBufList[MAX_FILELIST];		//!< 一時退避リスト
/** @} */

extern TStringList *DriveInfoList;		//!< ドライブ情報
extern TStringList *DriveLogList;		//!< ドライブ容量ログ
extern UnicodeString DriveLogName;		//!< ドライブ容量ログのファイル名

extern TStringList *WatchTailList;		//!< 末尾監視リスト
extern UnicodeString LastWatchLog;		//!< 直前の監視ログ

extern TStringList *InvalidUncList;		//!< 無効なUNCリスト

extern TStringList *GitCfgUrlList;		//!< .Git\config - URL 対応リスト (ファイル名=URL \t yyyy/mm/dd hh:nn:ss)
extern TStringList *GitInfList;			//!< Git情報のキャッシュ

extern TStringList *TabList;			//!< タブリスト
extern TStringList *TabBuff;			//!< 固定復帰用バッファ
extern int FlTabWidth;					//!< タブの幅
extern int FlTabStyle;					//!< タブのスタイル
extern UnicodeString TabGroupName;		//!< タブグループ・ファイル名

extern TStringList *CachedIcoList;		//!< ファイル固有アイコンのキャッシュ (IconRWLock で保護すること)
extern TMultiReadExclusiveWriteSynchronizer *IconRWLock;
extern int IconCache;					//!< アイコンキャシュ数

extern UsrIniFile  *FolderIconFile;		//!< フォルダアイコン設定ファイル
extern TStringList *FolderIconList;		//!< フォルダアイコンリスト
extern TMultiReadExclusiveWriteSynchronizer *FldIcoRWLock;
extern UnicodeString DefFldIcoName;		//!< デフォルトのフォルダアイコン
extern HICON hLinkIcon;					//!< リンクマーク(Shell32.dll,29)

extern TStringList *GeneralIconList;	//!< ファイルリスト表示用の一般アイコン
extern TStringList *MenuBtnIcoList;
extern TStringList *UsrIcoList;			//!< メニュー、ツールボタン用アイコン
extern TStringList *DrvIcoList;			//!< ドライブのアイコンリスト

extern TStringList *BakSetupList;		//!< バックアップ設定リスト
extern TStringList *SyncDirList;		//!< 同期コピー先リスト
extern TStringList *AssRenList;			//!< 関連ファイル同時改名設定リスト
extern TStringList *DistrDefList;		//!< 振り分け正義リスト

extern TStringList *GrepPathList;		//!< GREP 対象パスのリスト
extern TStringList *GrepFileList;		//!< GREP 対象ファイルリスト
extern TStringList *GrepResultBuff;		//!< GREP 結果リスト表示用バッファ
extern TStringList *GrepResultList;		//!< GREP の結果リスト
extern TStringList *GrepStashBuff;		//!< GREP 結果の退避バッファ
extern TStringList *GrepUnsortBuff;		//!< GREP ソート前バッファ
extern TStringList *GrepMatchList;		//!< GREP ファイル別マッチ数リスト
extern int  ResultListMode;				//!< 結果リストの内容	0:未定/ 1:GREP/ 2:置換

extern TStringList *ViewFileList;		//!< イメージビューアでのファイル名リスト
extern bool isViewIcon;					//!< イメージビューアでアイコンを表示中
extern bool isViewAGif;					//!< イメージビューアでアニメーションGIFを表示中
extern bool isViewClip;					//!< イメージビューアでクリップボードを表示中
extern bool isViewFTP;					//!< イメージビューアでFTPのファイルを表示中
extern bool rqThumbnail;				//!< クリップボード/FTP閲覧後のサムネイル復帰要求
extern bool nrmThumbnail;				//!< 通常画面時のサムネイル表示

extern TStringList *LaunchList;			//!< ランチャーリスト(アプリケーション一覧)

extern UnicodeString PathMask[MAX_FILELIST];	//!< パスマスク
extern UnicodeString DriveInf[MAX_FILELIST];	//!< ドライブ情報

extern TStringList *WorkList;			//!< ワークリスト
extern UnicodeString WorkListName;		//!< ワークリストのファイル名
extern TDateTime WorkListTime;			//!< ワークリストのタイムスタンプ
extern bool WorkListChanged;			//!< ワークリストの内容が変更された
extern bool WorkListFiltered;			//!< ワークリストにフィルタが適用されている
extern bool WorkListHasSep;				//!< ワークリストにセパレータがある
extern bool rqWorkListDirInf;			//!< ワークリストのディレクトリ情報更新を要求

extern TStringList *PlayList;			//!< プレイリスト
extern UnicodeString PlayListFile;		//!< プレイリストのファイル名
extern UnicodeString PlayFile;			//!< 再生中ファイル名
extern int  PlayStbIdx;
extern bool PlayRepeat;					//!< リピート再生
extern bool PlayShuffle;				//!< シャッフル再生
extern bool ListShuffled;				//!< シャッフルされた

extern int  IniPathMode[MAX_FILELIST];				//!< 起動時パスモード
extern UnicodeString InitialPath[MAX_FILELIST];		//!< 起動時パス
extern UnicodeString InitialMask[MAX_FILELIST];		//!< 起動時マスク
extern int  IniSortMode[MAX_FILELIST];				//!< 起動時ソート方法

extern int  IniWorkMode;				//!< ワークリスト 0:前回/ 1:指定
extern UnicodeString HomeWorkList;

extern TStringList *PopMenuList;		//!< ExeMenuFile コマンド用メニュー項目
extern TStringList *ToolBtnList;		//!< ツールボタン定義リスト(ファイラー)
extern TStringList *ToolBtnListV;		//!< ツールボタン定義リスト(テキストビューア)
extern TStringList *ToolBtnListI;		//!< ツールボタン定義リスト(イメージビューア)

extern int  IniWinMode;					//!< サイズモード 0:前回/ 1:指定
extern int  IniWinLeft, IniWinTop, IniWinWidth, IniWinHeight;
extern bool FixWinPos;					//!< ウィンドウサイズを固定
extern bool IniPathToTab1;				//!< 初期パスをタブ1に設定
extern bool IniTabHomeAll;				//!< 初期パス以外のタブをホームに戻す
extern bool ShowSplash;					//!< スプラッシュを表示

//---------------------------------------------------------------------------
/**
 * @defgroup OPTION_EVENT_CMDS オプション設定 - イベント
 * @brief イベント発生時に実行するコマンド
*/

/** @{ */
#define MAX_EVENT_CMD	66	//!< 最大イベント数

extern UnicodeString OnAppStart;
extern UnicodeString OnAppClose;
extern UnicodeString OnMaximized;
extern UnicodeString OnMinimized;
extern UnicodeString OnRestored;
extern UnicodeString OnCurChange;
extern UnicodeString OnTabChange;
extern UnicodeString OnNewDrive;
extern UnicodeString OnArcOpend;
extern UnicodeString OnArcClosed;
extern UnicodeString OnFindOpend;
extern UnicodeString OnFlCursor;
extern UnicodeString OnFlExDClick;
extern UnicodeString OnFlTbRClick;
extern UnicodeString OnTabDClick;
extern UnicodeString OnTabRClick;
extern UnicodeString OnFlRClick;
extern UnicodeString OnDragStart;
extern UnicodeString OnDragEnd;
extern UnicodeString OnGrepOpen;
extern UnicodeString OnGrepClosed;
extern UnicodeString OnWatchNotify;
extern UnicodeString OnFTPConnect;
extern UnicodeString OnFTPDiscon;
extern UnicodeString OnDirDClick;
extern UnicodeString OnDirRClick;
extern UnicodeString OnRelDClick;
extern UnicodeString OnRelRClick;
extern UnicodeString OnHdrRClick;
extern UnicodeString OnFScrRClick;
extern UnicodeString OnDrvDClick;
extern UnicodeString OnDrvRClick;
extern UnicodeString OnSplDClick;
extern UnicodeString OnSplRClick;
extern UnicodeString OnImgDClick;
extern UnicodeString OnTxtDClick;
extern UnicodeString OnFlIDClick;
extern UnicodeString OnTskDClick;
extern UnicodeString OnTskRClick;
extern UnicodeString OnLogDClick;
extern UnicodeString OnSttDClick;
extern UnicodeString OnSttRClick;
extern UnicodeString OnTimDClick;
extern UnicodeString OnTimRClick;
extern UnicodeString OnTvOpen;
extern UnicodeString OnTvOpened;
extern UnicodeString OnTvClose;
extern UnicodeString OnTvClosed;
extern UnicodeString OnTvTbRClick;
extern UnicodeString OnTvHRClick;
extern UnicodeString OnIvOpened;
extern UnicodeString OnIvClosed;
extern UnicodeString OnFullScr;
extern UnicodeString OnNormScr;
extern UnicodeString OnIvTbRClick;
extern UnicodeString OnIvImgDClick;
extern UnicodeString OnIvImgRClick;
extern UnicodeString OnIvMgnDClick;
extern UnicodeString OnThmDClick;
extern UnicodeString OnThmRClick;
extern UnicodeString OnIvIDClick;
extern UnicodeString OnIvSbRClick;
extern UnicodeString OnDragStartI;
extern UnicodeString OnDragEndI;
extern UnicodeString OnClipText;
extern UnicodeString OnUnlocked;

struct event_rec {
	UnicodeString *sp;	//!< 変数のポインタ
	const _TCHAR *key;	//!< キー名
	const _TCHAR *dsc;	//!< 説明
};

extern const event_rec EventCmdList[MAX_EVENT_CMD];	//!< イベントコマンドリスト

/** @} */

//---------------------------------------------------------------------------
#define MAX_TIMER_EVENT	2
#define MAX_TIMER_ALARM	6
extern bool Timer_Enabled[MAX_TIMER_EVENT], Timer_NopAct[MAX_TIMER_EVENT];
extern int  Timer_StartCnt[MAX_TIMER_EVENT], Timer_TimeCnt[MAX_TIMER_EVENT], Timer_NopCnt[MAX_TIMER_EVENT];
extern int  Timer_RepeatN[MAX_TIMER_EVENT], Timer_RepeatCnt[MAX_TIMER_EVENT];
extern TStringList  *Timer_AlarmList[MAX_TIMER_EVENT];
extern UnicodeString Timer_Condition[MAX_TIMER_EVENT];
extern UnicodeString OnTimerEvent[MAX_TIMER_EVENT];

//---------------------------------------------------------------------------
extern int  SortMode[MAX_FILELIST];			/**< ファイルリストのソート方法@n
											 * 0:名前/ 1:拡張子/ 2:更新日時/ 3:サイズ/ 4:属性/ 5:なし */
extern int  DirSortMode[MAX_FILELIST];		/**< ディレクトリのソート方法@n
											 * 0:ファイルと同じ/ 1:名前/ 2:更新日時/ 3:サイズ/ 4:属性/
											 * 5:ディレクトリを区別しない/ 6:フォルダアイコン */
extern int  SubSortMode[5];					//!< 第2ソートモード
extern int  PrimeSortMode;					//!< 第1ソートモード

extern bool FlOdrNatural[MAX_FILELIST];		//!< 自然順
extern bool FlOdrDscName[MAX_FILELIST];		//!< 降順
extern bool FlOdrSmall[MAX_FILELIST];		//!< 小さい順
extern bool FlOdrOld[MAX_FILELIST];			//!< 古い順
extern bool FlOdrDscAttr[MAX_FILELIST];		//!< 属性降順
extern bool FlOdrDscPath[MAX_FILELIST];		//!< 場所降順

extern bool NaturalOrder;					//!< 比較関数 - 自然順
extern bool DscNameOrder;					//!< 比較関数 - 名前降順
extern bool SmallOrder;						//!< 比較関数 - 小さい順
extern bool OldOrder;						//!< 比較関数 - 古い順
extern bool DscAttrOrder;					//!< 比較関数 - 属性降順
extern bool DscPathOrder;					//!< 比較関数 - 場所降順

extern bool TopSymbol;
extern bool SortBoth;						//!< 左右とも変更
extern bool SortLogical;					//!< 論理ソート(自然順ソート無効時)
extern UnicodeString SortSymList;
extern UnicodeString SortExtList;			//!< 拡張子順で優先する拡張子

extern TStringList *OptionList;				//!< オプション
extern TStringList *KeyFuncList;			//!< キー割り当て
extern TStringList *FKeyLabelList;			//!< ファンクションキー名
extern TStringList *HotKeyList;				//!< ホットキー
extern TStringList *DirStack;				//!< ディレクトリスタック
extern TStringList *PathMaskList;			//!< パスマスクリスト
extern TStringList *RegDirList;				//!< 登録ディレクトリ
extern TStringList *ProtectDirList;			//!< 削除制限ディレクトリ
extern TStringList *VirDriveList;			//!< 仮想ドライブリスト
extern TStringList *ColorList;				//!< 配色
extern TStringList *ExtColList;				//!< 拡張子別配色
extern TStringList *AssociateList;			//!< 関連付け
extern TStringList *OpenStdCmdList;			//!< OpenStandard のコマンド関連付け
extern TStringList *EtcEditorList;			//!< その他のエディタリスト
extern TStringList *ExtToolList;			//!< 外部ツール
extern TStringList *ExtMenuList;			//!< 追加メニュー
extern TStringList *CommandList;			//!< コマンドリスト
extern TStringList *CmdSetList;				//!< コマンド一覧リスト
extern TStringList *TaskCmdList;			//!< タスクコマンド名リスト
extern TStringList *DriveList;				//!< 変化監視用ドライブリスト
extern TStringList *NetDriveList;			//!< 現在有効なネットドライブリスト
extern TStringList *AllDirHistory;			//!< 全体のディレクトリ履歴
extern TStringList *TextViewHistory;		//!< テキスト閲覧履歴
extern TStringList *TextEditHistory;		//!< テキスト編集履歴
extern TStringList *WorkListHistory;		//!< ワークリスト履歴
extern TStringList *CopyPathHistory;		//!< コピーしたパス名の履歴
extern TStringList *InputDirHistory;		//!< ディレクトリ入力の履歴
extern TStringList *InputCmdsHistory;		//!< コマンド入力の履歴(ファイラー)
extern TStringList *InputCmdsHistoryV;		//!< コマンド入力の履歴(テキストビューア)
extern TStringList *InputCmdsHistoryI;		//!< コマンド入力の履歴(イメージビューア)
extern TStringList *IncSeaHistory;			//!< インクリメンタルサーチのキーワード履歴
extern TStringList *FilterHistory;			//!< フィルタのキーワード履歴
extern TStringList *WebSeaHistory;			//!< Web検索語の履歴
extern TStringList *LatLngHistory;			//!< 緯度経度検索の履歴
extern TStringList *HeadlineList;			//!< 見出しリスト (拡張子=正規表現パターン)
extern TStringList *ZoomRatioList;			//!< ズーム倍率リスト
extern TStringList *InterpolationList;		//!< 縮小・拡大アルゴリズムのリスト
extern TStringList *CnvCharList;			//!< 禁止文字／ユーザ定義文字変換リスト
extern TStringList *RenCmdFileList;			//!< 改名したコマンドファイルのリスト
extern TStringList *RenArcFileList;			//!< 改名したアーカイブファイルのリスト
extern TStringList *RedrawList;				//!< 描画抑止用リスト
extern TStringList *CmdRequestList;			//!< コマンド要求リスト
extern TStringList *CommandHistory;			//!< コマンド履歴

extern UnicodeString LogBufStr;				//!< タスクからのログ書込バッファ (LogRWLock で保護すること)
extern TMultiReadExclusiveWriteSynchronizer *LogRWLock;

extern TListBox     *LogWndListBox;			//!< ログウィンドウ用リストボックス
extern TStringList  *LogBufList;			//!< ログリストボックス(仮想)用バッファ
extern UsrScrollPanel *LogWndScrPanel;		//!< シンプルスクロールバー

extern int  LayoutMode;			//!< 画面レイアウトモード
extern bool DivFileListUD;		//!< ファイルリストを上下に分割
extern bool DivDirInfUD;		//!< ディレクトリ情報を上下に分割

extern TFont *ListFont;			//!< ファイルリスト等
extern TFont *FileInfFont;		//!< ファイル情報
extern TFont *TxtPrvFont;		//!< テキストプレビュー
extern TFont *LogFont;			//!< ログ
extern TFont *ViewerFont;		//!< テキストビューア
extern TFont *GrepResFont;		//!< GREP結果リスト
extern TFont *DirInfFont;		//!< ディレクトリ情報
extern TFont *DrvInfFont;		//!< ドライブ情報
extern TFont *LstHdrFont;		//!< 一覧のヘッダ
extern TFont *ViewHdrFont;		//!< ビューア情報ヘッダ
extern TFont *GenListFont;		//!< 一覧ダイアログ
extern TFont *HintFont;			//!< ヒント
extern TFont *SttBarFont;		//!< ステータスバー
extern TFont *CalcFont;			//!< 電卓
extern TFont *ToolBarFont;		//!< ツールバー
extern TFont *TabBarFont;		//!< タブバー
extern TFont *CharInfFont;		//!< 文字情報
extern TStringList *FontList;	//!< カラー

/** @defgroup GLOBAL_COLORS 配色 */
/** @{ */
/** @defgroup OPTION_COLORS オプション設定 */
/** @{ */
extern TColor col_bgList;		//!< 一覧の背景色
extern TColor col_bgList2;		//!< 一覧の背景色(交互)
extern TColor col_fgList;		//!< 一覧の文字色
extern TColor col_Splitter;		//!< 分割境界線
extern TColor col_bgArc;		//!< 仮想ディレクトリの背景色
extern TColor col_bgFind;		//!< 検索結果リストの背景色
extern TColor col_bgWork;		//!< ワークリストの背景色
extern TColor col_bgFTP;		//!< FTPリモート側の背景色
extern TColor col_bgADS;		//!< 代替データストリーム一覧の背景色
extern TColor col_selItem;		//!< 選択項目の背景色
extern TColor col_oppItem;		//!< 反対パス選択項目の背景色
extern TColor col_fgSelItem;	//!< 選択項目の文字色
extern TColor col_bgMark;		//!< 栞マーク項目の背景色
extern TColor col_matchItem;	//!< INC.サーチのマッチ項目背景色
extern TColor col_Differ;		//!< 結果リストの相違箇所背景色
extern TColor col_DifferN;		//!< 結果リストの注目箇所背景色
extern TColor col_Cursor;		//!< ラインカーソルの色
extern TColor col_bgScrBar;		//!< シンプルスクロールバーの背景色
extern TColor col_bgScrKnob;	//!< シンプルスクロールノブの色
extern TColor col_frScrKnob;	//!< シンプルスクロールノブの輪郭色
extern TColor col_bgActKnob;	//!< ドラッグ時のシンプルスクロールノブ色
extern TColor col_lnScrHit;		//!< シンプルスクロールバーのヒット行色
extern TColor col_lnScrSel;		//!< シンプルスクロールバーの選択行色
extern TColor col_Folder;		//!< ディレクトリの文字色
extern TColor col_SymLink;		//!< シンボリックリンク/ジャンクションの文字色
extern TColor col_Protect;		//!< 削除制限ディレクトリの文字色
extern TColor col_ReadOnly;		//!< 読み込み専用属性の文字色
extern TColor col_Compress;		//!< 圧縮属性の文字色
extern TColor col_Hidden;		//!< 隠し属性の文字色
extern TColor col_System;		//!< システム属性の文字色
extern TColor col_fgSpace;		//!< 空白記号の文字色
extern TColor col_fgTagNam;		//!< デフォルトのタグ色
extern TColor col_InvItem;		//!< 無効な項目の文字色
extern TColor col_bgTabBar;		//!< タブバーの背景色
extern TColor col_bgActTab;		//!< アクティブなタブの背景色
extern TColor col_bgInAcTab;	//!< 非アクティブなタブの背景色
extern TColor col_frmTab;		//!< タブの輪郭色
extern TColor col_fgTab;		//!< タブの文字色
extern TColor col_bgListHdr;	//!< リストヘッダの背景色
extern TColor col_fgListHdr;	//!< リストヘッダの文字色
extern TColor col_bgDirInf;		//!< ディレクトリ情報の背景色
extern TColor col_fgDirInf;		//!< ディレクトリ情報の文字色
extern TColor col_bgDirRel;		//!< ディレクトリ関係の背景色
extern TColor col_fgDirRel;		//!< ディレクトリ関係の文字色
extern TColor col_bdrDirB;		//!< ディレクトリ情報の下境界線
extern TColor col_bgDrvInf;		//!< ドライブ情報の背景色
extern TColor col_fgDrvInf;		//!< ドライブ情報の文字色
extern TColor col_bdrDrvT;		//!< ドライブ情報の上境界線
extern TColor col_bgInf;		//!< ファイル情報の背景色
extern TColor col_fgInf;		//!< ファイル情報の文字色
extern TColor col_fgInfNam;		//!< ファイル情報の項目名文字色
extern TColor col_fgInfEmp;		//!< ファイル情報の強調文字色
extern TColor col_bgTxtPrv;		//!< テキストプレビューの背景色
extern TColor col_fgTxtPrv;		//!< テキストプレビューの文字色
extern TColor col_bgLog;		//!< ログの背景色
extern TColor col_fgLog;		//!< ログの文字色
extern TColor col_bgTask;		//!< タスク状態表示の背景色
extern TColor col_fgPrgBar;		//!< タスク進捗バー色
extern TColor col_bgPrgBar;		//!< タスク進捗背景色
extern TColor col_Error;		//!< エラー/注意の文字色
extern TColor col_TlBorder;		//!< ツールウインドウの境界線

extern TColor col_bgView;		//!< テキストビューアの背景色
extern TColor col_fgView;		//!< テキストビューアの文字色
extern TColor col_Margin;		//!< テキストビューアの余白白
extern TColor col_bgRuler;		//!< ルーラの背景色
extern TColor col_fgRuler;		//!< ルーラの目盛色
extern TColor col_bgLineNo;		//!< 行番号背景色
extern TColor col_LineNo;		//!< 行番号文字色
extern TColor col_Mark;			//!< 行マーク
extern TColor col_bdrLine;		//!< 行番号の境界線
extern TColor col_bdrFold;		//!< 折り返し境界線
extern TColor col_bdrFixed;		//!< 固定長表示の縦罫線
extern TColor col_Indent;		//!< インデントガイド
extern TColor col_Indent2;		//!< インデントガイド(交互)
extern TColor col_Comment;		//!< コメントの文字色
extern TColor col_Strings;		//!< 文字列の文字色
extern TColor col_Reserved;		//!< 予約語の文字色
extern TColor col_Symbol;		//!< シンボルの文字色
extern TColor col_Numeric;		//!< 数値の文字色
extern TColor col_fgEmpBin1;	//!< バイナリ強調文字色1
extern TColor col_fgEmpBin2;	//!< バイナリ強調文字色2
extern TColor col_fgEmpBin3;	//!< バイナリ強調文字色3
extern TColor col_Headline;		//!< 見出しの文字色
extern TColor col_URL;			//!< URLの文字色
extern TColor col_LocalLink;	//!< ローカルファイルへのリンク
extern TColor col_bgImage;		//!< 画像の背景色
extern TColor col_bgDblPg;		//!< 見開き表示の余白色
extern TColor col_bgWMF;		//!< メタファイルの背景色
extern TColor col_bgTips;		//!< ツールチップの背景色
extern TColor col_fgTips;		//!< ツールチップの文字色
extern TColor col_bgHint;		//!< ヒント表示の背景色
extern TColor col_fgHint;		//!< ヒント表示の文字色
extern TColor col_bgWarn;		//!< 警告表示の背景色
extern TColor col_fgEmp;		//!< 強調文字色
extern TColor col_bgEmp;		//!< 強調背景色
extern TColor col_Ruby;			//!< ルビ
extern TColor col_TAB;			//!< タブ表示色
extern TColor col_CR;			//!< 改行表示色
extern TColor col_HR;			//!< 罫線の色
extern TColor col_Ctrl;			//!< コントロールコード
extern TColor col_fgPair;		//!< 対応する括弧の文字色

extern TColor col_bdrThumb;		//!< サムネイルの境界線
extern TColor col_ThumbExif;	//!< サムネイルのEixf情報
extern TColor col_ImgGrid;		//!< 画像分割グリッド
extern TColor col_OptFind;		//!< オプション設定の検索結果
extern TColor col_Tim1H;		//!< 1時間以内のタイムスタンプ色
extern TColor col_Tim3H;		//!< 3時間以内の～
extern TColor col_Tim6H;		//!< 6時間以内の～
extern TColor col_Tim1D;		//!< 1日以内の～
extern TColor col_Tim3D;		//!< 3日以内の～
extern TColor col_Tim7D;		//!< 7日以内の～
extern TColor col_Tim1M;		//!< 1ヶ月以内の～
extern TColor col_Tim3M;		//!< 3ヶ月以内の～
extern TColor col_Tim6M;		//!< 6ヶ月以内の～
extern TColor col_Tim1Y;		//!< 1年以内の～
extern TColor col_Tim3Y;		//!< 3年以内の～
extern TColor col_TimOld;		//!< それより前の～
extern TColor col_Size4G;		//!< 4GB以上
extern TColor col_Size2G;		//!< 2GB以上
extern TColor col_Size1G;		//!< 1GB以上
extern TColor col_Size512M;		//!< 512MB以上
extern TColor col_Size256M;		//!< 256MB以上
extern TColor col_Size128M;		//!< 128MB以上
extern TColor col_Size64M;		//!< 64MB以上
extern TColor col_Size32M;		//!< 32MB以上
extern TColor col_Size16M;		//!< 16MB以上
extern TColor col_Size1M;		//!< 1MB以上
extern TColor col_Size1K;		//!< 1KB以上
extern TColor col_SizeLT;		//!< 1KB未満
extern TColor col_Size0;		//!< 0

extern TColor col_GrBack;		//!< グラフの背景色
extern TColor col_GrLine;		//!< グラフのライン
extern TColor col_GrGrid;		//!< グラフのグリッド
extern TColor col_GrText;		//!< グラフの文字色

extern TColor col_GitHEAD;		//!< Gitビューア : ヘッド
extern TColor col_GitMark;		//!<   グラフマーク
extern TColor col_GitBra;		//!<   ブランチ
extern TColor col_GitBraR;		//!<   リモートブランチ
extern TColor col_GitTag;		//!<   タグ
extern TColor col_GitHash;		//!<   ハッシュ
extern TColor col_GitIns;		//!<   - 行
extern TColor col_GitDel;		//!<   + 行

extern TColor col_bgTlBar1;		//!< ツールバーのグラデーション開始色
extern TColor col_bgTlBar2;		//!< ツールバーのグラデーション終了色
extern TColor col_fgTlBar;		//!< ツールバーの文字色
extern TColor col_htTlBar;		//!< ツールバーのホットトラッキング色
extern TColor col_bgInfHdr;		//!< 情報ヘッダの背景色
extern TColor col_fgInfHdr;		//!< 情報ヘッダの文字色

extern TColor col_bgChInf;		//!< 文字情報サンプルの背景色
extern TColor col_fgChInf;		//!< 文字情報サンプルの文字色
extern TColor col_bgEdBox;		//!< Edit ボックスの背景色
extern TColor col_fgEdBox;		//!< Edit ボックスの文字色
/** @} */
/** @} */

extern UnicodeString BgImgName[MAX_BGIMAGE];		//!< 背景画像ファイル名
extern Graphics::TBitmap *BgImgBuff[MAX_BGIMAGE];	//!< 背景画像バッファ

extern int  BgImgMode;			//!< 背景画像表示モード
extern int  BgImgSubMode;
extern int  BgColAlpha;			//!< 背景色アルファ
extern bool BgImgGray;			//!< グレースケール化
extern bool BgImgHideScr;		//!< スクロール時に隠す
extern int  BgHideTime;			//!< 復帰時間
extern bool BgImgTileIf;		//!< 指定サイズ以下なら並べて表示
extern int  BgTileSize;

extern bool AlphaForm;			//!< メイン画面を透明に
extern int  AlphaValue;			//!< メイン画面アルファ

extern UnicodeString FontSampleTxt;		//!< フォントのサンプル表示文字列
extern UnicodeString FontSampleSym;		//!< フォントのサンプル表示シンボル
extern int FontSampleSize;				//!< 表示サイズ
extern TColor FontSampleFgCol;			//!< 文字色
extern TColor FontSampleBgCol;			//!< 背景色
extern TColor FontSampleGridCol;		//!< 基準線色
extern bool   FontSampleShowGrid;		//!< 基準線を表示

extern UnicodeString TextEditor;		//!< テキストエディタ
extern UnicodeString TextEditorFrmt;	//!< パラメータ(Grep用)
extern UnicodeString TextEditorFrmt2;	//!< パラメータ(ファラー用)

extern UnicodeString ImageEditor;		//!< イメージエディタ
extern UnicodeString FExtImgEidt;		//!< イメージエディタの対応拡張子
extern bool ImageEditSgl;				//!< イメージエディタをファイル毎に個別起動

extern UnicodeString FExtViewTab4;		//!< タブ4の拡張子
extern UnicodeString FExtViewTabX;		//!< 任意タブ幅の拡張子
extern int  ViewTabWidthX;				//!< 任意タブ幅

extern UnicodeString BinaryEditor;		//!< バイナリエディタ
extern UnicodeString SoundTaskFin;		//!< タスク終了時の通知音
extern UnicodeString SoundFindFin;		//!< 検索終了時の通知音
extern UnicodeString SoundWarning;		//!< 警告音
extern UnicodeString SoundWatch;		//!< ファイル監視

extern int  FlashCntWarning;			//!< 警告の点滅回数
extern int  FlashTimeWarning;			//!< 警告の点滅間隔
extern int  FlashCntTaskfin;			//!< タスク終了時の点滅回数
extern int  FlashTimeTaskfin;			//!< タスク終了時の点滅間隔

extern int  MaxLogLines;				//!< ログの最大行数
extern int  MsgHintTime;				//!< ヒントの表示時間
extern int  KeyHintTime;				//!< 2ストロークヒントの待機時間
extern int  NotifyTaskTime;				//!< ～秒以上かかったタスクの終了時に鳴らす
extern int  CmpDelOwCnt;				//!< 完全削除の上書き回数
extern int  ViewTxtInterLn;				//!< ビューアの行間
extern int  ViewLeftMargin;				//!< ビューアの左余白
extern int  ViewFoldWidth;				//!< 折り返し幅(半角単位)
extern bool ViewFoldFitWin;				//!< 折り返しをウィンドウ幅に合わせる
extern bool TvCursorVisible;			//!< ビューアでカーソルを常に可視領域に
extern bool LimitBinCsr;				//!< バイナリ表示でカーソル移動を制限
extern bool TxtColorHint;				//!< カーソル位置数値のカラーをヒント表示
extern bool AltBackSlash;				//!< \ を ＼(U+2216)で表示
extern bool FormatJson;					//!< .json ファイルを整形
extern bool DecodeDfmStr;				//!< .dfm ファイルの文字列をデコード
extern bool BinMemMaped;				//!< バイナリではメモリマップドファイルとして開く
extern int  ViewFixedLimit;				//!< 固定長表示の最大幅
extern int  ViewTxtLimitSize;			//!< テキストの最大読込サイズ
extern int  ViewBinLimitSize;			//!< バイナリの最大読込(or マップ)サイズ
extern int  ListWheelScrLn;				//!< ホイールによるスクロール行数(リスト)
extern int  ViewWheelScrLn;				//!< ホイールによるスクロール行数(ビューア)
extern int  PlaySndLimitTime;			//!< サウンド再生タイム制限
extern bool ShowTextPreview;			//!< テキストプレビューを表示
extern int  PrvTxtInfLn;				//!< テキストプレビューの行数
extern bool ShowTailPreview;			//!< 末尾プレビューを表示
extern int  PrvTxtTailLn;				//!< 末尾プレビュー行数
extern int  PrvActTailLn;				//!< 末尾プレビューを有効にする行数
extern int  WatchInterval;				//!< ディレクトリ監視間隔
extern int  InfPrvWait;					//!< 情報取得/プレビューの遅延
extern int  LogInterval;				//!< ログの更新間隔
extern int  ListInterLn;				//!< ファイルリストの行間
extern int  CursorWidth;				//!< カーソル線の幅
extern int  CursorAlpha;				//!< カーソル行背景アルファ
extern int  CellAlpha;					//!< セルの背景アルファ
extern int  SplitterWidth;				//!< 境界線の幅
extern int  SplitterWidth2;
extern int  FExtMaxWidth;				//!< 拡張子の最大文字数
extern int  SizeFormatMode;
extern int  SizeDecDigits;				//!< サイズ表示における小数点以下の桁数
extern int  ListPercent;				//!< ファイルリスト幅の比率
extern int  ImgFrameMargin;				//!< フィット表示時の余白幅
extern int  ImgFitMaxZoom;				//!< フィット表示時の許容倍率
extern int  ImgGridHorzN;				//!< グリッドの横分割数
extern int  ImgGridVertN;				//!< グリッドの縦分割数
extern int  MinShowTime;				//!< 最小表示タイム
extern int  ThumbnailSize;				//!< サムネイルのサイズ
extern int  ThumbBdrWidth;				//!< サムネイルの境界線幅
extern int  ThumbScaleOpt;				//!< サムネイルの縮小アルゴリズム
extern int  ThumbnailPos;				//!< サムネイルの表示位置
extern int  ImgDblMargin;				//!< 見開き間隔

extern bool ShowImgSidebar;				//!< サイドバーを表示
extern bool ImgSidebarIsLeft;			//!< サイドバーは左

extern bool HasCallHotkey;				//!< 呼び出しホットキーがあるか？

extern bool HideSizeTime;				//!< サイズと更新日時を隠す

//---------------------------------------------------------------------------
/** @addtogroup FILELIST */
/** @{ */

/**
 * @brief ファイルリスト項目
 */
struct file_rec {
	UnicodeString f_name;		//!< パス付ファイル名
	UnicodeString p_name;		//!< パス名
	UnicodeString n_name;		//!< パス無ファイル名
	UnicodeString b_name;		//!< ファイル名主部
	UnicodeString f_ext;		//!< 拡張子
	UnicodeString attr_str;		//!< 属性文字列
	UnicodeString alias;		//!< エイリアス
	UnicodeString arc_name;		//!< アーカイブ名
	UnicodeString tmp_name;		//!< 一時解凍名
	UnicodeString r_name;		//!< 表示名
	UnicodeString l_name;		//!< リンク先
	UnicodeString tags;			//!< タグ
	UnicodeString hash;			//!< ハッシュ/ 画像ハッシュ(類似性ソート)
	UnicodeString vctr;			//!< 画像:ベクトル(類似性ソート)
	UnicodeString memo;			//!< 栞マーク一覧:   メモ(内容 \t 設定日時)@n
								//!< リポジトリ一覧: 情報(コミット \t 状態)

	int  tag;					//!< 0: 左/ 1: 右
	bool is_up;					//!< ..
	bool is_dir;				//!< ディレクトリ
	bool is_sym;				//!< リパースポイント
	bool is_jct;				//!< ジャンクション
	bool is_virtual;			//!< 仮想ディレクトリ内のファイル
	bool is_ftp;				//!< FTP
	bool is_ads;				//!< 代替データストリーム
	bool is_dummy;				//!< ダミー(空のドライブ、ワークリストのセパレータ、比較結果の不在項目など)
	bool selected;				//!< 選択中
	bool failed;				//!< ファイラー: 一時解凍失敗/  イメージビューア: 読込失敗

	__int64 f_size;				//!< サイズ
	__int64 o_size;				//!< ディスク上の占有サイズ
	__int64 c_size;				//!< 圧縮サイズ

	int  f_attr;				//!< 属性
	TDateTime f_time;			//!< タイムスタンプ
	int  f_count;				//!< ファイル数
	int  d_count;				//!< ディレクトリ数
	int  img_ori;				//!< 画像方向
	int  distance;				//!< 編集距離ソート値
	bool is_video;				//!< 動画

	int  base_end_x;			//!< ファイル名主部の末尾位置(描画時に設定、マウス選択で利用)
	bool matched;				//!< インクリメンタルでマッチ

	TStringList *inf_list;		//!< 情報リスト
	UnicodeString prv_text;		//!< テキストプレビュー
	UnicodeString tail_text;	//!< テキストプレビュー(末尾)
	int  code_page;				//!< コードページ
};

//---------------------------------------------------------------------------
/**
 * @brief ファイルリストの状態
 */
struct flist_stt {
	UnicodeString vol_name;		//!< ボリューム名
	__int64 drive_Used;			//!< ドライブ使用容量
	__int64 drive_Free;			//!< ドライブ空き容量
	__int64 drive_Total;		//!< ドライブ全体容量
	__int64 cur_total;			//!< カレントの合計サイズ
	__int64 occ_total;			//!< カレントの占有サイズ
	__int64 cmp_total;			//!< カレントの圧縮サイズ
	int clu_size;				//!< クラスタサイズ

	int f_cnt;					//!< ファイル数
	int d_cnt;					//!< ディレクトリ数
	int f_cnt_total;
	int d_cnt_total;
	int sel_f_cnt;				//!< 選択ファイル数
	int sel_d_cnt;				//!< 選択ディレクトリ数
	__int64 sel_size;			//!< 選択サイズ

	int last_fl_idx;			//!< ファイルリストに復帰したときのカーソル位置

	bool show_f_d_cnt;			//!< ファイル、ディレクトリ数を表示
	bool dir_graph;				//!< ディレクトリ容量をグラフ表示(対カレント)
	bool dsk_graph;				//!< ディレクトリ容量をグラフ表示(対ドライブ)
	bool sub_counted;			//!< サブディレクトリ内をすべてカウント済み

	int lwd_half;				//!< "X" の幅
	int lwd_fext_max;			//!< ".WWWWWWWWWWWW" の幅
	int lwd_fext;				//!< 拡張子の表示幅
	int lwd_size;				//!< サイズの表示幅
	int lwd_time;				//!< タイムスタンプの表示幅
	int lwd_path;				//!< 場所の表示幅(検索リスト)

	int lxp_fext;				//!< 拡張子の表示位置
	int lxp_size;				//!< サイズの表示位置
	int lxp_time;				//!< タイムスタンプの表示位置
	int lxp_path;				//!< 場所の表示位置
	int lxp_right;				//!< 左端位置

	TColor color_bgDirInf;		//!< .NyanFi による個別色
	TColor color_fgDirInf;
	TColor color_bgDrvInf;
	TColor color_fgDrvInf;
	TColor color_Cursor;
	TColor color_selItem;

	bool is_TabFixed;			//!< タブ変更に対してパス固定

	bool git_checked;			//!< [..]でGit情報を取得した

	bool is_Work;				//!< ワークリスト
	bool is_FTP;				//!< FTPリモート側

	bool is_Arc;				//!< 仮想ディレクトリ
	UnicodeString arc_DspPath;	//!< アーカイブの表示パス
	UnicodeString arc_SubPath;	//!< アーカイブ以下のサブディレクトリ
	UnicodeString arc_Name;		//!< アーカイブファイル名(temp)
	TStringList  *arc_RetList;	//!< 多重アーカイブ用の戻りリスト
	TStringList  *arc_TmpList;	//!< 一時解凍ディレクトリリスト

	bool is_ADS;				//!< 代替データストリーム
	UnicodeString ads_Name;		//!< メインストリームのファイル名

	UnicodeString LibraryInfo;	//!< ライブラリファイル名 \t パス
	UnicodeString LibSubPath;

	bool is_Find;				//!< 検索結果リスト
	bool is_narrow;				//!< 絞り込み
	bool find_Loaded;			//!< ファイルから読み込んだリスト
	bool find_UseSet;			//!< 検索設定ファイルを使用
	int  find_SortMode;			//!< 検索設定ファイルによるソートモード設定

	bool find_Dir;				//!< ディレクトリ検索
	bool find_Both;				//!< ファイル・ディレクトリ検索
	bool find_SubDir;			//!< サブディレクトリも検索
	bool find_Arc;				//!< アーカイブ内も検索
	bool find_xTrash;			//!< ごみ箱内は検索しない

	bool find_MARK;				//!< マーク検索
	bool find_TAG;				//!< タグ検索
	bool find_TAG_all;			//!< すべてのタグにマッチ
	bool find_DICON;			//!< フォルダアイコン検索
	bool find_DUPL;				//!< 重複ファイルの検索
	bool find_HLINK;			//!< ハードリンク列挙

	bool find_RegEx;			//!< 正規表現
	bool find_And;				//!< AND検索
	bool find_Case;				//!< 大小文字区別

	bool find_Warn;				//!< 好ましくないファイル名
	bool find_hasAds;			//!< 代替データストリームを持つ
	bool find_useProc;			//!< 別プロセスが使用中

	bool find_ResLink;			//!< 結果リストから反対側へ反映
	bool find_DirLink;			//!< ディレクトリ名を反映
	bool find_PathSort;			//!< 場所順でソート

	UnicodeString find_Path;	//!< 検索パス
	UnicodeString find_DirList;	//!< 検索ディレクトリ・リスト
	UnicodeString find_SkipDir;	//!< 除外ディレクトリ(;区切り)
	UnicodeString find_Name;	//!< 検索名(ハードリンク用)
	UnicodeString find_Mask;	//!< マスク
	UnicodeString find_Keywd;	//!< キーワード
	UnicodeString find_Tags;	//!< タグ
	UnicodeString find_Icons;	//!< フォルダアイコン(改行区切り)

	TStringList  *find_SubList;	//!< 選択サブディレクトリ

	int  find_DT_mode;			//!< 日付条件
	TDateTime find_DT_value;
	UnicodeString find_DT_str;
	int  find_DT_rel;			//!< 相対指定値

	int  find_SZ_mode;			//!< サイズ条件
	__int64 find_SZ_value;
	int  find_CT_mode;			//!< 内容条件
	int  find_AT_mode;			//!< 属性条件
	int  find_AT_value;

	int  find_TM_mode;			//!< タイム
	TTime find_TM_value;

	int  find_codepage;			//!< コードページ
	UnicodeString find_LineBrk;	//!< 改行コード
	int  find_BOM_mode;			//!< BOM

	int  find_RT_mode;			//!< レイト
	int  find_RT_value;
	int  find_FS_mode;			//!< フレーム率
	int  find_FS_value;
	int  find_FW_mode;			//!< フレーム幅
	int  find_FW_value;
	int  find_FH_mode;			//!< フレーム高
	int  find_FH_value;

	int  find_IW_mode;			//!< 画像サイズ
	unsigned int find_IW_value;
	int  find_IH_mode;
	unsigned int find_IH_value;
	bool find_IWH_max;

	int  find_SR_mode;			//!< サンプリングレート
	int  find_SR_value;
	int  find_BT_mode;			//!< ビット
	int  find_CH_mode;			//!< チャンネル

	int  find_IC_mode;			//!< アイコン
	int  find_IC_value;

	int  find_HL_mode;			//!< リンクカウント数
	int  find_HL_value;

	UnicodeString find_PrpKwd;
	bool find_PrpRegEx;
	bool find_PrpAnd;
	bool find_PrpCase;

	UnicodeString find_TxtKwd;
	bool find_TxtRegEx;
	bool find_TxtAnd;
	bool find_TxtCase;

	UnicodeString find_ExifKwd;
	bool find_ExifRegEx;
	bool find_ExifAnd;
	bool find_ExifCase;

	UnicodeString find_LatLng;
	double find_GpsLat;
	double find_GpsLng;
	int    find_GpsRange;

	bool is_IncSea;				//!< インクリメンタルサーチ中
	bool is_Migemo;				//!< Migemoモード
	bool is_Filter;				//!< フィルタモード
	bool is_Fuzzy;				//!< あいまいモード
	bool filter_csns;			//!< フィルタで大小文字を区別

	UnicodeString incsea_Word;
	UnicodeString incsea_Ptn;
};

extern flist_stt ListStt[MAX_FILELIST];
extern flist_stt *CurStt;
extern flist_stt *OppStt;
/** @} */

//---------------------------------------------------------------------------
//ドライブ情報
//---------------------------------------------------------------------------
/**
 * @brief ドライブ情報
 */
struct drive_info {
	UnicodeString drive_str;
	bool		  accessible;
	bool		  ejectable;
	bool		  is_virtual;
	int			  drv_type;
	UnicodeString type_str;		//!< 種類
	UnicodeString volume;		//!< ボリューム名
	UnicodeString unc;			//!< ネットワークドライブのUNCパス
	UnicodeString mnt_dir;		//!< 仮想ドライブのマウントパス
	UnicodeString f_system;		//!< ファイルシステム
	UnicodeString bus_type;		//!< 接続I/F
	UnicodeString label;		//!< 表示用ラベル
	bool		  is_NTFS;
	bool		  is_SSD;
	bool		  is_RAM;
	TIcon		  *small_ico;
	TIcon		  *large_ico;
};

//---------------------------------------------------------------------------
/**
 * @brief タブ情報
 */
struct tab_info {
	TRect rc;	//描画領域
	TStringList *sel_list[MAX_FILELIST];	//!< 選択状態
	TStringList *dir_hist[MAX_FILELIST];	//!< ディレクトリ履歴
	int			 dir_hist_p[MAX_FILELIST];	//!< 履歴位置
	int			 sort_mode[MAX_FILELIST];	//!< ソートモード
	bool		 sync_lr;					//!< 階層同期
};

//---------------------------------------------------------------------------
//コマンドファイルリスト
//---------------------------------------------------------------------------
struct cmdf_rec {
	TDateTime   f_time;				//!< タイムスタンプ
	TStringList *file_buf;			//!< ファイル内容
	TStringList *cmd_list;			//!< コマンドリスト
	int exe_count;					//!< 実行回数
	bool noreload;					//!< 再読み込みしない
};
extern TStringList *CmdFileList;	//!< コマンドファイルのリスト
extern TStringList *XCMD_VarList;	//!< 変数リスト

//---------------------------------------------------------------------------
inline void InvalidateFileList(int tag = CurListTag)
{
	FileListBox[tag]->Invalidate();
}

//---------------------------------------------------------------------------
/** @brief VCLスタイルを使用しているか？ */
inline bool use_VclStyle()
{
	return !SameText(TStyleManager::ActiveStyle->Name, "Windows");
}

//---------------------------------------------------------------------------
inline TColor get_ListBgCol()
{
	return (col_bgList==col_None)? TStyleManager::ActiveStyle->GetSystemColor(clWindow) : col_bgList;
}
inline TColor get_ListFgCol()
{
	return (col_fgList==col_None)? TStyleManager::ActiveStyle->GetSystemColor(clWindowText) : col_fgList;
}
inline TColor get_AltBgCol(int idx)
{
	return (col_bgList2!=col_None && idx%2==1)? col_bgList2 : get_ListBgCol();
}
//---------------------------------------------------------------------------
inline TColor get_ViewBgCol()
{
	return (col_bgView==col_None)? TStyleManager::ActiveStyle->GetSystemColor(clWindow) : col_bgView;
}
inline TColor get_ViewFgCol()
{
	return (col_bgView==col_None)? TStyleManager::ActiveStyle->GetSystemColor(clWindowText) : col_fgView;
}
//---------------------------------------------------------------------------
inline TColor get_TxtPrvBgCol()
{
	return (col_bgTxtPrv==col_None)? TStyleManager::ActiveStyle->GetSystemColor(clWindow) : col_bgTxtPrv;
}
inline TColor get_TxtPrvFgCol()
{
	return (col_fgTxtPrv==col_None)? TStyleManager::ActiveStyle->GetSystemColor(clWindowText) : col_fgTxtPrv;
}
//---------------------------------------------------------------------------
inline TColor get_InfBgCol()
{
	return (col_bgInf==col_None)? TStyleManager::ActiveStyle->GetSystemColor(clWindow) : col_bgInf;
}
inline TColor get_InfFgCol()
{
	return (col_fgInf==col_None)? TStyleManager::ActiveStyle->GetSystemColor(clWindowText) : col_fgInf;
}
//---------------------------------------------------------------------------
inline TColor get_LogBgCol()
{
	return (col_bgLog==col_None)? TStyleManager::ActiveStyle->GetSystemColor(clWindow) : col_bgLog;
}
inline TColor get_LogFgCol()
{
	return (col_fgLog==col_None)? TStyleManager::ActiveStyle->GetSystemColor(clWindowText) : col_fgLog;
}
inline TColor get_TaskBgCol()
{
	return (col_bgTask==col_None)? TStyleManager::ActiveStyle->GetSystemColor(clWindow) : col_bgTask;
}
//---------------------------------------------------------------------------
inline TColor get_ActTabBgCol()
{
	return (col_bgActTab==col_None)? TStyleManager::ActiveStyle->GetSystemColor(clBtnFace) : col_bgActTab;
}
inline TColor get_InAcTabBgCol()
{
	return (col_bgInAcTab==col_None)?
		AdjustColor(TStyleManager::ActiveStyle->GetSystemColor(clBtnFace), ADJCOL_BGBIT) : col_bgInAcTab;
}
inline TColor get_TabFgCol()
{
	return (col_fgTab==col_None)? TStyleManager::ActiveStyle->GetSystemColor(clBtnText) : col_fgTab;
}
inline TColor get_TabFrmCol()
{
	return (col_frmTab==col_None)? TStyleManager::ActiveStyle->GetSystemColor(clBtnShadow): col_frmTab;
}
inline TColor get_TabBarBgCol()
{
	return (col_bgTabBar==col_None)? TStyleManager::ActiveStyle->GetSystemColor(clBtnFace) : col_bgTabBar;
}
//---------------------------------------------------------------------------
inline TColor get_ListHdrBgCol()
{
	return (col_bgListHdr==col_None)? TStyleManager::ActiveStyle->GetSystemColor(clBtnFace) : col_bgListHdr;
}
inline TColor get_ListHdrFgCol()
{
	return (col_fgListHdr==col_None)? TStyleManager::ActiveStyle->GetSystemColor(clBtnText) : col_fgListHdr;
}
//---------------------------------------------------------------------------
inline TColor get_InfHdrBgCol()
{
	return (col_bgInfHdr==col_None)? TStyleManager::ActiveStyle->GetSystemColor(clBtnFace) : col_bgInfHdr;
}
inline TColor get_InfHdrFgCol()
{
	return (col_fgInfHdr==col_None)? TStyleManager::ActiveStyle->GetSystemColor(clBtnText) : col_fgInfHdr;
}
//---------------------------------------------------------------------------
inline TColor get_DirInfBgCol()
{
	return ((col_bgDirInf==col_None)? TStyleManager::ActiveStyle->GetSystemColor(clBtnFace) : col_bgDirInf);
}
inline TColor get_DirInfFgCol()
{
	return ((col_fgDirInf==col_None)? TStyleManager::ActiveStyle->GetSystemColor(clBtnText) : col_fgDirInf);
}
//---------------------------------------------------------------------------
inline TColor get_DirRelBgCol()
{
	return ((col_bgDirRel==col_None)?
				AdjustColor(TStyleManager::ActiveStyle->GetSystemColor(clBtnFace), ADJCOL_BGBIT) : col_bgDirRel);
}
inline TColor get_DirRelFgCol()
{
	return ((col_fgDirRel==col_None)? TStyleManager::ActiveStyle->GetSystemColor(clBtnText) : col_fgDirRel);
}
//---------------------------------------------------------------------------
inline TColor get_DrvInfBgCol()
{
	return ((col_bgDrvInf==col_None)?
				AdjustColor(TStyleManager::ActiveStyle->GetSystemColor(clBtnFace), ADJCOL_BGBIT) : col_bgDrvInf);
}
inline TColor get_DrvInfFgCol()
{
	return ((col_fgDrvInf==col_None)? TStyleManager::ActiveStyle->GetSystemColor(clBtnText) : col_fgDrvInf);
}
//---------------------------------------------------------------------------
inline TColor get_SplitterCol()
{
	return (col_Splitter==col_None)? TStyleManager::ActiveStyle->GetSystemColor(clBtnFace) : col_Splitter;
}

//---------------------------------------------------------------------------
inline bool is_SelFgCol(TOwnerDrawState stt)
{
	return (stt.Contains(odSelected) && col_fgSelItem!=col_None);
}
inline bool is_SelFgCol(TGridDrawState stt)
{
	return (stt.Contains(gdSelected) && col_fgSelItem!=col_None);
}
inline bool is_SelFgCol(bool sel)
{
	return (sel && col_fgSelItem!=col_None);
}

//---------------------------------------------------------------------------
inline TColor GetActiveCol(TColor col)
{
	return ((InactiveGray && (!Application->Active || !Application->MainForm->Active))?
											AdjustColor(GrayCol(col), InactiveAdjust) : col);
}

//---------------------------------------------------------------------------
inline UnicodeString get_FExtMaxStr(int n = 0)
{
	return ("." + StringOfChar(_T('W'), (n>0)? n : FExtMaxWidth));
}

inline UnicodeString get_SearchStr(UnicodeString s, SearchOption opt)
{
	return (opt.Contains(soCSV)? get_csv_item(s, 0) : (opt.Contains(soTree) || opt.Contains(soTSV))? get_pre_tab(s) : s);
}

inline bool is_SearchMatch(UnicodeString s, UnicodeString ptn, SearchOption opt)
{
	TRegExOptions x_opt;
	if (!opt.Contains(soCaseSens)) x_opt << roIgnoreCase;

	return (opt.Contains(soMigemo)? TRegEx::IsMatch(s, ptn, x_opt) :
		  opt.Contains(soCaseSens)? ContainsStr(s, ptn) : ContainsText(s, ptn));
}

//---------------------------------------------------------------------------
//ソートモード
inline int CurSortMode()
{
	return (CurStt->is_Find && CurStt->find_PathSort)? 6 : SortMode[CurListTag];
}

inline int TagSortMode(int tag)
{
	return (ListStt[tag].is_Find && ListStt[tag].find_PathSort)? 6 : SortMode[tag];
}

//---------------------------------------------------------------------------
int __fastcall CompLogical(UnicodeString s0, UnicodeString s1, bool natural_sw);
int __fastcall CompNameFN(UnicodeString s0, UnicodeString s1);
int __fastcall CompNameLN(UnicodeString s0, UnicodeString s1);

int __fastcall CompDirName(file_rec *fp0, file_rec *fp1);
int __fastcall CompDirTime(file_rec *fp0, file_rec *fp1);
int __fastcall CompDirSize(file_rec *fp0, file_rec *fp1);
int __fastcall CompDirAttr(file_rec *fp0, file_rec *fp1);
int __fastcall CompDirIcon(file_rec *fp0, file_rec *fp1);

int __fastcall SortComp_Name(TStringList *List, int Index1, int Index2);
int __fastcall SortComp_Ext( TStringList *List, int Index1, int Index2);
int __fastcall SortComp_Time(TStringList *List, int Index1, int Index2);
int __fastcall SortComp_Size(TStringList *List, int Index1, int Index2);
int __fastcall SortComp_Attr(TStringList *List, int Index1, int Index2);
int __fastcall SortComp_DirOnly(TStringList *List, int Index1, int Index2);
int __fastcall SortComp_PathName(TStringList *List, int Index1, int Index2);
int __fastcall SortComp_Tags(TStringList *List, int Index1, int Index2);
int __fastcall SortComp_Memo(TStringList *List, int Index1, int Index2);
int __fastcall SortComp_MarkTime(TStringList *List, int Index1, int Index2);
int __fastcall SortComp_Distance(TStringList *List, int Index1, int Index2);
int __fastcall SortComp_GitStt(TStringList *List, int Index1, int Index2);

int __fastcall Comp_PathTree(TStringList *List, int Index1, int Index2);

int __fastcall KeyComp_Key(TStringList *List, int Index1, int Index2);
int __fastcall KeyComp_Cmd(TStringList *List, int Index1, int Index2);
int __fastcall KeyComp_Dsc(TStringList *List, int Index1, int Index2);

//---------------------------------------------------------------------------
UnicodeString yen_to_delimiter(UnicodeString s);
UnicodeString alt_yen_to(UnicodeString s);
UnicodeString get_MiniPathName(UnicodeString pnam, int max_w, TFont *font, bool rep_delimiter = true);

int get_EtcEditorFiles(TStringList *lst);
int get_ExtToolFiles(TStringList *lst);

UnicodeString get_dotNaynfi(UnicodeString dnam = EmptyStr);
UnicodeString get_dotNaynfi(UnicodeString dnam, bool inherit, bool force = false);

bool is_NewerTime(TDateTime scr_t, TDateTime dst_t);

bool check_if_unc(UnicodeString pnam);

bool load_NyanFiDef(UnicodeString fnam, TStringList *lst);
bool save_NyanFiDef(UnicodeString fnam, TStringList *lst);
UnicodeString read_NyanFiDef(UnicodeString fnam, UnicodeString key);
bool write_NyanFiDef(UnicodeString fnam, UnicodeString key, UnicodeString v);

UnicodeString get_cmdfile(UnicodeString s);
UnicodeString get_cmds_prm_file(UnicodeString prm);

UnicodeString make_ResponseFile(TStringList *lst, int arc_t, UnicodeString *files = NULL, bool excl = false);
UnicodeString make_ResponseFile(UnicodeString fnam, int arc_t);

UnicodeString format_CloneName(UnicodeString fmt, UnicodeString fnam, UnicodeString dst_dir, bool is_dir = false,
	TDateTime *ts = NULL, TStringList *lst = NULL);

UnicodeString format_FileName(UnicodeString fmt, UnicodeString fnam, UnicodeString *al_str = NULL);

TStringList *CreStringList(int obj_type = 0);

UnicodeString get_SrcHdrName(UnicodeString fnam);
UnicodeString get_NextSameName(UnicodeString fnam, bool only_text = false);
UnicodeString get_NextSameName(TStringList *lst, int idx, bool only_text = false);

void get_LibraryList(UnicodeString fnam, TStringList *lst, bool get_info = false);
UnicodeString get_LibFile_if_root();

UnicodeString get_SyncDirList(UnicodeString dnam, TStringList *lst, bool del_sw = false, bool syn_sw = true);
bool has_SyncDir(UnicodeString dnam, bool del_sw = false);
UnicodeString is_SyncDir(UnicodeString dnam1, UnicodeString dnam2);

void SetTempPathA(UnicodeString dnam);
void ClearTempDir(UnicodeString dnam = EmptyStr);
void ClearTempArc(UnicodeString dnam = EmptyStr);
void ClearTempArcList(int tag);

UnicodeString UpdateTempArcList(int tag = -1);
bool SetTmpFile(file_rec *fp, bool not_unpk = false, bool show_prg = false);
UnicodeString ExtractInZipImg(UnicodeString arc_file, UnicodeString img_fext);

void add_PackItem(file_rec *fp, int arc_t, UnicodeString src_dir, TStringList *lst);

bool is_InvalidUnc(UnicodeString dnam, bool del_sw = false);
UnicodeString CheckAvailablePath(UnicodeString dnam, int tag, bool prvnt_unc = false);

TStringList *GetCurBtnList(int scr_mode = ScrMode);

/** @addtogroup FILELIST */
/** @{ */

/**
 * @brief ファイルリストを取得
 * @param tag
 * @return TStringList*
 */
TStringList* GetFileList(int tag);

/**
 * @brief カレントのリストを取得
 * @param only_filer ファイラーのみを対象
 * @return TStringList*
 */
TStringList* GetCurList(bool only_filer = false);

/**
 * @brief 反対側のリストを取得
 * @return TStringList*
 */
TStringList* GetOppList();

/**
 * @brief 選択有り?
 * @param lst 対象リスト
 * @return true
 * @return false
 */
bool ListSelected(TStringList *lst);

/**
 * @brief 選択中の項目数を取得
 * @param lst 対象リスト
 * @return int 選択中の項目数
 */
int GetSelCount(TStringList *lst);

/**
 * @brief 選択中項目名リストを取得
 * @param lst 対象リスト
 * @param[out] sel_lst 選択項目リスト
 * @param with_path パス付きで取得
 * @param with_obj Objects も取得
 */
void GetSelList(TStringList *lst, TStringList *sel_lst, bool with_path = true, bool with_obj = false);

/**
 * @brief 選択状態を解除
 * @param lst 対象リスト
 */
void ClrSelect(TStringList *lst = NULL);

/**
 * @brief マッチ項目数を取得
 * @param lst 対象リスト
 * @return int マッチ項目数
 */
int  GetMatchCount(TStringList *lst);

/**
 * @brief ファイルリストのソート
 * @param lst 対象リスト
 * @param tag
 */
void SortList(TStringList *lst, int tag = CurListTag);

/**
 * @brief ファイルリストで項目を見つける
 * @param fnam ファイル名
 * @param tag
 * @param top_idx 先頭インデックス
 * @return int インデックス(見つからない場合は -1)
 */
int  IndexOfFileList(UnicodeString fnam, int tag = CurListTag, int top_idx = -1);

file_rec* ExistsInList(UnicodeString fnam, TStringList *lst);

UnicodeString GetSelFileStr(TStringList *lst, bool use_tmp = false, bool inc_dir = false, TStringList *s_lst = NULL);

/**
 * @brief file_rec を作成して初期化
 * @details file_rec を作成して初期化します。copy_fp を指定すると、その内容がコピーされます。
 * @param copy_fp
 * @return file_rec*
 */
file_rec* cre_new_file_rec(file_rec *copy_fp = NULL);

/**
 * @brief ファイル名から file_rec を作成
 * @param fnam ファイル名(末尾が \ の場合はディレクトリ名)
 * @param tag
 * @param force 存在しない場合も強制的に設定
 * @return file_rec*
 */
file_rec* cre_new_file_rec(UnicodeString fnam, int tag = -1, bool force = false);

/**
 * @brief [..]の file_rec を作成
 * @param tag
 * @return file_rec*
 */
file_rec* cre_new_up_rec(int tag);

/**
 * @brief file_rec のコピー
 * @param s_fp コピー元
 * @param d_fp コピー先
 */
void copy_file_rec(file_rec *s_fp, file_rec *d_fp);

/**
 * @brief file_rec の削除
 * @param fp 削除対象
 */
void del_file_rec(file_rec *fp);

void inv_file_rec(file_rec *fp);

/**
 * @brief 項目は選択可能か？
 * @param fp 対象項目
 * @return true
 * @return false
 */
bool is_selectable(file_rec *fp);

/**
 * @brief 選択可能な項目の選択状態を設定
 * @param fp 対象項目
 * @param sw 選択
 * @return true
 * @return false
 */
bool set_select(file_rec *fp, bool sw = true);

/**
 * @brief 選択可能な項目の選択状態を反転
 * @param fp 対象項目
 * @return true
 * @return false
 */
bool set_select_r(file_rec *fp);

/**
 * @brief ファイルリストのクリア
 * @param lst 対象リスト
 */
void clear_FileList(TStringList *lst);

/**
 * @brief ファイルリストの項目削除
 * @param lst 対象リスト
 * @param idx 削除インデックス
 */
void del_FileListItem(TStringList *lst, int idx);

/**
 * @brief ファイルリストの内容を入れ替える
 * @param lst1 リスト1
 * @param lst2 リスト2
 * @param swap_tag タグも入れ替える
 */
void swap_FileList(TStringList *lst1, TStringList *lst2, bool swap_tag = true);
/** @} */

tab_info* cre_tab_info(bool sync_lr = false);
int  add_TabList(UnicodeString item);
void insert_TabList(int idx, UnicodeString item);
void del_tab_info(tab_info *tp);
tab_info *get_TabInfo(int tab_idx = -1);
TStringList *get_DirHistory(int tab_idx = -1, int tag = CurListTag);
int  *get_DirHistPtr(int tab_idx = -1, int tag = CurListTag);
void clear_DirHistory(int tab_idx = -1, int tag = CurListTag);
UnicodeString get_TabWorkList(int tab_idx);
void save_DirHistory(UsrIniFile *ini_file);
bool save_TagGroup(UnicodeString fnam);

/**
 * @brief 検索設定のクリア
 * @param lst_stt
 */
void clear_FindStt(flist_stt *lst_stt);

/**
 * @brief 検索設定の保存
 * @param fnam ファイル名
 * @param lst_stt
 * @return true
 * @return false
 */
bool save_FindSettings(UnicodeString fnam, flist_stt *lst_stt);

/**
 * @brief 検索設定の読込
 * @param fnam ファイル名
 * @param lst_stt
 * @return true
 * @return false
 */
bool load_FindSettings(UnicodeString fnam, flist_stt *lst_stt);

/**
 * @brief 検索設定情報の取得
 * @param fnam ファイル名
 * @param[out] lst 情報リスト
 */
void get_FindSetInf(UnicodeString fnam, TStringList *lst);

/**
 * @brief 検索対象が全体か？
 * @param lst_stt
 * @return true
 * @return false
 */
bool is_FindAll(flist_stt *lst_stt);

/**
 * @brief 検索リスト情報文字列を取得
 * @param pnam_sw パス名などを付加
 * @return UnicodeString
 */
UnicodeString get_FindInfStr(bool pnam_sw);

bool check_int(int v0, int v1, int mode);
bool check_prop(UnicodeString fnam, UnicodeString prop, int v, int mode);

/**
 * @brief 標準ファイル検索
 * @attention 不正な正規表現パターンを用いないこと(要事前チェック)
 * @param fnam パス無しファイル名
 * @param f_tm タイムスタンプ
 * @param f_sz サイズ
 * @param f_atr 属性
 * @param lst_stt
 * @return true マッチ
 * @return false
 */
bool check_file_std(UnicodeString fnam, TDateTime f_tm, __int64 f_sz, int f_atr, flist_stt *lst_stt);

/**
 * @brief 拡張ファイル検索
 * @param fnam パス無しファイル名
 * @param lst_stt
 * @return true マッチ
 * @return false
 */
bool check_file_ex(UnicodeString fnam, flist_stt *lst_stt);

/**
 * @brief フォント情報を取得
 * @param fnam ファイル名
 * @param[out] lst 情報リスト
 * @return UnicodeString フォント名
 */
UnicodeString get_FontInf(UnicodeString fnam, TStringList *lst = NULL);

drive_info *get_DriveInfoList();
drive_info *get_DriveInfo(UnicodeString dstr);
void update_DriveInfo();
bool is_NTFS_Drive(UnicodeString dnam);
UnicodeString get_VolumeInfo(UnicodeString dnam, UnicodeString *fsys = NULL);

UnicodeString mount_VirDriveList(int idx);
UnicodeString get_VirMountDir(UnicodeString drv);
UnicodeString cv_VirToOrgName(UnicodeString fnam);
bool is_ExePath(UnicodeString pnam);

void get_DriveLogList(UnicodeString dstr, TStringList *lst, double &r_min, double &r_max);
void update_DriveLog(bool save = false);

bool save_RenLog(TStringList *lst);

void set_ListBoxItemHi(TListBox      *lp, TFont *font = NULL, bool with_ico = false);
void set_ListBoxItemHi(TCheckListBox *lp, TFont *font = NULL, bool with_ico = false);

void set_StdListBox(TListBox      *lp, int tag = 0, TFont *font = NULL, bool with_ico = false);
void set_StdListBox(TCheckListBox *lp, int tag = 0, TFont *font = NULL, bool with_ico = false);

void setup_ToolBar(TToolBar *tb, bool upd_sw = false);
void setup_Panel(TPanel *sb, TFont *font = NULL);

void set_UsrScrPanel(UsrScrollPanel *sp);
void set_FextWidth(file_rec *fp, int tag);

void assign_FileListBox(TListBox *lp, TStringList *lst, int idx = -1, UsrScrollPanel *sp = NULL);
void update_FileListBox(TStrings *lst, int tag, int idx = -1);
void update_FileListBoxT(TStrings *lst, int tag);

bool get_Files_objSize(UnicodeString pnam, TStrings *lst, bool exc_sym);
bool get_NameList_objSize(TStringList *lst, TStringList *o_lst, bool sub_sw, bool exc_sym);

/**
 * @brief 特殊ディレクトリのリストを取得
 * @param id
 * @param[out] o_lst リスト
 * @return true
 * @return false
 */
bool get_SpecialDirList(UnicodeString id, TStringList *o_lst = NULL);

void get_FindListF(UnicodeString pnam, flist_stt *lst_stt, TStrings *lst, int tag);
void get_FindListD(UnicodeString pnam, flist_stt *lst_stt, TStrings *lst, int tag);

/**
 * @brief すべてのサブディレクトリを取得
 * @param pnam 基準ディレクトリ
 * @param[out] lst ディレクトリ名リスト
 * @param stt_bar 経過表示用ステータスバー
 * @param stt_idx 表示パネルのインデックス
 * @param proc_msg メッセージキューを処理
 */
void get_SubDirs(UnicodeString pnam, TStrings *lst, TStatusBar *stt_bar = NULL, int stt_idx = 0, bool proc_msg = false);

int  get_HardLinkList(UnicodeString fnam, TStringList *o_lst);
UnicodeString get_ReparsePointTarget(UnicodeString pnam, bool &is_jct, bool force = false);

__int64 get_DirSize(UnicodeString dnam, int *f_cnt, int *d_cnt, __int64 *o_size, __int64 *c_size);
__int64 get_ArcDirSize(UnicodeString anam, UnicodeString dnam, int *f_cnt, int *d_cnt);

void  del_CachedIcon(UnicodeString fnam);
void  clr_all_CachedIcon();

HICON get_file_SmallIcon(UnicodeString fnam);
HICON get_fext_SmallIcon(UnicodeString fext = EmptyStr);
HICON get_folder_icon(UnicodeString dnam = EmptyStr);

bool draw_SmallIcon(file_rec *fp, TCanvas *cv, int x, int y, bool force_cache = false, TControl *cp = NULL);
bool draw_SmallIconF(UnicodeString fnam, TCanvas *cv, int x, int y, TControl *cp = NULL);
bool draw_SmallIcon2(UnicodeString fnam, TCanvas *cv, int x, int y, TControl *cp = NULL);
int  add_IconImage(UnicodeString fnam, TImageList *lst);
int  add_IconImage(UnicodeString fnam, TVirtualImageList *lst);

UnicodeString get_file_from_cmd(UnicodeString s);
void SetExtNameToCtrl(UnicodeString fnam, TWinControl *cp, bool nbt_sw = false);

bool load_MenuFile(UnicodeString fnam, TStringList *lst);

bool load_WorkList(UnicodeString wnam);
bool save_WorkList(UnicodeString wnam, TStringList *lst = NULL);

bool load_FontSample(UnicodeString fnam);
bool save_FontSample(UnicodeString fnam);

int  find_NextIncSea(TStringList *lst, int idx);
int  find_PrevIncSea(TStringList *lst, int idx);
int  find_NextIniSea(TStringList *lst, int idx, UnicodeString keywd = EmptyStr, bool circular = true);

int  to_NextFile(TStringList *lst, int idx);
int  to_PrevFile(TStringList *lst, int idx);
int  to_NextSelItem(TStringList *lst, int idx);
int  to_PrevSelItem(TStringList *lst, int idx);

/**
 * @brief ViewFileList で有効な項目数を取得
 * @return int
 */
int  get_ViewCount();

bool make_NrmImage(UnicodeString fnam, Graphics::TBitmap *c_bmp, Graphics::TBitmap *g_bmp, int wd, int hi, bool cc_sw);
UnicodeString make_HsvVector(Graphics::TBitmap *i_bmp);
UnicodeString make_HistVector(Graphics::TBitmap *i_bmp);
UnicodeString make_dHash(Graphics::TBitmap *i_bmp);
UnicodeString make_aHash(Graphics::TBitmap *i_bmp);
UnicodeString make_pHash(Graphics::TBitmap *i_bmp);
int eval_HsvVector(UnicodeString r_vct, UnicodeString o_vct);
int eval_HistgramVector(UnicodeString r_vct, UnicodeString o_vct);
int get_HammingDistance(UnicodeString vct0, UnicodeString vct1);

/**
 * @brief ファイルの削除
 * @param fnam ファイル名
 * @param use_trash ごみ箱を使用
 * @return true 成功
 * @return false
 */
bool delete_File(UnicodeString fnam, bool use_trash = false);

void delete_FileIf(UnicodeString fnam);

bool delete_DirEx(UnicodeString pnam, bool use_trash = false, bool force = false);

/**
 * @brief ファイルの移動(タグ/フォルダアイコンを考慮)
 * @param old_nam 移動元のファイル名
 * @param new_nam 移動先のファイル名
 * @return true 成功
 * @return false
 */
bool move_FileT(UnicodeString old_nam, UnicodeString new_nam);

/**
 * @brief フォルダアイコンの移動
 * @param old_dnam
 * @param new_dnam
 */
void move_FolderIcon(UnicodeString old_dnam, UnicodeString new_dnam);

/**
 * @brief フォルダアイコンのコピー
 * @param src_dnam
 * @param dst_dnam
 */
void copy_FolderIcon(UnicodeString src_dnam, UnicodeString dst_dnam);

/**
 * @brief フォルダアイコンファイルの取得
 * @param dnam
 * @return UnicodeString
 */
UnicodeString get_FolderIconName(UnicodeString dnam);

/**
 * @brief フォルダアイコンの設定
 * @param dnam ディレクトリ名
 * @param inam アイコンファイル名 (EmptyStr: 解除)
 */
void set_FolderIcon(UnicodeString dnam, UnicodeString inam = EmptyStr);

/**
 * @brief フォルダアイコン一覧を取得
 * @param[out] lst リスト
 */
void get_FolderIconList(TStringList *lst);

/**
 * @brief フォルダアイコンの改名
 * @param old_nam
 * @param new_nam
 */
void rename_FolderIcon(UnicodeString old_nam, UnicodeString new_nam);

/**
 * @brief 存在しないフォルダアイコン設定を整理
 */
void chk_FolderIcon();

/**
 * @brief 拡張子に関連付けされているアプリのリストを取得
 * @param fext 拡張子
 * @return TStringDynArray
 */
TStringDynArray get_AssociatedApps(UnicodeString fext);

/**
 * @brief 関連付けリストからメニュー用リストを作成
 * @param[in] app_lst 関連付けリスト
 * @param[out] lst メニュー用リスト
 */
void make_AssoMenuList(TStringDynArray app_lst, TStringList *lst);

/** @addtogroup GLOBAL_COLORS */
/** @{ */
/**
 * @brief ファイルリスト項目の背景色を取得
 * @param lst_stt
 * @param idx インデックス
 * @return TColor
 */
TColor get_FlBgColor(flist_stt *lst_stt, int idx = 0);

/**
 * @brief ファイル名の文字色を取得
 * @param fp
 * @param col_x
 * @return TColor
 */
TColor get_FileColor(file_rec *fp, TColor col_x);

/**
 * @brief 拡張子別カラーを取得
 * @param fext 拡張子
 * @param col デフォルト文字色
 * @return TColor
 */
TColor get_ExtColor(UnicodeString fext, TColor col = col_fgList);

/**
 * @brief タイムスタンプの文字色を取得
 * @param dt タイムスタンプ
 * @param col_def デフォルト文字色
 * @return TColor
 */
TColor get_TimeColor(TDateTime dt, TColor col_def);

/**
 * @brief サイズの文字色を取得
 * @param size サイズ
 * @param col_def デフォルト文字色
 * @return TColor
 */
TColor get_SizeColor(__int64 size, TColor col_def);

/**
 * @brief ログの文字色を取得
 * @param s 文字列
 * @return TColor
 */
TColor get_LogColor(UnicodeString s);
/** @} */

UnicodeString get_DirNwlName(UnicodeString pnam);
UnicodeString get_DispName(file_rec *fp);
UnicodeString get_RegDirName(UnicodeString pnam);
UnicodeString UNC_to_NetDriveName(UnicodeString pnam);
UnicodeString NetDriveName_to_UNC(UnicodeString pnam);
UnicodeString VirtualDrive_to_Actual(UnicodeString pnam);
UnicodeString get_RegDirItem(int idx, UnicodeString *unam = NULL);
UnicodeString get_RegDirItem(WideChar key, UnicodeString *unam = NULL);
void move_top_RegDirItem(int idx);
UnicodeString get_LRUD_str(int tag = CurListTag, bool both = false);

/**
 * @brief 削除制限されたディレクトリか？
 * @param dnam 
 * @return true 
 * @return false 
 */
bool is_ProtectDir(UnicodeString dnam);

/**
 * @brief ファイル情報リストを取得
 * @param fp 取得対象
 * @param force 強制的に取得
 */
void GetFileInfList(file_rec *fp, bool force = false);

/**
 * @brief 指定したファイル情報の値文字列を取得
 * @param fp 取得対象
 * @param tit タイトル
 * @param dlmt 値の区切り文字
 * @return UnicodeString 
 */
UnicodeString get_FileInfValue(file_rec *fp, UnicodeString tit, UnicodeString dlmt = EmptyStr);

void assign_InfListBox(TListBox *lp, TStringList *i_lst, UsrScrollPanel *sp = NULL);
void draw_InfListBox(TListBox *lp, TRect &Rect, int Index, TOwnerDrawState State);
void draw_ColorListBox(TListBox *lp, TRect &Rect, int Index, TOwnerDrawState State, TStringList *col_lst);

void draw_InputPaintBox(TPaintBox *pp, UnicodeString s);

/**
 * @brief タイムスタンプの表示文字列を取得
 * @param dt 
 * @return UnicodeString 
 */
UnicodeString get_TimeStampStr(TDateTime dt);

UnicodeString get_FileSizeStr(__int64 sz, bool trim = false);
UnicodeString get_FileSizeStrF(__int64 sz);
UnicodeString get_FileInfStr(file_rec *fp, bool with_atr = true);
UnicodeString get_FileInfStr(UnicodeString fnam, bool with_atr = true);
void get_FileNamePathInf(UnicodeString fnam, TStringList *lst, bool get_app = false);

/**
 * @brief ファイル情報リストを取得
 * @param fp 取得対象
 * @param[out] lst 情報リスト
 * @return true
 * @return false
 */
bool get_FileInfList(file_rec *fp, TStringList *lst);

/**
 * @brief ファイルが処理中か？
 * @param fp 対象
 * @param[out] err_msg エラーメッセージ
 * @return true
 * @return false
 */
bool is_Processing(file_rec *fp, UnicodeString *err_msg = NULL);

/**
 * @brief ファイルが処理中か？
 * @param fnam ファイル名
 * @param is_video 動画(書込もチェック)
 * @param[out] err_msg エラーメッセージ
 * @return true
 * @return false
 */
bool is_Processing(UnicodeString fnam, bool is_video = false, UnicodeString *err_msg = NULL);

/**
 * @brief 取得が抑止されているパスか？
 * @param pnam パス名
 * @param no_path 取得しないパスのリスト(環境変数、%ExePath% 対応)
 * @return true
 * @return false
 */
bool is_NoInfPath(UnicodeString pnam, UnicodeString no_path);

/**
 * @brief ストリームの改行コードを取得
 * @param ms メモリストリーム
 * @param code_page コードページ
 * @param strict 完全チェック
 * @return UnicodeString
 */
UnicodeString get_StreamLineBreak(TStream *ms, int code_page, bool strict = false);

/**
 * @brief ファイルのコードページを取得
 * @param fnam ファイル名
 * @param[out] line_brk 改行
 * @param[out] has_bom BOM有り
 * @return int コードページ (0: 不明)
 */
int get_FileCodePage(UnicodeString fnam, UnicodeString *line_brk = NULL, bool *has_bom = NULL);

/**
 * @brief ファイルはテキストか？
 * @param fnam ファイル名
 * @param[out] code_page コードページ
 * @param[out] line_brk 改行
 * @param[out] has_bom BOM有り
 * @return true
 * @return false
 */
bool is_TextFile(UnicodeString fnam, int *code_page = NULL, UnicodeString *line_brk = NULL, bool *has_bom = NULL);

/**
 * @brief 文字列リストの行数、コメント、空白行をカウント
 * @param lst 文字列リスト
 * @param fnam ファイル名
 * @param[out] rem_cnt コメント行数
 * @param[out] blk_cnt 空白行数
 * @return int 総行数
 */
int CountListLines(TStringList *lst, UnicodeString fnam, int *rem_cnt, int *blk_cnt);

/**
 * @brief INIファイルのタイプ文字列を取得
 * @param fp 対象
 * @return UnicodeString タイプ文字列
 */
UnicodeString get_IniTypeStr(file_rec *fp);

/**
 * @brief 検索設定ファイルか？
 * @param fp 対象
 * @return true
 * @return false
 */
bool is_FindSet(file_rec *fp);

/**
 * @brief メニューファイルか？
 * @param fp 対象
 * @return true
 * @return false
 */
bool is_MenuFile(file_rec *fp);

/**
 * @brief 結果リストファイルか？
 * @param fp 対象
 * @return true
 * @return false
 */
bool is_ResultList(file_rec *fp);

bool is_AudioVideo(UnicodeString fnam);		//!< ビデオ/オーディオ・ファイルか？
bool is_MPEG2_TS(UnicodeString fnam);		//!< MPEG-2 TS ファイルか？
bool is_SoundID(UnicodeString s);			//!< サウンド識別子か？
bool is_ViewableFext(UnicodeString fext);	//!< ビューアで表示可能か(アイコンは除く)？
bool is_Viewable(file_rec *fp);
bool is_ExtractIcon(file_rec *fp);			//!< アイコン抽出可能か？
bool test_ArcExt(UnicodeString fext);		//!< アーカイバの対応拡張子か？
bool is_AvailableArc(UnicodeString fnam, bool ex_sw = false);	//!< 利用可能なアーカイブか？

bool test_TxtFile(UnicodeString fnam);		//!< テキストファイルか？
bool test_NonTxtExt(UnicodeString fext);	//!< 非テキストの拡張子か？

UnicodeString get_img_fext();				//!< 画像の拡張子を取得

/**
 * @brief 拡張子別ファイル数情報を追加
 * @param f_lst ファイル名リスト
 * @param[out] lst 情報リスト
 */
void add_FExtInfList(TStringList *f_lst, TStringList *lst);

/**
 * @brief ファイルから画像サイズを取得
 * @param fnam ファイル名
 * @param[out] wd 幅
 * @param[out] hi 高さ
 * @return true 成功
 * @return false
 */
bool get_img_size(UnicodeString fnam, unsigned int *wd, unsigned int *hi);

/**
 * @brief 画像ファイルを読み込む
 * @param fnam ファイル名
 * @param[out] o_bmp ビットマップ
 * @param img_type
 * @param trans_bg 透過背景色
 * @return int
 */
int  load_ImageFile(UnicodeString fnam, Graphics::TBitmap *o_bmp, int img_type = WICIMG_PREVIEW, TColor trans_bg = col_None);

/**
 * @brief サムネイルキャッシュを取得
 * @param fnam ファイル名
 * @param[out] o_bmp ビットマップ
 * @return UnicodeString ファイル名 [TAB] 表示情報
 */
UnicodeString load_ImageThumbCache(UnicodeString fnam, Graphics::TBitmap *o_bmp);

/**
 * @brief グローバル変数などの初期化
 */
void InitializeGlobal();

/**
 * @brief 後片付け
 */
void EndGlobal();

/**
 * @brief OSバージョン情報を取得
 * @return UnicodeString 
 */
UnicodeString get_OsVerInfStr();

/** @brief タイマー設定の更新 */
void SetupTimer();

/** @brief 無操作状態の解除 */
void ClearNopStt();

/** @brief オプション設定の読み込み */
void LoadOptions();

/** @brief オプション設定の保存 */
void SaveOptions();

/** @brief INIファイルを更新 */
void UpdateIniFile(UsrIniFile *ini_file);

void BringOptionByTag(TForm *fp);
int  GetOptionIntDef(int tag);
void ApplyOptionByTag(TComponent *cp);
void ApplyOptionByTag(TForm *fp);
void ApplyOptionByTag(TTabSheet *sp);
void ApplyOptionByTag(TPanel *pp);

void SetToolWinBorder(TForm *fp, bool sw = true, TColor col = col_TlBorder);

/** @brief 一覧用グリッドの初期化 */
void InitializeListGrid(TStringGrid *gp, TFont *font = NULL);

/** @brief 一覧用ヘッダの初期化 */
void InitializeListHeader(THeaderControl *hp, const _TCHAR *hdr, TFont *font = NULL);

void set_ComboBox_AutoComp(TForm *frm);
void set_MigemoCheckBox(TCheckBox *cp, const _TCHAR *key, UnicodeString sct = EmptyStr);
void set_MigemoAction(TAction *ap, const _TCHAR *key, UnicodeString sct = EmptyStr);
void change_ComboBoxHistory(TComboBox *cp, const _TCHAR *nrm_sct, const _TCHAR *reg_sct, bool reg_sw);

/**
 * @brief リストの絞り込み
 * @param i_lst 対象リスト
 * @param[out] o_lst 結果リスト 
 * @param kwd 検索語
 * @param opt 検索オプション
 */
void filter_List(TStringList *i_lst, TStringList *o_lst, UnicodeString kwd, SearchOption opt);

/** @brief キーに割り当てられているファイラー・コマンドを取得 */
UnicodeString Key_to_CmdF(UnicodeString key);

/** @brief キーに割り当てられているテキストビューア・コマンドを取得 */
UnicodeString Key_to_CmdV(UnicodeString key);

bool is_ToLeftOpe(UnicodeString keystr, UnicodeString cmdstr);
bool is_ToRightOpe(UnicodeString keystr, UnicodeString cmdstr);

/**
 * @brief コマンドに対する説明文字列を取得
 * @param cmd コマンド
 * @param only_inf 説明のみ取得
 * @param menu_list 追加メニュー
 * @param tool_list 外部ツール
 * @param is_TV テキストビューア・コマンド
 * @return UnicodeString 
 */
UnicodeString get_CmdDesc(UnicodeString cmd, bool only_inf = false,
	TStrings *menu_list = NULL, TStrings *tool_list = NULL, bool is_TV = false);

/** @brief 禁止文字／ユーザ定義文字の変換 */
UnicodeString ApplyCnvCharList(UnicodeString s);

TColor read_ColorList(UnicodeString key, TColor def, TStringList *lst = NULL);
TColor read_ColorList(const _TCHAR *key, TColor def, TStringList *lst = NULL);
void set_col_from_ColorList();

/** @brief 編集履歴を追加 */
void add_TextEditHistory(UnicodeString fnam);

/** @brief 呼び出しホットキーの登録 */
bool register_HotKey(int id, UnicodeString kstr);

void set_FormTitle(TForm *frm, const _TCHAR *s);

/** @brief 警告音 */
void beep_Warn(UnicodeString fnam = EmptyStr);

/** @brief タイトルバーの点滅 */
void flash_win(int cnt = 0, int tm = 0);

/** @brief 音量ミュート */
bool mute_Volume(UnicodeString prm);

/** @brief サウンド再生 */
bool play_sound(UnicodeString fnam);
bool play_sound_id(UnicodeString id);
bool play_sound_ex(UnicodeString fnam, bool limit = true);

bool add_PlayFile(UnicodeString fnam);
bool add_PlayList(UnicodeString lnam);
bool play_PlayList(bool prev = false, bool inh_shfl = false);
bool is_ListPlaying();

void set_CloseButton(bool enabled);

/**
 * @brief タブを考慮して文字列幅を取得
 * @param s 対象文字列
 * @param cv キャンバス
 * @param tab_wd タブストップ幅
 * @return int 
 */
int  get_TabTextWidth(UnicodeString s, TCanvas *cv, int tab_wd);

void out_Text(TCanvas *cv, int x, int y, const _TCHAR *s);
void out_Text(TCanvas *cv, int x, int y, const _TCHAR *s, TColor fg);
void out_TextEx(TCanvas *cv, int &x, int y, UnicodeString s, TColor fg = col_None, TColor bg = col_None, int mgn = 0);
void out_TextRect(TCanvas *cv, TRect &rc, UnicodeString s, TColor fg = col_None, TColor bg = col_None);

/**
 * @brief 文字列に対するマッチ語のリストを取得
 * @param lbuf 対象文字列
 * @param kwd 検索語
 * @param opt オプション
 * @param[out] lst マッチ語リスト
 * @return int マッチ数 
 */
int get_MatchWordList(UnicodeString lbuf, UnicodeString kwd, SearchOption opt, TStringList *lst);

int get_MatchWordListEx(UnicodeString lbuf, UnicodeString kwd, SearchOption opt, TStringList *lst,
							int s_idx = 0, int s_len = 0);

void EmphasisTextOut(UnicodeString s, TStringList *kw_lst, TCanvas *cv, int &x, int y, bool case_sns = false);

enum TxtOutOpt {toNormal, toCaseSens, toOnlyTop, toCompBgCol, toIsDfm, toTrimLeft};
typedef Set <TxtOutOpt, toNormal, toTrimLeft> TxtOutOption;

void EmphasisTextOutEx(UnicodeString s, TStringList *kw_lst, TCanvas *cv, int &x, int y, TxtOutOption opt,
	TColor fg = col_fgEmp, TColor bg = col_bgEmp);
void EmphasisTextOutEx(UnicodeString s, UnicodeString kwd, TCanvas *cv, int &x, int y, TxtOutOption opt,
	TColor fg = col_fgEmp, TColor bg = col_bgEmp);

void draw_TAB(TCanvas *cv, int x, int y, int w, int h);
void draw_CR(TCanvas *cv, int x, int y, int w, int h);
void draw_Caret(TCanvas *cv, int x, int y);

void TabCrTextOut(UnicodeString s, TCanvas *cv, int &x, int y, TColor fg = col_fgList, int max_x = 0);
void RuledLnTextOut(UnicodeString s, TCanvas *cv, TRect &rc, TColor fg, int tab_wd = 8,
	TStringList *kw_lst = NULL, bool case_sns = false);

void PrvTextOut(TListBox *lp, int idx, TCanvas *cv, TRect &rc, TColor fg,
	int tab_wd, TStringList *kw_lst = NULL, bool case_sns = false, UnicodeString fnam = EmptyStr, bool en_mlt = true);

void LineNoOut(TCanvas *cv, TRect &rc, UnicodeString l_str);
void LineNoOut(TCanvas *cv, TRect &rc, int l_no);

void PathNameOut(UnicodeString s, TStringList *kw_lst, bool case_sns, TCanvas *cv, int &x, int y, bool mgn_sw = true);
void PathNameOut(UnicodeString s, TCanvas *cv, int &x, int y, int max_w = 0);
void FileNameOut(TCanvas *cv, TRect &rc, UnicodeString fnam, bool use_fgsel,
	bool to_slash = false, TStringList *kw_lst = NULL, bool case_sns = false);

void RloPipeTextOut(UnicodeString s, TCanvas *cv, int &x, int y, TColor fg);
void SpaceTextOut(UnicodeString s, TCanvas *cv, int &x, int y, TColor fg, bool force_nrm = false);

void Emphasis_RLO_info(UnicodeString fnam, TCanvas *cv, int xp, int yp);

//---------------------------------------------------------------------------
#define UBMK_UP		1
#define UBMK_DOWN	2
#define UBMK_BUP	3
#define UBMK_BDOWN	4
#define UBMK_VUP	5
#define UBMK_VDOWN	6
#define UBMK_VTOP	7
#define UBMK_VEND	8
#define UBMK_HTOP	9
#define UBMK_HEND	10
#define UBMK_LEFT	11
#define UBMK_RIGHT	12

void draw_SortMark(TCanvas *cv, int x, int y, bool is_asc, TColor fg = Graphics::clNone);
void draw_SortHeader(THeaderControl *hp, THeaderSection *sp, TRect rc, int mk_mode = 0, bool use_syscol = false);
void draw_ScaledLine(TCanvas *cv, UnicodeString cmds);
void set_ButtonMark(TSpeedButton *bp, int id, TColor fg, TColor bg);
void set_BtnMarkStyle(TSpeedButton *bp, int id);
void set_BtnTextStyle(TSpeedButton *bp, UnicodeString s);

void draw_OwnerTab(TCustomTabControl *Control, int idx, const TRect rc, bool active);
void draw_MenuSeparator(TCanvas *cv, TRect rc);
void draw_ListCursor(TListBox *lp, TRect &Rect, int Index, TOwnerDrawState State);
void draw_ListCursor2(TListBox *lp, TRect &Rect, int Index, TOwnerDrawState State);
void draw_GridCursor(TStringGrid *gp, TRect &Rect, int ARow, TGridDrawState State);
void draw_ImgGrid(TCanvas *cv, Graphics::TBitmap *bmp);
void draw_BarGraph(TCanvas *cv, TRect rc, double r);
void draw_ProgressBar(TCanvas *cv, TRect rc, double r);

bool saveto_TextUTF8(UnicodeString fnam, TStrings *lst);
bool saveto_TextUTF8(UnicodeString fnam, UnicodeString s);
bool saveto_TextFile(UnicodeString fnam, TStrings *lst, TEncoding *enc = NULL);
bool saveto_TextFile(UnicodeString fnam, TStrings *lst, int enc_idx);

int  load_text_ex(UnicodeString fnam, TStringList *f_buf, int code_page = 0, int limit_size = 0,
	bool force_txt = false, UnicodeString *line_brk = NULL, bool *has_bom = NULL, double *ave_lsz = NULL);

int  load_text_tail(UnicodeString fnam, TStringList *f_buf, int code_page = 0, int limit_ln = 100,
	bool reverse = false, UnicodeString *line_brk = NULL);
bool check_text_tail(UnicodeString fnam, int &code_page, int size, UnicodeString kwd, TStringList *lst);

void get_xml_inf(UnicodeString fnam, TStringList *lst);

UnicodeString get_autorun_ico(UnicodeString fnam);

bool divide_FileName_LineNo(UnicodeString &fnam, int &lno, UnicodeString rnam, int pos = 0);
UnicodeString get_tags_file(UnicodeString rnam);
int  get_FileNameByTag(UnicodeString tnam, UnicodeString &rnam, TStringList *lst, UnicodeString onam = EmptyStr);

/** @brief テキストエディタで開く */
bool open_by_TextEditor(UnicodeString fnam, int lno = 0);

void ini_HtmConv_def(HtmConv *htmcnv, UnicodeString fnam = EmptyStr, UnicodeString url = EmptyStr);

/**
 * @brief 指定ファイルを実行/開く
 * @param cmd 実行ファイル/フォルダ名/CLSId など
 * @param prm パラメータ
 * @param wdir 作業ディレクトリ
 * @param opt オプション
 * @param[out] exit_code 終了コード
 * @param[out] o_lst 出力リスト
 * @return true 
 * @return false 
 */
bool Execute_ex(UnicodeString cmd, UnicodeString prm = EmptyStr, UnicodeString wdir = EmptyStr,
		UnicodeString opt = EmptyStr, DWORD *exit_code = NULL, TStringList *o_lst = NULL);

/**
 * @brief コマンドラインを実行
 * @param cmdln コマンドライン
 * @param wdir 作業ディレクトリ
 * @param opt オプション
 * @param[out] exit_code 終了コード
 * @param[out] o_lst 出力リスト
 * @param[out] o_ms 出力イメージ 
 * @param rq_abort 中断要求
 * @return true 
 * @return false 
 */
bool Execute_cmdln(UnicodeString cmdln, UnicodeString wdir = EmptyStr,
		UnicodeString opt = EmptyStr, DWORD *exit_code = NULL, TStringList *o_lst = NULL, TMemoryStream *o_ms = NULL,
			bool *rq_abort = NULL);

/**
 * @brief 一般ユーザに降格して実行
 * @param cmd コマンド
 * @param prm パラメータ
 * @param wdir 作業ディレクトリ
 * @return true 
 * @return false 
 */
bool Execute_demote(UnicodeString cmd, UnicodeString prm = EmptyStr, UnicodeString wdir = EmptyStr);

/**
 * @brief git.exe を実行
 * @param prm パラメータ
 * @param wdir 作業ディレクトリ
 * @param[out] o_lst 出力リスト
 * @param[out] exit_cd 終了コード
 * @param[out] w_lst 警告リスト(出力から分離して取得) 
 * @param rq_abort 中断要求
 * @return true 
 * @return false 
 */
bool GitShellExe(UnicodeString prm, UnicodeString wdir, TStringList *o_lst, DWORD *exit_cd = NULL,
		TStringList *w_lst = NULL, bool *rq_abort = NULL);
bool GitShellExe(UnicodeString prm, UnicodeString wdir, TMemoryStream *o_ms, DWORD *exit_cd = NULL);
bool GitShellExe(UnicodeString prm, UnicodeString wdir);
void split_GitWarning(TStringList *o_lst, TStringList *w_lst = NULL);

/** @brief 指定リビジョンのファイルを一時ディレクトリに保存 */
UnicodeString save_GitRevAsTemp(UnicodeString id, UnicodeString fnam, UnicodeString wdir);

/**
 * @brief grep.exe を実行
 * @param prm パラメータ
 * @param wdir 作業ディレクトリ
 * @param[out] o_lst 出力リスト
 * @param[out] exit_cd 終了コード
 * @param[out] rq_abort 中断要求
 * @return true 
 * @return false 
 */
bool GrepShellExe(UnicodeString prm, UnicodeString wdir, TStringList *o_lst, DWORD *exit_cd = NULL, bool *rq_abort = NULL);

/** @brief 実行/待機中のタスク数を取得 */
int  get_BusyTaskCount();

/** @brief 強制実行を含む最大タスク数を取得 */
int  get_MaxTaskCount();

/**
 * @brief 空きタスクがあるか？
 * @param ex_sw 最大タスク数を超えて取得
 * @return true 
 * @return false 
 */
bool has_EmptyTask(bool ex_sw = false);

/**
 * @brief タスクスレッドを取得
 * @param cp タスク設定
 * @param reserve 予約する
 * @param force 保留中でも強制取得
 * @param ext_sw 最大タスク数を超えて取得
 * @return TTaskThread* 
 */
TTaskThread * CreTaskThread(TaskConfig **cp, bool reserve = true, bool force = false, bool ext_sw = false);

/** タスクの開始または予約 */
void ActivateTask(TTaskThread *tp, TaskConfig *cp);

/** 予約保留項目の実行 */
void StartReserve();
bool StartReserve(int idx, bool ext_sw = false);

/** @brief タスクに低速実行を要求 */
void RequestSlowTask();

/** @brief タスクで処理中のファイルか？ */
bool is_OnTask(UnicodeString fnam);

UnicodeString get_LogErrMsg(UnicodeString msg = EmptyStr, bool add_cr = true, UnicodeString fnam = EmptyStr, int err_id = NO_ERROR);
void set_LogErrMsg(UnicodeString &msg, UnicodeString s = EmptyStr, UnicodeString fnam = EmptyStr, int err_id = NO_ERROR);

int get_TopMargin(TCanvas *cv);
int get_TopMargin2(TCanvas *cv);

/** @brief 時計パネル用文字列を取得 */
UnicodeString GetClockStr();

/** @brief コマンドファイルの改名をオプション設定に反映 */
void RenameOptCmdFile();

/** @brief コマンドファイルの参照情報を取得 */
UnicodeString get_ref_CmdFile(UnicodeString fnam, TStringList *lst = NULL);

/** @brief エイリアスを参照しているキーを取得(カンマ区切り文字列) */
UnicodeString get_Alias_KeyStr(UnicodeString alias, TStringList *k_lst = NULL);

/** @brief 説明や引用符を外してパラメータを抽出 */
UnicodeString extract_ExeParam(UnicodeString prm, UnicodeString *dsc = NULL);

UnicodeString make_PathMask(UnicodeString mask, UnicodeString def_desc = EmptyStr);

UnicodeString make_LogHdr(UnicodeString cmd, UnicodeString fnam = EmptyStr, bool is_dir = false, int wd = 0);
UnicodeString make_LogHdr(const _TCHAR *cmd, UnicodeString fnam = EmptyStr, bool is_dir = false, int wd = 0);
UnicodeString make_LogHdr(const _TCHAR *cmd, file_rec *fp);
UnicodeString make_CreateLog(UnicodeString dnam);
UnicodeString make_RenameLog(UnicodeString o_nam, UnicodeString n_nam);
void cat_DestDir(UnicodeString &msg, UnicodeString dnam);
void cat_DestFile(UnicodeString &msg, UnicodeString fnam);
void set_RenameLog(UnicodeString &msg, UnicodeString fnam);

/** @brief ログリストボックスの更新 */
void UpdateLogListBox();

void StartLog(UnicodeString msg, int task_no = -1);
void StartLog(const _TCHAR *msg, int task_no = -1);
void EndLog(UnicodeString msg, UnicodeString inf = EmptyStr);
void EndLog(const _TCHAR *msg, UnicodeString inf = EmptyStr);
void EndLog(int id, UnicodeString inf = EmptyStr);
void ExeErrLog(UnicodeString fnam, UnicodeString msg);

UnicodeString get_ResCntStr(int ok_cnt = 0, int er_cnt = 0, int sk_cnt = 0, int ng_cnt = 0, bool is_task = false);

void AddLog(UnicodeString msg, bool with_t = false, bool raw = false);
void AddLog(const _TCHAR *msg, bool with_t = false);
void AddLogStrings(TStringList *lst);
void AddLogCr();
void AddErr_Highlight();
void AddDebugLog(UnicodeString msg, UnicodeString info = EmptyStr, UnicodeString info2 = EmptyStr);
void FlushLog();

bool __fastcall SpecialKeyProc(TForm *frm, WORD &Key, TShiftState Shift, const _TCHAR *topic = NULL);
bool __fastcall SpecialKeyProc(TForm *frm, WORD &Key, TShiftState Shift, int hlp_cnt);

bool __fastcall SpecialEditProc(TObject *Sender, WORD &Key, TShiftState Shift);

/** @brief ディレクトリ入力ボックス */
UnicodeString inputbox_dir(const _TCHAR *tit, const _TCHAR *cmd);

bool is_FirstKey(UnicodeString id, UnicodeString keystr);
bool is_IniSeaKey(UnicodeString &keystr);

bool update_IncSeaWord(UnicodeString &kwd, UnicodeString keystr, bool fl_sw = false);

bool is_OneNrmCmd(UnicodeString cmds, bool no_prm = false);

bool MovListBoxFromFilter(TListBox *lp, UnicodeString key_str);
bool MovGridFromFilter(TStringGrid *gp, UnicodeString key_str);

/** @brief リストボックスでのコマンド処理 */
bool ExeCmdListBox(TListBox *lp, UnicodeString cmd, UnicodeString prm = EmptyStr);

void copy_to_Clipboard(UnicodeString s);
void copy_to_Clipboard(TPicture *pic);
void copy_to_Clipboard(TMetafile *mf);
void copy_to_Clipboard(Graphics::TBitmap *bmp);

int  get_GenWndList(TStringList *lst);

bool CloseOtherNyanFi();
int  get_NyanFiList(TStringList *lst);
UnicodeString get_NewTitle(bool primary = false);
HWND get_NyanFiWnd(int rel_idx);
bool activate_NyanFi(int idx, bool rel = true);
bool IsDuplicated();

int  get_ExViewerList(TStringList *lst);
bool focus_ExViewer();
void close_all_ExViewer(TForm *frm = NULL);

/**
 * @brief 最初に起動された NyanFi のハンドルを取得
 * @return HWND 
 */
HWND get_PrimNyanWnd();

/**
 * @brief NyanFi のメイン画面か？
 * @param hWnd 
 */
bool IsNyanfiWnd(HWND hWnd);

/**
 * @brief 二重起動された NyanFi のメイン画面か？
 * @param hWnd 
 */
bool IsNyanfi2Wnd(HWND hWnd);

/**
 * @brief 最初に起動された NyanFi に文字列を送出
 * @param msg 
 * @return true 
 * @return false 
 */
bool NotifyPrimNyan(UnicodeString msg);

HWND get_ModalWnd();
HWND get_HelpWnd();
HWND get_MenuWnd();

double GetDistance(double lat1, double lng1, double lat2, double lng2);
bool OpenWebMaps(double lat, double lng, UnicodeString fnam, int map_idx, int zoom, UnicodeString tnam = EmptyStr);

UnicodeString cipher(UnicodeString orgstr);
UnicodeString uncipher(UnicodeString cipstr);

void AddToRecentFile(UnicodeString fnam);
void AddToRecentFile(TStringList *lst);

int get_ViewTabWidth(UnicodeString fext);

/**
 * @brief ツリーリストを(再)作成
 * @param lst 
 * @param pnam 
 * @param chk_sw 抜けをチェック
 */
void MakeTreeList(TStringList *lst, UnicodeString pnam, bool chk_sw = false);
bool AddPathToTreeList(TStringList *lst);

/**
 * @brief コマンド履歴の追加
 * @param cmd コマンド
 * @param prm パラメータ
 * @param id 画面モード
 * @param fnam 対象ファイル名
 */
void AddCmdHistory(UnicodeString cmd, UnicodeString prm = EmptyStr, UnicodeString id = EmptyStr, UnicodeString fnam = EmptyStr);

//Git 関連の関数
UnicodeString get_GitTopPath(UnicodeString dnam);
UnicodeString get_GitConfig(UnicodeString dnam);
UnicodeString get_GitUrl(file_rec *fp);
int get_GitStatusList(UnicodeString pnam, TStringList *lst, bool full_sw = false);
int get_GitChangedList(UnicodeString pnam, TStringList *lst);
UnicodeString get_GitStatusStr(TStringList *lst, bool *staged = NULL);
UnicodeString get_GitGraphStr(UnicodeString lbuf);
UnicodeString split_GitGraphStr(UnicodeString &lbuf);
void draw_GitGraph(UnicodeString s, UnicodeString s1, UnicodeString s2, TCanvas *cv, TRect &rc,
	bool is_head = false, bool is_wip = false);
void draw_GitTag(TCanvas *cv, int &x, int y, UnicodeString tag, int mgn = 0);
void get_GitInf(UnicodeString dnam, TStringList *lst, bool upd_sw = false, bool ext_sw = false);
UnicodeString get_GitDiffFiles(UnicodeString s, UnicodeString &fnam2);
UnicodeString get_GitDiffFile2(UnicodeString s);

int extract_ver_no(UnicodeString fnam);

//---------------------------------------------------------------------------
/**
 * @brief ツールチップ (配色変更のためにサブクラス化)
 */
class UsrTooltipWindow : public THintWindow
{
private:
	void __fastcall Paint(void);

public:
	__fastcall UsrTooltipWindow(TComponent* AOwner) : THintWindow(AOwner) {}
};
//---------------------------------------------------------------------------
#endif
