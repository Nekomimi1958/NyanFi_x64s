/**
 * @file usr_scale.h
 * @brief スケーリング処理
 */
//----------------------------------------------------------------------//
#ifndef UsrScaleH
#define UsrScaleH

//---------------------------------------------------------------------------
#include <Vcl.ComCtrls.hpp>
#include <Vcl.CheckLst.hpp>
#include <Vcl.Grids.hpp>

//---------------------------------------------------------------------------
#define DEFAULT_PPI	96	//!< デフォルト(100\%時)のPPI値

/**
 * @brief 現在のPPIを取得
 * @param cp 対象コントロール
 * @return int PPI値
 */
inline int GetCurPPI(TControl *cp = NULL)
{
	return (			cp? cp->CurrentPPI : 
		Screen->ActiveForm? Screen->ActiveForm->CurrentPPI
						  : Application->MainForm->CurrentPPI);
}

//----------------------------------------------------------------------
/** @brief 自身のフォームでスケーリングされた整数値を取得 */
#define SCALED_THIS(n)		MulDiv(n, CurrentPPI, DEFAULT_PPI)

/** @brief 自身のフォームでスケーリングされる前(100\%時)の整数値を取得 */
#define UNSCALED_THIS(n)	MulDiv(n, DEFAULT_PPI, CurrentPPI)

/** @brief メインフォームでスケーリングされた整数値を取得 */
#define SCALED_MAIN(n)		MulDiv(n, Application->MainForm->CurrentPPI, DEFAULT_PPI)

//----------------------------------------------------------------------
/**
 * @brief スケーリングされた整数値を取得
 * @param n 値
 * @param cp 対象コントロール
 * @return int 
 */
inline int ScaledInt(int n, TControl *cp = NULL)
{
	return MulDiv(n, GetCurPPI(cp), DEFAULT_PPI);
}
//----------------------------------------------------------------------
/**
 * @brief スケーリングされる前(100\%時)の整数値を取得
 * @param n 値
 * @param cp 対象コントロール
 * @return int 
 */
inline int UnscaledInt(int n, TControl *cp = NULL)
{
	return MulDiv(n, DEFAULT_PPI, GetCurPPI(cp));
}

//----------------------------------------------------------------------
/**
 * @brief システム・メトリックの取得
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
 * @brief 指定フォントの描画高を取得
 * @param font フォント
 * @param mgn マージン
 * @param min_mgn 最小マージン
 * @return int 描画高
 */
int get_FontHeightMgn(TFont *font, int mgn = 0, int min_mgn = 2);

/**
 * @brief 指定フォントの描画高を取得
 * @param font フォント
 * @param mgn マージン(100\%時の値、スケーリングされて適用)
 * @param min_mgn 最小マージン(100\%時の値、スケーリングされて適用)
 * @return int 描画高
 */
int get_FontHeightMgnS(TFont *font, int mgn = 0, int min_mgn = 2);

/**
 * @brief スケーリングされたフォントを割り当てる
 * @param s_font 割当先のフォント
 * @param font 割り当てるフォント
 * @param cp PPIを取得するコントロール
 * @param size サイズ
 * @param col 文字色
 */
void AssignScaledFont(TFont *s_font, TFont *font, TControl *cp, int size = 0, TColor col = Graphics::clNone);

/**
 * @brief コントロールにスケーリングされたフォントを設定
 * @param cp 対象コントロール
 * @param font フォント
 */
void AssignScaledFont(TWinControl *cp, TFont *font = NULL);

/**
 * @brief TLabel にスケーリングされたフォントを設定
 * @param lp 対象ラベル
 * @param font フォント
 */
void AssignScaledFont(TLabel *lp, TFont *font = NULL);

/**
 * @brief TPaintBox にスケーリングされたフォントを設定
 * @param pp 対象ペイントボックス
 * @param font フォント
 */
void AssignScaledFont(TPaintBox *pp, TFont *font = NULL);

/**
 * @brief サイズからスケーリングされたフォント高を取得
 * @param sz サイズ
 * @param cp 対象コントロール
 * @return int フォント高
 */
int  ScaledFontHeight(int sz, TControl *cp);

//---------------------------------------------------------------------------
#endif

