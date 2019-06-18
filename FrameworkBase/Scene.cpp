/*=============================================================================

âÊñ ëJà⁄[ Scene.h ]

-------------------------------------------------------------------------------
Å°  Author
	Ohno Takuya

Å°  Create
	2017/10/15
=============================================================================*/

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "RendererDirectX.h"
#include "Common.h"
#include "ModelManagerDirectX.h"
#include "Mathematics.h"
#include "../Object.h"
#include "../SpriteModeX.h"
#include "Scene.h"

/*-----------------------------------------------------------------------------

-----------------------------------------------------------------------------*/
void TestScene::Initialize(void)
{
}

void TestScene::Uninitialize(void)
{
	Object::ReleaseAll();
}

void TestScene::Update(void)
{
	Object::UpdateAll();
}

void TestScene::Draw(void)
{
	Object::DrawAll();
}