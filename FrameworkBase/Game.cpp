/*=============================================================================

�Q�[������[ Game.cpp ]

-------------------------------------------------------------------------------
��  Author
Ohno Takuya

��  Create
2017/11/11
=============================================================================*/

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "Common.h"
#include "Console.h"
#include "Debug.h"
#include "FileManager.h"
#include "RendererDirectX.h"
#include "CameraDirectX.h"
#include "LightDirectX.h"
#include "Fade.h"
#include "InputDirectX.h"
#include "SoundDirectX.h"
#include "TextureManagerDirectX.h"
#include "ModelManagerDirectX.h"
#include "MotionCharacterData.h"
#include "../DebugFont.h"
#include "../DebugMenu.h"
#include "../TitleScene.h"

#include "../GameScene.h"
#include "../GameClearScene.h"
#include "../GameOverScene.h"
#include "../TutorialScene.h"
#include "Game.h"

/*-----------------------------------------------------------------------------
Macro
-----------------------------------------------------------------------------*/
#define ENABLE_CONSOLE
#undef ENABLE_CONSOLE

#define ENABLE_CHARDATA
#undef ENABLE_CHARDATA

/*-----------------------------------------------------------------------------
Function:   Game* Game::GetInstance(void)
Overview:   �C���X�^���X�擾
-----------------------------------------------------------------------------*/
Game* Game::GetInstance(void)
{
	static Game instance;

	return &instance;
}

Game::Game()
{
	m_Renderer = NULL;
	m_Scene = new TitleScene;
	m_Camera = NULL;
	m_Light = NULL;
	m_Fade = NULL;
	m_TextureManager = NULL;
	m_ModelManager = NULL;
	m_Keyboard = NULL;
	m_Sound = NULL;
	m_MotionCharacterData = NULL;
}

void Game::Init(HINSTANCE instance, HWND wnd)
{
	HRESULT hr;

#ifdef ENABLE_CONSOLE
	Console::Init();
#endif

	// �����_���[
	m_Renderer = new RendererDirectX;
	hr = m_Renderer->Initialize(wnd);
	if (FAILED(hr)){ Debug::Assert("�����_���[�N���X�̐����Ɏ��s", "Game.cpp", ""); }

	// �J����
	m_Camera = new CameraDirectX;

	// ���C�g
	m_Light = new LightDirectX;
	m_Light->DirectionalLight();

	// �t�F�[�h
	m_Fade = new Fade;
	m_Fade->Initialize();

	// �e�N�X�`���̊Ǘ�
	m_TextureManager = new TextureManagerDirectX;
	m_TextureManager->Initialize();

	// ���f���Ǘ�
	m_ModelManager = new ModelManagerDirectX;
	m_ModelManager->Initialize();

	// �L�[�{�[�h
	m_Keyboard = new DirectXKeyboard;
	hr = m_Keyboard->Initialize(instance, wnd);
	if (FAILED(hr)){ Debug::Assert("�L�[�{�[�h�N���X�̐����Ɏ��s", "Game.cpp", ""); }

#ifdef _DEBUG
	m_Mouse = new DirectXMouse;
	m_Mouse->Initialize(instance, wnd);
#endif

	// XInput
	m_XInput = new XInput;

	// �T�E���h
	m_Sound = new SoundDirectX;
	hr = m_Sound->Initialize();
	if (FAILED(hr)){ Debug::Assert("�T�E���h�N���X�̐����Ɏ��s", "Game.cpp", ""); }

#ifdef ENABLE_CHARDATA
	// ���[�V�����f�[�^
	m_MotionCharacterData = new MotionCharacterData;
	m_MotionCharacterData->Initialize();
#endif

	DebugFont::Initialize();

	DebugMenu::Initialize();

	// ��ʑJ��
	m_Scene->Initialize();
}

void Game::Uninit(void)
{
	SAFE_UNINIT(m_Scene);

	DebugMenu::Uninitialize();

	DebugFont::Uninitialize();

#ifdef ENABLE_CHARDATA
	SAFE_UNINIT(m_MotionCharacterData);
#endif

	SAFE_UNINIT(m_Sound);

	SAFE_DELETE(m_XInput);

#ifdef _DEBUG
	SAFE_UNINIT(m_Mouse);
#endif

	SAFE_UNINIT(m_Keyboard);

	SAFE_UNINIT(m_ModelManager);

	SAFE_UNINIT(m_TextureManager);

	SAFE_UNINIT(m_Fade);

	SAFE_DELETE(m_Light);

	SAFE_UNINIT(m_Camera);

	SAFE_UNINIT(m_Renderer);

#ifdef ENABLE_CONSOLE
	Console::Uninit();
#endif
}

void Game::Update(void)
{
	m_Camera->Update();

	m_Keyboard->Update();

#ifdef _DEBUG
	m_Mouse->Update();
#endif

	m_XInput->Update();

	m_Fade->Update();


	if(!DebugMenu::GameBreak())
	{
		m_Scene->Update();
	}

	DebugMenu::Update();
}

void Game::Draw(void)
{
	m_Renderer->DrawBegin();

	m_Scene->Draw();

	m_Fade->Draw();

	DebugFont::Draw();

	DebugMenu::Draw();

	m_Renderer->DrawEnd();
}

/*-----------------------------------------------------------------------------
Function:   void Game::SetScene(Scene* scene)
Parameter:  Scene *scene
              �V�[���̃|�C���^
Overview:   �V�[���̐؂�ւ�
-----------------------------------------------------------------------------*/
void Game::SetScene(Scene* scene)
{
	SAFE_UNINIT(m_Scene);

	m_Scene = scene;

	m_Scene->Initialize();
}