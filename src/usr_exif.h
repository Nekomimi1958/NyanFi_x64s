/**
 * @file usr_exif.h
 * @brief Exif ���֘A�̊֐�
 */
//---------------------------------------------------------------------------
#ifndef UsrExifH
#define UsrExifH

//---------------------------------------------------------------------------
float CIFF_ev(int v);
bool CIFF_GetInf(UnicodeString fnam, TStringList *lst);

void EXIF_get_idf_inf(TFileStream *fs, int top, bool bsw, TStringList *lst, UnicodeString id = EmptyStr);
void EXIF_format_inf(UnicodeString fext, TStringList *lst);

/**
 * @brief �w��t�@�C����Exif���ꗗ���擾
 * @param fnam �t�@�C����
 * @param[out] lst ���ʊi�[���X�g(�^�O�ԍ�=������)
 * @return true 
 * @return false 
 */
bool EXIF_GetInf(UnicodeString fnam, TStringList *lst);

/**
 * @brief Exif���X�g����摜�T�C�Y���擾
 * 
 * @param lst Exif���X�g
 * @param fext �g���q
 * @param[out] w �� 
 * @param[out] h ����
 * @return true ����
 */
bool Exif_GetImgSize(TStringList *lst, UnicodeString fext, unsigned int *w, unsigned int *h);

/**
 * @brief �t�@�C����Exif�B�e�������擾
 * @param fnam �t�@�C����
 * @param[out] dt �B�e����
 * @return true ���� 
 */
bool EXIF_GetExifTime(UnicodeString fnam, TDateTime &dt);

/**
 * @brief �t�@�C����Exif�B�e�������w�菑���Ŏ擾
 * @param fnam �t�@�C����
 * @param format ����
 * @return UnicodeString �B�e����������
 */
UnicodeString EXIF_GetExifTimeStr(UnicodeString fnam, UnicodeString format);

/**
 * @brief �t�@�C���̃^�C���X�^���v��Exif�B�e������
 * 
 * @param fnam �t�@�C����
 * @return true ����
 */
bool EXIF_SetExifTime(UnicodeString fnam);

/**
 * @brief Jpeg�t�@�C������Exif�����폜
 * @param fnam �Ώۃt�@�C����
 * @param onam �o�̓t�@�C����
 * @param keep_time �^�C���X�^���v���ێ�
 * @retval 0 ���� 
 * @retval -1 ���s
 * @retval 1 Exif�Ȃ� 
 */
int  EXIF_DelJpgExif(UnicodeString fnam, UnicodeString onam, bool keep_time = true);
//---------------------------------------------------------------------------
#endif
