/**
 * @file file_filter.h
 * @brief �t�@�C���t�B���^����
 */
//---------------------------------------------------------------------------
#ifndef FileFilterH
#define FileFilterH

//---------------------------------------------------------------------------
UnicodeString GetFilterInfStr(UnicodeString filter, bool is_grep);
bool TestFilter(UnicodeString filter, bool is_grep);

//---------------------------------------------------------------------------
enum FilterOpt {foIsGrep, foExcludeTag};
typedef Set <FilterOpt, foIsGrep, foExcludeTag> FilterOption;

//---------------------------------------------------------------------------
/**
 * @brief �t�@�C���t�B���^����
 */
class FileFilter
{
private:
	bool GetBlockRange(UnicodeString tag);
	void SetHtmlComent();

public:
	UnicodeString FileName;
	UnicodeString Filter;
	TStringList *FileBuff;
	bool isGrep;
	bool excludeTag;

	int topLine;
	int endLine;
	int strIndex;
	int strLength;
	UnicodeString objType;
	UnicodeString propName;

	/** @brief �R���X�g���N�^ */
	FileFilter();

	~FileFilter();

	/**
	 * @brief ������
	 * @param fnam �t�@�C����
	 * @param fbuf �t�@�C���o�b�t�@
	 * @param filter �t�B���^
	 * @param opt �I�v�V����
	 * @return true 
	 * @return false 
	 */
	bool Initialize(UnicodeString fnam, TStringList *fbuf, UnicodeString filter, FilterOption opt);

	/**
	 * @brief �s���e�̎擾
	 * @param idx �C���f�b�N�X
	 * @param[out] r_idx �J�n�ʒu
	 * @param[out] r_len ����
	 * @param[out] lbuf �\���p�s���e
	 * @return UnicodeString �����ΏۂƂȂ镶����
	 */
	UnicodeString GetLinePart(int idx, int &r_idx, int &r_len, UnicodeString &lbuf);

	/**
	 * @brief �\���p�s���e���擾
	 * @param idx �C���f�b�N�X
	 * @return UnicodeString �\���p�s���e
	 */
	UnicodeString GetDispLine(int idx);

	/**
	 * @brief �����Ώۍs���H
	 * @param idx �C���f�b�N�X
	 * @return true �����Ώۍs
	 */
	bool IsValidLine(int idx);
};
//---------------------------------------------------------------------------
#endif
