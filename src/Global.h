/**
 * @file Global.h
 * @brief �O���[�o���ϐ�/�֐�
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
/** @defgroup DEFINE ��` */
/** @{ */
//---------------------------------------------------------------------------
#define SUPPORT_URL	"https://github.com/Nekomimi1958/NyanFi_x64s"
#define RELEASE_URL	"https://api.github.com/repos/Nekomimi1958/NyanFi_x64s/releases/latest"

//---------------------------------------------------------------------------
#define WM_FORM_SHOWED		(WM_APP + 1)	//!< �t�H�[�����\�����ꂽ
#define WM_NYANFI_APPEAR	(WM_APP + 100)	//!< �f�U�C���A�t�H���g�A�z�F���ύX���ꂽ
#define WM_NYANFI_FLICON	(WM_APP + 101)	//!< �A�C�R�����擾����
#define WM_NYANFI_THUMBNAIL	(WM_APP + 102)	//!< �T���l�C�����擾����
#define WM_NYANFI_CLPCOPIED	(WM_APP + 103)	//!< �N���b�v�{�[�h�ɃR�s�[����
#define WM_NYANFI_PLAYLIST	(WM_APP + 104)	//!< �v���C���X�g�ʒm
#define WM_NYANFI_LOCKKEY	(WM_APP + 105)	//!< LockKeyMouse ���쒆�̃L�[����
#define WM_NYANFI_CLSEDITM	(WM_APP + 106)	//!< �ݒ荀�ڂ̕ҏW�_�C�A���O�����
#define WM_NYANFI_GREP_END	(WM_APP + 110)	//!< GREP����

//---------------------------------------------------------------------------
//WM_COPYDATA ���b�Z�[�W�̎��ʔԍ�
#define CPYDTID_OPTIONS	1		//!< �N���I�v�V����
#define CPYDTID_DPL_INF	2		//!< ��d�N��������̉�ʏ��
#define CPYDTID_DPL_MSG	3		//!< ��d�N��������̒ʒm���b�Z�[�W
#define CPYDTID_TXTVIEW	4		//!< �e�L�X�g�r���[�A�ŊJ��
#define CPYDTID_IMGVIEW	5		//!< �C���[�W�r���[�A�ŊJ��
#define CPYDTID_EXECMDS	6		//!< �R�}���h�����s
/** @} */

//---------------------------------------------------------------------------
//�N���p�o�b�`�t�@�C��
extern UnicodeString RstBatName;		//!< �ċN���p�o�b�`�t�@�C����

//---------------------------------------------------------------------------
//HTML�w���v
extern bool CancelHelp;					//!< [F1]�ɃR�}���h�����蓖�Ă��Ă�����w���v��}�~

/**
 * @brief �w���v�g�s�b�N���J��
 * @param topic �g�s�b�N
 */
void HtmlHelpTopic(const _TCHAR *topic);

/**
 * @brief �w���v���J��
 * @param idx �R���e�L�X�g
 */
void HtmlHelpContext(int idx);

/**
 * @brief �t�@�C��/�L�[���[�h���w�肵�ăw���v���J��(hhh.exe)
 * @param fnam �w���v�t�@�C����
 * @param kwd �L�[���[�h
 */
void HtmlHelpKeyword(UnicodeString fnam, UnicodeString kwd);

/** @brief �w���v����� */
void CloseHelpWnd();

#define HELPTOPIC_TOP	"hid00001.htm"		//!< �\��
#define HELPTOPIC_FL	"hid00005.htm"		//!< �t�@�C���[ - �R�}���h
#define HELPTOPIC_TV	"hid00006.htm"		//!< �e�L�X�g�r���[�A
#define HELPTOPIC_IV	"hid00007.htm"		//!< �C���[�W�r���[�A
#define HELPTOPIC_IS	"hid00050.htm"		//!< �C���N�������^���T�[�`
#define HELPTOPIC_CI	"hid00100.htm"		//!< �R�}���h�̍���
#define HELPTOPIC_CILW	"hid00100.htm#LW"	//!< �R�}���h�̍���(���O�E�B���h�E)
#define HELPTOPIC_FI	"hid00101.htm"		//!< �R�}���h�̍���(�@�\��)
#define HELPTOPIC_XC	"hid00063.htm"		//!< ExeCommands �R�}���h
#define HELPTOPIC_GR	"hid00056.htm"		//!< �����񌟍�(GREP)
#define HELPTOPIC_RP	"hid00061.htm"		//!< ������u��
#define HELPTOPIC_GIT	"hid00090.htm"		//!< Git�̗��p
#define HELPTOPIC_CH	"hid00109.htm"		//!< �ύX����

//---------------------------------------------------------------------------
//����JAPI
typedef BOOL (WINAPI *FUNC_GetFontResourceInfo)(LPCWSTR, DWORD*, LPVOID, DWORD);
extern  HMODULE hGdi32;
extern  FUNC_GetFontResourceInfo	lpfGetFontResourceInfo;

//---------------------------------------------------------------------------
/** @addtogroup DEFINE */
/** @{ */

#define DEF_WIN_WIDTH	800
#define DEF_WIN_HEIGHT	600

/** @defgroup DEF_SCR_MODE ��ʃ��[�h(ScrMode) */
/** @{ */
#define SCMD_FLIST	1					//!< �t�@�C���[
#define SCMD_TVIEW	2					//!< �e�L�X�g�r���[�A
#define SCMD_IVIEW	4					//!< �C���[�W�r���[�A
#define SCMD_GREP	8					//!< GREP
/** @} */

#define MAX_FILELIST	 2				//!< �t�@�C�����X�g�� (���E)
#define MAX_TASK_THREAD	 6				//!< �ő�^�X�N�� = 4 + 2(�������s�p)

#define MAX_BGIMAGE		 6				//!< �w�i�摜��(�w�i*2/ ���E*2/ �m�u*2)
#define BGIMGID_KNOB_V	 4
#define BGIMGID_KNOB_H	 5

#define MAX_TABLIST	 	30				//!< �ő�^�u��

#define MAX_FNTZOOM_SZ	72				//!< �ő�t�H���g�T�C�Y
#define MIN_FNTZOOM_SZ	2				//!< �ŏ��t�H���g�T�C�Y

#define MAX_WORKHISTORY 50				//!< �ő像�[�N���X�g����
#define MAX_CMD_HISTORY 1000			//!< �ő�R�}���h����
#define MAX_FNCPY_HISTORY 50			//!< �R�s�[�����t�@�C�����̍ő嗚��

#define CMPDEL_BUFF_SIZE 2048			//!< ���S�폜�̃o�b�t�@�T�C�Y
#define CRLF_DETECT_LINE 1000			//!< ���s�R�[�h����̍s��

#define ID_CALL_HOTKEY	101
#define ID_APP_HOTKEY	102

#define TMP_ARC_F	"ARC~%04u"			//!< �A�[�J�C�u�p�ꎞ�f�B���N�g���̏���
#define TMP_ARC_P	"ARC~????"			//!< �A�[�J�C�u�p�ꎞ�f�B���N�g���̌����p�^�[��
#define TMP_FTP_D	"FTP~0000"			//!< FTP�p�ꎞ�f�B���N�g��

#define FICO_INI_FILE "FolderIcon.INI"	//!< �t�H���_�A�C�R����`
#define HILT_INI_FILE "Highlight.INI"	//!< �\�������\����`
#define DIR_HIST_FILE "DirHistory.INI"	//!< �f�B���N�g���S�̗���
#define CALC_INI_FILE "Calculator.INI"	//!< �d��̒�`
#define TAGDATA_FILE  "TAGDATA.TXT"		//!< �^�O�f�[�^
#define DRVLOG_FILE   "DriveLog.csv"	//!< �h���C�u�e�ʃ��O
#define RENLOG_FILE   "renamelog.txt"	//!< �������O
#define RENLIST_FILE  "renamelist.txt"	//!< �������X�g
#define CLIP_BMP_FILE "CLIPBOARD.BMP"	//!< �N���b�v�{�[�h�̈ꎞ�ۑ�

#define WEBMAP_FILE	  "$~WEBMAP.HTM"	//!< Web�}�b�v�\���p�t�@�C��
#define WEBMAP_TPLT	  "WEBMAP.HTM"		//!< Web�}�b�v�\���p�e���v���[�g

#define RESPONSE_FILE "$~LISTFILE.TXT"	//!< ���X�|���X�t�@�C����
#define RESPONSE_ERR  "ERROR"

#define DISTR_FILE	  "Distribute.INI"	//!< �U�蕪���o�^�t�@�C��

#define FONTSMPL_FILE "FontSample.INI"	//!< �t�H���g���{

#define SFX_AUTOREN   "_\\SN(1)"		//!< �f�t�H���g�̎�����������(�T�t�B�b�N�X)
#define FMT_AUTO_REN  "\\N" SFX_AUTOREN	//!< �f�t�H���g�̎�����������

#define LOG_ALL_TASK_RDY	"All Task Ready"

/** @defgroup DEF_CSVITMCNT CSV�̍��ڐ� */
/** @{ */
#define EXTMENU_CSVITMCNT	6			//!< caption,cmd,prm,alias,show,icon
#define EXTTOOL_CSVITMCNT	6			//!< caption,exe,prm,wk_dir,alias,show
#define TABLIST_CSVITMCNT	9			//!< path0,path1,caption,icon,home0,home1,nwl_mode,nwl,sync_lr
#define DISTRLS_CSVITMCNT	4			//!< title,enable,mask,dist
#define REGDIR_CSVITMCNT	4			//!< key,title,path,user_name
#define MAX_CSV_ITEM	  255
/** @} */

/** @defgroup DEF_LISTBOX_TAG ���X�g�{�b�N�X�p�I�v�V�����t���O
 * @details ListBox->Tag �ɐݒ肵�܂��B@n
 * ����2�o�C�g = �t�@�C�����:���ږ��ő啝/ �o�^�f�B���N�g��:�u�ꏊ�v�̕\���ʒu@n
 * ���4�r�b�g�� UserMdl �Ŏg�p
 */
/** @{ */
#define LBTAG_OPT_FIF1	0x00010000		//!< �t�@�C�����(�ŏ���3�s�͊�{���)
#define LBTAG_OPT_FIF2	0x00020000		//!< �t�@�C�����
#define LBTAG_OPT_SDIR	0x00040000		//!< ����t�H���_�ꗗ(���ϐ��g�p��)
#define LBTAG_OPT_TREE	0x00080000		//!< �c���[�\��
#define LBTAG_OPT_ZOOM	0x00100000		//!< �Y�[���\
#define LBTAG_OPT_LNNO	0x00200000		//!< �s�ԍ��\��
#define LBTAG_OPT_LCPY	0x00400000		//!< 1�s�R�s�[�\
#define LBTAG_OPT_LOOP	0x00800000		//!< ���[�v�ړ�
#define LBTAG_GEN_LIST	0x01000000		//!< �ꗗ�_�C�A���O
#define LBTAG_FIF_LIST	0x02000000		//!< �t�@�C�����_�C�A���O
#define LBTAG_TAB_FNAM	0x04000000		//!< �^�u�ȍ~�Ƀt�@�C����������
#define LBTAG_VAR_LIST	0x08000000		//!< �u���O=�l�v�`��
/** @} */

//---------------------------------------------------------------------------
#define SHOW_WARN_TAG	-1

//---------------------------------------------------------------------------
//�������Ɏ󂯕t����R�}���h
#define ONFIND_CMD	"CursorUp|CursorDown|PageUp|PageDown|CurrToOpp|FileEdit|BinaryEdit|OpenByApp|OpenByWin|OpenStandard|Select"

//---------------------------------------------------------------------------
//load_ImageFile �̖߂�l
#define LOADED_BY_STD	1		//!< WIC�W��
#define LOADED_BY_WIC	2		//!< WIC���̑�

//---------------------------------------------------------------------------
enum SeaOpt {soMigemo, soRegEx, soAndOr, soFuzzy, soCaseSens, soWord, soBytes, soFromPos,
			 soCSV, soTSV, soTree, soGitGrep, soGrep, soGrepS, soGrepF};
typedef Set <SeaOpt, soMigemo, soGrepF> SearchOption;	//!< �����p�I�v�V����

/** @} */

//---------------------------------------------------------------------------
/** @brief ��d�N���I�����̉�ʏ�� */
struct win_dat {
//���C���E�B���h�E
	int WinTop;
	int WinLeft;
	int WinWidth;
	int WinHeight;
	TWindowState WinState;
	int WinPPI;
//�T�u�p�l��
	int SubHeight;
	int SubWidth;
	int InfWidth;
	int InfHeight;
	int ImageWidth;
	int ImageHeight;
	int TailHeight;
//���̑�
	bool ShowFileListOnly;
};

//---------------------------------------------------------------------------
extern TCursor crTmpPrev;		//!< �J�[�\���̃v���r���[�p

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

extern UnicodeString TabPinMark;		//!< �^�u�Œ�s���}�[�N
extern UnicodeString HEAD_Mark;			//!< git HEAD �}�[�N
extern UnicodeString PLAY_Mark;			//!< �Đ����}�[�N

extern UnicodeString SortIdStr;

//---------------------------------------------------------------------------
extern HWND   MainHandle;				//!< ���C���E�B���h�E�̃n���h��
extern DWORD  ProcessId;				//!< �v���Z�XID
extern bool   IsAdmin;					//!< �Ǘ��Ҍ���
extern bool   IsPrimary;				//!< �ŏ��ɋN�����ꂽ
extern bool   GitExists;				//!< Git ���C���X�g�[������Ă���
extern bool   GrepExists;				//!< grep.exe ���C���X�g�[������Ă���
extern bool   IsMuted;					//!< ���ʃ~���[�g
extern int    StartedCount;				//!< ���s�J�n�J�E���g(m�b)
extern int    NyanFiIdNo;				//!< ���d NyanFi ����ID
extern bool   NoRoundWin;				//!< �p�ۃE�B���h�E�}�~

extern int    ScrMode;					//!< ��ʃ��[�h

extern UnicodeString VclStyle;			//!< VCL�X�^�C��

extern MarkList *ErrMarkList;

extern TRect  FileListRect;

extern TRichEdit *TempRichEdit;

extern TTaskThread *TaskThread[MAX_TASK_THREAD];	//!< �^�X�N�����X���b�h
extern bool gTaskCancel[MAX_TASK_THREAD];
extern bool gTaskPause[MAX_TASK_THREAD];
extern int  MaxTasks;						//!< �ő�^�X�N��
extern bool RsvSuspended;					//!< �\��ۗ̕�
extern TaskConfigList *TaskReserveList;		//!< �^�X�N�\�񃊃X�g
extern int  LastOpCount;					//!< �Ō�ɑ��삵���Ƃ��̃J�E���g�l

extern TImgViewThread   *ImgViewThread;		//!< �摜�r���[�����X���b�h
extern TThumbnailThread *ThumbnailThread;	//!< �T���l�C���擾�X���b�h
extern TGetIconThread   *GetIconThread;		//!< �A�C�R���擾�X���b�h

extern UserArcUnit *usr_ARC;				//!< �A�[�J�C�u�������j�b�g
extern UnicodeString FExt7zDll;				//!< 7z.dll �őΉ�����g���q

extern MigemoUnit  *usr_Migemo;				//!< Migemo �������j�b�g
extern UnicodeString MigemoPath;			//!< Migemo �f�B���N�g��
extern bool LastMigemoMode;
extern bool LastMigemoModeF;

extern int  WicScaleOpt;			//!< WIC�̏k���E�g��A���S���Y��
extern UnicodeString WicFextStr;	//!< WIC���Ή����Ă���g���q

extern bool gCopyAll;
extern bool gCopyCancel;

extern int  gCopyMode;				//!< ���E���ʃf�B���N�g���̏ꍇ�̃R�s�[���[�h
extern int  gCopyMode2;				//!< ���E������f�B���N�g���̏ꍇ�̃R�s�[���[�h
extern int  xCopyMode;				//!< ExeCommand ���ŗp���鋭�����[�h

#define CPYMD_OW			0
#define CPYMD_NEW			1
#define CPYMD_SKIP			2
#define CPYMD_AUT_REN		3
#define CPYMD_MAN_REN		4
#define CPYMD_REN_CLONE		5
#define CPYMD_NEW_BACKUP	10

extern UnicodeString gCopyFmt;

