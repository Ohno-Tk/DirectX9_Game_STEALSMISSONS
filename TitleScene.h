/*=============================================================================

タイトルシーン[ TitleScene.h ]

-------------------------------------------------------------------------------
■  Author
Ohno Takuya

■  Create
2017/11/11
=============================================================================*/

#ifndef _TITLESCENE_H_
#define _TITLESCENE_H_

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "FrameworkBase\Scene.h"

class DirectXKeyboard;
class XInput;
class SoundDirectX;
class Sprite2D;
class Fade2DObject;

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class TitleScene:public Scene
{
public:
	void Initialize(void)override;
	void Uninitialize(void)override;
	void Update(void)override;
	void Draw(void)override;

private:
	void SelectMode(void); // 選択時
	void SceneChange(void); // シーンを変える
	void CursorControl(void); // カーソル操作

private:
	enum SELECT
	{
		SELECT_NONE = 0,
		SELECT_START,	//	スタート
		SELECT_KEYGUID,			//	操作説明
		SELECT_MAX
	};
	int m_Select;	//	選択

	DirectXKeyboard* m_KeyBoard;
	SoundDirectX* m_Sound;
	XInput* m_XInput;

	Fade2DObject* m_PushButtom;

	Sprite2D* m_SelectFrame;
	Sprite2D* m_Start_Logo;
	Sprite2D* m_KeyGuid_Logo;
};

#endif
