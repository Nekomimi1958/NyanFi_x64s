/**
 * @file usr_file_ex.h
 * @brief �t�@�C������p�̔ėp�֐�
 */
//---------------------------------------------------------------------------
#ifndef UsrFileExH
#define UsrFileExH

//---------------------------------------------------------------------------
#include <winternl.h>

//---------------------------------------------------------------------------
/** �p�X�t���t�@�C�����̃}�b�`�p�^�[��*/
#define PATH_MATCH_PTN	"^(([a-z]:)|(%\\w+%)|(\\\\\\\\[^\\\\]+))\\\\(.+?\\\\)*.+$"

//---------------------------------------------------------------------------
#define	FileRenameInformation (FILE_INFORMATION_CLASS)10

typedef struct _FILE_RENAME_INFORMATION {
	BOOLEAN ReplaceIfExists;
	HANDLE	RootDirectory;
	ULONG	FileNameLength;
	WCHAR	FileName[1];
} FILE_RENAME_INFORMATION, *PFILE_RENAME_INFORMATION;

typedef LONG (WINAPI *FUNC_NtSetInformationFile)(HANDLE, PIO_STATUS_BLOCK, PVOID, ULONG, FILE_INFORMATION_CLASS);

//---------------------------------------------------------------------------
extern UnicodeString ExePath;	//!< NyanFi.exe �̏ꏊ

//---------------------------------------------------------------------------
int __fastcall FileComp_Base(TStringList *List, int Index1, int Index2);

/**
 * @brief 260�����ȏ�̃p�X���ɑΉ����邽�߂̃t�@�C�����ϊ�
 * @details �w��t�@�C�������A260�����ȏ�̃p�X���ɑΉ��ł���`���ɕϊ����܂��B
 * �������󔒂̏ꍇ�Ȃǂɂ��Ή��ł��܂��B
 * @param fnam �Ώۃt�@�C����
 * @return UnicodeString
 */
UnicodeString cv_ex_filename(UnicodeString fnam);

/**
 * @brief ���ϐ��̕ϊ�
 * @param s �Ώە�����
 * @return UnicodeString
 */
UnicodeString cv_env_var(UnicodeString s);

/**
 * @brief ���ϐ����܂ޕ������ϊ�
 * @param s �Ώە�����
 * @return UnicodeString
 */
UnicodeString cv_env_str(UnicodeString s);

/**
 * @brief ���ϐ��⏑����������܂ޕ����񂩂���ۂ̃p�X�����擾
 * @param pnam �Ώە�����
 * @return UnicodeString
 */
UnicodeString get_actual_path(UnicodeString pnam);

/**
 * @brief �p�X���ʂ��Ă���ꍇ�A�p�X�����t�@�C�������p�X�t���ɕϊ�
 * @param fnam �Ώۃt�@�C����
 * @param sw_fmt �����������W�J
 * @return UnicodeString
 */
UnicodeString get_actual_name(UnicodeString fnam, bool sw_fmt = false);

/**
 * @brief �p�X���ʂ��Ă���ꍇ�A�t�@�C��������p�X�Ɗg���q����菜��
 * @param fnam �Ώۃt�@�C����
 * @return UnicodeString
 */
UnicodeString exclude_env_path(UnicodeString fnam);

/**
 * @brief ���s�t�@�C���̃f�B���N�g������̑��΃t�@�C�����ɕϊ�
 * @param fnam �Ώۃt�@�C����
 * @return UnicodeString
 */
UnicodeString to_relative_name(UnicodeString fnam);

/**
 * @brief ��΃p�X�ɕϊ�(�h���C�u�����܂ޏꍇ�͐��K��)
 * @param fnam �Ώۃt�@�C����
 * @param rnam ��f�B���N�g����(EmptyStr: ExePath)
 * @return UnicodeString
 */
UnicodeString to_absolute_name(UnicodeString fnam, UnicodeString rnam = EmptyStr);

