/*=============================================================================

アイテム取得UI( レーション )[ ItemGetUIRation.cpp ]

-------------------------------------------------------------------------------
■  Author
Ohno Takuya

■  Create
2018/01/22
=============================================================================*/

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "FrameworkBase\Common.h"
#include "FrameworkBase\RendererDirectX.h"
#include "FrameworkBase\Game.h"
#include "FrameworkBase\TextureManagerDirectX.h"
#include "FrameworkBase\Mathematics.h"
#include "FrameworkBase\CameraDirectX.h"
#include "Object.h"
#include "ItemGetUIRation.h"

/*-----------------------------------------------------------------------------
Macro
-----------------------------------------------------------------------------*/
#define TEXTURE_FILEPATH (TEXTURE_PATH"GAME/ItemGetUI_Ration.png")
#define SCALE (1.0f)// 拡大値
#define VERTEX_SIZE_X (10.0f)
#define VERTEX_SIZE_Y (3.5f)
#define INTERPOLATION_TIME (90)

/*-----------------------------------------------------------------------------
コンストラクタ
-----------------------------------------------------------------------------*/
ItemGetUIRation::ItemGetUIRation(int priolity)
	:ItemGetUI(priolity)
	,m_FrameTime(0)
	,m_EndPosition(0.0f)
{}

/*-----------------------------------------------------------------------------
初期化
-----------------------------------------------------------------------------*/
void ItemGetUIRation::Initialize(void)
{
	m_EndPosition = ItemGetUI::GetPosition().y + 10.0f;

	MakeVertex();
}

/*-----------------------------------------------------------------------------
終了
-----------------------------------------------------------------------------*/
void ItemGetUIRation::Uninitialize(void)
{
	ItemGetUI::Uninitialize();
}

/*-----------------------------------------------------------------------------
更新
-----------------------------------------------------------------------------*/
void ItemGetUIRation::Update(void)
{
	if(!ItemGetUI::GetActive()){ return; }

	D3DXVECTOR3 potision = ItemGetUI::GetPosition();

	CubicExpressionInterpolation cubic(m_FrameTime);
	cubic.Interpolation(&potision.y,  ItemGetUI::GetPosition().y, m_EndPosition, INTERPOLATION_TIME);

	m_FrameTime++;

	ItemGetUI:: SetPosition(potision);

	if(m_FrameTime >= INTERPOLATION_TIME)
	{
		ItemGetUI::SetActive(false);
	}

	SetVertex();
}

/*-----------------------------------------------------------------------------
描画
-----------------------------------------------------------------------------*/
void ItemGetUIRation::Draw(void)
{
	if(!ItemGetUI::GetActive()){ return; }


	LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();
	Device->SetVertexShader(NULL);
	Device->SetPixelShader(NULL);

	Device->SetStreamSource(0, m_VertexBuffer, 0, sizeof(VERTEX_3D));

	Device->SetFVF(FVF_VERTEX_3D);

	Device->SetTexture(0, Game::GetInstance()->GetTextureManager()->GetTextureInfo(TEXTURE_FILEPATH).Texture);

	WorldTransform(Device);

	// 全体のライトを無効にする
	Device->SetRenderState(D3DRS_LIGHTING, FALSE);

	Device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	//	全体のライトを有効にする
	Device->SetRenderState(D3DRS_LIGHTING, TRUE);
}

/*-----------------------------------------------------------------------------
頂点の作成
-----------------------------------------------------------------------------*/
void ItemGetUIRation::MakeVertex(void)
{
	LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();


	if (FAILED(Device->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_VertexBuffer, NULL)))
	{

		MessageBox(NULL, "頂点バッファの生成に失敗", "ItemGetUIRation.cpp", MB_OK | MB_ICONHAND);
		return;
	}

	// 頂点情報を設定
	VERTEX_3D* pVtx;

	// バッファをロックし、仮想アドレスを取得
	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);


	//	頂点座標
	pVtx[0].Pos = D3DXVECTOR3(-VERTEX_SIZE_X, VERTEX_SIZE_Y, 0.0f);
	pVtx[1].Pos = D3DXVECTOR3( VERTEX_SIZE_X, VERTEX_SIZE_Y, 0.0f);
	pVtx[2].Pos = D3DXVECTOR3(-VERTEX_SIZE_X, 0.0f, 0.0f);
	pVtx[3].Pos = D3DXVECTOR3( VERTEX_SIZE_X, 0.0f, 0.0f);


	for(unsigned int i = 0; i < NUM_VERTEX; i++)
	{
		pVtx[i].Nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);// 法線
		pVtx[i].Color = ItemGetUI::GetColor();// 頂点カラー
	}

	// テクスチャ座標
	pVtx[0].Tex = D3DXVECTOR2(0, 0);
	pVtx[1].Tex = D3DXVECTOR2(1, 0);
	pVtx[2].Tex = D3DXVECTOR2(0, 1);
	pVtx[3].Tex = D3DXVECTOR2(1, 1);

	//	バッファをアンロック
	m_VertexBuffer->Unlock();
}

void ItemGetUIRation::SetVertex(void)
{
	// 頂点情報を設定
	VERTEX_3D* pVtx;

	// バッファをロックし、仮想アドレスを取得
	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);


	//	頂点座標
	pVtx[0].Pos = D3DXVECTOR3(-VERTEX_SIZE_X, VERTEX_SIZE_Y, 0.0f);
	pVtx[1].Pos = D3DXVECTOR3( VERTEX_SIZE_X, VERTEX_SIZE_Y, 0.0f);
	pVtx[2].Pos = D3DXVECTOR3(-VERTEX_SIZE_X, 0.0f, 0.0f);
	pVtx[3].Pos = D3DXVECTOR3( VERTEX_SIZE_X, 0.0f, 0.0f);

	for(unsigned int i = 0; i < NUM_VERTEX; i++)
	{
		pVtx[i].Color = ItemGetUI::GetColor();// 頂点カラー
	}

	//	バッファをアンロック
	m_VertexBuffer->Unlock();
}

/*-----------------------------------------------------------------------------
ワールド座標変換
-----------------------------------------------------------------------------*/
void ItemGetUIRation::WorldTransform(LPDIRECT3DDEVICE9 Device)
{
	D3DXVECTOR3 Position = Object::GetPosition();
	//	ビュー行列の逆行列を取得
	D3DXMATRIX mtxViewInverse = Game::GetInstance()->GetCamera()->GetInversedView();


	D3DXMATRIX matrixScale, matrixRotation, matrixPosition;

	D3DXMatrixIdentity(&m_MatrixWorld);	//	行列を単位行列にする

	D3DXMatrixScaling(&matrixScale,
		SCALE,
		SCALE,
		SCALE);


	D3DXMatrixTranslation(&matrixPosition,
		Position.x,
		Position.y,
		Position.z);

	D3DXMatrixMultiply(&m_MatrixWorld, &m_MatrixWorld, &mtxViewInverse);
	D3DXMatrixMultiply(&m_MatrixWorld, &m_MatrixWorld, &matrixScale);
	D3DXMatrixMultiply(&m_MatrixWorld, &m_MatrixWorld, &matrixPosition);


	Device->SetTransform(D3DTS_WORLD, &m_MatrixWorld);
}

ItemGetUIRation* ItemGetUIRation::Create(D3DXVECTOR3 position)
{
	auto object = new ItemGetUIRation;

	object->SetPosition(position);
	object->Initialize();

	return object;
}