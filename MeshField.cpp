/*=============================================================================

メッシュフィールド[ MeshField.cpp ]

-------------------------------------------------------------------------------
■  Author
	Ohno Takuya

■  Created Date
	2017/06/13
=============================================================================*/

/*-----------------------------------------------------------------------------
	Header
-----------------------------------------------------------------------------*/
#include "FrameworkBase\Common.h"
#include "FrameworkBase\RendererDirectX.h"
#include "FrameworkBase\Game.h"
#include "FrameworkBase\TextureManagerDirectX.h"
#include "FrameworkBase\CameraDirectX.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Object.h"
#include "MeshField.h"

/*-----------------------------------------------------------------------------
Macro
-----------------------------------------------------------------------------*/
#define MODEL_VERTEXSHADER_PATH (SHADER_PATH"Mesh_Vertex.hlsl")
#define MODEL_PIXELSHADER_PATH (SHADER_PATH"Mesh_Pixel.hlsl")

/*-----------------------------------------------------------------------------
	Static
-----------------------------------------------------------------------------*/
LPDIRECT3DTEXTURE9 MeshField::m_Texture = NULL;	// テクスチャ

/*-----------------------------------------------------------------------------
Namespace
-----------------------------------------------------------------------------*/
using namespace std;


MeshField::MeshField(int Priolity) : Object(Priolity)
{
	m_VertexBuffer = NULL;
	m_IndexBuffer = NULL;

	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_TexturePositon = D3DXVECTOR2(0.0f, 0.0f);

	m_NumBlock_X = 0;
	m_NumBlock_Y = 0;
	m_NumVertex = 0;
	m_NumIndexBuffer = 0;

	m_IndexBackDraw = IDXBACK_DRAW_CLOCKWISE;
}

MeshField* MeshField::Create(D3DXVECTOR3 Pos, UINT NumBlock_X, UINT NumBlock_Z, float SizeBlock_X, float SizeBlock_Z, char* tecturePath)
{
	auto *object = new MeshField;

	object->SetPosition( Pos );

	object->m_NumBlock_X = NumBlock_X;
	object->m_NumBlock_Y = NumBlock_Z;

	object->SetVertexCount( NumBlock_X , NumBlock_Z );
	object->SetIndexBufferCount( NumBlock_X , NumBlock_Z );

	object->m_IndexBackDraw = IDXBACK_DRAW_CLOCKWISE;

	object->m_SizeBlock_X = SizeBlock_X;
	object->m_SizeBlock_Z = SizeBlock_Z;

	object->m_TexturePath = tecturePath;

	object->Initialize();

	return object;
}

void MeshField::Initialize(void)
{
	LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();
		
	MakeVerTex(Device);

	MakeIndex(Device);

	m_VertexShader = new VertexShader;
	m_VertexShader->Initialize(MODEL_VERTEXSHADER_PATH);

	m_PixelShader = new PixelShader;
	m_PixelShader->Initialize(MODEL_PIXELSHADER_PATH);

}

void MeshField::Uninitialize(void)
{
	SAFE_RELEASE(m_VertexBuffer);

	SAFE_RELEASE(m_IndexBuffer);

	SAFE_UNINIT(m_VertexShader);
	SAFE_UNINIT(m_PixelShader);

	Object::Release();	//	オブジェクト自身の解放
}

