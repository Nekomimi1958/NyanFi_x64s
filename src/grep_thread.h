//----------------------------------------------------------------------//
// GREP �X���b�h														//
//----------------------------------------------------------------------//
#ifndef TGrepThreadH
#define TGrepThreadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>

//---------------------------------------------------------------------------
#define MAX_GREP_THREAD		4
#define REFRESH_INTERVAL	250

//---------------------------------------------------------------------------
//�����I�v�V����
enum GrepOpt {goRegEx, goAnd, goCaseSens, goWord, goOneMatch, goExcludeTag};
typedef Set <GrepOpt, goRegEx, goExcludeTag> GrepOption;

//---------------------------------------------------------------------------
class TGrepThread : public TThread
{
private:
	void __fastcall Execute();

	int ID;
	int IndexTag;
	UnicodeString FileName;
	UnicodeString Keyword;
	UnicodeString Filter;
	GrepOption    Options;

	TStringList *ResultList;
	void __fastcall AddResult();

public:
	__fastcall TGrepThread(bool CreateSuspended, int id,
					int idx_tag, UnicodeString fnam, UnicodeString kwd,
					GrepOption opt, UnicodeString filter = EmptyStr);
};
//---------------------------------------------------------------------------
#endif
