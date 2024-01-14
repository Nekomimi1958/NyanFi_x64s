//----------------------------------------------------------------------//
// ファイルフィルタ処理クラス											//
//																		//
//----------------------------------------------------------------------//
#ifndef FileFilterH
#define FileFilterH

//---------------------------------------------------------------------------
UnicodeString GetFilterInfStr(UnicodeString filter, bool is_grep);
bool TestFilter(UnicodeString filter, bool is_grep);

//---------------------------------------------------------------------------
enum FilterOpt {foIsGrep, foExcludeTag};
typedef Set <FilterOpt, foIsGrep, foExcludeTag> FilterOption;

//---------------------------------------------------------------------------
class FileFilter
{
private:
	bool GetBlockRange(UnicodeString tag);
	void SetHtmlComent();

public:
	UnicodeString FileName;
	UnicodeString Filter;
	TStringList *FileBuff;
	bool isGrep;
	bool excludeTag;

	int topLine;
	int endLine;
	int strIndex;
	int strLength;
	UnicodeString objType, propName;

	FileFilter();
	~FileFilter();

	bool Initialize(UnicodeString fnam, TStringList *fbuf, UnicodeString filter, FilterOption opt);
	UnicodeString GetLinePart(int idx, int &r_idx, int &r_len, UnicodeString &lbuf);
	UnicodeString GetDispLine(int idx);
	bool IsValidLine(int idx);
};
//---------------------------------------------------------------------------
#endif