/**
 * @brief ��փf�[�^�X�g���[�����l�������p�X���̎擾
 * @param fnam �Ώۃt�@�C����
 * @return UnicodeString �p�X��
 */
UnicodeString extract_file_path(UnicodeString fnam);

/**
 * @brief ����t�@�C�����H
 * @param fnam1 �t�@�C����1
 * @param fnam2 �t�@�C����2
 * @param rnam ��f�B���N�g����(EmptyStr: ExePath)
 * @return true
 * @return false
 */
bool is_same_file(UnicodeString fnam1, UnicodeString fnam2, UnicodeString rnam = EmptyStr);

/**
 * @brief ����f�B���N�g�����H (���ϐ��Ή�)
 * @param dir1 �f�B���N�g����1
 * @param dir2 �f�B���N�g����2
 * @return true
 * @return false
 */
bool is_same_dir(UnicodeString dir1, UnicodeString dir2);

/**
 * @brief �p�X���X�g�Ƀ}�b�`���邩�H
 * @param dnam �`�F�b�N�Ώ�
 * @param plist �p�X���X�g(���ϐ��A%ExePath% �Ή�)
 * @param start_sw �O����v(false:������v)
 * @return true
 * @return false
 */
bool match_path_list(UnicodeString dnam, UnicodeString plist, bool start_sw = false);

/**
 * @brief ���[�g��(�h���C�u���܂���UNC�̃R���s���[�^��)���擾
 * @param pnam �Ώۃp�X��
 * @return UnicodeString
 */
UnicodeString get_root_name(UnicodeString pnam);

/**
 * @brief ���ۂ̑召�����Ńt�@�C�������擾
 * @param fnam �Ώۃt�@�C����
 * @return UnicodeString
 */
UnicodeString get_case_name(UnicodeString fnam);

/**
 * @brief ���[�g�f�B���N�g�����H
 * @param dnam �Ώۃp�X��
 * @return true
 * @return false
 */
bool is_root_dir(UnicodeString dnam);

/**
 * @brief UNC�p�X�̃��[�g���H
 * @param dnam �Ώۃp�X��
 * @return true
 * @return false
 */
bool is_root_unc(UnicodeString dnam);

/**
 * @brief �f�B���N�g�������[�g�̏ꍇ�A������ \ ����菜��
 * @param dnam �Ώۃp�X��
 * @return UnicodeString
 */
UnicodeString exclede_delimiter_if_root(UnicodeString dnam);

/**
 * @brief �h���C�u��(�啶���A\�t��)���擾
 * @param dnam �Ώۃp�X��
 * @return UnicodeString
 */
UnicodeString get_drive_str(UnicodeString dnam);

/**
 * @brief �L���ȃh���C�u���H
 * @param drv �h���C�u��
 * @return true
 * @return false
 */
bool drive_exists(UnicodeString drv);

/**
 * @brief �h���C�u�̎�ނ��擾
 * @param dnam �Ώۃp�X��
 * @return UINT
 */
UINT get_drive_type(UnicodeString dnam);

/**
 * @brief �N���X�^�T�C�Y���擾
 * @param dnam �Ώۃp�X��
 * @return int
 */
int get_ClusterSize(UnicodeString dnam);

/**
 * @brief �t�@�C���̃x�[�X�����擾
 * @param fnam �Ώۃt�@�C����
 * @return UnicodeString
 */
UnicodeString get_base_name(UnicodeString fnam);

/**
 * @brief �g���q���擾
 * @Note  ���O�� . �Ŏn�܂�ꍇ(�h�b�g�t�@�C��)�A���̒���̕����͊g���q�Ƃ݂Ȃ���܂���B
 * @param fnam �Ώۃt�@�C����
 * @return UnicodeString
 */
UnicodeString get_extension(UnicodeString fnam);

/**
 * @brief �Ώۂ��t�@�C���Ȃ�g���q���擾
 * @param fnam �Ώۃt�@�C����
 * @return UnicodeString
 */
UnicodeString get_extension_if_file(UnicodeString fnam);

