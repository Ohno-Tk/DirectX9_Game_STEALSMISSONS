/*=============================================================================

HP�Q�[�W[ HitPointGauge.h ]

-------------------------------------------------------------------------------

��  Create
2017/11/18
=============================================================================*/

#ifndef _HITPOINTGAUGE_H_
#define _HITPOINTGAUGE_H_

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "FrameworkBase\RendererDirectX.h"
#include "Object.h"
#include "Sprite2D.h"

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class HitPointGauge:public Sprite2D
{
public:
	HitPointGauge(int priolity = 5);

	static HitPointGauge* Create(D3DXVECTOR3 position, D3DXVECTOR2 size, int maxHitPoint);

	void Initialize(void)override;
	void Uninitialize(void)override;
	void Update(void)override;
	void Draw(void)override;

	// Setter
	void SetHitPoint(const int hitPoint);

	// Getter
	int GetHitPoint(void){ return m_NowHitPoint; }
	int GetHitPointRate(void);
	int GetMaxHitPoint(void){ return m_MaxHitPoint; }

private:
	void SetVertex(D3DXVECTOR2 size, D3DXCOLOR color);

private:
	int m_MaxHitPoint; // �ő�HP
	int m_NowHitPoint; // ����HP

	float m_MaxSize; // �ő�傫��
	float m_HitPointRate; // HP����
};

#endif
