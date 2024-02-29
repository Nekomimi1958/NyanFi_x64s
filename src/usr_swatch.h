/**
 * @file usr_swatch.h
 * @brief �X�E�H�b�`�u�b�N�E�p�l��
 */
//---------------------------------------------------------------------------
#ifndef UsrSwatchPanelH
#define UsrSwatchPanelH

//---------------------------------------------------------------------------
#define MAX_SWATCH_COLOR	128
#define SWATCH_FILE	  "Swatchbook.INI"	//!< �F���{

//---------------------------------------------------------------------------
extern int SWATCH_ColTable[MAX_SWATCH_COLOR];

/**
 * @brief �X�E�H�b�`�u�b�N���H
 * @param fnam �t�@�C����
 * @return true �X�E�H�b�`�u�b�N
 */
bool IsSwatchbook(UnicodeString fnam);

/**
 * @brief �X�E�H�b�`�u�b�N���t�@�C���ɕۑ�
 * @param fnam �t�@�C����
 * @return true ����
 */
bool SaveSwatchbook(UnicodeString fnam);

/**
 * @brief �X�E�H�b�`�u�b�N���t�@�C������ǂݍ���
 * @param fnam �t�@�C����
 * @param tmp_sw SWATCH_ColBuff �Ɉꎞ�Ǎ�
 * @return int �J���[��
 */
int  LoadSwatchbook(UnicodeString fnam, bool tmp_sw = false);

/**
 * @brief �J�X�^���J���[��ݒ�
 * @param lst 
 */
void SetCustomColToSwatch(TStrings *lst);

/**
 * @brief �`�� (16��8�s)
 * @param cv �L�����o�X
 * @param rc �`��̈�
 * @param tmp_sw SWATCH_ColBuff �̓��e��`��
 */
void DrawSwatchbook(TCanvas *cv, TRect rc, bool tmp_sw = false);

//---------------------------------------------------------------------------
/**
 * @brief �X�E�H�b�`�u�b�N�E�p�l��
 */
class UsrSwatchPanel : public TPanel
{
private:
	TPaintBox *SwatchPaintBox;
	void __fastcall SwatchPaintBoxPaint(TObject *Sender);

public:
	/** @brief �R���X�g���N�^*/
	__fastcall UsrSwatchPanel(TComponent* Owner);

	/**
	 * @brief 16��8�i�̃p�l���T�C�Y���^�C���T�C�Y�Ɋ�Â��Đݒ�
	 * @param tile_size �^�C���T�C�Y
	 */
	void __fastcall SetPanelSize16x8(int tile_size);
};
//---------------------------------------------------------------------------
#endif
