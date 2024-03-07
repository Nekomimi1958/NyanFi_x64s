/**
 * @file usr_str.h
 * @brief �����񑀍�p�̔ėp�֐�
 */
//---------------------------------------------------------------------------
#ifndef UsrStrH
#define UsrStrH

//---------------------------------------------------------------------------
#include <System.JSON.hpp>

//---------------------------------------------------------------------------
extern bool DebugOut;	//!< �f�o�b�O�����񑗏o(�B���ݒ�)

/**
 * @brief �f�o�b�O�����񑗏o
 * @details DebugOut=true �̏ꍇ�A�f�o�b�O������𑗏o���܂�(OutputDebugString)�B
 * @param s ������
 */
void OutDebugStr(UnicodeString s);

//---------------------------------------------------------------------------
extern const _TCHAR *null_TCHAR;	//!< �󕶎���ւ̃|�C���^

//---------------------------------------------------------------------------
int __fastcall comp_NaturalOrder(TStringList *List, int Index1, int Index2);	//!< ���R��
int __fastcall comp_AscendOrder(TStringList *List, int Index1, int Index2);		//!< ����
int __fastcall comp_DescendOrder(TStringList *List, int Index1, int Index2);	//!< �~��
int __fastcall comp_ObjectsOrder(TStringList *List, int Index1, int Index2);	//!< Objects ����

//---------------------------------------------------------------------------
#define TXLIMIT_MARK "\x03\x03\x03"	//!< �s�������}�[�N

extern int  USR_CsvCol;				//!< �\�[�g�Ώۗ�
extern int  USR_CsvSortMode;		//!< �\�[�g���[�h(1:����/ -1�~��)
extern bool USR_CsvTopIsHdr;		//!< �擪�s�͍��ږ�

/**
 * @brief ������𐔒l�Ƃ��Ĕ�r
 * @param s1 ��r�Ώە�����1
 * @param s2 ��r�Ώە�����2
 * @retval >0 s1>s2
 * @retval <0 s1<s2
 * @retval 0 s1==s2
 */
int comp_NumStr(UnicodeString s1, UnicodeString s2);

/**
 * @brief TStringList.CustomSort �p�̔�r�֐�: CSV���R����
 * @details �Ώۂ�CSV���X�g�Ƃ݂Ȃ��A���R�����Ŕ�r���܂��B@n
 * ���l�Ƃ��Ĕ�r�ł��Ȃ���Ε����񏇁A�����Ȃ�΍s�ԍ���((int)Objects)�ɂȂ�܂��B@n
 * ��r�́AUSR_CsvCol�AUSR_CsvSortMode�AUSR_CsvTopIsHdr �Ɋ�Â��čs���܂��B
 * @sa USR_CsvCol
 * @sa USR_CsvSortMode
 * @sa USR_CsvTopIsHdr
 */
int __fastcall comp_CsvNaturalOrder(TStringList *List, int Index1, int Index2);

/**
 * @brief TStringList.CustomSort �p�̔�r�֐�: TSV���R����
 * @details �Ώۂ�TSV���X�g�Ƃ݂Ȃ��A���R�����Ŕ�r���܂��B@n
 * ���l�Ƃ��Ĕ�r�ł��Ȃ���Ε����񏇁A�����Ȃ�΍s�ԍ���((int)Objects)�ɂȂ�܂��B@n
 * ��r�́AUSR_CsvCol�AUSR_CsvSortMode�AUSR_CsvTopIsHdr �Ɋ�Â��čs���܂��B
 * @sa USR_CsvCol
 * @sa USR_CsvSortMode
 * @sa USR_CsvTopIsHdr
 */
int __fastcall comp_TsvNaturalOrder(TStringList *List, int Index1, int Index2);

/** @brief TStringList.CustomSort �p�̔�r�֐�: TSV������ */
int __fastcall comp_TsvTextOrder(TStringList *List, int Index1, int Index2);

//---------------------------------------------------------------------------
/**
 * @brief �w��Z�p���[�^�̑O�̕�������擾
 * @details * �w�肵���Z�p���[�^������̑O�ɂ��镶������擾���܂��B@n
 * �Z�p���[�^��������Ȃ��ꍇ�́A����������̂܂ܕԂ��܂��B
 * @param s �Ώە�����
 * @param sp �Z�p���[�^������
 * @return UnicodeString
 */
UnicodeString get_tkn(UnicodeString s, UnicodeString sp);

/**
 * @brief �w��Z�p���[�^�̌�̕�������擾
 * @details �w�肵���Z�p���[�^������̌�ɂ��镶������擾���܂��B@n
 * �Z�p���[�^��������Ȃ��ꍇ�́AEmptyStr ��Ԃ��܂��B
 * @param s �Ώە�����
 * @param sp �Z�p���[�^������
 * @return UnicodeString
 */
UnicodeString get_tkn_r(UnicodeString s, UnicodeString sp);

/**
 * @brief �w��Z�p���[�^�Ԃ̕�������擾
 * @details �w�肵��2�̃Z�p���[�^������̊Ԃɂ��镶������擾���܂��B@n
 * �Z�p���[�^2��������Ȃ��ꍇ�́A�Z�p���[�^1�ȍ~�̕������Ԃ��܂��B
 * @param s �Ώە�����
 * @param sp1 �Z�p���[�^������1
 * @param sp2 �Z�p���[�^������2
 * @return UnicodeString
 */
UnicodeString get_tkn_m(UnicodeString s, UnicodeString sp1, UnicodeString sp2);

/**
 * @brief �^�u�����̑O�ɂ��镶������擾
 * @details �^�u�����̑O�ɂ��镶������擾���܂��B�^�u�������Ȃ��ꍇ�́A����������̂܂ܕԂ��܂��B
 * @param s �Ώە�����
 * @return UnicodeString
 */
UnicodeString get_pre_tab(UnicodeString s);