extern int OptionPageIndex;			//!< �I�v�V�����ݒ�_�C�A���O�̃y�[�W�C���f�b�N�X

extern bool SyncLR;					//!< ���E�̃f�B���N�g���ύX�𓯊�

extern UnicodeString GlobalErrMsg;

extern bool Initialized;			//!< ����������������
extern bool UnInitializing;			//!< �I���������J�n���ꂽ
extern bool Closing;				//!< �I��������

extern int  InhReload;				//!< Reload �̗}�~
extern bool DisReload;				//!< Reload �̖�����

extern bool InhUpdate;			  	//!< UpdateList �}�~
extern bool InhCmdHistory;  		//!< �R�}���h�����̗}�~

extern UnicodeString FindPath;
extern bool FindAborted;			//!< �������f�v��
extern bool FindDiff;				//!< DiffDir ���s��
extern int  FindTag;
extern int  FindCount;				//!< �}�b�`��

extern bool CalcAborted;			//!< �v�Z���f�v��
extern int  CalcTag;

extern bool GitGrepAborted;			//!< GitGrep �̒��f�v��

//---------------------------------------------------------------------------
extern bool MultiInstance;			//!< ��d�N��������
extern bool CloseOthers;			//!< ����NyanFi���I��
extern bool StoreTaskTray;			//!< �ŏ������Ƀ^�X�N�g���C�Ɋi�[
extern bool ShowDirType;			//!< DIR��ʂ�\��
extern bool ShowSpace;				//!< �󔒂�\��
extern bool UseIndIcon;				//!< �t�@�C���ŗL�̃A�C�R�����g�p
extern bool ShowHideAtr;			//!< �B���t�@�C����\��
extern bool ShowSystemAtr;			//!< �V�X�e���t�@�C����\��
extern bool DispRegName;			//!< �p�X�̕\���ɓo�^����p����
extern bool UncToNetDrive;			//!< UNC���l�b�g���[�N�h���C�u����
extern bool CompInTitleBar;			//!< �^�C�g���o�[�ɃR���s���[�^����\��
extern bool PathInTitleBar;			//!< �^�C�g���o�[�ɃJ�����g�p�X��\��
extern bool TabGrInTitleBar;		//!< �^�C�g���o�[�Ƀ^�O�O���[�v����\��
extern bool OmitEndOfName;			//!< �������O�͖������ȗ�
extern bool ShowAdsInf;				//!< ��փf�[�^�X�g���[������\��
extern bool ShowUseProcInf;			//!< �v���Z�X�g�p����\��
extern bool ShowDirJumboIco;		//!< �f�B���N�g���͓���A�C�R����\��
extern bool ShowInZipImg;			//!< ZIP���̉摜��\��
extern bool PreviewAniGif;			//!< �A�j���[�V����GIF�̃v���r���[
extern bool SetPrvCursor;			//!< �v���r���[���Ń}�E�X�J�[�\����ݒ�
extern bool ForceDel;				//!< �Ǎ���p�t�@�C���������I�ɏ㏑���E�폜
extern bool RemoveCdReadOnly;		//!< CD-ROM����̃R�s�[���ɓǍ���p����������
extern bool CopyTags;				//!< �^�O���R�s�[
extern bool CopyNoBuffering;		//!< �o�b�t�@�[�Ȃ�I/O���g�p���ăR�s�[
extern bool ShowArcCopyProg;
extern bool DelUseTrash;			//!< �t�@�C���̍폜�ɃS�~�����g��
extern bool EditNewText;			//!< �V�K�e�L�X�g�쐬��ɃG�f�B�^�ŊJ��
extern bool ViewArcInf;				//!< �A�[�J�C�u���̃t�@�C������\��
extern bool CheckTS;				//!< �g���q .ts (MPEG2-TS/TypeScript)�̔��ʂ��s��
extern bool ReloadOnActive;			//!< �A�N�e�B�u���ɍŐV�̏���
extern bool OpenAddedDrive;			//!< �h���C�u���ǉ����ꂽ��J�����g�ɕ\��
extern bool CheckUnc;				//!< UNC�p�X���`�F�b�N
extern bool ShowMsgHint;			//!< �x���Ȃǂ��q���g�\��
extern bool ShowKeyHint;			//!< 2�X�g���[�N����̃q���g�\��
extern bool ShowNoKeyHint;			//!< ������2�X�g���[�N����̌x�����o��
extern bool ShowCopyHint;			//!< �N���b�v�{�[�h�ւ̃R�s�[�����q���g�\��
extern bool ShowDuplNotify;			//!< ��d�N�����ꂽNyanFi����̒ʒm��\��
extern bool ShowTooltip;			//!< �c�[���`�b�v��\��
extern bool LogErrOnly;				//!< �^�X�N�ŃG���[�ӏ��݂̂����O�\��
extern bool LogErrMsg;				//!< ���O�ɃG���[���b�Z�[�W���o��
extern bool LogDebugInf;			//!< ���O�Ƀf�o�b�O�����o��
extern bool LogHideSkip;			//!< ���O�ɃX�L�b�v���ڂ��o�͂��Ȃ�
extern bool LogFullPath;			//!< ���O�̏������e���t���p�X�ŕ\��
extern bool LogDestination;			//!< ���O�ɏ������\��
extern bool SaveLog;				//!< �I�����Ƀ��O��ۑ�
extern bool AppendLog;				//!< �����̃��O�͒ǋL�ۑ�
extern bool NotSortWorkList;		//!< ���[�N���X�g���ڂ��\�[�g���Ȃ�
extern bool RegWorkCsrPos;			//!< �J�[�\���ʒu�ɓo�^
extern bool AutoDelWorkList;		//!< ���݂��Ȃ����ڂ������폜
extern bool NoCheckWorkUnc;			//!< ���[�N���X�g��UNC���`�F�b�N���Ȃ�
extern bool AddToRecent;			//!< �ŋߎg�������ڂɒǉ�
extern bool NoCheckRecentUnc;		//!< UNC�p�X���`�F�b�N���Ȃ�
extern bool DirHistCsrPos;			//!< �f�B���N�g�������ŃJ�[�\���ʒu���L��
extern bool DirHistSortMode;		//!< �f�B���N�g�������Ń\�[�g���@���L��
extern bool DelDplDirHist;			//!< �d������f�B���N�g���������폜
extern bool WorkToDirHist;			//!< ���[�N���X�g�𗚗��Ɋ܂߂�
extern bool NoCheckDirHist;			//!< �f�B���N�g�������̑��݃`�F�b�N���s��Ȃ�
extern bool ExtSaveDirHist;			//!< �S�̗�����ʃt�@�C���ɕۑ�
extern bool LoopFilerCursor;		//!< �t�@�C���[�ŃJ�[�\�������[�v�ړ�
extern bool FlCursorVisible;		//!< �t�@�C���[�ŃJ�[�\������ɉ��̈��
extern bool AutoCompComboBox;		//!< �R���{�{�b�N�X���͂������⊮
extern bool DialogCenter;			//!< �_�C�A���O�����C����ʂ̒�����
extern bool InhbitAltMenu;			//!< ALT�L�[�Ń��j���[�Ƀt�H�[�J�X���Ȃ�
extern bool SelectByMouse;			//!< �}�E�X�Ńt�@�C���[�̍��ڂ�I��
extern bool SelectBaseOnly;			//!< �t�@�C�����啔�ł̂ݑI��
extern bool SelectIconSngl;			//!< �A�C�R�������ŌʂɑI��
extern bool TimColEnabled;			//!< �^�C���X�^���v�̔z�F��L��
extern bool PriorFExtCol;			//!< �g���q�����͑����F���D��
extern bool ColorOnlyFExt;			//!< �g���q�ʔz�F�͊g���q�����݂̂ɓK�p
extern bool SymColorToName;			//!< �t�@�C�����啔�ɃV���{���b�N�����N�F��K�p
extern bool RevTagColor;			//!< �^�O�F�̔��]�\��
extern bool InactiveGray;			//!< ��A�N�e�B�u�ȃ��C����ʂ̈ꕔ���O���[��
extern bool ShowMainMenu;			//!< ���C�����j���[��\��
extern bool ShowImgPreview;			//!< �C���[�W�v���r���[��\��
extern bool ShowProperty;			//!< �t�@�C������\��
extern bool ShowLogWin;				//!< ���O�E�B���h�E��\��
extern bool ShowFileListOnly;		//!< �t�@�C�����X�g�݂̂�\��
extern bool ShowFileListOnly2;
extern bool ShowSttBar;				//!< �X�e�[�^�X�o�[��\��
extern bool ShowToolBar;			//!< �c�[���o�[��\��(�t�@�C���[)
extern bool ShowToolBarV;			//!< �c�[���o�[��\��(�e�L�X�g�r���[�A)
extern bool ShowToolBarI;			//!< �c�[���o�[��\��(�C���[�W�r���[�A)
extern bool ToolBarISide;			//!< �c�[���o�[���T�C�h�o�[��ɕ\��(�C���[�W�r���[�A)
extern bool ShowTabBar;				//!< �^�u�o�[��\��
extern bool ShowFKeyBar;			//!< �t�@���N�V�����L�[�o�[��\��
extern bool ShowClsTabBtn;			//!< �^�u�̕���{�^����\��
extern bool ShowPopTabBtn;			//!< �^�u�́��{�^����\��
extern bool ShowPopDirBtn;			//!< �f�B���N�g�����́��{�^����\��
extern bool HideScrBar;				//!< �c�X�N���[���o�[���B��
extern bool ShowByteSize;			//!< �o�C�g�P�ʕ\��
extern bool ShowTargetInf;			//!< ���̂̏��ŕ\��
extern bool ShowHeader;				//!< �w�b�_��\��
extern bool FixListWidth;			//!< ���X�g�����Œ�
extern bool KeepOnResize;			//!< �E�B���h�E�T�C�Y�ύX���ɔ䗦���ێ�
extern bool KeepCurListWidth;		//!< �J�����g���̃��X�g�����ێ�
extern bool NoSpaceFExt;			//!< �g���q�𕪗����Ȃ�
extern bool HideTitleMenu;			//!< �ő剻���Ƀ^�C�g���o�[�ƃ��j���[���B��
extern bool ShowLineNo;				//!< �s�ԍ���\��
extern bool ShowLineCursor;			//!< �s�J�[�\����\��
extern bool ShowTAB;				//!< �^�u��\��
extern bool ShowCR;					//!< ���s��\��
extern bool ShowIndent;				//!< �C���f���g�K�C�h��\��
extern bool ShowTextRuler;			//!< ���[����\��
extern bool ShowSticky;				//!< �X�e�B�b�L�[��\��
extern bool ScrBarToFoldPos;		//!< �X�N���[���o�[��܂�Ԃ��ʒu�ɕ\��
extern bool TxtSttIsBottom;			//!< ���w�b�_�������ɕ\��(TV)
extern bool ChkAozora;				//!< �󕶌Ɍ`�����l������
extern bool UseXd2tx;				//!< xd2txlib.dll �Ńe�L�X�g�\��
extern bool ClickableUrl;			//!< �_�u���N���b�N��URL���J��
extern bool RestoreViewLine;		//!< �r���[�A�ŃJ�[�\���̍s�ʒu�𕜌�
extern bool EmpComment;				//!< �R�����g�������\��
extern bool EmpStrings;				//!< ������������\��
extern bool EmpReserved;			//!< �\���������\��
extern bool EmpSymbol;				//!< �V���{���������\��
extern bool EmpNumeric;				//!< ���l�������\��
extern bool EmpHeadline;			//!< ���o���������\��
extern bool EmpRuby;				//!< ���r�������\��
extern bool RotViewImg;				//!< Exif���ɂ��������ĉ摜����]
extern bool KeepZoomRatio;			//!< �ʂ̉摜�Ɉڂ������ɃY�[���{�����ێ�����
extern bool ShowThumbName;			//!< �T���l�C���Ƀt�@�C������\��
extern bool ShowThumbExif;			//!< �T���l�C���ɊȈ�Exif����\��
extern bool ShowThumbTags;			//!< �T���l�C���Ƀ^�O��\��
extern bool ShowThumbFExt;			//!< �T���l�C���Ɋg���q�������\��
extern bool NotThumbIfArc;			//!< �A�[�J�C�u���͈ꊇ�擾���Ȃ�
extern bool CacheThumbADS;			//!< �T���l�C����ADS�ɃL���b�V������
extern bool LoopViewCursor;			//!< �C���[�W�r���[�A�ŃJ�[�\�������[�v�ړ�
extern bool HintTopEndImg;			//!< �擪�E�Ō�Ńq���g�\��
extern bool BeepTopEndImg;			//!< �x����
extern bool ImgSttIsBottom;			//!< ���w�b�_�������ɕ\��(IV)
extern bool SeekBindDir;			//!< �V�[�N�o�[�̎n�_��Ԃ������ɍ��킹��
extern bool SeekSwapNxtPrv;			//!< �E�Ԃ���Next/PrevFile����
extern bool HideCsrInFull;			//!< �S��ʕ\���Ń}�E�X�J�[�\�����B��
extern bool HideThumbInFull;		//!< �S��ʕ\���ŃT���l�C�����B��
extern bool AnimateGif;				//!< �C���[�W�r���[�A�ŃA�j���[�V����GIF��\��
extern bool ShowThumbScroll;		//!< �T���l�C���̃X�N���[���o�[��\��
extern bool ShowHistogram;			//!< �q�X�g�O������\��
extern bool ShowLoupe;				//!< ���[�y��\��
extern bool ShowSubViewer;			//!< GIF�r���[�A��\��
extern bool ShowSeekBar;			//!< �V�[�N�o�[��\��
extern bool WarnHighlight;			//!< ����ьx��
extern bool DoublePage;				//!< ���J���\��
extern bool RightBind;				//!< �E�Ԃ�

extern UnicodeString JpWrapChar1;	//!< �s���֑�����
extern UnicodeString JpWrapChar2;	//!< �s���֑�����
extern bool WordWrap;				//!< ���[�h���b�v

extern bool PermitDotCmds;			//!< .nyanfi �ŃR�}���h���s������
extern bool InheritDotNyan;			//!< ��ʃf�B���N�g������ .nyanfi ���p��
extern bool DotNyanPerUser;			//!< ���[�U���ʂ� .nyanfi ���쐬
extern int  InitialModeI;			//!< �C���[�W�r���[�A���J�������̏������
extern int  LastZoomRatio;			//!< �O��̃Y�[��

extern bool MarkImgClose;			//!< �C���[�W�r���[�A����鎞�ɞx�}�[�N��ݒ�
extern UnicodeString MarkImgPath;	//!< �}�[�N����p�X
extern UnicodeString MarkImgFExt;	//!< �}�[�N����g���q
extern UnicodeString MarkImgMemo;

extern int  IconMode;				//!< �A�C�R���̕\�����[�h		0:��\��/ 1:�\��/ 2:�f�B���N�g���̂ݕ\��
extern int  ScrBarStyle;			//!< �X�N���[���o�[�E�X�^�C��	0:�W��/ 1:�V���v��/ 2:3/4��/ 3:1/2��/ 4:�摜

extern bool ModalScreen;			//!< ���[�_���\������
extern int  ModalScrAlpha;			//!< �X�N���[���̓����x
extern TColor col_ModalScr;			//!< ���[�_���\�����ʐF

extern TColor col_bgOptTab;			//!< �A�N�e�B�u�Ȑݒ�^�u�̔w�i�F
extern TColor col_fgOptTab;			//!< �A�N�e�B�u�Ȑݒ�^�u�̕����F

extern int TlWinBorderWidth;		//!< �c�[���E�C���h�E�̋��E����

extern UnicodeString DlgMoveShift;	//!< �_�C�A���O�ړ��̃V�t�g�L�[
extern UnicodeString DlgSizeShift;	//!< �_�C�A���O�̃T�C�Y�ύX�̃V�t�g�L�[
extern int DlgMovePrm;
extern int DlgSizePrm;

extern int DblClickFlMode;				//!< �t�@�C�����X�g�ł̃_�u���N���b�N

extern UnicodeString WheelCmdF[4];		//!< �z�C�[���R�}���h
extern UnicodeString WheelCmdV[4];
extern UnicodeString WheelCmdI[4];

extern UnicodeString WheelBtnCmdF[4];	//!< �z�C�[���{�^�����������Ƃ��̃R�}���h
extern UnicodeString WheelBtnCmdV;
extern UnicodeString WheelBtnCmdI;

