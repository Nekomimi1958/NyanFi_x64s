/**
 * @file SubView.h
 * @brief �T�u�C���[�W�r���[�A
 */
//---------------------------------------------------------------------------
#ifndef SubViewH
#define SubViewH

//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.Actions.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ActnList.hpp>

//---------------------------------------------------------------------------
/**
 * @brief �T�u�C���[�W�r���[�A
 */
class TSubViewer : public TForm
{
__published:	// IDE �ŊǗ������R���|�[�l���g
	TAction *FlipHorzAction;
	TAction *FlipVertAction;
	TAction *RotateLeftAction;
	TAction *RotateRightAction;
	TActionList *ActionList1;
	TImage *Image1;
	TMenuItem *BgColItem;
	TMenuItem *FlipHItem;
	TMenuItem *FlipVItem;
	TMenuItem *LockItem;
	TMenuItem *RotateLItem;
	TMenuItem *RotateRItem;
	TMenuItem *Sep_1;
	TMenuItem *Sep_2;
	TPanel *ImgPanel;
	TPopupMenu *PopupMenu1;
	TShape *BorderShape1;
	TShape *BorderShape2;
	TShape *BorderShape3;

	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormHide(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall Image1Click(TObject *Sender);
	void __fastcall FormClick(TObject *Sender);
	void __fastcall PopupMenu1Popup(TObject *Sender);
	void __fastcall BgColItemClick(TObject *Sender);
	void __fastcall LockItemClick(TObject *Sender);
	void __fastcall RotateActionExecute(TObject *Sender);
	void __fastcall RotateActionUpdate(TObject *Sender);

private:	// ���[�U�[�錾
	bool hasBitmap;
	UnicodeString TitleInf, ZoomInf;

	void __fastcall WmSysCommand(TWMSysCommand & SysCom)
	{
		if (SysCom.CmdType==SC_CLOSE) {	//[�~]�{�^���������ꂽ
			Close();
			if (ScrMode==SCMD_IVIEW) ShowSubViewer = false;
		}
		else TForm::Dispatch(&SysCom);
	}

	void __fastcall WmExitSizeMove(TMessage &msg) { Application->MainForm->SetFocus(); }

	double __fastcall GetZoomRatio();

public:		// ���[�U�[�錾
	UnicodeString FileName;		//!< �\���t�@�C����
	bool formFileInf;			//!< �t�@�C�����_�C�A���O����\��
	bool isClip;				//!< �N���b�v�{�[�h

	bool FImgLocked;
	void __fastcall SetImgLocked(bool Value);
	/** @brief �\���̃��b�N */
	__property bool ImgLocked = {read = FImgLocked,  write = SetImgLocked};

	void __fastcall DrawImage(UnicodeString fnam = EmptyStr);	//!< �摜�̕`��
	void __fastcall RotateImage(int rn);						//!< ��]
	void __fastcall LockImage();								//!< ���b�N

	__fastcall TSubViewer(TComponent* Owner);

	BEGIN_MESSAGE_MAP
		VCL_MESSAGE_HANDLER(WM_SYSCOMMAND,		TWMSysCommand,	WmSysCommand)
		VCL_MESSAGE_HANDLER(WM_EXITSIZEMOVE,	TMessage,		WmExitSizeMove)
	END_MESSAGE_MAP(TForm)
};
//---------------------------------------------------------------------------
extern PACKAGE TSubViewer *SubViewer;
//---------------------------------------------------------------------------
#endif
