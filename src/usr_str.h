/**
 * @file usr_str.h
 * @brief 文字列操作用の汎用関数
 */
//---------------------------------------------------------------------------
#ifndef UsrStrH
#define UsrStrH

//---------------------------------------------------------------------------
#include <System.JSON.hpp>

//---------------------------------------------------------------------------
extern bool DebugOut;	//!< デバッグ文字列送出(隠し設定)

/**
 * @brief デバッグ文字列送出
 * @details DebugOut=true の場合、デバッグ文字列を送出します(OutputDebugString)。
 * @param s 文字列
 */
void OutDebugStr(UnicodeString s);

//---------------------------------------------------------------------------
extern const _TCHAR *null_TCHAR;	//!< 空文字列へのポインタ

//---------------------------------------------------------------------------
int __fastcall comp_NaturalOrder(TStringList *List, int Index1, int Index2);	//!< 自然順
int __fastcall comp_AscendOrder(TStringList *List, int Index1, int Index2);		//!< 昇順
int __fastcall comp_DescendOrder(TStringList *List, int Index1, int Index2);	//!< 降順
int __fastcall comp_ObjectsOrder(TStringList *List, int Index1, int Index2);	//!< Objects 昇順

//---------------------------------------------------------------------------
#define TXLIMIT_MARK "\x03\x03\x03"	//!< 行数制限マーク

extern int  USR_CsvCol;				//!< ソート対象列
extern int  USR_CsvSortMode;		//!< ソートモード(1:昇順/ -1降順)
extern bool USR_CsvTopIsHdr;		//!< 先頭行は項目名

/**
 * @brief 文字列を数値として比較
 * @param s1 比較対象文字列1
 * @param s2 比較対象文字列2
 * @retval >0 s1>s2
 * @retval <0 s1<s2
 * @retval 0 s1==s2
 */
int comp_NumStr(UnicodeString s1, UnicodeString s2);

/**
 * @brief TStringList.CustomSort 用の比較関数: CSV自然昇順
 * @details 対象をCSVリストとみなし、自然昇順で比較します。@n
 * 数値として比較できなければ文字列順、同じならば行番号順((int)Objects)になります。@n
 * 比較は、USR_CsvCol、USR_CsvSortMode、USR_CsvTopIsHdr に基づいて行われます。
 * @sa USR_CsvCol
 * @sa USR_CsvSortMode
 * @sa USR_CsvTopIsHdr
 */
int __fastcall comp_CsvNaturalOrder(TStringList *List, int Index1, int Index2);

/**
 * @brief TStringList.CustomSort 用の比較関数: TSV自然昇順
 * @details 対象をTSVリストとみなし、自然昇順で比較します。@n
 * 数値として比較できなければ文字列順、同じならば行番号順((int)Objects)になります。@n
 * 比較は、USR_CsvCol、USR_CsvSortMode、USR_CsvTopIsHdr に基づいて行われます。
 * @sa USR_CsvCol
 * @sa USR_CsvSortMode
 * @sa USR_CsvTopIsHdr
 */
int __fastcall comp_TsvNaturalOrder(TStringList *List, int Index1, int Index2);

/** @brief TStringList.CustomSort 用の比較関数: TSV文字列順 */
int __fastcall comp_TsvTextOrder(TStringList *List, int Index1, int Index2);

//---------------------------------------------------------------------------
/**
 * @brief 指定セパレータの前の文字列を取得
 * @details * 指定したセパレータ文字列の前にある文字列を取得します。@n
 * セパレータが見つからない場合は、文字列をそのまま返します。
 * @param s 対象文字列
 * @param sp セパレータ文字列
 * @return UnicodeString
 */
UnicodeString get_tkn(UnicodeString s, UnicodeString sp);

/**
 * @brief 指定セパレータの後の文字列を取得
 * @details 指定したセパレータ文字列の後にある文字列を取得します。@n
 * セパレータが見つからない場合は、EmptyStr を返します。
 * @param s 対象文字列
 * @param sp セパレータ文字列
 * @return UnicodeString
 */
UnicodeString get_tkn_r(UnicodeString s, UnicodeString sp);

/**
 * @brief 指定セパレータ間の文字列を取得
 * @details 指定した2つのセパレータ文字列の間にある文字列を取得します。@n
 * セパレータ2が見つからない場合は、セパレータ1以降の文字列を返します。
 * @param s 対象文字列
 * @param sp1 セパレータ文字列1
 * @param sp2 セパレータ文字列2
 * @return UnicodeString
 */
UnicodeString get_tkn_m(UnicodeString s, UnicodeString sp1, UnicodeString sp2);

/**
 * @brief タブ文字の前にある文字列を取得
 * @details タブ文字の前にある文字列を取得します。タブ文字がない場合は、文字列をそのまま返します。
 * @param s 対象文字列
 * @return UnicodeString
 */
UnicodeString get_pre_tab(UnicodeString s);

/**
 * @brief タブ文字の後にある文字列を取得
 * @details タブ文字の後にある文字列を取得します。タブ文字がない場合は、EmptyStr を返します。
 * @param s 対象文字列
 * @return UnicodeString
 */
UnicodeString get_post_tab(UnicodeString s);

/**
 * @brief 複数行文字列の1行目の内容を取得
 * @param s 対象文字列
 * @return UnicodeString
 */
