/*=============================================================================

�t�F�[�h�I�u�W�F�N�g(2D)[ Fade2DObject.h ]

-------------------------------------------------------------------------------

��  Create
2017/11/17
=============================================================================*/

#ifndef _FADE2DOBJECT_H_
#define _FADE2DOBJECT_H_

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class Fade2DObject:public Sprite2D
{
public:
	Fade2DObject(int Priolity = 4);

	static Fade2DObject* Create(D3DXVECTOR3 position, D3DXVECTOR2 size, char* texturePath, float upperLimit = 1.0f, float lowerLimit = 0.0f, D3DXVECTOR4 color = D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f), float fadeRate = 1.0f/60);

	void Initialize(void)override;
	void Uninitialize(void)override;
	void Update(void)override;
	void Draw(void)override;

	// Setter
	void SetTexturePath(char* filePath);
	void SetFadeFlag(const bool flag){ m_FadeFlag = flag; }

private:
	void Fade(void); // �t�F�[�h

private:
	enum FADE_STATE
	{	//	�t�F�[�h�̏��
		FADE_IN = 0,	//	�t�F�[�h�C��
		FADE_OUT,	//	�t�F�[�h�A�E�g
	};

	FADE_STATE m_FadeState;

	float m_UpperLimit; // ���
	float m_LowerLimit; // ����
	float m_FadeRate; // �t�F�[�h���銄��

	bool m_FadeFlag;
};

#endif
