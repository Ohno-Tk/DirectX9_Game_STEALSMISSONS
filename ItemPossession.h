/*=============================================================================

���ݏ������A�C�e��[ NowPossessionItem.h ]

-------------------------------------------------------------------------------

��  Create
2018/01/24
=============================================================================*/

#ifndef _NOWPOSSESSIONITEM_H_
#define _NOWPOSSESSIONITEM_H_

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class ItemPossession:public Object
{
public:
	ItemPossession(int priolity = 4);

	static ItemPossession* Create(D3DXVECTOR3 position, unsigned int digit);// ����

	void Initialize(void);
	void Uninitialize(void);
	void Update(void);
	void Draw(void);

	void SetPossession(int possession);// �������̐ݒ�

private:
	void MakeVertex(void);// ���_�̍쐬
	void SetVertex(void);// ���_�̕ύX

private:
	LPDIRECT3DVERTEXBUFFER9 m_VertexBuffer;
	D3DXVECTOR2 m_Size;
	unsigned int m_Digit;// ����
	unsigned int m_Possession;
	float m_TexCoord;// �e�N�X�`�����W
};

#endif