extern UnicodeString X1BtnCmdF;			//!< X1�{�^�����������Ƃ��̃R�}���h
extern UnicodeString X2BtnCmdF;			//!< X2�{�^�����������Ƃ��̃R�}���h
extern UnicodeString X1BtnCmdV;
extern UnicodeString X2BtnCmdV;
extern UnicodeString X1BtnCmdI;
extern UnicodeString X2BtnCmdI;

extern UnicodeString EmpBinPtn1;		//!< �o�C�i�������p�^�[��1
extern UnicodeString EmpBinPtn2;		//!< �o�C�i�������p�^�[��2
extern UnicodeString EmpBinPtn3;		//!< �o�C�i�������p�^�[��3

extern UnicodeString HtmInsHrCls;		//!< �u���b�N�̑O�Ɍr����}������N���X
extern UnicodeString HtmHdrStr;			//!< ���o������
extern bool HtmInsHrSct;				//!< <section>�̑O�Ɍr���}��
extern bool HtmInsHrArt;				//!< <article>�̑O�Ɍr���}��
extern bool HtmInsHrNav;				//!< <nav>�̑O�Ɍr���}��
extern bool ToMarkdown;					//!< Markdown�L�@�ɕϊ�
extern UnicodeString HtmDelBlkCls;		//!< �폜����u���b�N�� class
extern UnicodeString HtmDelBlkId;		//!< �폜����u���b�N�� id

extern UnicodeString NoWatchPath;		//!< �f�B���N�g���Ď����珜�O����p�X

extern UnicodeString FExtGetInf;		//!< �t�@�C�������擾����g���q
extern UnicodeString FExtNoInf;			//!< �t�@�C�������擾���Ȃ��g���q
extern UnicodeString NoInfPath;			//!< �t�@�C�������擾���Ȃ��p�X
extern UnicodeString EmpInfItems;		//!< �����\������t�@�C����񍀖�(|��؂�)
extern TStringList  *HideInfItems;		//!< �B���t�@�C����񍀖�(�g���q=|��؂�`���̃��X�g)

extern UnicodeString FExtImgPrv;		//!< �C���[�W�v���r���[���s���g���q
extern UnicodeString FExtNoImgPrv;		//!< �C���[�W�v���r���[���s��Ȃ��g���q
extern UnicodeString NoImgPrvPath;		//!< �C���[�W�v���r���[���s��Ȃ��p�X���X�g

extern UnicodeString FExtNoIView;		//!< �C���[�W�r���[�A�ŉ{�����Ȃ��g���q
extern UnicodeString NoCachePath;		//!< �T���l�C���L���b�V�����Ȃ��p�X

extern UnicodeString DrvInfFmtR;		//!< �h���C�u���̏��� : ���[�g
extern UnicodeString DrvInfFmtS;		//!< �h���C�u���̏��� : �I����
extern UnicodeString DrvInfFmtN;		//!< �h���C�u���̏��� : ���̑�

extern UnicodeString SttBarFmt;			//!< �X�e�[�^�X�o�[�̏���
extern UnicodeString SttClockFmt;		//!< ���v�̏���

extern int  MaxLogFiles;				//!< ���O�t�@�C���̕ۑ����㐔
extern int  MaxDirHistory;				//!< �f�B���N�g�������̕ۑ���

extern int  ProtectDirMode;				//!< �f�B���N�g���̍폜�������[�h
extern bool ProtectSubDir;				//!< ���ʃf�B���N�g��������
extern bool ProtectFile;				//!< �t�@�C��������

extern bool WarnPowerFail;				//!< �d���ؒf�x��
extern bool WarnDisconnect;				//!< �C���^�[�l�b�g�ڑ��؂�
extern bool WarnLowBattery;				//!< �o�b�e���[�ቺ
extern int  BatLowerLimit;

extern int  BorderMoveWidth;			//!< BorderLeft�ABorderRight: �P��̈ړ���
extern UnicodeString AutoRenFmt;		//!< Copy�AMove: �������̎�����������
extern int  RemoteWaitTime;				//!< �R�[���o�b�N���̃E�F�C�g�^�C��
extern int  NormalWaitTime;
extern int  NopDtctTime;				//!< �����삾�Ƃ݂Ȃ�����
extern int  TimeTolerance;				//!< �^�C���X�^���v�̋��e�덷

extern bool AppListChgMin;				//!< AppList:   ���A�v���ɐ؂�ւ����Ƃ��ɍŏ���
extern bool CreDirChg;					//!< CreateDir: �f�B���N�g���쐬��ɃJ�����g�ύX
extern bool CreDirCnvChar;				//!< CreateDir: �����u����K�p
extern UnicodeString FExtExeFile;		//!< ExeCommandLine: ���s�t�@�C���Ƃ݂Ȃ��g���q
extern bool OpenOnlyCurEdit;			//!< FileEdit:  �I����Ԃɂ�����炸�J�[�\���ʒu�݂̂��J��
extern bool DontClrSelEdit;				//!< FileEdit:  �I�����������Ȃ�
extern int  OpenByMode;					//!< OpenByApp:  �֘A�t������Ă��Ȃ��ꍇ�̓��샂�[�h
extern bool OpenDirByStd;				//!< OpenByApp:  �f�B���N�g���ł͕W�� Enter �L�[����
extern bool OpenOnlyCurApp;				//!< OpenByApp:  �I����Ԃɂ�����炸�J�[�\���ʒu�݂̂��J��
extern bool DontClrSelApp;				//!< OpenByApp:  �I�����������Ȃ�
extern bool OpenOnlyCurWin;				//!< OpenByWin:  �I����Ԃɂ�����炸�J�[�\���ʒu�݂̂��J��
extern bool DontClrSelWin;				//!< OpenByWin:  �I�����������Ȃ�
extern bool OpenStdTabGroup;			//!< OpenStandard: �^�u�O���[�v���J��
extern bool OpenStdMenuFile;			//!< OpenStandard: ���j���[�t�@�C�����J��
extern bool OpenStdResultList;			//!< OpenStandard: ���ʃ��X�g���J��
extern bool OpenStdFindSet;				//!< OpenStandard: �����ݒ���J��
extern bool DownAfterOpenStd;			//!< OpenStandard: ���s��ɃJ�[�\�������Ɉړ�
extern bool OpenStdOnResList;			//!< OpenStandard: ���ʃ��X�g�ł��ʏ퓮��
extern UnicodeString IniSeaShift;		//!< IniSearch:  �������T�[�`�̃V�t�g�L�[
extern bool IniSeaByNum;				//!<   �����L�[�ł��������T�[�`
extern bool IniSeaBySign;				//!<   Shift+�����L�[�̋L�����T�[�`
extern bool IncSeaCaseSens;				//!< IncSearch: �召���������
extern bool IncSeaFuzzy;				//!< IncSearch: �����܂�����
extern bool IncSeaLoop;					//!< IncSearch: �㉺�[�Ń��[�v
extern bool IncSeaMatch1Exit;			//!< IncSearch: �}�b�`��1�Ŕ�����
extern int  IncSeaMigemoMin;			//!< IncSearch: Migemo �̌����J�n������
extern bool SyncItem;					//!< SyncLR : ���ڈʒu������
extern bool NotShowNoTask;				//!< TaskMan: �^�X�N�����s���Ă��Ȃ��Ƃ��̓}�l�[�W����\�����Ȃ�
extern UnicodeString GetFaviconUrl;		//!< favicon �擾API

extern bool FindPathColumn;				//!< ���ʃ��X�g�Ɂu�ꏊ�v���\��
extern int  FindPathWidth;				//!< �u�ꏊ�v�̍ŏ���
extern bool FindTagsColumn;				//!< ���ʃ��X�g�Ɂu�^�O�v���\��
extern int  FindTagsWidth;				//!< �u�^�O�v�̍ŏ���

extern bool GrepNotUpdList;				//!< GREP�������Ɍ��ʃ��X�g���X�V���Ȃ�
extern bool RepNotUpdList;				//!< �ꊇ�u�����Ɍ��ʃ��X�g���X�V���Ȃ�
extern bool GrepShowItemNo;				//!< GREP���ʂɍ��ڔԍ���\��
extern bool GrepFileItemNo;				//!< ���ڔԍ����t�@�C���P�ʂŕ\��
extern bool GrepShowSubDir;				//!< GREP���ʂɃT�u�f�B���N�g������\��
extern bool GrepTrimTop;				//!< GREP���ʂōs���̃^�u��󔒂��폜
extern bool GrepOmitTop;				//!< GREP���ʂŃ}�b�`�ꂪ�����Ȃ��Ƃ��O�������ȗ�
extern bool GrepEmFilter;				//!< GREP���ʂŃt�B���^�̌�������\��
extern bool GrepAdjNextLn;				//!< GREP���ʂŎ��s�\�������̖��x������
extern int  GrepOutMode;				//!< GREP �o�͐�	0:����/ 1:�t�@�C��/ 2:�N���b�v�{�[�h
extern UnicodeString GrepFileName;		//!< �o�̓t�@�C����
extern UnicodeString GrepAppName;		//!< �N���A�v����
extern UnicodeString GrepAppParam;		//!< �A�v���̋N���p�����[�^
extern UnicodeString GrepAppDir;		//!< �A�v���̍�ƃf�B���N�g��
extern bool GrepAppEnabled;				//!< �A�v���L��
extern bool GrepAppend;					//!< �����t�@�C���ɒǉ�
extern UnicodeString GrepFileFmt;		//!< �t�@�C�����̏���
extern UnicodeString GrepInsStrW;		//!< �}�b�`��O�̑}��������
extern UnicodeString GrepInsStrW2;		//!< �}�b�`���̑}��������
extern bool GrepTrimLeft;				//!< �s���̃^�u��󔒂��폜
extern bool GrepReplaceTab;				//!< �^�u����1�����ɒu��
extern bool GrepReplaceCr;				//!< ���s�𕶎���ɒu��
extern UnicodeString GrepRepCrStr;		//!< ���s�̒u��������
extern bool BackupReplace;				//!< �u���o�b�N�A�b�v�쐬
extern UnicodeString FExtRepBackup;		//!< �u���o�b�N�A�b�v�̊g���q
extern UnicodeString RepBackupDir;		//!< �u���o�b�N�A�b�v��
extern UnicodeString ReplaceLogName;	//!< �u�����O�t�@�C����
extern bool SaveReplaceLog;				//!< �u�����O��ۑ�
extern bool ReplaceAppend;				//!< �����t�@�C���ɒǉ�
extern bool OpenReplaceLog;				//!< ���O���e�L�X�g�G�f�B�^�ŊJ��

extern UnicodeString UserName;			//!< ���[�U��
extern UnicodeString TempPath;			//!< �ꎞ�f�B���N�g��
extern UnicodeString TempPathA;			//!< �ꎞ�f�B���N�g��(���)
extern UnicodeString TempPathFTP;		//!< FTP�p�ꎞ�f�B���N�g��(���)

extern UnicodeString DownloadPath;		//!< �_�E�����[�h�p
extern UnicodeString LibraryPath;		//!< ���C�u����
extern UnicodeString WorkListPath;		//!< ���[�N���X�g�Q�ƃp�X
extern UnicodeString ResultListPath;	//!< ���ʃ��X�g�Q�ƃp�X
extern UnicodeString ListFilePath;		//!< ���X�g�t�@�C���Q�ƃp�X
extern UnicodeString FindSetPath;		//!< �������ʎQ�ƃp�X
extern UnicodeString RefParamPath;		//!< �p�����[�^�Q�ƃp�X
extern UnicodeString CmdFilePath;		//!< �R�}���h�t�@�C���Q�ƃp�X
extern UnicodeString CmdGitExe;			//!< git.exe
extern UnicodeString GitBashExe;		//!< git-bash.exe
extern UnicodeString GitGuiExe;			//!< git-gui.exe
extern UnicodeString CmdGrepExe;		//!< grep.exe

extern int VersionNo;
extern UnicodeString VersionStr;		//!< �o�[�W�����\��
extern UnicodeString OSVerInfStr;		//!< OS�o�[�W�������
extern bool IsWin11;					//!< Windows 11 ���H

extern UnicodeString DirBraStr;			//!< �f�B���N�g�����ʕ���
extern UnicodeString DirKetStr;
extern UnicodeString TimeStampFmt;		//!< �^�C���X�^���v�̕\������

extern UnicodeString CallHotKey;		//!< �Ăяo���z�b�g�L�[
extern UnicodeString AppListHotKey;		//!< �A�v���ꗗ�z�b�g�L�[
extern UnicodeString AppListHotPrm;		//!< �A�v���ꗗ�p�����[�^

extern UnicodeString SaveTxtPath;		//!< �e�L�X�g�ۑ��p�X
extern int SaveEncIndex;				//!< �G���R�[�f�B���O�̃C���f�b�N�X

extern UnicodeString NoDirHistPath;		//!< �f�B���N�g�������ɓ���Ȃ��p�X
extern UnicodeString NoEditHistPath;	//!< �ҏW�����ɓ���Ȃ��p�X
extern UnicodeString NoViewHistPath;	//!< �{�������ɓ���Ȃ��p�X
extern UnicodeString NoRepoListPath;	//!< ���|�W�g���ꗗ�ɕ\�����Ȃ��p�X

extern UnicodeString DirDelimiter;		//!< �f�B���N�g����؂�̕\������

extern bool NoCheckUncRPT;				//!< UNC�p�X�̃��p�[�X�|�C���g�����`�F�b�N���Ȃ�

extern int  InactiveAdjust;				//!< ��A�N�e�B�u���O���[���̍ł̉����l

extern int CurTabIndex;					//!< �^�u�C���f�b�N�X(0�`)

extern UnicodeString CurPathName;
extern int CurListTag;					//!< �J�����g���^�O  0:��/ 1:�E
extern int OppListTag;					//!< ���Α��^�O
extern int LastCurTag;					//!< �O��I�����̃J�����g
extern int WorkingTag;					//!< ��Ƒ��̃^�O(CurWorking = true ��)

extern UnicodeString FTPTextModeFExt;	//!< �e�L�X�g���[�h�œ]������g���q
extern bool FTPDlKeepTime;				//!< �_�E�����[�h�t�@�C���̃^�C���X�^���v���ێ�
extern bool FTPUpKeepTime;				//!< �A�b�v���[�h�t�@�C���̃^�C���X�^���v���ێ�
extern bool FTPUpToLower;				//!< �t�@�C�����������������ăA�b�v���[�h����
extern bool FTPLogResponse;				//!< �������b�Z�[�W�����O�ɕ\��
extern int  FTPRemoteSide;				//!< �����[�g�� 0:�J�����g/ 1:��/ 2:�E
extern int  FTPDisconTimeout;			//!< FTP��������̏ꍇ�ؒf���鎞��

extern UnicodeString FTPSndConnect;		//!< �ڑ����̒ʒm��
extern UnicodeString FTPSndDiscon;		//!< �ؒf���̒ʒm��
extern UnicodeString FTPSndTransfer;	//!< �]���������̒ʒm��

extern UnicodeString FTPPathName;

extern TListBox *FileListBox[MAX_FILELIST];		//!< �t�@�C�����X�g�{�b�N�X
extern TPanel	*FileListPanel[MAX_FILELIST];

extern UnicodeString ViewFileName;		//!< �\�����̃t�@�C����
extern UnicodeString ViewFileName2;
extern bool ViewFromArc;				//!< �A�[�J�C�u����\��

//---------------------------------------------------------------------------
#define GENLST_FILELIST	1
#define GENLST_DRIVE	2
#define GENLST_CMDSLIST	3
#define GENLST_TABLIST	4
#define GENLST_ICON		5
#define GENLST_FONT		6

extern TStringList *GeneralList;		//!< TStringList �̃��X�g(�ꊇ�j���p)

//---------------------------------------------------------------------------
/** @defgroup FILELIST �t�@�C�����X�g�̑��� */
/** @{ */
extern TStringList *FileList[MAX_FILELIST];			//!< �t�@�C�����X�g
extern TStringList *ArcFileList[MAX_FILELIST];		//!< ���z�f�B���N�g���̃t�@�C�����X�g
extern TStringList *AdsFileList[MAX_FILELIST];		//!< ��փf�[�^�X�g���[���̃t�@�C�����X�g
extern TStringList *ResultList[MAX_FILELIST];		//!< �������ʃ��X�g
extern TStringList *SelMaskList[MAX_FILELIST];		//!< �I���}�X�N���X�g
extern TStringList *TmpBufList[MAX_FILELIST];		//!< �ꎞ�ޔ����X�g
/** @} */

