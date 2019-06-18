/*=============================================================================

メッシュエフェクト[ MeshEffect.cpp ]

-------------------------------------------------------------------------------
■  Author
Ohno Takuya

■  Create
2017/11/13
=============================================================================*/

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include <assert.h>
#include "FrameworkBase\Common.h"
#include "FrameworkBase\RendererDirectX.h"
#include "FrameworkBase\Game.h"
#include "FrameworkBase\TextureManagerDirectX.h"
#include "Object.h"
#include "MeshEffect.h"

MeshEffect::MeshEffect(int Priolity):Object(Priolity)
{
	m_VertexBuffer = NULL;
	m_IndexBuffer = NULL;

	m_TopPosition = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_ButtomPosition = D3DXVECTOR3(0.0f,0.0f,0.0f);

	m_TexturePositon = D3DXVECTOR2(0.0f,0.0f);

	m_NumBlock_X = 0;
	m_NumBlock_Y = 1;

	m_NumVertex = 0;
	m_NumIndexBuffer = 0;
}

/*-----------------------------------------------------------------------------
Function:   MeshEffect* MeshEffect::Create(UINT numBlock_X)
Parameter:  UINT numBlock_X
              横の枚数
Overview:   生成
-----------------------------------------------------------------------------*/
MeshEffect* MeshEffect::Create(UINT numBlock_X)
{
	auto object = new MeshEffect;

	object->m_NumBlock_X = numBlock_X;

	object->Initialize();

	return object;
}

void MeshEffect::Initialize(void)
{
	SetVertexCount(m_NumBlock_X, m_NumBlock_Y); // 頂点数の計算
	SetIndexBufferCount(m_NumBlock_X, m_NumBlock_Y);   // インデックスバッファの計算


	LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();

	MakeVerTex(Device); // 頂点の作成
	MakeIndex(Device);  // インデックスバッファの作成

	// 初期化
	for(int i = 0; i < m_NumVertex; i++)
	{
		m_VertexPosition.push_back(D3DXVECTOR3(0.0f,0.0f,0.0f));
	}
}

void MeshEffect::Uninitialize(void)
{
	m_VertexPosition.clear(); // 要素の解放
	std::vector<D3DXVECTOR3>().swap(m_VertexPosition); // メモリの解放

	SAFE_RELEASE(m_VertexBuffer);

	SAFE_RELEASE(m_IndexBuffer);

	Object::Release();
}

void MeshEffect::Update(void)
{
	for(unsigned int i = 0; i < m_NumBlock_X; i++)
	{
		m_VertexPosition[i*2] = m_VertexPosition[i*2+2];
		m_VertexPosition[i*2+1] = m_VertexPosition[i*2+3];
	}
	m_VertexPosition[m_NumBlock_X*2] = m_TopPosition;
	m_VertexPosition[m_NumBlock_X*2+1] = m_ButtomPosition;

	SetUpVerTex(); // 頂点の設定
}

void MeshEffect::Draw(void)
{
	LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();


	Device->SetStreamSource(0, m_VertexBuffer, 0, sizeof(VERTEX_3D));

	Device->SetIndices(m_IndexBuffer);

	Device->SetFVF(FVF_VERTEX_3D);

	auto textureManager = Game::GetInstance()->GetTextureManager();
	Device->SetTexture(0, NULL);

	WorldTransform(Device);

	// カリングoff
	Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	Device->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_NumIndexBuffer, 0, m_NumIndexBuffer - 2);

	// カリングon
	Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

/*-----------------------------------------------------------------------------
Function:   void MeshEffect::MakeVerTex(LPDIRECT3DDEVICE9 Device)
Parameter:  LPDIRECT3DDEVICE9 Device
              デバイス
Overview:   頂点の作成
-----------------------------------------------------------------------------*/
void MeshEffect::MakeVerTex(LPDIRECT3DDEVICE9 Device)
{
	if (FAILED(Device->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * m_NumVertex, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_VertexBuffer, NULL)))
	{
		MessageBox(NULL, "頂点バッファの生成エラー", "MeshEffect.cpp", MB_OK | MB_ICONHAND);
	}
}

/*-----------------------------------------------------------------------------
Function:   void MeshEffect::SetUpVerTex(void)
Overview:   頂点の設定
-----------------------------------------------------------------------------*/
void MeshEffect::SetUpVerTex(void)
{
	int Index = 0;
	VERTEX_3D* pVtx;

	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

	//	縦
	for (UINT i = 0; i < m_NumBlock_Y; i++)
	{

		Index = i * (m_NumBlock_X + 1);

		//	横
		for (UINT j = 0; j < (m_NumBlock_X + 1) * 2; j++)
		{
			//	頂点座標
			pVtx[j + Index].Pos = m_VertexPosition[j + Index];

			//	法線
			pVtx[j + Index].Nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//	頂点色
			pVtx[j + Index].Color = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

			//	テクスチャ座標
			pVtx[j + Index].Tex = D3DXVECTOR2((float)j, (float)i);
		}
	}

	m_VertexBuffer->Unlock();
}

