/*=============================================================================

スクロールオブジェクト(2D)[ Scroll2DObject.cpp ]

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
#include "Object.h"
#include "Sprite2D.h"
#include "Scroll2DObject.h"

/*-----------------------------------------------------------------------------
Function:   Scroll2DObject* Scroll2DObject::Create(D3DXVECTOR3 position, D3DXVECTOR2 size, char* textureFilePath, D3DXVECTOR2 scrollSpeed, int priolity)
Parameter:  D3DXVECTOR3 positon
              座標
            D3DXVECTOR2 size
			  大きさ
			char* textureFilePath
			  テクスチャのパス
			 D3DXVECTOR2 scrollSpeed
			   スクロールスピード
			int priolity
			  優先度
Overview:   生成
-----------------------------------------------------------------------------*/
Scroll2DObject* Scroll2DObject::Create(D3DXVECTOR3 position, D3DXVECTOR2 size, char* textureFilePath, D3DXVECTOR2 scrollSpeed, int priolity)
{
	auto object = new Scroll2DObject(priolity);

	object->SetPosition(position);
	object->SetSize(size);
	object->SetTexturePath(textureFilePath);
	object->m_ScrollSpeed = scrollSpeed;

	object->Initialize();

	return object;
}

void Scroll2DObject::Initialize(void)
{
	Sprite2D::Initialize();
}

void Scroll2DObject::Uninitialize(void)
{
	Sprite2D::Uninitialize();
}

void Scroll2DObject::Update(void)
{
	m_TexCoord += m_ScrollSpeed;

	Sprite2D::Update();
}

void Scroll2DObject::Draw(void)
{
	Sprite2D::Draw();
}

void Scroll2DObject::SetVertex(void)
{
	LPDIRECT3DVERTEXBUFFER9 vertexBuffer = Sprite2D::GetVertexBuffer();


	VERTEX_2D* Vtx;

	vertexBuffer->Lock(0, 0, (void**)&Vtx, 0);


	Vtx[0].Tex = D3DXVECTOR2(0 + m_TexCoord.x, 0 + m_TexCoord.y);
	Vtx[1].Tex = D3DXVECTOR2(1 + m_TexCoord.x, 0 + m_TexCoord.y);
	Vtx[2].Tex = D3DXVECTOR2(0 + m_TexCoord.x, 1 + m_TexCoord.y);
	Vtx[3].Tex = D3DXVECTOR2(1 + m_TexCoord.x, 1 + m_TexCoord.y);


	vertexBuffer->Unlock();
}