extern TStringList *DriveInfoList;		//!< �h���C�u���
extern TStringList *DriveLogList;		//!< �h���C�u�e�ʃ��O
extern UnicodeString DriveLogName;		//!< �h���C�u�e�ʃ��O�̃t�@�C����

extern TStringList *WatchTailList;		//!< �����Ď����X�g
extern UnicodeString LastWatchLog;		//!< ���O�̊Ď����O

extern TStringList *InvalidUncList;		//!< ������UNC���X�g

extern TStringList *GitCfgUrlList;		//!< .Git\config - URL �Ή����X�g (�t�@�C����=URL \t yyyy/mm/dd hh:nn:ss)
extern TStringList *GitInfList;			//!< Git���̃L���b�V��

extern TStringList *TabList;			//!< �^�u���X�g
extern TStringList *TabBuff;			//!< �Œ蕜�A�p�o�b�t�@
extern int FlTabWidth;					//!< �^�u�̕�
extern int FlTabStyle;					//!< �^�u�̃X�^�C��
extern UnicodeString TabGroupName;		//!< �^�u�O���[�v�E�t�@�C����

extern TStringList *CachedIcoList;		//!< �t�@�C���ŗL�A�C�R���̃L���b�V�� (IconRWLock �ŕی삷�邱��)
extern TMultiReadExclusiveWriteSynchronizer *IconRWLock;
extern int IconCache;					//!< �A�C�R���L���V����

extern UsrIniFile  *FolderIconFile;		//!< �t�H���_�A�C�R���ݒ�t�@�C��
extern TStringList *FolderIconList;		//!< �t�H���_�A�C�R�����X�g
extern TMultiReadExclusiveWriteSynchronizer *FldIcoRWLock;
extern UnicodeString DefFldIcoName;		//!< �f�t�H���g�̃t�H���_�A�C�R��
extern HICON hLinkIcon;					//!< �����N�}�[�N(Shell32.dll,29)

extern TStringList *GeneralIconList;	//!< �t�@�C�����X�g�\���p�̈�ʃA�C�R��
extern TStringList *MenuBtnIcoList;
extern TStringList *UsrIcoList;			//!< ���j���[�A�c�[���{�^���p�A�C�R��
extern TStringList *DrvIcoList;			//!< �h���C�u�̃A�C�R�����X�g

extern TStringList *BakSetupList;		//!< �o�b�N�A�b�v�ݒ胊�X�g
extern TStringList *SyncDirList;		//!< �����R�s�[�惊�X�g
extern TStringList *AssRenList;			//!< �֘A�t�@�C�����������ݒ胊�X�g
extern TStringList *DistrDefList;		//!< �U�蕪�����`���X�g

extern TStringList *GrepPathList;		//!< GREP �Ώۃp�X�̃��X�g
extern TStringList *GrepFileList;		//!< GREP �Ώۃt�@�C�����X�g
extern TStringList *GrepResultBuff;		//!< GREP ���ʃ��X�g�\���p�o�b�t�@
extern TStringList *GrepResultList;		//!< GREP �̌��ʃ��X�g
extern TStringList *GrepStashBuff;		//!< GREP ���ʂ̑ޔ��o�b�t�@
extern TStringList *GrepUnsortBuff;		//!< GREP �\�[�g�O�o�b�t�@
extern TStringList *GrepMatchList;		//!< GREP �t�@�C���ʃ}�b�`�����X�g
extern int  ResultListMode;				//!< ���ʃ��X�g�̓��e	0:����/ 1:GREP/ 2:�u��

extern TStringList *ViewFileList;		//!< �C���[�W�r���[�A�ł̃t�@�C�������X�g
extern bool isViewIcon;					//!< �C���[�W�r���[�A�ŃA�C�R����\����
extern bool isViewAGif;					//!< �C���[�W�r���[�A�ŃA�j���[�V����GIF��\����
extern bool isViewClip;					//!< �C���[�W�r���[�A�ŃN���b�v�{�[�h��\����
extern bool isViewFTP;					//!< �C���[�W�r���[�A��FTP�̃t�@�C����\����
extern bool rqThumbnail;				//!< �N���b�v�{�[�h/FTP�{����̃T���l�C�����A�v��
extern bool nrmThumbnail;				//!< �ʏ��ʎ��̃T���l�C���\��

extern TStringList *LaunchList;			//!< �����`���[���X�g(�A�v���P�[�V�����ꗗ)

extern UnicodeString PathMask[MAX_FILELIST];	//!< �p�X�}�X�N
extern UnicodeString DriveInf[MAX_FILELIST];	//!< �h���C�u���

extern TStringList *WorkList;			//!< ���[�N���X�g
extern UnicodeString WorkListName;		//!< ���[�N���X�g�̃t�@�C����
extern TDateTime WorkListTime;			//!< ���[�N���X�g�̃^�C���X�^���v
extern bool WorkListChanged;			//!< ���[�N���X�g�̓��e���ύX���ꂽ
extern bool WorkListFiltered;			//!< ���[�N���X�g�Ƀt�B���^���K�p����Ă���
extern bool WorkListHasSep;				//!< ���[�N���X�g�ɃZ�p���[�^������
extern bool rqWorkListDirInf;			//!< ���[�N���X�g�̃f�B���N�g�����X�V��v��

extern TStringList *PlayList;			//!< �v���C���X�g
extern UnicodeString PlayListFile;		//!< �v���C���X�g�̃t�@�C����
extern UnicodeString PlayFile;			//!< �Đ����t�@�C����
extern int  PlayStbIdx;
extern bool PlayRepeat;					//!< ���s�[�g�Đ�
extern bool PlayShuffle;				//!< �V���b�t���Đ�
extern bool ListShuffled;				//!< �V���b�t�����ꂽ

extern int  IniPathMode[MAX_FILELIST];				//!< �N�����p�X���[�h
extern UnicodeString InitialPath[MAX_FILELIST];		//!< �N�����p�X
extern UnicodeString InitialMask[MAX_FILELIST];		//!< �N�����}�X�N
extern int  IniSortMode[MAX_FILELIST];				//!< �N�����\�[�g���@

extern int  IniWorkMode;				//!< ���[�N���X�g 0:�O��/ 1:�w��
extern UnicodeString HomeWorkList;

extern TStringList *PopMenuList;		//!< ExeMenuFile �R�}���h�p���j���[����
extern TStringList *ToolBtnList;		//!< �c�[���{�^����`���X�g(�t�@�C���[)
extern TStringList *ToolBtnListV;		//!< �c�[���{�^����`���X�g(�e�L�X�g�r���[�A)
extern TStringList *ToolBtnListI;		//!< �c�[���{�^����`���X�g(�C���[�W�r���[�A)

extern int  IniWinMode;					//!< �T�C�Y���[�h 0:�O��/ 1:�w��
extern int  IniWinLeft, IniWinTop, IniWinWidth, IniWinHeight;
extern bool FixWinPos;					//!< �E�B���h�E�T�C�Y���Œ�
extern bool IniPathToTab1;				//!< �����p�X���^�u1�ɐݒ�
extern bool IniTabHomeAll;				//!< �����p�X�ȊO�̃^�u���z�[���ɖ߂�
extern bool ShowSplash;					//!< �X�v���b�V����\��

//---------------------------------------------------------------------------
/**
 * @defgroup OPTION_EVENT_CMDS �I�v�V�����ݒ� - �C�x���g
 * @brief �C�x���g�������Ɏ��s����R�}���h
*/

/** @{ */
#define MAX_EVENT_CMD	66	//!< �ő�C�x���g��

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
	UnicodeString *sp;	//!< �ϐ��̃|�C���^
	const _TCHAR *key;	//!< �L�[��
	const _TCHAR *dsc;	//!< ����
};

extern const event_rec EventCmdList[MAX_EVENT_CMD];	//!< �C�x���g�R�}���h���X�g

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
extern int  SortMode[MAX_FILELIST];			/**< �t�@�C�����X�g�̃\�[�g���@@n
											 * 0:���O/ 1:�g���q/ 2:�X�V����/ 3:�T�C�Y/ 4:����/ 5:�Ȃ� */
extern int  DirSortMode[MAX_FILELIST];		/**< �f�B���N�g���̃\�[�g���@@n
											 * 0:�t�@�C���Ɠ���/ 1:���O/ 2:�X�V����/ 3:�T�C�Y/ 4:����/
											 * 5:�f�B���N�g������ʂ��Ȃ�/ 6:�t�H���_�A�C�R�� */
extern int  SubSortMode[5];					//!< ��2�\�[�g���[�h
extern int  PrimeSortMode;					//!< ��1�\�[�g���[�h

extern bool FlOdrNatural[MAX_FILELIST];		//!< ���R��
extern bool FlOdrDscName[MAX_FILELIST];		//!< �~��
extern bool FlOdrSmall[MAX_FILELIST];		//!< ��������
extern bool FlOdrOld[MAX_FILELIST];			//!< �Â���
extern bool FlOdrDscAttr[MAX_FILELIST];		//!< �����~��
extern bool FlOdrDscPath[MAX_FILELIST];		//!< �ꏊ�~��

extern bool NaturalOrder;					//!< ��r�֐� - ���R��
extern bool DscNameOrder;					//!< ��r�֐� - ���O�~��
extern bool SmallOrder;						//!< ��r�֐� - ��������
extern bool OldOrder;						//!< ��r�֐� - �Â���
extern bool DscAttrOrder;					//!< ��r�֐� - �����~��
extern bool DscPathOrder;					//!< ��r�֐� - �ꏊ�~��

extern bool TopSymbol;
extern bool SortBoth;						//!< ���E�Ƃ��ύX
extern bool SortLogical;					//!< �_���\�[�g(���R���\�[�g������)
extern UnicodeString SortSymList;
extern UnicodeString SortExtList;			//!< �g���q���ŗD�悷��g���q

extern TStringList *OptionList;				//!< �I�v�V����
extern TStringList *KeyFuncList;			//!< �L�[���蓖��
extern TStringList *FKeyLabelList;			//!< �t�@���N�V�����L�[��
extern TStringList *HotKeyList;				//!< �z�b�g�L�[
extern TStringList *DirStack;				//!< �f�B���N�g���X�^�b�N
extern TStringList *PathMaskList;			//!< �p�X�}�X�N���X�g
extern TStringList *RegDirList;				//!< �o�^�f�B���N�g��
extern TStringList *ProtectDirList;			//!< �폜�����f�B���N�g��
extern TStringList *VirDriveList;			//!< ���z�h���C�u���X�g
extern TStringList *ColorList;				//!< �z�F
extern TStringList *ExtColList;				//!< �g���q�ʔz�F
extern TStringList *AssociateList;			//!< �֘A�t��
extern TStringList *OpenStdCmdList;			//!< OpenStandard �̃R�}���h�֘A�t��
extern TStringList *EtcEditorList;			//!< ���̑��̃G�f�B�^���X�g
extern TStringList *ExtToolList;			//!< �O���c�[��
extern TStringList *ExtMenuList;			//!< �ǉ����j���[
extern TStringList *CommandList;			//!< �R�}���h���X�g
extern TStringList *CmdSetList;				//!< �R�}���h�ꗗ���X�g
extern TStringList *TaskCmdList;			//!< �^�X�N�R�}���h�����X�g
extern TStringList *DriveList;				//!< �ω��Ď��p�h���C�u���X�g
extern TStringList *NetDriveList;			//!< ���ݗL���ȃl�b�g�h���C�u���X�g
extern TStringList *AllDirHistory;			//!< �S�̂̃f�B���N�g������
extern TStringList *TextViewHistory;		//!< �e�L�X�g�{������
extern TStringList *TextEditHistory;		//!< �e�L�X�g�ҏW����
extern TStringList *WorkListHistory;		//!< ���[�N���X�g����
extern TStringList *CopyPathHistory;		//!< �R�s�[�����p�X���̗���
extern TStringList *InputDirHistory;		//!< �f�B���N�g�����̗͂���
extern TStringList *InputCmdsHistory;		//!< �R�}���h���̗͂���(�t�@�C���[)
extern TStringList *InputCmdsHistoryV;		//!< �R�}���h���̗͂���(�e�L�X�g�r���[�A)
extern TStringList *InputCmdsHistoryI;		//!< �R�}���h���̗͂���(�C���[�W�r���[�A)
extern TStringList *IncSeaHistory;			//!< �C���N�������^���T�[�`�̃L�[���[�h����
extern TStringList *FilterHistory;			//!< �t�B���^�̃L�[���[�h����
extern TStringList *WebSeaHistory;			//!< Web������̗���
extern TStringList *LatLngHistory;			//!< �ܓx�o�x�����̗���
extern TStringList *HeadlineList;			//!< ���o�����X�g (�g���q=���K�\���p�^�[��)
extern TStringList *ZoomRatioList;			//!< �Y�[���{�����X�g
extern TStringList *InterpolationList;		//!< �k���E�g��A���S���Y���̃��X�g
extern TStringList *CnvCharList;			//!< �֎~�����^���[�U��`�����ϊ����X�g
extern TStringList *RenCmdFileList;			//!< ���������R�}���h�t�@�C���̃��X�g
extern TStringList *RenArcFileList;			//!< ���������A�[�J�C�u�t�@�C���̃��X�g
extern TStringList *RedrawList;				//!< �`��}�~�p���X�g
extern TStringList *CmdRequestList;			//!< �R�}���h�v�����X�g
extern TStringList *CommandHistory;			//!< �R�}���h����

extern UnicodeString LogBufStr;				//!< �^�X�N����̃��O�����o�b�t�@ (LogRWLock �ŕی삷�邱��)
extern TMultiReadExclusiveWriteSynchronizer *LogRWLock;

extern TListBox     *LogWndListBox;			//!< ���O�E�B���h�E�p���X�g�{�b�N�X
extern TStringList  *LogBufList;			//!< ���O���X�g�{�b�N�X(���z)�p�o�b�t�@
extern UsrScrollPanel *LogWndScrPanel;		//!< �V���v���X�N���[���o�[

extern int  LayoutMode;			//!< ��ʃ��C�A�E�g���[�h
extern bool DivFileListUD;		//!< �t�@�C�����X�g���㉺�ɕ���
extern bool DivDirInfUD;		//!< �f�B���N�g�������㉺�ɕ���

extern TFont *ListFont;			//!< �t�@�C�����X�g��
extern TFont *FileInfFont;		//!< �t�@�C�����
extern TFont *TxtPrvFont;		//!< �e�L�X�g�v���r���[
extern TFont *LogFont;			//!< ���O
extern TFont *ViewerFont;		//!< �e�L�X�g�r���[�A
extern TFont *GrepResFont;		//!< GREP���ʃ��X�g
extern TFont *DirInfFont;		//!< �f�B���N�g�����
extern TFont *DrvInfFont;		//!< �h���C�u���
extern TFont *LstHdrFont;		//!< �ꗗ�̃w�b�_
extern TFont *ViewHdrFont;		//!< �r���[�A���w�b�_
extern TFont *GenListFont;		//!< �ꗗ�_�C�A���O
extern TFont *HintFont;			//!< �q���g
extern TFont *SttBarFont;		//!< �X�e�[�^�X�o�[
extern TFont *CalcFont;			//!< �d��
extern TFont *ToolBarFont;		//!< �c�[���o�[
extern TFont *TabBarFont;		//!< �^�u�o�[
extern TFont *CharInfFont;		//!< �������
extern TStringList *FontList;	//!< �J���[

