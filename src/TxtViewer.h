/**
 * @file TxtViewer.h
 * @brief �e�L�X�g�r���[�A
 */
//---------------------------------------------------------------------------
#ifndef TxtViewerH
#define TxtViewerH

//---------------------------------------------------------------------------
#include "usr_mmfile.h"
#include "Global.h"

//---------------------------------------------------------------------------
/** �����N�挟���̐��K�\�� */
#define LINK_MATCH_PTN	"(https?://[\\w/:%#$&?()~.=+-]+)|(file:///[^*?\"<>|)�j]+\\.[a-zA-Z0-9]+)|(mailto:[a-zA-Z0-9]+[\\w.-]*@[\\w.-]+)"

/** �P��}�b�`�p���K�\�� */
#define WORD_MATCH_PTN	LINK_MATCH_PTN "|\\w+|[��-�]+|[��-��]+|[�@-���[]+|[��-���`-�y�O-�X]+|[�-�]+|#[0-9a-fA-F]{3,6}"

#define MAX_BIN_HCH_X	67
#define MARK_WIDTH		8

#define MAX_EM_PTN		7	//!< �����\���p�^�[����

//---------------------------------------------------------------------------
/** @brief �\���s���e */
struct line_rec {
	int  LineNo;			//!< �s�ԍ�
	int  LineIdx;			//!< ���s�s���C���f�b�N�X
	bool hasCR;				//!< �s���ɉ��s�R�[�h����
	WideChar topQch;
	int  RemPos0;			//!< �R�����g�J�n�ʒu
	int  RemPos1;			//!< �R�����g�I���ʒu
	int  IndentN;			//!< �C���f���g�K�C�h��
	int  StickyIdx;			//!< Sticky�p�C���X�g�[��(�|1: ���ݒ�)
};

//---------------------------------------------------------------------------
/**
 * @brief �e�L�X�g�r���[�A
 */
class TTxtViewer
{
private:
	TPaintBox	*ViewBox;			//�r���[�A�`��pPaintBox
	TCanvas		*ViewCanvas;
	TScrollBar	*ScrBar;
	UsrScrollPanel *ScrPanel;
	TPaintBox	*RulerBox;			//���[��
	TStatusBar	*SttHeader;			//�X�e�[�^�X�w�b�_
	TPaintBox	*MarginBox;			//�E�]��

	bool isExtWnd;					//�O���E�B���h�E�ŕ\��

	UnicodeString EmPtn[MAX_EM_PTN];	//�����\���p�^�[��
	TColor EmFgC[MAX_EM_PTN];			//���������F
	TColor EmBgC[MAX_EM_PTN];			//�����w�i�F

	TPanel *ColorPanel;				//�J�[�\���ʒu�l�̃J���[�\��

	TPanel *StickyPanel;			//�֐��X�e�B�b�L�[
	TPaintBox *StickyBox;
	UnicodeString StickyStr;		//�X�e�B�b�L�[�\�����e
	int StickyLine;					//�X�e�B�b�L�[�s�ԍ�(1�x�[�X)
	int LastTopPos;

	UnicodeString FuncPtn;			//�֐��}�b�`�p�^�[��
	UnicodeString FuncBrkPtn;		//�֐��u���[�N�p�^�[��
	UnicodeString FuncNamPtn;		//�֐��������p�^�[��

	Graphics::TBitmap *ImgBuff;

	TPoint LastPos;
	int	 LastTop;
	bool LastSel;
	bool SelSkip;
	bool inh_Repaint;

	TFont *UseFont;					//�g�p�t�H���g
	UnicodeString useFontName;		//�g�p�t�H���g��
	int  useFontSize;				//�g�p�t�H���g�T�C�Y(���Z�b�g�l)

