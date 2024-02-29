/**
 * @file usr_tag.h
 * @brief �^�O�Ǘ����j�b�g
 */
//---------------------------------------------------------------------------
#ifndef UsrTagManagerH
#define UsrTagManagerH

//---------------------------------------------------------------------------
#include <Vcl.CheckLst.hpp>
#include "usr_str.h"

//---------------------------------------------------------------------------
/**
 * @brief �^�O�Ǘ����j�b�g
 */
class TagManager
{
private:
	TDateTime TagDataTime;		//���݂̃^�C���X�^���v
	bool Modified;

	TColor DefColor;			//�f�t�H���g�̃^�O�F

	int  GetIndex(UnicodeString fnam);
	void MakeTagNameList();

	UnicodeString GetDataTags(int idx)
	{
		return (idx!=-1)? get_post_tab(TagDataList->Strings[idx]) : EmptyStr;
	}

	UnicodeString GetDataTags(int idx, UnicodeString &fnam)
	{
		if (idx==-1) return EmptyStr;

		UnicodeString ret_str = TagDataList->Strings[idx];
		fnam = split_pre_tab(ret_str);
		return ret_str;
	}

public:
	UnicodeString FileName;
	bool SortTags;

	TStringList *TagNameList;
	TStringList *TagDataList;
	TStringList *TagColList;

	TMultiReadExclusiveWriteSynchronizer *TagRWLock;	//!< TagDataList �̕ی�p

	TagManager(UnicodeString fnam);
	~TagManager();

	bool UpdateFile();		//!< �t�@�C�����X�V
	bool Recycle();			//!< �^�C���X�^���v���ω����Ă�����ēǂݍ���
	int  TrimData();		//!< ���݂��Ȃ����ڂ̃^�O�f�[�^�𐮗�

	UnicodeString GetTags(UnicodeString fnam);							//!< �w��t�@�C���̃^�O���擾
	UnicodeString NormTags(UnicodeString tags, bool sw_add = true);
	void DelItem(UnicodeString fnam);									//!< �w��t�@�C���̃^�O�����폜
	void SetTags(UnicodeString fnam, UnicodeString tags);				//!< �w��t�@�C���Ƀ^�O��ݒ�
	void AddTags(UnicodeString fnam, UnicodeString tags);				//!< �w��t�@�C���Ƀ^�O��ǉ�
	void Rename(UnicodeString old_nam, UnicodeString new_nam);			//!< �t�@�C��/�f�B���N�g�����̕ύX
	void Copy(UnicodeString from_nam, UnicodeString to_nam);			//!< �^�O�̃R�s�[
	int  RenTag(UnicodeString old_tag, UnicodeString new_tag);			//!< �^�O�̉���
	int  DelTagData(UnicodeString tag);									//!< �^�O�f�[�^�̍폜

	int IniCheckList(TCheckListBox *lp, UnicodeString tnam = EmptyStr, bool count_sw = false);
	UnicodeString CheckToTags(TCheckListBox *lp, UnicodeString tags);
	void CountTags(TCheckListBox *lp, bool clr_sw = false);

	/**
	 * @brief �w��^�O�Ƀ}�b�`���郊�X�g���擾
	 * @param tags �^�O
	 * @param and_sw AND����
	 * @param[out] lst ���X�g
	 * @return int �}�b�`��
	 */
	int  GetMatchList(UnicodeString tags, bool and_sw, TStringList *lst);

	/**
	 * @brief ���ׂẴ^�O���ڂ̃��X�g���擾
	 * @param[out] lst ���X�g
	 * @return int
	 */
	int  GetAllList(TStringList *lst);

	/** @brief �t�@�C���Ƀ^�O���t�����Ă��邩�H */
	bool HasTag(UnicodeString fnam);

	/**
	 * @brief �t�@�C�����w��^�O�Ƀ}�b�`���邩�H
	 * @param fnam �t�@�C����
	 * @param ktags �^�O
	 * @param and_sw AND����
	 * @return true
	 * @return false
	 */
	bool Match(UnicodeString fnam, UnicodeString ktags, bool and_sw);

	/**
	 * @brief �^�O�F���擾
	 * @param tag �^�O
	 * @param col_def �f�t�H���g�F
	 * @return TColor
	 */
	TColor GetColor(UnicodeString tag, TColor col_def);

	/**
	 * @brief �^�O�F��ݒ�
	 * @param tag �^�O
	 * @param col �F
	 */
	void SetColor(UnicodeString tag, TColor col);

	/**
	 * @brief �^�O�̕`��
	 * @param tags �^�O
	 * @param cv �L�����o�X
	 * @param x X�ʒu
	 * @param y Y�ʒu
	 * @param col_rev �w��w�i�F�Ŕ��]�\��
	 * @param blk_sw �u���b�N�L����\��
	 */
	void DrawTags(UnicodeString tags, TCanvas *cv, int x, int y, TColor col_rev = Graphics::clNone, bool blk_sw = false);
};
//---------------------------------------------------------------------------
extern TagManager *usr_TAG;
//---------------------------------------------------------------------------
#endif
