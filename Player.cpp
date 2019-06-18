/*=============================================================================

プレイヤー[ Player.cpp ]

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
#include "FrameworkBase\SoundDirectX.h"
#include "FrameworkBase\ModelManagerDirectX.h"
#include "FrameworkBase\InputDirectX.h"
#include "GameScene.h"
#include "Object.h"
#include "StencilShadow.h"
#include "HitPointGauge.h"
#include "ItemUI.h"
#include "MeshWall.h"
#include "HumanStateDamage.h"
#include "Player.h"
#include "Weapon.h"

/*-----------------------------------------------------------------------------
Macro
-----------------------------------------------------------------------------*/
#define OBJECT_MOTION_PATH (MOTION_PATH"Player.txt")
#define DAMAGE_DANGER_PERCENTAGE ( 50 )
#define DAMAGE_COUNT ( 30 )


Player::Player(int Priolity):Human(Priolity)
{
	m_OldPosision = D3DXVECTOR3(0.0f,0.0f,0.0f); // 前回の座標
	m_SphereRadius = 9.0f; // 球判定時のの半径
	m_Move = 1.0f;

	m_Shadow = NULL;
}

/*-----------------------------------------------------------------------------
Function:   Player* Player::Create(D3DXVECTOR3 position, float rotation)
Parameter:  D3DXVECTOR3 position
              座標
		    float rotation
			  回転
Overview:   生成
-----------------------------------------------------------------------------*/
Player* Player::Create(D3DXVECTOR3 position, float rotation)
{
	auto object = new Player;

	object->SetPosition(position);

	object->SetRotation(D3DXVECTOR3(0.0f, rotation, 0.0f));

	object->SetTextFileName(OBJECT_MOTION_PATH);

	object->Initialize();

	return object;
}

void Player::Initialize(void)
{
	Human::Initialize();
	
	m_Shadow = StencilShadow::Create(MODEL_PATH"StecilShadow.x"); // 影の生成

	m_HitPoint = HitPointGauge::Create(D3DXVECTOR3(25.0f, 25.0f, 0.0f), D3DXVECTOR2(250.0f,50.0f),100);

	m_XInput = Game::GetInstance()->GetXInput();

	Human::SetObjeType(OBJECT_TYPE_PLAYER);
}

void Player::Uninitialize(void)
{
	Human::Uninitialize();

	m_Shadow = NULL;
	m_HitPoint = NULL;
}

void Player::Update(void)
{
	D3DXVECTOR3* position = Object::GetPositionPointer();
	D3DXMATRIX matirx = Motion::GetPartsMatrix(8);

	Human::Update();

	m_OldPosision = *position;

	Control(position);
	
	Collision(position);// 衝突判定

	m_Shadow->SetPosition(*position);
}

void Player::Draw(void)
{
	Human::Draw();
}

void Player::Control(D3DXVECTOR3* position)
{
	DirectXKeyboard* keyboard = Game::GetInstance()->GetKeyboard();
	D3DXVECTOR3 rotation = Human::GetRotation();

	float AnalogX = m_XInput->GetAnalogValue(XInput::CONTROLLER_1, XInput::LEFT).x;
	float AnalogY = m_XInput->GetAnalogValue(XInput::CONTROLLER_1, XInput::LEFT).y;

	//	移動処理
	if (keyboard->GetKeyPress(DIK_W) && keyboard->GetKeyPress(DIK_D) || AnalogX > 0.8f && AnalogY > 0.8f)
	{
		rotation.y = 225.0f;

		position->x -= sinf(D3DXToRadian(rotation.y))*m_Move;
		position->z -= cosf(D3DXToRadian(rotation.y))*m_Move;

		Human::SetMotionIndex(1);
	}
	else if (keyboard->GetKeyPress(DIK_W) && keyboard->GetKeyPress(DIK_A) || AnalogX < -0.8f && AnalogY > 0.8f)
	{
		rotation.y = 135.0f;

		position->x -= sinf(D3DXToRadian(rotation.y))*m_Move;
		position->z -= cosf(D3DXToRadian(rotation.y))*m_Move;

		Human::SetMotionIndex(1);
	}
	else if (keyboard->GetKeyPress(DIK_S) && keyboard->GetKeyPress(DIK_D) || AnalogX > 0.8f && AnalogY < -0.8f)
	{
		rotation.y = 315.0f;

		position->x -= sinf(D3DXToRadian(rotation.y))*m_Move;
		position->z -= cosf(D3DXToRadian(rotation.y))*m_Move;

		Human::SetMotionIndex(1);
	}
	else if (keyboard->GetKeyPress(DIK_S) && keyboard->GetKeyPress(DIK_A) || AnalogX < -0.8f && AnalogY < -0.8f)
	{
		rotation.y = 45.0f;

		position->x -= sinf(D3DXToRadian(rotation.y))*m_Move;
		position->z -= cosf(D3DXToRadian(rotation.y))*m_Move;

		Human::SetMotionIndex(1);
	}
	else if (keyboard->GetKeyPress(DIK_W) || AnalogY > 0.8f)
	{
		rotation.y = 180.0f;

		position->x -= sinf(D3DXToRadian(rotation.y))*m_Move;
		position->z -= cosf(D3DXToRadian(rotation.y))*m_Move;

		Human::SetMotionIndex(1);
	}
	else if (keyboard->GetKeyPress(DIK_S) || AnalogY < -0.8f)
	{
		rotation.y = 0.0f;

		position->x -= sinf(D3DXToRadian(rotation.y))*m_Move;
		position->z -= cosf(D3DXToRadian(rotation.y))*m_Move;

		Human::SetMotionIndex(1);
	}
	else if (keyboard->GetKeyPress(DIK_D) || AnalogX > 0.8f)
	{
		rotation.y = 270.0f;

		position->x -= sinf(D3DXToRadian(rotation.y))*m_Move;
		position->z -= cosf(D3DXToRadian(rotation.y))*m_Move;

		Human::SetMotionIndex(1);
	}
	else if (keyboard->GetKeyPress(DIK_A) || AnalogX < -0.8f)
	{
		rotation.y = 90.0f;

		position->x -= sinf(D3DXToRadian(rotation.y))*m_Move;
		position->z -= cosf(D3DXToRadian(rotation.y))*m_Move;

		Human::SetMotionIndex(1);
	}
	else if (keyboard->GetKeyRelease(DIK_W) || keyboard->GetKeyRelease(DIK_S) || keyboard->GetKeyRelease(DIK_A) || keyboard->GetKeyRelease(DIK_D) || AnalogX == 0.0f && AnalogY == 0.0f)
	{
		Human::SetMotionIndex(0);
	}

	Human::SetRotation(rotation);

	// アイテム使用
	if (keyboard->GetKeyTrigger(DIK_I) || Game::GetInstance()->GetXInput()->GetKeyTrigger(XInput::CONTROLLER_1, XINPUT_GAMEPAD_Y))
	{
		GameScene::GetItemUI()->Use();
	}
}

