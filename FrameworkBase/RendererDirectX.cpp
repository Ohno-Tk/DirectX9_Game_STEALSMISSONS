/*=============================================================================

レンダラー(DirectX)[ RendererDirectX.cpp ]

-------------------------------------------------------------------------------
■  Author
	Ohno Takuya

■  Create
	2017/10/14
=============================================================================*/

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "Renderer.h"
#include "Common.h"
#include "GameLoop.h"
#include "RendererDirectX.h"

/*-----------------------------------------------------------------------------
Macro
-----------------------------------------------------------------------------*/
#define ENABLE_RENDERTARGET
#undef ENABLE_RENDERTARGET

/*-----------------------------------------------------------------------------
Static
-----------------------------------------------------------------------------*/
D3DXCOLOR RendererDirectX::m_BackBufferColor = D3DCOLOR_RGBA(0, 0, 0, 0);
LPDIRECT3DDEVICE9 RendererDirectX::m_D3DDevice = NULL;


RendererDirectX::RendererDirectX():
m_D3D(NULL),
m_BlurTexture_1(NULL),
m_BlurSurface_1(NULL),
m_BlurTexture_2(NULL),
m_BlurSurface_2(NULL),
m_BackBufferSurface(NULL),
m_VertexBuffer(NULL),
m_VertexBuffer2(NULL){}

HRESULT RendererDirectX::Initialize(HWND hWnd)
{
	HRESULT hr;

	D3DPRESENT_PARAMETERS d3dpp = {};
	D3DDISPLAYMODE d3ddm = {};


	// Direct3Dオブジェクトの作成
	m_D3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (!m_D3D)
	{
		MessageBox(NULL, "Direct3Dオブジェクトの作成に失敗", "RendererDirectX.cpp", MB_OK | MB_ICONHAND);
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得
	hr = m_D3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);
	if (FAILED(hr))
	{
		MessageBox(NULL, "ディスプレイモードの取得に失敗", "RendererDirectX.cpp", MB_OK | MB_ICONHAND);
		return E_FAIL;
	}

	hr = SetUpDevice(d3dpp, d3ddm, hWnd, true);	//	デバイスの初期化
	if (FAILED(hr))
	{
		MessageBox(NULL, "デバイスの初期化に失敗", "RendererDirectX.cpp", MB_OK | MB_ICONHAND);
		return E_FAIL;
	}

	SetRenderState();	//	レンダーステートの設定

	SetSamplerState();	//	サンプラーステートの設定

	SetTextureStageState();	//	テクスチャステージステートの設定

#ifdef ENABLE_RENDERTARGET
	InitRenderTarget(); // レンダーターゲットの初期化
	Polygon2DInitialize();
	PolygonScreenInit();
#endif

#ifdef _DEBUG
	// デバッグ情報表示用フォントを生成
	D3DXCreateFont(m_D3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_Font);
#endif

	return S_OK;
}

void RendererDirectX::Uninitialize(void)
{
#ifdef _DEBUG
	SAFE_RELEASE(m_Font);// 情報表示用フォント
#endif

	SAFE_RELEASE(m_D3D);//	Direct3Dオブジェクト

	SAFE_RELEASE(m_D3DDevice);// デバイスの破棄

#ifdef ENABLE_RENDERTARGET
	SAFE_RELEASE(m_BlurTexture_1);
	SAFE_RELEASE(m_BlurSurface_1);
	SAFE_RELEASE(m_BlurTexture_2);
	SAFE_RELEASE(m_BlurSurface_2);
	SAFE_RELEASE(m_BackBufferSurface);
	SAFE_RELEASE(m_VertexBuffer);
	SAFE_RELEASE(m_VertexBuffer2);
#endif
}

void RendererDirectX::DrawBegin(void)
{
#ifdef ENABLE_RENDERTARGET
	m_D3DDevice->SetRenderTarget(0, m_BlurSurface_2);
#endif

	// バックバッファ＆Ｚバッファのクリア
	m_D3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL), m_BackBufferColor, 1.0f, 0);

	m_D3DDevice->BeginScene(); // DirectXによる描画の開始
}