UnicodeString get_first_line(UnicodeString s);

/**
 * @brief 文字列中にある括弧内 (～) の文字列を取得
 * @param s 対象文字列
 * @return UnicodeString
 */
UnicodeString get_in_paren(UnicodeString s);

/**
 * @brief 文字列中にある括弧内 (～) の文字列を取得
 * @details 文字列中にある括弧内 (～) の文字列を取得します。元文字列は (～) の後続文字列になります。
 * @param s 対象文字列
 * @return UnicodeString
 */
UnicodeString split_in_paren(UnicodeString &s);

/**
 * @brief 前後にタブを含まない文字列を取得
 * @details 前後にタブを含まない文字列を取得します。対象が複数行の場合、空でない最初の文字列を返します。
 * @param s 対象文字列
 * @param trim_sw 前後の空白や制御文字を削除
 * @return UnicodeString
 */
UnicodeString get_norm_str(UnicodeString s, bool trim_sw = false);

/**
 * @brief 指定セパレータ前の文字列を分離して取得
 * @details 指定したセパレータ文字列の前にある文字列を分離して取得します。@n
 * 元文字列は、セパレータ文字列の後続文字列になります。@n
 * セパレータが見つからない場合は、文字列をそのまま返し、元文字列は空になります。
 * @param s 対象文字列
 * @param sp セパレータ文字列
 * @return UnicodeString
 */
UnicodeString split_tkn(UnicodeString &s, UnicodeString sp);

/**
 * @brief 空白区切り前の文字列を分離して取得
 * @details 空白区切りの前に前にある文字列を分離して取得します。@n
 * 先頭部分にある空白は、区切りと見なされません。例えば、split_tkn_spc("  abc def") は "  abc" を返します。
 * @param s 対象文字列
 * @return UnicodeString
 */
UnicodeString split_tkn_spc(UnicodeString &s);

/**
 * @brief タブ前の文字列を分離して取得
 * @details タブ文字の前にある文字列を分離して取得します。元文字列は、タブの後続文字列になります。@n
 * タブがない場合は、文字列をそのまま返し、元文字列は空になります。
 * @param s 対象文字列
 * @return UnicodeString
 */
UnicodeString split_pre_tab(UnicodeString &s);

/**
 * @brief 文字列から説明部分(^:～:)を分離して取得
 * @details 対象文字列の先頭にある説明部分(^:～:)を分離して取得します。元文字列は、説明部分の後続文字列になります。
 * @param s 対象文字列
 * @return UnicodeString
 */
UnicodeString split_dsc(UnicodeString &s);

/**
 * @brief 文字列から先頭文字を分離して取得
 * @details 文字列の先頭にある文字を分離して取得します。元文字列は、2文字目以降の文字列になります。
 * @param s 対象文字列
 * @return UnicodeString
 */
UnicodeString split_top_ch(UnicodeString &s);

/**
 * @brief 文字列から先頭文字を分離して取得
 * @details 文字列の先頭にある文字を分離して取得します。元文字列は、2文字目以降の文字列になります。
 * @param s 対象文字列
 * @return WideChar
 */
WideChar split_top_wch(UnicodeString &s);

/**
 * @brief コマンドラインをパラメータに分解
 * @details 対象文字列をコマンドラインとみなし、パラメータのリストを作成します。
 * @param s 対象文字列
 * @param[out] lst パラメータのリスト
 * @return int
 */
int split_cmd_line(UnicodeString s, TStringList *lst);

/**
 * @brief コマンドラインからファイル名を分離
 * @details 対象文字列をコマンドラインとみなし、先頭のファイル名部分を分離して取得します。@n
 * 元文字列は、ファイル名以降のパラメータ部分になります。
 * @param s 対象文字列
 * @return UnicodeString
 */
UnicodeString split_file_param(UnicodeString &s);

/**
 * @brief 文字列をタブ文字で分割し配列として取得
 * @param s 対象文字列
 * @return TStringDynArray
 */
TStringDynArray split_strings_tab(UnicodeString s);

/**
 * @brief 文字列をセミコロンで分割し配列として取得
 * @param s 対象文字列
 * @param del_empty EmptyStrを除外
 * @return TStringDynArray 
 */
TStringDynArray split_strings_semicolon(UnicodeString s, bool del_empty = false);

/**
 * @brief 文字列から検索文字列を削除
 * @param s 対象文字列
 * @param w 検索文字列
 * @return true 検索文字列を削除した
 * @return false 検索文字列が含まれていない
 */
bool remove_text(UnicodeString &s, UnicodeString w);

/**
 * @brief 文字列の先頭に検索文字列があったら削除(大小文字を無視)
 * @param s 対象文字列
 * @param w 検索文字列
 * @return true 先頭の検索文字列を削除した
 * @return false 先頭に検索文字列がない
 */
bool remove_top_text(UnicodeString &s, UnicodeString w);

/**
 * @brief 文字列の先頭に検索文字列があったら削除(大小文字を区別)
 * @param s 対象文字列
 * @param w 検索文字列
 * @return true 先頭の検索文字列を削除した
 * @return false 先頭に検索文字列がない
 */
bool remove_top_s(UnicodeString &s, UnicodeString w);

/**
 * @brief 文字列の先頭に @ があったら削除
 * @param s 対象文字列
 * @return true 先頭の @ を削除した
 * @return false 先頭に @ がない
 */
