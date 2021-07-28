/*=============================================================================

X���f���`��[ SpriteModeX.h ]
( Maybe-Later:std::string�̃�����������o���Ă��Ȃ� )
-------------------------------------------------------------------------------

��  Create
	2017/08/25
=============================================================================*/

#ifndef _SPRITEMODELX_H_
#define _SPRITEMODELX_H_

class VertexShader;
class PixelShader;

/*-----------------------------------------------------------------------------
	Class
-----------------------------------------------------------------------------*/
class SpriteModelX:public Object
{
public:
	SpriteModelX(int Priolity);

	static SpriteModelX* Create(D3DXVECTOR3 position, D3DXVECTOR3 rotation, char* modelFilePath, int priolity = 3);

	void Initialize(void)override;
	void Uninitialize(void)override;
	void Update(void)override {}
	void Draw(void)override;

	//	Setter
	void SetRotation(const D3DXVECTOR3 Rot) { m_Rotation = Rot; }
	void SetScale(const D3DXVECTOR3 Scl) { m_Scale = Scl; }
	void SetModelFileName(char* modelFilePath) { m_ModelFilePath = modelFilePath; }

	//	Getter
	D3DXVECTOR3 GetRotation(void) { return m_Rotation; }
	D3DXVECTOR3 GetScale(void) { return m_Scale; }
	D3DXMATRIX GetMatrix(void){ return m_MatrixWorld; }

private:
	void WorldTransform(LPDIRECT3DDEVICE9 Device);	//	���[���h���W�ϊ�
	void ConfigShader(LPDIRECT3DDEVICE9 device);// �V�F�[�_�[�̐ݒ�

private:
	D3DXVECTOR3	m_Rotation;	//	��]
	D3DXVECTOR3	m_Scale;	//	�g�嗦

	D3DXMATRIX m_MatrixWorld;

	MODEL_PARAM m_ModelParam;	//	���f���\����
	char* m_ModelFilePath;	//	���f���̃p�X

	VertexShader* m_VertexShader;
	PixelShader* m_PixelShader;

	LPDIRECT3DVERTEXDECLARATION9 m_VertexDeclaration;
};

#endif