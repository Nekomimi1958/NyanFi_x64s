/**
 * @file grep_thread.h
 * @brief GREP�����X���b�h
 */
//---------------------------------------------------------------------------
#ifndef TGrepThreadH
#define TGrepThreadH

//---------------------------------------------------------------------------
#include <System.Classes.hpp>

//---------------------------------------------------------------------------
#define MAX_GREP_THREAD		4		//!< �ő�X���b�h��
#define REFRESH_INTERVAL	250		//!< ���C���t�H�[���̍X�V�Ԋu

//---------------------------------------------------------------------------
enum GrepOpt {goRegEx, goAnd, goCaseSens, goWord, goOneMatch, goExcludeTag};

/*** @brief �����I�v�V���� */
typedef Set <GrepOpt, goRegEx, goExcludeTag> GrepOption;

//---------------------------------------------------------------------------
/**
 * @brief GREP�����X���b�h
 */
class TGrepThread : public TThread
{
private:
	void __fastcall Execute();

	int ID;						//!< �X���b�h����ID
	int IndexTag;				//!< �C���f�b�N�X�^�O
	UnicodeString FileName;		//!< �Ώۃt�@�C����
	UnicodeString Keyword;		//!< ����������
	UnicodeString Filter;		//!< �t�B���^
	GrepOption    Options;		//!< �����I�v�V����

	TStringList *ResultList;
	void __fastcall AddResult();

public:
	/**
	 * @brief �R���X�g���N�^
	 * @param CreateSuspended 
	 * @param id �X���b�h����ID
	 * @param idx_tag �C���f�b�N�X�^�O
	 * @param fnam �Ώۃt�@�C����
	 * @param kwd ����������
	 * @param opt �����I�v�V����
	 * @param filter �t�B���^
	 */
	__fastcall TGrepThread(bool CreateSuspended, int id,
					int idx_tag, UnicodeString fnam, UnicodeString kwd,
					GrepOption opt, UnicodeString filter = EmptyStr);
};
//---------------------------------------------------------------------------
#endif
