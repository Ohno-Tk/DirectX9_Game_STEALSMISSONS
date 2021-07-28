/*=============================================================================

�^�C�g���w�i[ TitleBackGround.h ]

-------------------------------------------------------------------------------

��  Create
2018/01/27
=============================================================================*/

#ifndef _TITLEBACKGROUND_H_
#define _TITLEBACKGROUND_H_

class VertexShader;
class PixelShader;

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class TitleBackGround:public Object
{
public:
	TitleBackGround(int priolity = 1);// �R���X�g���N�^

	static TitleBackGround *Create(D3DXVECTOR3 position, D3DXVECTOR3 rotation);// ����

	void Initialize(void)override;// ������
	void Uninitialize(void)override;// �I��
	void Update(void)override;// �X�V
	void Draw(void)override;// �`��

	// Setter
	void SetNormal(D3DXVECTOR3 normal){ m_Normal = normal; }

private:
	void MakeVerTex(LPDIRECT3DDEVICE9 Device);	//	���_�̍쐬
	void ChangeVerTex(void);	//	���_�̕ύX
	void MakeIndex(LPDIRECT3DDEVICE9 Device);	//	�C���f�b�N�X�o�b�t�@�̍쐬
	void WorldTransform(LPDIRECT3DDEVICE9 Device);	//	���[���h���W�ϊ�
	void ConfigShader(LPDIRECT3DDEVICE9 device);// �V�F�[�_�[�̐ݒ�

private:
	static LPDIRECT3DTEXTURE9	m_Texture;		// �e�N�X�`��
	LPDIRECT3DVERTEXBUFFER9		m_VertexBuffer;	// ���_�o�b�t�@
	LPDIRECT3DINDEXBUFFER9		m_IndexBuffer;	//	�C���f�b�N�X�o�b�t�@

	D3DXVECTOR3 m_Normal;
	D3DXVECTOR3	m_Rotation;	// ��]
	D3DXMATRIX	m_MatrixWorld;

	int m_NumVertex;			//	���_��
	int m_NumIndexBuffer;		//	�C���f�b�N�X�o�b�t�@��
	UINT m_NumBlock_X;		//	���̖���
	UINT m_NumBlock_Y;		//	�c�̖���
	float m_SizeBlock_X;	//	���̑傫��
	float m_SizeBlock_Z;	//	���̑傫��

	float m_TexCoord;

	VertexShader* m_VertexShader;
	PixelShader* m_PixelShader;
	LPDIRECT3DVERTEXDECLARATION9 m_VertexDeclaration;
};

#endif