/** @defgroup GLOBAL_COLORS �z�F */
/** @{ */
/** @defgroup OPTION_COLORS �I�v�V�����ݒ� */
/** @{ */
extern TColor col_bgList;		//!< �ꗗ�̔w�i�F
extern TColor col_bgList2;		//!< �ꗗ�̔w�i�F(����)
extern TColor col_fgList;		//!< �ꗗ�̕����F
extern TColor col_Splitter;		//!< �������E��
extern TColor col_bgArc;		//!< ���z�f�B���N�g���̔w�i�F
extern TColor col_bgFind;		//!< �������ʃ��X�g�̔w�i�F
extern TColor col_bgWork;		//!< ���[�N���X�g�̔w�i�F
extern TColor col_bgFTP;		//!< FTP�����[�g���̔w�i�F
extern TColor col_bgADS;		//!< ��փf�[�^�X�g���[���ꗗ�̔w�i�F
extern TColor col_selItem;		//!< �I�����ڂ̔w�i�F
extern TColor col_oppItem;		//!< ���΃p�X�I�����ڂ̔w�i�F
extern TColor col_fgSelItem;	//!< �I�����ڂ̕����F
extern TColor col_bgMark;		//!< �x�}�[�N���ڂ̔w�i�F
extern TColor col_matchItem;	//!< INC.�T�[�`�̃}�b�`���ڔw�i�F
extern TColor col_Differ;		//!< ���ʃ��X�g�̑���ӏ��w�i�F
extern TColor col_DifferN;		//!< ���ʃ��X�g�̒��ډӏ��w�i�F
extern TColor col_Cursor;		//!< ���C���J�[�\���̐F
extern TColor col_bgScrBar;		//!< �V���v���X�N���[���o�[�̔w�i�F
extern TColor col_bgScrKnob;	//!< �V���v���X�N���[���m�u�̐F
extern TColor col_frScrKnob;	//!< �V���v���X�N���[���m�u�̗֊s�F
extern TColor col_bgActKnob;	//!< �h���b�O���̃V���v���X�N���[���m�u�F
extern TColor col_lnScrHit;		//!< �V���v���X�N���[���o�[�̃q�b�g�s�F
extern TColor col_lnScrSel;		//!< �V���v���X�N���[���o�[�̑I���s�F
extern TColor col_Folder;		//!< �f�B���N�g���̕����F
extern TColor col_SymLink;		//!< �V���{���b�N�����N/�W�����N�V�����̕����F
extern TColor col_Protect;		//!< �폜�����f�B���N�g���̕����F
extern TColor col_ReadOnly;		//!< �ǂݍ��ݐ�p�����̕����F
extern TColor col_Compress;		//!< ���k�����̕����F
extern TColor col_Hidden;		//!< �B�������̕����F
extern TColor col_System;		//!< �V�X�e�������̕����F
extern TColor col_fgSpace;		//!< �󔒋L���̕����F
extern TColor col_fgTagNam;		//!< �f�t�H���g�̃^�O�F
extern TColor col_InvItem;		//!< �����ȍ��ڂ̕����F
extern TColor col_bgTabBar;		//!< �^�u�o�[�̔w�i�F
extern TColor col_bgActTab;		//!< �A�N�e�B�u�ȃ^�u�̔w�i�F
extern TColor col_bgInAcTab;	//!< ��A�N�e�B�u�ȃ^�u�̔w�i�F
extern TColor col_frmTab;		//!< �^�u�̗֊s�F
extern TColor col_fgTab;		//!< �^�u�̕����F
extern TColor col_bgListHdr;	//!< ���X�g�w�b�_�̔w�i�F
extern TColor col_fgListHdr;	//!< ���X�g�w�b�_�̕����F
extern TColor col_bgDirInf;		//!< �f�B���N�g�����̔w�i�F
extern TColor col_fgDirInf;		//!< �f�B���N�g�����̕����F
extern TColor col_bgDirRel;		//!< �f�B���N�g���֌W�̔w�i�F
extern TColor col_fgDirRel;		//!< �f�B���N�g���֌W�̕����F
extern TColor col_bdrDirB;		//!< �f�B���N�g�����̉����E��
extern TColor col_bgDrvInf;		//!< �h���C�u���̔w�i�F
extern TColor col_fgDrvInf;		//!< �h���C�u���̕����F
extern TColor col_bdrDrvT;		//!< �h���C�u���̏㋫�E��
extern TColor col_bgInf;		//!< �t�@�C�����̔w�i�F
extern TColor col_fgInf;		//!< �t�@�C�����̕����F
extern TColor col_fgInfNam;		//!< �t�@�C�����̍��ږ������F
extern TColor col_fgInfEmp;		//!< �t�@�C�����̋��������F
extern TColor col_bgTxtPrv;		//!< �e�L�X�g�v���r���[�̔w�i�F
extern TColor col_fgTxtPrv;		//!< �e�L�X�g�v���r���[�̕����F
extern TColor col_bgLog;		//!< ���O�̔w�i�F
extern TColor col_fgLog;		//!< ���O�̕����F
extern TColor col_bgTask;		//!< �^�X�N��ԕ\���̔w�i�F
extern TColor col_fgPrgBar;		//!< �^�X�N�i���o�[�F
extern TColor col_bgPrgBar;		//!< �^�X�N�i���w�i�F
extern TColor col_Error;		//!< �G���[/���ӂ̕����F
extern TColor col_TlBorder;		//!< �c�[���E�C���h�E�̋��E��

extern TColor col_bgView;		//!< �e�L�X�g�r���[�A�̔w�i�F
extern TColor col_fgView;		//!< �e�L�X�g�r���[�A�̕����F
extern TColor col_Margin;		//!< �e�L�X�g�r���[�A�̗]����
extern TColor col_bgRuler;		//!< ���[���̔w�i�F
extern TColor col_fgRuler;		//!< ���[���̖ڐ��F
extern TColor col_bgLineNo;		//!< �s�ԍ��w�i�F
extern TColor col_LineNo;		//!< �s�ԍ������F
extern TColor col_Mark;			//!< �s�}�[�N
extern TColor col_bdrLine;		//!< �s�ԍ��̋��E��
extern TColor col_bdrFold;		//!< �܂�Ԃ����E��
extern TColor col_bdrFixed;		//!< �Œ蒷�\���̏c�r��
extern TColor col_Indent;		//!< �C���f���g�K�C�h
extern TColor col_Indent2;		//!< �C���f���g�K�C�h(����)
extern TColor col_Comment;		//!< �R�����g�̕����F
extern TColor col_Strings;		//!< ������̕����F
extern TColor col_Reserved;		//!< �\���̕����F
extern TColor col_Symbol;		//!< �V���{���̕����F
extern TColor col_Numeric;		//!< ���l�̕����F
extern TColor col_fgEmpBin1;	//!< �o�C�i�����������F1
extern TColor col_fgEmpBin2;	//!< �o�C�i�����������F2
extern TColor col_fgEmpBin3;	//!< �o�C�i�����������F3
extern TColor col_Headline;		//!< ���o���̕����F
extern TColor col_URL;			//!< URL�̕����F
extern TColor col_LocalLink;	//!< ���[�J���t�@�C���ւ̃����N
extern TColor col_bgImage;		//!< �摜�̔w�i�F
extern TColor col_bgDblPg;		//!< ���J���\���̗]���F
extern TColor col_bgWMF;		//!< ���^�t�@�C���̔w�i�F
extern TColor col_bgTips;		//!< �c�[���`�b�v�̔w�i�F
extern TColor col_fgTips;		//!< �c�[���`�b�v�̕����F
extern TColor col_bgHint;		//!< �q���g�\���̔w�i�F
extern TColor col_fgHint;		//!< �q���g�\���̕����F
extern TColor col_bgWarn;		//!< �x���\���̔w�i�F
extern TColor col_fgEmp;		//!< ���������F
extern TColor col_bgEmp;		//!< �����w�i�F
extern TColor col_Ruby;			//!< ���r
extern TColor col_TAB;			//!< �^�u�\���F
extern TColor col_CR;			//!< ���s�\���F
extern TColor col_HR;			//!< �r���̐F
extern TColor col_Ctrl;			//!< �R���g���[���R�[�h
extern TColor col_fgPair;		//!< �Ή����銇�ʂ̕����F

extern TColor col_bdrThumb;		//!< �T���l�C���̋��E��
extern TColor col_ThumbExif;	//!< �T���l�C����Eixf���
extern TColor col_ImgGrid;		//!< �摜�����O���b�h
extern TColor col_OptFind;		//!< �I�v�V�����ݒ�̌�������
extern TColor col_Tim1H;		//!< 1���Ԉȓ��̃^�C���X�^���v�F
extern TColor col_Tim3H;		//!< 3���Ԉȓ��́`
extern TColor col_Tim6H;		//!< 6���Ԉȓ��́`
extern TColor col_Tim1D;		//!< 1���ȓ��́`
extern TColor col_Tim3D;		//!< 3���ȓ��́`
extern TColor col_Tim7D;		//!< 7���ȓ��́`
extern TColor col_Tim1M;		//!< 1�����ȓ��́`
extern TColor col_Tim3M;		//!< 3�����ȓ��́`
extern TColor col_Tim6M;		//!< 6�����ȓ��́`
extern TColor col_Tim1Y;		//!< 1�N�ȓ��́`
extern TColor col_Tim3Y;		//!< 3�N�ȓ��́`
extern TColor col_TimOld;		//!< ������O�́`
extern TColor col_Size4G;		//!< 4GB�ȏ�
extern TColor col_Size2G;		//!< 2GB�ȏ�
extern TColor col_Size1G;		//!< 1GB�ȏ�
extern TColor col_Size512M;		//!< 512MB�ȏ�
extern TColor col_Size256M;		//!< 256MB�ȏ�
extern TColor col_Size128M;		//!< 128MB�ȏ�
extern TColor col_Size64M;		//!< 64MB�ȏ�
extern TColor col_Size32M;		//!< 32MB�ȏ�
extern TColor col_Size16M;		//!< 16MB�ȏ�
extern TColor col_Size1M;		//!< 1MB�ȏ�
extern TColor col_Size1K;		//!< 1KB�ȏ�
extern TColor col_SizeLT;		//!< 1KB����
extern TColor col_Size0;		//!< 0

extern TColor col_GrBack;		//!< �O���t�̔w�i�F
extern TColor col_GrLine;		//!< �O���t�̃��C��
extern TColor col_GrGrid;		//!< �O���t�̃O���b�h
extern TColor col_GrText;		//!< �O���t�̕����F

extern TColor col_GitHEAD;		//!< Git�r���[�A : �w�b�h
extern TColor col_GitMark;		//!<   �O���t�}�[�N
extern TColor col_GitBra;		//!<   �u�����`
extern TColor col_GitBraR;		//!<   �����[�g�u�����`
extern TColor col_GitTag;		//!<   �^�O
extern TColor col_GitHash;		//!<   �n�b�V��
extern TColor col_GitIns;		//!<   - �s
extern TColor col_GitDel;		//!<   + �s

extern TColor col_bgTlBar1;		//!< �c�[���o�[�̃O���f�[�V�����J�n�F
extern TColor col_bgTlBar2;		//!< �c�[���o�[�̃O���f�[�V�����I���F
extern TColor col_fgTlBar;		//!< �c�[���o�[�̕����F
extern TColor col_htTlBar;		//!< �c�[���o�[�̃z�b�g�g���b�L���O�F
extern TColor col_bgInfHdr;		//!< ���w�b�_�̔w�i�F
extern TColor col_fgInfHdr;		//!< ���w�b�_�̕����F

extern TColor col_bgChInf;		//!< �������T���v���̔w�i�F
extern TColor col_fgChInf;		//!< �������T���v���̕����F
extern TColor col_bgEdBox;		//!< Edit �{�b�N�X�̔w�i�F
extern TColor col_fgEdBox;		//!< Edit �{�b�N�X�̕����F
/** @} */
/** @} */

extern UnicodeString BgImgName[MAX_BGIMAGE];		//!< �w�i�摜�t�@�C����
extern Graphics::TBitmap *BgImgBuff[MAX_BGIMAGE];	//!< �w�i�摜�o�b�t�@

extern int  BgImgMode;			//!< �w�i�摜�\�����[�h
extern int  BgImgSubMode;
extern int  BgColAlpha;			//!< �w�i�F�A���t�@
extern bool BgImgGray;			//!< �O���[�X�P�[����
extern bool BgImgHideScr;		//!< �X�N���[�����ɉB��
extern int  BgHideTime;			//!< ���A����
extern bool BgImgTileIf;		//!< �w��T�C�Y�ȉ��Ȃ���ׂĕ\��
extern int  BgTileSize;

extern bool AlphaForm;			//!< ���C����ʂ𓧖���
extern int  AlphaValue;			//!< ���C����ʃA���t�@

extern UnicodeString FontSampleTxt;		//!< �t�H���g�̃T���v���\��������
extern UnicodeString FontSampleSym;		//!< �t�H���g�̃T���v���\���V���{��
extern int FontSampleSize;				//!< �\���T�C�Y
extern TColor FontSampleFgCol;			//!< �����F
extern TColor FontSampleBgCol;			//!< �w�i�F
extern TColor FontSampleGridCol;		//!< ����F
extern bool   FontSampleShowGrid;		//!< �����\��

extern UnicodeString TextEditor;		//!< �e�L�X�g�G�f�B�^
extern UnicodeString TextEditorFrmt;	//!< �p�����[�^(Grep�p)
extern UnicodeString TextEditorFrmt2;	//!< �p�����[�^(�t�@���[�p)

extern UnicodeString ImageEditor;		//!< �C���[�W�G�f�B�^
extern UnicodeString FExtImgEidt;		//!< �C���[�W�G�f�B�^�̑Ή��g���q
extern bool ImageEditSgl;				//!< �C���[�W�G�f�B�^���t�@�C�����ɌʋN��

extern UnicodeString FExtViewTab4;		//!< �^�u4�̊g���q
extern UnicodeString FExtViewTabX;		//!< �C�Ӄ^�u���̊g���q
extern int  ViewTabWidthX;				//!< �C�Ӄ^�u��

extern UnicodeString BinaryEditor;		//!< �o�C�i���G�f�B�^
extern UnicodeString SoundTaskFin;		//!< �^�X�N�I�����̒ʒm��
extern UnicodeString SoundFindFin;		//!< �����I�����̒ʒm��
extern UnicodeString SoundWarning;		//!< �x����
extern UnicodeString SoundWatch;		//!< �t�@�C���Ď�

extern int  FlashCntWarning;			//!< �x���̓_�ŉ�
extern int  FlashTimeWarning;			//!< �x���̓_�ŊԊu
extern int  FlashCntTaskfin;			//!< �^�X�N�I�����̓_�ŉ�
extern int  FlashTimeTaskfin;			//!< �^�X�N�I�����̓_�ŊԊu

extern int  MaxLogLines;				//!< ���O�̍ő�s��
extern int  MsgHintTime;				//!< �q���g�̕\������
extern int  KeyHintTime;				//!< 2�X�g���[�N�q���g�̑ҋ@����
extern int  NotifyTaskTime;				//!< �`�b�ȏォ�������^�X�N�̏I�����ɖ炷
extern int  CmpDelOwCnt;				//!< ���S�폜�̏㏑����
extern int  ViewTxtInterLn;				//!< �r���[�A�̍s��
extern int  ViewLeftMargin;				//!< �r���[�A�̍��]��
extern int  ViewFoldWidth;				//!< �܂�Ԃ���(���p�P��)
extern bool ViewFoldFitWin;				//!< �܂�Ԃ����E�B���h�E���ɍ��킹��
extern bool TvCursorVisible;			//!< �r���[�A�ŃJ�[�\������ɉ��̈��
extern bool LimitBinCsr;				//!< �o�C�i���\���ŃJ�[�\���ړ��𐧌�
extern bool TxtColorHint;				//!< �J�[�\���ʒu���l�̃J���[���q���g�\��
extern bool AltBackSlash;				//!< \ �� �_(U+2216)�ŕ\��
extern bool FormatJson;					//!< .json �t�@�C���𐮌`
extern bool DecodeDfmStr;				//!< .dfm �t�@�C���̕�������f�R�[�h
extern bool BinMemMaped;				//!< �o�C�i���ł̓������}�b�v�h�t�@�C���Ƃ��ĊJ��
extern int  ViewFixedLimit;				//!< �Œ蒷�\���̍ő啝
extern int  ViewTxtLimitSize;			//!< �e�L�X�g�̍ő�Ǎ��T�C�Y
extern int  ViewBinLimitSize;			//!< �o�C�i���̍ő�Ǎ�(or �}�b�v)�T�C�Y
extern int  ListWheelScrLn;				//!< �z�C�[���ɂ��X�N���[���s��(���X�g)
extern int  ViewWheelScrLn;				//!< �z�C�[���ɂ��X�N���[���s��(�r���[�A)
extern int  PlaySndLimitTime;			//!< �T�E���h�Đ��^�C������
extern bool ShowTextPreview;			//!< �e�L�X�g�v���r���[��\��
extern int  PrvTxtInfLn;				//!< �e�L�X�g�v���r���[�̍s��
extern bool ShowTailPreview;			//!< �����v���r���[��\��
extern int  PrvTxtTailLn;				//!< �����v���r���[�s��
extern int  PrvActTailLn;				//!< �����v���r���[��L���ɂ���s��
extern int  WatchInterval;				//!< �f�B���N�g���Ď��Ԋu
extern int  InfPrvWait;					//!< ���擾/�v���r���[�̒x��
extern int  LogInterval;				//!< ���O�̍X�V�Ԋu
extern int  ListInterLn;				//!< �t�@�C�����X�g�̍s��
extern int  CursorWidth;				//!< �J�[�\�����̕�
extern int  CursorAlpha;				//!< �J�[�\���s�w�i�A���t�@
extern int  CellAlpha;					//!< �Z���̔w�i�A���t�@
extern int  SplitterWidth;				//!< ���E���̕�
extern int  SplitterWidth2;
extern int  FExtMaxWidth;				//!< �g���q�̍ő啶����
extern int  SizeFormatMode;
extern int  SizeDecDigits;				//!< �T�C�Y�\���ɂ����鏬���_�ȉ��̌���
extern int  ListPercent;				//!< �t�@�C�����X�g���̔䗦
extern int  ImgFrameMargin;				//!< �t�B�b�g�\�����̗]����
extern int  ImgFitMaxZoom;				//!< �t�B�b�g�\�����̋��e�{��
extern int  ImgGridHorzN;				//!< �O���b�h�̉�������
extern int  ImgGridVertN;				//!< �O���b�h�̏c������
extern int  MinShowTime;				//!< �ŏ��\���^�C��
extern int  ThumbnailSize;				//!< �T���l�C���̃T�C�Y
extern int  ThumbBdrWidth;				//!< �T���l�C���̋��E����
extern int  ThumbScaleOpt;				//!< �T���l�C���̏k���A���S���Y��
extern int  ThumbnailPos;				//!< �T���l�C���̕\���ʒu
extern int  ImgDblMargin;				//!< ���J���Ԋu