bool remove_top_AT(UnicodeString &s);

/**
 * @brief 文字列の先頭に $ があったら削除
 * @param s 対象文字列
 * @return true 先頭の $ を削除した
 * @return false 先頭に $ がない
 */
bool remove_top_Dollar(UnicodeString &s);

/**
 * @brief 文字列の末尾に検索文字列があったら削除(大小文字を無視)
 * @param s 対象文字列
 * @param w 検索文字列
 * @return true 末尾の検索文字列を削除した
 * @return false 末尾に検索文字列がない
 */
bool remove_end_text(UnicodeString &s, UnicodeString w);

/**
 * @brief 文字列の末尾に検索文字列があったら削除(大小文字を区別)
 * @param s 対象文字列
 * @param w 検索文字列
 * @return true 末尾の検索文字列を削除した
 * @return false 末尾に検索文字列がない
 */
bool remove_end_s(UnicodeString &s, UnicodeString w);

/**
 * @brief 文字列の末尾を1文字削除
 * @param s 対象文字列
 */
void delete_end(UnicodeString &s);

/**
 * @brief 先頭の1文字を除外した文字列を取得
 * @param s 対象文字列
 * @return UnicodeString
 */
UnicodeString exclude_top(UnicodeString s);

/**
 * @brief 先頭と末尾の文字を除外した文字列を取得
 * @param s 対象文字列
 * @return UnicodeString
 */
UnicodeString exclude_top_end(UnicodeString s);

/**
 * @brief 全角空白も考慮したトリミング
 * @param s 対象文字列
 * @return UnicodeString
 */
UnicodeString trim_ex(UnicodeString s);

/**
 * @brief ^ による先頭の連続削除を回避した置換
 * @param s 対象文字列
 * @param ptn パターン
 * @param rep 置換文字列
 * @param opt オプション
 * @return UnicodeString 
 */
UnicodeString replace_regex_2(UnicodeString s, UnicodeString ptn, UnicodeString rep, TRegExOptions opt);

/**
 * @brief //リスト(検索文字列 [TAB] 置換文字列)にしたがって文字列を置換
 * @param s 対象文字列
 * @param lst リスト
 * @return UnicodeString 
 */
UnicodeString replace_str_by_list(UnicodeString s, TStringList *lst);

/**
 * @brief ; 区切りで文字列を追加
 *
 * 対象文字列が空でない、セミコロンで区切って文字列を追加します。
 *
 * @param s 対象文字列
 * @param t 追加文字列
 */
void cat_str_semicolon(UnicodeString &s, UnicodeString t);

/**
 * @brief 文字列が指定長になるまで先頭に空白を挿入
 * @param s 対象文字列
 * @param len 文字列の長さ
 * @return UnicodeString
 */
UnicodeString ins_spc_length(UnicodeString s, int len);

/**
 * @brief 文字列が空ならデフォルト文字列を取得
 * @param s 対象文字列
 * @param def デフォルト文字列
 * @return UnicodeString 
 */
UnicodeString def_if_empty(UnicodeString s, UnicodeString def);

/**
 * @brief 文字列が空でないなら区切り文字列を追加
 * @param s 対象文字列
 * @param sep 区切り文字列
 */
void cat_separator(UnicodeString &s, UnicodeString sep);

/**
 * @brief 文字列が空でないなら区切り文字列を挿入して、指定文字列を追加
 * @param s 対象文字列
 * @param sep 区切り文字列
 * @param s2 追加文字列
 */
void ins_sep_cat(UnicodeString &s, UnicodeString sep, UnicodeString s2);

/**
 * @brief 文字列を NativeInt 値に変換
 * @param s 対象文字列
 * @return NativeInt
 */
NativeInt str_to_NativeInt(UnicodeString s);

/**
 * @brief 文字列から整数値を抽出
 * @param s 対象文字列
 * @return int
 * @exception 失敗した場合は例外を送出
 */
int extract_int(UnicodeString s);

/**
 * @brief 文字列から整数値を抽出
 * @details 文字列から整数値を抽出します。有効な値が取得できない場合は、デフォルト値を返します。
 * @param s 対象文字列
 * @param def デフォルト値
 * @return int
 */
int extract_int_def(UnicodeString s, int def = 0);

/**
 * @brief 文字列の先頭から数値部分の文字列を取得
 * @details 文字列の先頭から数値部分の文字列を取得します。カンマは無視、+/-、コンマに対応しています。
 * @param s 対象文字列
 * @return UnicodeString
 */
UnicodeString extract_top_num_str(UnicodeString s);

/**
 * @brief long double 値を文字列に変換
 * @param v 数値
 * @param f_w 小数部の桁数
 * @return UnicodeString
 */
UnicodeString ldouble_to_str(long double v, int f_w = 3);

/**
 * @brief サイズの数値を文字列に変換(TBまで)
 * @param sz サイズ
 * @param dg 桁数
 * @return UnicodeString
 */
UnicodeString get_size_str_T(__int64 sz, int dg);

/**
 * @brief サイズの数値を文字列に変換(GBまで)
 * @param sz サイズ
 * @param wd 桁指定
 * @param dg 小数桁数
 * @return UnicodeString
 */
UnicodeString get_size_str_G(__int64 sz, int wd = 10, int dg = 1);

