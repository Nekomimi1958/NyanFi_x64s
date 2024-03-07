/**
 * @file usr_highlight.h
 * @brief �\�������\��
 */
//---------------------------------------------------------------------------
#ifndef UsrHighlightH
#define UsrHighlightH

//---------------------------------------------------------------------------
#include "UIniFile.h"

//---------------------------------------------------------------------------
/**
 * @brief �\�������\����`�t�@�C��
 */
class HighlightFile : public UsrIniFile
{
private:
	TDateTime HighlightTime;	//���݂̃^�C���X�^���v

	void CheckValues();

public:
	UnicodeString CurSection;	//!< �g�p���̃Z�N�V����
	TStringList   *ErrorList;

	HighlightFile(UnicodeString fnam);
	~HighlightFile();

	UnicodeString ReadKeyStr(const _TCHAR *key);
	int			  ReadKeyInt(const _TCHAR *key, int def = 0);
	bool		  ReadKeyBool(const _TCHAR *key, bool def = false);
	UnicodeString ReadRegExPtn(const _TCHAR *key);
	TColor		  ReadColorRGB6H(const _TCHAR *key, TColor def = clBlack);

	/** @brief �^�C���X�^���v���ω����Ă�����ēǂݍ��� */
	bool Recycle();

	/**
	 * @brief �\�������\����`�t�@�C������Ή��Z�N�V�������擾
	 * @param fnam �t�@�C����
	 * @param is_clip �N���b�v�{�[�h
	 * @param is_log �^�X�N���O
	 * @param is_h2t HTML��TEXT�ϊ����[�h
	 * @return true �Z�N�V�������擾
	 */
	bool GetSection(UnicodeString fnam,
			bool is_clip = false, bool is_log = false, bool is_h2t = false);

	/**
	 * @brief �R�����g���ʕ�������擾
	 * @param fnam �t�@�C����
	 * @param ln_lst 1�s�R�����g
	 * @param bgn_lst �u���b�N�J�n
	 * @param end_lst �u���b�N�I��
	 * @param is_h2t HTML��TEXT�ϊ����[�h
	 * @param only_def �f�t�H���g�̂ݎ擾
	 * @return true �R�����g���ʕ����񂠂�
	 */
	bool GetCommentList(UnicodeString fnam,
			TStringList *ln_lst, TStringList *bgn_lst, TStringList *end_lst,
			bool is_h2t = false, bool only_def = false);

	/**
	 * @brief ���X�g�{�b�N�X�̎w��s�̃R�����g�J�n�ʒu���擾
	 * @param fnam �t�@�C����
	 * @param lp ���X�g�{�b�N�X
	 * @param idx �C���f�b�N�X
	 * @param en_mlt �����s�R�����g�ɑΉ�
	 * @return int �R�����g�J�n�ʒu
	 */
	int GetCommentPos(UnicodeString fnam, TListBox *lp, int idx, bool en_mlt = true);

	/**
	 * @brief �g���q�ˑ��̃f�t�H���g���o���p�^�[�����擾
	 * @param fext �g���q
	 * @return UnicodeString �f�t�H���g���o���p�^�[��
	 */
	UnicodeString GetDefHeadlnPtn(UnicodeString fext);

	/**
	 * @brief ���o���p�^�[�����擾
	 * 
	 * @param fnam �t�@�C����
	 * @param hl_lst �g���q�Ή����o�����X�g
	 * @param only_def �f�t�H���g�̂ݎ擾
	 * @return UnicodeString ���o���p�^�[��
	 */
	UnicodeString GetHeadlinePtn(UnicodeString fnam, TStringList *hl_lst = NULL, bool only_def = false);
};
//---------------------------------------------------------------------------
extern HighlightFile *UserHighlight;

//---------------------------------------------------------------------------
/**
 * @brief �f�t�H���g�̗\���p�^�[�����擾
 * @param fext �g���q
 * @param sns_case �召���������
 * @param is_xml �Ώۂ�XML
 * @param is_log �Ώۂ��^�X�N���O
 * @param is_h2t HTML��TEXT�ϊ����[�h
 * @return UnicodeString �\���p�^�[�� 
 */
UnicodeString GetDefReservedPtn(UnicodeString fext, bool &sns_case, bool is_xml, bool is_log, bool is_h2t);

/**
 * @brief �f�t�H���g�̐��l�p�^�[�����擾
 * @param fext �g���q
 * @return UnicodeString ���l�p�^�[��
 */
UnicodeString GetDefNumericPtn(UnicodeString fext);

/**
 * @brief �f�t�H���g�̃V���{���������擾
 * @param fext �g���q
 * @param is_xml �Ώۂ�XML
 * @param is_h2t HTML��TEXT�ϊ����[�h
 * @return UnicodeString 
 */
UnicodeString GetDefSymbolChars(UnicodeString fext, bool is_xml, bool is_h2t);

/**
 * @brief �f�t�H���g�̕�������p��
 * @param fext �g���q
 * @param[o] use_esc �G�X�P�[�v�V�[�P���X�L��
 * @param is_xml �Ώۂ�XML
 * @param is_ini �Ώۂ�INI�t�@�C������
 * @param is_h2t HTML��TEXT�ϊ����[�h
 * @return UnicodeString ��������p��
 */
UnicodeString GetDefQuotChars(UnicodeString fext, bool &use_esc, bool is_xml, bool is_ini, bool is_h2t);

/**
 * @brief �f�t�H���g�̊֐��p�^�[�����擾
 * @param fext �g���q
 * @param[out] name_ptn ���O�擾�p�^�[��
 * @param is_h2t HTML��TEXT�ϊ����[�h
 * @return UnicodeString �֐��p�^�[��
 */
UnicodeString GetDefFunctionPtn(UnicodeString fext, UnicodeString &name_ptn, bool is_h2t);

/**
 * @brief SearchPair �R�}���h�p�����p�^�[�����擾
 * @param fext �g���q
 * @param[out] lst �����p�^�[���̃��X�g
 * @return true �����p�^�[������
 */
bool GetSearchPairPtn(UnicodeString fext, TStringList *lst);

/**
 * @brief �f�t�H���g�̍\�������\����`���擾
 * @param fext �g���q
 * @param[out] lst ���ʃ��X�g
 * @param hl_lst �g���q�Ή����o�����X�g
 * @return true �\�������\����`����
 */
bool GetDefaultHighlight(UnicodeString fext, TStringList *lst, TStringList *hl_lst = NULL);
//---------------------------------------------------------------------------
#endif
