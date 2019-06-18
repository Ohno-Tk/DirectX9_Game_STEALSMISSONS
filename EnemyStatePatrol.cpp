/*=============================================================================

敵状態( 巡回 )[ EnemyStatePatrol.cpp ]

-------------------------------------------------------------------------------
■  Author
Ohno Takuya

■  Create
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
#include "EnemyStateLookOutOver.h"
#include "EnemyStateLookBack.h"
#include "EnemyStateChase.h"
#include "EnemyStatePatrol.h"


EnemyStatePatrol::EnemyStatePatrol(Enemy* owner)
{
	m_Owner = owner;

	m_LinearCnt = m_Owner->GetCountLinear(); //	補間カウンタ
	m_FrameTimeCount = 0; //	フレーム時間カウント
	m_NowRotation = m_Owner->GetNowRotation();

	m_NumLinear = m_Owner->GetNumLinear();

	m_Linear = new Enemy::LINEAR[m_NumLinear];

	for(unsigned int i = 0; i < (unsigned int)m_NumLinear; i++)
	{
		m_Linear[i] = m_Owner->GetLinearStruct(i);
	}

	m_ControlPoint = m_Owner->GetPosition();

	m_InverseFrontVector = m_Owner->GetFrontVector();
	m_InverseFrontVector *= -1;

	Debug::Log("敵 : 巡回状態");
}

void EnemyStatePatrol::Uninitialize(void)
{
	SAFE_ARRAYDELETE(m_Linear);
}

void EnemyStatePatrol::Update(D3DXVECTOR3 position)
{
	m_Owner->SetMotionIndex(1);

	if(m_Owner->VisionRangeCollision(position, m_Owner->GetVisionAngle(), m_Owner->GetVisionDistance()))
	{ // 視界の判定
		m_Owner->SetState(new EnemyStateChase(m_Owner));
	}
	else
	{
		Patrol(&position);
	}
}

void EnemyStatePatrol::Patrol(D3DXVECTOR3* position)
{
	int LinearNext = (m_LinearCnt + 1) % m_NumLinear;

	CubicExpressionInterpolation cubic(m_FrameTimeCount);
	cubic.Interpolation(position, m_ControlPoint, m_Linear[LinearNext].ControlPoint, m_Linear[m_LinearCnt].FrameTime);


	m_FrameTimeCount++;

	m_Owner->SetPosition(*position);

	if (m_Linear[m_LinearCnt].FrameTime < m_FrameTimeCount)
	{ // フレーム数を超えたら
		
		m_NowRotation = m_Owner->GetRotation().y;
		
		m_FrameTimeCount = 0;
		m_LinearCnt++;
		
		if (m_NumLinear <= m_LinearCnt)
		{	//	規定数を超えたら
			m_LinearCnt = 0;
		}

		if (m_Linear[m_LinearCnt].Rot < 0)
		{
			m_NowRotation *= -1;
		}

		m_Owner->SetCountNumLinear(m_LinearCnt);
		m_Owner->SetNowRotation(m_NowRotation);
		m_Owner->SetState(new EnemyStateLookOutOver(m_Owner, EnemyStateLookOutOver::LOOK_OUT));
	}
}