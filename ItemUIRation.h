/*=============================================================================

�A�C�e���\��UI( ���[�V���� )[ ItemUIRation.h ]

-------------------------------------------------------------------------------
��  Create
2018/01/24
=============================================================================*/

#ifndef _ITEMUIRATION_H_
#define _ITEMUIRATION_H_

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "ItemUI.h"

class ItemPossession;

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class ItemUIRation:public ItemUI
{
public:
	ItemUIRation(int priolity = 4);

	static ItemUIRation* Create(D3DXVECTOR3 position);// ����

	void Initialize(void)override;
	void Uninitialize(void)override;
	void Update(void)override;
	void Draw(void)override;

	void PlusNowPossession(const unsigned int plusValue);// ���ݏ������ǉ�
	void SubNowPossession(const unsigned int subValue);	 // ���ݏ��������Z

	void Use(void)override;// �g�p

private:
	void MakeVertex(void);// ���_�̍쐬
	void SetVertex(void);// ���_�̕ύX

private:
	LPDIRECT3DVERTEXBUFFER9 m_VertexBuffer;
	D3DXVECTOR2 m_Size;

	unsigned int m_NowPossession;// ���ݏ�����
	unsigned int m_MaxPossession;// �ő及����

	ItemPossession* m_NowPossessionUI;
	ItemPossession* m_MaxPossessionUI;
};

#endif
