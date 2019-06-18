/*=============================================================================

�G���( �o�H�T�� )[ EnemyStateRouteSearch.h ]

-------------------------------------------------------------------------------
��  Author
Ohno Takuya

��  Create
2017/12/04
=============================================================================*/

#ifndef _ENEMYSTATEROUTESEARCH_H_
#define _ENEMYSTATEROUTESEARCH_H_

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "HumanState.h"

/*-----------------------------------------------------------------------------

-----------------------------------------------------------------------------*/
class Enemy;

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class EnemyStateRouteSearch:public HumanState
{
public:
	EnemyStateRouteSearch(Enemy* owner);

	void Uninitialize(void)override{}
	void Update(D3DXVECTOR3 position)override;

private:
	Enemy* m_Owner; // ���L��

	int m_NumLinear;
	int m_CountLinear;
	float m_Length;
};

#endif