UnicodeString nrm_FileExt(UnicodeString fext);

/**
 * @brief �g���q�̃`�F�b�N
 * @details �Ώۊg���q���A�w�肵���g���q���X�g�Ɋ܂܂�Ă��邩���ׂ܂��B@n
 * �g���q���X�g�́A. �ŋ�؂�ꂽ�g���q�̕��тł�(��: ".txt.html.md")�B
 * @param fext �Ώۊg���q
 * @param list �g���q���X�g
 * @return true �܂܂�Ă���
 * @return false �܂܂�Ă��Ȃ�
 */
bool test_FileExt(UnicodeString fext, UnicodeString list);

/**
 * @brief �g���q�̃`�F�b�N(�T�C�Y�w��\)
 * @details �Ώۊg���q���A�w�肵���g���q���X�g�Ɋ܂܂�Ă��邩���ׂ܂��B@n
 * �g���q���X�g�́A. �ŋ�؂�ꂽ�g���q�̕��тł��B@n
 * �g���q�̌�� : �ŋ�؂��Đ����T�C�Y(MB�P��)���w��ł��܂��B���̏ꍇ�A�t�@�C���T�C�Y�������T�C�Y�������ƃ}�b�`���܂���B@n
 * ��: ".exe:100.dll"
 * @param fext �Ώۊg���q
 * @param list �g���q���X�g
 * @param size �t�@�C���T�C�Y
 * @return true �܂܂�Ă���(�����T�C�Y�ȏ�)
 * @return false �܂܂�Ă��Ȃ�
 */
bool test_FileExtSize(UnicodeString fext, UnicodeString list, __int64 size);

/**
 * @brief �f�B���N�g�����̖����Ɂu\�v��t��
 * @details �Ώۃf�B���N�g�����̖����ɋ�؂蕶���u\�v��t�����܂��BEmptyStr �̏ꍇ�� EmptyStr ��Ԃ��܂��B
 * @param dnam �Ώۃf�B���N�g����
 * @return UnicodeString
 */
UnicodeString to_path_name(UnicodeString dnam);

/**
 * @brief �f�B���N�g����(�����́u\�v����)���擾
 * @param dnam �Ώۃf�B���N�g����
 * @return UnicodeString
 */
UnicodeString get_dir_name(UnicodeString dnam);

/**
 * @brief �e�f�B���N�g�����擾
 * @param dnam �Ώۃf�B���N�g����
 * @return UnicodeString 
 */
UnicodeString get_parent_path(UnicodeString dnam);

/**
 * @brief �K�؂�FTP�p�X�ɕϊ�
 * @param pnam 
 * @return UnicodeString 
 */
UnicodeString nrm_ftp_path(UnicodeString pnam);

/**
 * @brief �Ώۃp�X���𕪉����� TStringDynArray ���쐬
 * @param pnam �Ώۃp�X��
 * @param dlmt �f�B���N�g����؂�
 * @return TStringDynArray 
 */
TStringDynArray split_path(UnicodeString pnam, UnicodeString dlmt);

/**
 * @brief �Ώۃp�X���𕪉����� TStringDynArray ���쐬
 * @param pnam �Ώۃp�X��
 * @return TStringDynArray 
 */
TStringDynArray split_path(UnicodeString pnam);

/**
 * @brief "UNC�p�X:���[�U��" ���烆�[�U���𕪗�
 * @param dnam �p�X��
 * @return UnicodeString
 */
UnicodeString split_user_name(UnicodeString &dnam);

/**
 * @brief �R���s���[�^�����H
 * @param pnam �Ώۃp�X��
 * @return true
 * @return false
 */
bool is_computer_name(UnicodeString pnam);

/**
 * @brief �f�B���N�g�����A�N�Z�X�\���H
 * @param dnam �Ώۃp�X��
 * @return true
 * @return false
 */
bool is_dir_accessible(UnicodeString dnam);