/*-----------------------------------------------------------------------------
Function:   void Player::Collision(D3DXVECTOR3* position)
Parameter:  D3DXVECTOR3 position
              座標
Overview:   衝突判定
-----------------------------------------------------------------------------*/
void Player::Collision(D3DXVECTOR3* position)
{
	//	壁との衝突判定
	MeshWall* MeshWall00 = GameScene::GetMeshWall(0);
	MeshWall* MeshWall01 = GameScene::GetMeshWall(1);
	MeshWall* MeshWall02 = GameScene::GetMeshWall(2);
	MeshWall* MeshWall03 = GameScene::GetMeshWall(3);

	if (position->x < MeshWall00->GetPosition().x)
	{
		*position = m_OldPosision;
	}

	if (MeshWall01->GetPosition().x < position->x){ *position = m_OldPosision; }

	if (MeshWall02->GetPosition().z < position->z)
	{
		*position = m_OldPosision;
	}

	if (position->z < MeshWall03->GetPosition().z){ *position = m_OldPosision; }

}

/*-----------------------------------------------------------------------------
Function:   bool Player::AttackHit(int damageValue)
Parameter:  int damageValue
              攻撃力
Overview:   攻撃ヒット
-----------------------------------------------------------------------------*/
bool Player::AttackHit(int damageValue)
{
	int hitPoint = m_HitPoint->GetHitPoint();

	hitPoint -= damageValue;

	m_HitPoint->SetHitPoint(hitPoint);


	if(m_HitPoint->GetHitPointRate() < DAMAGE_DANGER_PERCENTAGE)
	{
		m_HitPoint->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	}

	if(hitPoint <= 0)
	{
		hitPoint = 0;

		GameScene::GameOver();
		return true;
	}

	Human::SetState(new HumanStateDamage(this, DAMAGE_COUNT));

	return false;
}

/*-----------------------------------------------------------------------------
体力回復
-----------------------------------------------------------------------------*/
void Player::HitPointRecovery(int recoveryValue)
{
#ifndef ENABLE_SOUND
	Game::GetInstance()->GetSound()->Play(SoundDirectX::SOUND_SE_HEAL);
#endif
	int hitPoint = m_HitPoint->GetHitPoint();

	hitPoint += recoveryValue;

	if(hitPoint >= m_HitPoint->GetMaxHitPoint())
	{
		hitPoint = m_HitPoint->GetMaxHitPoint();
	}

	m_HitPoint->SetHitPoint(hitPoint);

	if(m_HitPoint->GetHitPointRate() > DAMAGE_DANGER_PERCENTAGE)
	{
		m_HitPoint->SetColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
	}
}

D3DXVECTOR3 Player::GetHeadPosition(void)
{
	return Human::GetPartsPosition(1);
}

int Player::GetHitPoint(void)
{
	return m_HitPoint->GetHitPoint();
}

int Player::GetMaxHitPoint(void)
{
	return m_HitPoint->GetMaxHitPoint();
}