/**
 * @brief サイズの数値を文字列に変換(GBまで)
 * @param sz サイズ
 * @param wd 桁指定
 * @param dg 小数桁数
 * @param fmt_mode 表示モード(0:GB/MB/バイト  1:GB/MB/KB/バイト  2:GB/MB/KB);
 * @return UnicodeString
 */
UnicodeString get_size_str_G(__int64 sz, int wd, int dg, int fmt_mode);

UnicodeString get_size_str_B(__int64 sz, int wd = 14);
UnicodeString get_size_str_C(int sz);
UnicodeString get_size_str_K(SIZE_T sz);

/**
 * @brief RRGGBB形式の文字列を TColor に変換
 * @param s 対象文字列
 * @return TColor
 */
TColor xRRGGBB_to_col(UnicodeString s);

/**
 * @brief TColor 値をRRGGBB形式の文字列に変換
 * @param col
 * @return UnicodeString
 */
UnicodeString col_to_xRRGGBB(TColor col);

/**
 * @brief 指定文字列の位置を取得(大小文字を無視)
 * @param wd 検索文字列
 * @param s 対象文字列
 * @return int 文字インデックス(1ベース、見つからない場合は 0)
 */
int pos_i(UnicodeString wd, UnicodeString s);

/**
 * @brief 指定文字列が最後に現れる位置を取得(大小文字を区別)
 * @param wd 検索文字列
 * @param s 対象文字列
 * @return int 文字インデックス(1ベース、見つからない場合は 0)
 */
int pos_r(UnicodeString wd, UnicodeString s);

/**
 * @brief 指定文字列が最後に現れる位置を取得(大小文字を無視)
 * @param wd 検索文字列
 * @param s 対象文字列
 * @return int 文字インデックス(1ベース、見つからない場合は 0)
 */
int pos_r_i(UnicodeString wd, UnicodeString s);

/**
 * @brief 引用符外で、指定文字列が最後に現れる位置を取得(大小文字を区別)
 * @param wd 検索文字列
 * @param s 対象文字列
 * @return int 文字インデックス(1ベース、見つからない場合は 0)
 */
int pos_r_q(UnicodeString wd, UnicodeString s);
int pos_r_q_colon(UnicodeString s);

bool contains_upper(UnicodeString s);

/**
 * @brief 文字列に検索文字列が含まれているか？
 * @details 対象文字列に検索文字列が含まれているかどうかを調べます。@n
 * 検索文字列では、AND(' ') / OR('|') 指定が可能です。
 * @param s 対象文字列
 * @param kwd 検索文字列
 * @param case_sw 大小文字区別
 * @return true
 * @return false
 */
bool contains_word_and_or(UnicodeString s, UnicodeString kwd, bool case_sw = false);
bool contains_fuzzy_word(UnicodeString s, UnicodeString kwd, bool case_sw = false, UnicodeString sp = EmptyStr);

/**
 * @brief 検索文字列が | 区切りリストに含まれているか(大小文字を無視)?
 * @param lst | 区切りリスト
 * @param wd 検索文字列
 * @return true
 * @return false
 */
bool contained_wd_i(UnicodeString lst, UnicodeString wd);

/**
 * @brief 対象文字列が | 区切りリストの語を含んでいるか(大小文字を無視)？
 * @param s 対象文字列
 * @param lst | 区切りリスト
 * @return true
 * @return false
 */
bool contains_wd_i(UnicodeString s, UnicodeString lst);

/**
 * @brief | 区切りリストから指定インデックスの文字列を取得(大小文字を無視)
 * @param lst | 区切りリスト
 * @param idx インデックス(0ベース)
 * @return UnicodeString
 */
UnicodeString get_word_i_idx(UnicodeString lst, int idx);

/**
 * @brief | 区切りリストから検索文字列のインデックスを取得(大小文字を無視)
 * @param lst | 区切りリスト
 * @param wd 検索文字列
 * @return int インデックス(0ベース、見つからない場合は -1)
 */
int idx_of_word_i(UnicodeString lst, UnicodeString wd);

/**
 * @brief 検索文字列が | 区切りリストにあるか？
 * @param w 検索文字列
 * @param list | 区切りリスト
 * @return true
 * @return false
 */
bool test_word_i(UnicodeString w, UnicodeString list);

/**
 * @brief ワイルドカードを含むパターンによる文字列マッチ
 * @param ptn パターン
 * @param s 対象文字列
 * @return true
 * @return false
 */
bool str_match(UnicodeString ptn, UnicodeString s);

/**
 * @brief 正しい正規表現パターンか？
 * @param ptn パターン
 * @return true
 * @return false
 */
bool chk_RegExPtn(UnicodeString ptn);

/**
 * @brief ; 区切り文字列から正規表現パターン(/～/)を抽出
 * @param s 対象文字列(; 区切り)
 * @return UnicodeString
 */
UnicodeString extract_prm_RegExPtn(UnicodeString &s);

/**
 * @brief 文字列に指定文字列/パターンが含まれているか？
 * @param ptn 文字列/パターン
 * @param s 対象文字列
 * @return UnicodeString マッチした部分の文字列
 */
UnicodeString ptn_match_str(UnicodeString ptn, UnicodeString s);

