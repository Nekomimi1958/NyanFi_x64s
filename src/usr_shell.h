/**
 * @file usr_shell.h
 * @brief シェル関連の処理
 */
//---------------------------------------------------------------------------
#ifndef UserShellH
#define UserShellH

//---------------------------------------------------------------------------
#include <System.Math.hpp>

//---------------------------------------------------------------------------
#define WM_FORM_DROPPED  (WM_APP + 10)

//---------------------------------------------------------------------------
#define WICIMG_FRAME		0
#define WICIMG_PREVIEW		1
#define WICIMG_THUMBNAIL	2

//---------------------------------------------------------------------------
#define FPRP_NAM_WD		15				//!< 項目名の最大表示幅(半角単位)

//情報項目の種類フラグ
#define LBFLG_STD_FINF	0x00010000		//!< 基本ファイル情報
#define LBFLG_PATH_FIF	0x00020000		//!< パス名
#define LBFLG_FILE_FIF	0x00040000		//!< ファイル名
#define LBFLG_TIME_FIF	0x00080000		//!< タイムスタンプ
#define LBFLG_ATTR_FIF	0x00100000		//!< 属性
#define LBFLG_TAGS_FIF	0x00200000		//!< タグ
#define LBFLG_TYPE_FIF	0x00400000		//!< 種類

#define LBFLG_FEXT_FIF	0x01000000		//!< 拡張子別ファイル数
#define LBFLG_CRCD_FIF	0x02000000		//!< 改行コード
#define LBFLG_ERR_FIF	0x04000000		//!< エラー/警告
#define LBFLG_DEBUG		0x08000000		//!< デバッグ状態
#define LBFLG_GIT_TAG	0x10000000		//!< Gitタグ
#define LBFLG_GIT_HASH	0x20000000		//!< Gitハッシュ

//---------------------------------------------------------------------------
UnicodeString get_WndText(HWND hWnd);
UnicodeString get_WndClassName(HWND hWnd);

UnicodeString get_LocalFlderName(UnicodeString pnam);

UnicodeString get_PropTitle(UnicodeString s);
UnicodeString get_PropTitle(const _TCHAR *s);
UnicodeString make_PropLine(UnicodeString tit, UnicodeString str);
UnicodeString make_PropLine(const _TCHAR *tit, UnicodeString str);
UnicodeString make_PropLine(UnicodeString tit, int n);
UnicodeString make_PropLine(const _TCHAR *tit, int n);

void add_PropLine(UnicodeString tit, UnicodeString str, TStrings *lst, int flag = 0);
void add_PropLine(const _TCHAR *tit, UnicodeString str, TStrings *lst, int flag = 0);
void add_PropLine(UnicodeString tit, int n, TStrings *lst, int flag = 0);
void add_PropLine(const _TCHAR *tit, int n, TStrings *lst, int flag = 0);
void add_PropLine_if(const _TCHAR *tit, UnicodeString str, TStrings *lst, int flag = 0);

void add_WarnLine(UnicodeString str, TStrings *lst);

//---------------------------------------------------------------------------
extern HWND TargetHandle;
extern int  DragStartTag;
extern int  DroppedTag;
extern int  DroppedMode;
extern int  DefDropMode;
extern UnicodeString DragDrive;
extern bool DropRefused;

extern TStringList *DroppedList;
extern TListBox *L_FileListBox;
extern TListBox *R_FileListBox;

extern IContextMenu2 *ContextMenu2;
extern IContextMenu3 *ContextMenu3;

//---------------------------------------------------------------------------
struct drop_target_rec {
	TForm *TargetForm;
	TWinControl *TargetWinCtrl;
	HWND hTargetWnd;
};

//---------------------------------------------------------------------------
// TDropSource クラス
//---------------------------------------------------------------------------
class TDropSource : public IDropSource
{
public:
	TDropSource() : FRefCount(0) { }
	HRESULT __stdcall QueryInterface(REFIID riid, void **ppv);
	ULONG   __stdcall AddRef();
	ULONG   __stdcall Release();
	HRESULT __stdcall QueryContinueDrag(BOOL fEsc, DWORD grfKeyState);
	HRESULT __stdcall GiveFeedback(DWORD dwEffect);

private:
	LONG FRefCount;
};

