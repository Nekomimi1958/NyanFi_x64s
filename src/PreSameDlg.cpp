//----------------------------------------------------------------------//
// NyanFi																//
//  �����������̎��O�w��_�C�A���O										//
//----------------------------------------------------------------------//
#include "Global.h"
#include "PreSameDlg.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPreSameNemeDlg *PreSameNemeDlg = NULL;

//---------------------------------------------------------------------------
__fastcall TPreSameNemeDlg::TPreSameNemeDlg(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TPreSameNemeDlg::FormShow(TObject *Sender)
{
	IniFile->LoadPosInfo(this, DialogCenter);

	PreMode = 0;
	PreModeRadioGroup->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TPreSameNemeDlg::FormClose(TObject *Sender, TCloseAction &Action)
{
	IniFile->SavePosInfo(this);

	PreMode = PreModeRadioGroup->ItemIndex;
}

//---------------------------------------------------------------------------
void __fastcall TPreSameNemeDlg::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	SpecialKeyProc(this, Key, Shift);
}
//---------------------------------------------------------------------------
