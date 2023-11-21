//----------------------------------------------------------------------//
// TEdit/TMaskEdit/TLabeledEdit のスタイル・フック						//
// 背景色に Color を使用(システム色の場合はスタイル用に変換)			//
//----------------------------------------------------------------------//
#include <Vcl.Styles.hpp>
#include "style_hook.h"

//---------------------------------------------------------------------------
__fastcall TEditStyleHookColor::TEditStyleHookColor(TWinControl *AControl)
	: TEditStyleHook(AControl)
{
	UpdateColors();
};
//---------------------------------------------------------------------------
void TEditStyleHookColor::UpdateColors()
{
	TCustomStyleServices *LStyle = StyleServices();
	TColor fg = LStyle->GetSystemColor(clWindowText);
	TColor bg = LStyle->GetStyleColor(scEdit);

	if (Control->ClassNameIs("TEdit")) {
		TEdit *ep = (TEdit *)Control;
		bg = ep->Color;
	}
	else if (Control->ClassNameIs("TMaskEdit")) {
		TMaskEdit *ep = (TMaskEdit *)Control;
		bg = ep->Color;
	}
	else if (Control->ClassNameIs("TLabeledEdit")) {
		TLabeledEdit *ep = (TLabeledEdit *)Control;
		bg = ep->Color;
	}
	else {
		return;
	}

	if (Control->Enabled) {
		if ((int)bg<0) bg = LStyle->GetSystemColor(bg);
		Brush->Color = bg;
		FontColor    = fg;
	}
	else {
		Brush->Color = LStyle->GetStyleColor(scEditDisabled);
		FontColor	 = LStyle->GetSystemColor(clGrayText);
	}
}
//---------------------------------------------------------------------------
void __fastcall TEditStyleHookColor::WndProc(TMessage &Message)
{
	switch (Message.Msg) {
	case CN_CTLCOLOREDIT:
		UpdateColors();
		SetTextColor(reinterpret_cast<HDC>(Message.WParam), ColorToRGB(FontColor));
		SetBkColor(reinterpret_cast<HDC>(Message.WParam), ColorToRGB(Brush->Color));
		Message.Result = reinterpret_cast<LRESULT>(Brush->Handle);
		Handled = true;
		break;
	case CM_ENABLEDCHANGED:
		UpdateColors();
		Handled = false;
		break;
	default:
		inherited::WndProc(Message);
		break;
	}
}
//---------------------------------------------------------------------------
