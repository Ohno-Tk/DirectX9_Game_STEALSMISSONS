/*=============================================================================

�G���( ���n�� )[ EnemyStateLookOutOver.cpp ]

-------------------------------------------------------------------------------

��  Create
2017/11/28
=============================================================================*/

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "FrameworkBase\RendererDirectX.h"
#include "FrameworkBase\Common.h"
#include "FrameworkBase\Debug.h"
#include "FrameworkBase\Mathematics.h"
#include "Enemy.h"
#include "EnemyStateLookBack.h"
#include "EnemyStateChase.h"
#include "EnemyStateRouteSearch.h"
#include "EnemyStateLookOutOver.h"

/*-----------------------------------------------------------------------------
Macro
-----------------------------------------------------------------------------*/
#define NUM_LOOKOVER (3)
#define INTERPOLATION_TIME (50)

/*-----------------------------------------------------------------------------
Namespace
-----------------------------------------------------------------------------*/
using namespace std;


EnemyStateLookOutOver::EnemyStateLookOutOver(Enemy* owner, NEXT next)
{
	m_Owner = owner;

	m_Next = next;

	m_CountInterpolation = 0;
	m_CountLookOut = 0;

	m_NowRotation = m_Owner->GetRotation();

	m_LookRotation[0] = D3DXVECTOR3(m_NowRotation.x, m_NowRotation.y - 45, m_NowRotation.z);
	m_LookRotation[1] = D3DXVECTOR3(m_NowRotation.x, m_NowRotation.y + 45, m_NowRotation.z);
	m_LookRotation[2] = D3DXVECTOR3(m_NowRotation.x, m_NowRotation.y,      m_NowRotation.z);


	Debug::Log("�G : ���n�����");
}

void EnemyStateLookOutOver::Uninitialize(void)
{
}

void EnemyStateLookOutOver::Update(D3DXVECTOR3 position)
{
	if(m_Owner->VisionRangeCollision(position, m_Owner->GetVisionAngle(), m_Owner->GetVisionDistance()))
	{ // ���E�̔���
		m_Owner->SetState(new EnemyStateChase(m_Owner));
	}
	else
	{
		if(m_Next == LOST)
		{
			m_Owner->SetHeadMarkActive(true);
			m_Owner->SetHeadMarkTextureChange(TEXTURE_PATH"GAME/Mark_Question.png");
		}


		LookOutOver();
	}	
}

void EnemyStateLookOutOver::LookOutOver(void)
{
	m_Owner->SetMotionIndex(0);

	D3DXVECTOR3 rotation = m_Owner->GetRotation();

	CubicExpressionInterpolation cubic(m_CountInterpolation);
	cubic.Interpolation(&rotation, m_NowRotation, m_LookRotation[m_CountLookOut], INTERPOLATION_TIME);

	m_CountInterpolation++;

	m_Owner->SetRotation(rotation);

	if (m_CountInterpolation > INTERPOLATION_TIME)
	{ // �t���[�����𒴂�����
		
		m_NowRotation = m_Owner->GetRotation();
		m_CountInterpolation = 0;
		m_CountLookOut++;

		if(m_CountLookOut >= NUM_LOOKOVER)
		{
			m_CountLookOut = 0;

			switch(m_Next)
			{
			case LOST:
				m_Owner->SetState(new EnemyStateRouteSearch(m_Owner));
				break;
			case LOOK_OUT:
				m_Owner->SetState(new EnemyStateLookBack(m_Owner));
				break;
			}
		}
	}
}