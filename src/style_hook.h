//----------------------------------------------------------------------//
// TEdit/TMaskEdit/TLabeledEdit のスタイル・フック						//
// 背景色に Color を使用(システム色の場合はスタイル用に変換)			//
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
