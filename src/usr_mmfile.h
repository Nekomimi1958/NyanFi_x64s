/**
 * @file usr_mmfile.h
 * @brief メモリマップドファイル
 */
//---------------------------------------------------------------------------
#ifndef UsrMMFileH
#define UsrMMFileH

//---------------------------------------------------------------------------
#define MAX_MEMMAP_SIZE	1073741824L		//!< 最大マップサイズ		   (1GB)
#define FAILED_BUF_SIZE	8388608L		//!< マップ失敗時の読込サイズ (8MB)

//---------------------------------------------------------------------------
/**
 * @brief メモリマップドファイル
 */
class MemMapFile
{
private:
	HANDLE hFile;
	HANDLE hMap;
	BYTE *pPointer;		//マップ用ポインタ

	TBytes ByteBuff;	//通常読込用バッファ

	void Initialize();	//初期化

	BYTE Get(unsigned int Index)
	{
		if (isMaped) {
			if (!pPointer || Index>=FileSize) return 0;
			BYTE *p = pPointer;
			p += Index;
			return *p;
		}
		else
			return (Index<BuffSize)? ByteBuff[Index] : 0;
	}

public:
	__property BYTE Bytes[unsigned int Index] = {read=Get};

	__int64 FileSize;		//!< ファイルサイズ
	unsigned int BuffSize;	//!< バッファ(マップ)サイズ
	bool MapEnabled;		//!< マップ有効
	bool isMaped;			//!< マップされている
	UnicodeString ErrMsg;	//!< エラーメッセージ

	/* @brief コンストラクタ */
	MemMapFile();

	~MemMapFile();

	/**
	 * @brief 読み取り専用のメモリマップドファイルとして開く@n
			  開けない場合はメモリに通常読み込み
	 * 
	 * @param fnam ファイル名
	 * @param top_adr 先頭アドレス
	 * @param max_size 最大サイズ
	 * @return true 成功
	 */
	bool OpenRO(UnicodeString fnam, __int64 top_adr, unsigned int max_size);

	/** @brief 閉じて初期化 */
	void Close();
};
//---------------------------------------------------------------------------
#endif
