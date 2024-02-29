/**
 * @file usr_migemo.h
 * @brief Migemo 処理
 */
//---------------------------------------------------------------------------
#ifndef UsrMigemoH
#define UsrMigemoH

//---------------------------------------------------------------------------
typedef struct _migemo migemo;
typedef migemo*			(WINAPI *FUNC_migemo_open)(const char*);
typedef void			(WINAPI *FUNC_migemo_close)(migemo*);
typedef unsigned char*	(WINAPI *FUNC_migemo_query)(migemo*, const unsigned char*);
typedef void 			(WINAPI *FUNC_migemo_release)(migemo*, unsigned char*);

//---------------------------------------------------------------------------
/**
 * @brief Migemo 処理
 */
class MigemoUnit
{
private:
	HINSTANCE hMigemo;
	migemo *MigemoObj;

	FUNC_migemo_open		f_migemo_open;
	FUNC_migemo_close		f_migemo_close;
	FUNC_migemo_query		f_migemo_query;
	FUNC_migemo_release		f_migemo_release;

public:
	bool Available;
	bool DictReady;
	UnicodeString PathName;
	UnicodeString FileName;
	int  MinLength;

	/**
	 * @brief コンストラクタ
	 * @param dnam Migemoディレクトリ
	 */
	MigemoUnit(UnicodeString dnam);

	~MigemoUnit();

	UnicodeString Query(UnicodeString qstr);

	/**
	 * @brief 正規表現パターンを取得
	 * 
	 * @param sw Migemoを利用
	 * @param w 検索語
	 * @param minlen 検索開始文字数
	 * @return UnicodeString 正規表現パターン
	 */
	UnicodeString GetRegExPtn(bool sw, UnicodeString w, int minlen = 0);
};

//---------------------------------------------------------------------------
#endif
