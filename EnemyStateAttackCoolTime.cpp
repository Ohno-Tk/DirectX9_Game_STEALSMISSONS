/*=============================================================================

“Gó‘Ô( UŒ‚‘Ò‚¿ŽžŠÔ )[ EnemyStateAttackCoolTime.cpp ]

-------------------------------------------------------------------------------
¡  Author
Ohno Takuya

¡  Create
2017/11/24
=============================================================================*/

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "FrameworkBase\Common.h"
#include "FrameworkBase\Debug.h"
#include "FrameworkBase\RendererDirectX.h"
#include "FrameworkBase\Mathematics.h"
#include "GameScene.h"
#include "Enemy.h"
#include "EnemyStateChase.h"
#include "EnemyStatePatrol.h"
#include "EnemyStateAttack.h"
#include "EnemyStateLookBack.h"
#include "EnemyStateLookOutOver.h"
#include "EnemyStateAttackCoolTime.h"

/*-----------------------------------------------------------------------------
Macro
-----------------------------------------------------------------------------*/
#define COOL_TIME ( 180 )


EnemyStateAttackCoolTime::EnemyStateAttackCoolTime(Enemy* owner):m_Owner(owner)
{
	m_CoolTimeCount = 0;

	Debug::Log("“G : UŒ‚‘Ò‚¿ó‘Ô");
}

void EnemyStateAttackCoolTime::Update(D3DXVECTOR3 position)
{
	m_CoolTimeCount++;

	if(m_CoolTimeCount > COOL_TIME)
	{
		m_CoolTimeCount = 0;

		if(m_Owner->AttackRangeCollision(position, m_Owner->GetVisionAngle(), m_Owner->GetVisionDistance()))
		{
			m_Owner->SetState(new EnemyStateAttack(m_Owner));
		}
		else if(m_Owner->VisionRangeCollision(position, m_Owner->GetVisionAngle(), m_Owner->GetVisionDistance()) == false)
		{
			m_Owner->SetHeadMarkActive(false);
			m_Owner->SetState(new EnemyStateLookOutOver(m_Owner, EnemyStateLookOutOver::LOST));
		}
	}
}