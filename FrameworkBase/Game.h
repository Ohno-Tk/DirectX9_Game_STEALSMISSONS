/*=============================================================================

ゲーム部分[ Game.h ]
(シングルトンパターン)

-------------------------------------------------------------------------------
■  Author
Ohno Takuya

■  Create
2017/11/11
=============================================================================*/

#ifndef _GAME_H_
#define _GAME_H_

/*-----------------------------------------------------------------------------

-----------------------------------------------------------------------------*/
class Renderer;
class Scene;
class CameraDirectX;
class LightDirectX;
class Fade;
class TextureManagerDirectX;
class ModelManagerDirectX;
class DirectXKeyboard;
#ifdef _DEBUG
	class DirectXMouse;
#endif
class XInput;
class SoundDirectX;
class MotionCharacterData;

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class Game
{
public:
	static Game* GetInstance(void); // インスタンス取得

	void SetScene(Scene* scene); // シーンの切り替え

	void Init(HINSTANCE instance, HWND wnd);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// Getter
	Renderer* GetRenderer(void){ return m_Renderer; }
	CameraDirectX* GetCamera(void){ return m_Camera; }
	TextureManagerDirectX* GetTextureManager(void){ return m_TextureManager; }
	ModelManagerDirectX* GetModelManager(void){ return m_ModelManager; }
	DirectXKeyboard* GetKeyboard(void){ return m_Keyboard; }
#ifdef _DEBUG
	DirectXMouse* GetMouse(void){ return m_Mouse; }
#endif
	XInput* GetXInput(void){ return m_XInput; }
	SoundDirectX* GetSound(void){ return m_Sound; }
	MotionCharacterData* GetMotionCharaData(void){ return m_MotionCharacterData; }

private:
	Game();
	Game(const Game& ref){}
	Game& operator=(const Game& ref){}

private:
	Renderer* m_Renderer;
	Scene* m_Scene;
	CameraDirectX* m_Camera;
	LightDirectX* m_Light;
	Fade* m_Fade;
	TextureManagerDirectX* m_TextureManager;
	ModelManagerDirectX* m_ModelManager;
	DirectXKeyboard* m_Keyboard;
#ifdef _DEBUG
	DirectXMouse* m_Mouse;
#endif
	XInput* m_XInput;
	SoundDirectX* m_Sound;
	MotionCharacterData* m_MotionCharacterData;
};

#endif
