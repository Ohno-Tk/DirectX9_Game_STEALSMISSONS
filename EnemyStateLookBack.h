/*=============================================================================

敵状態( 振り返る )[ EnemyStateLookBack.h ]

-------------------------------------------------------------------------------
■  Author
Ohno Takuya

■  Create
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
	int m_NumLinear;	//	いくつ補間するか
	unsigned int m_LinearCnt;	//	補間カウンタ
	unsigned int m_WaitCount;	//	待機時間カウント

	float m_NowRotation; // 現在の回転

	Enemy::LINEAR* m_Linear; // 補間構造体
	Enemy* m_Owner; // 所有者
};

#endif
