/*=============================================================================

フェード[ Fade.cpp ]

-------------------------------------------------------------------------------
■  Author
	Ohno Takuya

■  Created Date
	2017/08/25
=============================================================================*/

/*-----------------------------------------------------------------------------
	Header
-----------------------------------------------------------------------------*/
#include "Common.h"
#include "RendererDirectX.h"
#include "TextureManagerDirectX.h"
#include "Game.h"
#include "Scene.h"
#include "Fade.h"

/*-----------------------------------------------------------------------------
	Macro
-----------------------------------------------------------------------------*/
#define OBJECT_TEXTURE_PATH (TEXTURE_PATH"Fade.jpg")
#define FADE_RATE ( 1.0f / 60 )	//	どのくらいでフェードさせるのか

/*-----------------------------------------------------------------------------
	Static
-----------------------------------------------------------------------------*/
Fade::FADE_STATE Fade::m_Fade = FADE_NONE;	//	フェード状態
Scene *Fade::m_Scene = NULL;			//	画面遷移のポインタ

void Fade::Initialize(void)
{
	MakeVerTex();	//	頂点の作成
}

void Fade::Uninitialize(void)
{
	SAFE_RELEASE(m_VtxBuff);

	m_Scene = NULL;
}

void Fade::Update(void)
{
	if(m_Fade == FADE_NONE){return;}

	AlphaFade();	//	α値のフェード

	SetVerTex();	//	頂点の変更
}

void Fade::Draw(void)
{
	//	デバイスの取得
	LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();


	Device->SetVertexShader(NULL);
	Device->SetPixelShader(NULL);

	// 頂点バッファをデータストリームに設定
	Device->SetStreamSource(0, m_VtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	Device->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	Device->SetTexture(0, Game::GetInstance()->GetTextureManager()->GetTextureInfo(OBJECT_TEXTURE_PATH).Texture);
	//Device->SetTexture(0, NULL);

	// 描画
	Device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

/*-----------------------------------------------------------------------------
頂点の作成
-----------------------------------------------------------------------------*/
void Fade::MakeVerTex(void)
{
	//	デバイスの取得
	LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();


	// 頂点バッファの生成
	if (FAILED(Device->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_VtxBuff, NULL)))
	{
		MessageBox(NULL, "頂点バッファの生成に失敗", "Fade.cpp", MB_OK | MB_ICONHAND);
		return;
	}


	// 頂点情報を設定
	// 構造体のポインタ宣言
	VERTEX_2D* pVtx;

	// バッファをロックし、仮想アドレスを取得
	m_VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//	頂点座標の設定
	pVtx[0].Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].Pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].Pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].Pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	for(unsigned int CountVertex = 0; CountVertex < NUM_VERTEX; CountVertex++)
	{
		pVtx[CountVertex].Rhw = 1.0f;//	座標変換済み頂点フラグの設定
		pVtx[CountVertex].Color = m_Color;//	頂点色
	}

	//	テクスチャ座標の設定
	pVtx[0].Tex = D3DXVECTOR2(0, 0);
	pVtx[1].Tex = D3DXVECTOR2(1, 0);
	pVtx[2].Tex = D3DXVECTOR2(0, 1);
	pVtx[3].Tex = D3DXVECTOR2(1, 1);

	//	バッファをアンロック
	m_VtxBuff->Unlock();
}

/*-----------------------------------------------------------------------------
頂点の変更
-----------------------------------------------------------------------------*/
void Fade::SetVerTex(void)
{
	// 頂点情報を設定
	// 構造体のポインタ宣言
	VERTEX_2D* pVtx;

	// バッファをロックし、仮想アドレスを取得
	m_VtxBuff->Lock(0, 0, (void**)&pVtx, 0);


	//	頂点色の設定
	for(unsigned int CountVertex = 0; CountVertex < NUM_VERTEX; CountVertex++)
	{
		pVtx[CountVertex].Color = m_Color;
	}

	//	バッファをアンロック
	m_VtxBuff->Unlock();
}

/*-----------------------------------------------------------------------------
α値のフェード
-----------------------------------------------------------------------------*/
void Fade::AlphaFade(void)
{
	if (m_Fade == FADE_IN)
	{	//	フェードイン時の処理

		m_Color.a -= FADE_RATE;	//	a値を減算して後ろの画面を浮かび上がらせる

		if (m_Color.a < 0.0f)
		{	//	フェードインの終了

			m_Color.a = 0.0f;
			m_Fade = FADE_NONE;
		}
	}

	else if (m_Fade == FADE_OUT)
	{	//	フェードアウト時の処理

		m_Color.a += FADE_RATE;	//	a値を加算して後ろの画面を消していく

		if (m_Color.a > 1.0f)
		{	//	フェードアウトの終了

			m_Color.a = 1.0f;
			m_Fade = FADE_IN;	//	フェードインに処理の切り替え

			//	遷移の設定
			Game::GetInstance()->SetScene(m_Scene);
		}
	}
}