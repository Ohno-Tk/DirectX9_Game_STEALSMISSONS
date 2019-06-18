/*=============================================================================

敵状態( 巡回 )[ EnemyStatePatrol.h ]

-------------------------------------------------------------------------------
■  Author
Ohno Takuya

■  Create
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
	D3DXVECTOR3 m_ControlPoint; // 制御点
	D3DXVECTOR3 m_InverseFrontVector; // 前方向ベクトルの逆

	int m_NumLinear;	//	いくつ補間するか
	unsigned int m_LinearCnt;	//	補間カウンタ
	unsigned int m_FrameTimeCount;	//	フレーム時間カウント

	float m_NowRotation; // 現在の回転


	Enemy::LINEAR* m_Linear; // 補間構造体

	Enemy* m_Owner; // 所有者
};

#endif
