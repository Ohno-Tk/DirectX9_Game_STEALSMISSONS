/*=============================================================================

視界( デバッグ用 )[ Vision.cpp ]

-------------------------------------------------------------------------------
■  Author
Ohno Takuya

■  Create
2017/11/28
=============================================================================*/

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "FrameworkBase\RendererDirectX.h"
#include "FrameworkBase\Common.h"
#include "FrameworkBase\Game.h"
#include "FrameworkBase\TextureManagerDirectX.h"
#include "Object.h"
#include "Vision.h"

/*-----------------------------------------------------------------------------

-----------------------------------------------------------------------------*/
#define OBJECT_TEXTURE_PATH ( TEXTURE_PATH"GAME/White.png" )


Vision* Vision::Create(float VisionDistance, float Angle)
{
	auto object = new Vision;

	object->m_Angle = Angle;
	object->m_VisionDistance = VisionDistance;

	object->Initialize();

	return object;
}

void Vision::Initialize(void)
{
	Object::SetObjeType(OBJECT_TYPE_VISION);

	D3DXMatrixIdentity(&m_OwnerMatrix);

	MakeVerTex();
}

void Vision::Uninitialize(void)
{
	SAFE_RELEASE(m_VertexBuffer);

	Object::Release();
}

void Vision::Draw(void)
{
	LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();

	if(!m_Active){ return; }

	Device->SetVertexShader(NULL);
	Device->SetPixelShader(NULL);

	WorldTransform(Device);

	Device->SetStreamSource(0, m_VertexBuffer, 0, sizeof(VERTEX_3D));

	Device->SetFVF(FVF_VERTEX_3D);

	Device->SetTexture(0, Game::GetInstance()->GetTextureManager()->GetTextureInfo(OBJECT_TEXTURE_PATH).Texture);

	// 全体のライトを無効にする
	Device->SetRenderState(D3DRS_LIGHTING, FALSE);

	Device->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, NUM_POLYGON);

	//	全体のライトを有効にする
	Device->SetRenderState(D3DRS_LIGHTING, TRUE);
}

void Vision::MakeVerTex(void)
{
	LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();


	if (FAILED(Device->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_VertexBuffer, NULL)))
	{

		MessageBox(NULL, "頂点バッファの生成に失敗", "Vision.cpp", MB_OK | MB_ICONHAND);
		return;
	}

	// 頂点情報を設定
	VERTEX_3D* Vtx;

	// バッファをロックし、仮想アドレスを取得
	m_VertexBuffer->Lock(0, 0, (void**)&Vtx, 0);

	int angle = (int)(m_Angle * 0.5f);
	angle *= 0.5f;

	float i = tan(D3DXToRadian(angle));
	float a = 2 * m_VisionDistance * i;

	//	頂点座標
	Vtx[0].Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Vtx[1].Pos = D3DXVECTOR3(a, 0.0f, -m_VisionDistance);
	Vtx[2].Pos = D3DXVECTOR3(-a, 0.0f, -m_VisionDistance);

	for(int i = 0; i < NUM_VERTEX; i++)
	{
		Vtx[i].Nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		Vtx[i].Color = D3DXCOLOR(255, 255, 255, 255);
	}

	// テクスチャ座標
	Vtx[0].Tex = D3DXVECTOR2(0, 0);
	Vtx[1].Tex = D3DXVECTOR2(1, 0);
	Vtx[2].Tex = D3DXVECTOR2(0, 1);


	//	バッファをアンロック
	m_VertexBuffer->Unlock();
}

void Vision::WorldTransform(LPDIRECT3DDEVICE9 Device)
{
	D3DXVECTOR3 position = Object::GetPosition();


	D3DXMATRIX matrixScale , matrixRotation , matrixPosition , matrixWorld;

	D3DXMatrixIdentity(&matrixWorld);

	D3DXMatrixScaling(&matrixScale,
		1.0f,
		1.0f,
		1.0f);

	D3DXMatrixRotationYawPitchRoll(&matrixRotation,
		D3DXToRadian(m_Rotation.y),
		D3DXToRadian(m_Rotation.x),
		D3DXToRadian(m_Rotation.z));

	D3DXMatrixTranslation(&matrixPosition,
		position.x,
		position.y,
		position.z);


	D3DXMatrixMultiply(&matrixWorld, &matrixWorld, &matrixScale);
	D3DXMatrixMultiply(&matrixWorld, &matrixWorld, &matrixRotation);
	D3DXMatrixMultiply(&matrixWorld, &matrixWorld, &matrixPosition);

	D3DXMatrixMultiply(&matrixWorld, &matrixWorld, &m_OwnerMatrix); // 親のマトリクスのかける

	Device->SetTransform(D3DTS_WORLD, &matrixWorld);
}