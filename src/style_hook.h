/**
 * @file style_hook.h
 * @author your name (you@domain.com)
 * @brief スタイル・フック
 */
//---------------------------------------------------------------------------
#ifndef StyleHookH
#define StyleHookH

//---------------------------------------------------------------------------
/**
 * @brief スタイル・フック
 * @details TEdit/TMaskEdit/TLabeledEdit 用のスタイル・フックです。@n
 * 背景色に Color を適用します(システム色の場合はスタイル用に変換)。
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