/**
 * @brief �h���C�u���A�N�Z�X�\���H
 * @param dnam �h���C�u������n�܂�p�X
 * @return true
 * @return false
 */
bool is_drive_accessible(UnicodeString dnam);

/**
 * @brief �h���C�u�����C�g�v���e�N�g����Ă��邩�H
 * @param dnam �h���C�u������n�܂�p�X
 * @return true
 * @return false
 */
bool is_drive_protected(UnicodeString dnam);

/**
 * @brief NTFS���k�����̐ݒ�
 * @param fnam �Ώۃt�@�C����
 * @param sw ���k
 * @return true
 * @return false
 */
bool set_CompressAttr(UnicodeString fnam, bool sw);

/**
 * @brief �t�@�C���̑������擾
 * @param fnam �Ώۃt�@�C����
 * @return int �����l(TSearchRec.Attr �Ɠ���)
 */
int  file_GetAttr(UnicodeString fnam);

/**
 * @brief �t�@�C���̑�����ݒ�
 * @param fnam �Ώۃt�@�C����
 * @param attr �����l(TSearchRec.Attr �Ɠ���)
 * @return true ����
 * @return false ���s
 */
bool file_SetAttr(UnicodeString fnam, int attr);

/**
 * @brief �f�B���N�g���̑������R�s�[
 * @param src_nam �R�s�[���f�B���N�g����
 * @param dst_nam �R�s�[��f�B���N�g����
 * @param remove_ro �Ǎ���p����������
 * @return true ����
 * @return false ���s
 */
bool dir_CopyAttr(UnicodeString src_nam, UnicodeString dst_nam, bool remove_ro = false);

/**
 * @brief �t�@�C���̓ǂݏo����p����������
 * @param fnam �Ώۃt�@�C����
 * @return true ����
 * @return false ���s
 */
bool set_FileWritable(UnicodeString fnam);

/**
 * @brief ���p�[�X�|�C���g?
 * @param fnam �Ώۃt�@�C����
 * @return true
 * @return false
 */
bool is_SymLink(UnicodeString fnam);

/**
 * @brief �����N�J�E���g���擾
 * @param fnam �Ώۃt�@�C����
 * @return int �����N�J�E���g(2�ȏ�Ȃ�n�[�h�����N)
 */
int  get_HardLinkCount(UnicodeString fnam);

/**
 * @brief �t�@�C���̓��ꐫ�`�F�b�N
 * @param fnam1 �Ώۃt�@�C����1
 * @param fnam2 �Ώۃt�@�C����2
 * @return true
 * @return false
 */
bool is_IdenticalFile(UnicodeString fnam1, UnicodeString fnam2);

/**
 * @brief �t�@�C���̑��݃`�F�b�N
 * @param fnam �Ώۃt�@�C����
 * @return true ���݂���
 * @return false ���݂��Ȃ�
 */
bool file_exists(UnicodeString fnam);

/**
 * @brief �t�@�C���̑��݃`�F�b�N
 * @details �t�@�C���̑��݂��`�F�b�N���܂��B�Ώۂ��f�B���N�g���������ꍇ�͐������܂���B
 * @param fnam �Ώۃt�@�C����
 * @return true �t�@�C���Ƃ��đ��݂���
 * @return false �t�@�C���Ƃ��đ��݂��Ȃ�
 */
bool file_exists_x(UnicodeString fnam);

/**
 * @brief �t�@�C���̑��݃`�F�b�N
 * @details �t�@�C���̑��݂��`�F�b�N���܂��B�t�@�C������"���O,�C���f�b�N�X"�Ƃ����`���������ꍇ�A, �ȍ~�������ă`�F�b�N���܂��B
 * @param fnam �Ώۃt�@�C����
 * @return true
 * @return false
 */
bool file_exists_ico(UnicodeString fnam);

