/*=============================================================================

スカイスフィア[ SkySphere.cpp ]

-------------------------------------------------------------------------------
■  Author
Ohno Takuya

■  Create
2017/11/15
=============================================================================*/

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "FrameworkBase\Common.h"
#include "FrameworkBase\RendererDirectX.h"
#include "FrameworkBase\TextureManagerDirectX.h"
#include "Object.h"
#include "MeshSphere.h"
#include "SkySphere.h"

/*-----------------------------------------------------------------------------
Macro
-----------------------------------------------------------------------------*/
#define OBJECT_TEXTURE_PATH (TEXTURE_PATH"GAME/sky2.png")
#define ROTATION_SPEED (0.05f) // 回転スピード
#define SPHERE_NUMBLOCK_X (50) // 球の横の枚数
#define SPHERE_NUMBLOCK_Y (50) // 球の縦の枚数
#define SPHERE_RADIUS (800.0f) // 球の半径

/*-----------------------------------------------------------------------------
Function:   SkySphere* SkySphere::Create(void)
Overview:   生成
-----------------------------------------------------------------------------*/
SkySphere* SkySphere::Create(void)
{
	auto object = new SkySphere;

	object->SetPosition(D3DXVECTOR3(0.0f,0.0f,0.0f));

	object->SetNumBlock(SPHERE_NUMBLOCK_X, SPHERE_NUMBLOCK_Y);

	object->SetVertexCount(SPHERE_NUMBLOCK_X, SPHERE_NUMBLOCK_Y);
	object->SetIndexBufferCount(SPHERE_NUMBLOCK_X, SPHERE_NUMBLOCK_Y);

	object->SetIndexBackDraw(MeshSphere::IDXBACK_DRAW_INV_CLOCKWISE);

	object->SetTexturePath(OBJECT_TEXTURE_PATH);

	object->SetRadius(SPHERE_RADIUS);

	object->Initialize();

	return object;
}

void SkySphere::Initialize(void)
{
	MeshSphere::Initialize();
}

void SkySphere::Uninitialize(void)
{
	MeshSphere::Uninitialize();
}

void SkySphere::Update(void)
{
	D3DXVECTOR3 rotation = MeshSphere::GetRotation();

	rotation.y += ROTATION_SPEED;

	MeshSphere::SetRotation(rotation);
}

void SkySphere::Draw(void)
{
	MeshSphere::Draw();
}