/**
 * @brief 文字列が指定語/パターンで始まっているか？
 * @param ptn 文字列(/～/ なら正規表現パターン)
 * @param s 対象文字列
 * @return true
 * @return false
 */
bool starts_ptn(UnicodeString ptn, UnicodeString s);

/**
 * @brief あいまい検索のための正規表現パターンを取得
 * @param kwd キーワード
 * @param sep_sw \s,\\,/ 区切りをまたがない
 * @return UnicodeString
 */
UnicodeString get_fuzzy_ptn(UnicodeString kwd, bool sep_sw = false);

/**
 * @brief 検索語リスト作成
 * @param wd 対象文字列
 * @param[out] lst
 */
void get_find_wd_list(UnicodeString wd, TStringList *lst);

/**
 * @brief 複数の文字列を OR/AND 検索
 * @param wd 検索語(複数の場合は半角または全角空白で区切る)
 * @param s 対象文字列
 * @param and_sw AND検索
 * @param not_sw NOT検索
 * @param case_sw 大小文字を区別
 * @param word_sw 単語単位
 * @return true 
 * @return false 
 */
bool find_mlt(UnicodeString wd, UnicodeString s,
		bool and_sw = false, bool not_sw = false, bool case_sw = false, bool word_sw = false);

/**
 * @brief 複数の文字列を検索し、マッチした語のリストを取得する
 * @param wd 検索語 (複数の場合は半角または全角空白で区切る)
 * @param s 対象文字列
 * @param[out] lst マッチした語のリスト
 * @param case_sw 大小文字を区別
 * @return true 
 * @return false 
 */
bool find_mlt_str(UnicodeString wd, UnicodeString s, TStringList *lst, bool case_sw);

/**
 * @brief 文字列の行数を取得
 * @param s 対象文字列
 * @return int 行数
 */
int get_line_count(UnicodeString s);

/**
 * @brief TStringDynArray に文字列を追加
 * @param lst
 * @param s 追加文字列
 * @param no_dupl 既存の場合は追加しない
 */
void add_dyn_array(TStringDynArray &lst, UnicodeString s, bool no_dupl = false);

/**
 * @brief TStringDynArray の指定インデックス項目を取得
 * @param items
 * @param idx インデックス
 * @return UnicodeString
 */
UnicodeString get_array_item(TStringDynArray items, int idx);

/**
 * @brief TStringDynArray の全要素を指定区切り文字列を用いて結合
 * @param lst
 * @param sep 区切り文字列
 * @return UnicodeString
 */
UnicodeString join_dynarray(TStringDynArray lst, UnicodeString sep);

/**
 * @brief CSV文字列の項目内容を TStringDynArray として取得
 * @param src 対象文字列
 * @param size 項目数
 * @param force_size 項目数を強制的に設定
 * @return TStringDynArray
 */
TStringDynArray get_csv_array(UnicodeString src, int size, bool force_size = false);

/**
 * @brief CSV文字列の項目内容を TStringDynArray として取得(引用符を考慮)
 * @param src 対象文字列
 * @param size 項目数
 * @param del_q 引用符を外す
 * @return TStringDynArray
 */
TStringDynArray get_csv_array_Q(UnicodeString src, int size, bool del_q = true);

/**
 * @brief CSV文字列から指定インデックスの項目を取得
 * @param src 対象文字列
 * @param idx インデックス
 * @return UnicodeString
 */
UnicodeString get_csv_item(UnicodeString src, int idx);

/**
 * @brief TSV文字列から指定インデックスの項目を取得
 * @param src 対象文字列
 * @param idx インデックス
 * @return UnicodeString
 */
UnicodeString get_tsv_item(UnicodeString src, int idx);

/**
 * @brief CSV項目を作成
 * @param s 対象文字列
 * @return UnicodeString
 */
UnicodeString make_csv_str(UnicodeString s);

/**
 * @brief bool 値のCSV項目を作成
 * @param sw
 * @return UnicodeString
 */
UnicodeString make_csv_str(bool sw);

/**
 * @brief TStringDynArray からCSV文字列を作成
 * @param lst
 * @return UnicodeString
 */
UnicodeString make_csv_rec_str(TStringDynArray lst);
UnicodeString make_csv_rec_str(std::initializer_list<UnicodeString> lst);

/**
 * @brief CSVリストから、指定列インデックスの項目が検索文字列に一致する行インデックスを取得
 * @param lst CSVリスト
 * @param s 検索文字列
 * @param p 列インデックス
 * @return int
 */
int indexof_csv_list(TStringList *lst, UnicodeString s, int p);

/**
 * @brief CSVのリストから p 番目の項目が s のレコードを取得
 * @param lst CSVリスト
 * @param s 検索文字列
 * @param p 列インデックス
 * @param size 列サイズ
 * @return TStringDynArray
 */
TStringDynArray record_of_csv_list(TStringList *lst, UnicodeString s, int p, int size);

/**
 * @brief エスケープシーケンス文字の変換
 * @param s 対象文字列
 * @return UnicodeString
 */
UnicodeString conv_esc_char(UnicodeString s);

/**
 * @brief \\ を / に置換
 * @param s 対象文字列
 * @return UnicodeString
 */
UnicodeString yen_to_slash(UnicodeString s);

/**
 * @brief / を \\ に置換
 * @param s 対象文字列
 * @return UnicodeString
 */