/**
 * @brief �^�u�����̌�ɂ��镶������擾
 * @details �^�u�����̌�ɂ��镶������擾���܂��B�^�u�������Ȃ��ꍇ�́AEmptyStr ��Ԃ��܂��B
 * @param s �Ώە�����
 * @return UnicodeString
 */
UnicodeString get_post_tab(UnicodeString s);

/**
 * @brief �����s�������1�s�ڂ̓��e���擾
 * @param s �Ώە�����
 * @return UnicodeString
 */
UnicodeString get_first_line(UnicodeString s);

/**
 * @brief �����񒆂ɂ��銇�ʓ� (�`) �̕�������擾
 * @param s �Ώە�����
 * @return UnicodeString
 */
UnicodeString get_in_paren(UnicodeString s);

/**
 * @brief �����񒆂ɂ��銇�ʓ� (�`) �̕�������擾
 * @details �����񒆂ɂ��銇�ʓ� (�`) �̕�������擾���܂��B��������� (�`) �̌㑱������ɂȂ�܂��B
 * @param s �Ώە�����
 * @return UnicodeString
 */
UnicodeString split_in_paren(UnicodeString &s);

/**
 * @brief �O��Ƀ^�u���܂܂Ȃ���������擾
 * @details �O��Ƀ^�u���܂܂Ȃ���������擾���܂��B�Ώۂ������s�̏ꍇ�A��łȂ��ŏ��̕������Ԃ��܂��B
 * @param s �Ώە�����
 * @param trim_sw �O��̋󔒂␧�䕶�����폜
 * @return UnicodeString
 */
UnicodeString get_norm_str(UnicodeString s, bool trim_sw = false);

/**
 * @brief �w��Z�p���[�^�O�̕�����𕪗����Ď擾
 * @details �w�肵���Z�p���[�^������̑O�ɂ��镶����𕪗����Ď擾���܂��B@n
 * ��������́A�Z�p���[�^������̌㑱������ɂȂ�܂��B@n
 * �Z�p���[�^��������Ȃ��ꍇ�́A����������̂܂ܕԂ��A��������͋�ɂȂ�܂��B
 * @param s �Ώە�����
 * @param sp �Z�p���[�^������
 * @return UnicodeString
 */
UnicodeString split_tkn(UnicodeString &s, UnicodeString sp);

/**
 * @brief �󔒋�؂�O�̕�����𕪗����Ď擾
 * @details �󔒋�؂�̑O�ɑO�ɂ��镶����𕪗����Ď擾���܂��B@n
 * �擪�����ɂ���󔒂́A��؂�ƌ��Ȃ���܂���B�Ⴆ�΁Asplit_tkn_spc("  abc def") �� "  abc" ��Ԃ��܂��B
 * @param s �Ώە�����
 * @return UnicodeString
 */
UnicodeString split_tkn_spc(UnicodeString &s);

/**
 * @brief �^�u�O�̕�����𕪗����Ď擾
 * @details �^�u�����̑O�ɂ��镶����𕪗����Ď擾���܂��B��������́A�^�u�̌㑱������ɂȂ�܂��B@n
 * �^�u���Ȃ��ꍇ�́A����������̂܂ܕԂ��A��������͋�ɂȂ�܂��B
 * @param s �Ώە�����
 * @return UnicodeString
 */
UnicodeString split_pre_tab(UnicodeString &s);

/**
 * @brief �����񂩂��������(^:�`:)�𕪗����Ď擾
 * @details �Ώە�����̐擪�ɂ����������(^:�`:)�𕪗����Ď擾���܂��B��������́A���������̌㑱������ɂȂ�܂��B
 * @param s �Ώە�����
 * @return UnicodeString
 */
UnicodeString split_dsc(UnicodeString &s);

/**
 * @brief �����񂩂�擪�����𕪗����Ď擾
 * @details ������̐擪�ɂ��镶���𕪗����Ď擾���܂��B��������́A2�����ڈȍ~�̕�����ɂȂ�܂��B
 * @param s �Ώە�����
 * @return UnicodeString
 */
UnicodeString split_top_ch(UnicodeString &s);

/**
 * @brief �����񂩂�擪�����𕪗����Ď擾
 * @details ������̐擪�ɂ��镶���𕪗����Ď擾���܂��B��������́A2�����ڈȍ~�̕�����ɂȂ�܂��B
 * @param s �Ώە�����
 * @return WideChar
 */
WideChar split_top_wch(UnicodeString &s);

/**
 * @brief �R�}���h���C�����p�����[�^�ɕ���
 * @details �Ώە�������R�}���h���C���Ƃ݂Ȃ��A�p�����[�^�̃��X�g���쐬���܂��B
 * @param s �Ώە�����
 * @param[out] lst �p�����[�^�̃��X�g
 * @return int
 */
int split_cmd_line(UnicodeString s, TStringList *lst);

/**
 * @brief �R�}���h���C������t�@�C�����𕪗�
 * @details �Ώە�������R�}���h���C���Ƃ݂Ȃ��A�擪�̃t�@�C���������𕪗����Ď擾���܂��B@n
 * ��������́A�t�@�C�����ȍ~�̃p�����[�^�����ɂȂ�܂��B
 * @param s �Ώە�����
 * @return UnicodeString
 */
UnicodeString split_file_param(UnicodeString &s);

/**
 * @brief ��������^�u�����ŕ������z��Ƃ��Ď擾
 * @param s �Ώە�����
 * @return TStringDynArray
 */
TStringDynArray split_strings_tab(UnicodeString s);

/**
 * @brief ��������Z�~�R�����ŕ������z��Ƃ��Ď擾
 * @param s �Ώە�����
 * @param del_empty EmptyStr�����O
 * @return TStringDynArray 
 */
TStringDynArray split_strings_semicolon(UnicodeString s, bool del_empty = false);

/**
 * @brief �����񂩂猟����������폜
 * @param s �Ώە�����
 * @param w ����������
 * @return true ������������폜����
 * @return false ���������񂪊܂܂�Ă��Ȃ�
 */
bool remove_text(UnicodeString &s, UnicodeString w);

