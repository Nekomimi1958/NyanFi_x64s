//----------------------------------------------------------------------//
// カラー関連関数														//
//																		//
//----------------------------------------------------------------------//
#include "usr_color.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
const TColor col_None = Graphics::clNone;
const TColor col_Teal = clTeal;

//---------------------------------------------------------------------------
//輝度を取得(0～1.0)
//---------------------------------------------------------------------------
double GetLuminance(TColor col)
{
	int c = ColorToRGB(col);
	return ((GetRValue(c)*0.3 + GetGValue(c)*0.59 + GetBValue(c)*0.11) / 255.0);
}

//---------------------------------------------------------------------------
//カラーに倍率をかける
//---------------------------------------------------------------------------
TColor RatioCol(TColor col, float rt)
{
	if (rt>1.0) rt = 1.0; else if (rt<0.0) rt = 0.0;
	int c = ColorToRGB(col);
	int r = GetRValue(c) * rt;
	int g = GetGValue(c) * rt;
	int b = GetBValue(c) * rt;
	return TColor(RGB(r, g, b));
}
//---------------------------------------------------------------------------
//輝度に基づいてグレースケール化
//---------------------------------------------------------------------------
TColor GrayCol(TColor col)
{
	if (col==Graphics::clNone) col = clBlack;
	BYTE v = (BYTE)(GetLuminance(col) * 255);
	return TColor(RGB(v, v, v));
}

//---------------------------------------------------------------------------
//RGB→HSL 変換
//---------------------------------------------------------------------------
void RgbToHsl(TColor col, int *h, int *s, int *l)
{
	int cref = ColorToRGB(col);
	float r = GetRValue(cref)/255.0;
	float g = GetGValue(cref)/255.0;
	float b = GetBValue(cref)/255.0;

	float maxv = std::max(r, std::max(g, b));
	float minv = std::min(r, std::min(g, b));
	float h_f, s_f;
	float l_f = (maxv + minv)/2.0;

	if (maxv==minv) {
		h_f = s_f = 0.0;
	}
	else {
		float d = maxv - minv;
		if		(maxv==r) h_f = (g - b)/d;
		else if (maxv==g) h_f = (b - r)/d + 2.0;
		else			  h_f = (r - g)/d + 4.0;
		h_f *= 60.0;
		if (h_f<0.0) h_f += 360.0;

		s_f = ((l_f<0.5)? d/(maxv + minv) : d/(2.0 - maxv - minv)) * 100.0;
	}

	l_f *= 100.0;

	*h = (int)(h_f + 0.5);
	*s = (int)(s_f + 0.5);
	*l = (int)(l_f + 0.5);
}
//---------------------------------------------------------------------------
//RGB→HSV 変換
//---------------------------------------------------------------------------
void RgbToHsv(BYTE r, BYTE g, BYTE b, int *h, int *s, int *v)
{
	float f_r = r/255.0;
	float f_g = g/255.0;
	float f_b = b/255.0;

	float maxv = std::max(f_r, std::max(f_g, f_b));
	float minv = std::min(f_r, std::min(f_g, f_b));
	float h_f, s_f;
	float v_f = maxv * 100;

	if (maxv==minv) {
		h_f = s_f = 0.0;
	}
	else {
		float d = maxv - minv;
		if		(maxv==f_r)	h_f = (f_g - f_b)/d;
		else if (maxv==f_g)	h_f = (f_b - f_r)/d + 2.0;
		else				h_f = (f_r - f_g)/d + 4.0;
		h_f *= 60.0;
		if (h_f<0.0) h_f += 360.0;

		s_f = d/maxv * 100.0;
	}

	*h = (int)(h_f + 0.5);
	*s = (int)(s_f + 0.5);
	*v = (int)(v_f + 0.5);
}
//---------------------------------------------------------------------------
void RgbToHsv(TColor col, int *h, int *s, int *v)
{
	int cref = ColorToRGB(col);
	RgbToHsv(GetRValue(cref), GetGValue(cref), GetBValue(cref), h, s, v);
}

//---------------------------------------------------------------------------
//背景の輝度から白または黒を選択・加減
//---------------------------------------------------------------------------
TColor SelectWorB(
	TColor col,		//背景色
	float  rt)		//加減指定  (default = 1.0)
{
	double v = GetLuminance(col);
	if (rt<1.0)
		return (v>0.5)? RatioCol(clWhite, 1.0 - rt) : RatioCol(clWhite, rt);
	else
		return (v>0.5)? clBlack : clWhite;
}
//---------------------------------------------------------------------------
//輝度に基づいて明暗を加減
//---------------------------------------------------------------------------
TColor AdjustColor(
	TColor col,		//元の色
	int adj)		//加減値	0～255
{
	int cref = ColorToRGB(col);
	int r = GetRValue(cref);
	int g = GetGValue(cref);
	int b = GetBValue(cref);

	//明→暗
	if (GetLuminance(col)>0.5) {
		r -= (adj * r / 255);
		g -= (adj * g / 255);
		b -= (adj * b / 255);
	}
	//暗→明
	else {
		r += (adj * (255 - r) / 255);
		g += (adj * (255 - g) / 255);
		b += (adj * (255 - b) / 255);
	}

	r = std::clamp(r, 0, 255);
	g = std::clamp(g, 0, 255);
	b = std::clamp(b, 0, 255);

	return TColor(RGB(r, g, b));
}

