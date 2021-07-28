/*=============================================================================

�Q�[�����[�v[ GameLoop.h ]
(�V���O���g���p�^�[��)

-------------------------------------------------------------------------------

��  Create
2017/11/11
=============================================================================*/

#ifndef _GAMELOOP_H_
#define _GAMELOOP_H_

/*-----------------------------------------------------------------------------
Library
[�\���v���p�e�B]->[�����J�[]->[����]->[�ǉ��̈ˑ��t�@�C��]�ɋL�q���Ă��\
-----------------------------------------------------------------------------*/
#pragma comment( lib , "winmm.lib" )

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class GameLoop
{
public:
	static GameLoop* Instance(void); // �C���X�^���X����
	static void Destroy(void); // �C���X�^���X�j��

	void Init(HINSTANCE hInstance, HWND hWnd); // ������
	void ClockFps(void); //	FPS�v��
	void Uninit(void); // �I��

	// Getter
	const int GetFPS(void){ return m_CountFPS; } // FPS�擾

private:
	GameLoop();

private:
	static GameLoop* m_Instance;

	DWORD m_FrameCount;
	DWORD m_CurrentTime; // ���݂̎���
	DWORD m_ExecLastTime; // ���݂̎������~���P�ʂŎ擾
	DWORD m_FPSLastTime;
	int m_CountFPS; //	FPS�J�E���^
};

#endif
