/*=============================================================================

�`���[�g���A���V�[��[ TutorialScene.cpp ]

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
#include "GameScene.h"
#include "TutorialScene.h"

void TutorialScene::Initialize(void)
{
	Debug::Log("�`���[�g���A���V�[��");

#ifndef ENABLE_SOUND
	Game::GetInstance()->GetSound()->Play(SoundDirectX::SOUND_SE_CALL);
#endif

	m_XInput = Game::GetInstance()->GetXInput();


	Sprite2D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), TEXTURE_PATH"TUTORIAL/Communication_UI.png",D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f), 0);

	Sprite2D::Create(D3DXVECTOR3(18.0f, 50.0f, 0.0f), D3DXVECTOR2(200.0f, 200.0f), TEXTURE_PATH"TUTORIAL/Colonel.png",D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f), 3);

	Sprite2D::Create(D3DXVECTOR3(590.0f, 50.0f, 0.0f), D3DXVECTOR2(200.0f, 220.0f), TEXTURE_PATH"TUTORIAL/Snake.png",D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f), 3);

	Sprite2D::Create(D3DXVECTOR3(80.0f, 245.0f, 0.0f), D3DXVECTOR2(650.0f, 350.0f), TEXTURE_PATH"TUTORIAL/Description.png",D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f), 3);

	m_PushButtom = Fade2DObject::Create(D3DXVECTOR3(700.0f, 500.0f, 0.0f), D3DXVECTOR2(50.0f, 50.0f), TEXTURE_PATH"TUTORIAL/BButtom.png", 1.0f, 0.1f);

}

void TutorialScene::Uninitialize(void)
{
	Object::ReleaseAll(); // �S�I�u�W�F�N�g�̉��
}

void TutorialScene::Update(void)
{
	if(m_XInput->GetActive(XInput::CONTROLLER_1))
	{
		m_PushButtom->SetPosition(D3DXVECTOR3(700.0f, 500.0f, 0.0f));
		m_PushButtom->SetSize(D3DXVECTOR2(50.0f, 50.0f));
		m_PushButtom->SetTexturePath(TEXTURE_PATH"TITLE/PushBButtom.png");
	}
	else
	{
		m_PushButtom->SetPosition(D3DXVECTOR3(550.0f, 450.0f, 0.0f));
		m_PushButtom->SetSize(D3DXVECTOR2(200.0f, 150.0f));
		m_PushButtom->SetTexturePath(TEXTURE_PATH"TITLE/PushEnter.png");
	}


	SceneChange(); // �V�[����ς���

	Object::UpdateAll(); //	�S�I�u�W�F�N�g�̍X�V
}

void TutorialScene::Draw(void)
{
	Object::DrawAll(); // �S�I�u�W�F�N�g�̕`��
}

/*-----------------------------------------------------------------------------
Function:   void TutorialScene::SceneChange(void)
Overview:   �V�[����ς���
-----------------------------------------------------------------------------*/
void TutorialScene::SceneChange(void)
{
	DirectXKeyboard* keyBoard = Game::GetInstance()->GetKeyboard();

	if (keyBoard->GetKeyTrigger(DIK_RETURN) || m_XInput->GetKeyTrigger(XInput::CONTROLLER_1, XINPUT_GAMEPAD_B))
	{
		Fade::SetFade(Fade::FADE_OUT, new GameScene);
	}
}