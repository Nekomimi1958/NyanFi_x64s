/**
 * @file BakDlg.h
 * @brief �o�b�N�A�b�v�_�C�A���O
 */
//---------------------------------------------------------------------------
#ifndef BakDlgH
#define BakDlgH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.Actions.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.Mask.hpp>
#include <Vcl.Menus.hpp>

//---------------------------------------------------------------------------
/**
 * @brief �o�b�N�A�b�v�_�C�A���O
 */
class TBackupDlg : public TForm
{
__published:	// IDE �ŊǗ������R���|�[�l���g
	TAction *DelSetupAction;
	TAction *MakeNbtAction;
	TAction *SaveSetupAction;
	TActionList *ActionList1;
	TButton *CanButton;
	TButton *OkButton;
	TButton *SaveCmdBtn;
	TButton *SaveFmtBtn;
	TCheckBox *MirrorCheckBox;
	TCheckBox *SubDirCheckBox;
	TCheckBox *SureCheckBox;
	TCheckBox *SyncCheckBox;
	TComboBox *BakExcMaskComboBox;
	TComboBox *BakIncMaskComboBox;
	TComboBox *SetupComboBox;
	TLabel *Label1;
	TLabel *SyncLabel;
	TLabeledEdit *BakDateCondEdit;
	TLabeledEdit *BakSkipDirEdit;
	TLabeledEdit *DstDirEdit;
	TLabeledEdit *SrcDirEdit;
	TMenuItem *DelSetupItem;
	TPanel *BottomPanel;
	TPopupMenu *SetupPopupMenu;
	TBevel *Bevel1;

	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall SetupComboBoxClick(TObject *Sender);
	void __fastcall SaveSetupActionExecute(TObject *Sender);
	void __fastcall SaveSetupActionUpdate(TObject *Sender);
	void __fastcall DelSetupActionExecute(TObject *Sender);
	void __fastcall DelSetupActionUpdate(TObject *Sender);
	void __fastcall MakeNbtActionExecute(TObject *Sender);
	void __fastcall MakeNbtActionUpdate(TObject *Sender);
	void __fastcall OkButtonClick(TObject *Sender);

private:	// ���[�U�[�錾

public:		// ���[�U�[�錾
	__fastcall TBackupDlg(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TBackupDlg *BackupDlg;
//---------------------------------------------------------------------------
#endif
