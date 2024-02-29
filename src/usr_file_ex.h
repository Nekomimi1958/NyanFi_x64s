/**
 * @file usr_file_ex.h
 * @brief ファイル操作用の汎用関数
 */
//---------------------------------------------------------------------------
#ifndef UsrFileExH
#define UsrFileExH

//---------------------------------------------------------------------------
#include <winternl.h>

//---------------------------------------------------------------------------
/** パス付きファイル名のマッチパターン*/
#define PATH_MATCH_PTN	"^(([a-z]:)|(%\\w+%)|(\\\\\\\\[^\\\\]+))\\\\(.+?\\\\)*.+$"

//---------------------------------------------------------------------------
#define	FileRenameInformation (FILE_INFORMATION_CLASS)10

typedef struct _FILE_RENAME_INFORMATION {
	BOOLEAN ReplaceIfExists;
	HANDLE	RootDirectory;
	ULONG	FileNameLength;
	WCHAR	FileName[1];
} FILE_RENAME_INFORMATION, *PFILE_RENAME_INFORMATION;

typedef LONG (WINAPI *FUNC_NtSetInformationFile)(HANDLE, PIO_STATUS_BLOCK, PVOID, ULONG, FILE_INFORMATION_CLASS);

//---------------------------------------------------------------------------
extern UnicodeString ExePath;	//!< NyanFi.exe の場所

//---------------------------------------------------------------------------
int __fastcall FileComp_Base(TStringList *List, int Index1, int Index2);

/**
 * @brief 260文字以上のパス名に対応するためのファイル名変換
 * @details 指定ファイル名を、260文字以上のパス名に対応できる形式に変換します。
 * 末尾が空白の場合などにも対応できます。
 * @param fnam 対象ファイル名
 * @return UnicodeString
 */
UnicodeString cv_ex_filename(UnicodeString fnam);

/**
 * @brief 環境変数の変換
 * @param s 対象文字列
 * @return UnicodeString
 */
UnicodeString cv_env_var(UnicodeString s);

/**
 * @brief 環境変数を含む文字列を変換
 * @param s 対象文字列
 * @return UnicodeString
 */
UnicodeString cv_env_str(UnicodeString s);

/**
 * @brief 環境変数や書式文字列を含む文字列から実際のパス名を取得
 * @param pnam 対象文字列
 * @return UnicodeString
 */
UnicodeString get_actual_path(UnicodeString pnam);

/**
 * @brief パスが通っている場合、パス無しファイル名をパス付きに変換
 * @param fnam 対象ファイル名
 * @param sw_fmt 書式文字列を展開
 * @return UnicodeString
 */
UnicodeString get_actual_name(UnicodeString fnam, bool sw_fmt = false);

/**
 * @brief パスが通っている場合、ファイル名からパスと拡張子を取り除く
 * @param fnam 対象ファイル名
 * @return UnicodeString
 */
UnicodeString exclude_env_path(UnicodeString fnam);

/**
 * @brief 実行ファイルのディレクトリからの相対ファイル名に変換
 * @param fnam 対象ファイル名
 * @return UnicodeString
 */
UnicodeString to_relative_name(UnicodeString fnam);

/**
 * @brief 絶対パスに変換(ドライブ名を含む場合は正規化)
 * @param fnam 対象ファイル名
 * @param rnam 基準ディレクトリ名(EmptyStr: ExePath)
 * @return UnicodeString
 */
UnicodeString to_absolute_name(UnicodeString fnam, UnicodeString rnam = EmptyStr);

/**
 * @brief 代替データストリームを考慮したパス名の取得
 * @param fnam 対象ファイル名
 * @return UnicodeString パス名
 */
UnicodeString extract_file_path(UnicodeString fnam);

/**
 * @brief 同一ファイルか？
 * @param fnam1 ファイル名1
 * @param fnam2 ファイル名2
 * @param rnam 基準ディレクトリ名(EmptyStr: ExePath)
 * @return true
 * @return false
 */
bool is_same_file(UnicodeString fnam1, UnicodeString fnam2, UnicodeString rnam = EmptyStr);