	int  FontHeight;				//�t�H���g��
	int  LineHeight;				//�s��
	int  HchWidth;					//���p��(px)
	int  TabWidth;					//�^�u��(px)
	int  CurHchX;					//�㉺�ړ�����X�ʒu(���p�P��)
	int  MaxHchX;					//X�ʒu�̍ő�l(���p�P��)
	int  LeftMargin;
	int  CurTop;					//�\���擪�s(1�x�[�X)
	int  CurBottom;					//�\���ŉ��s
	int  TopXpos;					//�s���̕\���J�n�ʒu
	int  TopMargin;					//�s���̗]��

	DynamicArray<int>  FixWdList;	//�Œ蒷�����X�g
	DynamicArray<bool> IsNumList;	//���ڂ����l��

	TStringList *RemLnList;			//�P�s�R�����g���ʕ�����
	TStringList *RemBgnList;		//�u���b�N�R�����g�J�n������
	TStringList *RemEndList;		//�u���b�N�R�����g�I��������

	UnicodeString QuotStr;			//������̈��p��
	bool useEsc;					//��������ŃG�X�P�[�v�V�[�P���X����

	UnicodeString ReservedPtn;		//�\���
	bool ReservedCase;				//�\���ő召���������

	UnicodeString SymbolChs;		//�V���{��
	UnicodeString NumericPtn;		//���l
	UnicodeString CharPtn;			//����

	UnicodeString UsrKeyword;		//���[�U��`�L�[���[�h
	bool   UsrKeywdCase;			//���[�U��`�L�[���[�h�ő召���������
	TColor UsrKeywdCol;				//���[�U��`�L�[���[�h�̕����F

	UnicodeString UsrKeyword2;		//���[�U��`�L�[���[�h
	bool   UsrKeywdCase2;			//���[�U��`�L�[���[�h�ő召���������
	TColor UsrKeywdCol2;			//���[�U��`�L�[���[�h�̕����F

	TStringList *PairPtnList;		//SearchPair �p�̊J�n/�I���s�p�^�[�����X�g

	TBytes FindByte0, FindByte1;	//�o�C�i��������
	TBytes FindMask;				//�o�C�i�������p�}�X�N

	bool alt_BackSlash;				//\ �� �_(U+2216)�ŕ\��

	line_rec BinLineRec;
	line_rec* __fastcall AddDispLine(UnicodeString s, int lno, int lidx = 0);
	void __fastcall ClearDispLine();

	void __fastcall AlphaBlendCsvCol(TCanvas *cv, int max_x, int y, int h);
	void __fastcall onRulerPaint(TObject *Sender);
	void __fastcall onStickyPaint(TObject *Sender);
	void __fastcall onStickyClick(TObject *Sender);
	void __fastcall PaintText();
	bool __fastcall SetToggleSw(bool &sw, UnicodeString prm);

	void __fastcall SetScrBar();

	UnicodeString __fastcall ArrayToTsv(TStringDynArray lst);
	void __fastcall FormatFixed(TStringList *txt_lst);

	TPoint __fastcall nrm_Pos(TPoint p);
	bool __fastcall has_CR(UnicodeString s);
	int  __fastcall add_CharWidth(WideChar c, int w);
	int  __fastcall get_StrWidth(UnicodeString s);
	int  __fastcall get_CurEndPos();
	void __fastcall adjust_PosX();
	void __fastcall to_Lead_if_Trail(bool sel = false);
	void __fastcall set_SelEnd();
	void __fastcall set_CurCsvCol();

	WideChar __fastcall get_CurChar();
	int  __fastcall cv_PosX_to_HchX(int px);
	void __fastcall TabTextOut(UnicodeString s, TCanvas *cv, int &x, int max_x);
	void __fastcall IniSelected(bool sel = false);
	void __fastcall SetPosFromPt(int x, int y);
	bool __fastcall PtInSelected(int x, int y);
	void __fastcall UpdatePos(bool up_pos = false, bool force = false);
	void __fastcall UpdateSticky();
	void __fastcall UpdateVisible();
	int  __fastcall get_MovePrm(UnicodeString prm);
	int  __fastcall to_Bytes(UnicodeString s, bool &case_sw, int code_page = 932);

