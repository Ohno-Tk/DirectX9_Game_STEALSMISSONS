/*=============================================================================

レンダラー(DirectX)[ RendererDirectX.h ]

-------------------------------------------------------------------------------
■  Author
	Ohno Takuya

■  Create
	2017/10/14
=============================================================================*/

#ifndef _RENDERERDIRECTX_H_
#define _RENDERERDIRECTX_H_

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include <d3dx9.h>
#include <Xinput.h>
#include "Renderer.h"

/*-----------------------------------------------------------------------------
Macro
-----------------------------------------------------------------------------*/
//	頂点フォーマット
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)	//	2D
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 | D3DFVF_NORMAL)	//	3D

#define NUM_VERTEX ( 4 )	//	頂点数
#define NUM_POLYGON ( 2 )	//	ポリゴン数

#define SAFE_RELEASE(p) if(p){ p->Release(); p = NULL; }// ポインタの解放処理マクロ

/*-----------------------------------------------------------------------------
Library
[構成プロパティ]->[リンカー]->[入力]->[追加の依存ファイル]に記述しても可能
-----------------------------------------------------------------------------*/
#pragma comment(lib , "d3d9.lib")
#define DIRECTINPUT_VERSION (0x0800)
#include <dinput.h>
#include <XAudio2.h>

#pragma comment(lib, "xinput.lib")	//	XInput
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")

/*-----------------------------------------------------------------------------
Struct
-----------------------------------------------------------------------------*/
struct VERTEX_2D
{
	D3DXVECTOR3 Pos;	//	頂点座標
	float Rhw;			//	座標変換済み頂点フラグ（DirectXにしかない仕様）必ず1.0fを入れる
	D3DCOLOR Color;		//	頂点カラー
	D3DXVECTOR2 Tex;	//	テクスチャ座標
};

struct VERTEX_3D
{
	D3DXVECTOR3 Pos;	//	頂点座標
	D3DXVECTOR3 Nor;	//	法線
	D3DCOLOR Color;		//	頂点カラー
	D3DXVECTOR2 Tex;	//	テクスチャ座標
};

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class RendererDirectX:public Renderer
{
public:
	RendererDirectX();

	HRESULT Initialize(HWND hWnd)override;
	void Uninitialize(void)override;
	void DrawBegin(void)override;
	void DrawEnd(void)override;

	void Normal(void); // 通常時
	void WireFrame(void); // ワイヤーフレーム

	//	Getter
	static LPDIRECT3DDEVICE9 GetDevice(void) { return m_D3DDevice; }

private:
	//	デバイスの初期化
	HRESULT SetUpDevice(D3DPRESENT_PARAMETERS d3dpp, D3DDISPLAYMODE d3ddm, HWND Wnd, bool Window);
	void SetRenderState(void);			//	レンダーステートの設定
	void SetSamplerState(void);			//	サンプラーステートの設定
	void SetTextureStageState(void);	//	テクスチャステージステートの設定
	void InitRenderTarget(void);		 // レンダーターゲットの初期化
	void Polygon2DInitialize(void);
	void Polygon2DDraw(void);
	void PolygonScreenInit(void);
	void PolygonScreenDraw(void);

#ifdef _DEBUG
	void DrawFPS(void); // FPS表示
#endif

private:
	static D3DXCOLOR m_BackBufferColor;	//	バックバッファ色
	static LPDIRECT3DDEVICE9 m_D3DDevice;	// Deviceオブジェクト(描画に必要)

	LPDIRECT3D9 m_D3D;	// Direct3Dオブジェクト

	LPDIRECT3DTEXTURE9 m_BlurTexture_1;// テクスチャ
    LPDIRECT3DSURFACE9 m_BlurSurface_1;// サーフェス
	LPDIRECT3DTEXTURE9 m_BlurTexture_2;
    LPDIRECT3DSURFACE9 m_BlurSurface_2;
    LPDIRECT3DSURFACE9 m_BackBufferSurface;// バックバッファ
	LPDIRECT3DVERTEXBUFFER9 m_VertexBuffer;
	LPDIRECT3DVERTEXBUFFER9 m_VertexBuffer2;

#ifdef _DEBUG
	LPD3DXFONT m_Font;	// フォントへのポインタ
#endif
};

#endif
