/*=============================================================================

�Q�[���I�[�o�[�V�[��[ GameOverScene.cpp ]

-------------------------------------------------------------------------------

��  Create
2017/11/13
=============================================================================*/

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "FrameworkBase\Common.h"
#include "FrameworkBase\Debug.h"
#include "FrameworkBase\RendererDirectX.h"
#include "FrameworkBase\Game.h"
#include "FrameworkBase\Fade.h"
#include "FrameworkBase\InputDirectX.h"
#include "FrameworkBase\SoundDirectX.h"
#include "Object.h"
#include "Sprite2D.h"
#include "Fade2DObject.h"
#include "Scroll2DObject.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "GameOverScene.h"


void GameOverScene::Initialize(void)
{
	Debug::Log("�Q�[���I�[�o�[�V�[��");

	// ������
	m_KeyBoard = Game::GetInstance()->GetKeyboard();
	m_XInput = Game::GetInstance()->GetXInput();
	m_Select = SELECT_CONTINUE;

	m_BackGround = Scroll2DObject::Create(D3DXVECTOR3(0.0f,0.0f,0.0f), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), TEXTURE_PATH"RESULT/GameOver_Bg.jpg", D3DXVECTOR2(0.0f,0.001f), 0);

	Sprite2D::Create(D3DXVECTOR3(240.0f, 100.0f, 0.0f), D3DXVECTOR2(350.0f, 200.0f), TEXTURE_PATH"RESULT/GameOver_Logo.png");

	m_ContiueLogo = Fade2DObject::Create(D3DXVECTOR3(350.0f, 350.0f, 0.0f), D3DXVECTOR2(100.0f, 50.0f), TEXTURE_PATH"RESULT/Continue.png",1.0f, 0.5f);

	m_EndLogo = Fade2DObject::Create(D3DXVECTOR3(350.0f, 430.0f, 0.0f), D3DXVECTOR2(100.0f, 50.0f), TEXTURE_PATH"RESULT/End.png",1.0f, 0.5f);
	m_EndLogo->SetFadeFlag(false);

	m_SelectFrame = Sprite2D::Create(m_ContiueLogo->GetPosition(), D3DXVECTOR2(100.0f, 50.0f), TEXTURE_PATH"GAME/White.png",D3DXVECTOR4(0.0f,1.0f,1.0f,0.5f), 2);

#ifndef ENABLE_SOUND
	m_Sound = Game::GetInstance()->GetSound();

	m_Sound->Play(SoundDirectX::SOUND_SE_GAMEOVER);
#endif
}

void GameOverScene::Uninitialize(void)
{
	m_KeyBoard = NULL;
	m_Sound = NULL;
	m_BackGround = NULL;
	m_ContiueLogo = NULL;
	m_EndLogo = NULL;
	m_SelectFrame = NULL;

	Object::ReleaseAll(); // �S�I�u�W�F�N�g�̉��
}

void GameOverScene::Update(void)
{
	KeyboardControl();

	Object::UpdateAll(); //	�S�I�u�W�F�N�g�̍X�V

#ifdef _DEBUG
	if(m_KeyBoard->GetKeyTrigger(DIK_SPACE))
	{
		Fade::SetFade(Fade::FADE_OUT, new TitleScene);
	}
#endif
}

void GameOverScene::Draw(void)
{
	Object::DrawAll(); // �S�I�u�W�F�N�g�̕`��
}

/*-----------------------------------------------------------------------------
Function:   void TutorialScene::SceneChange(void)
Overview:   �V�[����ς���
-----------------------------------------------------------------------------*/
void GameOverScene::SceneChange(void)
{
	switch (m_Select)
	{
	case SELECT_CONTINUE:	//	�R���e�B�j���[
		//	�X�N���[���X�s�[�h�̕ύX
		m_BackGround->SetScrollSpeed(D3DXVECTOR2(0.0f, 0.01f));

		Fade::SetFade(Fade::FADE_OUT, new GameScene);

#ifndef ENABLE_SOUND
		m_Sound->Play(SoundDirectX::SOUND_SE_TITLEGUN);
		m_Sound->Stop(SoundDirectX::SOUND_SE_GAMEOVER);
#endif

		break;
	case SELECT_END:	//	�G���h

		Fade::SetFade(Fade::FADE_OUT, new TitleScene);

#ifndef ENABLE_SOUND
		m_Sound->Play(SoundDirectX::SOUND_SE_EXIT);
		m_Sound->Stop(SoundDirectX::SOUND_SE_GAMEOVER);
#endif

		break;
	}
}

/*-----------------------------------------------------------------------------
Function:   void TutorialScene::SelectMode(void)
Overview:   �I����
-----------------------------------------------------------------------------*/
void GameOverScene::SelectMode(void)
{
	switch (m_Select)
	{
	case SELECT_CONTINUE:	//	�R���e�B�j���[

		m_ContiueLogo->SetFadeFlag(true);
		m_EndLogo->SetFadeFlag(false);
		m_EndLogo->SetAlphaColor(0.5f);

		m_SelectFrame->SetPosition(m_ContiueLogo->GetPosition());
		break;
	case SELECT_END:	//	�G���h

		m_ContiueLogo->SetFadeFlag(false);
		m_ContiueLogo->SetAlphaColor(0.5f);
		m_EndLogo->SetFadeFlag(true);

		m_SelectFrame->SetPosition(m_EndLogo->GetPosition());
		break;
	}
}

/*-----------------------------------------------------------------------------
Function:   void TutorialScene::KeyboardControl(void)
Overview:   �L�[�{�[�h����
-----------------------------------------------------------------------------*/
void GameOverScene::KeyboardControl(void)
{
	float AnalogY = m_XInput->GetAnalogValue(XInput::CONTROLLER_1, XInput::LEFT).y;

	if (m_KeyBoard->GetKeyTrigger(DIK_W) || AnalogY > 0.9f)
	{
		m_Select--;

		if (m_Select < SELECT_CONTINUE)
		{
			m_Select = SELECT_CONTINUE;
		}
	}
	else if (m_KeyBoard->GetKeyTrigger(DIK_S) || AnalogY < -0.9f)
	{
		m_Select++;

		if (m_Select >= SELECT_MAX)
		{
			m_Select = SELECT_MAX - 1;
		}
	}

	SelectMode(); // �I����

	if(m_KeyBoard->GetKeyTrigger(DIK_RETURN) ||  m_XInput->GetKeyTrigger(XInput::CONTROLLER_1, XINPUT_GAMEPAD_B))
	{
		SceneChange(); // �V�[����ς���
	}
}