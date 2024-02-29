/**
 * @file usr_id3.h
 * @brief MP3 ID3�^�O���̏���
 */
//---------------------------------------------------------------------------
#ifndef UsrID3H
#define UsrID3H

//---------------------------------------------------------------------------
/** @brief ID3�w�b�_ */
struct id3_hdr {
	char hdr_id[3];
	BYTE maj_ver;
	BYTE revision;
	BYTE flag;
	BYTE size[4];
};
/** @brief �g���w�b�_ */
struct id3_ex_hdr {
	BYTE size[4];
	BYTE flag[2];
};

/** @brief �t���[���w�b�_(v2.3,v2.4) */
struct id3_frm_hdr {
	char frame_id[4];
	BYTE size[4];
	BYTE flag[2];
};

/** @brief �t���[���w�b�_(v2.2) */
struct id3_frm_hdr_2 {
	char frame_id[3];
	BYTE size[3];
};

//---------------------------------------------------------------------------
/**
 * @brief MP3�t�@�C���� ID3 Tag v2/v1 �����擾
 * @param fnam �t�@�C����
 * @param[out] lst ���ʃ��X�g(����=���e)
 * @param id_min �ŏ����̏��� (T??=�`���Ŏ擾)
 * @return true ���� 
 */
bool ID3_GetInf(UnicodeString fnam, TStringList* lst, bool id_min = false);

/**
 * @brief MP3�t�@�C�����疄�ߍ��݉摜���r�b�g�}�b�v�Ŏ擾/�t�@�C���o��
 * @param fnam �t�@�C����
 * @param[out] bmpimg �o�̓r�b�g�}�b�v
 * @param o_fnam �o�̓t�@�C����
 * @return true ����
 */
bool ID3_GetImage(UnicodeString fnam, Graphics::TBitmap *bmpimg, UnicodeString o_fnam = EmptyStr);

//---------------------------------------------------------------------------
#endif
