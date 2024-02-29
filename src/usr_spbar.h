/**
 * @file usr_spbar.h
 * @brief �X�e�[�^�X�o�[��̃v���O���X�o�[
 */
//---------------------------------------------------------------------------
#ifndef UsrSttPrgBarH
#define UsrSttPrgBarH

//---------------------------------------------------------------------------
#include <Vcl.ComCtrls.hpp>

//---------------------------------------------------------------------------
/**
 * @brief �w�肵���X�e�[�^�X�o�[�̃p�l����Ƀv���O���X�o�[��\��
 */
class SttProgressBar
{
private:
	TStatusBar *SttBar;
	int PrgIndex;
	double BarRatio;

	void __fastcall PrgBoxPaint(TObject *Sender);
	void __fastcall ResetPos();

public:
	TPaintBox *PrgBox;
	int MsgIndex;		//!< ���b�Z�[�W��\������p�l���̃C���f�b�N�X

	TColor BgColor;
	TColor BarColor;

	SttProgressBar(TStatusBar *sp, int idx);
	~SttProgressBar();

	/**
	 * @brief �v���O���X�o�[�\���J�n
	 * @param s �\�����b�Z�[�W
	 */
	void __fastcall Begin(const _TCHAR *s = NULL);

	/**
	 * @brief �v���O���X�o�[�\���I��
	 * @param s �\�����b�Z�[�W
	 * @param wait �B���܂ł̑҂�����(�~���b)
	 */
	void __fastcall End(UnicodeString s = EmptyStr, int wait = 100);

	/**
	 * @brief �w�肵���i���l�Ɋ�Â��ăv���O���X�o�[�̕\����ݒ�
	 * @param cnt �i���l
	 * @param max_cnt �ő�l
	 */
	void __fastcall SetPosI(int cnt, int max_cnt);
};
//---------------------------------------------------------------------------
#endif