/**
 * @brief 同一ディレクトリか？ (環境変数対応)
 * @param dir1 ディレクトリ名1
 * @param dir2 ディレクトリ名2
 * @return true
 * @return false
 */
bool is_same_dir(UnicodeString dir1, UnicodeString dir2);

/**
 * @brief パスリストにマッチするか？
 * @param dnam チェック対象
 * @param plist パスリスト(環境変数、%ExePath% 対応)
 * @param start_sw 前方一致(false:部分一致)
 * @return true
 * @return false
 */
bool match_path_list(UnicodeString dnam, UnicodeString plist, bool start_sw = false);

/**
 * @brief ルート名(ドライブ名またはUNCのコンピュータ名)を取得
 * @param pnam 対象パス名
 * @return UnicodeString
 */
UnicodeString get_root_name(UnicodeString pnam);

/**
 * @brief 実際の大小文字でファイル名を取得
 * @param fnam 対象ファイル名
 * @return UnicodeString
 */
UnicodeString get_case_name(UnicodeString fnam);

/**
 * @brief ルートディレクトリか？
 * @param dnam 対象パス名
 * @return true
 * @return false
 */
bool is_root_dir(UnicodeString dnam);

/**
 * @brief UNCパスのルートか？
 * @param dnam 対象パス名
 * @return true
 * @return false
 */
bool is_root_unc(UnicodeString dnam);

/**
 * @brief ディレクトリがルートの場合、末尾の \ を取り除く
 * @param dnam 対象パス名
 * @return UnicodeString
 */
UnicodeString exclede_delimiter_if_root(UnicodeString dnam);

/**
 * @brief ドライブ名(大文字、\付き)を取得
 * @param dnam 対象パス名
 * @return UnicodeString
 */
UnicodeString get_drive_str(UnicodeString dnam);

/**
 * @brief 有効なドライブか？
 * @param drv ドライブ名
 * @return true
 * @return false
 */
bool drive_exists(UnicodeString drv);

/**
 * @brief ドライブの種類を取得
 * @param dnam 対象パス名
 * @return UINT
 */
UINT get_drive_type(UnicodeString dnam);

/**
 * @brief クラスタサイズを取得
 * @param dnam 対象パス名
 * @return int
 */
int get_ClusterSize(UnicodeString dnam);

/**
 * @brief ファイルのベース名を取得
 * @param fnam 対象ファイル名
 * @return UnicodeString
 */
UnicodeString get_base_name(UnicodeString fnam);

/**
 * @brief 拡張子を取得
 * @Note  名前が . で始まる場合(ドットファイル)、その直後の部分は拡張子とみなされません。
 * @param fnam 対象ファイル名
 * @return UnicodeString
 */
UnicodeString get_extension(UnicodeString fnam);

/**
 * @brief 対象がファイルなら拡張子を取得
 * @param fnam 対象ファイル名
 * @return UnicodeString
 */
UnicodeString get_extension_if_file(UnicodeString fnam);

UnicodeString nrm_FileExt(UnicodeString fext);

/**
 * @brief 拡張子のチェック
 * @details 対象拡張子が、指定した拡張子リストに含まれているか調べます。@n
 * 拡張子リストは、. で区切られた拡張子の並びです(例: ".txt.html.md")。
 * @param fext 対象拡張子
 * @param list 拡張子リスト
 * @return true 含まれている
 * @return false 含まれていない
 */
bool test_FileExt(UnicodeString fext, UnicodeString list);

/**
 * @brief 拡張子のチェック(サイズ指定可能)
 * @details 対象拡張子が、指定した拡張子リストに含まれているか調べます。@n
 * 拡張子リストは、. で区切られた拡張子の並びです。@n
 * 拡張子の後に : で区切って制限サイズ(MB単位)を指定できます。その場合、ファイルサイズが制限サイズ未満だとマッチしません。@n
 * 例: ".exe:100.dll"
 * @param fext 対象拡張子
 * @param list 拡張子リスト
 * @param size ファイルサイズ
 * @return true 含まれている(制限サイズ以上)
 * @return false 含まれていない
 */