void RendererDirectX::DrawEnd(void)
{
#ifdef _DEBUG
	DrawFPS(); // FPS表示
#endif

	m_D3DDevice->EndScene(); // DirectXによる描画の終了

#ifdef ENABLE_RENDERTARGET
	m_D3DDevice->SetTexture(0, m_BlurTexture_1);

	// 2Dポリゴン描画
	Polygon2DDraw();

	m_D3DDevice->EndScene();

	m_D3DDevice->SetRenderTarget(0, m_BackBufferSurface);

	m_D3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL), m_BackBufferColor, 1.0f, 0);

	m_D3DDevice->BeginScene();

	m_D3DDevice->SetTexture(0, m_BlurTexture_2);

	//2Dポリゴン描画
	PolygonScreenDraw();

	m_D3DDevice->EndScene();


	// 入れ替え
	LPDIRECT3DTEXTURE9 texture;
	texture = m_BlurTexture_1;
	m_BlurTexture_1 = m_BlurTexture_2;
	m_BlurTexture_2 = texture;

	LPDIRECT3DSURFACE9 surface;
	surface = m_BlurSurface_1;
	m_BlurSurface_1 = m_BlurSurface_2;
	m_BlurSurface_2 = surface;
#endif
	
	m_D3DDevice->Present(NULL, NULL, NULL, NULL); // バックバッファとフロントバッファの入れ替え
}

/*-----------------------------------------------------------------------------
Function:   void RendererDirectX::SetTextureStageState(void)
Parameter:  D3DPRESENT_PARAMETERS d3dpp, D3DDISPLAYMODE d3ddm, HWND Wnd, bool Window
Overview:   デバイスの初期化
-----------------------------------------------------------------------------*/
HRESULT RendererDirectX::SetUpDevice(D3DPRESENT_PARAMETERS d3dpp, D3DDISPLAYMODE d3ddm, HWND Wnd, bool Window)
{
	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));							// ワークをゼロクリア
	d3dpp.BackBufferCount = 1;									// バックバッファの数
	d3dpp.BackBufferWidth = SCREEN_WIDTH;						// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;						// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;						// カラーモードの指定
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					// 映像信号に同期してフリップする
	d3dpp.EnableAutoDepthStencil = TRUE;						// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.Windowed = Window;									// ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// インターバル


	HRESULT hr;

	// デバイスの生成
	// ディスプレイアダプタを表すためのデバイスを作成
	// 描画と頂点処理をハードウェアで行なう
	hr = m_D3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		Wnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &m_D3DDevice);
	if (FAILED(hr))
	{
		// 上記の設定が失敗したら
		// 描画をハードウェアで行い、頂点処理はCPUで行なう
		hr = m_D3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			Wnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &m_D3DDevice);
		if (FAILED(hr))
		{
			// 上記の設定が失敗したら
			// 描画と頂点処理をCPUで行なう
			hr = m_D3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF, Wnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp, &m_D3DDevice);
			if (FAILED(hr))
			{

				MessageBox(NULL, "デバイスの生成に失敗", "RendererDirectX.cpp", MB_OK | MB_ICONHAND);
				return E_FAIL;
			}
		}
	}

	return S_OK;
}

/*-----------------------------------------------------------------------------
Function:   void RendererDirectX::SetTextureStageState(void)
Overview:   レンダーステートの設定
-----------------------------------------------------------------------------*/
void RendererDirectX::SetRenderState(void)
{
	m_D3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW); // カリングを行わない
	m_D3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE); // Zバッファを使用
	m_D3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE); // αブレンドを行う
	m_D3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA); // αソースカラーの指定
	m_D3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定
}

/*-----------------------------------------------------------------------------
Function:   void RendererDirectX::SetTextureStageState(void)
Overview:   サンプラーステートの設定
-----------------------------------------------------------------------------*/
void RendererDirectX::SetSamplerState(void)
{
	m_D3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP); // テクスチャＵ値の繰り返し設定
	m_D3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP); // テクスチャＶ値の繰り返し設定
	m_D3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// テクスチャ拡大時の補間設定
	m_D3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// テクスチャ縮小時の補間設定
}

