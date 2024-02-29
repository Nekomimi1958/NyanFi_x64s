/**
 * @file usr_key.h
 * @brief キーボード入力関連の関数
 */
//---------------------------------------------------------------------------
#ifndef UsrKeyH
#define UsrKeyH

//---------------------------------------------------------------------------
#define ESC_INTERVAL	256

#define REPEAT_WAIT		50

extern UnicodeString KeyStr_Shift;
extern UnicodeString KeyStr_Ctrl;
extern UnicodeString KeyStr_Alt;
extern int KeyboardMode;

/**
 * @brief キーリストの作成
 * @param[out] lst キーリスト
 */
void make_KeyList(TStringList *lst);

void assign_KeyList(TComboBox *cp, bool ins_empty = false, bool keep_item = false);

/**
 * @brief 指定キーが押されているか？
 * @param key 仮想キーコード
 */
bool is_KeyDown(WORD key);

/**
 * @brief ダイアログキーか？
 * @param Key 仮想キーコード
 */
bool is_DialogKey(WORD Key);

/**
 * @brief 0～9キーか？
 * @param keystr キー文字列
 */
bool is_Num0to9(UnicodeString keystr);

/**
 * @brief WPARAM からシフト状態を取得
 * @param prm
 * @return int
 */
int  get_shift_from_wparam(WPARAM prm);

/**
 * @brief 日本語キーボードか？
 */
bool is_JpKeybd();

/**
 * @brief キー・マウスバッファをクリア
 * @param key_only キーバッファのみクリア
 */
void ClearKeyBuff(bool key_only = false);

/**
 * @brief コントロールでキーを押す
 * @param cp 対象コントロール
 * @param key 仮想キーコード
 */
void perform_Key(TControl *cp, int key);

/**
 * @brief コントロールでENTERキーを押す
 * @param cp 対象コントロール
 */
void perform_Key_RETURN(TControl *cp);

TShiftState   get_Shift();
UnicodeString get_ShiftStr(TShiftState Shift);
UnicodeString get_KeyStr(WORD Key);
UnicodeString get_KeyStr(WORD Key, TShiftState Shift);
UnicodeString get_AlNumChar(WORD Key);

UnicodeString WaitForKey();

//---------------------------------------------------------------------------
inline bool has_KeyDownMsg()
{
	MSG msg;
	return ::PeekMessage(&msg, NULL, WM_KEYDOWN, WM_KEYDOWN, PM_NOREMOVE);
}
//---------------------------------------------------------------------------
inline bool is_KeyPress_ESC()
{
	if (!Application->Active) return false;
	Application->ProcessMessages();		//！要注意
	return (HIBYTE(::GetAsyncKeyState(VK_ESCAPE)) != 0);
}
//---------------------------------------------------------------------------
#endif
