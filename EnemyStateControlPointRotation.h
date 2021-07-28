/*=============================================================================

�G���( ����_�։�] )[ EnemyStateControlPointRotation.h ]

-------------------------------------------------------------------------------

��  Create
2017/12/04
=============================================================================*/

#ifndef _ENEMYSTATECONTROLPOINTROTATION_H_
#define _ENEMYSTATECONTROLPOINTROTATION_H_

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
class EnemyStateControlPointRotation:public HumanState
{
public:
	EnemyStateControlPointRotation(Enemy* owner);

	void Uninitialize(void)override{}
	void Update(D3DXVECTOR3 position)override;

private:
	void RotationControlPoint(void);

private:
	Enemy* m_Owner; // ���L��

	float m_NowRotation;
	float m_Angle;

	int m_CountInterpolation; // ��Ԃ̃J�E���^
	unsigned int m_CountLinear;
};

#endif
