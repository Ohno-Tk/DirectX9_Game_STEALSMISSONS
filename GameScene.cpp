/*=============================================================================

�Q�[���V�[��[ GameScene.cpp ]

-------------------------------------------------------------------------------

��  Create
2017/11/11
=============================================================================*/

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "FrameworkBase\RendererDirectX.h"
#include "FrameworkBase\Common.h"
#include "FrameworkBase\Debug.h"
#include "FrameworkBase\TextureManagerDirectX.h"
#include "FrameworkBase\ModelManagerDirectX.h"
#include "FrameworkBase\FileManager.h"
#include "FrameworkBase\CameraDirectX.h"
#include "FrameworkBase\Game.h"
#include "FrameworkBase\Fade.h"
#include "FrameworkBase\InputDirectX.h"
#include "FrameworkBase\SoundDirectX.h"
#include "CameraState.h"
#include "CameraStateFollow.h"
#include "Object.h"
#include "Sprite2D.h"
#include "SpriteModeX.h"
#include "MeshField.h"
#include "MeshWall.h"
#include "MeshSphere.h"
#include "SkySphere.h"
#include "ObstaclePillar.h"
#include "ObstacleContainer.h"
#include "Goal.h"
#include "Player.h"
#include "Enemy.h"
#include "FolkLift.h"
#include "ItemRation.h"
#include "TitleScene.h"
#include "GameClearScene.h"
#include "GameOverScene.h"
#include "GameScene.h"
#include "MeshDome.h"
#include "ItemUIRation.h"
#include "ItemPossession.h"

/*-----------------------------------------------------------------------------
Static
-----------------------------------------------------------------------------*/
bool GameScene::m_GameClear = false;
bool GameScene::m_GameOver = false;
Player* GameScene::m_Player = NULL;
MeshField* GameScene::m_MeshField = NULL;
MeshWall* GameScene::m_MeshWall[] = {NULL};
Goal* GameScene::m_Goal = NULL;
ItemUI* GameScene::m_ItemUI = NULL;

/*-----------------------------------------------------------------------------
Namespace
-----------------------------------------------------------------------------*/
using namespace std;


