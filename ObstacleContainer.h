/*=============================================================================

��Q��( �R���e�i )[ ObstacleContainer.h ]

-------------------------------------------------------------------------------

��  Create
2018/01/17
=============================================================================*/

#ifndef _OBSTACLECONTAINER_H_
#define _OBSTACLECONTAINER_H_

class VertexShader;
class PixelShader;

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class ObstacleContainer:public Object
{
public:
	ObstacleContainer(int Priolity = 2);

	static ObstacleContainer* Create(D3DXVECTOR3 pos);

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
