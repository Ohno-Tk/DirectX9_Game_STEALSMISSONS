/*=============================================================================

�G���( ����_�ֈړ� )[ EnemyStateControlPointMove.h ]

-------------------------------------------------------------------------------

��  Create
2017/12/05
=============================================================================*/

#ifndef _ENEMYSTATECONTROLPOINTMOVE_H_
#define _ENEMYSTATECONTROLPOINTMOVE_H_

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
class EnemyStateControlPointMove:public HumanState
{
public:
	EnemyStateControlPointMove(Enemy* owner);

	void Uninitialize(void)override;
	void Update(D3DXVECTOR3 position)override;

private:
	void ControlPointMove(D3DXVECTOR3* position);

private:
	D3DXVECTOR3 m_ControlPoint; // ����_
	D3DXVECTOR3 m_InverseFrontVector; // �O�����x�N�g���̋t

	int m_NumLinear;	//	������Ԃ��邩
	unsigned int m_FrameTimeCount;	//	�t���[�����ԃJ�E���g
	unsigned int m_CountLinear;

	float m_NowRotation; // ���݂̉�]


	Enemy::LINEAR m_Linear; // ��ԍ\����

	Enemy* m_Owner; // ���L��
};

#endif