bool test_FileExtSize(UnicodeString fext, UnicodeString list, __int64 size);

/**
 * @brief ディレクトリ名の末尾に「\」を付加
 * @details 対象ディレクトリ名の末尾に区切り文字「\」を付加します。EmptyStr の場合は EmptyStr を返します。
 * @param dnam 対象ディレクトリ名
 * @return UnicodeString
 */
UnicodeString to_path_name(UnicodeString dnam);

/**
 * @brief ディレクトリ名(末尾の「\」無し)を取得
 * @param dnam 対象ディレクトリ名
 * @return UnicodeString
 */
UnicodeString get_dir_name(UnicodeString dnam);

/**
 * @brief 親ディレクトリを取得
 * @param dnam 対象ディレクトリ名
 * @return UnicodeString 
 */
UnicodeString get_parent_path(UnicodeString dnam);

/**
 * @brief 適切なFTPパスに変換
 * @param pnam 
 * @return UnicodeString 
 */
UnicodeString nrm_ftp_path(UnicodeString pnam);

/**
 * @brief 対象パス名を分解して TStringDynArray を作成
 * @param pnam 対象パス名
 * @param dlmt ディレクトリ区切り
 * @return TStringDynArray 
 */
TStringDynArray split_path(UnicodeString pnam, UnicodeString dlmt);

/**
 * @brief 対象パス名を分解して TStringDynArray を作成
 * @param pnam 対象パス名
 * @return TStringDynArray 
 */
TStringDynArray split_path(UnicodeString pnam);

/**
 * @brief "UNCパス:ユーザ名" からユーザ名を分離
 * @param dnam パス名
 * @return UnicodeString
 */
UnicodeString split_user_name(UnicodeString &dnam);

/**
 * @brief コンピュータ名か？
 * @param pnam 対象パス名
 * @return true
 * @return false
 */
bool is_computer_name(UnicodeString pnam);

/**
 * @brief ディレクトリがアクセス可能か？
 * @param dnam 対象パス名
 * @return true
 * @return false
 */
bool is_dir_accessible(UnicodeString dnam);

/**
 * @brief ドライブがアクセス可能か？
 * @param dnam ドライブ名から始まるパス
 * @return true
 * @return false
 */
bool is_drive_accessible(UnicodeString dnam);

/**
 * @brief ドライブがライトプロテクトされているか？
 * @param dnam ドライブ名から始まるパス
 * @return true
 * @return false
 */
bool is_drive_protected(UnicodeString dnam);

/**
 * @brief NTFS圧縮属性の設定
 * @param fnam 対象ファイル名
 * @param sw 圧縮
 * @return true
 * @return false
 */
bool set_CompressAttr(UnicodeString fnam, bool sw);

/**
 * @brief ファイルの属性を取得
 * @param fnam 対象ファイル名
 * @return int 属性値(TSearchRec.Attr と同じ)
 */
int  file_GetAttr(UnicodeString fnam);

/**
 * @brief ファイルの属性を設定
 * @param fnam 対象ファイル名
 * @param attr 属性値(TSearchRec.Attr と同じ)
 * @return true 成功
 * @return false 失敗
 */
bool file_SetAttr(UnicodeString fnam, int attr);

/**
 * @brief ディレクトリの属性をコピー
 * @param src_nam コピー元ディレクトリ名
 * @param dst_nam コピー先ディレクトリ名
 * @param remove_ro 読込専用属性を解除
 * @return true 成功
 * @return false 失敗
 */
bool dir_CopyAttr(UnicodeString src_nam, UnicodeString dst_nam, bool remove_ro = false);

/**
 * @brief ファイルの読み出し専用属性を解除
 * @param fnam 対象ファイル名
 * @return true 成功
 * @return false 失敗
 */
bool set_FileWritable(UnicodeString fnam);

/**
 * @brief リパースポイント?
 * @param fnam 対象ファイル名
 * @return true
 * @return false
 */
