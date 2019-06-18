/*=============================================================================

ステンシルシャドウ[ StencilShadow.cpp ]

-------------------------------------------------------------------------------
■  Author
	Ohno Takuya

■  Create
	2017/11/09
=============================================================================*/

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "FrameworkBase\Common.h"
#include "FrameworkBase\RendererDirectX.h"
#include "FrameworkBase\Game.h"
#include "FrameworkBase\ModelManagerDirectX.h"
#include "Object.h"
#include "StencilShadow.h"

/*-----------------------------------------------------------------------------
Function:   StencilShadow* StencilShadow::Create(char* modelFileName)
Parameter:  char* modelFileName
              モデルのファイル名
Overview:   生成
-----------------------------------------------------------------------------*/
StencilShadow* StencilShadow::Create(char* modelFileName)
{
	auto object = new StencilShadow;

	object->m_ModelFilePath = modelFileName;

	object->Initialize();

	return object;
}

void StencilShadow::Initialize(void)
{
	MakeVerTex(); // 頂点の作成
}

void StencilShadow::Uninitialize(void)
{
	SAFE_RELEASE(m_VertexBuffer);

	Object::Release();	//	オブジェクト自身の解放
}

void StencilShadow::Draw(void)
{
	LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();

	Device->SetVertexShader(NULL);
	Device->SetPixelShader(NULL);
	
	//	ワールド座標変換
	WorldTransform(Device);
	
	// 表面描画
	Device->SetRenderState(D3DRS_STENCILENABLE, TRUE);
	Device->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	Device->SetRenderState(D3DRS_COLORWRITEENABLE, 0);
	Device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
	Device->SetRenderState(D3DRS_STENCILREF, 1);
	Device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);
	Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	
	ModelDraw(Device);
	
	// 裏面描画
	Device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_DECR);
	Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	
	ModelDraw(Device);
	
	Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	Device->SetRenderState(D3DRS_COLORWRITEENABLE, 0xf);
	Device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
	
	// 2Dポリゴン描画
	Polygon2DDraw( Device);
	
	Device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	Device->SetRenderState(D3DRS_STENCILENABLE, FALSE);
}

/*-----------------------------------------------------------------------------
Function:   void StencilShadow::ModelDraw(LPDIRECT3DDEVICE9 Device)
Parameter:  LPDIRECT3DDEVICE9 Device
              デバイス
Overview:   モデル描画
-----------------------------------------------------------------------------*/
void StencilShadow::ModelDraw(LPDIRECT3DDEVICE9 Device)
{
	D3DMATERIAL9 materialDefault;

	ModelManagerDirectX* ModelManager = Game::GetInstance()->GetModelManager();

	// モデルの取得
	m_ModelParam = ModelManager->GetModelParam(m_ModelFilePath);

	WorldTransform(Device);

	//	現在デバイスに設定されているマテリアル情報の取得
	Device->GetMaterial(&materialDefault);

	// 現在のマテリアルを取得
	Device->GetMaterial(&materialDefault);

	// マテリアルへのポインタを取得
	m_ModelParam.Material = (D3DXMATERIAL*)m_ModelParam.BufferMaterial->GetBufferPointer();

	for (int CountMaterial = 0; CountMaterial < (int)m_ModelParam.NumMaterial; CountMaterial++)
	{
		// デバイスにマテリアルの設定
		Device->SetMaterial(&m_ModelParam.Material[CountMaterial].MatD3D);

		// テクスチャの設定
		Device->SetTexture(0, m_ModelParam.Texture[CountMaterial]);

		// 描画
		m_ModelParam.Mesh->DrawSubset(CountMaterial);
	}

	// マテリアルを元に戻す
	Device->SetMaterial(&materialDefault);
}

/*-----------------------------------------------------------------------------
Function:   void StencilShadow::Polygon2DDraw(LPDIRECT3DDEVICE9 Device)
Parameter:  LPDIRECT3DDEVICE9 Device
              デバイス
Overview:   全画面2Dポリゴン描画
-----------------------------------------------------------------------------*/
void StencilShadow::Polygon2DDraw(LPDIRECT3DDEVICE9 Device)
{
	// 頂点バッファをデータストリームに設定
	Device->SetStreamSource(0, m_VertexBuffer, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	Device->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	Device->SetTexture(0, NULL);

	// 描画
	Device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

/*-----------------------------------------------------------------------------
Function:   void StencilShadow::MakeVerTex(void)
Parameter:  
Overview:   頂点の作成
-----------------------------------------------------------------------------*/
void StencilShadow::MakeVerTex(void)
{
	//	デバイスの取得
	LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();

	// 頂点バッファの生成
	if (FAILED(Device->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_VertexBuffer, NULL)))
	{
		MessageBox(NULL, "頂点バッファの生成に失敗", "StencilShadow.cpp", MB_OK | MB_ICONHAND);
	}

	// 頂点情報を設定
	VERTEX_2D* pVtx;

	// バッファをロックし、仮想アドレスを取得
	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

	//	頂点座標
	pVtx[0].Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].Pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].Pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].Pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	for(unsigned int CountVertex = 0; CountVertex < NUM_VERTEX; CountVertex++)
	{
		pVtx[CountVertex].Rhw = 1.0f; //	座標変換済み頂点フラグ
		pVtx[CountVertex].Color = D3DXCOLOR(0.0f,0.0f,0.0f,0.4f); // 頂点カラー
	}

	// テクスチャ座標
	pVtx[0].Tex = D3DXVECTOR2(0, 0);
	pVtx[1].Tex = D3DXVECTOR2(1, 0);
	pVtx[2].Tex = D3DXVECTOR2(0, 1);
	pVtx[3].Tex = D3DXVECTOR2(1, 1);

	//	バッファをアンロック
	m_VertexBuffer->Unlock();
}

/*-----------------------------------------------------------------------------
Function:   void StencilShadow::WorldTransform(LPDIRECT3DDEVICE9 Device)
Parameter:  LPDIRECT3DDEVICE9 Device
              デバイス
Overview:   全画面2Dポリゴン描画
-----------------------------------------------------------------------------*/
void StencilShadow::WorldTransform(LPDIRECT3DDEVICE9 Device)
{
	D3DXMATRIX matrixPosition;

	D3DXVECTOR3 position = Object::GetPosition();

	D3DXMatrixIdentity(&m_MatrixWorld);

	D3DXMatrixTranslation(&matrixPosition,
		position.x,	//	X軸移動
		position.y,	//	Y軸移動
		position.z);	//	Z軸移動

	D3DXMatrixMultiply(&m_MatrixWorld, &m_MatrixWorld, &matrixPosition);

	Device->SetTransform(D3DTS_WORLD, &m_MatrixWorld);
}