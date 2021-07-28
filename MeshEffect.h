/*=============================================================================

���b�V���G�t�F�N�g[ MeshEffect.h ]

-------------------------------------------------------------------------------

��  Create
2017/11/13
=============================================================================*/

#ifndef _MESHEFFECT_H_
#define _MESHEFFECT_H_

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class MeshEffect:public Object
{
public:
	MeshEffect(int Priolity = 4);

	static MeshEffect* Create(UINT numBlock_X);

	void Initialize(void)override;
	void Uninitialize(void)override;
	void Update(void)override;
	void Draw(void)override;

	// Setter
	void SetVertexPosition(const D3DXVECTOR3 topPosition, const D3DXVECTOR3 bottomPosition){ m_TopPosition = topPosition; m_ButtomPosition = bottomPosition; }

private:
	void MakeVerTex(LPDIRECT3DDEVICE9 Device);	// ���_�̍쐬
	void SetUpVerTex(void);	                    // ���_�̐ݒ�
	void MakeIndex(LPDIRECT3DDEVICE9 Device);   // �C���f�b�N�X�o�b�t�@�̍쐬
	void SetVertexCount(const UINT NumBlock_X, const UINT NumBlock_Y); // ���_���̌v�Z
	void SetIndexBufferCount(const UINT NumBlock_X, const UINT NumBlock_Y);   // �C���f�b�N�X�o�b�t�@�̌v�Z
	void WorldTransform(LPDIRECT3DDEVICE9 Device);                     // ���[���h���W�ϊ�

private:
	LPDIRECT3DVERTEXBUFFER9 m_VertexBuffer; //	���_�o�b�t�@
	LPDIRECT3DINDEXBUFFER9	m_IndexBuffer; //	�C���f�b�N�X�o�b�t�@

	D3DXVECTOR3 m_TopPosition;
	D3DXVECTOR3 m_ButtomPosition;

	D3DXVECTOR2 m_TexturePositon;	//	�e�N�X�`�����W

	UINT m_NumBlock_X;		//	���̖���
	UINT m_NumBlock_Y;		//	�c�̖���

	int m_NumVertex;		//	���_��
	int m_NumIndexBuffer;	//	�C���f�b�N�X�o�b�t�@��

	std::vector<D3DXVECTOR3> m_VertexPosition;
};

#endif
