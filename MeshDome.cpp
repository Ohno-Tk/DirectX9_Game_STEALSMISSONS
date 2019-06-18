/*=============================================================================

メッシュ半球[ MeshDome.cpp ]

-------------------------------------------------------------------------------
■  Author
	Ohno Takuya

■  Create
	2017/05/12
=============================================================================*/

/*-----------------------------------------------------------------------------
	Header
-----------------------------------------------------------------------------*/
#include "FrameworkBase\Common.h"
#include "FrameworkBase\RendererDirectX.h"
#include "FrameworkBase\Game.h"
#include "FrameworkBase\TextureManagerDirectX.h"
#include "Object.h"
#include "MeshDome.h"

/*-----------------------------------------------------------------------------
	Static
-----------------------------------------------------------------------------*/
LPDIRECT3DTEXTURE9 MeshDome::m_Texture = NULL;	// テクスチャ

/*-----------------------------------------------------------------------------
Namespace
-----------------------------------------------------------------------------*/
using namespace std;


MeshDome::MeshDome(int Priolity) : Object(Priolity)
{
	m_VertexBuffer = NULL;
	m_IndexBuffer = NULL;

	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	m_TexturePositon = D3DXVECTOR2(0.0f, 0.0f);

	m_NumBlock_X = 0;
	m_NumBlock_Y = 0;
	m_NumVertex = 0;
	m_NumIndexBuffer = 0;

	m_Radius = 0.0f;

	m_IndexBackDraw = IDXBACK_DRAW_CLOCKWISE;
}

MeshDome *MeshDome::Create(D3DXVECTOR3 Pos, UINT NumBlock_X, UINT NumBlock_Y, float Radius, IDXBACK_DRAW IdxBack, char* TextureName)
{
	auto object= new MeshDome;

	object->SetPosition( Pos );

	object->SetNumBlock( NumBlock_X , NumBlock_Y );

	object->SetVertexCount( NumBlock_X , NumBlock_Y );

	object->SetIndexBufferCount( NumBlock_X , NumBlock_Y );

	object->SetIndexBackDraw( IdxBack );

	object->SetTexture( TextureName );

	object->m_Radius = Radius;

	object->Initialize();

	return object;
}

void MeshDome::Initialize(void)
{
	LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();
	
	MakeVerTex(Device);
		
	MakeIndex(Device);
}

void MeshDome::Uninitialize(void)
{
	SAFE_RELEASE(m_VertexBuffer);

	SAFE_RELEASE(m_IndexBuffer);

	Object::Release();	//	オブジェクト自身の解放
}

void MeshDome::Draw(void)
{
	LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();


	Device->SetStreamSource(0, m_VertexBuffer, 0, sizeof(VERTEX_3D));

	Device->SetIndices(m_IndexBuffer);

	Device->SetFVF(FVF_VERTEX_3D);

	TextureManagerDirectX* manager = Game::GetInstance()->GetTextureManager();
	Device->SetTexture(0, manager->GetTextureInfo(m_TexturePath).Texture);

	WorldTransform(Device);

	Device->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_NumIndexBuffer, 0, m_NumIndexBuffer - 2);

}

/*-----------------------------------------------------------------------------
頂点の作成
-----------------------------------------------------------------------------*/
void MeshDome::MakeVerTex(LPDIRECT3DDEVICE9 Device)
{

	if (FAILED(Device->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * m_NumVertex, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_VertexBuffer, NULL)))
	{
		MessageBox(NULL, "頂点バッファの生成エラー", "MeshDome.cpp", MB_OK | MB_ICONHAND);
	}

	//	仮想アドレスを取得するポインタ変数
	VERTEX_3D* pVtx;

	//	座標の格納変数
	D3DXVECTOR3 Pos;

	//	360度の一つ分の角度求める
	float Rot_XZ = 360.0f / m_NumBlock_X;

	//	90度の一つ分の角度求める
	float Rot_Y = 90.0f / m_NumBlock_Y;

	//	一つのUV座標を求める
	m_TexturePositon.x = 1.0f / m_NumBlock_X;
	m_TexturePositon.y = 1.0f / m_NumBlock_Y;


	//	バッファをロックし仮想アドレスを取得する
	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

	//	縦
	for (UINT Cnt1 = 0; Cnt1 < m_NumBlock_Y + 1; Cnt1++)
	{

		//	角度の設定
		float θy = 90 - (Cnt1 * Rot_Y);

		//	最初に90度から求める
		//	90度から引いていく
		Pos.y = m_Radius * sinf(D3DXToRadian(θy));

		//	横
		for (UINT Cnt2 = 0; Cnt2 < m_NumBlock_X + 1; Cnt2++)
		{
			//	角度の設定
			float θxz = Cnt2 * Rot_XZ;

			//	XZ軸で360度求める
			Pos.x = m_Radius * cosf(D3DXToRadian(θy)) * cosf(D3DXToRadian(θxz));
			Pos.z = m_Radius * cosf(D3DXToRadian(θy)) * sinf(D3DXToRadian(θxz));


			//	頂点座標の設定
			pVtx[0].Pos = Pos;


			//	法線の設定
			pVtx[0].Nor = D3DXVECTOR3(0.0f, 10.0f, 0.0f);


			//	頂点色の設定
			pVtx[0].Color = D3DCOLOR_RGBA(255, 255, 255, 255);


			//	テクスチャ座標の設定
			pVtx[0].Tex = D3DXVECTOR2(Cnt2 * m_TexturePositon.x, Cnt1 * m_TexturePositon.y);

			pVtx++;	//	ポインタをずらす

		}
	}

	//	バッファのアンロック
	m_VertexBuffer->Unlock();

}

