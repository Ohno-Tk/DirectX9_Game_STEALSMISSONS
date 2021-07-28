/*=============================================================================

�G���( �o�H�T�� )[ EnemyStateRouteSearch.cpp ]

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
#include "Enemy.h"
#include "EnemyStateControlPointRotation.h"
#include "EnemyStateRouteSearch.h"

/*-----------------------------------------------------------------------------

-----------------------------------------------------------------------------*/
EnemyStateRouteSearch::EnemyStateRouteSearch(Enemy* owner)
{
	m_Owner = owner;

	m_CountLinear = 0;
	m_Length = 0.0f;

	m_NumLinear = m_Owner->GetNumLinear();
	D3DXVECTOR3 controlPoint = m_Owner->GetLinearStruct(0).ControlPoint;
	D3DXVECTOR3 controlPointToEnemyVector = controlPoint - m_Owner->GetPosition();
	m_Length = D3DXVec3Length(&controlPointToEnemyVector);

	Debug::Log("�G : ����_�̌������");
}

void EnemyStateRouteSearch::Update(D3DXVECTOR3 position)
{
	// ��ԋ߂��Ƃ��������
	for(int i = 0; i < m_NumLinear; i++)
	{
		D3DXVECTOR3 controlPoint = m_Owner->GetLinearStruct(i).ControlPoint;
		D3DXVECTOR3 controlPointToEnemyVector = controlPoint - m_Owner->GetPosition();
		float length = D3DXVec3Length(&controlPointToEnemyVector);

		if(length < m_Length)
		{
			m_CountLinear = i;
			m_Length = length;
		}
	}

	m_Owner->SetCountNumLinear(m_CountLinear);
	m_Owner->SetState(new EnemyStateControlPointRotation(m_Owner));
}