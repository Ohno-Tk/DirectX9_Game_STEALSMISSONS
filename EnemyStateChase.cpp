/*=============================================================================

�G���( �ǐ� )[ EnemyStateChase.cpp ]

-------------------------------------------------------------------------------

��  Create
2017/11/22
=============================================================================*/

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "FrameworkBase\Common.h"
#include "FrameworkBase\Debug.h"
#include "FrameworkBase\RendererDirectX.h"
#include "FrameworkBase\Mathematics.h"
#include "FrameworkBase\Game.h"
#include "FrameworkBase\SoundDirectX.h"
#include "GameScene.h"
#include "Object.h"
#include "Player.h"
#include "Enemy.h"
#include "EnemyStateAttack.h"
#include "EnemyStateLookOutOver.h"
#include "EnemyStatePatrol.h"
#include "EnemyStateChase.h"


EnemyStateChase::EnemyStateChase(Enemy* owner):m_Owner(owner)
{
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_Owner->SetHeadMarkActive(true);
	m_Owner->SetHeadMarkTextureChange(TEXTURE_PATH"GAME/Mark_Find.png");

	Debug::Log("�G : �ǐՏ��");

#ifndef ENABLE_SOUND
	Game::GetInstance()->GetSound()->Play(SoundDirectX::SOUND_SE_FOUND);
#endif
}

void EnemyStateChase::Update(D3DXVECTOR3 position)
{

	m_Owner->SetMotionIndex(1);

	if(m_Owner->AttackRangeCollision(position, m_Owner->GetVisionAngle(), m_Owner->GetAttackRange()))
	{// �U���͈͔̔���

		m_Owner->SetState(new EnemyStateAttack(m_Owner));
	}
	else if(m_Owner->DistanceWithinCollision(m_Owner->GetVisionDistance() * 1.1f))
	{
		// ������������
		m_Owner->SetState(new EnemyStateLookOutOver(m_Owner, EnemyStateLookOutOver::LOST));
	}
	else
	{
		Chase(position);
	}
}

void EnemyStateChase::Chase(D3DXVECTOR3 position)
{

	D3DXVECTOR3 enemyToPlayerVector = GameScene::GetPlayer()->GetPosition() - position;

	D3DXVec3Normalize(&enemyToPlayerVector, &enemyToPlayerVector);

	float angle = atan2(enemyToPlayerVector.x, enemyToPlayerVector.z);
	
	m_Move = enemyToPlayerVector * 0.5f;
	position += m_Move;

	m_Owner->SetPosition(position);
	m_Owner->SetRotation(D3DXVECTOR3(0.0f, D3DXToDegree(angle + D3DX_PI), 0.0f));
}