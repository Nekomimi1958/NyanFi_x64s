/**
 * @file usr_key.h
 * @brief �L�[�{�[�h���͊֘A�̊֐�
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
 * @brief �L�[���X�g�̍쐬
 * @param[out] lst �L�[���X�g
 */
void make_KeyList(TStringList *lst);

void assign_KeyList(TComboBox *cp, bool ins_empty = false, bool keep_item = false);

/**
 * @brief �w��L�[��������Ă��邩�H
 * @param key ���z�L�[�R�[�h
 */
bool is_KeyDown(WORD key);

/**
 * @brief �_�C�A���O�L�[���H
 * @param Key ���z�L�[�R�[�h
 */
bool is_DialogKey(WORD Key);

/**
 * @brief 0�`9�L�[���H
 * @param keystr �L�[������
 */
bool is_Num0to9(UnicodeString keystr);

/**
 * @brief WPARAM ����V�t�g��Ԃ��擾
 * @param prm
 * @return int
 */
int  get_shift_from_wparam(WPARAM prm);

/**
 * @brief ���{��L�[�{�[�h���H
 */
bool is_JpKeybd();

/**
 * @brief �L�[�E�}�E�X�o�b�t�@���N���A
 * @param key_only �L�[�o�b�t�@�̂݃N���A
 */
void ClearKeyBuff(bool key_only = false);

/**
 * @brief �R���g���[���ŃL�[������
 * @param cp �ΏۃR���g���[��
 * @param key ���z�L�[�R�[�h
 */
void perform_Key(TControl *cp, int key);

/**
 * @brief �R���g���[����ENTER�L�[������
 * @param cp �ΏۃR���g���[��
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
	Application->ProcessMessages();		//�I�v����
	return (HIBYTE(::GetAsyncKeyState(VK_ESCAPE)) != 0);
}
//---------------------------------------------------------------------------
#endif
