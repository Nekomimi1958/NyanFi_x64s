/**
 * @file usr_id3.h
 * @brief MP3 ID3タグ情報の処理
 */
//---------------------------------------------------------------------------
#ifndef UsrID3H
#define UsrID3H

//---------------------------------------------------------------------------
/** @brief ID3ヘッダ */
struct id3_hdr {
	char hdr_id[3];
	BYTE maj_ver;
	BYTE revision;
	BYTE flag;
	BYTE size[4];
};
/** @brief 拡張ヘッダ */
struct id3_ex_hdr {
	BYTE size[4];
	BYTE flag[2];
};

/** @brief フレームヘッダ(v2.3,v2.4) */
struct id3_frm_hdr {
	char frame_id[4];
	BYTE size[4];
	BYTE flag[2];
};

/** @brief フレームヘッダ(v2.2) */
struct id3_frm_hdr_2 {
	char frame_id[3];
	BYTE size[3];
};

//---------------------------------------------------------------------------
/**
 * @brief MP3ファイルの ID3 Tag v2/v1 情報を取得
 * @param fnam ファイル名
 * @param[out] lst 結果リスト(項目=内容)
 * @param id_min 最小限の情報を (T??=形式で取得)
 * @return true 成功 
 */
bool ID3_GetInf(UnicodeString fnam, TStringList* lst, bool id_min = false);

/**
 * @brief MP3ファイルから埋め込み画像をビットマップで取得/ファイル出力
 * @param fnam ファイル名
 * @param[out] bmpimg 出力ビットマップ
 * @param o_fnam 出力ファイル名
 * @return true 成功
 */
bool ID3_GetImage(UnicodeString fnam, Graphics::TBitmap *bmpimg, UnicodeString o_fnam = EmptyStr);

//---------------------------------------------------------------------------
#endif