UnicodeString slash_to_yen(UnicodeString s);

/**
 * @brief SHA-1 を7桁の短縮形に変換
 * @param s 対象ハッシュ文字列
 * @return UnicodeString
 */
UnicodeString sha1_to_short(UnicodeString s);

/**
 * @brief 文字列は "1" か？
 * @param s 対象文字列
 * @return true
 * @return false
 */
bool equal_1(UnicodeString s);

/**
 * @brief 文字列は "0" か？
 * @param s 対象文字列
 * @return true
 * @return false
 */
bool equal_0(UnicodeString s);

/**
 * @brief 文字列は "ENTER" か？
 * @param s 対象文字列
 * @return true
 * @return false
 */
bool equal_ENTER(UnicodeString s);

/**
 * @brief 文字列は "ESC" か？
 * @param s 対象文字列
 * @return true
 * @return false
 */
bool equal_ESC(UnicodeString s);

/**
 * @brief 文字列は "TAB" か？
 * @param s 対象文字列
 * @return true
 * @return false
 */
bool equal_TAB(UnicodeString s);

/**
 * @brief 文字列は "DEL" か？
 *
 * @param s 対象文字列
 * @return true
 * @return false
 */
bool equal_DEL(UnicodeString s);

/**
 * @brief 文字列は "LEFT" か？
 * @param s 対象文字列
 * @return true
 * @return false
 */
bool equal_LEFT(UnicodeString s);

/**
 * @brief 文字列は "RIGHT" か？
 * @param s 対象文字列
 * @return true
 * @return false
 */
bool equal_RIGHT(UnicodeString s);

/**
 * @brief 文字列は "UP" か？
 * @param s 対象文字列
 * @return true
 * @return false
 */
bool equal_UP(UnicodeString s);

/**
 * @brief 文字列は "DOWN" か？
 * @param s 対象文字列
 * @return true
 * @return false
 */
bool equal_DOWN(UnicodeString s);

/**
 * @brief 文字列は "HOME" か？
 * @param s 対象文字列
 * @return true
 * @return false
 */
bool equal_HOME(UnicodeString s);

/**
 * @brief 文字列は "END" か？
 * @param s 対象文字列
 * @return true
 * @return false
 */
bool equal_END(UnicodeString s);

/**
 * @brief 文字列は "F1" か？
 * @param s 対象文字列
 * @return true
 * @return false
 */
bool equal_F1(UnicodeString s);

/**
 * @brief 文字列は "F5" か？
 * @param s 対象文字列
 * @return true
 * @return false
 */
bool equal_F5(UnicodeString s);

/**
 * @brief 文字列はセパレータ("-")か？
 * @param s 対象文字列
 * @return true
 * @return false
 */
bool is_separator(UnicodeString s);

/**
 * @brief 英数文字列か？
 * @param s 対象文字列 
 * @return true 
 * @return false 
 */
bool is_alnum_str(UnicodeString s);

/**
 * @brief 英単語か？
 * @param s 対象文字列
 * @param p 位置
 * @param len 長さ
 * @return true 
 * @return false 
 */
bool is_word(UnicodeString s, int p, int len);

/**
 * @brief 文字列の先頭が指定文字リストのいずれかに一致するか？
 * @param lst 文字リスト
 * @param s 対象文字列
 * @return true
 * @return false
 */
bool starts_tchs(UnicodeString lst, UnicodeString s);

/**
 * @brief 文字列の末尾が指定文字リストのいずれかに一致するか？
 * @param lst 文字リスト
 * @param s 対象文字列
 * @return true
 * @return false
 */
bool ends_tchs(UnicodeString lst, UnicodeString s);

/**
 * @brief 文字列が @ で始まっているか ?
 * @param s 対象文字列
 * @return true
 * @return false
 */
bool starts_AT(UnicodeString s);

/**
 * @brief 文字列が $ で始まっているか ?
 * @param s 対象文字列
 * @return true
 * @return false
 */
bool starts_Dollar(UnicodeString s);

/**
 * @brief 文字列の末尾が \ か？
 * @param s 対象文字列
 * @return true
 * @return false
 */
bool ends_PathDlmtr(UnicodeString s);

/**
 * @brief 文字列に \ が含まれているか？
 * @param s 対象文字列
 * @return true
 * @return false
 */
bool contains_PathDlmtr(UnicodeString s);

/**
 * @brief 文字列に / が含まれているか？
 * @param s 対象文字列
 * @return true
 * @return false
 */
bool contains_Slash(UnicodeString s);

/**
 * @brief 文字列に含まれている \ の個数を取得
 * @param s 対象文字列
 * @return int
 */
int  count_PathDlmtr(UnicodeString s);

/**
 * @brief 文字列は正規表現(/～/)か？
 * @param s 対象文字列
 * @return true
 * @return false
 */
bool is_regex_slash(UnicodeString s);

/**
 * @brief 文字列が引用符で囲まれているか？
 * @param s 対象文字列
 * @return true
 * @return false
 */
bool is_quot(UnicodeString s);

/**
 * @brief 文字列が空白を含んでいたら引用符で囲む
 * @param s 対象文字列
 * @return UnicodeString
 */
UnicodeString add_quot_if_spc(UnicodeString s);

/**
 * @brief 文字列の引用符を外す
 * @param s 対象文字列
 * @return UnicodeString
 */
