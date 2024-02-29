/**
 * @file MarkList.h
 * @brief コントロールの検索＆マーク/エラー枠
 */
//---------------------------------------------------------------------------
#ifndef MarkListH
#define MarkListH

//---------------------------------------------------------------------------
/**
 * @brief マークリスト (TList から継承)
 */
class MarkList : public TList
{
private:
	TShape * __fastcall Get(int Index)
	{
		return (TShape*)(TList::Get(Index));
	}
	void __fastcall Put(int Index, TShape *Item)
	{
		TList::Put(Index, Item);
	}

public:
	__fastcall MarkList(Classes::TComponent* AOwner);
	__fastcall ~MarkList();

	/** @brief マークをすべてクリア */
	void __fastcall ClearAll();

	/**
	 * @brief コントロールの検索@n
	 * キャプションに検索語が含まれるコントロールをマーク
	 * @param ctrl 対象コントロール
	 * @param wd 検索語
	 * @return int マッチ数
	 */
	int __fastcall SearchControl(TWinControl *ctrl, UnicodeString wd);

	/** @brief 検索マークを表示 */
	void __fastcall ShowMark();

	/**
	 * @brief エラー枠を表示
	 * @param Owner 
	 * @param cp 対象コントロール 
	 * @param sw_show 表示 
	 */
	void __fastcall SetErrFrame(TForm *Owner, TWinControl *cp, bool sw_show);

	TForm *MarkOwner;
	TColor MarkColor;

	__property TShape * Items[int Index] = {read=Get, write=Put};
};
//---------------------------------------------------------------------------
#endif
