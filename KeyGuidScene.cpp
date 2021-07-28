/*=============================================================================

[ KeyGuidScene.cpp ]

-------------------------------------------------------------------------------

��  Create
2018/02/23
=============================================================================*/

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "FrameworkBase\Common.h"
#include "FrameworkBase\RendererDirectX.h"
#include "FrameworkBase\Debug.h"
#include "FrameworkBase\Game.h"
#include "FrameworkBase\InputDirectX.h"
#include "FrameworkBase\SoundDirectX.h"
#include "FrameworkBase\Fade.h"
#include "Object.h"
#include "Sprite2D.h"
#include "Fade2DObject.h"
#include "TitleScene.h"
#include "KeyGuidScene.h"

void KeyGuidScene::Initialize(void)
{
	Debug::Log("��������V�[��");

#ifndef ENABLE_SOUND
	Game::GetInstance()->GetSound()->Play(SoundDirectX::SOUND_SE_CALL);
#endif

	m_XInput = Game::GetInstance()->GetXInput();


	Sprite2D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), TEXTURE_PATH"GUID/KeyGuid.jpg",D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f), 0);

	m_PushButtom = Fade2DObject::Create(D3DXVECTOR3(700.0f, 500.0f, 0.0f), D3DXVECTOR2(50.0f, 50.0f), TEXTURE_PATH"TUTORIAL/BButtom.png", 1.0f, 0.1f);

}

void KeyGuidScene::Uninitialize(void)
{
	Object::ReleaseAll(); // �S�I�u�W�F�N�g�̉��
}

void KeyGuidScene::Update(void)
{
	if(m_XInput->GetActive(XInput::CONTROLLER_1))
	{
		m_PushButtom->SetPosition(D3DXVECTOR3(700.0f, 500.0f, 0.0f));
		m_PushButtom->SetSize(D3DXVECTOR2(50.0f, 50.0f));
		m_PushButtom->SetTexturePath(TEXTURE_PATH"TITLE/PushBButtom.png");
	}
	else
	{
		m_PushButtom->SetPosition(D3DXVECTOR3(550.0f, 480.0f, 0.0f));
		m_PushButtom->SetSize(D3DXVECTOR2(200.0f, 150.0f));
		m_PushButtom->SetTexturePath(TEXTURE_PATH"TITLE/PushEnter.png");
	}


	SceneChange(); // �V�[����ς���

	Object::UpdateAll(); //	�S�I�u�W�F�N�g�̍X�V
}

void KeyGuidScene::Draw(void)
{
	Object::DrawAll(); // �S�I�u�W�F�N�g�̕`��
}

/*-----------------------------------------------------------------------------
Function:   void TutorialScene::SceneChange(void)
Overview:   �V�[����ς���
-----------------------------------------------------------------------------*/
void KeyGuidScene::SceneChange(void)
{
	DirectXKeyboard* keyBoard = Game::GetInstance()->GetKeyboard();

	if (keyBoard->GetKeyTrigger(DIK_RETURN) || m_XInput->GetKeyTrigger(XInput::CONTROLLER_1, XINPUT_GAMEPAD_B))
	{
		Fade::SetFade(Fade::FADE_OUT, new TitleScene);
	}
}