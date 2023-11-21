//----------------------------------------------------------------------//
// NyanFi																//
//  同名ファイルの比較ダイアログ										//
//----------------------------------------------------------------------//
#include "UserFunc.h"
#include "Global.h"
#include "CompDlg.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFileCompDlg *FileCompDlg = NULL;

//---------------------------------------------------------------------------
__fastcall TFileCompDlg::TFileCompDlg(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFileCompDlg::FormCreate(TObject *Sender)
{
	set_ComboBoxText(AlgComboBox, HASH_ALG_LIST);

	AllDirHasSize = false;
}
//---------------------------------------------------------------------------
void __fastcall TFileCompDlg::FormShow(TObject *Sender)
{
	IniFile->LoadPosInfo(this, DialogCenter);

	TimeRadioGroup->ItemIndex = IniFile->ReadIntGen(_T("CompModeT"));
	SizeRadioGroup->ItemIndex = IniFile->ReadIntGen(_T("CompModeS"));
	HashRadioGroup->ItemIndex = IniFile->ReadIntGen(_T("CompModeH"));
	AlgComboBox->ItemIndex	  = IniFile->ReadIntGen(_T("CompAlg"));
	IdRadioGroup->ItemIndex   = IniFile->ReadIntGen(_T("CompID"));
	CmpDirCheckBox->Checked   = IniFile->ReadBoolGen(_T("CompDir"));
	CmpArcCheckBox->Checked   = IniFile->ReadBoolGen(_T("CompArc"));
	SelOppCheckBox->Checked   = IniFile->ReadBoolGen(_T("CompSelOpp"));
	ReverseCheckBox->Checked  = IniFile->ReadBoolGen(_T("CompReverse"));
	SelMaskCheckBox->Checked  = IniFile->ReadBoolGen(_T("CompSelMask"));
}
//---------------------------------------------------------------------------
void __fastcall TFileCompDlg::FormClose(TObject *Sender, TCloseAction &Action)
{
	IniFile->SavePosInfo(this);

	IniFile->WriteIntGen(_T("CompModeT"),	 TimeRadioGroup);
	IniFile->WriteIntGen(_T("CompModeS"),	 SizeRadioGroup);
	IniFile->WriteIntGen(_T("CompModeH"),	 HashRadioGroup);
	IniFile->WriteIntGen(_T("CompAlg"),		 AlgComboBox);
	IniFile->WriteIntGen(_T("CompID"),		 IdRadioGroup);
	IniFile->WriteBoolGen(_T("CompDir"),	 CmpDirCheckBox);
	IniFile->WriteBoolGen(_T("CompArc"),	 CmpArcCheckBox);
	IniFile->WriteBoolGen(_T("CompSelOpp"),	 SelOppCheckBox);
	IniFile->WriteBoolGen(_T("CompReverse"), ReverseCheckBox);
	IniFile->WriteBoolGen(_T("CompSelMask"), SelMaskCheckBox);
}
//---------------------------------------------------------------------------
void __fastcall TFileCompDlg::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	SpecialKeyProc(this, Key, Shift, _T(HELPTOPIC_FL) _T("#CompareDlg"));
}
//---------------------------------------------------------------------------
void __fastcall TFileCompDlg::OptRadioGroupClick(TObject *Sender)
{
	TRadioGroup *rp = (TRadioGroup *)Sender;
	if (rp==HashRadioGroup && rp->ItemIndex>0) IdRadioGroup->ItemIndex = 0;
	if (rp==IdRadioGroup && rp->ItemIndex>0) HashRadioGroup->ItemIndex = 0;
}

//---------------------------------------------------------------------------
void __fastcall TFileCompDlg::OkActionUpdate(TObject *Sender)
{
	SizeRadioGroup->Enabled = !CmpDirCheckBox->Checked || AllDirHasSize;

	HashRadioGroup->Enabled = !CmpDirCheckBox->Checked && SizeRadioGroup->ItemIndex==2 && !CurStt->is_FTP && !OppStt->is_FTP;
	AlgComboBox->Enabled	= HashRadioGroup->Enabled;

	IdRadioGroup->Enabled	= !CmpDirCheckBox->Checked && (SizeRadioGroup->ItemIndex==0 || SizeRadioGroup->ItemIndex==2)
								&& !CurStt->is_Arc && !OppStt->is_Arc && !CurStt->is_FTP && !OppStt->is_FTP;

	CmpArcCheckBox->Enabled	= CmpDirCheckBox->Checked;

	TimePanel->Color = get_PanelColor(TimeRadioGroup->ItemIndex==0);
	SizePanel->Color = get_PanelColor(!SizeRadioGroup->Enabled || SizeRadioGroup->ItemIndex==0);
	HashPanel->Color = get_PanelColor(!HashRadioGroup->Enabled || HashRadioGroup->ItemIndex==0);
	IdPanel->Color	 = get_PanelColor(!IdRadioGroup->Enabled   || IdRadioGroup->ItemIndex==0);

	((TAction*)Sender)->Enabled = true;
}
//---------------------------------------------------------------------------

