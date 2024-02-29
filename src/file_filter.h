/**
 * @file file_filter.h
 * @brief ファイルフィルタ処理
 */
//---------------------------------------------------------------------------
#ifndef FileFilterH
#define FileFilterH

//---------------------------------------------------------------------------
UnicodeString GetFilterInfStr(UnicodeString filter, bool is_grep);
bool TestFilter(UnicodeString filter, bool is_grep);

//---------------------------------------------------------------------------
enum FilterOpt {foIsGrep, foExcludeTag};
typedef Set <FilterOpt, foIsGrep, foExcludeTag> FilterOption;

//---------------------------------------------------------------------------
/**
 * @brief ファイルフィルタ処理
 */
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
	UnicodeString objType;
	UnicodeString propName;

	/** @brief コンストラクタ */
	FileFilter();

	~FileFilter();

	/**
	 * @brief 初期化
	 * @param fnam ファイル名
	 * @param fbuf ファイルバッファ
	 * @param filter フィルタ
	 * @param opt オプション
	 * @return true 
	 * @return false 
	 */
	bool Initialize(UnicodeString fnam, TStringList *fbuf, UnicodeString filter, FilterOption opt);

	/**
	 * @brief 行内容の取得
	 * @param idx インデックス
	 * @param[out] r_idx 開始位置
	 * @param[out] r_len 長さ
	 * @param[out] lbuf 表示用行内容
	 * @return UnicodeString 検索対象となる文字列
	 */
	UnicodeString GetLinePart(int idx, int &r_idx, int &r_len, UnicodeString &lbuf);

	/**
	 * @brief 表示用行内容を取得
	 * @param idx インデックス
	 * @return UnicodeString 表示用行内容
	 */
	UnicodeString GetDispLine(int idx);

	/**
	 * @brief 検索対象行か？
	 * @param idx インデックス
	 * @return true 検索対象行
	 */
	bool IsValidLine(int idx);
};
//---------------------------------------------------------------------------
#endif
