/*=============================================================================

�A�C�e���擾UI( ���[�V���� )[ ItemGetUIRation.h ]

-------------------------------------------------------------------------------

��  Create
2018/01/22
=============================================================================*/

#ifndef _ITEMGETUIRATION_H_
#define _ITEMGETUIRATION_H_

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "ItemGetUI.h"

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class ItemGetUIRation:public ItemGetUI
{
public:
	ItemGetUIRation(int priolity = 4);

	static ItemGetUIRation* Create(D3DXVECTOR3 position);// ����

	void Initialize(void)override;
	void Uninitialize(void)override;
	void Update(void)override;
	void Draw(void)override;

private:
	void MakeVertex(void);// ���_�̍쐬
	void SetVertex(void);// ���_�̕ύX
	void WorldTransform(LPDIRECT3DDEVICE9 Device);// ���[���h���W�ϊ�

private:
	LPDIRECT3DVERTEXBUFFER9 m_VertexBuffer;
	D3DXMATRIX m_MatrixWorld;

	int m_FrameTime;
	float m_EndPosition;
};

#endif