/**
 * @brief ������̐擪�Ɍ��������񂪂�������폜(�召�����𖳎�)
 * @param s �Ώە�����
 * @param w ����������
 * @return true �擪�̌�����������폜����
 * @return false �擪�Ɍ��������񂪂Ȃ�
 */
bool remove_top_text(UnicodeString &s, UnicodeString w);

/**
 * @brief ������̐擪�Ɍ��������񂪂�������폜(�召���������)
 * @param s �Ώە�����
 * @param w ����������
 * @return true �擪�̌�����������폜����
 * @return false �擪�Ɍ��������񂪂Ȃ�
 */
bool remove_top_s(UnicodeString &s, UnicodeString w);

/**
 * @brief ������̐擪�� @ ����������폜
 * @param s �Ώە�����
 * @return true �擪�� @ ���폜����
 * @return false �擪�� @ ���Ȃ�
 */
bool remove_top_AT(UnicodeString &s);

/**
 * @brief ������̐擪�� $ ����������폜
 * @param s �Ώە�����
 * @return true �擪�� $ ���폜����
 * @return false �擪�� $ ���Ȃ�
 */
bool remove_top_Dollar(UnicodeString &s);

/**
 * @brief ������̖����Ɍ��������񂪂�������폜(�召�����𖳎�)
 * @param s �Ώە�����
 * @param w ����������
 * @return true �����̌�����������폜����
 * @return false �����Ɍ��������񂪂Ȃ�
 */
bool remove_end_text(UnicodeString &s, UnicodeString w);

/**
 * @brief ������̖����Ɍ��������񂪂�������폜(�召���������)
 * @param s �Ώە�����
 * @param w ����������
 * @return true �����̌�����������폜����
 * @return false �����Ɍ��������񂪂Ȃ�
 */
bool remove_end_s(UnicodeString &s, UnicodeString w);

/**
 * @brief ������̖�����1�����폜
 * @param s �Ώە�����
 */
void delete_end(UnicodeString &s);

/**
 * @brief �擪��1���������O������������擾
 * @param s �Ώە�����
 * @return UnicodeString
 */
UnicodeString exclude_top(UnicodeString s);

/**
 * @brief �擪�Ɩ����̕��������O������������擾
 * @param s �Ώە�����
 * @return UnicodeString
 */
UnicodeString exclude_top_end(UnicodeString s);

/**
 * @brief �S�p�󔒂��l�������g���~���O
 * @param s �Ώە�����
 * @return UnicodeString
 */
UnicodeString trim_ex(UnicodeString s);

/**
 * @brief ^ �ɂ��擪�̘A���폜����������u��
 * @param s �Ώە�����
 * @param ptn �p�^�[��
 * @param rep �u��������
 * @param opt �I�v�V����
 * @return UnicodeString 
 */
UnicodeString replace_regex_2(UnicodeString s, UnicodeString ptn, UnicodeString rep, TRegExOptions opt);

/**
 * @brief //���X�g(���������� [TAB] �u��������)�ɂ��������ĕ������u��
 * @param s �Ώە�����
 * @param lst ���X�g
 * @return UnicodeString 
 */
UnicodeString replace_str_by_list(UnicodeString s, TStringList *lst);

/**
 * @brief ; ��؂�ŕ������ǉ�
 *
 * �Ώە����񂪋�łȂ��A�Z�~�R�����ŋ�؂��ĕ������ǉ����܂��B
 *
 * @param s �Ώە�����
 * @param t �ǉ�������
 */
void cat_str_semicolon(UnicodeString &s, UnicodeString t);

/**
 * @brief �����񂪎w�蒷�ɂȂ�܂Ő擪�ɋ󔒂�}��
 * @param s �Ώە�����
 * @param len ������̒���
 * @return UnicodeString
 */
UnicodeString ins_spc_length(UnicodeString s, int len);

/**
 * @brief �����񂪋�Ȃ�f�t�H���g��������擾
 * @param s �Ώە�����
 * @param def �f�t�H���g������
 * @return UnicodeString 
 */
UnicodeString def_if_empty(UnicodeString s, UnicodeString def);

/**
 * @brief �����񂪋�łȂ��Ȃ��؂蕶�����ǉ�
 * @param s �Ώە�����
 * @param sep ��؂蕶����
 */
void cat_separator(UnicodeString &s, UnicodeString sep);

/**
 * @brief �����񂪋�łȂ��Ȃ��؂蕶�����}�����āA�w�蕶�����ǉ�
 * @param s �Ώە�����
 * @param sep ��؂蕶����
 * @param s2 �ǉ�������
 */
void ins_sep_cat(UnicodeString &s, UnicodeString sep, UnicodeString s2);

/**
 * @brief ������� NativeInt �l�ɕϊ�
 * @param s �Ώە�����
 * @return NativeInt
 */
NativeInt str_to_NativeInt(UnicodeString s);

/**
 * @brief �����񂩂琮���l�𒊏o
 * @param s �Ώە�����
 * @return int
 * @exception ���s�����ꍇ�͗�O�𑗏o
 */
int extract_int(UnicodeString s);

/**
 * @brief �����񂩂琮���l�𒊏o
 * @details �����񂩂琮���l�𒊏o���܂��B�L���Ȓl���擾�ł��Ȃ��ꍇ�́A�f�t�H���g�l��Ԃ��܂��B
 * @param s �Ώە�����
 * @param def �f�t�H���g�l
 * @return int
 */
int extract_int_def(UnicodeString s, int def = 0);

/**
 * @brief ������̐擪���琔�l�����̕�������擾
 * @details ������̐擪���琔�l�����̕�������擾���܂��B�J���}�͖����A+/-�A�R���}�ɑΉ����Ă��܂��B
 * @param s �Ώە�����
 * @return UnicodeString
 */
UnicodeString extract_top_num_str(UnicodeString s);

/**
 * @brief long double �l�𕶎���ɕϊ�
 * @param v ���l
 * @param f_w �������̌���
 * @return UnicodeString
 */
UnicodeString ldouble_to_str(long double v, int f_w = 3);

