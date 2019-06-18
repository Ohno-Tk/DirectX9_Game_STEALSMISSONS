/*=============================================================================

敵状態( 制御点へ移動 )[ EnemyStateControlPointMove.h ]

-------------------------------------------------------------------------------
■  Author
Ohno Takuya

■  Create
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
	D3DXVECTOR3 m_ControlPoint; // 制御点
	D3DXVECTOR3 m_InverseFrontVector; // 前方向ベクトルの逆

	int m_NumLinear;	//	いくつ補間するか
	unsigned int m_FrameTimeCount;	//	フレーム時間カウント
	unsigned int m_CountLinear;

	float m_NowRotation; // 現在の回転


	Enemy::LINEAR m_Linear; // 補間構造体

	Enemy* m_Owner; // 所有者
};

#endif
