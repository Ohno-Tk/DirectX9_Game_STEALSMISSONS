/*=============================================================================

�v���C���[[ Player.h ]

-------------------------------------------------------------------------------

��  Create
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

	bool AttackHit(int damageValue); // �U���q�b�g
	void HitPointRecovery(int recoveryValue);// �̗͉�

	// Setter
	void SetOldPosition(void){ Object::SetPosition(m_OldPosision); }

	// Getter
	float GetSphereRadius(void){ return m_SphereRadius; }
	D3DXVECTOR3 GetHeadPosition(void);
	int GetHitPoint(void);
	int GetMaxHitPoint(void);

private:
	void Control(D3DXVECTOR3* position); // ����
	void Collision(D3DXVECTOR3* position); // �Փ˔���

private:
	D3DXVECTOR3 m_OldPosision; // �O��̍��W

	float m_Move; // �ړ���
	float m_SphereRadius; // �����莞�̂̔��a

	StencilShadow* m_Shadow;
	HitPointGauge* m_HitPoint;
	XInput* m_XInput;
};

#endif
