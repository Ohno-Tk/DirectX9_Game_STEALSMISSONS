/*=============================================================================

�T�E���h(DirectX)[ ConfigWindows.h ]

-------------------------------------------------------------------------------

��  Create
	2017/10/15
=============================================================================*/

#ifndef _SOUND_H_
#define _SOUND_H_

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "RendererDirectX.h"

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class SoundDirectX
{
public:
	SoundDirectX();

	// �T�E���h�t�@�C��
	enum SOUND_LABEL
	{
		SOUND_BGM_TITLESCENE = 0,	//	�^�C�g��BGM
		SOUND_BGM_GAMESCENE,		// �Q�[��BGM
		SOUND_SE_TITLEGUN,	//	�^�C�g���e��
		SOUND_SE_SELECT,		// �I���ړ���
		SOUND_SE_EXIT,		// �I����
		SOUND_SE_GAMECLEAR,		// �Q�[���N���A
		SOUND_SE_GAMEOVER,		// �Q�[���I�[�o�[
		SOUND_SE_FOUND,	//	������
		SOUND_SE_CALL,	//	call��
		SOUND_SE_HEAL,	// �񕜉�
		SOUND_SE_GETITEM,// �A�C�e���擾
		SOUND_LABEL_MAX

	};

	HRESULT Initialize(void);	//	������
	void Uninitialize(void);	//	�I��

	HRESULT Play(SOUND_LABEL label);					//	���y�Đ�
	void Stop(SOUND_LABEL label);						//	���Ԗڂ̉����~�߂�
	void Stop(void);									//	��~
	void SetVolume(SOUND_LABEL label, float fValue);	//	�{�����[���ݒ�

private:
	// �p�����[�^�\����
	struct PARAM
	{
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���^

	};

	HRESULT CheckChunk(HANDLE hFile, DWORD dwFormat, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *m_pXAudio2;									// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice;				// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// �\�[�X�{�C�X
	BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^�T�C�Y

	static PARAM m_aParam[SOUND_LABEL_MAX];					// �p�����[�^
};

#endif