	int  __fastcall GetComCmdIndex(UnicodeString cmd);

public:
	TForm *OwnerForm;

	MemMapFile	 *MMF;				//!< �������}�b�v�h�t�@�C��

	TStringList  *TxtBufList;		//!< ���e���X�g
	TStringList  *TxtBufList2;		//!< HTML��TEXT�ϊ���̓��e���X�g/ ���`��JSON
	TStringList  *DispLines;		//!< �\���s���X�g(�e�L�X�g�p)

	UnicodeString FileName;			//!< �t�@�C����
	UnicodeString OrgName;			//!< �ꎞ�𓀂��Ă���ꍇ�̌��t�@�C����
	file_rec     *FileRec;
	bool 		  HasBOM;			//!< BOM�t��
	UnicodeString LineBreakStr;		//!< ���s�R�[�h
	UnicodeString SttHdrInf;		//!< �t�@�C�����
	UnicodeString MarkListStr;		//!< �}�[�N���X�g

	bool isReady;
	bool isFitWin;					//!< �܂�Ԃ����E�B���h�E����
	bool isText;					//!< �e�L�X�g�\��
	bool isBinary;					//!< �o�C�i���\��
	bool isXDoc2Txt;				//!< xdoc2txt���g�p
	bool isHtm2Txt;					//!< HTML��TEXT�ϊ����[�h
	bool isFixedLen;				//!< �Œ蒷�\�����[�h
	bool isCSV;						//!< CSV(TSV���܂�)
	bool isTSV;
	bool isSelected;				//!< �t�@�C���I��
	bool ShowRuby;					//!< ���r�\��
	bool isAozora;					//!< �󕶌Ɍ`��
	bool isJsonFmt;					//!< ���`��JSON
	bool isLog;						//!< �^�X�N���O
	bool isClip;					//!< �N���b�v�{�[�h
	bool isIniFmt;					//!< INI�t�@�C���Ȃ�
	bool isAwstats;					//!< Awstats���O
	bool isNyanTxt;					//!< NyanFi�p�e�L�X�g
	bool isLimited;					//!< �T�C�Y�����L��
	bool isContinue;				//!< �Ōォ�瑱��
	bool isSelMode;					//!< �I�����[�h
	bool isBoxMode;					//!< ���`�I�����[�h
	bool ExtClicked;				//!< �e�L�X�g�O���N���b�N���ꂽ
	bool Selecting;					//!< �}�E�X�őI��
	bool PtInSelect;				//!< �I��͈͓����N���b�N����
	bool reqCurPos;					//!< �����Ƃ��Ƀt�@�C���[�̃J�[�\���ʒu��ݒ�

	int  TabLength;					//!< �^�u��
	int  LineCount;					//!< 1�y�[�W���̍s��(-1)
	int  MaxLine;					//!< �ő�s��
	int  MaxDispLine;				//!< �ő�\���s

	bool isTail;					//!< ������\��
	bool isReverse;					//!< �t��
	int  TailLine;					//!< �����s��

	//TopIsHeader �v���p�e�B
	bool FTopIsHeader;
	void __fastcall SetTopIsHeader(bool Value);
	/** @brief �擪�s��CSV���ږ� */
	__property bool TopIsHeader = {read = FTopIsHeader,  write = SetTopIsHeader};

	unsigned int BinarySize;		//!< �o�C�i���Ǎ��T�C�Y
	unsigned __int64 BinFileSize;	//!< �t�@�C���T�C�Y
	__int64 TopAddress;				//!< �擪�A�h���X

	TPoint CurPos;					//!< �J�[�\���ʒu(�����P�� 0�x�[�X)
	TPoint SelStart, SelEnd;		//!< �ʏ�I��͈�(�����P��)
	TPoint BoxStart, BoxEnd;		//!< ���`�I��͈�(���p�P��)

