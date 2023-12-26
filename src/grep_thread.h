//----------------------------------------------------------------------//
// GREP ƒXƒŒƒbƒh														//
//----------------------------------------------------------------------//
#ifndef TGrepThreadH
#define TGrepThreadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>

//---------------------------------------------------------------------------
#define MAX_GREP_THREAD		4
#define REFRESH_INTERVAL	250

//---------------------------------------------------------------------------
class TGrepThread : public TThread
{
private:
	void __fastcall Execute();

	int ID;
	int IndexTag;
	UnicodeString FileName;
	UnicodeString Keyword;

	bool opt_regex;
	bool opt_and;
	bool opt_case;
	bool opt_one;
	bool opt_xtag;

	TStringList *ResultList;
	void __fastcall AddResult();

public:
	__fastcall TGrepThread(bool CreateSuspended, int id,
							int idx_tag, UnicodeString fnam, UnicodeString kwd,
							bool sw_regex, bool sw_and, bool sw_case, bool sw_one, bool sw_xtag);
};
//---------------------------------------------------------------------------
#endif
