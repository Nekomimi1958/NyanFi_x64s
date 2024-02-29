/**
 * @file usr_cmdlist.h
 * @brief �R�}���h�ꗗ
 */
//---------------------------------------------------------------------------
#ifndef UsrCmdListH
#define UsrCmdListH

//---------------------------------------------------------------------------
#include "usr_str.h"

//---------------------------------------------------------------------------
#define HASH_ALG_LIST	_T("MD5\nSHA1\nSHA256\nSHA384\nSHA512\nCRC32\n")

//---------------------------------------------------------------------------
extern UnicodeString ScrModeIdStr;

//---------------------------------------------------------------------------
/**
 * @brief �R�}���h�ꗗ���X�g��ݒ�
 * 
 * @param[out] c_list ���X�g(�R�}���h��=����)
 * @param[out] s_list ���X�g(���ʕ���:�R�}���h��=����)
 */
void set_CmdList(TStringList *c_list, TStringList *s_list);

/**
 * @brief �R�}���h�̃p�����[�^�ꗗ���擾
 * 
 * @param cmd �R�}���h
 * @param id_idx "FSVIL"���[�h�̃C���f�b�N�X(0�x�[�X)
 * @param[out] p_list �p�����[�^�ꗗ
 * @param cp �R���{�{�b�N�X
 */
void get_PrmList(UnicodeString cmd, int id_idx, TStringList *p_list, TComboBox *cp = NULL);

/**
 * @brief �t�@�C��/�f�B���N�g���Q�Ƃ��K�v���H
 * 
 * @param cmd �R�}���h
 * @return true �K�v
 */
bool need_RefDirFile(UnicodeString cmd);

/**
 * @brief �R�}���h�p�����[�^���������������폜
 * @param cmd �R�}���h
 * @return UnicodeString 
 */
UnicodeString del_CmdDesc(UnicodeString cmd);

/**
 * @brief �J�[�\���L�[���R�}���h�ɕϊ�
 * @param key_str �L�[������
 * @return UnicodeString �R�}���h
 */
UnicodeString get_CsrKeyCmd(UnicodeString key_str);

//---------------------------------------------------------------------------
/** @brief �R�}���h�������擾 */
inline UnicodeString get_CmdStr(UnicodeString s)
{
	return starts_AT(s)? s : get_tkn(s, '_');
}

/** @brief �p�����[�^�������擾 */
inline UnicodeString get_PrmStr(UnicodeString s)
{
	return get_tkn_r(s, '_');
}
//---------------------------------------------------------------------------
#endif
