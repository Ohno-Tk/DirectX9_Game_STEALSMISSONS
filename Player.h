/*=============================================================================

プレイヤー[ Player.h ]

-------------------------------------------------------------------------------
■  Author
Ohno Takuya

■  Create
2017/11/11
=============================================================================*/

#ifndef _PLAYER_H_
#define _PLAYER_H_

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "Human.h"

/*-----------------------------------------------------------------------------

-----------------------------------------------------------------------------*/
class StencilShadow;
class HitPointGauge;
class DirectXKeyboard;
class XInput;

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class Player:public Human
{
public:
	Player(int Priolity = 3);

	static Player* Create(D3DXVECTOR3 position, float rotation);

	void Initialize(void)override;
	void Uninitialize(void)override;
	void Update(void)override;
	void Draw(void)override;

	bool AttackHit(int damageValue); // 攻撃ヒット
	void HitPointRecovery(int recoveryValue);// 体力回復

	// Setter
	void SetOldPosition(void){ Object::SetPosition(m_OldPosision); }

	// Getter
	float GetSphereRadius(void){ return m_SphereRadius; }
	D3DXVECTOR3 GetHeadPosition(void);
	int GetHitPoint(void);
	int GetMaxHitPoint(void);

private:
	void Control(D3DXVECTOR3* position); // 操作
	void Collision(D3DXVECTOR3* position); // 衝突判定

private:
	D3DXVECTOR3 m_OldPosision; // 前回の座標

	float m_Move; // 移動量
	float m_SphereRadius; // 球判定時のの半径

	StencilShadow* m_Shadow;
	HitPointGauge* m_HitPoint;
	XInput* m_XInput;
};

#endif