extern bool ShowImgSidebar;				//!< �T�C�h�o�[��\��
extern bool ImgSidebarIsLeft;			//!< �T�C�h�o�[�͍�

extern bool HasCallHotkey;				//!< �Ăяo���z�b�g�L�[�����邩�H

extern bool HideSizeTime;				//!< �T�C�Y�ƍX�V�������B��

//---------------------------------------------------------------------------
/** @addtogroup FILELIST */
/** @{ */

/**
 * @brief �t�@�C�����X�g����
 */
struct file_rec {
	UnicodeString f_name;		//!< �p�X�t�t�@�C����
	UnicodeString p_name;		//!< �p�X��
	UnicodeString n_name;		//!< �p�X���t�@�C����
	UnicodeString b_name;		//!< �t�@�C�����啔
	UnicodeString f_ext;		//!< �g���q
	UnicodeString attr_str;		//!< ����������
	UnicodeString alias;		//!< �G�C���A�X
	UnicodeString arc_name;		//!< �A�[�J�C�u��
	UnicodeString tmp_name;		//!< �ꎞ�𓀖�
	UnicodeString r_name;		//!< �\����
	UnicodeString l_name;		//!< �����N��
	UnicodeString tags;			//!< �^�O
	UnicodeString hash;			//!< �n�b�V��/ �摜�n�b�V��(�ގ����\�[�g)
	UnicodeString vctr;			//!< �摜:�x�N�g��(�ގ����\�[�g)
	UnicodeString memo;			//!< �x�}�[�N�ꗗ:   ����(���e \t �ݒ����)@n
								//!< ���|�W�g���ꗗ: ���(�R�~�b�g \t ���)

	int  tag;					//!< 0: ��/ 1: �E
	bool is_up;					//!< ..
	bool is_dir;				//!< �f�B���N�g��
	bool is_sym;				//!< ���p�[�X�|�C���g
	bool is_jct;				//!< �W�����N�V����
	bool is_virtual;			//!< ���z�f�B���N�g�����̃t�@�C��
	bool is_ftp;				//!< FTP
	bool is_ads;				//!< ��փf�[�^�X�g���[��
	bool is_dummy;				//!< �_�~�[(��̃h���C�u�A���[�N���X�g�̃Z�p���[�^�A��r���ʂ̕s�ݍ��ڂȂ�)
	bool selected;				//!< �I��
	bool failed;				//!< �t�@�C���[: �ꎞ�𓀎��s/  �C���[�W�r���[�A: �Ǎ����s

	__int64 f_size;				//!< �T�C�Y
	__int64 o_size;				//!< �f�B�X�N��̐�L�T�C�Y
	__int64 c_size;				//!< ���k�T�C�Y

	int  f_attr;				//!< ����
	TDateTime f_time;			//!< �^�C���X�^���v
	int  f_count;				//!< �t�@�C����
	int  d_count;				//!< �f�B���N�g����
	int  img_ori;				//!< �摜����
	int  distance;				//!< �ҏW�����\�[�g�l
	bool is_video;				//!< ����

	int  base_end_x;			//!< �t�@�C�����啔�̖����ʒu(�`�掞�ɐݒ�A�}�E�X�I���ŗ��p)
	bool matched;				//!< �C���N�������^���Ń}�b�`

	TStringList *inf_list;		//!< ��񃊃X�g
	UnicodeString prv_text;		//!< �e�L�X�g�v���r���[
	UnicodeString tail_text;	//!< �e�L�X�g�v���r���[(����)
	int  code_page;				//!< �R�[�h�y�[�W
};

//---------------------------------------------------------------------------
/**
 * @brief �t�@�C�����X�g�̏��
 */
struct flist_stt {
	UnicodeString vol_name;		//!< �{�����[����
	__int64 drive_Used;			//!< �h���C�u�g�p�e��
	__int64 drive_Free;			//!< �h���C�u�󂫗e��
	__int64 drive_Total;		//!< �h���C�u�S�̗e��
	__int64 cur_total;			//!< �J�����g�̍��v�T�C�Y
	__int64 occ_total;			//!< �J�����g�̐�L�T�C�Y
	__int64 cmp_total;			//!< �J�����g�̈��k�T�C�Y
	int clu_size;				//!< �N���X�^�T�C�Y

	int f_cnt;					//!< �t�@�C����
	int d_cnt;					//!< �f�B���N�g����
	int f_cnt_total;
	int d_cnt_total;
	int sel_f_cnt;				//!< �I���t�@�C����
	int sel_d_cnt;				//!< �I���f�B���N�g����
	__int64 sel_size;			//!< �I���T�C�Y

	int last_fl_idx;			//!< �t�@�C�����X�g�ɕ��A�����Ƃ��̃J�[�\���ʒu

	bool show_f_d_cnt;			//!< �t�@�C���A�f�B���N�g������\��
	bool dir_graph;				//!< �f�B���N�g���e�ʂ��O���t�\��(�΃J�����g)
	bool dsk_graph;				//!< �f�B���N�g���e�ʂ��O���t�\��(�΃h���C�u)
	bool sub_counted;			//!< �T�u�f�B���N�g���������ׂăJ�E���g�ς�

	int lwd_half;				//!< "X" �̕�
	int lwd_fext_max;			//!< ".WWWWWWWWWWWW" �̕�
	int lwd_fext;				//!< �g���q�̕\����
	int lwd_size;				//!< �T�C�Y�̕\����
	int lwd_time;				//!< �^�C���X�^���v�̕\����
	int lwd_path;				//!< �ꏊ�̕\����(�������X�g)

	int lxp_fext;				//!< �g���q�̕\���ʒu
	int lxp_size;				//!< �T�C�Y�̕\���ʒu
	int lxp_time;				//!< �^�C���X�^���v�̕\���ʒu
	int lxp_path;				//!< �ꏊ�̕\���ʒu
	int lxp_right;				//!< ���[�ʒu

	TColor color_bgDirInf;		//!< .NyanFi �ɂ��ʐF
	TColor color_fgDirInf;
	TColor color_bgDrvInf;
	TColor color_fgDrvInf;
	TColor color_Cursor;
	TColor color_selItem;

	bool is_TabFixed;			//!< �^�u�ύX�ɑ΂��ăp�X�Œ�

	bool git_checked;			//!< [..]��Git�����擾����

	bool is_Work;				//!< ���[�N���X�g
	bool is_FTP;				//!< FTP�����[�g��

	bool is_Arc;				//!< ���z�f�B���N�g��
	UnicodeString arc_DspPath;	//!< �A�[�J�C�u�̕\���p�X
	UnicodeString arc_SubPath;	//!< �A�[�J�C�u�ȉ��̃T�u�f�B���N�g��
	UnicodeString arc_Name;		//!< �A�[�J�C�u�t�@�C����(temp)
	TStringList  *arc_RetList;	//!< ���d�A�[�J�C�u�p�̖߂胊�X�g
	TStringList  *arc_TmpList;	//!< �ꎞ�𓀃f�B���N�g�����X�g

	bool is_ADS;				//!< ��փf�[�^�X�g���[��
	UnicodeString ads_Name;		//!< ���C���X�g���[���̃t�@�C����

	UnicodeString LibraryInfo;	//!< ���C�u�����t�@�C���� \t �p�X
	UnicodeString LibSubPath;

	bool is_Find;				//!< �������ʃ��X�g
	bool is_narrow;				//!< �i�荞��
	bool find_Loaded;			//!< �t�@�C������ǂݍ��񂾃��X�g
	bool find_UseSet;			//!< �����ݒ�t�@�C�����g�p
	int  find_SortMode;			//!< �����ݒ�t�@�C���ɂ��\�[�g���[�h�ݒ�

	bool find_Dir;				//!< �f�B���N�g������
	bool find_Both;				//!< �t�@�C���E�f�B���N�g������
	bool find_SubDir;			//!< �T�u�f�B���N�g��������
	bool find_Arc;				//!< �A�[�J�C�u��������
	bool find_xTrash;			//!< ���ݔ����͌������Ȃ�

	bool find_MARK;				//!< �}�[�N����
	bool find_TAG;				//!< �^�O����
	bool find_TAG_all;			//!< ���ׂẴ^�O�Ƀ}�b�`
	bool find_DICON;			//!< �t�H���_�A�C�R������
	bool find_DUPL;				//!< �d���t�@�C���̌���
	bool find_HLINK;			//!< �n�[�h�����N��

	bool find_RegEx;			//!< ���K�\��
	bool find_And;				//!< AND����
	bool find_Case;				//!< �召�������

	bool find_Warn;				//!< �D�܂����Ȃ��t�@�C����
	bool find_hasAds;			//!< ��փf�[�^�X�g���[��������
	bool find_useProc;			//!< �ʃv���Z�X���g�p��

	bool find_ResLink;			//!< ���ʃ��X�g���甽�Α��֔��f
	bool find_DirLink;			//!< �f�B���N�g�����𔽉f
	bool find_PathSort;			//!< �ꏊ���Ń\�[�g

	UnicodeString find_Path;	//!< �����p�X
	UnicodeString find_DirList;	//!< �����f�B���N�g���E���X�g
	UnicodeString find_SkipDir;	//!< ���O�f�B���N�g��(;��؂�)
	UnicodeString find_Name;	//!< ������(�n�[�h�����N�p)
	UnicodeString find_Mask;	//!< �}�X�N
	UnicodeString find_Keywd;	//!< �L�[���[�h
	UnicodeString find_Tags;	//!< �^�O
	UnicodeString find_Icons;	//!< �t�H���_�A�C�R��(���s��؂�)

	TStringList  *find_SubList;	//!< �I���T�u�f�B���N�g��

	int  find_DT_mode;			//!< ���t����
	TDateTime find_DT_value;
	UnicodeString find_DT_str;
	int  find_DT_rel;			//!< ���Ύw��l

	int  find_SZ_mode;			//!< �T�C�Y����
	__int64 find_SZ_value;
	int  find_CT_mode;			//!< ���e����
	int  find_AT_mode;			//!< ��������
	int  find_AT_value;

	int  find_TM_mode;			//!< �^�C��
	TTime find_TM_value;

	int  find_codepage;			//!< �R�[�h�y�[�W
	UnicodeString find_LineBrk;	//!< ���s�R�[�h
	int  find_BOM_mode;			//!< BOM

	int  find_RT_mode;			//!< ���C�g
	int  find_RT_value;
	int  find_FS_mode;			//!< �t���[����
	int  find_FS_value;
	int  find_FW_mode;			//!< �t���[����
	int  find_FW_value;
	int  find_FH_mode;			//!< �t���[����
	int  find_FH_value;

	int  find_IW_mode;			//!< �摜�T�C�Y
	unsigned int find_IW_value;
	int  find_IH_mode;
	unsigned int find_IH_value;
	bool find_IWH_max;

	int  find_SR_mode;			//!< �T���v�����O���[�g
	int  find_SR_value;
	int  find_BT_mode;			//!< �r�b�g
	int  find_CH_mode;			//!< �`�����l��

	int  find_IC_mode;			//!< �A�C�R��
	int  find_IC_value;

	int  find_HL_mode;			//!< �����N�J�E���g��
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

	bool is_IncSea;				//!< �C���N�������^���T�[�`��
	bool is_Migemo;				//!< Migemo���[�h
	bool is_Filter;				//!< �t�B���^���[�h
	bool is_Fuzzy;				//!< �����܂����[�h
	bool filter_csns;			//!< �t�B���^�ő召���������

	UnicodeString incsea_Word;
	UnicodeString incsea_Ptn;
};

extern flist_stt ListStt[MAX_FILELIST];
extern flist_stt *CurStt;
extern flist_stt *OppStt;
/** @} */

//---------------------------------------------------------------------------
//�h���C�u���
//---------------------------------------------------------------------------
/**
 * @brief �h���C�u���
 */
struct drive_info {
	UnicodeString drive_str;
	bool		  accessible;
	bool		  ejectable;
	bool		  is_virtual;
	int			  drv_type;
	UnicodeString type_str;		//!< ���
	UnicodeString volume;		//!< �{�����[����
	UnicodeString unc;			//!< �l�b�g���[�N�h���C�u��UNC�p�X
	UnicodeString mnt_dir;		//!< ���z�h���C�u�̃}�E���g�p�X
	UnicodeString f_system;		//!< �t�@�C���V�X�e��
	UnicodeString bus_type;		//!< �ڑ�I/F
	UnicodeString label;		//!< �\���p���x��
	bool		  is_NTFS;
	bool		  is_SSD;
	bool		  is_RAM;
	TIcon		  *small_ico;
	TIcon		  *large_ico;
};

//---------------------------------------------------------------------------
/**
 * @brief �^�u���
 */
struct tab_info {
	TRect rc;	//�`��̈�
	TStringList *sel_list[MAX_FILELIST];	//!< �I�����
	TStringList *dir_hist[MAX_FILELIST];	//!< �f�B���N�g������
	int			 dir_hist_p[MAX_FILELIST];	//!< �����ʒu
	int			 sort_mode[MAX_FILELIST];	//!< �\�[�g���[�h
	bool		 sync_lr;					//!< �K�w����
};

//---------------------------------------------------------------------------
//�R�}���h�t�@�C�����X�g
//---------------------------------------------------------------------------
struct cmdf_rec {
	TDateTime   f_time;				//!< �^�C���X�^���v
	TStringList *file_buf;			//!< �t�@�C�����e
	TStringList *cmd_list;			//!< �R�}���h���X�g
	int exe_count;					//!< ���s��
	bool noreload;					//!< �ēǂݍ��݂��Ȃ�
};
extern TStringList *CmdFileList;	//!< �R�}���h�t�@�C���̃��X�g
extern TStringList *XCMD_VarList;	//!< �ϐ����X�g

//---------------------------------------------------------------------------
inline void InvalidateFileList(int tag = CurListTag)
{
	FileListBox[tag]->Invalidate();
}

//---------------------------------------------------------------------------
/** @brief VCL�X�^�C�����g�p���Ă��邩�H */
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
//�\�[�g���[�h
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
 * @brief �t�@�C�����X�g���擾
 * @param tag
 * @return TStringList*
 */
TStringList* GetFileList(int tag);

/**
 * @brief �J�����g�̃��X�g���擾
 * @param only_filer �t�@�C���[�݂̂�Ώ�
 * @return TStringList*
 */
TStringList* GetCurList(bool only_filer = false);