/**
 * @brief �t�@�C��(���C���h�J�[�h��)�̑��݃`�F�b�N
 * @details �t�@�C��(���C���h�J�[�h��)�̑��݃`�F�b�N���s���܂��Bfnm �ɂ́A�ŏ��Ƀ}�b�`�����t�@�C�������Ԃ�܂��B
 * @param[in,out] fnam �t�@�C����(���C���h�J�[�h��)
 * @return true
 * @return false
 */
bool file_exists_wc(UnicodeString &fnam);

/**
 * @brief �f�B���N�g���̑��݃`�F�b�N
 * @param dnam �Ώۃf�B���N�g����
 * @return true
 * @return false
 */
bool dir_exists(UnicodeString dnam);

/**
 * @brief ���E���莞�������[�J���� TDateTime �ɕϊ�
 * @param utc ���E���莞��
 * @return TDateTime ���[�J������
 */
TDateTime utc_to_DateTime(FILETIME *utc);

/**
 * @brief �t�@�C���̃^�C���X�^���v�� TDateTime �^�Ŏ擾
 * @param fnam �Ώۃt�@�C����
 * @return TDateTime �^�C���X�^���v(�X�V����)
 */
TDateTime get_file_age(UnicodeString fnam);

/**
 * @brief �t�@�C���T�C�Y���擾
 * @param fnam �t�@�C����
 * @return __int64 �T�C�Y
 */
__int64 get_file_size(UnicodeString fnam);

/**
 * @brief ���k�T�C�Y���擾
 * @param fnam �t�@�C����
 * @return __int64 ���k�T�C�Y
 */
__int64 get_comp_size(UnicodeString fnam);

/**
 * @brief ��փf�[�^�X�g���[���t���p�X�����H
 * @param fnam �t�@�C����
 * @return true
 * @return false
 */
bool is_ADS_name(UnicodeString fnam);

/**
 * @brief ��փf�[�^�X�g���[���̋�؂�ʒu���擾
 * @param fnam �t�@�C����
 * @return int ��؂�̈ʒu
 */
int  pos_ADS_delimiter(UnicodeString fnam);

/**
 * @brief ��փf�[�^�X�g���[���t���p�X���𕪉�
 * @details ��փf�[�^�X�g���[���t���p�X�����A�t�@�C�����ƃX�g���[�����ɕ������܂��B
 * �t�@�C�����������߂�l�ɂȂ�A�X�g���[������ fnam �ɐݒ肳��܂��B
 * @param[in,out] fnam �t�@�C����
 * @return UnicodeString �t�@�C����
 */
UnicodeString split_ADS_name(UnicodeString &fnam);

/**
 * @brief ��փf�[�^�X�g���[���̍폜
 * @param fnam �t�@�C����
 * @param force �Ǎ���p�ł������I�ɕύX
 * @param mask �}�X�N
 * @param[out] lst �폜�����X�g���[�����̃��X�g
 * @retval 1 ����
 * @retval 0 ���s(lst->Text �ɃG���[���b�Z�[�W)
 * @retval -1 ADS�Ȃ�
 */
int delete_ADS(UnicodeString fnam, bool force = false, UnicodeString mask = "*", TStringList *lst = NULL);

/**
 * @brief ��փf�[�^�X�g���[�����̕ύX
 * @param fnam ���t�@�C����:�X�g���[����
 * @param new_name :�V�X�g���[����
 * @return true ����
 * @return false ���s
 */
bool rename_ADS(UnicodeString fnam, UnicodeString new_name);

/**
 * @brief �w��f�B���N�g�������݂��Ȃ��ꍇ�ɍ쐬
 * @param dnam �f�B���N�g����
 * @return UnicodeString �f�B���N�g����(�쐬�ł��Ȃ������ꍇ EmptyStr)
 */
UnicodeString chk_cre_dir(UnicodeString dnam);

/**
 * @brief ��f�B���N�g�����H
 * @param dnam �Ώۃf�B���N�g����
 * @param no_file �t�@�C�����܂܂�Ă��Ȃ�
 * @return true
 * @return false
 */
bool is_EmptyDir(UnicodeString dnam, bool no_file = false);

