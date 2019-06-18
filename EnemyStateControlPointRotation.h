/*=============================================================================

敵状態( 制御点へ回転 )[ EnemyStateControlPointRotation.h ]

-------------------------------------------------------------------------------
■  Author
Ohno Takuya

■  Create
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
	Enemy* m_Owner; // 所有者

	float m_NowRotation;
	float m_Angle;

	int m_CountInterpolation; // 補間のカウンタ
	unsigned int m_CountLinear;
};

#endif