//---------------------------------------------------------------------------
//２色混合
//---------------------------------------------------------------------------
TColor Mix2Colors(TColor col1, TColor col2)
{
	int c1 = ColorToRGB(col1);
	int c2 = ColorToRGB(col2);
	int r = (GetRValue(c1) + GetRValue(c2)) / 2;
	int g = (GetGValue(c1) + GetGValue(c2)) / 2;
	int b = (GetBValue(c1) + GetBValue(c2)) / 2;
	return TColor(RGB(r, g, b));
}

//---------------------------------------------------------------------------
//文字列からカラーを設定
//---------------------------------------------------------------------------
void str_to_Color(TColor &col, UnicodeString s)
{
	TColor c = (TColor)s.ToIntDef(Graphics::clNone);
	if (c!=Graphics::clNone) col = c;
}

//---------------------------------------------------------------------------
//スタイルを考慮した色の取得
//---------------------------------------------------------------------------
TColor get_WinColor(
	bool is_inv)	//無効な項目	(default = false)
{
	TColor col = TStyleManager::ActiveStyle->GetSystemColor(clWindow);
	if (is_inv) col = AdjustColor(col, ADJCOL_BGINV);
	return col;
}
//---------------------------------------------------------------------------
TColor get_TextColor(
	bool is_hl)	//ハイライト	(default = false)
{
	return TStyleManager::ActiveStyle->GetSystemColor(is_hl? clHighlightText : clWindowText);
}
//---------------------------------------------------------------------------
TColor get_PanelColor(
	bool is_inv)	//無効な項目	(default = false)
{
	TColor col = TStyleManager::ActiveStyle->GetSystemColor(clBtnFace);
	if (is_inv) col = AdjustColor(col, ADJCOL_BGINV);
	return col;
}
//---------------------------------------------------------------------------
TColor get_LabelColor(
	bool is_inv)	//無効な項目	(default = false)
{
	return TStyleManager::ActiveStyle->GetSystemColor(is_inv? clGrayText : clBtnText);
}

//---------------------------------------------------------------------------
void set_EditColor(
	TEdit *ep,
	bool is_inv)	//無効な項目	(default = false)
{
	TColor col = TStyleManager::ActiveStyle->GetSystemColor(clWindow);
	if (is_inv) col = AdjustColor(col, ADJCOL_BGINV);
	ep->Color = col;
	ep->Font->Color = TStyleManager::ActiveStyle->GetSystemColor(clWindowText);
}
//---------------------------------------------------------------------------
void set_EditColor(TLabeledEdit *ep, bool is_inv)
{
	TColor col = TStyleManager::ActiveStyle->GetSystemColor(clWindow);
	if (is_inv) col = AdjustColor(col, ADJCOL_BGINV);
	ep->Color = col;
	ep->Font->Color = TStyleManager::ActiveStyle->GetSystemColor(clWindowText);
}
//---------------------------------------------------------------------------
void set_EditColor(TMaskEdit *ep, bool is_inv)
{
	TColor col = TStyleManager::ActiveStyle->GetSystemColor(clWindow);
	if (is_inv) col = AdjustColor(col, ADJCOL_BGINV);
	ep->Color = col;
	ep->Font->Color = TStyleManager::ActiveStyle->GetSystemColor(clWindowText);
}

//---------------------------------------------------------------------------
//空欄なら無効色に
//---------------------------------------------------------------------------
void InvColIfEmpty(TLabeledEdit *ep)
{
	TColor col = TStyleManager::ActiveStyle->GetSystemColor(clWindow);
	if (ep->NumbersOnly? (ep->Text.ToIntDef(0)==0) : ep->Text.IsEmpty()) col = AdjustColor(col, ADJCOL_BGINV);
	ep->Color = col;
	ep->Font->Color = TStyleManager::ActiveStyle->GetSystemColor(clWindowText);
}
//---------------------------------------------------------------------------
void InvColIfEmpty(TEdit *ep)
{
	TColor col = TStyleManager::ActiveStyle->GetSystemColor(clWindow);
	if (ep->NumbersOnly? (ep->Text.ToIntDef(0)==0) : ep->Text.IsEmpty()) col = AdjustColor(col, ADJCOL_BGINV);
	ep->Color = col;
	ep->Font->Color = TStyleManager::ActiveStyle->GetSystemColor(clWindowText);
}

//---------------------------------------------------------------------------
//ハイライト色の設定
//---------------------------------------------------------------------------
void SetHighlight(TCanvas *cv, bool hl)
{
	cv->Brush->Color = TStyleManager::ActiveStyle->GetSystemColor(hl? clHighlight : clWindow);
	cv->Font->Color  = TStyleManager::ActiveStyle->GetSystemColor(hl? clHighlightText : clWindowText);
}

//---------------------------------------------------------------------------
TColor get_OptSysColor(TColor col, TColor def)
{
	return ((col==col_None)? TStyleManager::ActiveStyle->GetSystemColor(def) : col);
}
//---------------------------------------------------------------------------
