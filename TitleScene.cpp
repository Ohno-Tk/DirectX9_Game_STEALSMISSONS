/*=============================================================================

タイトルシーン[ TitleScene.cpp ]

-------------------------------------------------------------------------------
■  Author
Ohno Takuya

■  Create
2017/11/11
=============================================================================*/

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "FrameworkBase\Common.h"
#include "FrameworkBase\Debug.h"
#include "FrameworkBase\RendererDirectX.h"
#include "FrameworkBase\Game.h"
#include "FrameworkBase\CameraDirectX.h"
#include "FrameworkBase\Fade.h"
#include "FrameworkBase\InputDirectX.h"
#include "FrameworkBase\SoundDirectX.h"
#include "FrameworkBase\ModelManagerDirectX.h"
#include "FrameworkBase\FileManager.h"
#include "CameraState.h"
#include "Object.h"
#include "Sprite2D.h"
#include "SpriteModeX.h"
#include "FrameworkBase\Motion.h"
#include "MeshField.h"
#include "MeshWall.h"
#include "MeshDome.h"
#include "Fade2DObject.h"
#include "TitleBackGround.h"
#include "LiftModel.h"
#include "TutorialScene.h"
#include "KeyGuidScene.h"
#include "TitleScene.h"

/*-----------------------------------------------------------------------------
Namespace
-----------------------------------------------------------------------------*/
using namespace std;


void TitleScene::Initialize(void)
{
	Debug::Log("タイトルシーン");

#ifndef ENABLE_SOUND
	m_Sound = Game::GetInstance()->GetSound();
	m_Sound->Play(SoundDirectX::SOUND_BGM_TITLESCENE);
#endif

	m_KeyBoard = Game::GetInstance()->GetKeyboard();
	m_XInput = Game::GetInstance()->GetXInput();
	m_Select = SELECT_START;


	Game::GetInstance()->GetCamera()->SetPositionEye(D3DXVECTOR3(0.0f, 10.0f, -30.0f));
	Game::GetInstance()->GetCamera()->SetPositionAt(D3DXVECTOR3(0.0f, 20.5f, 0.0f));

	Game::GetInstance()->GetCamera()->SetState(new CameraStateNull);

	TitleBackGround* object[3];
	object[0] = TitleBackGround::Create(D3DXVECTOR3( 0.0f,38.0f,30.0f), D3DXVECTOR3(0.0f,  0.0f,0.0f));
	object[0]->SetNormal(D3DXVECTOR3(0.0f,0.0f,-1.0f));
	object[1] = TitleBackGround::Create(D3DXVECTOR3( 52.5f,38.0f,0.0f), D3DXVECTOR3(0.0f, 60.0f,0.0f));
	object[1]->SetNormal(D3DXVECTOR3(0.0f,0.0f,-1.0f));
	object[2] = TitleBackGround::Create(D3DXVECTOR3(-52.5f,38.0f,0.0f), D3DXVECTOR3(0.0f,-60.0f,0.0f));
	object[2]->SetNormal(D3DXVECTOR3(-1.0f,0.0f,-1.0f));

	Motion* player = Motion::Create(3, MOTION_PATH"Player.txt");
	player->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 0.0f));

	LiftModel::Create();

	Sprite2D::Create(D3DXVECTOR3(100.0f, 80.0f, 0.0f), D3DXVECTOR2(600.0f, 200.0f), TEXTURE_PATH"TITLE/Title_Logo.png",D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f), 5);

//	m_PushButtom = Fade2DObject::Create(D3DXVECTOR3(150.0f, 330.0f, 0.0f), D3DXVECTOR2(250.0f, 200.0f), TEXTURE_PATH"PushEnter.png");

	m_Start_Logo = Sprite2D::Create(D3DXVECTOR3(150.0f, 350.0f, 0.0f), D3DXVECTOR2(100.0f, 50.0f), TEXTURE_PATH"TITLE/Start_logo.png");

	m_KeyGuid_Logo = Sprite2D::Create(D3DXVECTOR3(150.0f, 450.0f, 0.0f), D3DXVECTOR2(100.0f, 50.0f), TEXTURE_PATH"TITLE/KeyGuid_logo.png");

	m_SelectFrame = Sprite2D::Create(m_Start_Logo->GetPosition(), D3DXVECTOR2(100.0f, 50.0f), TEXTURE_PATH"GAME/White.png",D3DXVECTOR4(0.0f,1.0f,1.0f,0.5f), 2);
}

void TitleScene::Uninitialize(void)
{
	Object::ReleaseAll(); // 全オブジェクトの解放
}

void TitleScene::Update(void)
{
	CursorControl();

	Object::UpdateAll(); //	全オブジェクトの更新

	if(m_KeyBoard->GetKeyTrigger(DIK_RETURN) ||  m_XInput->GetKeyTrigger(XInput::CONTROLLER_1, XINPUT_GAMEPAD_B))
	{
		SceneChange(); // シーンを変える
	}

}

void TitleScene::Draw(void)
{
	Object::DrawAll(); // 全オブジェクトの描画
}

/*-----------------------------------------------------------------------------
選択時
-----------------------------------------------------------------------------*/
void TitleScene::SelectMode(void)
{
	switch (m_Select)
	{
	case SELECT_START:	//	コンティニュー
		m_SelectFrame->SetPosition(m_Start_Logo->GetPosition());
		break;
	case SELECT_KEYGUID:	//	エンド
		m_SelectFrame->SetPosition(m_KeyGuid_Logo->GetPosition());
		break;
	}
}

/*-----------------------------------------------------------------------------
Function:   void TitleScene::SceneChange(void)
Overview:   シーンを変える
-----------------------------------------------------------------------------*/
void TitleScene::SceneChange(void)
{
	switch (m_Select)
	{
	case SELECT_START:	//	コンティニュー
		Fade::SetFade(Fade::FADE_OUT, new TutorialScene);

#ifndef ENABLE_SOUND
		m_Sound->Play(SoundDirectX::SOUND_SE_TITLEGUN);
		m_Sound->Stop(SoundDirectX::SOUND_BGM_TITLESCENE);
#endif

		break;
	case SELECT_KEYGUID:	//	エンド
		Fade::SetFade(Fade::FADE_OUT, new KeyGuidScene);

#ifndef ENABLE_SOUND
		m_Sound->Play(SoundDirectX::SOUND_SE_TITLEGUN);
		m_Sound->Stop(SoundDirectX::SOUND_BGM_TITLESCENE);
#endif

		break;
	}
}

void TitleScene::CursorControl(void)
{
	float AnalogY = m_XInput->GetAnalogValue(XInput::CONTROLLER_1, XInput::LEFT).y;

	if (m_KeyBoard->GetKeyTrigger(DIK_W) || AnalogY > 0.9f)
	{
		m_Select--;

		if (m_Select < SELECT_NONE)
		{
			m_Select = SELECT_START;
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

	SelectMode(); // 選択時
}