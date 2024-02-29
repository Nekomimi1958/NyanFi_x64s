/**
 * @file usr_swatch.h
 * @brief スウォッチブック・パネル
 */
//---------------------------------------------------------------------------
#ifndef UsrSwatchPanelH
#define UsrSwatchPanelH

//---------------------------------------------------------------------------
#define MAX_SWATCH_COLOR	128
#define SWATCH_FILE	  "Swatchbook.INI"	//!< 色見本

//---------------------------------------------------------------------------
extern int SWATCH_ColTable[MAX_SWATCH_COLOR];

/**
 * @brief スウォッチブックか？
 * @param fnam ファイル名
 * @return true スウォッチブック
 */
bool IsSwatchbook(UnicodeString fnam);

/**
 * @brief スウォッチブックをファイルに保存
 * @param fnam ファイル名
 * @return true 成功
 */
bool SaveSwatchbook(UnicodeString fnam);

/**
 * @brief スウォッチブックをファイルから読み込む
 * @param fnam ファイル名
 * @param tmp_sw SWATCH_ColBuff に一時読込
 * @return int カラー数
 */
int  LoadSwatchbook(UnicodeString fnam, bool tmp_sw = false);

/**
 * @brief カスタムカラーを設定
 * @param lst 
 */
void SetCustomColToSwatch(TStrings *lst);

/**
 * @brief 描画 (16列8行)
 * @param cv キャンバス
 * @param rc 描画領域
 * @param tmp_sw SWATCH_ColBuff の内容を描画
 */
void DrawSwatchbook(TCanvas *cv, TRect rc, bool tmp_sw = false);

//---------------------------------------------------------------------------
/**
 * @brief スウォッチブック・パネル
 */
class UsrSwatchPanel : public TPanel
{
private:
	TPaintBox *SwatchPaintBox;
	void __fastcall SwatchPaintBoxPaint(TObject *Sender);

public:
	/** @brief コンストラクタ*/
	__fastcall UsrSwatchPanel(TComponent* Owner);

	/**
	 * @brief 16列8段のパネルサイズをタイルサイズに基づいて設定
	 * @param tile_size タイルサイズ
	 */
	void __fastcall SetPanelSize16x8(int tile_size);
};
//---------------------------------------------------------------------------
#endif
