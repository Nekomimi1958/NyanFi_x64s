//----------------------------------------------------------------------//
// NyanFi																//
//  ���K�\���`�F�b�J�[													//
//----------------------------------------------------------------------//
#ifndef RegExChkH
#define RegExChkH

//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.Actions.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.AppEvnts.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.Mask.hpp>
#include <Vcl.Menus.hpp>

//---------------------------------------------------------------------------
class TRegExChecker : public TForm
{
__published:	// IDE �ŊǗ������R���|�[�l���g
	TAction *CopyAction;
	TAction *CopyCAction;
	TAction *EditSampleAction;
	TAction *LoadSamplAction;
	TAction *PasteAction;
	TAction *ReplaceAction;
	TAction *TestAction;
	TActionList *ActionList1;
	TBevel *Bevel1;
	TButton *CCopyBtn;
	TButton *CopyBtn;
	TButton *HiddenCanBtn;
	TButton *MatchBtn;
	TButton *PasteBtn;
	TButton *RefFileBtn;
	TButton *ReplaceBtn;
	TCheckBox *CaseCheckBox;
	TCheckBox *DetailCheckBox;
	TCheckBox *UpdtCheckBox;
	TComboBox *PtnComboBox;
	TLabel *ResultLabel;
	TLabeledEdit *FileEdit;
	TLabeledEdit *ReplaceEdit;
	TListBox *ReferListBox;
	TListBox *ResListBox;
	TListBox *SampleListBox;
	TMemo *ObjMemo;
	TMenuItem *EditSampleItem;
	TMenuItem *LoadSampleItem;
	TPaintBox *StxPaintBox;
	TPanel *MainPanel;
	TPanel *OpePanel;
	TPanel *ReferPanel;
	TPanel *ResPanel;
	TPopupMenu *PopupMenu1;
	TSplitter *Splitter1;
	TSplitter *Splitter2;
	TSplitter *Splitter3;

	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall TestActionExecute(TObject *Sender);
	void __fastcall TestActionUpdate(TObject *Sender);
	void __fastcall ReplaceActionExecute(TObject *Sender);
	void __fastcall ReplaceActionUpdate(TObject *Sender);
	void __fastcall PasteActionExecute(TObject *Sender);
	void __fastcall PasteActionUpdate(TObject *Sender);
	void __fastcall CopyActionExecute(TObject *Sender);
	void __fastcall CopyActionUpdate(TObject *Sender);
	void __fastcall ReferListBoxDblClick(TObject *Sender);
	void __fastcall RefFileBtnClick(TObject *Sender);
	void __fastcall ResListBoxDrawItem(TWinControl *Control, int Index, TRect &Rect, TOwnerDrawState State);
	void __fastcall StxPaintBoxPaint(TObject *Sender);
	void __fastcall PtnComboBoxChange(TObject *Sender);
	void __fastcall DetailCheckBoxClick(TObject *Sender);
	void __fastcall LoadSamplActionExecute(TObject *Sender);
	void __fastcall EditSampleActionExecute(TObject *Sender);
	void __fastcall EditSampleActionUpdate(TObject *Sender);

private:	// ���[�U�[�錾
	int PtnSelStart;
	int PtnSelLength;
	bool with_Slash;

	TStringList *ResultList;
	TStringList *DetailList;

	int MatchCount;
	int MatchLines;

	UnicodeString SampleFile;
	TDateTime SampleTime;

public:		// ���[�U�[�錾
	TComboBox   *ObjComboBox;
	TCustomEdit *ObjCustomEdit;

	UnicodeString PatternStr;

	__fastcall TRegExChecker(TComponent* Owner);

	void __fastcall AssignSample(TStringList *lst);
	void __fastcall ReloadSample();
};
//---------------------------------------------------------------------------
extern PACKAGE TRegExChecker *RegExChecker;
//---------------------------------------------------------------------------
#endif