/**
 * @brief ���Α��̃��X�g���擾
 * @return TStringList*
 */
TStringList* GetOppList();

/**
 * @brief �I��L��?
 * @param lst �Ώۃ��X�g
 * @return true
 * @return false
 */
bool ListSelected(TStringList *lst);

/**
 * @brief �I�𒆂̍��ڐ����擾
 * @param lst �Ώۃ��X�g
 * @return int �I�𒆂̍��ڐ�
 */
int GetSelCount(TStringList *lst);

/**
 * @brief �I�𒆍��ږ����X�g���擾
 * @param lst �Ώۃ��X�g
 * @param[out] sel_lst �I�����ڃ��X�g
 * @param with_path �p�X�t���Ŏ擾
 * @param with_obj Objects ���擾
 */
void GetSelList(TStringList *lst, TStringList *sel_lst, bool with_path = true, bool with_obj = false);

/**
 * @brief �I����Ԃ�����
 * @param lst �Ώۃ��X�g
 */
void ClrSelect(TStringList *lst = NULL);

/**
 * @brief �}�b�`���ڐ����擾
 * @param lst �Ώۃ��X�g
 * @return int �}�b�`���ڐ�
 */
int  GetMatchCount(TStringList *lst);

/**
 * @brief �t�@�C�����X�g�̃\�[�g
 * @param lst �Ώۃ��X�g
 * @param tag
 */
void SortList(TStringList *lst, int tag = CurListTag);

/**
 * @brief �t�@�C�����X�g�ō��ڂ�������
 * @param fnam �t�@�C����
 * @param tag
 * @param top_idx �擪�C���f�b�N�X
 * @return int �C���f�b�N�X(������Ȃ��ꍇ�� -1)
 */
int  IndexOfFileList(UnicodeString fnam, int tag = CurListTag, int top_idx = -1);

file_rec* ExistsInList(UnicodeString fnam, TStringList *lst);

UnicodeString GetSelFileStr(TStringList *lst, bool use_tmp = false, bool inc_dir = false, TStringList *s_lst = NULL);

/**
 * @brief file_rec ���쐬���ď�����
 * @details file_rec ���쐬���ď��������܂��Bcopy_fp ���w�肷��ƁA���̓��e���R�s�[����܂��B
 * @param copy_fp
 * @return file_rec*
 */
file_rec* cre_new_file_rec(file_rec *copy_fp = NULL);

/**
 * @brief �t�@�C�������� file_rec ���쐬
 * @param fnam �t�@�C����(������ \ �̏ꍇ�̓f�B���N�g����)
 * @param tag
 * @param force ���݂��Ȃ��ꍇ�������I�ɐݒ�
 * @return file_rec*
 */
file_rec* cre_new_file_rec(UnicodeString fnam, int tag = -1, bool force = false);

/**
 * @brief [..]�� file_rec ���쐬
 * @param tag
 * @return file_rec*
 */
file_rec* cre_new_up_rec(int tag);

/**
 * @brief file_rec �̃R�s�[
 * @param s_fp �R�s�[��
 * @param d_fp �R�s�[��
 */
void copy_file_rec(file_rec *s_fp, file_rec *d_fp);

/**
 * @brief file_rec �̍폜
 * @param fp �폜�Ώ�
 */
void del_file_rec(file_rec *fp);

void inv_file_rec(file_rec *fp);

/**
 * @brief ���ڂ͑I���\���H
 * @param fp �Ώۍ���
 * @return true
 * @return false
 */
bool is_selectable(file_rec *fp);

/**
 * @brief �I���\�ȍ��ڂ̑I����Ԃ�ݒ�
 * @param fp �Ώۍ���
 * @param sw �I��
 * @return true
 * @return false
 */
bool set_select(file_rec *fp, bool sw = true);

/**
 * @brief �I���\�ȍ��ڂ̑I����Ԃ𔽓]
 * @param fp �Ώۍ���
 * @return true
 * @return false
 */
bool set_select_r(file_rec *fp);

/**
 * @brief �t�@�C�����X�g�̃N���A
 * @param lst �Ώۃ��X�g
 */
void clear_FileList(TStringList *lst);

/**
 * @brief �t�@�C�����X�g�̍��ڍ폜
 * @param lst �Ώۃ��X�g
 * @param idx �폜�C���f�b�N�X
 */
void del_FileListItem(TStringList *lst, int idx);

/**
 * @brief �t�@�C�����X�g�̓��e�����ւ���
 * @param lst1 ���X�g1
 * @param lst2 ���X�g2
 * @param swap_tag �^�O������ւ���
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
 * @brief �����ݒ�̃N���A
 * @param lst_stt
 */
void clear_FindStt(flist_stt *lst_stt);

/**
 * @brief �����ݒ�̕ۑ�
 * @param fnam �t�@�C����
 * @param lst_stt
 * @return true
 * @return false
 */
bool save_FindSettings(UnicodeString fnam, flist_stt *lst_stt);

/**
 * @brief �����ݒ�̓Ǎ�
 * @param fnam �t�@�C����
 * @param lst_stt
 * @return true
 * @return false
 */
bool load_FindSettings(UnicodeString fnam, flist_stt *lst_stt);

/**
 * @brief �����ݒ���̎擾
 * @param fnam �t�@�C����
 * @param[out] lst ��񃊃X�g
 */
void get_FindSetInf(UnicodeString fnam, TStringList *lst);

/**
 * @brief �����Ώۂ��S�̂��H
 * @param lst_stt
 * @return true
 * @return false
 */
bool is_FindAll(flist_stt *lst_stt);

/**
 * @brief �������X�g��񕶎�����擾
 * @param pnam_sw �p�X���Ȃǂ�t��
 * @return UnicodeString
 */
UnicodeString get_FindInfStr(bool pnam_sw);

bool check_int(int v0, int v1, int mode);
bool check_prop(UnicodeString fnam, UnicodeString prop, int v, int mode);

/**
 * @brief �W���t�@�C������
 * @attention �s���Ȑ��K�\���p�^�[����p���Ȃ�����(�v���O�`�F�b�N)
 * @param fnam �p�X�����t�@�C����
 * @param f_tm �^�C���X�^���v
 * @param f_sz �T�C�Y
 * @param f_atr ����
 * @param lst_stt
 * @return true �}�b�`
 * @return false
 */
bool check_file_std(UnicodeString fnam, TDateTime f_tm, __int64 f_sz, int f_atr, flist_stt *lst_stt);

/**
 * @brief �g���t�@�C������
 * @param fnam �p�X�����t�@�C����
 * @param lst_stt
 * @return true �}�b�`
 * @return false
 */
bool check_file_ex(UnicodeString fnam, flist_stt *lst_stt);

/**
 * @brief �t�H���g�����擾
 * @param fnam �t�@�C����
 * @param[out] lst ��񃊃X�g
 * @return UnicodeString �t�H���g��
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
 * @brief ����f�B���N�g���̃��X�g���擾
 * @param id
 * @param[out] o_lst ���X�g
 * @return true
 * @return false
 */
bool get_SpecialDirList(UnicodeString id, TStringList *o_lst = NULL);

void get_FindListF(UnicodeString pnam, flist_stt *lst_stt, TStrings *lst, int tag);
void get_FindListD(UnicodeString pnam, flist_stt *lst_stt, TStrings *lst, int tag);

/**
 * @brief ���ׂẴT�u�f�B���N�g�����擾
 * @param pnam ��f�B���N�g��
 * @param[out] lst �f�B���N�g�������X�g
 * @param stt_bar �o�ߕ\���p�X�e�[�^�X�o�[
 * @param stt_idx �\���p�l���̃C���f�b�N�X
 * @param proc_msg ���b�Z�[�W�L���[������
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
 * @brief ViewFileList �ŗL���ȍ��ڐ����擾
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
 * @brief �t�@�C���̍폜
 * @param fnam �t�@�C����
 * @param use_trash ���ݔ����g�p
 * @return true ����
 * @return false
 */
bool delete_File(UnicodeString fnam, bool use_trash = false);

void delete_FileIf(UnicodeString fnam);

bool delete_DirEx(UnicodeString pnam, bool use_trash = false, bool force = false);

/**
 * @brief �t�@�C���̈ړ�(�^�O/�t�H���_�A�C�R�����l��)
 * @param old_nam �ړ����̃t�@�C����
 * @param new_nam �ړ���̃t�@�C����
 * @return true ����
 * @return false
 */
bool move_FileT(UnicodeString old_nam, UnicodeString new_nam);

/**
 * @brief �t�H���_�A�C�R���̈ړ�
 * @param old_dnam
 * @param new_dnam
 */
void move_FolderIcon(UnicodeString old_dnam, UnicodeString new_dnam);

/**
 * @brief �t�H���_�A�C�R���̃R�s�[
 * @param src_dnam
 * @param dst_dnam
 */
void copy_FolderIcon(UnicodeString src_dnam, UnicodeString dst_dnam);

/**
 * @brief �t�H���_�A�C�R���t�@�C���̎擾
 * @param dnam
 * @return UnicodeString
 */
UnicodeString get_FolderIconName(UnicodeString dnam);

/**
 * @brief �t�H���_�A�C�R���̐ݒ�
 * @param dnam �f�B���N�g����
 * @param inam �A�C�R���t�@�C���� (EmptyStr: ����)
 */
void set_FolderIcon(UnicodeString dnam, UnicodeString inam = EmptyStr);

/**
 * @brief �t�H���_�A�C�R���ꗗ���擾
 * @param[out] lst ���X�g
 */
void get_FolderIconList(TStringList *lst);

/**
 * @brief �t�H���_�A�C�R���̉���
 * @param old_nam
 * @param new_nam
 */
void rename_FolderIcon(UnicodeString old_nam, UnicodeString new_nam);

/**
 * @brief ���݂��Ȃ��t�H���_�A�C�R���ݒ�𐮗�
 */
void chk_FolderIcon();

/**
 * @brief �g���q�Ɋ֘A�t������Ă���A�v���̃��X�g���擾
 * @param fext �g���q
 * @return TStringDynArray
 */
TStringDynArray get_AssociatedApps(UnicodeString fext);

/**
 * @brief �֘A�t�����X�g���烁�j���[�p���X�g���쐬
 * @param[in] app_lst �֘A�t�����X�g
 * @param[out] lst ���j���[�p���X�g
 */
void make_AssoMenuList(TStringDynArray app_lst, TStringList *lst);

/** @addtogroup GLOBAL_COLORS */
/** @{ */
/**
 * @brief �t�@�C�����X�g���ڂ̔w�i�F���擾
 * @param lst_stt
 * @param idx �C���f�b�N�X
 * @return TColor
 */
TColor get_FlBgColor(flist_stt *lst_stt, int idx = 0);

/**
 * @brief �t�@�C�����̕����F���擾
 * @param fp
 * @param col_x
 * @return TColor
 */
TColor get_FileColor(file_rec *fp, TColor col_x);

/**
 * @brief �g���q�ʃJ���[���擾
 * @param fext �g���q
 * @param col �f�t�H���g�����F
 * @return TColor
 */
TColor get_ExtColor(UnicodeString fext, TColor col = col_fgList);

/**
 * @brief �^�C���X�^���v�̕����F���擾
 * @param dt �^�C���X�^���v
 * @param col_def �f�t�H���g�����F
 * @return TColor
 */
TColor get_TimeColor(TDateTime dt, TColor col_def);

/**
 * @brief �T�C�Y�̕����F���擾
 * @param size �T�C�Y
 * @param col_def �f�t�H���g�����F
 * @return TColor
 */
TColor get_SizeColor(__int64 size, TColor col_def);

/**
 * @brief ���O�̕����F���擾
 * @param s ������
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
 * @brief �폜�������ꂽ�f�B���N�g�����H
 * @param dnam 
 * @return true 
 * @return false 
 */
bool is_ProtectDir(UnicodeString dnam);

/**
 * @brief �t�@�C����񃊃X�g���擾
 * @param fp �擾�Ώ�
 * @param force �����I�Ɏ擾
 */
void GetFileInfList(file_rec *fp, bool force = false);

/**
 * @brief �w�肵���t�@�C�����̒l��������擾
 * @param fp �擾�Ώ�
 * @param tit �^�C�g��
 * @param dlmt �l�̋�؂蕶��
 * @return UnicodeString 
 */
UnicodeString get_FileInfValue(file_rec *fp, UnicodeString tit, UnicodeString dlmt = EmptyStr);

void assign_InfListBox(TListBox *lp, TStringList *i_lst, UsrScrollPanel *sp = NULL);
void draw_InfListBox(TListBox *lp, TRect &Rect, int Index, TOwnerDrawState State);
void draw_ColorListBox(TListBox *lp, TRect &Rect, int Index, TOwnerDrawState State, TStringList *col_lst);

void draw_InputPaintBox(TPaintBox *pp, UnicodeString s);

/**
 * @brief �^�C���X�^���v�̕\����������擾
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
 * @brief �t�@�C����񃊃X�g���擾
 * @param fp �擾�Ώ�
 * @param[out] lst ��񃊃X�g
 * @return true
 * @return false
 */
bool get_FileInfList(file_rec *fp, TStringList *lst);

/**
 * @brief �t�@�C�������������H
 * @param fp �Ώ�
 * @param[out] err_msg �G���[���b�Z�[�W
 * @return true
 * @return false
 */
bool is_Processing(file_rec *fp, UnicodeString *err_msg = NULL);

/**
 * @brief �t�@�C�������������H
 * @param fnam �t�@�C����
 * @param is_video ����(�������`�F�b�N)
 * @param[out] err_msg �G���[���b�Z�[�W
 * @return true
 * @return false
 */
bool is_Processing(UnicodeString fnam, bool is_video = false, UnicodeString *err_msg = NULL);

/**
 * @brief �擾���}�~����Ă���p�X���H
 * @param pnam �p�X��
 * @param no_path �擾���Ȃ��p�X�̃��X�g(���ϐ��A%ExePath% �Ή�)
 * @return true
 * @return false
 */
bool is_NoInfPath(UnicodeString pnam, UnicodeString no_path);

/**
 * @brief �X�g���[���̉��s�R�[�h���擾
 * @param ms �������X�g���[��
 * @param code_page �R�[�h�y�[�W
 * @param strict ���S�`�F�b�N
 * @return UnicodeString
 */
UnicodeString get_StreamLineBreak(TStream *ms, int code_page, bool strict = false);

/**
 * @brief �t�@�C���̃R�[�h�y�[�W���擾
 * @param fnam �t�@�C����
 * @param[out] line_brk ���s
 * @param[out] has_bom BOM�L��
 * @return int �R�[�h�y�[�W (0: �s��)
 */
int get_FileCodePage(UnicodeString fnam, UnicodeString *line_brk = NULL, bool *has_bom = NULL);

/**
 * @brief �t�@�C���̓e�L�X�g���H
 * @param fnam �t�@�C����
 * @param[out] code_page �R�[�h�y�[�W
 * @param[out] line_brk ���s
 * @param[out] has_bom BOM�L��
 * @return true
 * @return false
 */
bool is_TextFile(UnicodeString fnam, int *code_page = NULL, UnicodeString *line_brk = NULL, bool *has_bom = NULL);

/**
 * @brief �����񃊃X�g�̍s���A�R�����g�A�󔒍s���J�E���g
 * @param lst �����񃊃X�g
 * @param fnam �t�@�C����
 * @param[out] rem_cnt �R�����g�s��
 * @param[out] blk_cnt �󔒍s��
 * @return int ���s��
 */
int CountListLines(TStringList *lst, UnicodeString fnam, int *rem_cnt, int *blk_cnt);

/**
 * @brief INI�t�@�C���̃^�C�v��������擾
 * @param fp �Ώ�
 * @return UnicodeString �^�C�v������
 */
UnicodeString get_IniTypeStr(file_rec *fp);

/**
 * @brief �����ݒ�t�@�C�����H
 * @param fp �Ώ�
 * @return true
 * @return false
 */
bool is_FindSet(file_rec *fp);

/**
 * @brief ���j���[�t�@�C�����H
 * @param fp �Ώ�
 * @return true
 * @return false
 */
bool is_MenuFile(file_rec *fp);

/**
 * @brief ���ʃ��X�g�t�@�C�����H
 * @param fp �Ώ�
 * @return true
 * @return false
 */
bool is_ResultList(file_rec *fp);