bool is_SymLink(UnicodeString fnam);

/**
 * @brief リンクカウントを取得
 * @param fnam 対象ファイル名
 * @return int リンクカウント(2以上ならハードリンク)
 */
int  get_HardLinkCount(UnicodeString fnam);

/**
 * @brief ファイルの同一性チェック
 * @param fnam1 対象ファイル名1
 * @param fnam2 対象ファイル名2
 * @return true
 * @return false
 */
bool is_IdenticalFile(UnicodeString fnam1, UnicodeString fnam2);

/**
 * @brief ファイルの存在チェック
 * @param fnam 対象ファイル名
 * @return true 存在する
 * @return false 存在しない
 */
bool file_exists(UnicodeString fnam);

/**
 * @brief ファイルの存在チェック
 * @details ファイルの存在をチェックします。対象がディレクトリだった場合は成立しません。
 * @param fnam 対象ファイル名
 * @return true ファイルとして存在する
 * @return false ファイルとして存在しない
 */
bool file_exists_x(UnicodeString fnam);

/**
 * @brief ファイルの存在チェック
 * @details ファイルの存在をチェックします。ファイル名が"名前,インデックス"という形式だった場合、, 以降を除いてチェックします。
 * @param fnam 対象ファイル名
 * @return true
 * @return false
 */
bool file_exists_ico(UnicodeString fnam);

/**
 * @brief ファイル(ワイルドカード可)の存在チェック
 * @details ファイル(ワイルドカード可)の存在チェックを行います。fnm には、最初にマッチしたファイル名が返ります。
 * @param[in,out] fnam ファイル名(ワイルドカード可)
 * @return true
 * @return false
 */
bool file_exists_wc(UnicodeString &fnam);

/**
 * @brief ディレクトリの存在チェック
 * @param dnam 対象ディレクトリ名
 * @return true
 * @return false
 */
bool dir_exists(UnicodeString dnam);

/**
 * @brief 世界協定時刻をローカルの TDateTime に変換
 * @param utc 世界協定時刻
 * @return TDateTime ローカル時刻
 */
TDateTime utc_to_DateTime(FILETIME *utc);

/**
 * @brief ファイルのタイムスタンプを TDateTime 型で取得
 * @param fnam 対象ファイル名
 * @return TDateTime タイムスタンプ(更新日時)
 */
TDateTime get_file_age(UnicodeString fnam);

/**
 * @brief ファイルサイズを取得
 * @param fnam ファイル名
 * @return __int64 サイズ
 */
__int64 get_file_size(UnicodeString fnam);

/**
 * @brief 圧縮サイズを取得
 * @param fnam ファイル名
 * @return __int64 圧縮サイズ
 */
__int64 get_comp_size(UnicodeString fnam);

/**
 * @brief 代替データストリーム付きパス名か？
 * @param fnam ファイル名
 * @return true
 * @return false
 */
bool is_ADS_name(UnicodeString fnam);

/**
 * @brief 代替データストリームの区切り位置を取得
 * @param fnam ファイル名
 * @return int 区切りの位置
 */
int  pos_ADS_delimiter(UnicodeString fnam);

/**
 * @brief 代替データストリーム付きパス名を分解
 * @details 代替データストリーム付きパス名を、ファイル名とストリーム名に分解します。
 * ファイル名部分が戻り値になり、ストリーム名は fnam に設定されます。
 * @param[in,out] fnam ファイル名
 * @return UnicodeString ファイル名
 */
UnicodeString split_ADS_name(UnicodeString &fnam);

/**
 * @brief 代替データストリームの削除
 * @param fnam ファイル名
 * @param force 読込専用でも強制的に変更
 * @param mask マスク
 * @param[out] lst 削除したストリーム名のリスト
 * @retval 1 成功
 * @retval 0 失敗(lst->Text にエラーメッセージ)
 * @retval -1 ADSなし
 */
int delete_ADS(UnicodeString fnam, bool force = false, UnicodeString mask = "*", TStringList *lst = NULL);

