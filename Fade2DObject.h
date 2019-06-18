/*=============================================================================

フェードオブジェクト(2D)[ Fade2DObject.h ]

-------------------------------------------------------------------------------
■  Author
Ohno Takuya

■  Create
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
	void Fade(void); // フェード

private:
	enum FADE_STATE
	{	//	フェードの状態
		FADE_IN = 0,	//	フェードイン
		FADE_OUT,	//	フェードアウト
	};

	FADE_STATE m_FadeState;

	float m_UpperLimit; // 上限
	float m_LowerLimit; // 下限
	float m_FadeRate; // フェードする割合

	bool m_FadeFlag;
};

#endif
