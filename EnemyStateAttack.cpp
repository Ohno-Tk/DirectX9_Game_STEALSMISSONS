/*=============================================================================

�G���( �U�� )[ EnemyStateAttack.cpp ]

-------------------------------------------------------------------------------

��  Create
2017/11/20
=============================================================================*/

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "FrameworkBase\Common.h"
#include "FrameworkBase\Debug.h"
#include "FrameworkBase\RendererDirectX.h"
#include "Enemy.h"
#include "EnemyStateChase.h"
#include "EnemyStateAttack.h"
#include "EnemyStatePatrol.h"
#include "EnemyStateAttackCoolTime.h"


EnemyStateAttack::EnemyStateAttack(Enemy* owner)
{
	m_Owner = owner;

	Debug::Log("�G : �U�����");
}

void EnemyStateAttack::Uninitialize(void){}

void EnemyStateAttack::Update(D3DXVECTOR3 position)
{
	m_Owner->SetMotionIndex(2);
	if(m_Owner->AttackCollision(position))
	{
		m_Owner->SetState(new EnemyStateAttackCoolTime(m_Owner));
	}
	else
	{
		m_Owner->SetState(new EnemyStateChase(m_Owner));
	}
}