/**
 * @brief �T�C�Y�̐��l�𕶎���ɕϊ�(TB�܂�)
 * @param sz �T�C�Y
 * @param dg ����
 * @return UnicodeString
 */
UnicodeString get_size_str_T(__int64 sz, int dg);

/**
 * @brief �T�C�Y�̐��l�𕶎���ɕϊ�(GB�܂�)
 * @param sz �T�C�Y
 * @param wd ���w��
 * @param dg ��������
 * @return UnicodeString
 */
UnicodeString get_size_str_G(__int64 sz, int wd = 10, int dg = 1);

/**
 * @brief �T�C�Y�̐��l�𕶎���ɕϊ�(GB�܂�)
 * @param sz �T�C�Y
 * @param wd ���w��
 * @param dg ��������
 * @param fmt_mode �\�����[�h(0:GB/MB/�o�C�g  1:GB/MB/KB/�o�C�g  2:GB/MB/KB);
 * @return UnicodeString
 */
UnicodeString get_size_str_G(__int64 sz, int wd, int dg, int fmt_mode);

UnicodeString get_size_str_B(__int64 sz, int wd = 14);
UnicodeString get_size_str_C(int sz);
UnicodeString get_size_str_K(SIZE_T sz);

/**
 * @brief RRGGBB�`���̕������ TColor �ɕϊ�
 * @param s �Ώە�����
 * @return TColor
 */
TColor xRRGGBB_to_col(UnicodeString s);

/**
 * @brief TColor �l��RRGGBB�`���̕�����ɕϊ�
 * @param col
 * @return UnicodeString
 */
UnicodeString col_to_xRRGGBB(TColor col);

/**
 * @brief �w�蕶����̈ʒu���擾(�召�����𖳎�)
 * @param wd ����������
 * @param s �Ώە�����
 * @return int �����C���f�b�N�X(1�x�[�X�A������Ȃ��ꍇ�� 0)
 */
int pos_i(UnicodeString wd, UnicodeString s);

/**
 * @brief �w�蕶���񂪍Ō�Ɍ����ʒu���擾(�召���������)
 * @param wd ����������
 * @param s �Ώە�����
 * @return int �����C���f�b�N�X(1�x�[�X�A������Ȃ��ꍇ�� 0)
 */
int pos_r(UnicodeString wd, UnicodeString s);

/**
 * @brief �w�蕶���񂪍Ō�Ɍ����ʒu���擾(�召�����𖳎�)
 * @param wd ����������
 * @param s �Ώە�����
 * @return int �����C���f�b�N�X(1�x�[�X�A������Ȃ��ꍇ�� 0)
 */
int pos_r_i(UnicodeString wd, UnicodeString s);

/**
 * @brief ���p���O�ŁA�w�蕶���񂪍Ō�Ɍ����ʒu���擾(�召���������)
 * @param wd ����������
 * @param s �Ώە�����
 * @return int �����C���f�b�N�X(1�x�[�X�A������Ȃ��ꍇ�� 0)
 */
int pos_r_q(UnicodeString wd, UnicodeString s);
int pos_r_q_colon(UnicodeString s);

bool contains_upper(UnicodeString s);

/**
 * @brief ������Ɍ��������񂪊܂܂�Ă��邩�H
 * @details �Ώە�����Ɍ��������񂪊܂܂�Ă��邩�ǂ����𒲂ׂ܂��B@n
 * ����������ł́AAND(' ') / OR('|') �w�肪�\�ł��B
 * @param s �Ώە�����
 * @param kwd ����������
 * @param case_sw �召�������
 * @return true
 * @return false
 */
bool contains_word_and_or(UnicodeString s, UnicodeString kwd, bool case_sw = false);
bool contains_fuzzy_word(UnicodeString s, UnicodeString kwd, bool case_sw = false, UnicodeString sp = EmptyStr);

/**
 * @brief ���������� | ��؂胊�X�g�Ɋ܂܂�Ă��邩(�召�����𖳎�)?
 * @param lst | ��؂胊�X�g
 * @param wd ����������
 * @return true
 * @return false
 */
bool contained_wd_i(UnicodeString lst, UnicodeString wd);

/**
 * @brief �Ώە����� | ��؂胊�X�g�̌���܂�ł��邩(�召�����𖳎�)�H
 * @param s �Ώە�����
 * @param lst | ��؂胊�X�g
 * @return true
 * @return false
 */
bool contains_wd_i(UnicodeString s, UnicodeString lst);

/**
 * @brief | ��؂胊�X�g����w��C���f�b�N�X�̕�������擾(�召�����𖳎�)
 * @param lst | ��؂胊�X�g
 * @param idx �C���f�b�N�X(0�x�[�X)
 * @return UnicodeString
 */
UnicodeString get_word_i_idx(UnicodeString lst, int idx);

/**
 * @brief | ��؂胊�X�g���猟��������̃C���f�b�N�X���擾(�召�����𖳎�)
 * @param lst | ��؂胊�X�g
 * @param wd ����������
 * @return int �C���f�b�N�X(0�x�[�X�A������Ȃ��ꍇ�� -1)
 */
int idx_of_word_i(UnicodeString lst, UnicodeString wd);

/**
 * @brief ���������� | ��؂胊�X�g�ɂ��邩�H
 * @param w ����������
 * @param list | ��؂胊�X�g
 * @return true
 * @return false
 */
bool test_word_i(UnicodeString w, UnicodeString list);

/**
 * @brief ���C���h�J�[�h���܂ރp�^�[���ɂ�镶����}�b�`
 * @param ptn �p�^�[��
 * @param s �Ώە�����
 * @return true
 * @return false
 */
bool str_match(UnicodeString ptn, UnicodeString s);

/**
 * @brief ���������K�\���p�^�[�����H
 * @param ptn �p�^�[��
 * @return true
 * @return false
 */
bool chk_RegExPtn(UnicodeString ptn);

/**
 * @brief ; ��؂蕶���񂩂琳�K�\���p�^�[��(/�`/)�𒊏o
 * @param s �Ώە�����(; ��؂�)
 * @return UnicodeString
 */
