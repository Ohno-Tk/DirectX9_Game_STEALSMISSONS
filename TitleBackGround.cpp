/*=============================================================================

タイトル背景[ TitleBackGround.cpp ]

-------------------------------------------------------------------------------
■  Author
Ohno Takuya

■  Create
2018/01/27
=============================================================================*/

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "FrameworkBase\Common.h"
#include "FrameworkBase\RendererDirectX.h"
#include "FrameworkBase\Game.h"
#include "FrameworkBase\TextureManagerDirectX.h"
#include "FrameworkBase\CameraDirectX.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Object.h"
#include "TitleBackGround.h"

/*-----------------------------------------------------------------------------
Macro
-----------------------------------------------------------------------------*/
#define OBJECT_TEXTURE_PATH (TEXTURE_PATH"TITLE/Wall000.jpg")
#define MODEL_VERTEXSHADER_PATH (SHADER_PATH"TitleMeshWall_Vertex.hlsl")
#define MODEL_PIXELSHADER_PATH (SHADER_PATH"TitleMeshWall_Pixel.hlsl")
#define TEX_SPEED (-0.05f)

/*-----------------------------------------------------------------------------
Static
-----------------------------------------------------------------------------*/
LPDIRECT3DTEXTURE9 TitleBackGround::m_Texture = NULL;


