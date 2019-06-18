/*=============================================================================

2D描画[ Sprite2D.cpp ]

-------------------------------------------------------------------------------
■  Author
Ohno Takuya

■  Create
2017/11/17
=============================================================================*/

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "FrameworkBase\Common.h"
#include "FrameworkBase\RendererDirectX.h"
#include "FrameworkBase\Game.h"
#include "FrameworkBase\TextureManagerDirectX.h"
#include "Object.h"
#include "Sprite2D.h"

/*-----------------------------------------------------------------------------
Namespace
-----------------------------------------------------------------------------*/
using namespace std;


Sprite2D::Sprite2D(int Priolity):Object(Priolity)
{
	m_VertexBuffer = NULL;

	m_Size = D3DXVECTOR2(0.0f,0.0f);
	m_Color = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
}

/*-----------------------------------------------------------------------------
Function:   Sprite2D* Sprite2D::Create(D3DXVECTOR3 position, D3DXVECTOR2 size, char* texturePath,D3DXVECTOR4 color, int priolity)
Parameter:  D3DXVECTOR3 positon
              座標
            D3DXVECTOR2 size
			  大きさ
            char* texturePath
			  テクスチャのパス
			 D3DXVECTOR4 color
			  色
			int priolity
			  優先度
Overview:   生成
-----------------------------------------------------------------------------*/
Sprite2D* Sprite2D::Create(D3DXVECTOR3 position, D3DXVECTOR2 size, char* texturePath, D3DXVECTOR4 color, int priolity)
{
	auto object = new Sprite2D(priolity);

	object->SetPosition(position);
	object->m_Size = size;
	object->m_TexturePath = texturePath;
	object->m_Color = (D3DXCOLOR)color;

	object->Initialize();

	return object;
}

void Sprite2D::Initialize(void)
{
	LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();

	MakeVertex(Device);
}

void Sprite2D::Uninitialize(void)
{
	SAFE_RELEASE(m_VertexBuffer);

	Object::Release();
}

void Sprite2D::Update(void)
{
	SetVertex();
}

void Sprite2D::Draw(void)
{
	LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();


	Device->SetVertexShader(NULL);
	Device->SetPixelShader(NULL);

	// 頂点バッファをデータストリームに設定
	Device->SetStreamSource(0, m_VertexBuffer, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	Device->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	Device->SetTexture(0, Game::GetInstance()->GetTextureManager()->GetTextureInfo(m_TexturePath).Texture);

	// 描画
	Device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

void Sprite2D::MakeVertex(LPDIRECT3DDEVICE9 Device)
{
	D3DXVECTOR3 position = Object::GetPosition();


	// 頂点バッファの生成
	if (FAILED(Device->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_VertexBuffer, NULL)))
	{
		MessageBox(NULL, "頂点バッファの生成に失敗", "Sprite2D.cpp", MB_OK | MB_ICONHAND);
	}

	// 頂点情報を設定
	VERTEX_2D* Vtx;

	// バッファをロックし、仮想アドレスを取得
	m_VertexBuffer->Lock(0, 0, (void**)&Vtx, 0);

	//	頂点座標
	Vtx[0].Pos = D3DXVECTOR3(position.x           , position.y, 0.0f);
	Vtx[1].Pos = D3DXVECTOR3(position.x + m_Size.x, position.y, 0.0f);
	Vtx[2].Pos = D3DXVECTOR3(position.x           , position.y + m_Size.y, 0.0f);
	Vtx[3].Pos = D3DXVECTOR3(position.x + m_Size.x, position.y + m_Size.y, 0.0f);

	for(unsigned int CountVertex = 0; CountVertex < NUM_VERTEX; CountVertex++)
	{
		Vtx[CountVertex].Rhw = 1.0f;//	座標変換済み頂点フラグ
		Vtx[CountVertex].Color = m_Color;// 頂点カラー
	}

	// テクスチャ座標
	Vtx[0].Tex = D3DXVECTOR2(0, 0);
	Vtx[1].Tex = D3DXVECTOR2(1, 0);
	Vtx[2].Tex = D3DXVECTOR2(0, 1);
	Vtx[3].Tex = D3DXVECTOR2(1, 1);

	//	バッファをアンロック
	m_VertexBuffer->Unlock();

}

void Sprite2D::SetVertex(void)
{
	D3DXVECTOR3 position = Object::GetPosition();


	VERTEX_2D* Vtx;

	m_VertexBuffer->Lock(0, 0, (void**)&Vtx, 0);

	//	頂点座標
	Vtx[0].Pos = D3DXVECTOR3(position.x           , position.y, 0.0f);
	Vtx[1].Pos = D3DXVECTOR3(position.x + m_Size.x, position.y, 0.0f);
	Vtx[2].Pos = D3DXVECTOR3(position.x           , position.y + m_Size.y, 0.0f);
	Vtx[3].Pos = D3DXVECTOR3(position.x + m_Size.x, position.y + m_Size.y, 0.0f);

	for(unsigned int CountVertex = 0; CountVertex < NUM_VERTEX; CountVertex++)
	{
		Vtx[CountVertex].Color = m_Color;// 頂点カラー
	}


	//	バッファをアンロック
	m_VertexBuffer->Unlock();

}