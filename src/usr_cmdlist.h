/**
 * @file usr_cmdlist.h
 * @brief コマンド一覧
 */
//---------------------------------------------------------------------------
#ifndef UsrCmdListH
#define UsrCmdListH

//---------------------------------------------------------------------------
#include "usr_str.h"

//---------------------------------------------------------------------------
#define HASH_ALG_LIST	_T("MD5\nSHA1\nSHA256\nSHA384\nSHA512\nCRC32\n")

//---------------------------------------------------------------------------
extern UnicodeString ScrModeIdStr;

//---------------------------------------------------------------------------
/**
 * @brief コマンド一覧リストを設定
 * 
 * @param[out] c_list リスト(コマンド名=説明)
 * @param[out] s_list リスト(識別文字:コマンド名=説明)
 */
void set_CmdList(TStringList *c_list, TStringList *s_list);

/**
 * @brief コマンドのパラメータ一覧を取得
 * 
 * @param cmd コマンド
 * @param id_idx "FSVIL"モードのインデックス(0ベース)
 * @param[out] p_list パラメータ一覧
 * @param cp コンボボックス
 */
void get_PrmList(UnicodeString cmd, int id_idx, TStringList *p_list, TComboBox *cp = NULL);

/**
 * @brief ファイル/ディレクトリ参照が必要か？
 * 
 * @param cmd コマンド
 * @return true 必要
 */
bool need_RefDirFile(UnicodeString cmd);

/**
 * @brief コマンドパラメータから説明文字列を削除
 * @param cmd コマンド
 * @return UnicodeString 
 */
UnicodeString del_CmdDesc(UnicodeString cmd);

/**
 * @brief カーソルキーをコマンドに変換
 * @param key_str キー文字列
 * @return UnicodeString コマンド
 */
UnicodeString get_CsrKeyCmd(UnicodeString key_str);

//---------------------------------------------------------------------------
/** @brief コマンド部分を取得 */
inline UnicodeString get_CmdStr(UnicodeString s)
{
	return starts_AT(s)? s : get_tkn(s, '_');
}

/** @brief パラメータ部分を取得 */
inline UnicodeString get_PrmStr(UnicodeString s)
{
	return get_tkn_r(s, '_');
}
//---------------------------------------------------------------------------
#endif