void MeshField::Draw(void)
{
	LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();


	D3DVERTEXELEMENT9 elements[] = {
	{0 ,0 ,D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
	{0 ,12 ,D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
	{0 ,24 ,D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
	D3DDECL_END()
	};
	Device->CreateVertexDeclaration(elements,&m_VertexDeclaration);

	Device->SetStreamSource(0, m_VertexBuffer, 0, sizeof(VERTEX_3D));

	Device->SetIndices(m_IndexBuffer);

	Device->SetFVF(FVF_VERTEX_3D);

	UINT samplerIndex0 = m_PixelShader->GetPixelShaderConstantTable()->GetSamplerIndex("sampler0");
	Device->SetTexture(samplerIndex0, Game::GetInstance()->GetTextureManager()->GetTextureInfo(m_TexturePath).Texture);

	WorldTransform(Device);
	ConfigShader(Device);

	Device->SetVertexShader(m_VertexShader->GetVertexShader());
	Device->SetPixelShader(m_PixelShader->GetPixelShader());

	Device->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_NumIndexBuffer, 0, m_NumIndexBuffer - 2);

}

/*-----------------------------------------------------------------------------
頂点の作成
-----------------------------------------------------------------------------*/
void MeshField::MakeVerTex(LPDIRECT3DDEVICE9 Device)
{

	if (FAILED(Device->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * m_NumVertex, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_VertexBuffer, NULL)))
	{
		MessageBox(NULL, "頂点バッファの生成エラー", "MeshField.cpp", MB_OK | MB_ICONHAND);
	}

	
	// 構造体のポインタ宣言
	VERTEX_3D* pVtx;

	D3DXVECTOR3 position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	頂点座標

	D3DXVECTOR3 Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		//	法線の計算結果
	D3DXVECTOR3 Normal_X = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	X座標法線
	D3DXVECTOR3 Normal_Z = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	Z座標法線

	D3DXVECTOR3 Direction_X = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 Direction_Z = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	int Index = 0;


	//	一つのUV座標を求める
	m_TexturePositon.x = 1.0f / m_NumBlock_X;
	m_TexturePositon.y = 1.0f / m_NumBlock_Y;


	//	バッファをロックし仮想アドレスを取得する
	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);


	//	縦
	for (UINT i = 0; i < m_NumBlock_Y + 1; i++)
	{

		Index = i * (m_NumBlock_X + 1 );

		//	横
		for (UINT j = 0; j < (m_NumBlock_X + 1) * 2; j++)
		{

			//	座標の設定
			position.x = (m_SizeBlock_X * m_NumBlock_X / 2) - m_NumBlock_X * m_SizeBlock_X + (m_SizeBlock_X * j);
			position.y = 0.0f;
			position.z = (m_SizeBlock_Z * m_NumBlock_Y / 2) - (m_SizeBlock_Z * i);


			//	頂点座標の設定
			pVtx[j + Index].Pos = position;

			pVtx[j + Index].Nor = D3DXVECTOR3(0.0f,1.0f,0.0f);


			//	頂点色の設定
			pVtx[j + Index].Color = D3DCOLOR_RGBA(255, 255, 255, 255);


			//	テクスチャ座標の設定
			pVtx[j + Index].Tex = D3DXVECTOR2((float)j, (float)i);

		}
	}


	//	法線の計算
	//	縦
/*	for (UINT i = 1; i <= m_NumBlock_Y; i++)
	{

		Index = i * (m_NumBlock_X + 1);

		//	横
		for (UINT j = 1; j <= m_NumBlock_X; j++)
		{

			//	X軸法線( 終点から始点を引く )
			Direction_X = pVtx[j + Index + 1].Pos - pVtx[j + Index - 1].Pos;
			
			//	yとxに対する法線ベクトル
/*			Normal_X.x = -Direction_X.y;
			Normal_X.y = Direction_X.x;
			Normal_X.z = 0.0f;

			//	Z軸法線( 終点から始点を引く )
			Direction_Z = pVtx[j + Index - m_NumBlock_X].Pos - pVtx[j + Index + m_NumBlock_X].Pos;
			
			//	yとzに対する法線ベクトル
			Normal_Z.x = 0.0f;
			Normal_Z.y = Direction_Z.z;
			Normal_Z.z = -Direction_Z.y;

			//	ベクトルの合成
			Normal = Normal_X + Normal_Z;

			//	単位行列にする
			D3DXVec3Normalize(&Normal, &Normal);


			//	法線の設定
			pVtx[j + Index].Nor = Normal;

		}
	}*/

	//	バッファのアンロック
	m_VertexBuffer->Unlock();

}

