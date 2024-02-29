/**
 * @file MaskSelDlg.h
 * @brief マスク/マッチ選択ダイアログ
 */
//---------------------------------------------------------------------------
#ifndef MaskSelDlgH
#define MaskSelDlgH

//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

//---------------------------------------------------
/**
 * @brief マスク/マッチ選択ダイアログ
 */
class TMaskSelectDlg : public TForm
{
__published:	// IDE で管理されるコンポーネント
	TButton *CanButton;
	TButton *OkButton;
	TComboBox *MaskSelComboBox;

	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);

private:	// ユーザー宣言
	bool IsMask;

public:		// ユーザー宣言
	UnicodeString CmdName;

	__fastcall TMaskSelectDlg(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMaskSelectDlg *MaskSelectDlg;
//---------------------------------------------------------------------------
#endif