UnicodeString extract_prm_RegExPtn(UnicodeString &s);

/**
 * @brief ������Ɏw�蕶����/�p�^�[�����܂܂�Ă��邩�H
 * @param ptn ������/�p�^�[��
 * @param s �Ώە�����
 * @return UnicodeString �}�b�`���������̕�����
 */
UnicodeString ptn_match_str(UnicodeString ptn, UnicodeString s);

/**
 * @brief �����񂪎w���/�p�^�[���Ŏn�܂��Ă��邩�H
 * @param ptn ������(/�`/ �Ȃ琳�K�\���p�^�[��)
 * @param s �Ώە�����
 * @return true
 * @return false
 */
bool starts_ptn(UnicodeString ptn, UnicodeString s);

/**
 * @brief �����܂������̂��߂̐��K�\���p�^�[�����擾
 * @param kwd �L�[���[�h
 * @param sep_sw \s,\\,/ ��؂���܂����Ȃ�
 * @return UnicodeString
 */
UnicodeString get_fuzzy_ptn(UnicodeString kwd, bool sep_sw = false);

/**
 * @brief �����ꃊ�X�g�쐬
 * @param wd �Ώە�����
 * @param[out] lst
 */
void get_find_wd_list(UnicodeString wd, TStringList *lst);

/**
 * @brief �����̕������ OR/AND ����
 * @param wd ������(�����̏ꍇ�͔��p�܂��͑S�p�󔒂ŋ�؂�)
 * @param s �Ώە�����
 * @param and_sw AND����
 * @param not_sw NOT����
 * @param case_sw �召���������
 * @param word_sw �P��P��
 * @return true 
 * @return false 
 */
bool find_mlt(UnicodeString wd, UnicodeString s,
		bool and_sw = false, bool not_sw = false, bool case_sw = false, bool word_sw = false);

/**
 * @brief �����̕�������������A�}�b�`������̃��X�g���擾����
 * @param wd ������ (�����̏ꍇ�͔��p�܂��͑S�p�󔒂ŋ�؂�)
 * @param s �Ώە�����
 * @param[out] lst �}�b�`������̃��X�g
 * @param case_sw �召���������
 * @return true 
 * @return false 
 */
bool find_mlt_str(UnicodeString wd, UnicodeString s, TStringList *lst, bool case_sw);

/**
 * @brief ������̍s�����擾
 * @param s �Ώە�����
 * @return int �s��
 */
int get_line_count(UnicodeString s);

/**
 * @brief TStringDynArray �ɕ������ǉ�
 * @param lst
 * @param s �ǉ�������
 * @param no_dupl �����̏ꍇ�͒ǉ����Ȃ�
 */
void add_dyn_array(TStringDynArray &lst, UnicodeString s, bool no_dupl = false);

/**
 * @brief TStringDynArray �̎w��C���f�b�N�X���ڂ��擾
 * @param items
 * @param idx �C���f�b�N�X
 * @return UnicodeString
 */
UnicodeString get_array_item(TStringDynArray items, int idx);

/**
 * @brief TStringDynArray �̑S�v�f���w���؂蕶�����p���Č���
 * @param lst
 * @param sep ��؂蕶����
 * @return UnicodeString
 */
UnicodeString join_dynarray(TStringDynArray lst, UnicodeString sep);

/**
 * @brief CSV������̍��ړ��e�� TStringDynArray �Ƃ��Ď擾
 * @param src �Ώە�����
 * @param size ���ڐ�
 * @param force_size ���ڐ��������I�ɐݒ�
 * @return TStringDynArray
 */
TStringDynArray get_csv_array(UnicodeString src, int size, bool force_size = false);

/**
 * @brief CSV������̍��ړ��e�� TStringDynArray �Ƃ��Ď擾(���p�����l��)
 * @param src �Ώە�����
 * @param size ���ڐ�
 * @param del_q ���p�����O��
 * @return TStringDynArray
 */
TStringDynArray get_csv_array_Q(UnicodeString src, int size, bool del_q = true);

/**
 * @brief CSV�����񂩂�w��C���f�b�N�X�̍��ڂ��擾
 * @param src �Ώە�����
 * @param idx �C���f�b�N�X
 * @return UnicodeString
 */
UnicodeString get_csv_item(UnicodeString src, int idx);

/**
 * @brief TSV�����񂩂�w��C���f�b�N�X�̍��ڂ��擾
 * @param src �Ώە�����
 * @param idx �C���f�b�N�X
 * @return UnicodeString
 */
UnicodeString get_tsv_item(UnicodeString src, int idx);

/**
 * @brief CSV���ڂ��쐬
 * @param s �Ώە�����
 * @return UnicodeString
 */
UnicodeString make_csv_str(UnicodeString s);

/**
 * @brief bool �l��CSV���ڂ��쐬
 * @param sw
 * @return UnicodeString
 */
UnicodeString make_csv_str(bool sw);

/**
 * @brief TStringDynArray ����CSV��������쐬
 * @param lst
 * @return UnicodeString
 */
UnicodeString make_csv_rec_str(TStringDynArray lst);
UnicodeString make_csv_rec_str(std::initializer_list<UnicodeString> lst);

/**
 * @brief CSV���X�g����A�w���C���f�b�N�X�̍��ڂ�����������Ɉ�v����s�C���f�b�N�X���擾
 * @param lst CSV���X�g
 * @param s ����������
 * @param p ��C���f�b�N�X
 * @return int
 */
int indexof_csv_list(TStringList *lst, UnicodeString s, int p);

/**
 * @brief CSV�̃��X�g���� p �Ԗڂ̍��ڂ� s �̃��R�[�h���擾
 * @param lst CSV���X�g
 * @param s ����������
 * @param p ��C���f�b�N�X
 * @param size ��T�C�Y
 * @return TStringDynArray
 */
TStringDynArray record_of_csv_list(TStringList *lst, UnicodeString s, int p, int size);

