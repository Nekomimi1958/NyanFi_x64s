/**
 * @file usr_tag.h
 * @brief タグ管理ユニット
 */
//---------------------------------------------------------------------------
#ifndef UsrTagManagerH
#define UsrTagManagerH

//---------------------------------------------------------------------------
#include <Vcl.CheckLst.hpp>
#include "usr_str.h"

//---------------------------------------------------------------------------
/**
 * @brief タグ管理ユニット
 */
class TagManager
{
private:
	TDateTime TagDataTime;		//現在のタイムスタンプ
	bool Modified;

	TColor DefColor;			//デフォルトのタグ色

	int  GetIndex(UnicodeString fnam);
	void MakeTagNameList();

	UnicodeString GetDataTags(int idx)
	{
		return (idx!=-1)? get_post_tab(TagDataList->Strings[idx]) : EmptyStr;
	}

	UnicodeString GetDataTags(int idx, UnicodeString &fnam)
	{
		if (idx==-1) return EmptyStr;

		UnicodeString ret_str = TagDataList->Strings[idx];
		fnam = split_pre_tab(ret_str);
		return ret_str;
	}

public:
	UnicodeString FileName;
	bool SortTags;

	TStringList *TagNameList;
	TStringList *TagDataList;
	TStringList *TagColList;

	TMultiReadExclusiveWriteSynchronizer *TagRWLock;	//!< TagDataList の保護用

	TagManager(UnicodeString fnam);
	~TagManager();

	bool UpdateFile();		//!< ファイルを更新
	bool Recycle();			//!< タイムスタンプが変化していたら再読み込み
	int  TrimData();		//!< 存在しない項目のタグデータを整理

	UnicodeString GetTags(UnicodeString fnam);							//!< 指定ファイルのタグを取得
	UnicodeString NormTags(UnicodeString tags, bool sw_add = true);
	void DelItem(UnicodeString fnam);									//!< 指定ファイルのタグ情報を削除
	void SetTags(UnicodeString fnam, UnicodeString tags);				//!< 指定ファイルにタグを設定
	void AddTags(UnicodeString fnam, UnicodeString tags);				//!< 指定ファイルにタグを追加
	void Rename(UnicodeString old_nam, UnicodeString new_nam);			//!< ファイル/ディレクトリ名の変更
	void Copy(UnicodeString from_nam, UnicodeString to_nam);			//!< タグのコピー
	int  RenTag(UnicodeString old_tag, UnicodeString new_tag);			//!< タグの改名
	int  DelTagData(UnicodeString tag);									//!< タグデータの削除

	int IniCheckList(TCheckListBox *lp, UnicodeString tnam = EmptyStr, bool count_sw = false);
	UnicodeString CheckToTags(TCheckListBox *lp, UnicodeString tags);
	void CountTags(TCheckListBox *lp, bool clr_sw = false);

	/**
	 * @brief 指定タグにマッチするリストを取得
	 * @param tags タグ
	 * @param and_sw AND検索
	 * @param[out] lst リスト
	 * @return int マッチ数
	 */
	int  GetMatchList(UnicodeString tags, bool and_sw, TStringList *lst);

	/**
	 * @brief すべてのタグ項目のリストを取得
	 * @param[out] lst リスト
	 * @return int
	 */
	int  GetAllList(TStringList *lst);

	/** @brief ファイルにタグが付けられているか？ */
	bool HasTag(UnicodeString fnam);

	/**
	 * @brief ファイルが指定タグにマッチするか？
	 * @param fnam ファイル名
	 * @param ktags タグ
	 * @param and_sw AND検索
	 * @return true
	 * @return false
	 */
	bool Match(UnicodeString fnam, UnicodeString ktags, bool and_sw);

	/**
	 * @brief タグ色を取得
	 * @param tag タグ
	 * @param col_def デフォルト色
	 * @return TColor
	 */
	TColor GetColor(UnicodeString tag, TColor col_def);

	/**
	 * @brief タグ色を設定
	 * @param tag タグ
	 * @param col 色
	 */
	void SetColor(UnicodeString tag, TColor col);

	/**
	 * @brief タグの描画
	 * @param tags タグ
	 * @param cv キャンバス
	 * @param x X位置
	 * @param y Y位置
	 * @param col_rev 指定背景色で反転表示
	 * @param blk_sw ブロック記号を表示
	 */
	void DrawTags(UnicodeString tags, TCanvas *cv, int x, int y, TColor col_rev = Graphics::clNone, bool blk_sw = false);
};
//---------------------------------------------------------------------------
extern TagManager *usr_TAG;
//---------------------------------------------------------------------------
#endif