//---------------------------------------------------------------------------
// TDropTarget クラス
//---------------------------------------------------------------------------
class TDropTargetBase : public IDropTarget
{
protected:
	unsigned int refCount;

	TDropTargetBase();
	virtual ~TDropTargetBase() { }

	virtual HRESULT __stdcall QueryInterface(const IID& iid, void **ppv);
	virtual ULONG __stdcall AddRef();
	virtual ULONG __stdcall Release();
};

//---------------------------------------------------------------------------
// TDropTarget クラス
//---------------------------------------------------------------------------
class TDropTarget : public TDropTargetBase
{
public:
	static void CreateInstance(IDropTarget **pp);

private:
	virtual HRESULT __stdcall DragEnter(IDataObject *pDataObj, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect);
	virtual HRESULT __stdcall DragOver(DWORD grfKeyState, POINTL pt, DWORD *pdwEffect);
	virtual HRESULT __stdcall DragLeave();
	virtual HRESULT __stdcall Drop(IDataObject *pDataObj, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect);
};

//---------------------------------------------------------------------------
/**
 * @brief ドロップターゲット・リスト
 */
class TDropTargetList : public TList
{
private:
	drop_target_rec * __fastcall Get(int Index)
	{
		return (drop_target_rec*)(TList::Get(Index));
	}
	void __fastcall Put(int Index, drop_target_rec *Item)
	{
		TList::Put(Index, Item);
	}

	virtual void __fastcall Notify(void *Ptr, TListNotification Action);

public:
	__property drop_target_rec *Items[int Index] = {read=Get, write=Put};

	__fastcall TDropTargetList();
	void __fastcall AddNew(TForm *form, TWinControl *ctrl);
};

extern TDropTargetList *TargetList;
extern int TargetIndex;

//---------------------------------------------------------------------------
/**
 * @brief シェル関連の処理クラス
 */
class UserShell
{
private:
	TStringList *PropertyList;		//!< プロパティの項目リスト (項目名=インデックスNo.)

	TFPUExceptionMask FpuTmpMask;	//!< 浮動小数点例外の抑止マスク
									//!< ※特殊な .opus ファイルでのエラー対策

	IDataObject* GetFilePathDataObject(UnicodeString dnam, TStringList *flist);

	unsigned int   msRead_uint(TMemoryStream *ms, int ofs);
	unsigned short msRead_ushort(TMemoryStream *ms, int ofs);
	UnicodeString  msRead_strdat(TMemoryStream *ms, int &ptr, bool is_uc);

public:
	UserShell(HWND hWnd);
	~UserShell();

	int  PropNameWidth;		//!< プロパティ項目名の最大表示幅(半角単位)

	void AddTargetList(TForm *form, TWinControl *ctrl);
	void DelTargetItem(TForm *form);

	DWORD DoFilesDragDrop(UnicodeString dnam, TStringList *flist, int tag);
	DWORD DoClipDragDrop();

	/**
	 * @brief コンテキストメニューを表示
	 * @param hWnd ウィンドウハンドル
	 * @param dnam ディレクトリ名
	 * @param flist 対象リスト
	 * @param ex_item 追加メニュー項目リスト(キャプション [TAB] コマンド [TAB] アイコン)
	 * @return UnicodeString 失敗の場合 "ERROR"、追加項目ならその文字列、それ以外は EmptyStr
	 */
	UnicodeString ShowContextMenu(HWND hWnd, UnicodeString dnam, TStringList *flist, TStringList *ex_item);

	/**
	 * @brief //ドライブのコンテキストメニューを表示/指定IDを実行
	 * @param ウィンドウハンドル
	 * @param drvnam ドライブ名
	 * @param ex_item 追加メニュー項目リスト(キャプション [TAB] コマンド、サブメニュー非対応)
	 * @param ex_ID コマンドID(>0 の場合メニューを表示せずにIDを実行)
	 * @return UnicodeString 失敗の場合 "ERROR"、追加項目ならその文字列、それ以外は EmptyStr
	 */
	UnicodeString DriveContextMenu(HWND hWnd, UnicodeString drvnam, TStringList *ex_item, int ex_ID = 0);