/*-----------------------------------------------------------------------------
コンストラクタ
-----------------------------------------------------------------------------*/
TitleBackGround::TitleBackGround(int priolity)
	:Object(priolity)
	,m_NumBlock_X(10)
	,m_NumBlock_Y(10)
	,m_SizeBlock_X(7.0f)
	,m_SizeBlock_Z(9.0f)
	,m_TexCoord(0.0f)
	,m_Normal(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{}

/*-----------------------------------------------------------------------------
生成
-----------------------------------------------------------------------------*/
TitleBackGround* TitleBackGround::Create(D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
	auto object = new TitleBackGround;

	object->SetPosition(position);
	object->m_Rotation = rotation;

	object->Initialize();

	return object;
}

/*-----------------------------------------------------------------------------
初期化
-----------------------------------------------------------------------------*/
void TitleBackGround::Initialize(void)
{
	LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();

	m_NumVertex = (m_NumBlock_X + 1) * (m_NumBlock_Y + 1);
	m_NumIndexBuffer = (2 + 2 * m_NumBlock_X) * m_NumBlock_Y + (m_NumBlock_Y - 1) * 2;


	MakeVerTex(Device);

	MakeIndex(Device);


	m_VertexShader = new VertexShader;
	m_VertexShader->Initialize(MODEL_VERTEXSHADER_PATH);

	m_PixelShader = new PixelShader;
	m_PixelShader->Initialize(MODEL_PIXELSHADER_PATH);
}

/*-----------------------------------------------------------------------------
終了
-----------------------------------------------------------------------------*/
void TitleBackGround::Uninitialize(void)
{
	SAFE_RELEASE(m_VertexBuffer);

	SAFE_RELEASE(m_IndexBuffer);

	SAFE_UNINIT(m_VertexShader);
	SAFE_UNINIT(m_PixelShader);

	Object::Release();	//	オブジェクト自身の解放
}

/*-----------------------------------------------------------------------------
更新
-----------------------------------------------------------------------------*/
void TitleBackGround::Update(void)
{
	m_TexCoord += TEX_SPEED;

	ChangeVerTex();
}

/*-----------------------------------------------------------------------------
描画
-----------------------------------------------------------------------------*/
void TitleBackGround::Draw(void)
{
	LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();


	D3DVERTEXELEMENT9 elements[] = {
	{0 ,0 ,D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
	{0 ,12 ,D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
	{0 ,24 ,D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
	D3DDECL_END()
	};
	RendererDirectX::GetDevice()->CreateVertexDeclaration(elements,&m_VertexDeclaration);


	Device->SetStreamSource(0, m_VertexBuffer, 0, sizeof(VERTEX_3D));

	Device->SetIndices(m_IndexBuffer);

	Device->SetFVF(FVF_VERTEX_3D);

	UINT samplerIndex0 = m_PixelShader->GetPixelShaderConstantTable()->GetSamplerIndex("sampler0");
	Device->SetTexture(samplerIndex0, Game::GetInstance()->GetTextureManager()->GetTextureInfo(OBJECT_TEXTURE_PATH).Texture);

	WorldTransform(Device);
	ConfigShader(Device);

	Device->SetVertexShader(m_VertexShader->GetVertexShader());
	Device->SetPixelShader(m_PixelShader->GetPixelShader());

	Device->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_NumIndexBuffer, 0, m_NumIndexBuffer - 2);

}

/*-----------------------------------------------------------------------------
ワールド座標変換
-----------------------------------------------------------------------------*/
void TitleBackGround::WorldTransform(LPDIRECT3DDEVICE9 Device)
{
	D3DXVECTOR3 Position = Object::GetPosition();


	D3DXMATRIX matrixScale, matrixRotation, matrixPosition;

	D3DXMatrixIdentity(&m_MatrixWorld);

	D3DXMatrixScaling(&matrixScale,
		1.0f,
		1.0f,
		1.0f);

	D3DXMatrixRotationYawPitchRoll(&matrixRotation,
		D3DXToRadian(m_Rotation.y),
		D3DXToRadian(m_Rotation.x),
		D3DXToRadian(m_Rotation.z));

	D3DXMatrixTranslation(&matrixPosition,
		Position.x,
		Position.y,
		Position.z);

	D3DXMatrixMultiply(&m_MatrixWorld, &m_MatrixWorld, &matrixScale);
	D3DXMatrixMultiply(&m_MatrixWorld, &m_MatrixWorld, &matrixRotation);
	D3DXMatrixMultiply(&m_MatrixWorld, &m_MatrixWorld, &matrixPosition);

//	Device->SetTransform(D3DTS_WORLD, &m_MatrixWorld);

}

void TitleBackGround::ConfigShader(LPDIRECT3DDEVICE9 device)
{
	LPD3DXCONSTANTTABLE vetexShaderConstantTable = m_VertexShader->GetVertexShaderConstantTable();
	LPD3DXCONSTANTTABLE pixelShaderConstantTable = m_PixelShader->GetPixelShaderConstantTable();

	vetexShaderConstantTable->SetMatrix(device, "mtxW", &m_MatrixWorld);

	D3DXMATRIX mtxWVP = m_MatrixWorld * Game::GetInstance()->GetCamera()->GetViewProjectionMatrix();
	vetexShaderConstantTable->SetMatrix(device, "mtxWVP", &mtxWVP);

	D3DXMATRIX mtxInv;
	D3DXMatrixInverse(&mtxInv, NULL, &m_MatrixWorld);
	D3DXMatrixTranspose(&mtxInv, &mtxInv);
	vetexShaderConstantTable->SetMatrix(device, "mtxWIT", &mtxInv);


	D3DXVECTOR3 lightDirW(0.0f,0.0f, -1.0f);
	vetexShaderConstantTable->SetValue(device, "lightDirW", &lightDirW, sizeof(lightDirW));


}

/*-----------------------------------------------------------------------------
頂点の作成
-----------------------------------------------------------------------------*/
void TitleBackGround::MakeVerTex(LPDIRECT3DDEVICE9 Device)
{

	if (FAILED(Device->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * m_NumVertex, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_VertexBuffer, NULL)))
	{
		MessageBox(NULL, "頂点バッファの生成エラー", "TitleBackGround.cpp", MB_OK | MB_ICONHAND);
	}

	// 構造体のポインタ宣言
	VERTEX_3D* pVtx;

	D3DXVECTOR3 position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	int Index = 0;

	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);


	//	縦
	for (UINT i = 0; i < m_NumBlock_Y + 1; i++)
	{

		Index = i * (m_NumBlock_X + 1);

		//	横
		for (UINT j = 0; j < (m_NumBlock_X + 1) * 2; j++)
		{

			//	座標
			position.x = (m_SizeBlock_X * m_NumBlock_X / 2) - m_NumBlock_X * m_SizeBlock_X + (m_SizeBlock_X * j);
			position.y = (m_SizeBlock_Z * m_NumBlock_Y / 2) - (m_SizeBlock_Z * i);
			position.z = 0.0f;
			
			pVtx[j + Index].Pos = position;//	頂点座標
			
			pVtx[j + Index].Nor = D3DXVECTOR3(0.0f, -1.0f, -1.0f);//	法線
			
			pVtx[j + Index].Color = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);//	頂点色
		
			pVtx[j + Index].Tex = D3DXVECTOR2((float)j, (float)i);//	テクスチャ座標

		}
	}

	//	バッファのアンロック
	m_VertexBuffer->Unlock();

}

/*-----------------------------------------------------------------------------
頂点の変更
-----------------------------------------------------------------------------*/
void TitleBackGround::ChangeVerTex(void)
{
	VERTEX_3D* pVtx;

	int Index = 0;

	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);


	//	縦
	for (UINT i = 0; i < m_NumBlock_Y + 1; i++)
	{

		Index = i * (m_NumBlock_X + 1);

		//	横
		for (UINT j = 0; j < (m_NumBlock_X + 1) * 2; j++)
		{	
			pVtx[j + Index].Nor = m_Normal;
			pVtx[j + Index].Tex = D3DXVECTOR2((float)j, (float)i + m_TexCoord);//	テクスチャ座標
		}
	}

	//	バッファのアンロック
	m_VertexBuffer->Unlock();
}

/*-----------------------------------------------------------------------------
インデックスバッファの作成
-----------------------------------------------------------------------------*/
void TitleBackGround::MakeIndex(LPDIRECT3DDEVICE9 Device)
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

		MessageBox(NULL, "インデックスバッファの生成失敗", "TitleBackGround.cpp", MB_OK | MB_ICONHAND);
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