	TPoint PairPos1, PairPos2;		//!< �Ή����銇�ʂ̈ʒu
	bool PairChanged;

	int  MaxFoldWd;					//!< �ő�܂�Ԃ���
	int  CsvCol;					//!< CSV��(�Œ蒷�\�����[�h��)

	int  SortMode;					//!< �\�[�g���[�h(0:�Ȃ�/ 1:����/ -1:�~��)
	int  SortCol;					//!< �\�[�g��(�Œ蒷�\�����[�h��)

	UnicodeString JsonErrMsg;		//!< JSON��̓G���[

	UnicodeString FindWord;			//!< ����������
	UnicodeString RegExPtn;			//!< ���K�\���p�^�[��
	UnicodeString LastSelWord;		//!< �O�� FindSel�`�ŗp����������
	bool isCase;					//!< �召���������
	bool isRegEx;					//!< ���K�\��
	bool isWord;					//!< �P��P�ʂŌ���
	bool isMigemo;					//!< Migemo���[�h
	bool isBytes;					//!< �o�C�g�񌟍�
	int  BinCodePage;				//!< �R�[�h�y�[�W
	bool Highlight;					//!< �}�b�`�̋����\��
	bool LastFound;					//!< ���O�̌�������
	TPoint FoundPos;				//!< ���O�̃q�b�g�ʒu

	UnicodeString IncSeaWord;		//!< �C���N�������^���T�[�`���͌�
	bool isIncSea;					//!< �C���N�������^���T�[�`
	bool isIncMigemo;				//!< Migemo���[�h

	UnicodeString HeadlinePtn;		//!< ���o���̐��K�\��
	UnicodeString RubyPtn;			//!< ���r�̐��K�\��

	TStringList *ColBufList;
	TColor color_Cursor;			//!< ���C���J�[�\���̐F
	TColor color_selItem;			//!< �I�����ڂ̔w�i�F
	TColor color_fgSelItem;			//!< �I�����ڂ̕����F
	TColor color_Folder;			//!< �f�B���N�g���̕����F
	TColor color_Error;				//!< �G���[�̕����F
	TColor color_bgView;			//!< �e�L�X�g�r���[�A�̔w�i�F
	TColor color_fgView;			//!< �e�L�X�g�r���[�A�̕����F
	TColor color_Margin;			//!< �e�L�X�g�r���[�A�̗]����
	TColor color_bgLineNo;			//!< �e�L�X�g�r���[�A�̍s�ԍ��w�i�F
	TColor color_LineNo;			//!< �e�L�X�g�r���[�A�̍s�ԍ������F
	TColor color_Mark;				//!< �e�L�X�g�r���[�A�̃}�[�N
	TColor color_bgRuler;			//!< ���[���̔w�i�F
	TColor color_fgRuler;			//!< ���[���̖ڐ��F
	TColor color_bdrLine;			//!< �s�ԍ��̋��E��
	TColor color_Indent;			//!< �C���f���g�K�C�h
	TColor color_Indent2;			//!< �C���f���g�K�C�h(����)
	TColor color_bdrFold;			//!< �܂�Ԃ����E��
	TColor color_bdrFixed;			//!< �Œ蒷�\���̏c�r��
	TColor color_Comment;			//!< �R�����g�̕����F
	TColor color_Strings;			//!< ������̕����F
	TColor color_Reserved;			//!< �\���̕����F
	TColor color_Symbol;			//!< �V���{���̕����F
	TColor color_Numeric;			//!< ���l�̕����F
	TColor color_fgEmpBin1;			//!< �o�C�i�����������F1
	TColor color_fgEmpBin2;			//!< �o�C�i�����������F2
	TColor color_fgEmpBin3;			//!< �o�C�i�����������F3
	TColor color_Headline;			//!< ���o���̕����F
	TColor color_URL;				//!< URL�̕����F
	TColor color_LocalLink;			//!< ���[�J�t�@�C���ւ̃����N
	TColor color_fgEmp;				//!< ���������F
	TColor color_bgEmp;				//!< �����w�i�F
	TColor color_Ruby;				//!< ���r
	TColor color_TAB;				//!< �^�u�\���F
	TColor color_CR;				//!< ���s�\���F
	TColor color_HR;				//!< �r���̐F
	TColor color_Ctrl;				//!< �R���g���[���R�[�h
	TColor color_fgPair;			//!< �Ή����銇�ʂ̕����F

