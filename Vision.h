/*=============================================================================

���E( �f�o�b�O�p )[ Vision.h ]

-------------------------------------------------------------------------------

��  Create
2017/11/28
=============================================================================*/

#ifndef _VISION_H_
#define _VISION_H_

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class Vision:public Object
{
public:
	Vision(int priolity = 5):Object(priolity), m_Active(false), m_VisionDistance(0.0f), m_Angle(0.0f), m_Rotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f)){}

	static Vision* Create(float VisionDistance, float Angle);

	void Initialize(void)override;
	void Uninitialize(void)override;
	void Update(void)override{}
	void Draw(void)override;

	// Setter
	void SetActive(const bool flag){ m_Active = flag; }
	void SetOwnerMatrix(D3DXMATRIX matrix){ m_OwnerMatrix = matrix; }

private:
	void MakeVerTex(void);						//	���_�̍쐬
	void WorldTransform(LPDIRECT3DDEVICE9 Device);	//	���[���h���W�ϊ�

private:
	LPDIRECT3DVERTEXBUFFER9 m_VertexBuffer;
	D3DXVECTOR3 m_Rotation;

	D3DXMATRIX m_OwnerMatrix; // ���L�҂̃}�g���N�X

	bool m_Active;
	float m_VisionDistance;	//	���o����
	float m_Angle;			//	�p�x
};

#endif
