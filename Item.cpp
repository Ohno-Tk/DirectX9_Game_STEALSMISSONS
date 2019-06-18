/*=============================================================================

�A�C�e��[ Item.cpp ]

-------------------------------------------------------------------------------
��  Author
Ohno Takuya

��  Create
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
�I��
-----------------------------------------------------------------------------*/
void Item::Uninitialize(void)
{
	Object::Release();
}

/*-----------------------------------------------------------------------------
�X�V
-----------------------------------------------------------------------------*/
void Item::Update(void)
{
	if(Collision())
	{
#ifndef ENABLE_SOUND
		// �擾BGM
		Game::GetInstance()->GetSound()->Play(SoundDirectX::SOUND_SE_GETITEM);

#endif
	}
}