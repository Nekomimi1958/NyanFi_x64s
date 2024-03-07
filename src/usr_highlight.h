/**
 * @file usr_highlight.h
 * @brief 構文強調表示
 */
//---------------------------------------------------------------------------
#ifndef UsrHighlightH
#define UsrHighlightH

//---------------------------------------------------------------------------
#include "UIniFile.h"

//---------------------------------------------------------------------------
/**
 * @brief 構文強調表示定義ファイル
 */
class HighlightFile : public UsrIniFile
{
private:
	TDateTime HighlightTime;	//現在のタイムスタンプ

	void CheckValues();

public:
	UnicodeString CurSection;	//!< 使用中のセクション
	TStringList   *ErrorList;

	HighlightFile(UnicodeString fnam);
	~HighlightFile();

	UnicodeString ReadKeyStr(const _TCHAR *key);
	int			  ReadKeyInt(const _TCHAR *key, int def = 0);
	bool		  ReadKeyBool(const _TCHAR *key, bool def = false);
	UnicodeString ReadRegExPtn(const _TCHAR *key);
	TColor		  ReadColorRGB6H(const _TCHAR *key, TColor def = clBlack);

	/** @brief タイムスタンプが変化していたら再読み込み */
	bool Recycle();

	/**
	 * @brief 構文強調表示定義ファイルから対応セクションを取得
	 * @param fnam ファイル名
	 * @param is_clip クリップボード
	 * @param is_log タスクログ
	 * @param is_h2t HTML→TEXT変換モード
	 * @return true セクションを取得
	 */
	bool GetSection(UnicodeString fnam,
			bool is_clip = false, bool is_log = false, bool is_h2t = false);

	/**
	 * @brief コメント識別文字列を取得
	 * @param fnam ファイル名
	 * @param ln_lst 1行コメント
	 * @param bgn_lst ブロック開始
	 * @param end_lst ブロック終了
	 * @param is_h2t HTML→TEXT変換モード
	 * @param only_def デフォルトのみ取得
	 * @return true コメント識別文字列あり
	 */
	bool GetCommentList(UnicodeString fnam,
			TStringList *ln_lst, TStringList *bgn_lst, TStringList *end_lst,
			bool is_h2t = false, bool only_def = false);

	/**
	 * @brief リストボックスの指定行のコメント開始位置を取得
	 * @param fnam ファイル名
	 * @param lp リストボックス
	 * @param idx インデックス
	 * @param en_mlt 複数行コメントに対応
	 * @return int コメント開始位置
	 */
	int GetCommentPos(UnicodeString fnam, TListBox *lp, int idx, bool en_mlt = true);

	/**
	 * @brief 拡張子依存のデフォルト見出しパターンを取得
	 * @param fext 拡張子
	 * @return UnicodeString デフォルト見出しパターン
	 */
	UnicodeString GetDefHeadlnPtn(UnicodeString fext);

	/**
	 * @brief 見出しパターンを取得
	 * 
	 * @param fnam ファイル名
	 * @param hl_lst 拡張子対応見出しリスト
	 * @param only_def デフォルトのみ取得
	 * @return UnicodeString 見出しパターン
	 */
	UnicodeString GetHeadlinePtn(UnicodeString fnam, TStringList *hl_lst = NULL, bool only_def = false);
};
//---------------------------------------------------------------------------
extern HighlightFile *UserHighlight;

//---------------------------------------------------------------------------
/**
 * @brief デフォルトの予約語パターンを取得
 * @param fext 拡張子
 * @param sns_case 大小文字を区別
 * @param is_xml 対象がXML
 * @param is_log 対象がタスクログ
 * @param is_h2t HTML→TEXT変換モード
 * @return UnicodeString 予約語パターン 
 */
UnicodeString GetDefReservedPtn(UnicodeString fext, bool &sns_case, bool is_xml, bool is_log, bool is_h2t);

/**
 * @brief デフォルトの数値パターンを取得
 * @param fext 拡張子
 * @return UnicodeString 数値パターン
 */
UnicodeString GetDefNumericPtn(UnicodeString fext);

/**
 * @brief デフォルトのシンボル文字を取得
 * @param fext 拡張子
 * @param is_xml 対象がXML
 * @param is_h2t HTML→TEXT変換モード
 * @return UnicodeString 
 */
UnicodeString GetDefSymbolChars(UnicodeString fext, bool is_xml, bool is_h2t);

/**
 * @brief デフォルトの文字列引用符
 * @param fext 拡張子
 * @param[o] use_esc エスケープシーケンス有り
 * @param is_xml 対象がXML
 * @param is_ini 対象がINIファイル書式
 * @param is_h2t HTML→TEXT変換モード
 * @return UnicodeString 文字列引用符
 */
UnicodeString GetDefQuotChars(UnicodeString fext, bool &use_esc, bool is_xml, bool is_ini, bool is_h2t);

/**
 * @brief デフォルトの関数パターンを取得
 * @param fext 拡張子
 * @param[out] name_ptn 名前取得パターン
 * @param is_h2t HTML→TEXT変換モード
 * @return UnicodeString 関数パターン
 */
UnicodeString GetDefFunctionPtn(UnicodeString fext, UnicodeString &name_ptn, bool is_h2t);

/**
 * @brief SearchPair コマンド用検索パターンを取得
 * @param fext 拡張子
 * @param[out] lst 検索パターンのリスト
 * @return true 検索パターンあり
 */
bool GetSearchPairPtn(UnicodeString fext, TStringList *lst);

/**
 * @brief デフォルトの構文強調表示定義を取得
 * @param fext 拡張子
 * @param[out] lst 結果リスト
 * @param hl_lst 拡張子対応見出しリスト
 * @return true 構文強調表示定義あり
 */
bool GetDefaultHighlight(UnicodeString fext, TStringList *lst, TStringList *hl_lst = NULL);
//---------------------------------------------------------------------------
#endif
