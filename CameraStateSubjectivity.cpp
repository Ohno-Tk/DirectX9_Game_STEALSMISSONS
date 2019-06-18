/*=============================================================================

ƒJƒƒ‰ó‘Ô(ŽåŠÏ)[ CameraStateSubjectivity.cpp ]

-------------------------------------------------------------------------------
¡  Author
Ohno Takuya

¡  Create
2018/01/19
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
#include "CameraStateSubjectivity.h"

CameraStateSubjectivity::CameraStateSubjectivity(CameraDirectX* owner):m_Owner(owner)
{
	Debug::Log("ƒJƒƒ‰ : ’Ç]ó‘Ô");
}
void CameraStateSubjectivity::Update(void)
{
	Player* player = GameScene::GetPlayer();

	m_Owner->SetPositionAt(player->GetPosition());
	m_Owner->SetPositionEye(D3DXVECTOR3(player->GetPosition().x, player->GetPosition().y + 80.0f, player->GetPosition().z - 60.0f));
}