/**
 * @brief �G�X�P�[�v�V�[�P���X�����̕ϊ�
 * @param s �Ώە�����
 * @return UnicodeString
 */
UnicodeString conv_esc_char(UnicodeString s);

/**
 * @brief \\ �� / �ɒu��
 * @param s �Ώە�����
 * @return UnicodeString
 */
UnicodeString yen_to_slash(UnicodeString s);

/**
 * @brief / �� \\ �ɒu��
 * @param s �Ώە�����
 * @return UnicodeString
 */
UnicodeString slash_to_yen(UnicodeString s);

/**
 * @brief SHA-1 ��7���̒Z�k�`�ɕϊ�
 * @param s �Ώۃn�b�V��������
 * @return UnicodeString
 */
UnicodeString sha1_to_short(UnicodeString s);

/**
 * @brief ������� "1" ���H
 * @param s �Ώە�����
 * @return true
 * @return false
 */
bool equal_1(UnicodeString s);

/**
 * @brief ������� "0" ���H
 * @param s �Ώە�����
 * @return true
 * @return false
 */
bool equal_0(UnicodeString s);

/**
 * @brief ������� "ENTER" ���H
 * @param s �Ώە�����
 * @return true
 * @return false
 */
bool equal_ENTER(UnicodeString s);

/**
 * @brief ������� "ESC" ���H
 * @param s �Ώە�����
 * @return true
 * @return false
 */
bool equal_ESC(UnicodeString s);

/**
 * @brief ������� "TAB" ���H
 * @param s �Ώە�����
 * @return true
 * @return false
 */
bool equal_TAB(UnicodeString s);

/**
 * @brief ������� "DEL" ���H
 *
 * @param s �Ώە�����
 * @return true
 * @return false
 */
bool equal_DEL(UnicodeString s);

/**
 * @brief ������� "LEFT" ���H
 * @param s �Ώە�����
 * @return true
 * @return false
 */
bool equal_LEFT(UnicodeString s);

/**
 * @brief ������� "RIGHT" ���H
 * @param s �Ώە�����
 * @return true
 * @return false
 */
bool equal_RIGHT(UnicodeString s);

/**
 * @brief ������� "UP" ���H
 * @param s �Ώە�����
 * @return true
 * @return false
 */
bool equal_UP(UnicodeString s);

/**
 * @brief ������� "DOWN" ���H
 * @param s �Ώە�����
 * @return true
 * @return false
 */
bool equal_DOWN(UnicodeString s);

/**
 * @brief ������� "HOME" ���H
 * @param s �Ώە�����
 * @return true
 * @return false
 */
bool equal_HOME(UnicodeString s);

/**
 * @brief ������� "END" ���H
 * @param s �Ώە�����
 * @return true
 * @return false
 */
bool equal_END(UnicodeString s);

/**
 * @brief ������� "F1" ���H
 * @param s �Ώە�����
 * @return true
 * @return false
 */
bool equal_F1(UnicodeString s);

/**
 * @brief ������� "F5" ���H
 * @param s �Ώە�����
 * @return true
 * @return false
 */
bool equal_F5(UnicodeString s);

/**
 * @brief ������̓Z�p���[�^("-")���H
 * @param s �Ώە�����
 * @return true
 * @return false
 */
bool is_separator(UnicodeString s);

/**
 * @brief �p�������񂩁H
 * @param s �Ώە����� 
 * @return true 
 * @return false 
 */
bool is_alnum_str(UnicodeString s);

/**
 * @brief �p�P�ꂩ�H
 * @param s �Ώە�����
 * @param p �ʒu
 * @param len ����
 * @return true 
 * @return false 
 */
bool is_word(UnicodeString s, int p, int len);

/**
 * @brief ������̐擪���w�蕶�����X�g�̂����ꂩ�Ɉ�v���邩�H
 * @param lst �������X�g
 * @param s �Ώە�����
 * @return true
 * @return false
 */
bool starts_tchs(UnicodeString lst, UnicodeString s);

/**
 * @brief ������̖������w�蕶�����X�g�̂����ꂩ�Ɉ�v���邩�H
 * @param lst �������X�g
 * @param s �Ώە�����
 * @return true
 * @return false
 */
bool ends_tchs(UnicodeString lst, UnicodeString s);

/**
 * @brief ������ @ �Ŏn�܂��Ă��邩 ?
 * @param s �Ώە�����
 * @return true
 * @return false
 */
bool starts_AT(UnicodeString s);

/**
 * @brief ������ $ �Ŏn�܂��Ă��邩 ?
 * @param s �Ώە�����
 * @return true
 * @return false
 */
bool starts_Dollar(UnicodeString s);

/**
 * @brief ������̖����� \ ���H
 * @param s �Ώە�����
 * @return true
 * @return false
 */
bool ends_PathDlmtr(UnicodeString s);

/**
 * @brief ������� \ ���܂܂�Ă��邩�H
 * @param s �Ώە�����
 * @return true
 * @return false
 */
bool contains_PathDlmtr(UnicodeString s);

/**
 * @brief ������� / ���܂܂�Ă��邩�H
 * @param s �Ώە�����
 * @return true
 * @return false
 */
bool contains_Slash(UnicodeString s);

/**
 * @brief ������Ɋ܂܂�Ă��� \ �̌����擾
 * @param s �Ώە�����
 * @return int
 */
int  count_PathDlmtr(UnicodeString s);

/**
 * @brief ������͐��K�\��(/�`/)���H
 * @param s �Ώە�����
 * @return true
 * @return false
 */
bool is_regex_slash(UnicodeString s);

/**
 * @brief �����񂪈��p���ň͂܂�Ă��邩�H
 * @param s �Ώە�����
 * @return true
 * @return false
 */
bool is_quot(UnicodeString s);

/**
 * @brief �����񂪋󔒂��܂�ł�������p���ň͂�
 * @param s �Ώە�����
 * @return UnicodeString
 */
UnicodeString add_quot_if_spc(UnicodeString s);