UnicodeString exclude_quot(UnicodeString s);

/**
 * @brief TStringList Vlues[name] の整数値を取得
 * @param lst 対象リスト
 * @param name 名前
 * @param def デフォルト値 
 * @return int 
 */
int  get_ListIntVal(TStringList *lst, UnicodeString name, int def = 0);

/**
 * @brief TStringList Vlues[name] が空か？
 * @param lst 対象リスト
 * @param name 名前
 * @return true 
 * @return false 
 */
bool ListVal_is_empty(TStringList *lst, UnicodeString name);

/**
 * @brief TStringList Vlues[name]=="1"?
 * @param lst 対象リスト
 * @param name 名前
 * @return true 
 * @return false 
 */
bool ListVal_equal_1(TStringList *lst, UnicodeString name);

/**
 * @brief 文字列を履歴として重複なしでリスト追加
 * @param[in,out] lst リスト
 * @param s 追加文字列
 */
void add_as_history(TStrings *lst, UnicodeString s);

/**
 * @brief m秒を時間文字列に変換
 * @param ms ミリ秒値
 * @param cs 1/100秒を表示
 * @return UnicodeString
 */
UnicodeString __fastcall mSecToTStr(unsigned int ms, bool cs = true);

/**
 * @brief パラメータ文字列(S/M/Hを含む)をm秒値に変換
 * @param prm パラメータ文字列
 * @return int
 */
int param_to_mSec(UnicodeString prm);

/**
 * @brief 文字列の表示幅を取得
 * @param cv キャンバス
 * @param s 対象文字列
 * @param spc_sw 半/全角空白の代替文字を考慮
 * @return int 表示幅
 */
int get_TextWidth(TCanvas *cv, UnicodeString s, bool spc_sw = false);

int get_CharWidth(TCanvas *cv, int n, int mgn = 0);

/**
 * @brief TPanel 内での文字列幅を取得
 * @param s 対象文字列 
 * @param pp パネル
 * @param d2d_sw Direct2D で取得
 * @return int 
 */
int get_WidthInPanel(UnicodeString s, TPanel *pp, bool d2d_sw = false);

/**
 * @brief 半角換算の文字列長を取得
 * @param s 対象文字列
 * @return int
 */
int str_len_half(UnicodeString s);

/**
 * @brief サロゲートペアを考慮して文字長を取得
 * @param s 対象文字列
 * @return int
 */
int str_len_unicode(UnicodeString s);

/**
 * @brief 半角換算の最大幅を更新
 * @param[o] w 最大幅
 * @param s 対象文字列
 */
void max_len_half(int &w, UnicodeString s);

/**
 * @brief 指定幅(半角単位)内で文字列が右詰になるように空白を挿入
 * @param s 対象文字列
 * @param wd 幅
 * @param post_s 追加文字列
 * @return UnicodeString
 */
UnicodeString align_r_str(UnicodeString s, int wd, UnicodeString post_s = EmptyStr);

/**
 * @brief 指定幅(半角単位)内で文字列が左詰になるように空白を挿入
 * @param s 対象文字列
 * @param wd 幅
 * @param post_s 追加文字列
 * @return UnicodeString
 */
UnicodeString align_l_str(UnicodeString s, int wd, UnicodeString post_s = EmptyStr);

/**
 * @brief 文字列が指定幅に収まるように調整
 * @param s 対象文字列
 * @param cv 
 * @param wd 制限幅
 * @param omit_end 末尾を省略 (false: 中間を省略)
 * @param spc_sw 半/全角空白の代替文字を考慮
 * @return UnicodeString 
 */
UnicodeString minimize_str(UnicodeString s, TCanvas *cv, int wd, bool omit_end = false, bool spc_sw = false);

/**
 * @brief 文字列が指定幅になるように省略/空白追加
 * @param s 対象文字列
 * @param cv
 * @param wd 制限幅
 * @param omit_end 末尾を省略(false の場合は中間を省略)
 * @return UnicodeString
 */
UnicodeString fit_str(UnicodeString s, TCanvas *cv, int wd, bool omit_end = false);

/**
 * @brief //全角/半角変換
 * @param s 対象文字列
 * @param to_w 全角に変換
 * @return UnicodeString
 */
UnicodeString to_Full_or_Half(UnicodeString s, bool to_w);

/**
 * @brief 全角に変換
 * @param s 対象文字列
 * @return UnicodeString
 */
UnicodeString to_FullWidth(UnicodeString s);

/**
 * @brief 半角に変換
 * @param s 対象文字列
 * @return UnicodeString
 */
UnicodeString to_HalfWidth(UnicodeString s);

/**
 * @brief タブを空白に変換(等幅フォント用)
 * @param s 対象文字列
 * @param cv
 * @return UnicodeString
 */
UnicodeString cv_TabToSpc(UnicodeString s, TCanvas *cv);

/**
 * @brief 文字列は罫線行か？
 * @param s 対象文字列
 * @return int
 */
int is_RuledLine(UnicodeString s);

/**
 * @brief 罫線行文字列を取得
 * @param cnt ブロック数
 * @param ... ブロック幅
 * @return UnicodeString
 */
UnicodeString make_RuledLine(int cnt, ...);

/**
 * @brief アドレス文字列を取得
 * @param adr アドレス値
 * @param w 表示桁
 * @return UnicodeString
 */
