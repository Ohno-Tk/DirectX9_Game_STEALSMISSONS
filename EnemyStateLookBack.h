/*=============================================================================

�G���( �U��Ԃ� )[ EnemyStateLookBack.h ]

-------------------------------------------------------------------------------

��  Create
2017/11/20
=============================================================================*/

#ifndef _ENEMYSTATELOOKBACK_H_
#define _ENEMYSTATELOOKBACK_H_

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
class EnemyStateLookBack:public HumanState
{
public:
	EnemyStateLookBack(Enemy* owner);

	void Uninitialize(void)override;
	void Update(D3DXVECTOR3 position)override;

private:
	void LookBack(void);

private:
	int m_NumLinear;	//	������Ԃ��邩
	unsigned int m_LinearCnt;	//	��ԃJ�E���^
	unsigned int m_WaitCount;	//	�ҋ@���ԃJ�E���g

	float m_NowRotation; // ���݂̉�]

	Enemy::LINEAR* m_Linear; // ��ԍ\����
	Enemy* m_Owner; // ���L��
};

#endif
