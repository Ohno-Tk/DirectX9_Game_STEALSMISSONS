/*=============================================================================

人型状態( ダメージ )[ HumanStateDamage.h ]

-------------------------------------------------------------------------------
■  Author
Ohno Takuya

■  Create
2017/11/19
=============================================================================*/

#ifndef _PLAYERSTATEDAMAGE_H_
#define _PLAYERSTATEDAMAGE_H_

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "HumanState.h"

/*-----------------------------------------------------------------------------

-----------------------------------------------------------------------------*/
class Human;

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class HumanStateDamage:public HumanState
{
public:
	HumanStateDamage(Human* owner, int damegeCount):m_Owner(owner),m_DamegeCount(damegeCount), m_Active(true){}

	void Uninitialize(void)override{}
	void Update(D3DXVECTOR3 position)override;

private:
	int m_DamegeCount;

	bool m_Active;

	Human* m_Owner; // 所有者
};

#endif
