/**
 * @file usr_color.h
 * @brief �J���[�����֘A�̊֐�
 */
//---------------------------------------------------------------------------
#ifndef UsrColorH
#define UsrColorH

//---------------------------------------------------------------------------
extern const TColor col_None;
extern const TColor col_Teal;

//---------------------------------------------------------------------------
/**
 * @brief �P�x���擾
 * @param col �ΏېF
 * @return double �P�x�l(0�`1.0)
 */
double GetLuminance(TColor col);

/**
 * @brief �F�ɔ{����������
 * @param col ���̐F
 * @param rt �{��(0.0�`1.0)
 * @return TColor 
 */
TColor RatioCol(TColor col, float rt);

/**
 * @brief �P�x�Ɋ�Â��ăO���[�X�P�[����
 * @param col ���̐F
 * @return TColor �O���[�X�P�[�������ꂽ�F
 */
TColor GrayCol(TColor col);

/**
 * @brief ��F���擾
 * @param col ���̐F
 * @return TColor ��F
 */
TColor ComplementaryCol(TColor col);

/** @brief RGB��HSL �ϊ� */
void RgbToHsl(TColor col, int *h, int *s, int *l);

/** @brief RGB��HSV �ϊ� */
void RgbToHsv(TColor col, int *h, int *s, int *v);

/** @brief RGB��HSV �ϊ� */
void RgbToHsv(BYTE r, BYTE g, BYTE b, int *h, int *s, int *v);

/** @brief HSL��RGB �ϊ� */
TColor HslToCol(int h, int s, int l);

/**
 * @brief �w�i�̋P�x���甒�܂��͍���I���E����
 * @param col �w�i�F
 * @param rt �����w��
 * @return TColor 
 */
TColor SelectWorB(TColor col, float rt = 1.0);

#define ADJCOL_FGLIST	96
#define ADJCOL_LIGHT	72
#define ADJCOL_BGMID	64
#define ADJCOL_BGLTL	48
#define ADJCOL_BGINV	32
#define ADJCOL_BGBIT	16

/**
 * @brief �P�x�Ɋ�Â��Ė��Â�����
 * @param col ���̐F
 * @param adj �����l (0�`255)
 * @return TColor 
 */
TColor AdjustColor(TColor col, int adj);

/** @brief �Q�F���� */
TColor Mix2Colors(TColor col1, TColor col2);

/**
 * @brief �����񂩂�J���[��ݒ�
 * @param[out] col 
 * @param s �����l��\��������
 */
void str_to_Color(TColor &col, UnicodeString s);

/**
 * @brief �X�^�C�����l�������E�B���h�E�w�i�F�̎擾
 * @param is_inv �����ȍ���
 * @return TColor 
 */
TColor get_WinColor(bool is_inv = false);

/**
 * @brief �X�^�C�����l�������E�B���h�E�����F�̎擾
 * @param is_hl �n�C���C�g
 * @return TColor 
 */
TColor get_TextColor(bool is_hl = false);

/**
 * @brief �X�^�C�����l�������p�l���F�̎擾
 * @param is_inv �����ȍ���
 * @return TColor 
 */
TColor get_PanelColor(bool is_inv = false);

/**
 * @brief �X�^�C�����l���������x�������F�̎擾
 * @param is_inv �����ȍ���
 * @return TColor 
 */
TColor get_LabelColor(bool is_inv = false);

void set_EditColor(TEdit *ep, bool is_inv = false);
void set_EditColor(TLabeledEdit *ep, bool is_inv = false);
void set_EditColor(TMaskEdit *ep, bool is_inv = false);
void InvColIfEmpty(TLabeledEdit *ep);
void InvColIfEmpty(TEdit *ep);

TColor get_OptSysColor(TColor col, TColor def);

/**
 * @brief �n�C���C�g�F�̐ݒ�
 * @param cv �L�����o�X
 * @param hl �n�C���C�g
 */
void SetHighlight(TCanvas *cv, bool hl);

//---------------------------------------------------------------------------
#endif