	/**
	 * @brief Copy/ Cut などのコマンドを実行
	 * @param hWnd ウィンドウハンドル
	 * @param dnam ディレクトリ名
	 * @param flist 対象ファイルリスト
	 * @param cmd コマンド
	 * @return true
	 * @return false
	 */
	bool InvokeMenuCmd(HWND hWnd, UnicodeString dnam, TStringList *flist, LPCSTR cmd);

	/** @brief ファイル名を指定して実行 */
	bool ShowFileRun();

	/**
	 * @brief ショートカットの作成
	 * @param fnam ファイル名
	 * @param target
	 * @param cmdprm
	 * @param wdir
	 * @param desc
	 * @return true
	 * @return false
	 */
	bool CreateShortCut(UnicodeString fnam, UnicodeString target,
		UnicodeString cmdprm = EmptyStr, UnicodeString wdir = EmptyStr, UnicodeString desc = EmptyStr);

	UnicodeString get_PropInf(UnicodeString fnam, TStringList *lst = NULL, UnicodeString idx_str = EmptyStr, bool lst_sw = false);
	UnicodeString get_PropStr(UnicodeString fnam, UnicodeString prp_nam);
	UnicodeString get_VerStr(UnicodeString fnam);

	UnicodeString get_PropValue(TStringList *lst, UnicodeString name);
	int  get_Duration(UnicodeString fnam);

	/**
	 * @brief ショートカット情報の取得
	 * @param fnam ファイル名
	 * @param[out] lst 情報リスト
	 * @param[out] nam リンク先
	 * @param[out] prm パラメータ
	 * @param[out] fld 作業場所
	 * @param[out] shw 実行時の大きさ
	 * @param[out] rem コメント
	 * @param[out] is_ra 管理者として実行
	 * @return true
	 * @return false
	 */
	bool get_LnkInf(UnicodeString fnam, TStringList *lst, UnicodeString *nam = NULL,
		UnicodeString *prm = NULL, UnicodeString *fld = NULL, int *shw = NULL, UnicodeString *rem = NULL, bool *is_ra = NULL);

	/**
	 * @brief ファイルの種類を取得
	 * @param fnam ファイル名
	 * @return UnicodeString
	 */
	UnicodeString get_FileTypeStr(UnicodeString fnam);

	/**
	 * @brief ショートカットのリンク先を取得
	 * @param fnam ファイル名
	 * @return UnicodeString
	 */
	UnicodeString get_LnkName(UnicodeString fnam);

	HICON get_ico_f(UnicodeString fnam, int size, bool force = false);

	HICON get_Icon(UnicodeString fnam, int &size, bool chk_sz = true);

	/**
	 * @brief スモールアイコンを取得
	 * @param fnam ファイル名
	 * @return HICON
	 */
	HICON get_SmallIcon(UnicodeString fnam);

	/**
	 * @brief スモールアイコンを描画
	 * @param fnam ファイル名
	 * @param cv キャンバス
	 * @param x X位置
	 * @param y Y位置
	 * @param cp コントロール
	 * @return true
	 * @return false
	 */
	bool draw_SmallIcon(UnicodeString fnam, TCanvas *cv, int x, int y,TControl *cp = NULL);

	bool draw_SmallIcon(UnicodeString fnam, TImage *ip, TColor bg = clBtnFace, TControl *cp = NULL);

	/**
	 * @brief ファイルからサムネイルを取得
	 * @param fnam ファイル名
	 * @param[out] o_bmp
	 * @param o_size
	 * @return true
	 * @return false
	 */
	bool  get_Thumbnail(UnicodeString fnam, Graphics::TBitmap *o_bmp, int o_size);

	/** @brief 既知パスのGUID文字列をパス名に変換 */
	UnicodeString KnownGuidStrToPath(UnicodeString s);

	/**@brief 既知パスIDをパス名に変換 */
	UnicodeString KnownGuidToPath(REFKNOWNFOLDERID id);

	void AddKnownPath(REFKNOWNFOLDERID id, TStringList *lst, bool brk_sw = false);
	void AddEnvPath(UnicodeString enam, TStringList *lst, bool brk_sw = false);

	/**
	 * @brief 特殊フォルダ一覧を取得(ワークリスト形式)
	 * @param[out] lst リスト 
	 */
	void get_SpecialFolderList(TStringList *lst);
};
//---------------------------------------------------------------------------
extern UserShell *usr_SH;
//---------------------------------------------------------------------------

#endif
