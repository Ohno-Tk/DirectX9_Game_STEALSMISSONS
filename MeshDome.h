/*=============================================================================

���b�V������[ MeshDome.h ]
( Maybe-Later:std::string�̃�����������o���Ă��Ȃ� )
-------------------------------------------------------------------------------

��  Create
	2017/05/12
=============================================================================*/

#ifndef _MESHDOME_H_
#define _MESHDOME_H_

/*-----------------------------------------------------------------------------
	Class
-----------------------------------------------------------------------------*/
class MeshDome : public Object
{
public:
	typedef enum
	{	//	�ǂ�������ŕ`�悳���邩

		IDXBACK_DRAW_CLOCKWISE = 0,	//	���v���
		IDXBACK_DRAW_INV_CLOCKWISE	//	�t���v���

	}IDXBACK_DRAW;

	MeshDome(int Priolity = 1);		//	�R���X�g���N�^

	static MeshDome* Create(D3DXVECTOR3 Pos, UINT NumBlock_X, UINT NumBlock_Y, float Radius, IDXBACK_DRAW IdxBack, char* TextureName);

	void Initialize(void)override;
	void Uninitialize(void)override;
	void Update(void)override{}
	void Draw(void)override;

	// Setter
	void SetRot(const D3DXVECTOR3 Rot) { m_Rotation = Rot; };		//	��]�̃Z�b�g

	//	�e�N�X�`���p�X�̃Z�b�g
	void SetTexture(char* texturePath) { m_TexturePath = texturePath; }

private:
	void MakeVerTex(LPDIRECT3DDEVICE9 Device);	//	���_�̍쐬
	void MakeIndex(LPDIRECT3DDEVICE9 Device);	//	�C���f�b�N�X�o�b�t�@�̍쐬
	void WorldTransform(LPDIRECT3DDEVICE9 Device);		//	���[���h���W�ϊ�

private:
	static LPDIRECT3DTEXTURE9 m_Texture;	// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_VertexBuffer;		// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9	m_IndexBuffer;		//	�C���f�b�N�X�o�b�t�@�C���^�t�F�[�X�ւ̃|�C���^�̃A�h���X

	D3DXVECTOR3	m_Rotation;			// ��]
	D3DXVECTOR3	m_Scale;			// �g�嗦

	D3DXVECTOR2 m_TexturePositon;		//	�e�N�X�`�����W

	D3DXMATRIX	m_MatixWorld;		// ���[���h�}�g���b�N�X

	UINT m_NumBlock_X;	//	���̖���
	UINT m_NumBlock_Y;	//	�c�̖���

	int m_NumVertex;		//	���_��
	int m_NumIndexBuffer;	//	�C���f�b�N�X�o�b�t�@��

	float m_Radius;	//	���a

	IDXBACK_DRAW m_IndexBackDraw;	//	�ǂ�������ŕ`�悳���邩

	char* m_TexturePath;//	�e�N�X�`���p�X

protected:
	//	�c���̖����̃Z�b�g
	void SetNumBlock(const UINT NumBlock_X, const UINT NumBlock_Y) { m_NumBlock_X = NumBlock_X; m_NumBlock_Y = NumBlock_Y; };

	//	���_���̌v�Z
	void SetVertexCount(const UINT NumBlock_X, const UINT NumBlock_Y) { m_NumVertex = (NumBlock_X + 1) * (NumBlock_Y + 1); };

	//	�C���f�b�N�X�o�b�t�@�̌v�Z
	void SetIndexBufferCount(const UINT NumBlock_X, const UINT NumBlock_Y) { m_NumIndexBuffer = (2 + 2 * NumBlock_X) * NumBlock_Y + (NumBlock_Y - 1) * 2; };

	//	�ǂ�������ŕ`�悳���邩
	void SetIndexBackDraw(const IDXBACK_DRAW IdxBackDraw) { m_IndexBackDraw = IdxBackDraw; };

};

#endif