/**
 * @file style_hook.h
 * @author your name (you@domain.com)
 * @brief �X�^�C���E�t�b�N
 */
//---------------------------------------------------------------------------
#ifndef StyleHookH
#define StyleHookH

//---------------------------------------------------------------------------
/**
 * @brief �X�^�C���E�t�b�N
 * @details TEdit/TMaskEdit/TLabeledEdit �p�̃X�^�C���E�t�b�N�ł��B@n
 * �w�i�F�� Color ��K�p���܂�(�V�X�e���F�̏ꍇ�̓X�^�C���p�ɕϊ�)�B
 */
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
