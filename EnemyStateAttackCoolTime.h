/*=============================================================================

ìGèÛë‘( çUåÇë“Çøéûä‘ )[ EnemyStateAttackCoolTime.h ]

-------------------------------------------------------------------------------
Å°  Author
Ohno Takuya

Å°  Create
2017/11/24
=============================================================================*/

#ifndef _ENEMYSTATEATTACKCOOLTIME_H_
#define _ENEMYSTATEATTACKCOOLTIME_H_

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
class EnemyStateAttackCoolTime:public HumanState
{
public:
	EnemyStateAttackCoolTime(Enemy* owner);

	void Uninitialize(void)override{}
	void Update(D3DXVECTOR3 position)override;

private:
	Enemy* m_Owner; // èäóLé“

	int m_CoolTimeCount;
};

#endif
