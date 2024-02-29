/**
 * @file icon_thread.h
 * @brief �A�C�R���擾�X���b�h
 */
//---------------------------------------------------------------------------
#ifndef TGetIconThreadH
#define TGetIconThreadH

//---------------------------------------------------------------------------
#include <System.Classes.hpp>

//---------------------------------------------------------------------------
/**
 * @brief �A�C�R���擾�X���b�h
 * 
 * CachedIcoList �Ƀt�@�C�������ǉ������ƁA���̃A���R�����擾���ăL���b�V�����܂�(Objects �ɐݒ�)�B
 * @attention CachedIcoList �𑀍삷��ۂ� IconRWLock �Ń��b�N���Ă��������B
 */
class TGetIconThread : public TThread
{
private:
	void __fastcall IconNotify();
	void __fastcall Execute();

public:
	HWND CallbackWnd;	//!< �ʒm��E�B���h�E�̃n���h��

	/**
	 * @brief �R���X�g���N�^
	 * @param CreateSuspended 
	 */
	__fastcall TGetIconThread(bool CreateSuspended);
};
//---------------------------------------------------------------------------
#endif