/**
 * @brief 代替データストリーム名の変更
 * @param fnam 元ファイル名:ストリーム名
 * @param new_name :新ストリーム名
 * @return true 成功
 * @return false 失敗
 */
bool rename_ADS(UnicodeString fnam, UnicodeString new_name);

/**
 * @brief 指定ディレクトリが存在しない場合に作成
 * @param dnam ディレクトリ名
 * @return UnicodeString ディレクトリ名(作成できなかった場合 EmptyStr)
 */
UnicodeString chk_cre_dir(UnicodeString dnam);

/**
 * @brief 空ディレクトリか？
 * @param dnam 対象ディレクトリ名
 * @param no_file ファイルが含まれていない
 * @return true
 * @return false
 */
bool is_EmptyDir(UnicodeString dnam, bool no_file = false);

/**
 * @brief 利用可能なドライブのリストを取得
 * @param[out] lst ドライブのリスト(ドライブ文字:\)
 * @return int
 */
int get_available_drive_list(TStringList *lst);

/**
 * @brief ファイルの属性文字列を取得
 * @param atr 属性値
 * @return UnicodeString 属性文字列(RHSAC 含まない属性は _)
 */
UnicodeString get_file_attr_str(int atr);

/**
 * @brief 指定ディレクトリ下でマスクに該当する最初のファイルを取得
 * @param pnam 対象ディレクトリ名
 * @param mask マスク
 * @param subSW サブディレクトリもチェック
 * @return UnicodeString ファイル名
 */
UnicodeString find_FirstFile(UnicodeString pnam, UnicodeString mask, bool subSW = false);

/**
 * @brief 指定ディレクトリ下のマスクに該当する全ファイルを取得
 * @param pnam 対象ディレクトリ名
 * @param mask マスク
 * @param[out] lst ファイル名リスト
 * @param subSW サブディレクトリも検索
 */
void get_files(UnicodeString pnam, UnicodeString mask, TStrings *lst, bool subSW = false);

/**
 * @brief 指定ディレクトリ下のマスクに該当する全ファイルのリストを追加取得
 * @param pnam 対象ディレクトリ名
 * @param mask マスク
 * @param[out] lst ファイル名リスト
 * @param subSW サブディレクトリも検索
 * @param subn サブディレクトリの階層の深さ
 * @param skip_dir 除外Dirマスク(;で区切り複数可)
 * @param inc_hide 隠し属性も検索
 * @param inc_sys システム属性も検索
 * @return int ファイル数(空ディレクトリは除く)
 */
int  get_all_files_ex(UnicodeString pnam, UnicodeString mask, TStrings *lst,
	bool sub_sw = false, int sub_n = 99, UnicodeString skip_dir = EmptyStr,
	bool inc_hide = true, bool inc_sys = true);

/**
 * @brief 指定ディレクトリ下の全ディレクトリを取得
 * @param pnam 対象ディレクトリ名
 * @param[out] lst ディレクトリ名リスト
 * @param subSW サブディレクトリも検索
 */
void get_dirs(UnicodeString pnam, TStrings *lst, bool subSW = true);

/**
 * @brief 指定ファイルにタイムスタンプ(更新日時)を設定
 * @param fnam 対象ファイル名
 * @param dt タイムスタンプ(更新日時)
 * @param force 読込専用でも強制的に変更
 * @return true 成功
 * @return false 失敗
 */
bool set_file_age(UnicodeString fnam, TDateTime dt, bool force = false);

/**
 * @brief 空のファイルを作成
 * @param fnam 作成ファイル名
 * @return true 成功
 * @return false 失敗
 */
bool create_EmptyFile(UnicodeString fnam);

/**
 * @brief ディレクトリの作成
 * @param dnam 作成ディレクトリ名
 * @return true 成功
 * @return false 失敗
 */
bool create_Dir(UnicodeString dnam);

/**
 * @brief ディレクトリの作成(複数階層可)
 * @param dnam 作成ディレクトリ名
 * @return true 成功
 * @return false 失敗
 */
bool create_ForceDirs(UnicodeString dnam);