/**
 * @brief ���p�\�ȃh���C�u�̃��X�g���擾
 * @param[out] lst �h���C�u�̃��X�g(�h���C�u����:\)
 * @return int
 */
int get_available_drive_list(TStringList *lst);

/**
 * @brief �t�@�C���̑�����������擾
 * @param atr �����l
 * @return UnicodeString ����������(RHSAC �܂܂Ȃ������� _)
 */
UnicodeString get_file_attr_str(int atr);

/**
 * @brief �w��f�B���N�g�����Ń}�X�N�ɊY������ŏ��̃t�@�C�����擾
 * @param pnam �Ώۃf�B���N�g����
 * @param mask �}�X�N
 * @param subSW �T�u�f�B���N�g�����`�F�b�N
 * @return UnicodeString �t�@�C����
 */
UnicodeString find_FirstFile(UnicodeString pnam, UnicodeString mask, bool subSW = false);

/**
 * @brief �w��f�B���N�g�����̃}�X�N�ɊY������S�t�@�C�����擾
 * @param pnam �Ώۃf�B���N�g����
 * @param mask �}�X�N
 * @param[out] lst �t�@�C�������X�g
 * @param subSW �T�u�f�B���N�g��������
 */
void get_files(UnicodeString pnam, UnicodeString mask, TStrings *lst, bool subSW = false);

/**
 * @brief �w��f�B���N�g�����̃}�X�N�ɊY������S�t�@�C���̃��X�g��ǉ��擾
 * @param pnam �Ώۃf�B���N�g����
 * @param mask �}�X�N
 * @param[out] lst �t�@�C�������X�g
 * @param subSW �T�u�f�B���N�g��������
 * @param subn �T�u�f�B���N�g���̊K�w�̐[��
 * @param skip_dir ���ODir�}�X�N(;�ŋ�؂蕡����)
 * @param inc_hide �B������������
 * @param inc_sys �V�X�e������������
 * @return int �t�@�C����(��f�B���N�g���͏���)
 */
int  get_all_files_ex(UnicodeString pnam, UnicodeString mask, TStrings *lst,
	bool sub_sw = false, int sub_n = 99, UnicodeString skip_dir = EmptyStr,
	bool inc_hide = true, bool inc_sys = true);

/**
 * @brief �w��f�B���N�g�����̑S�f�B���N�g�����擾
 * @param pnam �Ώۃf�B���N�g����
 * @param[out] lst �f�B���N�g�������X�g
 * @param subSW �T�u�f�B���N�g��������
 */
void get_dirs(UnicodeString pnam, TStrings *lst, bool subSW = true);

/**
 * @brief �w��t�@�C���Ƀ^�C���X�^���v(�X�V����)��ݒ�
 * @param fnam �Ώۃt�@�C����
 * @param dt �^�C���X�^���v(�X�V����)
 * @param force �Ǎ���p�ł������I�ɕύX
 * @return true ����
 * @return false ���s
 */
bool set_file_age(UnicodeString fnam, TDateTime dt, bool force = false);

/**
 * @brief ��̃t�@�C�����쐬
 * @param fnam �쐬�t�@�C����
 * @return true ����
 * @return false ���s
 */
bool create_EmptyFile(UnicodeString fnam);

/**
 * @brief �f�B���N�g���̍쐬
 * @param dnam �쐬�f�B���N�g����
 * @return true ����
 * @return false ���s
 */
bool create_Dir(UnicodeString dnam);

/**
 * @brief �f�B���N�g���̍쐬(�����K�w��)
 * @param dnam �쐬�f�B���N�g����
 * @return true ����
 * @return false ���s
 */
bool create_ForceDirs(UnicodeString dnam);

/**
 * @brief �f�B���N�g���̍폜
 * @param dnam �폜�f�B���N�g����
 * @param force �����I�ɍ폜
 * @return true ����
 * @return false ���s
 */
bool delete_Dir(UnicodeString dnam, bool force = false);

