/*=============================================================================

ゲームオーバーシーン[ GameOverScene.h ]

-------------------------------------------------------------------------------
■  Author
Ohno Takuya

■  Create
2017/11/13
=============================================================================*/

#ifndef _GAMEOVERSCENE_H_
#define _GAMEOVERSCENE_H_

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "FrameworkBase\Scene.h"

/*-----------------------------------------------------------------------------

-----------------------------------------------------------------------------*/
class DirectXKeyboard;
class XInput;
class SoundDirectX;
class Sprite2D;
class Scroll2DObject;
class Fade2DObject;

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class GameOverScene:public Scene
{
public:
	void Initialize(void)override;
	void Uninitialize(void)override;
	void Update(void)override;
	void Draw(void)override;

private:
	void SceneChange(void); // シーンを変える
	void SelectMode(void); // 選択時
	void KeyboardControl(void); // キーボード操作

private:
	enum SELECT
	{
		SELECT_CONTINUE = 0,	//	コンティニュー
		SELECT_END,			//	エンド
		SELECT_MAX
	};

	int m_Select;	//	選択

	DirectXKeyboard* m_KeyBoard;
	XInput* m_XInput;
	SoundDirectX* m_Sound;

	Scroll2DObject* m_BackGround;
	Fade2DObject* m_ContiueLogo;
	Fade2DObject* m_EndLogo;
	Sprite2D* m_SelectFrame;
};

#endif
