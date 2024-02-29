/**
 * @file usr_scale.h
 * @brief �X�P�[�����O����
 */
//----------------------------------------------------------------------//
#ifndef UsrScaleH
#define UsrScaleH

//---------------------------------------------------------------------------
#include <Vcl.ComCtrls.hpp>
#include <Vcl.CheckLst.hpp>
#include <Vcl.Grids.hpp>

//---------------------------------------------------------------------------
#define DEFAULT_PPI	96	//!< �f�t�H���g(100\%��)��PPI�l

/**
 * @brief ���݂�PPI���擾
 * @param cp �ΏۃR���g���[��
 * @return int PPI�l
 */
inline int GetCurPPI(TControl *cp = NULL)
{
	return (			cp? cp->CurrentPPI : 
		Screen->ActiveForm? Screen->ActiveForm->CurrentPPI
						  : Application->MainForm->CurrentPPI);
}

//----------------------------------------------------------------------
/** @brief ���g�̃t�H�[���ŃX�P�[�����O���ꂽ�����l���擾 */
#define SCALED_THIS(n)		MulDiv(n, CurrentPPI, DEFAULT_PPI)

/** @brief ���g�̃t�H�[���ŃX�P�[�����O�����O(100\%��)�̐����l���擾 */
#define UNSCALED_THIS(n)	MulDiv(n, DEFAULT_PPI, CurrentPPI)

/** @brief ���C���t�H�[���ŃX�P�[�����O���ꂽ�����l���擾 */
#define SCALED_MAIN(n)		MulDiv(n, Application->MainForm->CurrentPPI, DEFAULT_PPI)

//----------------------------------------------------------------------
/**
 * @brief �X�P�[�����O���ꂽ�����l���擾
 * @param n �l
 * @param cp �ΏۃR���g���[��
 * @return int 
 */
inline int ScaledInt(int n, TControl *cp = NULL)
{
	return MulDiv(n, GetCurPPI(cp), DEFAULT_PPI);
}
//----------------------------------------------------------------------
/**
 * @brief �X�P�[�����O�����O(100\%��)�̐����l���擾
 * @param n �l
 * @param cp �ΏۃR���g���[��
 * @return int 
 */
inline int UnscaledInt(int n, TControl *cp = NULL)
{
	return MulDiv(n, DEFAULT_PPI, GetCurPPI(cp));
}

//----------------------------------------------------------------------
/**
 * @brief �V�X�e���E���g���b�N�̎擾
 * @param idx 
 * @param ppi 
 * @return int 
 */
inline int get_SysMetricsForPPI(int idx, int ppi)
{
	if (IsWindows10OrGreater())
		return GetSystemMetricsForDpi(idx, ppi);
	else
		return GetSystemMetrics(idx);
}

//---------------------------------------------------------------------------
/**
 * @brief �w��t�H���g�̕`�捂���擾
 * @param font �t�H���g
 * @param mgn �}�[�W��
 * @param min_mgn �ŏ��}�[�W��
 * @return int �`�捂
 */
int get_FontHeightMgn(TFont *font, int mgn = 0, int min_mgn = 2);

/**
 * @brief �w��t�H���g�̕`�捂���擾
 * @param font �t�H���g
 * @param mgn �}�[�W��(100\%���̒l�A�X�P�[�����O����ēK�p)
 * @param min_mgn �ŏ��}�[�W��(100\%���̒l�A�X�P�[�����O����ēK�p)
 * @return int �`�捂
 */
int get_FontHeightMgnS(TFont *font, int mgn = 0, int min_mgn = 2);

/**
 * @brief �X�P�[�����O���ꂽ�t�H���g�����蓖�Ă�
 * @param s_font ������̃t�H���g
 * @param font ���蓖�Ă�t�H���g
 * @param cp PPI���擾����R���g���[��
 * @param size �T�C�Y
 * @param col �����F
 */
void AssignScaledFont(TFont *s_font, TFont *font, TControl *cp, int size = 0, TColor col = Graphics::clNone);

/**
 * @brief �R���g���[���ɃX�P�[�����O���ꂽ�t�H���g��ݒ�
 * @param cp �ΏۃR���g���[��
 * @param font �t�H���g
 */
void AssignScaledFont(TWinControl *cp, TFont *font = NULL);

/**
 * @brief TLabel �ɃX�P�[�����O���ꂽ�t�H���g��ݒ�
 * @param lp �Ώۃ��x��
 * @param font �t�H���g
 */
void AssignScaledFont(TLabel *lp, TFont *font = NULL);

/**
 * @brief TPaintBox �ɃX�P�[�����O���ꂽ�t�H���g��ݒ�
 * @param pp �Ώۃy�C���g�{�b�N�X
 * @param font �t�H���g
 */
void AssignScaledFont(TPaintBox *pp, TFont *font = NULL);

/**
 * @brief �T�C�Y����X�P�[�����O���ꂽ�t�H���g�����擾
 * @param sz �T�C�Y
 * @param cp �ΏۃR���g���[��
 * @return int �t�H���g��
 */
int  ScaledFontHeight(int sz, TControl *cp);

//---------------------------------------------------------------------------
#endif

