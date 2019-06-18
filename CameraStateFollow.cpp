/*=============================================================================

ƒJƒƒ‰ó‘Ô( ’Ç] )[ CameraStateFollow.cpp ]

-------------------------------------------------------------------------------
¡  Author
Ohno Takuya

¡  Create
2017/11/22
=============================================================================*/

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "FrameworkBase\RendererDirectX.h"
#include "FrameworkBase\Common.h"
#include "FrameworkBase\Debug.h"
#include "GameScene.h"
#include "Player.h"
#include "FrameworkBase\CameraDirectX.h"
#include "CameraStateFollow.h"


CameraStateFollow::CameraStateFollow(CameraDirectX* owner):m_Owner(owner)
{
	Debug::Log("ƒJƒƒ‰ : ’Ç]ó‘Ô");
}
void CameraStateFollow::Update(void)
{
	Player* player = GameScene::GetPlayer();

	m_Owner->SetPositionAt(player->GetPosition());
	m_Owner->SetPositionEye(D3DXVECTOR3(player->GetPosition().x, player->GetPosition().y + 90.0f, player->GetPosition().z - 50.0f));
}