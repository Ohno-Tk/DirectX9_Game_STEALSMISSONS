/*=============================================================================

制御点( デバッグ用 )[ ControlPoint.cpp ]

-------------------------------------------------------------------------------
■  Author
Ohno Takuya

■  Create
2017/11/29
=============================================================================*/

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "FrameworkBase\RendererDirectX.h"
#include "FrameworkBase\Common.h"
#include "Object.h"
#include "MeshSphere.h"
#include "ControlPoint.h"


ControlPoint* ControlPoint::Create(D3DXVECTOR3 position)
{
	auto object = new ControlPoint;

	object->SetPosition(position);
	object->Initialize();

	return object;
}

void ControlPoint::Initialize(void)
{
	MeshSphere::SetNumBlock(10, 10);
	MeshSphere::SetVertexCount(10, 10);
	MeshSphere::SetIndexBufferCount(10, 10);
	MeshSphere::SetIndexBackDraw(IDXBACK_DRAW_CLOCKWISE);
	MeshSphere::SetTexturePath(TEXTURE_PATH"GAME/White.png");
	MeshSphere::SetRadius(3.0f);

	MeshSphere::Initialize();

	Object::SetObjeType(OBJECT_TYPE_CONTROLPOINT);
}

void ControlPoint::Uninitialize(void)
{
	MeshSphere::Uninitialize();
}

void ControlPoint::Draw(void)
{
	if(!m_Actice){ return; }

	LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();
	Device->SetVertexShader(NULL);
	Device->SetPixelShader(NULL);

	Device->SetRenderState(D3DRS_LIGHTING, FALSE);

	MeshSphere::Draw();

	Device->SetRenderState(D3DRS_LIGHTING, TRUE);
}