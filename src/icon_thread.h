/**
 * @file icon_thread.h
 * @brief アイコン取得スレッド
 */
//---------------------------------------------------------------------------
#ifndef TGetIconThreadH
#define TGetIconThreadH

//---------------------------------------------------------------------------
#include <System.Classes.hpp>

//---------------------------------------------------------------------------
/**
 * @brief アイコン取得スレッド
 * 
 * CachedIcoList にファイル名が追加されると、そのアンコンを取得してキャッシュします(Objects に設定)。
 * @attention CachedIcoList を操作する際は IconRWLock でロックしてください。
 */
class TGetIconThread : public TThread
{
private:
	void __fastcall IconNotify();
	void __fastcall Execute();

public:
	HWND CallbackWnd;	//!< 通知先ウィンドウのハンドル

	/**
	 * @brief コンストラクタ
	 * @param CreateSuspended 
	 */
	__fastcall TGetIconThread(bool CreateSuspended);
};
//---------------------------------------------------------------------------
#endif