/*-----------------------------------------------------------------------------
Function:   void RendererDirectX::SetTextureStageState(void)
Overview:   テクスチャステージステートの設定
-----------------------------------------------------------------------------*/
void RendererDirectX::SetTextureStageState(void)
{
	m_D3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// アルファブレンディング処理(初期値はD3DTOP_SELECTARG1)
	m_D3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// 最初のアルファ引数(初期値はD3DTA_TEXTURE、テクスチャがない場合はD3DTA_DIFFUSE)
	m_D3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);	// ２番目のアルファ引数(初期値はD3DTA_CURRENT)
}

#ifdef _DEBUG
/*-----------------------------------------------------------------------------
Function:   void RendererDirectX::DrawFPS(void)
Overview:   FPS表示
-----------------------------------------------------------------------------*/
void RendererDirectX::DrawFPS(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[256];
	int nCountFPS;

	// FPS取得
	nCountFPS = GameLoop::Instance()->GetFPS();
	wsprintf(str, "FPS:%d\n", nCountFPS);

	// テキスト描画
	m_Font->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}
#endif

/*-----------------------------------------------------------------------------
Function:   void RendererDirectX::Normal(void)
Overview:   ワイヤーフレーム
-----------------------------------------------------------------------------*/
void RendererDirectX::Normal(void)
{
	m_D3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_FORCE_DWORD);
}

/*-----------------------------------------------------------------------------
Function:   void RendererDirectX::WireFrame(void)
Overview:   通常時
-----------------------------------------------------------------------------*/
void RendererDirectX::WireFrame(void)
{
	m_D3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
}

/*-----------------------------------------------------------------------------
Function:   void RendererDirectX::InitRenderTarget(void)
Overview:   レンダーターゲットの初期化
-----------------------------------------------------------------------------*/
void RendererDirectX::InitRenderTarget(void)
{
	D3DXCreateTexture(m_D3DDevice,SCREEN_WIDTH, // テクスチャのピクセル数(横)
	 SCREEN_HEIGHT, // テクスチャのピクセル数(縦)
	 1, // ミップマップのレベル数
	 D3DUSAGE_RENDERTARGET, // どういう用途で使用するか
	 D3DFMT_A8R8G8B8, // ピクセルフォーマット
	 D3DPOOL_DEFAULT,
	 &m_BlurTexture_1);

	// サーフェースの取得
	m_BlurTexture_1->GetSurfaceLevel(0, &m_BlurSurface_1);

	D3DXCreateTexture(m_D3DDevice, SCREEN_WIDTH, SCREEN_HEIGHT, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_BlurTexture_2);

	m_BlurTexture_2->GetSurfaceLevel(0, &m_BlurSurface_2);

	// バックバッファのサーフェースを取得
	m_D3DDevice->GetRenderTarget(0, &m_BackBufferSurface);

}

void RendererDirectX::Polygon2DInitialize(void)
{
	if (FAILED(m_D3DDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_VertexBuffer, NULL)))
	{
		MessageBox(NULL, "頂点バッファの生成に失敗", "RendererDirectX.cpp", MB_OK | MB_ICONHAND);
		return;
	}

	// 頂点情報を設定
	VERTEX_2D* pVtx;

	// バッファをロックし、仮想アドレスを取得
	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);


	//	頂点座標
 // ブラーがかかる  頂点を少し大きくした
	pVtx[0].Pos = D3DXVECTOR3( -10.0f            ,-10.0f, 0.0f);
	pVtx[1].Pos = D3DXVECTOR3( SCREEN_WIDTH+10.0f,-10.0f, 0.0f);
	pVtx[2].Pos = D3DXVECTOR3( -10.0f            , SCREEN_HEIGHT+10.0f, 0.0f);
	pVtx[3].Pos = D3DXVECTOR3( SCREEN_WIDTH+10.0f, SCREEN_HEIGHT+10.0f, 0.0f);


