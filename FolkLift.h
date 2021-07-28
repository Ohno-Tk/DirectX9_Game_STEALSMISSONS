/*=============================================================================

�I�u�W�F�N�g( �t�H�[�N���t�g )[ FolkLift.h ]

-------------------------------------------------------------------------------

��  Create
2018/02/04
=============================================================================*/

#ifndef _FOLKLIFT_H_
#define _FOLKLIFT_H_

class VertexShader;
class PixelShader;

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class FolkLift:public Object
{
public:
	FolkLift(int Priolity = 3):Object(Priolity), m_Rotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f)), m_SphereRadius(5.0f){}

	static FolkLift* Create(void);

	void Initialize(void)override;
	void Uninitialize(void)override;
	void Update(void)override;
	void Draw(void)override;

private:
	void Collision(void); // �Փ˔���
	void WorldTransform(LPDIRECT3DDEVICE9 Device);// ���[���h���W�ϊ�
	void ConfigShader(LPDIRECT3DDEVICE9 device);// �V�F�[�_�[�̐ݒ�

private:
	D3DXVECTOR3	m_Rotation;	//	��]
	float m_SphereRadius; // �����莞�̂̔��a
	D3DXMATRIX m_MatrixWorld;

	MODEL_PARAM m_ModelParam;	//	���f���\����

	VertexShader* m_VertexShader;
	PixelShader* m_PixelShader;

	LPDIRECT3DVERTEXDECLARATION9 m_VertexDeclaration;
};

#endif
