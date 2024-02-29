/**
 * @file grep_thread.h
 * @brief GREP処理スレッド
 */
//---------------------------------------------------------------------------
#ifndef TGrepThreadH
#define TGrepThreadH

//---------------------------------------------------------------------------
#include <System.Classes.hpp>

//---------------------------------------------------------------------------
#define MAX_GREP_THREAD		4		//!< 最大スレッド数
#define REFRESH_INTERVAL	250		//!< メインフォームの更新間隔

//---------------------------------------------------------------------------
enum GrepOpt {goRegEx, goAnd, goCaseSens, goWord, goOneMatch, goExcludeTag};

/*** @brief 検索オプション */
typedef Set <GrepOpt, goRegEx, goExcludeTag> GrepOption;

//---------------------------------------------------------------------------
/**
 * @brief GREP処理スレッド
 */
class TGrepThread : public TThread
{
private:
	void __fastcall Execute();

	int ID;						//!< スレッド識別ID
	int IndexTag;				//!< インデックスタグ
	UnicodeString FileName;		//!< 対象ファイル名
	UnicodeString Keyword;		//!< 検索文字列
	UnicodeString Filter;		//!< フィルタ
	GrepOption    Options;		//!< 検索オプション

	TStringList *ResultList;
	void __fastcall AddResult();

public:
	/**
	 * @brief コンストラクタ
	 * @param CreateSuspended 
	 * @param id スレッド識別ID
	 * @param idx_tag インデックスタグ
	 * @param fnam 対象ファイル名
	 * @param kwd 検索文字列
	 * @param opt 検索オプション
	 * @param filter フィルタ
	 */
	__fastcall TGrepThread(bool CreateSuspended, int id,
					int idx_tag, UnicodeString fnam, UnicodeString kwd,
					GrepOption opt, UnicodeString filter = EmptyStr);
};
//---------------------------------------------------------------------------
#endif
