/*=============================================================================

�G���( ����_�ֈړ� )[ EnemyStateControlPointMove.cpp ]

-------------------------------------------------------------------------------

��  Create
2017/12/05
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
#include "EnemyStateChase.h"
#include "EnemyStateControlPointMove.h"

/*-----------------------------------------------------------------------------

-----------------------------------------------------------------------------*/
EnemyStateControlPointMove::EnemyStateControlPointMove(Enemy* owner)
{
	m_Owner = owner;

	m_FrameTimeCount = 0; //	�t���[�����ԃJ�E���g
	m_NowRotation = m_Owner->GetNowRotation();

	m_NumLinear = m_Owner->GetNumLinear();

	m_CountLinear = m_Owner->GetCountLinear();
	m_Linear = m_Owner->GetLinearStruct(m_CountLinear);
/*	m_Linear = new Enemy::LINEAR[m_NumLinear];

	for(unsigned int i = 0; i < (unsigned int)m_NumLinear; i++)
	{
		m_Linear[i] = m_Owner->GetLinearStruct(i);
	}
*/
	m_ControlPoint = m_Owner->GetPosition();

	m_InverseFrontVector = m_Owner->GetFrontVector();
	m_InverseFrontVector *= -1;

	Debug::Log("�G : ����_�ֈړ����");
}

void EnemyStateControlPointMove::Uninitialize(void)
{
//	SAFE_ARRAYDELETE(m_Linear);
}

void EnemyStateControlPointMove::Update(D3DXVECTOR3 position)
{
	m_Owner->SetMotionIndex(1);

	if(m_Owner->VisionRangeCollision(position, m_Owner->GetVisionAngle(), m_Owner->GetVisionDistance()))
	{ // ���E�̔���
		m_Owner->SetState(new EnemyStateChase(m_Owner));
	}
	else
	{
		ControlPointMove(&position);
	}
}

void EnemyStateControlPointMove::ControlPointMove(D3DXVECTOR3* position)
{
	//HermiteInterpolation hermite(m_FrameTimeCount);
	//hermite.Interpolation(position, m_ControlPoint, m_InverseFrontVector, m_Linear.ControlPoint, m_Linear.ControlVectorNext, m_Linear.FrameTime);
	CubicExpressionInterpolation cubic(m_FrameTimeCount);
	cubic.Interpolation(position, m_ControlPoint, m_Linear.ControlPoint, m_Linear.FrameTime);


	m_FrameTimeCount++;

	m_Owner->SetPosition(*position);

	if (m_Linear.FrameTime < m_FrameTimeCount)
	{ // �t���[�����𒴂�����
		
		m_NowRotation = m_Owner->GetRotation().y;
		
		m_FrameTimeCount = 0;
		
		if (m_NumLinear <= m_CountLinear)
		{	//	�K�萔�𒴂�����
			m_CountLinear = 0;
		}

		if (m_Linear.Rot < 0)
		{
			m_NowRotation *= -1;
		}

		m_Owner->SetCountNumLinear(m_CountLinear);
		m_Owner->SetNowRotation(m_NowRotation);
		m_Owner->SetState(new EnemyStateLookOutOver(m_Owner, EnemyStateLookOutOver::LOOK_OUT));
	}
}