/* // 少しぼやける   頂点を等しくした
	pVtx[0].Pos = D3DXVECTOR3( 0.0f        , 0.0f, 0.0f);
	pVtx[1].Pos = D3DXVECTOR3( SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].Pos = D3DXVECTOR3( 0.0f        , SCREEN_HEIGHT, 0.0f);
	pVtx[3].Pos = D3DXVECTOR3( SCREEN_WIDTH ,SCREEN_HEIGHT, 0.0f);
*/
/* // 中心に近づくようになる　頂点を少し小さくした
	pVtx[0].Pos = D3DXVECTOR3( 5.0f              , 5.0f, 0.0f);
	pVtx[1].Pos = D3DXVECTOR3( SCREEN_WIDTH-5.0f , 5.0f, 0.0f);
	pVtx[2].Pos = D3DXVECTOR3( 5.0f              , SCREEN_HEIGHT-5.0f, 0.0f);
	pVtx[3].Pos = D3DXVECTOR3( SCREEN_WIDTH-5.0f , SCREEN_HEIGHT-5.0f, 0.0f);
*/

	for(int i = 0; i < NUM_VERTEX; i++)
	{
		pVtx[i].Rhw = 1.0f;
		pVtx[i].Color = D3DXCOLOR(1.0f,1.0f,1.0f, 0.99f);
	}
	// テクスチャ座標
	pVtx[0].Tex = D3DXVECTOR2(0, 0);
	pVtx[1].Tex = D3DXVECTOR2(1, 0);
	pVtx[2].Tex = D3DXVECTOR2(0, 1);
	pVtx[3].Tex = D3DXVECTOR2(1, 1);

	//	バッファをアンロック
	m_VertexBuffer->Unlock();
}

void RendererDirectX::Polygon2DDraw(void)
{
	m_D3DDevice->SetStreamSource(0, m_VertexBuffer, 0, sizeof(VERTEX_2D));

	m_D3DDevice->SetFVF(FVF_VERTEX_2D);

	m_D3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

void RendererDirectX::PolygonScreenInit(void)
{
	if (FAILED(m_D3DDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_VertexBuffer2, NULL)))
	{
		MessageBox(NULL, "頂点バッファの生成に失敗", "RendererDirectX.cpp", MB_OK | MB_ICONHAND);
		return;
	}

	// 頂点情報を設定
	VERTEX_2D* pVtx;

	// バッファをロックし、仮想アドレスを取得
	m_VertexBuffer2->Lock(0, 0, (void**)&pVtx, 0);


	//	頂点座標
	pVtx[0].Pos = D3DXVECTOR3( 0.0f        ,  0.0f, 0.0f);
	pVtx[1].Pos = D3DXVECTOR3( SCREEN_WIDTH,  0.0f, 0.0f);
	pVtx[2].Pos = D3DXVECTOR3( 0.0f        , SCREEN_HEIGHT, 0.0f);
	pVtx[3].Pos = D3DXVECTOR3( SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);


	for(int i = 0; i < NUM_VERTEX; i++)
	{
		pVtx[i].Rhw = 1.0f;
		pVtx[i].Color = D3DXCOLOR(1.0f,1.0f,1.0f, 1.0f);
	}
	// テクスチャ座標
	pVtx[0].Tex = D3DXVECTOR2(0, 0);
	pVtx[1].Tex = D3DXVECTOR2(1, 0);
	pVtx[2].Tex = D3DXVECTOR2(0, 1);
	pVtx[3].Tex = D3DXVECTOR2(1, 1);

	//	バッファをアンロック
	m_VertexBuffer2->Unlock();
}

void RendererDirectX::PolygonScreenDraw(void)
{
	m_D3DDevice->SetStreamSource(0, m_VertexBuffer2, 0, sizeof(VERTEX_2D));

	m_D3DDevice->SetFVF(FVF_VERTEX_2D);

	m_D3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
//	m_D3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	m_D3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	m_D3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
//	m_D3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
}