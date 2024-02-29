/**
 * @file usr_wic.h
 * @brief WIC関連の関数
 */
//---------------------------------------------------------------------------
#ifndef UserWicH
#define UserWicH

//---------------------------------------------------------------------------
#define WICIMG_FRAME		0
#define WICIMG_PREVIEW		1
#define WICIMG_THUMBNAIL	2

/** フレームを優勢的に取得する拡張子 */
#define FEXT_FRAME_PRI		_T(".bmp.png.gif.tif.wdp.hdp.jpg.jpeg.jpe.webp.heic.eps.psd")

//---------------------------------------------------------------------------

/**
 * @brief WIC拡張コーデック一覧の取得
 * @param[out] lst 情報一覧
 * @param[out] fxstr 拡張子
 * @return int 項目数
 */
int WIC_get_ex_list(TStringList *lst, UnicodeString *fxstr = NULL);

/**
 * @brief メモリ内容を指定形式でデコードしてビットマップを取得
 * @param ms 対象メモリストリーム
 * @param[out] o_bmp 出力ビットマップ
 * @param fmt コンテナ形式のGUID
 * @return true 成功
 * @return false 失敗
 */
bool WIC_get_from_memory(TMemoryStream *ms, Graphics::TBitmap *o_bmp, GUID fmt);

/**
 * @brief ファイルから指定した種類のビットマップを取得
 * @param fnam ファイル名
 * @param[out] o_bmp 出力ビットマップ
 * @param img_type 種類(WICIMG_FRAME, WICIMG_PREVIEW, WICIMG_THUMBNAIL)
 * @return true 成功
 * @return false 失敗
 */
bool WIC_load_image(UnicodeString fnam, Graphics::TBitmap *o_bmp, int img_type = WICIMG_PREVIEW);

/**
 * @brief ビットマップを指定形式でファイルに保存
 * @param fnam ファイル名
 * @param[in] i_bmp ビットマップ
 * @param jpg_q JPEG画質(0～100)
 * @param jpg_ycrcb JPEGサブサンプリング(0～3)
 * @param grayscale jpeg/PNG グレースケール(8bit)で保存
 * @param tif_cmp TIFF圧縮(0～7)
 * @return true 成功
 * @return false 失敗
 */
bool WIC_save_image(UnicodeString fnam, Graphics::TBitmap *i_bmp,
	int jpg_q = 100, int jpg_ycrcb = 0, bool grayscale = false, int tif_cmp = 0);

/**
 * @brief 画像の縮小・拡大
 * @param[in] i_bmp 入力ビットマップ
 * @param[out] o_bmp 出力ビットマップ
 * @param ratio 倍率(0.0:無効)
 * @param s_wd 横サイズ(0:無効)
 * @param s_hi 縦サイズ
 * @param s_opt アルゴリズム
 *
 * 倍率かサイズのいずれかを指定してください。
*
 * @return true 成功
 * @return false 失敗
 */
bool WIC_resize_image(Graphics::TBitmap *i_bmp, Graphics::TBitmap *o_bmp,
	float ratio, unsigned int s_wd = 0, unsigned int s_hi = 0, int s_opt = 0);

/**
 * @brief 指定サイズに収まるように縮小・拡大、切り出し
 * @param[in] i_bmp 入力ビットマップ
 * @param[out] o_bmp 出力ビットマップ
 * @param s_wd 横サイズ
 * @param s_hi 縦サイズ
 * @param s_opt アルゴリズム
 * @return true 成功
 * @return false 失敗
 */
bool WIC_fit_trim_image(Graphics::TBitmap *i_bmp, Graphics::TBitmap *o_bmp,
	unsigned int s_wd, unsigned int s_hi, int s_opt = 0);

/**
 * @brief 画像の回転・反転
 * @param[in,out] i_bmp 入出力ビットマップ
 * @param rot_opt 1:90/ 2:180/ 3:270(左に90)/ 4:左右反転/ 5:上下反転
 * @return true 成功
 * @return false 失敗
 */
bool WIC_rotate_image(Graphics::TBitmap *i_bmp, int rot_opt);

/**
 * @brief 画像のグレースケール化
 * @param[in,out] i_bmp 入出力ビットマップ
 * @return true 成功
 * @return false 失敗
 */
bool WIC_grayscale_image(Graphics::TBitmap *i_bmp);

/**
 * @brief 画像のサイズを取得
 * @param fnam ファイル名
 * @param[out] wd 幅 
 * @param[out] hi 高さ
 * @return true 成功
 * @return false 失敗
 */
bool WIC_get_img_size(UnicodeString fnam, unsigned int *wd, unsigned int *hi);

//---------------------------------------------------------------------------
#endif
