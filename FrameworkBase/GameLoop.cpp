/*=============================================================================

�Q�[�����[�v[ GameLoop.cpp ]

-------------------------------------------------------------------------------

��  Create
2017/11/11
=============================================================================*/

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "Common.h"
#include "Game.h"
#include "GameLoop.h"

/*-----------------------------------------------------------------------------
Static
-----------------------------------------------------------------------------*/
GameLoop* GameLoop::m_Instance = NULL;

/*-----------------------------------------------------------------------------
Function:   Game* Game::Instance(void)
Overview:   �C���X�^���X����
-----------------------------------------------------------------------------*/
GameLoop* GameLoop::Instance(void)
{
	if(!m_Instance)
	{
		m_Instance = new GameLoop;
	}

	return m_Instance;
}

/*-----------------------------------------------------------------------------
Function:   void GameLoop::Destroy(void)
Overview:   �C���X�^���X�j��
-----------------------------------------------------------------------------*/
void GameLoop::Destroy(void)
{
	SAFE_DELETE(m_Instance);
}

GameLoop::GameLoop()
{
	m_FrameCount = 0;
	m_CurrentTime = 0; //	���݂̎���
	m_ExecLastTime = 0; // ���݂̎������~���P�ʂŎ擾
	m_FPSLastTime = 0;
	m_CountFPS = 0; // FPS�J�E���^
}

void GameLoop::Init(HINSTANCE hInstance, HWND hWnd)
{
	//	����\�̐ݒ�i�^�C�}�[�̐��x��ǂ�����j
	timeBeginPeriod(1);

	//	�e�J�E���^�[�̏�����
	m_FrameCount = 0;
	m_CurrentTime = 0;				//	���݂̎���
	m_ExecLastTime = timeGetTime();	//	���݂̎������~���P�ʂŎ擾
	m_FPSLastTime = m_ExecLastTime;

	Game::GetInstance()->Init(hInstance, hWnd);
}

void GameLoop::ClockFps(void)
{
	m_CurrentTime = timeGetTime();	//	���݂̎������~���P�ʂŎ擾

	if ((m_CurrentTime - m_FPSLastTime) >= 500)
	{

		m_CountFPS = (m_FrameCount * 1000) / (m_CurrentTime - m_FPSLastTime);
		m_FPSLastTime = m_CurrentTime;
		m_FrameCount = 0;

	}

	if ((m_CurrentTime - m_ExecLastTime) >= (1000 / 60))
	{	//	���݂̃t���[������ǂ�ʂ������̂�( �����v�Z )	�f�o�b�O�Ōv���������Ƃ���if���R�����g�A�E�g

		m_ExecLastTime = m_CurrentTime;	//	�����������Ԃ�ۑ�

		// �X�V����
		Game::GetInstance()->Update();

		// �`�揈��
		Game::GetInstance()->Draw();

		m_FrameCount++;

	}
}

void GameLoop::Uninit(void)
{
	Game::GetInstance()->Uninit();
}