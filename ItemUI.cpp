/*=============================================================================

�A�C�e���\��UI[ ItemUI.cpp ]

-------------------------------------------------------------------------------
��  Author
Ohno Takuya

��  Create
2018/01/24
=============================================================================*/

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "FrameworkBase\Common.h"
#include "FrameworkBase\RendererDirectX.h"
#include "Object.h"
#include "ItemUI.h"


/*-----------------------------------------------------------------------------
�I��
-----------------------------------------------------------------------------*/
void ItemUI::Uninitialize(void)
{
	Object::Release();
}