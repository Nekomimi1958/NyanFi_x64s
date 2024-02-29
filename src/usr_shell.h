/**
 * @file usr_shell.h
 * @brief �V�F���֘A�̏���
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
#define FPRP_NAM_WD		15				//!< ���ږ��̍ő�\����(���p�P��)

//��񍀖ڂ̎�ރt���O
#define LBFLG_STD_FINF	0x00010000		//!< ��{�t�@�C�����
#define LBFLG_PATH_FIF	0x00020000		//!< �p�X��
#define LBFLG_FILE_FIF	0x00040000		//!< �t�@�C����
#define LBFLG_TIME_FIF	0x00080000		//!< �^�C���X�^���v
#define LBFLG_ATTR_FIF	0x00100000		//!< ����
#define LBFLG_TAGS_FIF	0x00200000		//!< �^�O
#define LBFLG_TYPE_FIF	0x00400000		//!< ���

#define LBFLG_FEXT_FIF	0x01000000		//!< �g���q�ʃt�@�C����
#define LBFLG_CRCD_FIF	0x02000000		//!< ���s�R�[�h
#define LBFLG_ERR_FIF	0x04000000		//!< �G���[/�x��
#define LBFLG_DEBUG		0x08000000		//!< �f�o�b�O���
#define LBFLG_GIT_TAG	0x10000000		//!< Git�^�O
#define LBFLG_GIT_HASH	0x20000000		//!< Git�n�b�V��

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
// TDropSource �N���X
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
// TDropTarget �N���X
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
// TDropTarget �N���X
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
 * @brief �h���b�v�^�[�Q�b�g�E���X�g
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
 * @brief �V�F���֘A�̏����N���X
 */
class UserShell
{
private:
	TStringList *PropertyList;		//!< �v���p�e�B�̍��ڃ��X�g (���ږ�=�C���f�b�N�XNo.)

	TFPUExceptionMask FpuTmpMask;	//!< ���������_��O�̗}�~�}�X�N
									//!< ������� .opus �t�@�C���ł̃G���[�΍�

	IDataObject* GetFilePathDataObject(UnicodeString dnam, TStringList *flist);

	unsigned int   msRead_uint(TMemoryStream *ms, int ofs);
	unsigned short msRead_ushort(TMemoryStream *ms, int ofs);
	UnicodeString  msRead_strdat(TMemoryStream *ms, int &ptr, bool is_uc);

public:
	UserShell(HWND hWnd);
	~UserShell();

	int  PropNameWidth;		//!< �v���p�e�B���ږ��̍ő�\����(���p�P��)

	void AddTargetList(TForm *form, TWinControl *ctrl);
	void DelTargetItem(TForm *form);

	DWORD DoFilesDragDrop(UnicodeString dnam, TStringList *flist, int tag);
	DWORD DoClipDragDrop();

	/**
	 * @brief �R���e�L�X�g���j���[��\��
	 * @param hWnd �E�B���h�E�n���h��
	 * @param dnam �f�B���N�g����
	 * @param flist �Ώۃ��X�g
	 * @param ex_item �ǉ����j���[���ڃ��X�g(�L���v�V���� [TAB] �R�}���h [TAB] �A�C�R��)
	 * @return UnicodeString ���s�̏ꍇ "ERROR"�A�ǉ����ڂȂ炻�̕�����A����ȊO�� EmptyStr
	 */
	UnicodeString ShowContextMenu(HWND hWnd, UnicodeString dnam, TStringList *flist, TStringList *ex_item);

	/**
	 * @brief //�h���C�u�̃R���e�L�X�g���j���[��\��/�w��ID�����s
	 * @param �E�B���h�E�n���h��
	 * @param drvnam �h���C�u��
	 * @param ex_item �ǉ����j���[���ڃ��X�g(�L���v�V���� [TAB] �R�}���h�A�T�u���j���[��Ή�)
	 * @param ex_ID �R�}���hID(>0 �̏ꍇ���j���[��\��������ID�����s)
	 * @return UnicodeString ���s�̏ꍇ "ERROR"�A�ǉ����ڂȂ炻�̕�����A����ȊO�� EmptyStr
	 */
	UnicodeString DriveContextMenu(HWND hWnd, UnicodeString drvnam, TStringList *ex_item, int ex_ID = 0);

