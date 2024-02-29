/**
 * @file usr_exif.h
 * @brief Exif 情報関連の関数
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
 * @brief 指定ファイルのExif情報一覧を取得
 * @param fnam ファイル名
 * @param[out] lst 結果格納リスト(タグ番号=文字列)
 * @return true 
 * @return false 
 */
bool EXIF_GetInf(UnicodeString fnam, TStringList *lst);

/**
 * @brief Exifリストから画像サイズを取得
 * 
 * @param lst Exifリスト
 * @param fext 拡張子
 * @param[out] w 幅 
 * @param[out] h 高さ
 * @return true 成功
 */
bool Exif_GetImgSize(TStringList *lst, UnicodeString fext, unsigned int *w, unsigned int *h);

/**
 * @brief ファイルのExif撮影日時を取得
 * @param fnam ファイル名
 * @param[out] dt 撮影日時
 * @return true 成功 
 */
bool EXIF_GetExifTime(UnicodeString fnam, TDateTime &dt);

/**
 * @brief ファイルのExif撮影日時を指定書式で取得
 * @param fnam ファイル名
 * @param format 書式
 * @return UnicodeString 撮影日時文字列
 */
UnicodeString EXIF_GetExifTimeStr(UnicodeString fnam, UnicodeString format);

/**
 * @brief ファイルのタイムスタンプをExif撮影日時に
 * 
 * @param fnam ファイル名
 * @return true 成功
 */
bool EXIF_SetExifTime(UnicodeString fnam);

/**
 * @brief JpegファイルからExif情報を削除
 * @param fnam 対象ファイル名
 * @param onam 出力ファイル名
 * @param keep_time タイムスタンプを維持
 * @retval 0 成功 
 * @retval -1 失敗
 * @retval 1 Exifなし 
 */
int  EXIF_DelJpgExif(UnicodeString fnam, UnicodeString onam, bool keep_time = true);
//---------------------------------------------------------------------------
#endif
