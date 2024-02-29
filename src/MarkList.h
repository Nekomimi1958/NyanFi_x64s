/**
 * @file MarkList.h
 * @brief �R���g���[���̌������}�[�N/�G���[�g
 */
//---------------------------------------------------------------------------
#ifndef MarkListH
#define MarkListH

//---------------------------------------------------------------------------
/**
 * @brief �}�[�N���X�g (TList ����p��)
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

	/** @brief �}�[�N�����ׂăN���A */
	void __fastcall ClearAll();

	/**
	 * @brief �R���g���[���̌���@n
	 * �L���v�V�����Ɍ����ꂪ�܂܂��R���g���[�����}�[�N
	 * @param ctrl �ΏۃR���g���[��
	 * @param wd ������
	 * @return int �}�b�`��
	 */
	int __fastcall SearchControl(TWinControl *ctrl, UnicodeString wd);

	/** @brief �����}�[�N��\�� */
	void __fastcall ShowMark();

	/**
	 * @brief �G���[�g��\��
	 * @param Owner 
	 * @param cp �ΏۃR���g���[�� 
	 * @param sw_show �\�� 
	 */
	void __fastcall SetErrFrame(TForm *Owner, TWinControl *cp, bool sw_show);

	TForm *MarkOwner;
	TColor MarkColor;

	__property TShape * Items[int Index] = {read=Get, write=Put};
};
//---------------------------------------------------------------------------
#endif
