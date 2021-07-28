/*=============================================================================

�f�o�b�O���j���[[ DebugMenu.cpp ]

-------------------------------------------------------------------------------

��  Create
2017/12/19
=============================================================================*/

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "FrameworkBase\RendererDirectX.h"
#include "FrameworkBase\Common.h"
#include "FrameworkBase\Game.h"
#include "FrameworkBase\InputDirectX.h"
#include "Object.h"
#include "GameScene.h"
#include "Player.h"
#include "Vision.h"
#include "MeshSphere.h"
#include "ControlPoint.h"
#include "DebugMenu.h"

/*-----------------------------------------------------------------------------
Static
-----------------------------------------------------------------------------*/
LPD3DXFONT DebugMenu::m_Font = NULL;
#ifndef _DEBUG
	bool DebugMenu::m_Active = false;
#else
	bool DebugMenu::m_Active = true;
#endif
bool DebugMenu::m_WireFrameActive = false;
bool DebugMenu::m_VisionActive = false;
bool DebugMenu::m_GameStop = false;
bool DebugMenu::m_ControlPointActive = false;


void DebugMenu::Initialize(void)
{
	LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();

	D3DXCreateFont(Device, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_Font);
}

void DebugMenu::Uninitialize(void)
{
	SAFE_RELEASE(m_Font);
}

void DebugMenu::Update(void)
{
	if(Game::GetInstance()->GetKeyboard()->GetKeyTrigger(DIK_0))
	{
		m_Active ^= 1;
	}

	else if(!m_Active){ return; }

	else if(Game::GetInstance()->GetKeyboard()->GetKeyTrigger(DIK_1))
	{
		m_WireFrameActive ^= 1;

		if(m_WireFrameActive){ Game::GetInstance()->GetRenderer()->WireFrame(); }
		else{ Game::GetInstance()->GetRenderer()->Normal(); }
	}

	else if(Game::GetInstance()->GetKeyboard()->GetKeyTrigger(DIK_2))
	{
		m_VisionActive ^= 1;

		for (int CntPriolity = 0; CntPriolity < PRIOLITY_MAX; CntPriolity++)
		{
			Object *object = Object::GetList(CntPriolity);
			while (object != NULL)
			{
				if (object->GetObjeType() == Object::OBJECT_TYPE_VISION)
				{
					Vision *vision = (Vision*)object;
					vision->SetActive(m_VisionActive);
				}
				object = object->GetNext();
			}
		}
	}

	else if(Game::GetInstance()->GetKeyboard()->GetKeyTrigger(DIK_3))
	{
		GameScene::GetPlayer()->HitPointRecovery(1000);
	}

	else if(Game::GetInstance()->GetKeyboard()->GetKeyTrigger(DIK_4))
	{
		m_GameStop^=1;
	}

	else if(Game::GetInstance()->GetKeyboard()->GetKeyTrigger(DIK_5))
	{
		m_ControlPointActive ^= 1;
		for (int CntPriolity = 0; CntPriolity < PRIOLITY_MAX; CntPriolity++)
		{
			Object *object = Object::GetList(CntPriolity);
			while (object != NULL)
			{
				if (object->GetObjeType() == Object::OBJECT_TYPE_CONTROLPOINT)
				{
					ControlPoint *point = (ControlPoint*)object;
					point->SetActive(m_ControlPointActive);
				}
				object = object->GetNext();
			}
		}
	}
}

void DebugMenu::Draw(void)
{
	if(!m_Active){ return; }


	int y = 100;
	char str[256];
	DWORD format = DT_LEFT; 
	D3DXCOLOR color = D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff);


	RECT rect = { 0, y, SCREEN_WIDTH, SCREEN_HEIGHT };
	wsprintf(str, "< �f�o�b�O���j���[ >\n");
	m_Font->DrawText(NULL, str, -1, &rect, format, color);

	rect.top = y + 25;
	wsprintf(str, "�f�o�b�O���j���[�I��[ 0 ]");
	m_Font->DrawText(NULL, str, -1, &rect, format, color);

	rect.top = y + 50;
	wsprintf(str, "���C���[�t���[��[ 1 ] : %s", m_WireFrameActive ? "ON" : "OFF");
	m_Font->DrawText(NULL, str, -1, &rect, format, color);

	rect.top = y + 75;
	wsprintf(str, "�G�̎��E[ 2 ] : %s", m_VisionActive ? "ON" : "OFF");
	m_Font->DrawText(NULL, str, -1, &rect, format, color);

	rect.top = y + 100;
	wsprintf(str, "�v���C���[�̗̑͑S��[ 3 ]");
	m_Font->DrawText(NULL, str, -1, &rect, format, color);

	rect.top = y + 125;
	wsprintf(str, "�|�[�Y[ 4 ] : %s", m_GameStop ? "ON" : "OFF");
	m_Font->DrawText(NULL, str, -1, &rect, format, color);

	rect.top = y + 150;
	wsprintf(str, "����_�\��[ 5 ] : %s", m_ControlPointActive ? "ON" : "OFF");
	m_Font->DrawText(NULL, str, -1, &rect, format, color);
}