	/**
	 * @brief Copy/ Cut �Ȃǂ̃R�}���h�����s
	 * @param hWnd �E�B���h�E�n���h��
	 * @param dnam �f�B���N�g����
	 * @param flist �Ώۃt�@�C�����X�g
	 * @param cmd �R�}���h
	 * @return true
	 * @return false
	 */
	bool InvokeMenuCmd(HWND hWnd, UnicodeString dnam, TStringList *flist, LPCSTR cmd);

	/** @brief �t�@�C�������w�肵�Ď��s */
	bool ShowFileRun();

	/**
	 * @brief �V���[�g�J�b�g�̍쐬
	 * @param fnam �t�@�C����
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
	 * @brief �V���[�g�J�b�g���̎擾
	 * @param fnam �t�@�C����
	 * @param[out] lst ��񃊃X�g
	 * @param[out] nam �����N��
	 * @param[out] prm �p�����[�^
	 * @param[out] fld ��Əꏊ
	 * @param[out] shw ���s���̑傫��
	 * @param[out] rem �R�����g
	 * @param[out] is_ra �Ǘ��҂Ƃ��Ď��s
	 * @return true
	 * @return false
	 */
	bool get_LnkInf(UnicodeString fnam, TStringList *lst, UnicodeString *nam = NULL,
		UnicodeString *prm = NULL, UnicodeString *fld = NULL, int *shw = NULL, UnicodeString *rem = NULL, bool *is_ra = NULL);

	/**
	 * @brief �t�@�C���̎�ނ��擾
	 * @param fnam �t�@�C����
	 * @return UnicodeString
	 */
	UnicodeString get_FileTypeStr(UnicodeString fnam);

	/**
	 * @brief �V���[�g�J�b�g�̃����N����擾
	 * @param fnam �t�@�C����
	 * @return UnicodeString
	 */
	UnicodeString get_LnkName(UnicodeString fnam);

	HICON get_ico_f(UnicodeString fnam, int size, bool force = false);

	HICON get_Icon(UnicodeString fnam, int &size, bool chk_sz = true);

	/**
	 * @brief �X���[���A�C�R�����擾
	 * @param fnam �t�@�C����
	 * @return HICON
	 */
	HICON get_SmallIcon(UnicodeString fnam);

	/**
	 * @brief �X���[���A�C�R����`��
	 * @param fnam �t�@�C����
	 * @param cv �L�����o�X
	 * @param x X�ʒu
	 * @param y Y�ʒu
	 * @param cp �R���g���[��
	 * @return true
	 * @return false
	 */
	bool draw_SmallIcon(UnicodeString fnam, TCanvas *cv, int x, int y,TControl *cp = NULL);

	bool draw_SmallIcon(UnicodeString fnam, TImage *ip, TColor bg = clBtnFace, TControl *cp = NULL);

	/**
	 * @brief �t�@�C������T���l�C�����擾
	 * @param fnam �t�@�C����
	 * @param[out] o_bmp
	 * @param o_size
	 * @return true
	 * @return false
	 */
	bool  get_Thumbnail(UnicodeString fnam, Graphics::TBitmap *o_bmp, int o_size);

	/** @brief ���m�p�X��GUID��������p�X���ɕϊ� */
	UnicodeString KnownGuidStrToPath(UnicodeString s);

	/**@brief ���m�p�XID���p�X���ɕϊ� */
	UnicodeString KnownGuidToPath(REFKNOWNFOLDERID id);

	void AddKnownPath(REFKNOWNFOLDERID id, TStringList *lst, bool brk_sw = false);
	void AddEnvPath(UnicodeString enam, TStringList *lst, bool brk_sw = false);

	/**
	 * @brief ����t�H���_�ꗗ���擾(���[�N���X�g�`��)
	 * @param[out] lst ���X�g 
	 */
	void get_SpecialFolderList(TStringList *lst);
};
//---------------------------------------------------------------------------
extern UserShell *usr_SH;
//---------------------------------------------------------------------------

#endif