	/**
	 * @brief �R���X�g���N�^
	 * @param frm �t�H�[��
	 * @param viewbox �\���̈�
	 * @param scrbar �X�N���[���o�[
	 * @param sp �V���v���X�N���[���o�[
	 * @param stthdr ���w�b�_
	 * @param ruler ���[��
	 * @param mgn_box �E�]���p�l��
	 */
	TTxtViewer(TForm *frm, TPaintBox *viewbox, TScrollBar *scrbar, UsrScrollPanel *sp,
				TStatusBar *stthdr, TPaintBox *ruler, TPaintBox *mgn_box = NULL);
	~TTxtViewer();

	/** @brief �⏕��ʂ���� */
	bool __fastcall CloseAuxForm();

	void __fastcall Clear();

	/** @brief �z�F�̐ݒ� */
	void __fastcall SetColor(TStringList *lst);
	void __fastcall SetColor(UnicodeString prm = EmptyStr);

	/** @brief �I�v�V�����ݒ�ɔz�F�𔽉f */
	void __fastcall SetOptColor();

	/** @brief ���g���b�N�̐ݒ� */
	void __fastcall SetMetric(bool set_hi = false);

	/**
	 * @brief �֐��̃}�b�`�p�^�[�����擾
	 * @param[out] nam_ptn �֐����̋����p�^�[��
	 * @param[out] cap_str �ꗗ�p�L���v�V����
	 * @return UnicodeString 
	 */
	UnicodeString __fastcall GetFuncPtns(UnicodeString *nam_ptn = NULL, UnicodeString *cap_str = NULL);

	/**
	 * @brief ��ʂɍ��킹�čs���e��ݒ�
	 * @param lno �s�ԍ� (0: ���ݍs)
	 */
	void __fastcall UpdateScr(int lno = 1);

	/**
	 * @brief �e�L�X�g���e��ݒ�
	 * @param[in] lst �e�L�X�g���e
	 * @param lno �s�ԍ� (0:�������Q��)
	 * @param sort_mode �\�[�g���[�h (0:����/ 1:����/ -1:�~��)
	 */
	void __fastcall AssignText(TStrings *lst = NULL, int lno = 1, int sort_mode = 0);

	/**
	 * @brief �o�C�i���t�@�C����ǂݍ���œ��e��ݒ�
	 *
	 * @param top_adr �擪�A�h���X
	 * @param reload �ēǂݍ��� (false: ��������}�[�N�𕜌�)
	 * @param adr �ړ��A�h���X
	 * @return true
	 * @return false
	 */
	bool __fastcall AssignBin(__int64 top_adr = 0, bool reload = false, unsigned int adr = 0);

	/** @brief �ĕ`��v�� */
	void __fastcall Repaint(bool force = false);

	/**
	 * @brief ��ԕ\����ݒ�
	 * @param msg
	 */
	void __fastcall SetSttInf(UnicodeString msg = EmptyStr);

	/** @brief ���w�b�_�̕`�� */
	void __fastcall SttHeaderDrawPanel(TStatusBar *StatusBar, TStatusPanel *Panel, TRect Rect);

	void __fastcall onMouseDown(int x, int y);
	void __fastcall onMouseMove(int x, int y);
	void __fastcall onMouseUp();
	void __fastcall onDblClick();
	void __fastcall onRulerDblClick(TObject *Sender);

