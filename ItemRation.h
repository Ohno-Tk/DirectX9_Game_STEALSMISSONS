/*=============================================================================

�A�C�e��( ���[�V���� )[ ItemRation.h ]

-------------------------------------------------------------------------------

��  Create
2018/01/22
=============================================================================*/

#ifndef _ITEMRATION_H_
#define _ITEMRATION_H_

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "Item.h"

class VertexShader;
class PixelShader;

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class ItemRation:public Item
{
public:
	ItemRation(int priolity = 3);

	static ItemRation* Create(D3DXVECTOR3 position);// ����

	void Initialize(void)override;
	void Uninitialize(void)override;
	void Update(void)override;
	void Draw(void)override;

private:
	bool Collision(void)override;// �����蔻��
	void WorldTransform(LPDIRECT3DDEVICE9 Device);// ���[���h���W�ϊ�
	void ConfigShader(LPDIRECT3DDEVICE9 device);// �V�F�[�_�[�̐ݒ�

private:
	D3DXVECTOR3	m_Rotation;// ��]
	D3DXMATRIX m_MatrixWorld;

	MODEL_PARAM m_ModelParam;

	VertexShader* m_VertexShader;
	PixelShader* m_PixelShader;

	LPDIRECT3DVERTEXDECLARATION9 m_VertexDeclaration;
};

#endif
