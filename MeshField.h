/*=============================================================================

���b�V���t�B�[���h[ MeshField.h ]
( Maybe-Later:std::string�̃�����������o���Ă��Ȃ� )
-------------------------------------------------------------------------------

��  Created Date
	2017/06/13
=============================================================================*/

#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

class VertexShader;
class PixelShader;

/*-----------------------------------------------------------------------------
	Class
-----------------------------------------------------------------------------*/
class MeshField:public Object
{
public:
	enum IDXBACK_DRAW
	{	//	�ǂ�������ŕ`�悳���邩

		IDXBACK_DRAW_CLOCKWISE = 0,	//	���v���
		IDXBACK_DRAW_INV_CLOCKWISE	//	�t���v���

	};

	MeshField(int Priolity = 1);

	static MeshField* Create(D3DXVECTOR3 Pos , UINT NumBlock_X , UINT NumBlock_Z , float SizeBlock_X , float SizeBlock_Z, char* tecturePath);	//	����

	float GetHeight(D3DXVECTOR3 Position);	//	����Ă��鉚�ʂ̍����擾

	// Setter
	void SetRotation(const D3DXVECTOR3 rotation){ m_Rotation = rotation; }

private:
	void Initialize(void)override;
	void Uninitialize(void)override;
	void Update(void)override {}
	void Draw(void)override;

	void MakeVerTex(LPDIRECT3DDEVICE9 Device);//	���_�̍쐬
	void MakeIndex(LPDIRECT3DDEVICE9 Device);	//	�C���f�b�N�X�o�b�t�@�̍쐬
	void WorldTransform(LPDIRECT3DDEVICE9 Device);	//	���[���h���W�ϊ�
	void ConfigShader(LPDIRECT3DDEVICE9 device);// �V�F�[�_�[�̐ݒ�

	//	���_���̌v�Z
	void SetVertexCount(const UINT NumBlock_X, const UINT NumBlock_Y);
	//	�C���f�b�N�X�o�b�t�@�̌v�Z
	void SetIndexBufferCount(const UINT NumBlock_X, const UINT NumBlock_Y);

private:
	static LPDIRECT3DTEXTURE9 m_Texture;	// �e�N�X�`��
	LPDIRECT3DVERTEXBUFFER9	m_VertexBuffer;	// ���_�o�b�t�@
	LPDIRECT3DINDEXBUFFER9	m_IndexBuffer;	//	�C���f�b�N�X�o�b�t�@

	D3DXVECTOR3	m_Rotation;		// ��]
	D3DXMATRIX m_MatrixWorld;
	D3DXVECTOR2 m_TexturePositon;	//	�e�N�X�`�����W

	UINT m_NumBlock_X;	//	���̖���
	UINT m_NumBlock_Y;	//	�c�̖���

	int m_NumVertex;		//	���_��
	int m_NumIndexBuffer;	//	�C���f�b�N�X�o�b�t�@��

	float m_SizeBlock_X;		//	���̑傫��
	float m_SizeBlock_Z;		//	���̑傫��

	IDXBACK_DRAW m_IndexBackDraw;	//	�ǂ�������ŕ`�悳���邩

	char* m_TexturePath;	//	�e�N�X�`���p�X

	VertexShader* m_VertexShader;
	PixelShader* m_PixelShader;

	LPDIRECT3DVERTEXDECLARATION9 m_VertexDeclaration;
};

#endif