/*-----------------------------------------------------------------------------
Function:   void MeshEffect::MakeIndex(LPDIRECT3DDEVICE9 Device)
Parameter:  LPDIRECT3DDEVICE9 Device
              デバイス
Overview:   インデックスバッファの作成
-----------------------------------------------------------------------------*/
void MeshEffect::MakeIndex(LPDIRECT3DDEVICE9 Device)
{
	HRESULT hr;

	WORD* pIdx;

	//	インデックスバッファの生成
	hr = Device->CreateIndexBuffer(
		sizeof(WORD) * m_NumIndexBuffer,	//	バッファ量
		D3DUSAGE_WRITEONLY,	//	使用方法フラグ
		D3DFMT_INDEX16, //	インデックスフォーマット
		D3DPOOL_MANAGED, //	メモリの管理方法
		&m_IndexBuffer,	//	インデックスバッファインターフェースへのポインタのアドレス
		NULL);


	if (FAILED(hr))
	{
		MessageBox(NULL, "インデックスバッファの生成失敗", "MeshEffect.cpp", MB_OK | MB_ICONHAND);
	}


	//	インデックスバッファをロック
	m_IndexBuffer->Lock(0, 0, (void**)&pIdx, 0);

	//	時計回りを裏面とする
	//	縦
	for (UINT Cnt1 = 0; Cnt1 < m_NumBlock_Y; Cnt1++)
	{

		//	はじめじゃなかったら
		//	縮退ポリゴン
		if (Cnt1 != 0)
		{

			//	1点打つ
			pIdx[0] = (WORD)((Cnt1 + 1) * (m_NumBlock_X + 1));

			pIdx++;	//	ポインタをずらす
		}

		//	2点打つ
		pIdx[0] = (WORD)((Cnt1 + 1) * (m_NumBlock_X + 1));
		pIdx[1] = (WORD)((Cnt1 + 1) * (m_NumBlock_X + 1) - (m_NumBlock_X + 1));

		pIdx += 2;	//	ポインタをずらす

		//	横
		for (UINT Cnt2 = 0; Cnt2 < m_NumBlock_X; Cnt2++)
		{

			//	2点打つ
			pIdx[0] = (WORD)(((Cnt1 + 1) * (m_NumBlock_X + 1) + 1) + Cnt2);
			pIdx[1] = (WORD)(((Cnt1 + 1) * (m_NumBlock_X + 1) + 1) - (m_NumBlock_X + 1) + Cnt2);

			pIdx += 2;	//	ポインタをずらす

		}

		//	最後じゃなかったら
		//	縮退ポリゴン
		if (Cnt1 != m_NumBlock_Y - 1)
		{

			//	1点打つ
			pIdx[0] = (WORD)((Cnt1 + 1) * (m_NumBlock_X + 1) - 1);

			pIdx++;	//	ポインタをずらす
		}
	}

	//	インデックスバッファのアンロック
	m_IndexBuffer->Unlock();
}

/*-----------------------------------------------------------------------------
Function:   void MeshEffect::SetIdxVerTex(const UINT NumBlock_X, const UINT NumBlock_Y)
Parameter:  const UINT NumBlock_X
              横の枚数
            const UINT NumBlock_Y
              縦の枚数
Overview:   頂点数の計算
-----------------------------------------------------------------------------*/
void MeshEffect::SetVertexCount(const UINT NumBlock_X, const UINT NumBlock_Y)
{
	m_NumVertex = (NumBlock_X + 1) * (NumBlock_Y + 1);
}

/*-----------------------------------------------------------------------------
Function:   void MeshEffect::SetIndexBufferCount(const UINT NumBlock_X, const UINT NumBlock_Y)
Parameter:  const UINT NumBlock_X
              横の枚数
            const UINT NumBlock_Y
              縦の枚数
Overview:   インデックスバッファの計算
-----------------------------------------------------------------------------*/
void MeshEffect::SetIndexBufferCount(const UINT NumBlock_X, const UINT NumBlock_Y)
{
	m_NumIndexBuffer = (2 + 2 * NumBlock_X) * NumBlock_Y + (NumBlock_Y - 1) * 2;
}

/*-----------------------------------------------------------------------------
Function:   void MeshEffect::WorldTransform(LPDIRECT3DDEVICE9 Device)
Parameter:  LPDIRECT3DDEVICE9 Device
              デバイス
Overview:   ワールド座標変換
-----------------------------------------------------------------------------*/
void MeshEffect::WorldTransform(LPDIRECT3DDEVICE9 Device)
{
	D3DXMATRIX matrixWorld;

	D3DXMatrixIdentity(&matrixWorld);	//	行列を単位行列にする

	//	デバイスにワールド変換行列を設定
	Device->SetTransform(D3DTS_WORLD, &matrixWorld);
}