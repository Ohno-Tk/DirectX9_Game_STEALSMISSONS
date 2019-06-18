/*=============================================================================

アイテム[ Item.cpp ]

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
#include "FrameworkBase\SoundDirectX.h"
#include "Object.h"
#include "ItemGetUI.h"
#include "Item.h"


/*-----------------------------------------------------------------------------
終了
-----------------------------------------------------------------------------*/
void Item::Uninitialize(void)
{
	Object::Release();
}

/*-----------------------------------------------------------------------------
更新
-----------------------------------------------------------------------------*/
void Item::Update(void)
{
	if(Collision())
	{
#ifndef ENABLE_SOUND
		// 取得BGM
		Game::GetInstance()->GetSound()->Play(SoundDirectX::SOUND_SE_GETITEM);

#endif
	}
}