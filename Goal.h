/*=============================================================================

�S�[���n�_[ Goal.h ]

-------------------------------------------------------------------------------

��  Create
2017/11/15
=============================================================================*/

#ifndef _GOAL_H_
#define _GOAL_H_

class VertexShader;
class PixelShader;

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class Goal:public Object
{
public:
	Goal(int Priolity = 4):Object(Priolity),m_SphereRadius(2.0f),m_Rotation(D3DXVECTOR3(0.0f,0.0f,0.0f)){}

	static Goal* Create(D3DXVECTOR3 pos);

	void Initialize(void)override;
	void Uninitialize(void)override;
	void Update(void)override;
	void Draw(void)override;

private:
	void Collision(void); // �Փ˔���
	void WorldTransform(void);// ���[���h���W�ϊ�
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