	void __fastcall CursorLeft(bool sel = false);
	void __fastcall CursorRight(bool sel = false, bool skip_end = false);
	void __fastcall CursorUp(bool sel = false, UnicodeString prm = EmptyStr);
	void __fastcall CursorDown(bool sel = false, UnicodeString prm = EmptyStr);
	void __fastcall MovePage(bool is_down, bool sel = false);

	/** @brief �X�N���[�����̕\������ */
	void __fastcall ScrollAdjust();

	/**
	 * @brief �X�N���[��
	 * @param is_down ������
	 * @param prm �p�����[�^
	 * @param move_csr �J�[�\�����ړ�
	 */
	void __fastcall MoveScroll(bool is_down, UnicodeString prm, bool move_csr = false);

	void __fastcall LineTop(bool sel = false);
	void __fastcall MoveLineTop(bool is_next, bool sel = false);
	void __fastcall LineEnd(bool sel = false);
	void __fastcall TextTop(bool sel = false);
	void __fastcall TextEnd(bool sel = false);

	/** @brief CSV��ʒu���猅��ݒ� (���R�[�h��1�s�ڂł̂ݗL��) */
	bool __fastcall set_PosFromCol(int col);

	void __fastcall WordLeft(bool sel = false);
	void __fastcall WordRight(bool sel = false);

	/**
	 * @brief �N���b�v�{�[�h�ɃR�s�[
	 * @param append �ǉ��R�s�[
	 */
	void __fastcall ClipCopy(bool append = false);

	/** @brief �w��s�̕\���s���R�[�h(line_rec)���擾 */
	line_rec* __fastcall get_LineRec(int idx);
	UnicodeString __fastcall get_DispLine(int idx, int b0 = 0, int b1 = 15);

	/**
	 * @brief �I�𕶎�����擾
	 * @param clr_sel �擾��A�I����Ԃ��N���A
	 * @return UnicodeString 
	 */
	UnicodeString __fastcall get_SelText(bool clr_sel = false);

	/** @brief �J�[�\���ʒu/�s����URL���擾 */
	UnicodeString __fastcall get_CurUrl();

	/**
	 * @brief �J�[�\���s�̕�������擾
	 * @param to_cr ���s�܂Ŏ擾
	 * @return UnicodeString 
	 */
	UnicodeString __fastcall get_CurLine(bool to_cr = false);

	/** @brief �J�[�\���s�̍s�ԍ����擾 */
	int __fastcall get_CurLineNo();

	/** @brief �J�[�\���ʒu�̐�΃A�h���X���擾 (�o�C�i��) */
	__int64 __fastcall get_CurAddrA();

	/** @brief �J�[�\���ʒu�̑��΃A�h���X���擾 (�o�C�i��) */
	unsigned int __fastcall get_CurAddrR();

	/** @brief �s������̃I�t�Z�b�g���擾 (�o�C�i��) */
	unsigned int __fastcall get_OfsR(int xp);

	/** @brief �J�[�\���ʒu�̍s(y)�E��(x)���擾 (�e�L�X�g) */
	TPoint __fastcall get_CurLinePos();

	/** @brief CSV���o�����X�g���擾 */
	TStringDynArray __fastcall GetCsvHdrList();

	/** @brief �S�đI�� */
	void __fastcall SelectAll();

	/**
	 * @brief �J�[�\���ʒu�̒P����擾/�I��
	 * @param ptn �}�b�`�p�^�[��
	 * @param[out] p_s �J�n�ʒu
	 * @param[out] p_e �I���ʒu
	 * @return UnicodeString 
	 */
	UnicodeString __fastcall GetCurWord(UnicodeString ptn = EmptyStr, int *p_s = NULL, int *p_e = NULL);

	/**
	 * @brief �J�[�\���ʒu�̒P���I��
	 * @param append �ǉ��I��
	 */
	void __fastcall SelCurWord(bool append = false);

