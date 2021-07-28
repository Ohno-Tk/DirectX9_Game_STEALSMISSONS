/*=============================================================================

���b�V����[ MeshSphere.h ]
( Maybe-Later:std::string�̃�����������o���Ă��Ȃ� )
-------------------------------------------------------------------------------

��  Create
	2017/05/12
=============================================================================*/

#ifndef _MESHSPHERE_H_
#define _MESHSPHERE_H_

/*-----------------------------------------------------------------------------
	Class
-----------------------------------------------------------------------------*/
class MeshSphere : public Object
{
public:
	enum IDXBACK_DRAW
	{	//	�ǂ�������ŕ`�悳���邩

		IDXBACK_DRAW_CLOCKWISE = 0,	//	���v���
		IDXBACK_DRAW_INV_CLOCKWISE	//	�t���v���

	};

	MeshSphere(int Priolity = 5);

	static MeshSphere* Create(D3DXVECTOR3 Pos, UINT NumBlock_X, UINT NumBlock_Y, float Radius, IDXBACK_DRAW IdxBack, char* TexturePath,D3DXCOLOR color = D3DXCOLOR(1.0f,1.0f,1.0f,0.5f));

	void Initialize(void)override;
	void Uninitialize(void)override;
	void Update(void)override {}
	void Draw(void)override;

	// Setter
	void SetColor(const D3DXCOLOR color) { m_Color = color; }//	�F
	void SetRotation(const D3DXVECTOR3 rotation){ m_Rotation = rotation; }// ��]
	void SetTexturePath(char* texturePath){ m_TexturePath = texturePath; }// �e�N�X�`���̃p�X

	// Getter	
	D3DXVECTOR3 GetRotation(void) {return m_Rotation;}//	��]

private:
	void MakeVerTex(LPDIRECT3DDEVICE9 Device);		//	���_�̍쐬
	void MakeIndex(LPDIRECT3DDEVICE9 Device);		//	�C���f�b�N�X�o�b�t�@�̍쐬
	void WorldTransform(LPDIRECT3DDEVICE9 Device);	//	���[���h���W�ϊ�
	void SetVerTex(void);							//	���_�̕ύX

private:
	static LPDIRECT3DTEXTURE9 m_Texture;	// �e�N�X�`��
	LPDIRECT3DVERTEXBUFFER9	m_VertexBuffer;	// ���_�o�b�t�@
	LPDIRECT3DINDEXBUFFER9	m_IndexBuffer;	//	�C���f�b�N�X�o�b�t�@

	D3DXVECTOR3	m_Rotation;		// ��]

	D3DXVECTOR2 m_TexturePositon;		//	�e�N�X�`�����W

	D3DXCOLOR m_Color;			//	�F

	D3DXMATRIX	m_MatrixWorld;		// ���[���h�}�g���b�N�X

	UINT m_NumBlock_X;	//	���̖���
	UINT m_NumBlock_Y;	//	�c�̖���

	int m_NumVertex;		//	���_��
	int m_NumIndexBuffer;	//	�C���f�b�N�X�o�b�t�@��

	float m_Radius;		//	���a

	IDXBACK_DRAW m_IndexBackDraw;	//	�ǂ�������ŕ`�悳���邩

	char* m_TexturePath;//	�e�N�X�`���p�X

protected:
	// Setter
	void SetNumBlock(const UINT numBlockX, const UINT numBlockY);//	����
	void SetVertexCount(const UINT NumBlock_X, const UINT NumBlock_Y);// ���_���̌v�Z
	void SetIndexBufferCount(const UINT NumBlock_X, const UINT NumBlock_Y);// �C���f�b�N�X�o�b�t�@�̌v�Z
	void SetIndexBackDraw(const IDXBACK_DRAW indexBackDraw){ m_IndexBackDraw = indexBackDraw; }//	�ǂ�������ŕ`�悳���邩
	void SetRadius(const float radius) { m_Radius = radius; }//	���a

};

#endif