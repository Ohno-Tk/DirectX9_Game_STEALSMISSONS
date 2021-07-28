/*=============================================================================

HP�Q�[�W[ HitPointGauge.cpp ]

-------------------------------------------------------------------------------

��  Create
2017/11/18
=============================================================================*/

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "FrameworkBase\Common.h"
#include "HitPointGauge.h"

/*-----------------------------------------------------------------------------
	Macro
-----------------------------------------------------------------------------*/
#define OBJECT_TEXTURE_PATH ( TEXTURE_PATH"GAME/GuageBar.png" )


HitPointGauge::HitPointGauge(int priolity):Sprite2D(priolity)
{
	m_MaxHitPoint = 0;
	m_NowHitPoint = 0;

	m_MaxSize = 0.0f;
	m_HitPointRate = 0.0f;
}

/*-----------------------------------------------------------------------------
Function:   HitPointGauge* HitPointGauge::Create(D3DXVECTOR3 position, D3DXVECTOR2 size, int maxHitPoint)
Parameter:  D3DXVECTOR3 position
              ���W
			D3DXVECTOR2 size
			  �傫��
			int maxHitPoint
			  �ő�q�b�g�|�C���g
Overview:   ����
-----------------------------------------------------------------------------*/
HitPointGauge* HitPointGauge::Create(D3DXVECTOR3 position, D3DXVECTOR2 size, int maxHitPoint)
{
	auto object = new HitPointGauge;

	object->SetPosition(position);
	object->SetSize(size);
	object->SetTexturePath(OBJECT_TEXTURE_PATH);
	object->m_MaxHitPoint = maxHitPoint;
	object->m_NowHitPoint = maxHitPoint;
	object->m_MaxSize = size.x;

	object->Initialize();

	return object;
}

void HitPointGauge::Initialize(void)
{
	Sprite2D::Initialize();
	Sprite2D::SetColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
}

void HitPointGauge::Uninitialize(void)
{
	Sprite2D::Uninitialize();
}

void HitPointGauge::Update(void)
{
	D3DXCOLOR color = Sprite2D::GetColor();
	D3DXVECTOR2 size = Sprite2D::GetSize();

	m_HitPointRate = (float)m_NowHitPoint / m_MaxHitPoint; // ��������������

	size.x = m_HitPointRate * m_MaxSize; // �傫���̌v�Z

	Sprite2D::SetSize(size);
	Sprite2D::SetColor(color);

	SetVertex(size, color);
}

void HitPointGauge::Draw(void)
{
	Sprite2D::Draw();
}

void HitPointGauge::SetVertex(D3DXVECTOR2 size, D3DXCOLOR color)
{
	LPDIRECT3DVERTEXBUFFER9 vertexBuffer = Sprite2D::GetVertexBuffer();
	D3DXVECTOR3 position = Object::GetPosition();

	VERTEX_2D* Vtx;

	vertexBuffer->Lock(0, 0, (void**)&Vtx, 0);


	Vtx[0].Pos = D3DXVECTOR3(position.x         , position.y, 0.0f);
	Vtx[1].Pos = D3DXVECTOR3(position.x + size.x, position.y, 0.0f);
	Vtx[2].Pos = D3DXVECTOR3(position.x         , position.y + size.y, 0.0f);
	Vtx[3].Pos = D3DXVECTOR3(position.x + size.x, position.y + size.y, 0.0f);

	for(unsigned int CountVertex = 0; CountVertex < NUM_VERTEX; CountVertex++)
	{
		Vtx[CountVertex].Color = color;// ���_�J���[
	}

	// �e�N�X�`�����W
	Vtx[0].Tex = D3DXVECTOR2(0             , 0);
	Vtx[1].Tex = D3DXVECTOR2(m_HitPointRate, 0);
	Vtx[2].Tex = D3DXVECTOR2(0             , 1);
	Vtx[3].Tex = D3DXVECTOR2(m_HitPointRate, 1);


	//	�o�b�t�@���A�����b�N
	vertexBuffer->Unlock();
}

void HitPointGauge::SetHitPoint(const int hitPoint)
{
	m_NowHitPoint = hitPoint;
	m_HitPointRate = (float)m_NowHitPoint / m_MaxHitPoint;
}

int HitPointGauge::GetHitPointRate(void)
{
	int percentage = m_HitPointRate * 100;

	return percentage;
}