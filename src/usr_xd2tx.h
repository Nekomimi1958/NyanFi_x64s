/**
 * @file usr_xd2tx.h
 * @brief xdoc2txt
 */
//---------------------------------------------------------------------------
#ifndef UsrXDoc2TxtH
#define UsrXDoc2TxtH

//---------------------------------------------------------------------------
typedef int (*FUNC_ExtractText)(BSTR, bool, BSTR*);		//�Icdecl �Ăяo��

//---------------------------------------------------------------------------
//�I.html .eml �͏��O
#define FEXT_XD2T_OPN	_T(".sxw.sxc.sxi.sxd.odt.ods.odp.odg")
#define FEXT_XD2T_MSO	_T(".docx.docm.xlsx.xlsm.pptx.pptm.doc.xls.ppt")
#define FEXT_XD2T_ETC	_T(".jaw.jtw.jbw.juw.jfw.jvw.jtd.jtt.oas.oa2.oa3.bun.wj2.wj3.wk3.wk4.123.pdf.mht")
#define FEXT_XD2T_PRP	FEXT_XD2T_MSO _T(".sxw.sxc.sxi.sxd.jtd.jtt")	//!< �v���p�e�B�擾�\
#define FEXT_XD2TX		FEXT_XD2T_OPN FEXT_XD2T_MSO FEXT_XD2T_ETC		//!< ���o�\

//---------------------------------------------------------------------------
extern bool xd2tx_Available;
extern UnicodeString xd2tx_FileName;

//---------------------------------------------------------------------------
/**
 * @brief ������
 * @return true xd2txlib.dll �����p�\
 */
bool xd2tx_Initialize();

/**
 * @brief �Ή��g���q���H
 * @param fext �g���q
 * @param inc_rtf .rtf .wri ���܂�
 */
bool xd2tx_TestExt(UnicodeString fext, bool inc_rtf = false);

/**
 * @brief �v���p�e�B�擾�\���H
 * @param fext �g���q
 */
bool xd2tx_PropExt(UnicodeString fext);

/**
 * @brief �e�L�X�g�̒��o
 * @param fnam �t�@�C����
 * @param[out] lst 
 * @param prop 
 * @return true ����
 * @return false ���s
 */
bool xd2tx_Extract(UnicodeString fnam, TStringList *lst, bool prop = false);

/**
 * @brief �v���p�e�B�擾
 * @param fnam �t�@�C����
 * @param[out] lst 
 * @return true ����
 * @return false ���s
 */
bool xd2tx_GetInfo(UnicodeString fnam, TStringList *lst);

//---------------------------------------------------------------------------
#endif