bool is_AudioVideo(UnicodeString fnam);		//!< �r�f�I/�I�[�f�B�I�E�t�@�C�����H
bool is_MPEG2_TS(UnicodeString fnam);		//!< MPEG-2 TS �t�@�C�����H
bool is_SoundID(UnicodeString s);			//!< �T�E���h���ʎq���H
bool is_ViewableFext(UnicodeString fext);	//!< �r���[�A�ŕ\���\��(�A�C�R���͏���)�H
bool is_Viewable(file_rec *fp);
bool is_ExtractIcon(file_rec *fp);			//!< �A�C�R�����o�\���H
bool test_ArcExt(UnicodeString fext);		//!< �A�[�J�C�o�̑Ή��g���q���H
bool is_AvailableArc(UnicodeString fnam, bool ex_sw = false);	//!< ���p�\�ȃA�[�J�C�u���H

bool test_TxtFile(UnicodeString fnam);		//!< �e�L�X�g�t�@�C�����H
bool test_NonTxtExt(UnicodeString fext);	//!< ��e�L�X�g�̊g���q���H

UnicodeString get_img_fext();				//!< �摜�̊g���q���擾

/**
 * @brief �g���q�ʃt�@�C��������ǉ�
 * @param f_lst �t�@�C�������X�g
 * @param[out] lst ��񃊃X�g
 */
void add_FExtInfList(TStringList *f_lst, TStringList *lst);

/**
 * @brief �t�@�C������摜�T�C�Y���擾
 * @param fnam �t�@�C����
 * @param[out] wd ��
 * @param[out] hi ����
 * @return true ����
 * @return false
 */
bool get_img_size(UnicodeString fnam, unsigned int *wd, unsigned int *hi);

/**
 * @brief �摜�t�@�C����ǂݍ���
 * @param fnam �t�@�C����
 * @param[out] o_bmp �r�b�g�}�b�v
 * @param img_type
 * @param trans_bg ���ߔw�i�F
 * @return int
 */
int  load_ImageFile(UnicodeString fnam, Graphics::TBitmap *o_bmp, int img_type = WICIMG_PREVIEW, TColor trans_bg = col_None);

/**
 * @brief �T���l�C���L���b�V�����擾
 * @param fnam �t�@�C����
 * @param[out] o_bmp �r�b�g�}�b�v
 * @return UnicodeString �t�@�C���� [TAB] �\�����
 */
UnicodeString load_ImageThumbCache(UnicodeString fnam, Graphics::TBitmap *o_bmp);

/**
 * @brief �O���[�o���ϐ��Ȃǂ̏�����
 */
void InitializeGlobal();

/**
 * @brief ��Еt��
 */
void EndGlobal();

/**
 * @brief OS�o�[�W���������擾
 * @return UnicodeString 
 */
UnicodeString get_OsVerInfStr();

/** @brief �^�C�}�[�ݒ�̍X�V */
void SetupTimer();

/** @brief �������Ԃ̉��� */
void ClearNopStt();

/** @brief �I�v�V�����ݒ�̓ǂݍ��� */
void LoadOptions();

/** @brief �I�v�V�����ݒ�̕ۑ� */
void SaveOptions();

/** @brief INI�t�@�C�����X�V */
void UpdateIniFile(UsrIniFile *ini_file);

void BringOptionByTag(TForm *fp);
int  GetOptionIntDef(int tag);
void ApplyOptionByTag(TComponent *cp);
void ApplyOptionByTag(TForm *fp);
void ApplyOptionByTag(TTabSheet *sp);
void ApplyOptionByTag(TPanel *pp);

void SetToolWinBorder(TForm *fp, bool sw = true, TColor col = col_TlBorder);

/** @brief �ꗗ�p�O���b�h�̏����� */
void InitializeListGrid(TStringGrid *gp, TFont *font = NULL);

/** @brief �ꗗ�p�w�b�_�̏����� */
void InitializeListHeader(THeaderControl *hp, const _TCHAR *hdr, TFont *font = NULL);

void set_ComboBox_AutoComp(TForm *frm);
void set_MigemoCheckBox(TCheckBox *cp, const _TCHAR *key, UnicodeString sct = EmptyStr);
void set_MigemoAction(TAction *ap, const _TCHAR *key, UnicodeString sct = EmptyStr);
void change_ComboBoxHistory(TComboBox *cp, const _TCHAR *nrm_sct, const _TCHAR *reg_sct, bool reg_sw);

/**
 * @brief ���X�g�̍i�荞��
 * @param i_lst �Ώۃ��X�g
 * @param[out] o_lst ���ʃ��X�g 
 * @param kwd ������
 * @param opt �����I�v�V����
 */
void filter_List(TStringList *i_lst, TStringList *o_lst, UnicodeString kwd, SearchOption opt);

/** @brief �L�[�Ɋ��蓖�Ă��Ă���t�@�C���[�E�R�}���h���擾 */
UnicodeString Key_to_CmdF(UnicodeString key);

/** @brief �L�[�Ɋ��蓖�Ă��Ă���e�L�X�g�r���[�A�E�R�}���h���擾 */
UnicodeString Key_to_CmdV(UnicodeString key);

bool is_ToLeftOpe(UnicodeString keystr, UnicodeString cmdstr);
bool is_ToRightOpe(UnicodeString keystr, UnicodeString cmdstr);

/**
 * @brief �R�}���h�ɑ΂��������������擾
 * @param cmd �R�}���h
 * @param only_inf �����̂ݎ擾
 * @param menu_list �ǉ����j���[
 * @param tool_list �O���c�[��
 * @param is_TV �e�L�X�g�r���[�A�E�R�}���h
 * @return UnicodeString 
 */
UnicodeString get_CmdDesc(UnicodeString cmd, bool only_inf = false,
	TStrings *menu_list = NULL, TStrings *tool_list = NULL, bool is_TV = false);

/** @brief �֎~�����^���[�U��`�����̕ϊ� */
UnicodeString ApplyCnvCharList(UnicodeString s);

TColor read_ColorList(UnicodeString key, TColor def, TStringList *lst = NULL);
TColor read_ColorList(const _TCHAR *key, TColor def, TStringList *lst = NULL);
void set_col_from_ColorList();

/** @brief �ҏW������ǉ� */
void add_TextEditHistory(UnicodeString fnam);

/** @brief �Ăяo���z�b�g�L�[�̓o�^ */
bool register_HotKey(int id, UnicodeString kstr);

void set_FormTitle(TForm *frm, const _TCHAR *s);

/** @brief �x���� */
void beep_Warn(UnicodeString fnam = EmptyStr);

/** @brief �^�C�g���o�[�̓_�� */
void flash_win(int cnt = 0, int tm = 0);

/** @brief ���ʃ~���[�g */
bool mute_Volume(UnicodeString prm);

/** @brief �T�E���h�Đ� */
bool play_sound(UnicodeString fnam);
bool play_sound_id(UnicodeString id);
bool play_sound_ex(UnicodeString fnam, bool limit = true);

bool add_PlayFile(UnicodeString fnam);
bool add_PlayList(UnicodeString lnam);
bool play_PlayList(bool prev = false, bool inh_shfl = false);
bool is_ListPlaying();

void set_CloseButton(bool enabled);

/**
 * @brief �^�u���l�����ĕ����񕝂��擾
 * @param s �Ώە�����
 * @param cv �L�����o�X
 * @param tab_wd �^�u�X�g�b�v��
 * @return int 
 */
int  get_TabTextWidth(UnicodeString s, TCanvas *cv, int tab_wd);

void out_Text(TCanvas *cv, int x, int y, const _TCHAR *s);
void out_Text(TCanvas *cv, int x, int y, const _TCHAR *s, TColor fg);
void out_TextEx(TCanvas *cv, int &x, int y, UnicodeString s, TColor fg = col_None, TColor bg = col_None, int mgn = 0);
void out_TextRect(TCanvas *cv, TRect &rc, UnicodeString s, TColor fg = col_None, TColor bg = col_None);

/**
 * @brief ������ɑ΂���}�b�`��̃��X�g���擾
 * @param lbuf �Ώە�����
 * @param kwd ������
 * @param opt �I�v�V����
 * @param[out] lst �}�b�`�ꃊ�X�g
 * @return int �}�b�`�� 
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

/** @brief �e�L�X�g�G�f�B�^�ŊJ�� */
bool open_by_TextEditor(UnicodeString fnam, int lno = 0);

void ini_HtmConv_def(HtmConv *htmcnv, UnicodeString fnam = EmptyStr, UnicodeString url = EmptyStr);

/**
 * @brief �w��t�@�C�������s/�J��
 * @param cmd ���s�t�@�C��/�t�H���_��/CLSId �Ȃ�
 * @param prm �p�����[�^
 * @param wdir ��ƃf�B���N�g��
 * @param opt �I�v�V����
 * @param[out] exit_code �I���R�[�h
 * @param[out] o_lst �o�̓��X�g
 * @return true 
 * @return false 
 */
bool Execute_ex(UnicodeString cmd, UnicodeString prm = EmptyStr, UnicodeString wdir = EmptyStr,
		UnicodeString opt = EmptyStr, DWORD *exit_code = NULL, TStringList *o_lst = NULL);

/**
 * @brief �R�}���h���C�������s
 * @param cmdln �R�}���h���C��
 * @param wdir ��ƃf�B���N�g��
 * @param opt �I�v�V����
 * @param[out] exit_code �I���R�[�h
 * @param[out] o_lst �o�̓��X�g
 * @param[out] o_ms �o�̓C���[�W 
 * @param rq_abort ���f�v��
 * @return true 
 * @return false 
 */
bool Execute_cmdln(UnicodeString cmdln, UnicodeString wdir = EmptyStr,
		UnicodeString opt = EmptyStr, DWORD *exit_code = NULL, TStringList *o_lst = NULL, TMemoryStream *o_ms = NULL,
			bool *rq_abort = NULL);

/**
 * @brief ��ʃ��[�U�ɍ~�i���Ď��s
 * @param cmd �R�}���h
 * @param prm �p�����[�^
 * @param wdir ��ƃf�B���N�g��
 * @return true 
 * @return false 
 */
bool Execute_demote(UnicodeString cmd, UnicodeString prm = EmptyStr, UnicodeString wdir = EmptyStr);

/**
 * @brief git.exe �����s
 * @param prm �p�����[�^
 * @param wdir ��ƃf�B���N�g��
 * @param[out] o_lst �o�̓��X�g
 * @param[out] exit_cd �I���R�[�h
 * @param[out] w_lst �x�����X�g(�o�͂��番�����Ď擾) 
 * @param rq_abort ���f�v��
 * @return true 
 * @return false 
 */
bool GitShellExe(UnicodeString prm, UnicodeString wdir, TStringList *o_lst, DWORD *exit_cd = NULL,
		TStringList *w_lst = NULL, bool *rq_abort = NULL);
bool GitShellExe(UnicodeString prm, UnicodeString wdir, TMemoryStream *o_ms, DWORD *exit_cd = NULL);
bool GitShellExe(UnicodeString prm, UnicodeString wdir);
void split_GitWarning(TStringList *o_lst, TStringList *w_lst = NULL);

/** @brief �w�胊�r�W�����̃t�@�C�����ꎞ�f�B���N�g���ɕۑ� */
UnicodeString save_GitRevAsTemp(UnicodeString id, UnicodeString fnam, UnicodeString wdir);

/**
 * @brief grep.exe �����s
 * @param prm �p�����[�^
 * @param wdir ��ƃf�B���N�g��
 * @param[out] o_lst �o�̓��X�g
 * @param[out] exit_cd �I���R�[�h
 * @param[out] rq_abort ���f�v��
 * @return true 
 * @return false 
 */
bool GrepShellExe(UnicodeString prm, UnicodeString wdir, TStringList *o_lst, DWORD *exit_cd = NULL, bool *rq_abort = NULL);

/** @brief ���s/�ҋ@���̃^�X�N�����擾 */
int  get_BusyTaskCount();

/** @brief �������s���܂ލő�^�X�N�����擾 */
int  get_MaxTaskCount();

/**
 * @brief �󂫃^�X�N�����邩�H
 * @param ex_sw �ő�^�X�N���𒴂��Ď擾
 * @return true 
 * @return false 
 */
bool has_EmptyTask(bool ex_sw = false);

/**
 * @brief �^�X�N�X���b�h���擾
 * @param cp �^�X�N�ݒ�
 * @param reserve �\�񂷂�
 * @param force �ۗ����ł������擾
 * @param ext_sw �ő�^�X�N���𒴂��Ď擾
 * @return TTaskThread* 
 */
TTaskThread * CreTaskThread(TaskConfig **cp, bool reserve = true, bool force = false, bool ext_sw = false);

/** �^�X�N�̊J�n�܂��͗\�� */
void ActivateTask(TTaskThread *tp, TaskConfig *cp);

/** �\��ۗ����ڂ̎��s */
void StartReserve();
bool StartReserve(int idx, bool ext_sw = false);

/** @brief �^�X�N�ɒᑬ���s��v�� */
void RequestSlowTask();

/** @brief �^�X�N�ŏ������̃t�@�C�����H */
bool is_OnTask(UnicodeString fnam);

UnicodeString get_LogErrMsg(UnicodeString msg = EmptyStr, bool add_cr = true, UnicodeString fnam = EmptyStr, int err_id = NO_ERROR);
void set_LogErrMsg(UnicodeString &msg, UnicodeString s = EmptyStr, UnicodeString fnam = EmptyStr, int err_id = NO_ERROR);

int get_TopMargin(TCanvas *cv);
int get_TopMargin2(TCanvas *cv);

/** @brief ���v�p�l���p��������擾 */
UnicodeString GetClockStr();

/** @brief �R�}���h�t�@�C���̉������I�v�V�����ݒ�ɔ��f */
void RenameOptCmdFile();

/** @brief �R�}���h�t�@�C���̎Q�Ə����擾 */
UnicodeString get_ref_CmdFile(UnicodeString fnam, TStringList *lst = NULL);

/** @brief �G�C���A�X���Q�Ƃ��Ă���L�[���擾(�J���}��؂蕶����) */
UnicodeString get_Alias_KeyStr(UnicodeString alias, TStringList *k_lst = NULL);

/** @brief ��������p�����O���ăp�����[�^�𒊏o */
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

/** @brief ���O���X�g�{�b�N�X�̍X�V */
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

/** @brief �f�B���N�g�����̓{�b�N�X */
UnicodeString inputbox_dir(const _TCHAR *tit, const _TCHAR *cmd);

bool is_FirstKey(UnicodeString id, UnicodeString keystr);
bool is_IniSeaKey(UnicodeString &keystr);

bool update_IncSeaWord(UnicodeString &kwd, UnicodeString keystr, bool fl_sw = false);

bool is_OneNrmCmd(UnicodeString cmds, bool no_prm = false);

bool MovListBoxFromFilter(TListBox *lp, UnicodeString key_str);
bool MovGridFromFilter(TStringGrid *gp, UnicodeString key_str);

/** @brief ���X�g�{�b�N�X�ł̃R�}���h���� */
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
 * @brief �ŏ��ɋN�����ꂽ NyanFi �̃n���h�����擾
 * @return HWND 
 */
HWND get_PrimNyanWnd();

/**
 * @brief NyanFi �̃��C����ʂ��H
 * @param hWnd 
 */
bool IsNyanfiWnd(HWND hWnd);

/**
 * @brief ��d�N�����ꂽ NyanFi �̃��C����ʂ��H
 * @param hWnd 
 */
bool IsNyanfi2Wnd(HWND hWnd);

/**
 * @brief �ŏ��ɋN�����ꂽ NyanFi �ɕ�����𑗏o
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
 * @brief �c���[���X�g��(��)�쐬
 * @param lst 
 * @param pnam 
 * @param chk_sw �������`�F�b�N
 */
void MakeTreeList(TStringList *lst, UnicodeString pnam, bool chk_sw = false);
bool AddPathToTreeList(TStringList *lst);

/**
 * @brief �R�}���h�����̒ǉ�
 * @param cmd �R�}���h
 * @param prm �p�����[�^
 * @param id ��ʃ��[�h
 * @param fnam �Ώۃt�@�C����
 */
void AddCmdHistory(UnicodeString cmd, UnicodeString prm = EmptyStr, UnicodeString id = EmptyStr, UnicodeString fnam = EmptyStr);

//Git �֘A�̊֐�
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
 * @brief �c�[���`�b�v (�z�F�ύX�̂��߂ɃT�u�N���X��)
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
