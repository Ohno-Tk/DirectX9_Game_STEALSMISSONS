/*=============================================================================

�G���( ����_�։�] )[ EnemyStateControlPointRotation.cpp ]

-------------------------------------------------------------------------------

��  Create
2017/12/04
=============================================================================*/

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "FrameworkBase\RendererDirectX.h"
#include "FrameworkBase\Common.h"
#include "FrameworkBase\Debug.h"
#include "FrameworkBase\Mathematics.h"
#include "Enemy.h"
#include "EnemyStateChase.h"
#include "EnemyStatePatrol.h"
#include "EnemyStateControlPointMove.h"
#include "EnemyStateControlPointRotation.h"

/*-----------------------------------------------------------------------------
Macro
-----------------------------------------------------------------------------*/
#define INTERPOLATION_TIME (70)


EnemyStateControlPointRotation::EnemyStateControlPointRotation(Enemy* owner)
{
	m_Owner = owner;

	m_CountInterpolation = 0;

	m_NowRotation = m_Owner->GetRotation().y;
	if(m_NowRotation < -180)
	{
		m_NowRotation += 360;
	}
	else if(m_NowRotation > 180)
	{
		m_NowRotation -= 360;
	}
	m_Owner->SetRotation(D3DXVECTOR3(0.0f, m_NowRotation, 0.0f));


	// ����_�ւ̊p�x�v�Z
	m_CountLinear = m_Owner->GetCountLinear();
	D3DXVECTOR3 controlPoint = m_Owner->GetLinearStruct(m_CountLinear).ControlPoint;
	D3DXVECTOR3 enemyToControlPoint = controlPoint - m_Owner->GetPosition();
	D3DXVec3Normalize(&enemyToControlPoint, &enemyToControlPoint);
	float digree = atan2(enemyToControlPoint.x, enemyToControlPoint.z);
	m_Angle = D3DXToDegree(digree + D3DX_PI);
	if(m_Angle < -180)
	{
		m_Angle += 360;
	}
	else if(m_Angle > 180)
	{
		m_Angle -= 360;
	}

	Debug::Log("�G : ����_�։�]���");
}

void EnemyStateControlPointRotation::Update(D3DXVECTOR3 position)
{
	if(m_Owner->VisionRangeCollision(position, m_Owner->GetVisionAngle(), m_Owner->GetVisionDistance()))
	{ // ���E�̔���
		m_Owner->SetState(new EnemyStateChase(m_Owner));
	}
	else
	{
		RotationControlPoint();
	}
}

void EnemyStateControlPointRotation::RotationControlPoint(void)
{
	D3DXVECTOR3 Rot = m_Owner->GetRotation();

	CubicExpressionInterpolation cubic(m_CountInterpolation);
	cubic.Interpolation(&Rot.y, m_NowRotation, m_Angle, INTERPOLATION_TIME);

	m_CountInterpolation++;

	m_Owner->SetRotation(Rot);

	if(m_CountInterpolation > INTERPOLATION_TIME)
	{
		m_Owner->SetHeadMarkActive(false);

		m_Owner->SetCountNumLinear(m_CountLinear);
		m_Owner->SetState(new EnemyStateControlPointMove(m_Owner));
	}
}