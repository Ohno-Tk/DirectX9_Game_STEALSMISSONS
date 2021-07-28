/*=============================================================================

�G���( ���� )[ EnemyStatePatrol.h ]

-------------------------------------------------------------------------------

��  Create
2017/11/20
=============================================================================*/

#ifndef _ENEMYSTATEPATROL_H_
#define _ENEMYSTATEPATROL_H_

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
class EnemyStatePatrol:public HumanState
{
public:
	EnemyStatePatrol(Enemy* owner);

	void Uninitialize(void)override;
	void Update(D3DXVECTOR3 position)override;

private:
	void Patrol(D3DXVECTOR3* position);

private:
	D3DXVECTOR3 m_ControlPoint; // ����_
	D3DXVECTOR3 m_InverseFrontVector; // �O�����x�N�g���̋t

	int m_NumLinear;	//	������Ԃ��邩
	unsigned int m_LinearCnt;	//	��ԃJ�E���^
	unsigned int m_FrameTimeCount;	//	�t���[�����ԃJ�E���g

	float m_NowRotation; // ���݂̉�]


	Enemy::LINEAR* m_Linear; // ��ԍ\����

	Enemy* m_Owner; // ���L��
};

#endif