void GameScene::Initialize(void)
{
	Debug::Log("�Q�[���V�[��");

#ifndef ENABLE_SOUND
	m_Sound = Game::GetInstance()->GetSound();

	m_Sound->Play(SoundDirectX::SOUND_BGM_GAMESCENE);
#endif

	m_KeyBoard = Game::GetInstance()->GetKeyboard();

	Game::GetInstance()->GetCamera()->SetPositionAt(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	Game::GetInstance()->GetCamera()->SetPositionEye(D3DXVECTOR3(-130.0, 90.0f, -180.0f));
	
	Game::GetInstance()->GetCamera()->SetState(new CameraStateFollow(Game::GetInstance()->GetCamera()));

	//Game::GetInstance()->GetCamera()->SetPositionAt(D3DXVECTOR3(12.0, 20.0f, 120.0f));
	//Game::GetInstance()->GetCamera()->SetPositionEye(D3DXVECTOR3(12.0, 20.0f, 180.0f));

	m_MeshField = MeshField::Create(D3DXVECTOR3(0.0f,0.0f,0.0f), 10, 10, 30.0f, 30.0f, TEXTURE_PATH"GAME/field.jpg");

	m_MeshWall[0] = MeshWall::Create(D3DXVECTOR3(-150.0f, 60.0f,  0.0f), -90.0f, 20, 8, 15.0f, 15.0f);
	m_MeshWall[0]->SetNormal(D3DXVECTOR3(1.0f, 0.0f, 0.0f));
	m_MeshWall[1] = MeshWall::Create(D3DXVECTOR3( 150.0f, 60.0f,  0.0f),  90.0f, 20, 8, 15.0f, 15.0f);
	m_MeshWall[1]->SetNormal(D3DXVECTOR3(-1.0f, 0.0f, 0.0f));
	m_MeshWall[2] = MeshWall::Create(D3DXVECTOR3( 0.0f,   60.0f,  150.0f), 0.0f, 20, 8, 15.0f, 15.0f);
	m_MeshWall[2]->SetNormal(D3DXVECTOR3(0.0f, 0.0f, -1.0f));
	m_MeshWall[3] = MeshWall::Create(D3DXVECTOR3(0.0f,    60.0f, -150.0f),180.0f,20, 8, 15.0f, 15.0f);
	m_MeshWall[3]->SetNormal(D3DXVECTOR3(0.0f, 0.0f, 1.0f));

	FolkLift::Create();

	m_Goal = Goal::Create(D3DXVECTOR3(12.0, 0.0f, 120.0f));

	ObstaclePillar::Create(D3DXVECTOR3(-140.0f, 0.0f, 140.0f));
	ObstaclePillar::Create(D3DXVECTOR3(-123.5f, 0.0f, 140.0f));
	ObstaclePillar::Create(D3DXVECTOR3(-107.0f, 0.0f, 140.0f));
	ObstaclePillar::Create(D3DXVECTOR3( -90.5f, 0.0f, 140.0f));
	ObstaclePillar::Create(D3DXVECTOR3(-140.5f, 0.0f, 123.5f));
	ObstaclePillar::Create(D3DXVECTOR3(-123.5f, 0.0f, 123.5f));
	ObstaclePillar::Create(D3DXVECTOR3(-107.0f, 0.0f, 123.5f));
	ObstaclePillar::Create(D3DXVECTOR3( -90.5f, 0.0f, 123.5f));
	ObstaclePillar::Create(D3DXVECTOR3(-140.5f, 0.0f, 107.5f));
	ObstaclePillar::Create(D3DXVECTOR3(-123.5f, 0.0f, 107.5f));
	ObstaclePillar::Create(D3DXVECTOR3(-107.0f, 0.0f, 107.5f));
	ObstaclePillar::Create(D3DXVECTOR3( -90.5f, 0.0f, 107.5f));
	ObstaclePillar::Create(D3DXVECTOR3(-140.5f, 0.0f,  90.5f));
	ObstaclePillar::Create(D3DXVECTOR3(-123.5f, 0.0f,  90.5f));
	ObstaclePillar::Create(D3DXVECTOR3(-140.5f, 0.0f,  74.0f));
	ObstaclePillar::Create(D3DXVECTOR3(-123.5f, 0.0f,  74.0f));
	ObstaclePillar::Create(D3DXVECTOR3(-140.5f, 0.0f,  57.5f));
	ObstaclePillar::Create(D3DXVECTOR3(-123.5f, 0.0f,  57.5f));
	ObstaclePillar::Create(D3DXVECTOR3(-140.5f, 0.0f,  41.0f));
	ObstaclePillar::Create(D3DXVECTOR3(-123.5f, 0.0f,  41.0f));
	ObstaclePillar::Create(D3DXVECTOR3(-140.5f, 0.0f,  24.5f));
	ObstaclePillar::Create(D3DXVECTOR3(-123.5f, 0.0f,  24.5f));
	ObstaclePillar::Create(D3DXVECTOR3(-140.5f, 0.0f,   8.0f));
	ObstaclePillar::Create(D3DXVECTOR3(-123.5f, 0.0f,   8.0f));
	ObstaclePillar::Create(D3DXVECTOR3(-140.5f, 0.0f,  -8.5f));
	ObstaclePillar::Create(D3DXVECTOR3(-123.5f, 0.0f,  -8.5f));
	ObstaclePillar::Create(D3DXVECTOR3(-140.5f, 0.0f, -25.0f));
	ObstaclePillar::Create(D3DXVECTOR3(-123.5f, 0.0f, -25.0f));
	ObstaclePillar::Create(D3DXVECTOR3(-140.5f, 0.0f, -41.5f));
	ObstaclePillar::Create(D3DXVECTOR3(-123.5f, 0.0f, -41.5f));
	ObstaclePillar::Create(D3DXVECTOR3(-140.5f, 0.0f, -58.0f));
	ObstaclePillar::Create(D3DXVECTOR3(-123.5f, 0.0f, -58.0f));

	ObstacleContainer::Create(D3DXVECTOR3(-50.0f,  0.0f, 35.0f));
	ObstacleContainer::Create(D3DXVECTOR3(-50.0f, 25.0f, 35.0f));
	ObstacleContainer::Create(D3DXVECTOR3(-25.0f,  0.0f, 35.0f));
	ObstacleContainer::Create(D3DXVECTOR3( 60.0f,  0.0f, 35.0f));
	ObstacleContainer::Create(D3DXVECTOR3( 85.0f,  0.0f, 35.0f));
	ObstacleContainer::Create(D3DXVECTOR3( 85.0f, 25.0f, 35.0f));
	ObstacleContainer::Create(D3DXVECTOR3(-50.0f,  0.0f,-80.0f));
	ObstacleContainer::Create(D3DXVECTOR3(-50.0f, 25.0f,-80.0f));
	ObstacleContainer::Create(D3DXVECTOR3(-25.0f,  0.0f,-80.0f));
	ObstacleContainer::Create(D3DXVECTOR3( 60.0f,  0.0f,-80.0f));
	ObstacleContainer::Create(D3DXVECTOR3( 85.0f,  0.0f,-80.0f));
	ObstacleContainer::Create(D3DXVECTOR3( 85.0f, 25.0f,-80.0f));

	m_Player = Player::Create(D3DXVECTOR3(-130.0, 0.0f, -130.0f), 180.0f);

	Enemy::Create("data/GAMEDATA/Enemy00.txt");
	Enemy::Create("data/GAMEDATA/Enemy01.txt");
	Enemy::Create("data/GAMEDATA/Enemy02.txt");

	ItemRation::Create(D3DXVECTOR3(-135.0, 5.0f, -85.0f));
	ItemRation::Create(D3DXVECTOR3(140.0, 5.0f, 140.0f));

	m_ItemUI = ItemUIRation::Create(D3DXVECTOR3(50.0f, 460.0f,0.0f));

	// HP�Q�[�WUI
	Sprite2D::Create(D3DXVECTOR3(25.0f,25.0f,0.0f),D3DXVECTOR2(250.0f,50.0f),TEXTURE_PATH"GAME/GuageBar_Frame.png", D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),5);

	// Life����
	Sprite2D::Create(D3DXVECTOR3(25.0f,60.0f,0.0f),D3DXVECTOR2(65.0f,30.0f),TEXTURE_PATH"GAME/Life_logo.png", D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),5);


	// ������
	m_GameClear = false;
	m_GameOver = false;
	m_SceneChangeFlag = false;
}