/**
 * @brief �T�u�f�B���N�g�����܂߂��f�B���N�g���̍폜
 * @param pnam �폜�f�B���N�g����
 * @return true ����
 * @return false ���s
 */
bool delete_Dirs(UnicodeString pnam);

/**
 * @brief �t�@�C���̈ړ�
 * @param old_nam �ړ����t�@�C����
 * @param new_nam �ړ���t�@�C����
 * @return true ����
 * @return false ���s
 */
bool move_File(UnicodeString old_nam, UnicodeString new_nam);

/**
 * @brief �t�@�C���̃R�s�[
 * @param src_nam �R�s�[���t�@�C����
 * @param dst_nam �R�s�[��t�@�C����
 * @return true ����
 * @return false ���s
 */
bool copy_File(UnicodeString src_nam, UnicodeString dst_nam);

/**
 * @brief �t�@�C�����O�̕ύX
 * @param old_nam ���̃t�@�C����
 * @param new_nam �ύX��̃t�@�C����
 * @return true ����
 * @return false ���s
 */
bool rename_File(UnicodeString old_nam, UnicodeString new_nam);

/**
 * @brief �p�X���̕ύX
 * @param old_nam ���̃p�X��
 * @param new_nam �ύX��̃p�X��
 * @return true ����
 * @return false ���s
 */
bool rename_Path(UnicodeString old_nam, UnicodeString new_nam);

//---------------------------------------------------------------------------
#ifndef REPARSE_DATA_BUFFER
typedef struct _REPARSE_DATA_BUFFER {
	ULONG  ReparseTag;
	USHORT ReparseDataLength;
	USHORT Reserved;

	union {
		struct {
		  USHORT SubstituteNameOffset;
		  USHORT SubstituteNameLength;
		  USHORT PrintNameOffset;
		  USHORT PrintNameLength;
		  ULONG  Flags;
		  WCHAR  PathBuffer[1];
		} SymbolicLinkReparseBuffer;

		struct {
		  USHORT SubstituteNameOffset;
		  USHORT SubstituteNameLength;
		  USHORT PrintNameOffset;
		  USHORT PrintNameLength;
		  WCHAR  PathBuffer[1];
		} MountPointReparseBuffer;

		struct {
		  UCHAR DataBuffer[1];
		} GenericReparseBuffer;
	};
} REPARSE_DATA_BUFFER, *PREPARSE_DATA_BUFFER;
#endif

//---------------------------------------------------------------------------
/**
 * @brief �W�����N�V�����̍쐬
 * @param pnam
 * @param target
 * @return true ����
 * @return false ���s
 */
bool cre_Junction(UnicodeString pnam, UnicodeString target);

//---------------------------------------------------------------------------
BYTE   fsRead_byte(TFileStream *fs);
int    fsRead_int2(TFileStream *fs, bool be_sw = false);
int    fsRead_int3(TFileStream *fs, bool be_sw = false);
int    fsRead_int4(TFileStream *fs, bool be_sw = false);
double fsRead_double(TFileStream *fs);
UnicodeString fsRead_char(TFileStream *fs, int size);
UnicodeString fsRead_comment_utf8(TFileStream *fs);

/**
 * @brief �t�@�C���̌��݈ʒu�Ɏw�蕶���񂪂��邩�H@n
          ����Β���ʒu�ցA������Ό��݈ʒu�̂܂�
 * @param fs �t�@�C���X�g���[��
 * @param s ������
 * @return true
 * @return false
 */
bool fsRead_check_char(TFileStream *fs, const char *s);

//---------------------------------------------------------------------------
inline UnicodeString warn_filename_RLO(UnicodeString fnam)
{
	return ReplaceStr(ExtractFileName(fnam), L"\u202e", "<RLO>");
}
//---------------------------------------------------------------------------
inline UnicodeString warn_pathname_RLO(UnicodeString pnam)
{
	return ReplaceStr(pnam, L"\u202e", "<RLO>");
}
//---------------------------------------------------------------------------
#endif
