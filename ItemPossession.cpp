/*=============================================================================

現在所持数アイテム[ NowPossessionItem.cpp ]

-------------------------------------------------------------------------------
■  Author
Ohno Takuya

■  Create
2018/01/24
=============================================================================*/

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "FrameworkBase\Common.h"
#include "FrameworkBase\RendererDirectX.h"
#include "FrameworkBase\Game.h"
#include "FrameworkBase\TextureManagerDirectX.h"
#include "Object.h"
#include "ItemPossession.h"

/*-----------------------------------------------------------------------------
Macro
-----------------------------------------------------------------------------*/
#define OBJECT_TEXTURE_PATH (TEXTURE_PATH"GAME/Number003.png")
#define BUNKATUSU ( 0.1f )	//	テクスチャの分割数


ItemPossession::ItemPossession(int priolity)
	:Object(priolity)
	,m_VertexBuffer(NULL)
	,m_Size(D3DXVECTOR2(40.0f, 40.0f))
	,m_Digit(0)
	,m_TexCoord(0.0f)
	,m_Possession(0)
{}

/*-----------------------------------------------------------------------------
生成
-----------------------------------------------------------------------------*/
ItemPossession* ItemPossession::Create(D3DXVECTOR3 position, unsigned int digit)
{
	auto object = new ItemPossession;

	object->SetPosition(position);
	object->m_Digit = digit;
	object->Initialize();

	return object;
}

/*-----------------------------------------------------------------------------
初期化
-----------------------------------------------------------------------------*/
void ItemPossession::Initialize(void)
{
	MakeVertex();
}

/*-----------------------------------------------------------------------------
終了
-----------------------------------------------------------------------------*/
void ItemPossession::Uninitialize(void)
{
	SAFE_RELEASE(m_VertexBuffer);
	Object::Release();
}

/*-----------------------------------------------------------------------------
更新
-----------------------------------------------------------------------------*/
void ItemPossession::Update(void)
{
	SetVertex();
}

/*-----------------------------------------------------------------------------
描画
-----------------------------------------------------------------------------*/
void ItemPossession::Draw(void)
{
	LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();


	Device->SetStreamSource(0, m_VertexBuffer, 0, sizeof(VERTEX_2D));

	Device->SetFVF(FVF_VERTEX_2D);

	Device->SetTexture(0, Game::GetInstance()->GetTextureManager()->GetTextureInfo(OBJECT_TEXTURE_PATH).Texture);

	for(unsigned int i = 0; i < m_Digit; i++)
	{
		Device->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * NUM_VERTEX, NUM_POLYGON);
	}
}

/*-----------------------------------------------------------------------------
頂点の作成
-----------------------------------------------------------------------------*/
void ItemPossession::MakeVertex(void)
{
	D3DXVECTOR3 position = Object::GetPosition();
	LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();

	// 頂点バッファの生成
	if (FAILED(Device->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX * m_Digit, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_VertexBuffer, NULL)))
	{
		MessageBox(NULL, "頂点バッファの生成に失敗", "NowPossessionItem.cpp", MB_OK | MB_ICONHAND);
	}

	// 頂点情報を設定
	VERTEX_2D* Vtx;

	// バッファをロックし、仮想アドレスを取得
	m_VertexBuffer->Lock(0, 0, (void**)&Vtx, 0);


	for(unsigned int i = 0; i < m_Digit; i++)
	{

		//	頂点座標
		Vtx[0].Pos = D3DXVECTOR3(position.x            - m_Size.x * i, position.y, 0.0f);
		Vtx[1].Pos = D3DXVECTOR3(position.x + m_Size.x - m_Size.x * i, position.y, 0.0f);
		Vtx[2].Pos = D3DXVECTOR3(position.x            - m_Size.x * i, position.y + m_Size.y, 0.0f);
		Vtx[3].Pos = D3DXVECTOR3(position.x + m_Size.x - m_Size.x * i, position.y + m_Size.y, 0.0f);

		for(unsigned int j = 0; j < NUM_VERTEX; j++)
		{
			Vtx[j].Rhw = 1.0f;//	座標変換済み頂点フラグ
			Vtx[j].Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);// 頂点カラー
		}

		// テクスチャ座標
		Vtx[0].Tex = D3DXVECTOR2( m_TexCoord             , 0 );
		Vtx[1].Tex = D3DXVECTOR2( m_TexCoord + BUNKATUSU , 0 );
		Vtx[2].Tex = D3DXVECTOR2( m_TexCoord             , 1 );
		Vtx[3].Tex = D3DXVECTOR2( m_TexCoord + BUNKATUSU , 1 );

		Vtx += 4;
	}

	//	バッファをアンロック
	m_VertexBuffer->Unlock();

}

/*-----------------------------------------------------------------------------
頂点の変更
-----------------------------------------------------------------------------*/
void ItemPossession::SetVertex(void)
{
	int Number;		//	数字を表示する変数
	int Value = m_Possession;		//	値の保持


	D3DXVECTOR3 position = Object::GetPosition();

	// 頂点情報を設定
	VERTEX_2D* Vtx;

	// バッファをロックし、仮想アドレスを取得
	m_VertexBuffer->Lock(0, 0, (void**)&Vtx, 0);


	for(unsigned int i = 0; i < m_Digit; i++)
	{
		Number = Value % 10;
		Value /= 10;
		m_TexCoord = Number * BUNKATUSU;


		//	頂点座標
		Vtx[0].Pos = D3DXVECTOR3(position.x            - m_Size.x * i, position.y, 0.0f);
		Vtx[1].Pos = D3DXVECTOR3(position.x + m_Size.x - m_Size.x * i, position.y, 0.0f);
		Vtx[2].Pos = D3DXVECTOR3(position.x            - m_Size.x * i, position.y + m_Size.y, 0.0f);
		Vtx[3].Pos = D3DXVECTOR3(position.x + m_Size.x - m_Size.x * i, position.y + m_Size.y, 0.0f);

		// テクスチャ座標
		Vtx[0].Tex = D3DXVECTOR2( m_TexCoord             , 0 );
		Vtx[1].Tex = D3DXVECTOR2( m_TexCoord + BUNKATUSU , 0 );
		Vtx[2].Tex = D3DXVECTOR2( m_TexCoord             , 1 );
		Vtx[3].Tex = D3DXVECTOR2( m_TexCoord + BUNKATUSU , 1 );

		Vtx += 4;

	}

	//	バッファをアンロック
	m_VertexBuffer->Unlock();

}

/*-----------------------------------------------------------------------------
数字の設定
-----------------------------------------------------------------------------*/
void ItemPossession::SetPossession(int possession)
{
	m_Possession = possession;
}