/*-----------------------------------------------------------------------------
インデックスバッファの作成
-----------------------------------------------------------------------------*/
void MeshDome::MakeIndex(LPDIRECT3DDEVICE9 Device)
{

	HRESULT hr;

	WORD* pIdx;	//	ポインタ変数

	//	インデックスバッファの生成
	hr = Device->CreateIndexBuffer(
		sizeof(WORD) * m_NumIndexBuffer,	//	バッファ量
		D3DUSAGE_WRITEONLY,	//	使用方法フラグ
		D3DFMT_INDEX16, //	インデックスフォーマット
		D3DPOOL_MANAGED, //	メモリの管理方法
		&m_IndexBuffer,	//	インデックスバッファインターフェースへのポインタのアドレス
		NULL);


	//	インデックスバッファのエラーチェック
	if (FAILED(hr))
	{
		MessageBox(NULL, "インデックスバッファの生成失敗", "Mesh.cpp", MB_OK | MB_ICONHAND);
	}


	//	インデックスバッファをロック
	m_IndexBuffer->Lock(0, 0, (void**)&pIdx, 0);


	if (m_IndexBackDraw == IDXBACK_DRAW_CLOCKWISE)
	{	//	時計回り

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
	}
	else
	{

		//	逆時計回りを裏面とする
		//	縦
		for (UINT Cnt1 = 0; Cnt1 < m_NumBlock_Y; Cnt1++)
		{
			//	はじめじゃなかったら
			//	縮退ポリゴン
			if (Cnt1 != 0)
			{
				//	1点打つ

				pIdx[0] = (WORD)((Cnt1 + 1) * (m_NumBlock_X + 1) - 1);

				pIdx++;	//	ポインタをずらす

			}

				//	2点打つ
			pIdx[1] = (WORD)((Cnt1 + 1) * (m_NumBlock_X + 1));
			pIdx[0] = (WORD)((Cnt1 + 1) * (m_NumBlock_X + 1) - (m_NumBlock_X + 1));

			pIdx += 2;	//	ポインタをずらす

			//	横
			for (UINT Cnt2 = 0; Cnt2 < m_NumBlock_X; Cnt2++)
			{
				//	2点打つ
				pIdx[1] = (WORD)(((Cnt1 + 1) * (m_NumBlock_X + 1) + 1) + Cnt2);
				pIdx[0] = (WORD)(((Cnt1 + 1) * (m_NumBlock_X + 1) + 1) - (m_NumBlock_X + 1) + Cnt2);

				pIdx += 2;	//	ポインタをずらす

			}

				//	最後じゃなかったら
				//	縮退ポリゴン
			if (Cnt1 != m_NumBlock_Y - 1)
			{
				//	1点打つ
				pIdx[0] = (WORD)((Cnt1 + 1) * (m_NumBlock_X + 1));

				pIdx++;	//	ポインタをずらす

			}
		}
	}

	//	インデックスバッファのアンロック
	m_IndexBuffer->Unlock();

}

/*-----------------------------------------------------------------------------
ワールド座標変換
-----------------------------------------------------------------------------*/
void MeshDome::WorldTransform(LPDIRECT3DDEVICE9 Device)
{
	D3DXVECTOR3 Position = Object::GetPosition();


	D3DXMATRIX matrixScale, matrixRotation, matrixPosision;

	D3DXMatrixIdentity(&m_MatixWorld);	//	行列を単位行列にする


	//	拡大行列を作る
	D3DXMatrixScaling(&matrixScale,	//拡大行列が作られる
		m_Scale.x,	//	X軸拡大
		m_Scale.y,	//	Y軸拡大
		m_Scale.z);	//	Z軸拡大

	//	回転行列を作る
	D3DXMatrixRotationYawPitchRoll(&matrixRotation,	//	回転行列が作られる
		D3DXToRadian(m_Rotation.y), //	Y軸回転
		D3DXToRadian(m_Rotation.x), //	X軸回転
		D3DXToRadian(m_Rotation.z)); //	Z軸回転

	//	平行移動行列を作る
	D3DXMatrixTranslation(&matrixPosision,
		Position.x,	//	X軸移動
		Position.y,	//	Y軸移動
		Position.z);	//	Z軸移動


	//	掛ける
	D3DXMatrixMultiply(&m_MatixWorld, &m_MatixWorld, &matrixScale);
	D3DXMatrixMultiply(&m_MatixWorld, &m_MatixWorld, &matrixRotation);
	D3DXMatrixMultiply(&m_MatixWorld, &m_MatixWorld, &matrixPosision);

	//	デバイスにワールド変換行列を設定
	Device->SetTransform(D3DTS_WORLD, &m_MatixWorld);

}