/**
 * @brief ������̈��p�����O��
 * @param s �Ώە�����
 * @return UnicodeString
 */
UnicodeString exclude_quot(UnicodeString s);

/**
 * @brief TStringList Vlues[name] �̐����l���擾
 * @param lst �Ώۃ��X�g
 * @param name ���O
 * @param def �f�t�H���g�l 
 * @return int 
 */
int  get_ListIntVal(TStringList *lst, UnicodeString name, int def = 0);

/**
 * @brief TStringList Vlues[name] ���󂩁H
 * @param lst �Ώۃ��X�g
 * @param name ���O
 * @return true 
 * @return false 
 */
bool ListVal_is_empty(TStringList *lst, UnicodeString name);

/**
 * @brief TStringList Vlues[name]=="1"?
 * @param lst �Ώۃ��X�g
 * @param name ���O
 * @return true 
 * @return false 
 */
bool ListVal_equal_1(TStringList *lst, UnicodeString name);

/**
 * @brief ������𗚗��Ƃ��ďd���Ȃ��Ń��X�g�ǉ�
 * @param[in,out] lst ���X�g
 * @param s �ǉ�������
 */
void add_as_history(TStrings *lst, UnicodeString s);

/**
 * @brief m�b�����ԕ�����ɕϊ�
 * @param ms �~���b�l
 * @param cs 1/100�b��\��
 * @return UnicodeString
 */
UnicodeString __fastcall mSecToTStr(unsigned int ms, bool cs = true);

/**
 * @brief �p�����[�^������(S/M/H���܂�)��m�b�l�ɕϊ�
 * @param prm �p�����[�^������
 * @return int
 */
int param_to_mSec(UnicodeString prm);

/**
 * @brief ������̕\�������擾
 * @param cv �L�����o�X
 * @param s �Ώە�����
 * @param spc_sw ��/�S�p�󔒂̑�֕������l��
 * @return int �\����
 */
int get_TextWidth(TCanvas *cv, UnicodeString s, bool spc_sw = false);

int get_CharWidth(TCanvas *cv, int n, int mgn = 0);

/**
 * @brief TPanel ���ł̕����񕝂��擾
 * @param s �Ώە����� 
 * @param pp �p�l��
 * @param d2d_sw Direct2D �Ŏ擾
 * @return int 
 */
int get_WidthInPanel(UnicodeString s, TPanel *pp, bool d2d_sw = false);

/**
 * @brief ���p���Z�̕����񒷂��擾
 * @param s �Ώە�����
 * @return int
 */
int str_len_half(UnicodeString s);

/**
 * @brief �T���Q�[�g�y�A���l�����ĕ��������擾
 * @param s �Ώە�����
 * @return int
 */
int str_len_unicode(UnicodeString s);

/**
 * @brief ���p���Z�̍ő啝���X�V
 * @param[o] w �ő啝
 * @param s �Ώە�����
 */
void max_len_half(int &w, UnicodeString s);

/**
 * @brief �w�蕝(���p�P��)���ŕ����񂪉E�l�ɂȂ�悤�ɋ󔒂�}��
 * @param s �Ώە�����
 * @param wd ��
 * @param post_s �ǉ�������
 * @return UnicodeString
 */
UnicodeString align_r_str(UnicodeString s, int wd, UnicodeString post_s = EmptyStr);

/**
 * @brief �w�蕝(���p�P��)���ŕ����񂪍��l�ɂȂ�悤�ɋ󔒂�}��
 * @param s �Ώە�����
 * @param wd ��
 * @param post_s �ǉ�������
 * @return UnicodeString
 */
UnicodeString align_l_str(UnicodeString s, int wd, UnicodeString post_s = EmptyStr);

/**
 * @brief �����񂪎w�蕝�Ɏ��܂�悤�ɒ���
 * @param s �Ώە�����
 * @param cv 
 * @param wd ������
 * @param omit_end �������ȗ� (false: ���Ԃ��ȗ�)
 * @param spc_sw ��/�S�p�󔒂̑�֕������l��
 * @return UnicodeString 
 */
UnicodeString minimize_str(UnicodeString s, TCanvas *cv, int wd, bool omit_end = false, bool spc_sw = false);

/**
 * @brief �����񂪎w�蕝�ɂȂ�悤�ɏȗ�/�󔒒ǉ�
 * @param s �Ώە�����
 * @param cv
 * @param wd ������
 * @param omit_end �������ȗ�(false �̏ꍇ�͒��Ԃ��ȗ�)
 * @return UnicodeString
 */
UnicodeString fit_str(UnicodeString s, TCanvas *cv, int wd, bool omit_end = false);

/**
 * @brief //�S�p/���p�ϊ�
 * @param s �Ώە�����
 * @param to_w �S�p�ɕϊ�
 * @return UnicodeString
 */
UnicodeString to_Full_or_Half(UnicodeString s, bool to_w);

/**
 * @brief �S�p�ɕϊ�
 * @param s �Ώە�����
 * @return UnicodeString
 */
UnicodeString to_FullWidth(UnicodeString s);

/**
 * @brief ���p�ɕϊ�
 * @param s �Ώە�����
 * @return UnicodeString
 */
UnicodeString to_HalfWidth(UnicodeString s);

/**
 * @brief �^�u���󔒂ɕϊ�(�����t�H���g�p)
 * @param s �Ώە�����
 * @param cv
 * @return UnicodeString
 */
UnicodeString cv_TabToSpc(UnicodeString s, TCanvas *cv);

/**
 * @brief ������͌r���s���H
 * @param s �Ώە�����
 * @return int
 */
int is_RuledLine(UnicodeString s);

/**
 * @brief �r���s��������擾
 * @param cnt �u���b�N��
 * @param ... �u���b�N��
 * @return UnicodeString
 */
UnicodeString make_RuledLine(int cnt, ...);

/**
 * @brief �A�h���X��������擾
 * @param adr �A�h���X�l
 * @param w �\����
 * @return UnicodeString
 */
UnicodeString get_AddrStr(__int64 adr, int w = 0);

