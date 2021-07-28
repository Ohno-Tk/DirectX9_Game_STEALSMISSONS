/*=============================================================================

���b�V����[ MeshWall.h ]
( Maybe-Later:std::string�̃�����������o���Ă��Ȃ� )
-------------------------------------------------------------------------------

��  Create
	2017/07/06
=============================================================================*/

#ifndef _MESHWALL_H_
#define _MESHWALL_H_

class VertexShader;
class PixelShader;

/*-----------------------------------------------------------------------------
	Class
-----------------------------------------------------------------------------*/
class MeshWall : public Object
{
public:
	MeshWall(int Priolity = 1);

	static MeshWall *Create(D3DXVECTOR3 Pos, float Rot, UINT NumBlock_X, UINT NumBlock_Y, float SizeBlock_X, float SizeBlock_Y);

	D3DXVECTOR3 CollisionMeshWall(D3DXVECTOR3 Position, D3DXVECTOR3 FrontVector);	//	�ǂ���

	void Initialize(void)override;
	void Uninitialize(void)override;
	void Update(void)override;
	void Draw(void)override;

	// Setter
	void SetNormal(D3DXVECTOR3 normal){ m_Normal = normal; }

private:
	void MakeVerTex(LPDIRECT3DDEVICE9 Device);	//	���_�̍쐬
	void SetVerTex(void);// ���_�̕ύX
	void MakeIndex(LPDIRECT3DDEVICE9 Device);	//	�C���f�b�N�X�o�b�t�@�̍쐬
	void WorldTransform(LPDIRECT3DDEVICE9 Device);	//	���[���h���W�ϊ�
	void ConfigShader(LPDIRECT3DDEVICE9 device);// �V�F�[�_�[�̐ݒ�

	//	���_���̌v�Z
	void SetVertexCount(const UINT NumBlock_X, const UINT NumBlock_Y);
	//	�C���f�b�N�X�o�b�t�@�̌v�Z
	void SetIndexBufferCount(const UINT NumBlock_X, const UINT NumBlock_Y);

private:
	static LPDIRECT3DTEXTURE9	m_Texture;		// �e�N�X�`��
	LPDIRECT3DVERTEXBUFFER9		m_VertexBuffer;	// ���_�o�b�t�@
	LPDIRECT3DINDEXBUFFER9		m_IndexBuffer;	//	�C���f�b�N�X�o�b�t�@

	D3DXVECTOR3 m_Normal;
	D3DXVECTOR3	m_Rotation;	// ��]

	D3DXCOLOR m_Color;		//	�F

	D3DXMATRIX	m_MatrixWorld;	// ���[���h�}�g���b�N�X

	UINT m_NumBlock_X;		//	���̖���
	UINT m_NumBlock_Y;		//	�c�̖���

	int m_NumVertex;			//	���_��
	int m_NumIndexBuffer;		//	�C���f�b�N�X�o�b�t�@��

	float m_SizeBlock_X;	//	���̑傫��
	float m_SizeBlock_Z;	//	���̑傫��

	char* m_TexturePath;	//	�e�N�X�`���p�X

	VertexShader* m_VertexShader;
	PixelShader* m_PixelShader;

	LPDIRECT3DVERTEXDECLARATION9 m_VertexDeclaration;

};

#endif