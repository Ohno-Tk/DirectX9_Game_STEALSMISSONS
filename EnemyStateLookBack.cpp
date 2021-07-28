/*=============================================================================

�G���( �U��Ԃ� )[ EnemyStateLookBack.cpp ]

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
#include "FrameworkBase\Mathematics.h"
#include "GameScene.h"
#include "Enemy.h"
#include "EnemyStatePatrol.h"
#include "EnemyStateChase.h"
#include "EnemyStateLookBack.h"


EnemyStateLookBack::EnemyStateLookBack(Enemy* owner)
{
	m_Owner = owner;

	m_LinearCnt = m_Owner->GetCountLinear(); //	��ԃJ�E���^
	m_WaitCount = 0;
	m_NowRotation = m_Owner->GetNowRotation();

	m_NumLinear = m_Owner->GetNumLinear();

	m_Linear = new Enemy::LINEAR[m_NumLinear];

	for(unsigned int i = 0; i < (unsigned int)m_NumLinear; i++)
	{
		m_Linear[i] = m_Owner->GetLinearStruct(i);
	}

	Debug::Log("�G : �U��Ԃ���");
}

void EnemyStateLookBack::Uninitialize(void)
{
	SAFE_ARRAYDELETE(m_Linear);
}

void EnemyStateLookBack::Update(D3DXVECTOR3 position)
{
	m_Owner->SetMotionIndex(0);

	if(m_Owner->VisionRangeCollision(position, m_Owner->GetVisionAngle(), m_Owner->GetVisionDistance()))
	{ // ���E�̔���
		m_Owner->SetState(new EnemyStateChase(m_Owner));
	}
	else
	{
		LookBack();
	}
}

void EnemyStateLookBack::LookBack(void)
{
	D3DXVECTOR3 Rot = m_Owner->GetRotation();

	LinearInterpolation Linear(m_WaitCount);
	Linear.Interpolation(&Rot.y, m_NowRotation, m_Linear[m_LinearCnt].Rot, m_Linear[m_LinearCnt].WaitTime);

	m_WaitCount++;

	m_Owner->SetRotation(Rot);

	if(m_WaitCount > m_Linear[m_LinearCnt].WaitTime)
	{
		m_Owner->SetNowRotation(m_NowRotation);
		m_Owner->SetState(new EnemyStatePatrol(m_Owner));
	}
}