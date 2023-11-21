//----------------------------------------------------------------------//
// ÉJÉâÅ[ä÷òAä÷êî														//
//																		//
//----------------------------------------------------------------------//
#ifndef UsrColorH
#define UsrColorH

//---------------------------------------------------------------------------
extern const TColor col_None;
extern const TColor col_Teal;

//---------------------------------------------------------------------------
double GetLuminance(TColor col);
TColor RatioCol(TColor col, float rt);
TColor GrayCol(TColor col);
void RgbToHsl(TColor col, int *h, int *s, int *l);
void RgbToHsv(TColor col, int *h, int *s, int *v);
void RgbToHsv(BYTE r, BYTE g, BYTE b, int *h, int *s, int *v);
TColor SelectWorB(TColor col, float rt = 1.0);

#define ADJCOL_LIGHT	72
#define ADJCOL_FGLIST	96
#define ADJCOL_BGINV	32
#define ADJCOL_BGLTL	24
#define ADJCOL_BGBIT	12
TColor AdjustColor(TColor col, int adj);

TColor Mix2Colors(TColor col1, TColor col2);
void str_to_Color(TColor &col, UnicodeString s);

TColor get_WinColor(bool is_inv = false);
TColor get_TextColor(bool is_hl = false);
TColor get_PanelColor(bool is_inv = false);
TColor get_LabelColor(bool is_inv = false);

void set_EditColor(TEdit *ep, bool is_inv = false);
void set_EditColor(TLabeledEdit *ep, bool is_inv = false);
void set_EditColor(TMaskEdit *ep, bool is_inv = false);
void InvColIfEmpty(TLabeledEdit *ep);
void InvColIfEmpty(TEdit *ep);

TColor get_OptSysColor(TColor col, TColor def);

void SetHighlight(TCanvas *cv, bool hl);

//---------------------------------------------------------------------------
#endif