/*-----------------------------------------------------------------------------
インデックスバッファの作成
-----------------------------------------------------------------------------*/
void MeshField::MakeIndex(LPDIRECT3DDEVICE9 Device)
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
		MessageBox(NULL, "インデックスバッファの生成失敗", "MeshField.cpp", MB_OK | MB_ICONHAND);
	}


	//	インデックスバッファをロック
	m_IndexBuffer->Lock(0, 0, (void**)&pIdx, 0);


	//	時計回り
	if (m_IndexBackDraw == IDXBACK_DRAW_CLOCKWISE)
	{

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

			}	//	end of for

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
	else{

		//	逆時計回りを裏面とする
		//	縦
		for (UINT Cnt1 = 0; Cnt1 < m_NumBlock_Y; Cnt1++)
		{
			//	はじめじゃなかったら
			//	縮退ポリゴン
			if (Cnt1 != 0){
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
void MeshField::WorldTransform(LPDIRECT3DDEVICE9 Device)
{
	D3DXVECTOR3 Position = Object::GetPosition();


	D3DXMATRIX matrixScale, matrixRotation, matrixPosision;

	D3DXMatrixIdentity(&m_MatrixWorld);	//	行列を単位行列にする


	//	拡大行列を作る
	D3DXMatrixScaling(&matrixScale,	//拡大行列が作られる
		1.0f,	//	X軸拡大
		1.0f,	//	Y軸拡大
		1.0f);	//	Z軸拡大

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


	//	掛けてあげる
	D3DXMatrixMultiply(&m_MatrixWorld, &m_MatrixWorld, &matrixScale);
	D3DXMatrixMultiply(&m_MatrixWorld, &m_MatrixWorld, &matrixRotation);
	D3DXMatrixMultiply(&m_MatrixWorld, &m_MatrixWorld, &matrixPosision);
}

void MeshField::ConfigShader(LPDIRECT3DDEVICE9 device)
{
	LPD3DXCONSTANTTABLE vetexShaderConstantTable = m_VertexShader->GetVertexShaderConstantTable();
	LPD3DXCONSTANTTABLE pixelShaderConstantTable = m_PixelShader->GetPixelShaderConstantTable();

	vetexShaderConstantTable->SetMatrix(device, "mtxW", &m_MatrixWorld);

	D3DXMATRIX mtxWVP = m_MatrixWorld * Game::GetInstance()->GetCamera()->GetViewMatrix() * Game::GetInstance()->GetCamera()->GetProjectionMatrix();
	vetexShaderConstantTable->SetMatrix(device, "mtxWVP", &mtxWVP);

	D3DXMATRIX mtxInv;
	D3DXMatrixInverse(&mtxInv, NULL, &m_MatrixWorld);
	D3DXMatrixTranspose(&mtxInv, &mtxInv);
	vetexShaderConstantTable->SetMatrix(device, "mtxWIT", &mtxInv);

	D3DXVECTOR3 Pos[9] = {D3DXVECTOR3(-90.0f, 30.0f,   95.0f), D3DXVECTOR3(21.0f, 30.0f,   95.0f), D3DXVECTOR3(125.0f, 30.0f,   95.0f),
						  D3DXVECTOR3(-90.0f, 30.0f,  -15.0f), D3DXVECTOR3(21.0f, 30.0f,  -15.0f), D3DXVECTOR3(125.0f, 30.0f,  -15.0f),
						  D3DXVECTOR3(-90.0f, 30.0f, -115.0f), D3DXVECTOR3(21.0f, 30.0f, -115.0f), D3DXVECTOR3(125.0f, 30.0f, -115.0f)};
	pixelShaderConstantTable->SetValue(device, "LightPosW", Pos, sizeof(Pos));
	pixelShaderConstantTable->SetValue(device, "CameraEyeW", Game::GetInstance()->GetCamera()->GetPositionEye(), sizeof(D3DXVECTOR3));
}

/*-----------------------------------------------------------------------------
乗っている凹凸の高さ取得
-----------------------------------------------------------------------------*/
float MeshField::GetHeight(D3DXVECTOR3 Position)
{

	// 構造体のポインタ宣言
	VERTEX_3D* pVtx;

	// ポリゴン3頂点用
	D3DXVECTOR3 P0 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	自分の頂点
	D3DXVECTOR3 P1 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	自分の上の頂点
	D3DXVECTOR3 P2 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	自分の隣の頂点

	// 頂点→頂点
	D3DXVECTOR3 v01 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	頂点の縦のベクトル
	D3DXVECTOR3 v12 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	頂点の横のベクトル
	D3DXVECTOR3 v20 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	頂点の斜めのベクトル
	
	//	頂点からプレイヤーのベクトル
	D3DXVECTOR3 v0P = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 v1P = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 v2P = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	//	1行の頂点数
	int NumLineVertex = m_NumBlock_X + 1;


	//	バッファをロックし仮想アドレスを取得する
	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);


	//	縦
	for (UINT i = 0; i <= m_NumBlock_Y; i++)
	{

		//	横
		for (UINT j = 0; j <= m_NumBlock_X; j++)
		{

			/*-------------------------------------
						  1ポリゴン
			-------------------------------------*/		
			//	ポリゴンの3頂点を求める
			P0 = pVtx[NumLineVertex * (i + 1) + j].Pos;
			P1 = pVtx[NumLineVertex * i + j].Pos;
			P2 = pVtx[NumLineVertex * (i + 1) + (j + 1)].Pos;

			// vc0求める
			v01 = P1 - P0;
			v0P = Position - P0;

			D3DXVECTOR3 VC0 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 法線ベクトル用
			D3DXVec3Cross(&VC0, &v01, &v0P);

			//	Positionが三角形ポリゴンの中にいるかの判定
			if( VC0.y >= 0.0f )
			{

				// vc1求める
				v12 = P2 - P1;
				v1P = Position - P1;

				D3DXVECTOR3 VC1 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 法線ベクトル用
				D3DXVec3Cross(&VC1, &v12, &v1P);

				if( VC1.y >= 0.0f )
				{

					// vc2求める
					v20 = P0 - P2;
					v2P = Position - P2;

					D3DXVECTOR3 VC2 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 法線ベクトル用
					D3DXVec3Cross(&VC2, &v20, &v2P);

					if( VC2.y >= 0.0f )
					{

						//	法線の計算
						D3DXVECTOR3 N = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	法線
						D3DXVECTOR3 V01 = P1 - P0;
						D3DXVECTOR3 V02 = P2 - P0;
						D3DXVec3Cross(&N, &v01, &V02);
						D3DXVec3Normalize(&N, &N);	//	単位ベクトルに変換

						//	高さの計算
						Position.y = P0.y - ((Position.x - P0.x) * N.x + (Position.z - P0.z) * N.z) / N.y;

						//	バッファのアンロック
						m_VertexBuffer->Unlock();

						return Position.y;
						
					}
				}
			}

			/*-------------------------------------
						  2ポリゴン
			-------------------------------------*/
			//	ポリゴンの3頂点を求める
			P0 = pVtx[NumLineVertex * i + (j + 1)].Pos;
			P1 = pVtx[NumLineVertex * (i + 1) + (j + 1)].Pos;
			P2 = pVtx[NumLineVertex * i + j].Pos;

			// vc0求める
			v01 = P1 - P0;
			v0P = Position - P0;

			D3DXVec3Cross(&VC0, &v01, &v0P);

			//	座標が三角形ポリゴンの中にいるかの判定
			if( VC0.y >= 0.0f ){

				// vc1求める
				v12 = P2 - P1;
				v1P = Position - P1;

				D3DXVECTOR3 VC1 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				D3DXVec3Cross(&VC1, &v12, &v1P);

				if( VC1.y >= 0.0f )
				{

					// vc2求める
					v20 = P0 - P2;
					v2P = Position - P2;

					D3DXVECTOR3 VC2 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					D3DXVec3Cross(&VC2, &v20, &v2P);

					if( VC2.y >= 0.0f )
					{

						//	法線の計算
						D3DXVECTOR3 N = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	法線
						D3DXVECTOR3 V01 = P1 - P0;
						D3DXVECTOR3 V02 = P2 - P0;
						D3DXVec3Cross(&N, &v01, &V02);
						D3DXVec3Normalize(&N, &N);	//	単位ベクトルに変換

						//	高さの計算
						Position.y = P0.y - ((Position.x - P0.x) * N.x + (Position.z - P0.z) * N.z) / N.y;

						//	バッファのアンロック
						m_VertexBuffer->Unlock();

						return Position.y;
						
					}
				}
			}
		}
	}

	//	バッファのアンロック
	m_VertexBuffer->Unlock();

	return 0;
}

/*-----------------------------------------------------------------------------
頂点数の計算
-----------------------------------------------------------------------------*/
void MeshField::SetVertexCount(const UINT NumBlock_X, const UINT NumBlock_Y)
{
	m_NumVertex = (NumBlock_X + 1) * (NumBlock_Y + 1);
}

/*-----------------------------------------------------------------------------
インデックスバッファの計算
-----------------------------------------------------------------------------*/
void MeshField::SetIndexBufferCount(const UINT NumBlock_X, const UINT NumBlock_Y)
{
	m_NumIndexBuffer = (2 + 2 * NumBlock_X) * NumBlock_Y + (NumBlock_Y - 1) * 2;
}