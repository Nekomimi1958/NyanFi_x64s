/**
 * @file usr_spbar.h
 * @brief ステータスバー上のプログレスバー
 */
//---------------------------------------------------------------------------
#ifndef UsrSttPrgBarH
#define UsrSttPrgBarH

//---------------------------------------------------------------------------
#include <Vcl.ComCtrls.hpp>

//---------------------------------------------------------------------------
/**
 * @brief 指定したステータスバーのパネル上にプログレスバーを表示
 */
class SttProgressBar
{
private:
	TStatusBar *SttBar;
	int PrgIndex;
	double BarRatio;

	void __fastcall PrgBoxPaint(TObject *Sender);
	void __fastcall ResetPos();

public:
	TPaintBox *PrgBox;
	int MsgIndex;		//!< メッセージを表示するパネルのインデックス

	TColor BgColor;
	TColor BarColor;

	SttProgressBar(TStatusBar *sp, int idx);
	~SttProgressBar();

	/**
	 * @brief プログレスバー表示開始
	 * @param s 表示メッセージ
	 */
	void __fastcall Begin(const _TCHAR *s = NULL);

	/**
	 * @brief プログレスバー表示終了
	 * @param s 表示メッセージ
	 * @param wait 隠すまでの待ち時間(ミリ秒)
	 */
	void __fastcall End(UnicodeString s = EmptyStr, int wait = 100);

	/**
	 * @brief 指定した進捗値に基づいてプログレスバーの表示を設定
	 * @param cnt 進捗値
	 * @param max_cnt 最大値
	 */
	void __fastcall SetPosI(int cnt, int max_cnt);
};
//---------------------------------------------------------------------------
#endif