	/** @brief ���s�P�ʂōs�S�̂�I�� */
	void __fastcall SelLine(bool cr = false);

	void __fastcall saveDef_CodePage(int code_page);
	int  __fastcall change_CodePage(UnicodeString prm);

	/** @brief �J�[�\���ʒu�̉摜�t�@�C�������擾 */
	UnicodeString __fastcall GetCurImgFile();

	/**
	 * @brief �����񌟍�
	 * @param is_down �������Ɍ���
	 * @param kwd ������
	 * @param opt �����I�v�V����
	 * @return true 
	 * @return false 
	 */
	bool __fastcall SearchCore(bool is_down, UnicodeString kwd, SearchOption opt);

	bool __fastcall SearchDown(UnicodeString kwd, SearchOption opt);
	bool __fastcall SearchUp(UnicodeString kwd, SearchOption opt);

	/** @brief �������Ƀo�C�g�񌟍� */
	bool __fastcall SearchDownBytes(UnicodeString kwd, bool case_sw);
	/** @brief ������Ƀo�C�g�񌟍�*/
	bool __fastcall SearchUpBytes(UnicodeString kwd, bool case_sw);

	/**
	 * @brief �I�𕶎��������
	 * @param up_sw ������Ɍ���
	 * @param em_sw �}�b�`��������\��
	 * @return true 
	 * @return false 
	 */
	bool __fastcall SearchSel(bool up_sw, bool em_sw);

	/** @brief �J�[�\���ʒu�̑Ή����銇�ʂ�ݒ� */
	bool __fastcall UpdatePairPos();

	bool __fastcall SearchPairCore(UnicodeString bgn_ptn, UnicodeString end_ptn);

	/** @brief �Ή�����s�v�f������ */
	bool __fastcall SearchPair(UnicodeString prm);

	/** @brief �w��s�ԍ��Ɉړ�*/
	bool __fastcall ToLine(int lno, int col = -1);

	/** @brief TopAddress ����̑��΃A�h���X�Ɉړ� */
	bool __fastcall ToAddrR(unsigned int adr);

	/** @brief ��΃A�h���X�Ɉړ� */
	bool __fastcall ToAddrA(__int64 adr);

	void __fastcall JumpLine(UnicodeString ln_str);

	void __fastcall MarkLine(int lno);
	bool __fastcall IsMarked(int lno = 0);

	/** @brief �{�������ɒǉ� */
	void __fastcall add_ViewHistory();

	/** @brief �_���v���X�g���擾 */
	void __fastcall GetDumpList(TStringList *lst);

	/** @brief �C���N�������^���T�[�` */
	void __fastcall IncSearch(UnicodeString keystr);

	/**
	 * @brief �W���L�[����ɑΉ�����R�}���h���擾
	 * @param keystr �L�[������
	 * @return UnicodeString �R�}���h
	 */
	UnicodeString __fastcall GetStdKeyCommand(UnicodeString keystr);

	/**
	 * @brief �R�}���h�����s
	 * @param cmd �R�}���h
	 * @param prm �p�����[�^
	 * @return true �������ꂽ
	 */
	bool __fastcall ExeCommand(const _TCHAR *cmd, UnicodeString prm = EmptyStr);

	/** @brief �e�L�X�g�r���[�A�ŗ��p�\�ȃR�}���h���H */
	bool __fastcall IsCmdAvailable(UnicodeString cmd);

	/** @brief ���[�h�ŗL�̋֎~�R�}���h���H */
	bool __fastcall IsCmdInhibited(UnicodeString cmd);

	/** @brief HtmlToText �̃I�v�V�����ݒ� */
	void __fastcall SetHtmlToText(UnicodeString prm);
};
//---------------------------------------------------------------------------
extern TTxtViewer *TxtViewer;

//---------------------------------------------------------------------------
#endif