UnicodeString get_AddrStr(__int64 adr, int w = 0);

/**
 * @brief アスペクト比文字列を取得
 * @param w 幅
 * @param h 高さ
 * @return UnicodeString
 */
UnicodeString get_AspectStr(int w, int h);

/**
 * @brief 文字セット名を取得
 * @param charset
 * @return UnicodeString
 */
UnicodeString get_NameOfCharSet(int charset);

/**
 * @brief 文字のウエイト名を取得
 * @param w
 * @return UnicodeString
 */
UnicodeString get_NameOfWeight(int w);

extern const UnicodeString CodePageList;	//!< コードページリスト
extern const UnicodeString CodePageListX;	//!< コードページリスト

/**
 * @brief コードページの名前を取得
 * @param code_page コードページ
 * @param long_sw 長い名前
 * @param has_bom BOMの有無
 * @return UnicodeString
 */
UnicodeString get_NameOfCodePage(int code_page, bool long_sw = false, bool has_bom = false);

/**
 * @brief 指定した名前のコードページを取得
 * @param code_name 名前
 * @return int
 */
int get_CodePageOfName(UnicodeString code_name);

/**
 * @brief Unicodeブロック名を取得
 * @param code 
 * @return UnicodeString 
 */
UnicodeString get_UnicodeBlockName(int code);

/**
 * @brief 文字列から正規表現パターンに基づいてユニコードポイントを抽出
 * @param s 
 * @param ptn 
 * @param dec_sw 
 * @return int 
 */
int extract_UnicodePoint(UnicodeString &s, UnicodeString ptn, bool dec_sw = false);

/**
 * @brief ユニコードポイントを文字に変換
 * @param uc ユニコードポイント
 * @return UnicodeString 
 */
UnicodeString UnicodePointToStr(int uc);

/**
 * @brief サロゲートペアをユニコードポイントに変換
 * @param c 
 * @return int ユニコードポイント
 */
int SurrogateToUnicodePoint(UnicodeString c);

/**
 * @brief 文字実体参照から数値文字参照へ
 * @param s 
 * @return UnicodeString 
 */
UnicodeString ChEntRef_to_NumChRef(UnicodeString s);

/**
 * @brief UTF8として適切か
 * @param bp チェック対象
 * @param size サイズ
 * @return int
 */
int check_UTF8(BYTE *bp, int size);

/**
 * @brief メモリストリームのコードページを取得
 * @param ms
 * @param has_bom
 * @return int コードページ(0:不明/ -1:バイナリ)
 */
int  get_MemoryCodePage(TMemoryStream *ms, bool *has_bom = NULL);

/**
 * @brief メモリストリームのコードページを判定し文字列として取得
 * @param ms メモリストリーム
 * @return UnicodeString
 */
UnicodeString get_MemoryStrins(TMemoryStream *ms);

/**
 * @brief サロゲートペア文字をチェック
 * @param s
 * @return UnicodeString 見つかった文字を空白区切りで連結してします。なければ EmptyStr
 */
UnicodeString check_Surrogates(UnicodeString s);

/**
 * @brief 環境依存文字(ローマ数字、囲み文字、単位記号、合成文字など)をチェック
 * @param s
 * @return UnicodeString 見つかった文字を空白区切りで連結して返します。なければ EmptyStr
 */
UnicodeString check_EnvDepandChars(UnicodeString s);

/**
 * @brief 標準化されたレーベンシュタイン距離を取得(最大比較文字数=256)
 * @param s1 対象文字列1
 * @param s2 対象文字列2
 * @param ig_case 大小文字を無視
 * @param ig_num 数字部分を無視
 * @param ig_fh 全角/半角を無視
 * @return int 距離(0～1000)
 */
int get_NrmLevenshteinDistance(UnicodeString s1, UnicodeString s2,
	bool ig_case = false, bool ig_num = false, bool ig_fh = false);

UnicodeString get_JsonValStr(TJSONValue *val);

/**
 * @brief JSON文字列の整形
 * @param val 
 * @param[out] lst 
 * @param lvl 
 */
void format_Json(TJSONValue *val, TStringList *lst, int lvl = 0);

UnicodeString decode_TxtVal(UnicodeString s, bool with_q = false);

UnicodeString conv_DfmText(UnicodeString s);

/**
 * @brief .dfm ファイル内の文字をデコード
 * @param[in,out] txt_lst 
 */
void conv_DfmText(TStringList *txt_lst);

/**
 * @brief インデックスからメニュー用アクセラレータ文字列を作成
 * @param idx インデックス番号
 * @param alp_sw A～Zを使用(false: 1～9,0 のみ)
 * @return UnicodeString 
 */
UnicodeString make_MenuAccStr(int idx, bool alp_sw = false);

/**
 * @brief 次のアルファベット文字列を取得
 * @param s 対象文字列 
 * @return UnicodeString 
 */
UnicodeString get_NextAlStr(UnicodeString s);

/**
 * @brief 文字列を TDateTime に変換
 * @param ts 対象文字列
 * @param sw_dt 数字を日付に変換
 * @return TDateTime 
 * @exception 変換できない場合例外を送出
 */
TDateTime str_to_DateTime(UnicodeString ts, bool sw_dt = false);
//---------------------------------------------------------------------------
#endif
