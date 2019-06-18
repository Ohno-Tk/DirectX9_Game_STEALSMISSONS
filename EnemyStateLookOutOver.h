/*=============================================================================

ìGèÛë‘( å©ìnÇ∑ )[ EnemyStateLookOutOver.h ]

-------------------------------------------------------------------------------
Å°  Author
Ohno Takuya

Å°  Create
2017/11/28
=============================================================================*/

#ifndef _ENEMYSTATELOOKOUTOVER_H_
#define _ENEMYSTATELOOKOUTOVER_H_

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
class EnemyStateLookOutOver:public HumanState
{
public:
	enum NEXT
	{
		LOST = 0,
		LOOK_OUT,
	};

	EnemyStateLookOutOver(Enemy* owner, NEXT next);

	void Uninitialize(void)override;
	void Update(D3DXVECTOR3 position)override;

private:
	void LookOutOver(void);

private:
	NEXT m_Next;

	Enemy* m_Owner; // èäóLé“

	D3DXVECTOR3 m_NowRotation;

	int m_CountInterpolation; // ï‚ä‘ÇÃÉJÉEÉìÉ^
	int m_CountLookOut; // å©ìnÇ∑ÉJÉEÉìÉg

	D3DXVECTOR3 m_LookRotation[3]; // å©ìnÇ∑äpìx
};

#endif
