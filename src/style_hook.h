//----------------------------------------------------------------------//
// TEdit/TMaskEdit/TLabeledEdit �̃X�^�C���E�t�b�N						//
// �w�i�F�� Color ���g�p(�V�X�e���F�̏ꍇ�̓X�^�C���p�ɕϊ�)			//
//----------------------------------------------------------------------//
#ifndef StyleHookH
#define StyleHookH

//---------------------------------------------------------------------------
class TEditStyleHookColor : public TEditStyleHook
{
	typedef TEditStyleHook inherited;

private:
	void UpdateColors();

protected:
	virtual void __fastcall WndProc(TMessage &Message);

public:
	__fastcall TEditStyleHookColor(TWinControl *AControl);
};
//---------------------------------------------------------------------------
#endif
