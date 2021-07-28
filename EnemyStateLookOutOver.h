/*=============================================================================

�G���( ���n�� )[ EnemyStateLookOutOver.h ]

-------------------------------------------------------------------------------

��  Create
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

	Enemy* m_Owner; // ���L��

	D3DXVECTOR3 m_NowRotation;

	int m_CountInterpolation; // ��Ԃ̃J�E���^
	int m_CountLookOut; // ���n���J�E���g

	D3DXVECTOR3 m_LookRotation[3]; // ���n���p�x
};

#endif
