/**
 * @file usr_migemo.h
 * @brief Migemo ����
 */
//---------------------------------------------------------------------------
#ifndef UsrMigemoH
#define UsrMigemoH

//---------------------------------------------------------------------------
typedef struct _migemo migemo;
typedef migemo*			(WINAPI *FUNC_migemo_open)(const char*);
typedef void			(WINAPI *FUNC_migemo_close)(migemo*);
typedef unsigned char*	(WINAPI *FUNC_migemo_query)(migemo*, const unsigned char*);
typedef void 			(WINAPI *FUNC_migemo_release)(migemo*, unsigned char*);

//---------------------------------------------------------------------------
/**
 * @brief Migemo ����
 */
class MigemoUnit
{
private:
	HINSTANCE hMigemo;
	migemo *MigemoObj;

	FUNC_migemo_open		f_migemo_open;
	FUNC_migemo_close		f_migemo_close;
	FUNC_migemo_query		f_migemo_query;
	FUNC_migemo_release		f_migemo_release;

public:
	bool Available;
	bool DictReady;
	UnicodeString PathName;
	UnicodeString FileName;
	int  MinLength;

	/**
	 * @brief �R���X�g���N�^
	 * @param dnam Migemo�f�B���N�g��
	 */
	MigemoUnit(UnicodeString dnam);

	~MigemoUnit();

	UnicodeString Query(UnicodeString qstr);

	/**
	 * @brief ���K�\���p�^�[�����擾
	 * 
	 * @param sw Migemo�𗘗p
	 * @param w ������
	 * @param minlen �����J�n������
	 * @return UnicodeString ���K�\���p�^�[��
	 */
	UnicodeString GetRegExPtn(bool sw, UnicodeString w, int minlen = 0);
};

//---------------------------------------------------------------------------
#endif