/**
 * @brief �A�X�y�N�g�䕶������擾
 * @param w ��
 * @param h ����
 * @return UnicodeString
 */
UnicodeString get_AspectStr(int w, int h);

/**
 * @brief �����Z�b�g�����擾
 * @param charset
 * @return UnicodeString
 */
UnicodeString get_NameOfCharSet(int charset);

/**
 * @brief �����̃E�G�C�g�����擾
 * @param w
 * @return UnicodeString
 */
UnicodeString get_NameOfWeight(int w);

extern const UnicodeString CodePageList;	//!< �R�[�h�y�[�W���X�g
extern const UnicodeString CodePageListX;	//!< �R�[�h�y�[�W���X�g

/**
 * @brief �R�[�h�y�[�W�̖��O���擾
 * @param code_page �R�[�h�y�[�W
 * @param long_sw �������O
 * @param has_bom BOM�̗L��
 * @return UnicodeString
 */
UnicodeString get_NameOfCodePage(int code_page, bool long_sw = false, bool has_bom = false);

/**
 * @brief �w�肵�����O�̃R�[�h�y�[�W���擾
 * @param code_name ���O
 * @return int
 */
int get_CodePageOfName(UnicodeString code_name);

/**
 * @brief Unicode�u���b�N�����擾
 * @param code 
 * @return UnicodeString 
 */
UnicodeString get_UnicodeBlockName(int code);

/**
 * @brief �����񂩂琳�K�\���p�^�[���Ɋ�Â��ă��j�R�[�h�|�C���g�𒊏o
 * @param s 
 * @param ptn 
 * @param dec_sw 
 * @return int 
 */
int extract_UnicodePoint(UnicodeString &s, UnicodeString ptn, bool dec_sw = false);

/**
 * @brief ���j�R�[�h�|�C���g�𕶎��ɕϊ�
 * @param uc ���j�R�[�h�|�C���g
 * @return UnicodeString 
 */
UnicodeString UnicodePointToStr(int uc);

/**
 * @brief �T���Q�[�g�y�A�����j�R�[�h�|�C���g�ɕϊ�
 * @param c 
 * @return int ���j�R�[�h�|�C���g
 */
int SurrogateToUnicodePoint(UnicodeString c);

/**
 * @brief �������̎Q�Ƃ��琔�l�����Q�Ƃ�
 * @param s 
 * @return UnicodeString 
 */
UnicodeString ChEntRef_to_NumChRef(UnicodeString s);

/**
 * @brief UTF8�Ƃ��ēK�؂�
 * @param bp �`�F�b�N�Ώ�
 * @param size �T�C�Y
 * @return int
 */
int check_UTF8(BYTE *bp, int size);

/**
 * @brief �������X�g���[���̃R�[�h�y�[�W���擾
 * @param ms
 * @param has_bom
 * @return int �R�[�h�y�[�W(0:�s��/ -1:�o�C�i��)
 */
int  get_MemoryCodePage(TMemoryStream *ms, bool *has_bom = NULL);

/**
 * @brief �������X�g���[���̃R�[�h�y�[�W�𔻒肵������Ƃ��Ď擾
 * @param ms �������X�g���[��
 * @return UnicodeString
 */
UnicodeString get_MemoryStrins(TMemoryStream *ms);

/**
 * @brief �T���Q�[�g�y�A�������`�F�b�N
 * @param s
 * @return UnicodeString ���������������󔒋�؂�ŘA�����Ă��܂��B�Ȃ���� EmptyStr
 */
UnicodeString check_Surrogates(UnicodeString s);

/**
 * @brief ���ˑ�����(���[�}�����A�͂ݕ����A�P�ʋL���A���������Ȃ�)���`�F�b�N
 * @param s
 * @return UnicodeString ���������������󔒋�؂�ŘA�����ĕԂ��܂��B�Ȃ���� EmptyStr
 */
UnicodeString check_EnvDepandChars(UnicodeString s);

/**
 * @brief �W�������ꂽ���[�x���V���^�C���������擾(�ő��r������=256)
 * @param s1 �Ώە�����1
 * @param s2 �Ώە�����2
 * @param ig_case �召�����𖳎�
 * @param ig_num ���������𖳎�
 * @param ig_fh �S�p/���p�𖳎�
 * @return int ����(0�`1000)
 */
int get_NrmLevenshteinDistance(UnicodeString s1, UnicodeString s2,
	bool ig_case = false, bool ig_num = false, bool ig_fh = false);

UnicodeString get_JsonValStr(TJSONValue *val);

/**
 * @brief JSON������̐��`
 * @param val 
 * @param[out] lst 
 * @param lvl 
 */
void format_Json(TJSONValue *val, TStringList *lst, int lvl = 0);

UnicodeString decode_TxtVal(UnicodeString s, bool with_q = false);

UnicodeString conv_DfmText(UnicodeString s);

/**
 * @brief .dfm �t�@�C�����̕������f�R�[�h
 * @param[in,out] txt_lst 
 */
void conv_DfmText(TStringList *txt_lst);

/**
 * @brief �C���f�b�N�X���烁�j���[�p�A�N�Z�����[�^��������쐬
 * @param idx �C���f�b�N�X�ԍ�
 * @param alp_sw A�`Z���g�p(false: 1�`9,0 �̂�)
 * @return UnicodeString 
 */
UnicodeString make_MenuAccStr(int idx, bool alp_sw = false);

/**
 * @brief ���̃A���t�@�x�b�g��������擾
 * @param s �Ώە����� 
 * @return UnicodeString 
 */
UnicodeString get_NextAlStr(UnicodeString s);

/**
 * @brief ������� TDateTime �ɕϊ�
 * @param ts �Ώە�����
 * @param sw_dt ��������t�ɕϊ�
 * @return TDateTime 
 * @exception �ϊ��ł��Ȃ��ꍇ��O�𑗏o
 */
TDateTime str_to_DateTime(UnicodeString ts, bool sw_dt = false);
//---------------------------------------------------------------------------
#endif
