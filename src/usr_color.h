/**
 * @file usr_color.h
 * @brief カラー処理関連の関数
 */
//---------------------------------------------------------------------------
#ifndef UsrColorH
#define UsrColorH

//---------------------------------------------------------------------------
extern const TColor col_None;
extern const TColor col_Teal;

//---------------------------------------------------------------------------
/**
 * @brief 輝度を取得
 * @param col 対象色
 * @return double 輝度値(0～1.0)
 */
double GetLuminance(TColor col);

/**
 * @brief 色に倍率をかける
 * @param col 元の色
 * @param rt 倍率(0.0～1.0)
 * @return TColor 
 */
TColor RatioCol(TColor col, float rt);

/**
 * @brief 輝度に基づいてグレースケール化
 * @param col 元の色
 * @return TColor グレースケール化された色
 */
TColor GrayCol(TColor col);

/**
 * @brief 補色を取得
 * @param col 元の色
 * @return TColor 補色
 */
TColor ComplementaryCol(TColor col);

/** @brief RGB→HSL 変換 */
void RgbToHsl(TColor col, int *h, int *s, int *l);

/** @brief RGB→HSV 変換 */
void RgbToHsv(TColor col, int *h, int *s, int *v);

/** @brief RGB→HSV 変換 */
void RgbToHsv(BYTE r, BYTE g, BYTE b, int *h, int *s, int *v);

/** @brief HSL→RGB 変換 */
TColor HslToCol(int h, int s, int l);

/**
 * @brief 背景の輝度から白または黒を選択・加減
 * @param col 背景色
 * @param rt 加減指定
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
 * @brief 輝度に基づいて明暗を加減
 * @param col 元の色
 * @param adj 加減値 (0～255)
 * @return TColor 
 */
TColor AdjustColor(TColor col, int adj);

/** @brief ２色混合 */
TColor Mix2Colors(TColor col1, TColor col2);

/**
 * @brief 文字列からカラーを設定
 * @param[out] col 
 * @param s 整数値を表す文字列
 */
void str_to_Color(TColor &col, UnicodeString s);

/**
 * @brief スタイルを考慮したウィンドウ背景色の取得
 * @param is_inv 無効な項目
 * @return TColor 
 */
TColor get_WinColor(bool is_inv = false);

/**
 * @brief スタイルを考慮したウィンドウ文字色の取得
 * @param is_hl ハイライト
 * @return TColor 
 */
TColor get_TextColor(bool is_hl = false);

/**
 * @brief スタイルを考慮したパネル色の取得
 * @param is_inv 無効な項目
 * @return TColor 
 */
TColor get_PanelColor(bool is_inv = false);

/**
 * @brief スタイルを考慮したラベル文字色の取得
 * @param is_inv 無効な項目
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
 * @brief ハイライト色の設定
 * @param cv キャンバス
 * @param hl ハイライト
 */
void SetHighlight(TCanvas *cv, bool hl);

//---------------------------------------------------------------------------
#endif
