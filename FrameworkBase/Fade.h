/*=============================================================================

フェード[ Fade.h ]

-------------------------------------------------------------------------------
■  Author
	Ohno Takuya

■  Created Date
	2017/08/25
=============================================================================*/

#ifndef _FADE_H_
#define _FADE_H_

/*-----------------------------------------------------------------------------

-----------------------------------------------------------------------------*/
class Scene;

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class Fade
{
public:
	enum FADE_STATE
	{	//	フェードの状態
		FADE_NONE = 0,
		FADE_IN,	//	フェードイン
		FADE_OUT,	//	フェードアウト
	};

	Fade():m_VtxBuff(NULL),m_Color(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f)){}

	//	フェードのセット
	static void SetFade(const FADE_STATE Fade, Scene *Mode) { m_Fade = Fade, m_Scene = Mode; }

	void Initialize(void);
	void Uninitialize(void);
	void Update(void);
	void Draw(void);

private:
	void MakeVerTex(void);		//	頂点の作成
	void SetVerTex(void);	//	頂点の変更
	void AlphaFade(void);		//	α値のフェード

private:
	LPDIRECT3DVERTEXBUFFER9 m_VtxBuff;	// 頂点バッファ

	D3DXCOLOR m_Color;	//	色

	static FADE_STATE m_Fade;		//	フェード状態
	static Scene* m_Scene;	//	シーンのポインタ
};

#endif