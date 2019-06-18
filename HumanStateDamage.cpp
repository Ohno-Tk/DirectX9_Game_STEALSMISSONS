/*=============================================================================

人型状態( ダメージ )[ HumanStateDamage.cpp ]

-------------------------------------------------------------------------------
■  Author
Ohno Takuya

■  Create
2017/11/19
=============================================================================*/

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "FrameworkBase\RendererDirectX.h"
#include "FrameworkBase\Common.h"
#include "FrameworkBase\Debug.h"
#include "Human.h"
#include "Player.h"
#include "HumanStateDamage.h"

/*-----------------------------------------------------------------------------

-----------------------------------------------------------------------------*/
void HumanStateDamage::Update(D3DXVECTOR3 position)
{
	m_DamegeCount--;
	m_Active ^= 1;
	m_Owner->SetActive(m_Active);

	if(m_DamegeCount <= 0)
	{
		m_DamegeCount = 0;
		m_Owner->SetActive(true);
		m_Owner->SetState(new HumanStateNull);
	}
}