void GameScene::Uninitialize(void)
{
	m_KeyBoard = NULL;
	m_Sound = NULL;
	m_Player = NULL;
	m_MeshField = NULL;
	m_Goal = NULL;
	m_GameClear = false;
	m_GameOver = false;
	m_SceneChangeFlag = false;

	Object::ReleaseAll(); // �S�I�u�W�F�N�g�̉��
}

void GameScene::Update(void)
{
	SceneChange(); // �V�[����ς���

	Object::UpdateAll(); //	�S�I�u�W�F�N�g�̍X�V
}

void GameScene::Draw(void)
{
	Object::DrawAll(); // �S�I�u�W�F�N�g�̕`��
}

/*-----------------------------------------------------------------------------
Function:   void GameScene::SceneChange(void)
Overview:   �V�[����ς���
-----------------------------------------------------------------------------*/
void GameScene::SceneChange(void)
{

#ifdef _DEBUG
	if (m_KeyBoard->GetKeyTrigger(DIK_SPACE))
	{
		Fade::SetFade(Fade::FADE_OUT, new TitleScene);

		Game::GetInstance()->GetCamera()->SetState(new CameraStateNull);

#ifndef ENABLE_SOUND
		m_Sound->Stop(SoundDirectX::SOUND_BGM_GAMESCENE);
#endif
	}
#endif

	if(!m_SceneChangeFlag)
	{
		if(m_GameClear)
		{
			Fade::SetFade(Fade::FADE_OUT, new GameClearScene);

			Game::GetInstance()->GetCamera()->SetState(new CameraStateNull);

#ifndef ENABLE_SOUND
		m_Sound->Stop(SoundDirectX::SOUND_BGM_GAMESCENE);
#endif

			m_GameClear = false;
			m_SceneChangeFlag = true;
		}
		else if(m_GameOver)
		{
			Fade::SetFade(Fade::FADE_OUT, new GameOverScene);

			Game::GetInstance()->GetCamera()->SetState(new CameraStateNull);

#ifndef ENABLE_SOUND
		m_Sound->Stop(SoundDirectX::SOUND_BGM_GAMESCENE);
#endif

			m_GameOver = false;
			m_SceneChangeFlag = true;
		}
	}
}