/**
 * @brief ディレクトリの削除
 * @param dnam 削除ディレクトリ名
 * @param force 強制的に削除
 * @return true 成功
 * @return false 失敗
 */
bool delete_Dir(UnicodeString dnam, bool force = false);

/**
 * @brief サブディレクトリを含めたディレクトリの削除
 * @param pnam 削除ディレクトリ名
 * @return true 成功
 * @return false 失敗
 */
bool delete_Dirs(UnicodeString pnam);

/**
 * @brief ファイルの移動
 * @param old_nam 移動元ファイル名
 * @param new_nam 移動先ファイル名
 * @return true 成功
 * @return false 失敗
 */
bool move_File(UnicodeString old_nam, UnicodeString new_nam);

/**
 * @brief ファイルのコピー
 * @param src_nam コピー元ファイル名
 * @param dst_nam コピー先ファイル名
 * @return true 成功
 * @return false 失敗
 */
bool copy_File(UnicodeString src_nam, UnicodeString dst_nam);

/**
 * @brief ファイル名前の変更
 * @param old_nam 元のファイル名
 * @param new_nam 変更後のファイル名
 * @return true 成功
 * @return false 失敗
 */
bool rename_File(UnicodeString old_nam, UnicodeString new_nam);

/**
 * @brief パス名の変更
 * @param old_nam 元のパス名
 * @param new_nam 変更後のパス名
 * @return true 成功
 * @return false 失敗
 */
bool rename_Path(UnicodeString old_nam, UnicodeString new_nam);

//---------------------------------------------------------------------------
#ifndef REPARSE_DATA_BUFFER
typedef struct _REPARSE_DATA_BUFFER {
	ULONG  ReparseTag;
	USHORT ReparseDataLength;
	USHORT Reserved;

	union {
		struct {
		  USHORT SubstituteNameOffset;
		  USHORT SubstituteNameLength;
		  USHORT PrintNameOffset;
		  USHORT PrintNameLength;
		  ULONG  Flags;
		  WCHAR  PathBuffer[1];
		} SymbolicLinkReparseBuffer;

		struct {
		  USHORT SubstituteNameOffset;
		  USHORT SubstituteNameLength;
		  USHORT PrintNameOffset;
		  USHORT PrintNameLength;
		  WCHAR  PathBuffer[1];
		} MountPointReparseBuffer;

		struct {
		  UCHAR DataBuffer[1];
		} GenericReparseBuffer;
	};
} REPARSE_DATA_BUFFER, *PREPARSE_DATA_BUFFER;
#endif

//---------------------------------------------------------------------------
/**
 * @brief ジャンクションの作成
 * @param pnam
 * @param target
 * @return true 成功
 * @return false 失敗
 */
bool cre_Junction(UnicodeString pnam, UnicodeString target);

//---------------------------------------------------------------------------
BYTE   fsRead_byte(TFileStream *fs);
int    fsRead_int2(TFileStream *fs, bool be_sw = false);
int    fsRead_int3(TFileStream *fs, bool be_sw = false);
int    fsRead_int4(TFileStream *fs, bool be_sw = false);
double fsRead_double(TFileStream *fs);
UnicodeString fsRead_char(TFileStream *fs, int size);
UnicodeString fsRead_comment_utf8(TFileStream *fs);

/**
 * @brief ファイルの現在位置に指定文字列があるか？@n
          あれば直後位置へ、無ければ現在位置のまま
 * @param fs ファイルストリーム
 * @param s 文字列
 * @return true
 * @return false
 */
bool fsRead_check_char(TFileStream *fs, const char *s);

//---------------------------------------------------------------------------
inline UnicodeString warn_filename_RLO(UnicodeString fnam)
{
	return ReplaceStr(ExtractFileName(fnam), L"\u202e", "<RLO>");
}
//---------------------------------------------------------------------------
inline UnicodeString warn_pathname_RLO(UnicodeString pnam)
{
	return ReplaceStr(pnam, L"\u202e", "<RLO>");
}
//---------------------------------------------------------------------------
#endif
