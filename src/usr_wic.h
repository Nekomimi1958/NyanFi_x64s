/**
 * @file usr_wic.h
 * @brief WIC�֘A�̊֐�
 */
//---------------------------------------------------------------------------
#ifndef UserWicH
#define UserWicH

//---------------------------------------------------------------------------
#define WICIMG_FRAME		0
#define WICIMG_PREVIEW		1
#define WICIMG_THUMBNAIL	2

/** �t���[����D���I�Ɏ擾����g���q */
#define FEXT_FRAME_PRI		_T(".bmp.png.gif.tif.wdp.hdp.jpg.jpeg.jpe.webp.heic.eps.psd")

//---------------------------------------------------------------------------

/**
 * @brief WIC�g���R�[�f�b�N�ꗗ�̎擾
 * @param[out] lst ���ꗗ
 * @param[out] fxstr �g���q
 * @return int ���ڐ�
 */
int WIC_get_ex_list(TStringList *lst, UnicodeString *fxstr = NULL);

/**
 * @brief ���������e���w��`���Ńf�R�[�h���ăr�b�g�}�b�v���擾
 * @param ms �Ώۃ������X�g���[��
 * @param[out] o_bmp �o�̓r�b�g�}�b�v
 * @param fmt �R���e�i�`����GUID
 * @return true ����
 * @return false ���s
 */
bool WIC_get_from_memory(TMemoryStream *ms, Graphics::TBitmap *o_bmp, GUID fmt);

/**
 * @brief �t�@�C������w�肵����ނ̃r�b�g�}�b�v���擾
 * @param fnam �t�@�C����
 * @param[out] o_bmp �o�̓r�b�g�}�b�v
 * @param img_type ���(WICIMG_FRAME, WICIMG_PREVIEW, WICIMG_THUMBNAIL)
 * @return true ����
 * @return false ���s
 */
bool WIC_load_image(UnicodeString fnam, Graphics::TBitmap *o_bmp, int img_type = WICIMG_PREVIEW);

/**
 * @brief �r�b�g�}�b�v���w��`���Ńt�@�C���ɕۑ�
 * @param fnam �t�@�C����
 * @param[in] i_bmp �r�b�g�}�b�v
 * @param jpg_q JPEG�掿(0�`100)
 * @param jpg_ycrcb JPEG�T�u�T���v�����O(0�`3)
 * @param grayscale jpeg/PNG �O���[�X�P�[��(8bit)�ŕۑ�
 * @param tif_cmp TIFF���k(0�`7)
 * @return true ����
 * @return false ���s
 */
bool WIC_save_image(UnicodeString fnam, Graphics::TBitmap *i_bmp,
	int jpg_q = 100, int jpg_ycrcb = 0, bool grayscale = false, int tif_cmp = 0);

/**
 * @brief �摜�̏k���E�g��
 * @param[in] i_bmp ���̓r�b�g�}�b�v
 * @param[out] o_bmp �o�̓r�b�g�}�b�v
 * @param ratio �{��(0.0:����)
 * @param s_wd ���T�C�Y(0:����)
 * @param s_hi �c�T�C�Y
 * @param s_opt �A���S���Y��
 *
 * �{�����T�C�Y�̂����ꂩ���w�肵�Ă��������B
*
 * @return true ����
 * @return false ���s
 */
bool WIC_resize_image(Graphics::TBitmap *i_bmp, Graphics::TBitmap *o_bmp,
	float ratio, unsigned int s_wd = 0, unsigned int s_hi = 0, int s_opt = 0);

/**
 * @brief �w��T�C�Y�Ɏ��܂�悤�ɏk���E�g��A�؂�o��
 * @param[in] i_bmp ���̓r�b�g�}�b�v
 * @param[out] o_bmp �o�̓r�b�g�}�b�v
 * @param s_wd ���T�C�Y
 * @param s_hi �c�T�C�Y
 * @param s_opt �A���S���Y��
 * @return true ����
 * @return false ���s
 */
bool WIC_fit_trim_image(Graphics::TBitmap *i_bmp, Graphics::TBitmap *o_bmp,
	unsigned int s_wd, unsigned int s_hi, int s_opt = 0);

/**
 * @brief �摜�̉�]�E���]
 * @param[in,out] i_bmp ���o�̓r�b�g�}�b�v
 * @param rot_opt 1:90/ 2:180/ 3:270(����90)/ 4:���E���]/ 5:�㉺���]
 * @return true ����
 * @return false ���s
 */
bool WIC_rotate_image(Graphics::TBitmap *i_bmp, int rot_opt);

/**
 * @brief �摜�̃O���[�X�P�[����
 * @param[in,out] i_bmp ���o�̓r�b�g�}�b�v
 * @return true ����
 * @return false ���s
 */
bool WIC_grayscale_image(Graphics::TBitmap *i_bmp);

/**
 * @brief �摜�̃T�C�Y���擾
 * @param fnam �t�@�C����
 * @param[out] wd �� 
 * @param[out] hi ����
 * @return true ����
 * @return false ���s
 */
bool WIC_get_img_size(UnicodeString fnam, unsigned int *wd, unsigned int *hi);

//---------------------------------------------------------------------------
#endif
