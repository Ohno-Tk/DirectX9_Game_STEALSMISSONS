/*=============================================================================

�^�C�g���V�[��[ TitleScene.h ]

-------------------------------------------------------------------------------

��  Create
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
	void SelectMode(void); // �I����
	void SceneChange(void); // �V�[����ς���
	void CursorControl(void); // �J�[�\������

private:
	enum SELECT
	{
		SELECT_NONE = 0,
		SELECT_START,	//	�X�^�[�g
		SELECT_KEYGUID,			//	�������
		SELECT_MAX
	};
	int m_Select;	//	�I��

	DirectXKeyboard* m_KeyBoard;
	SoundDirectX* m_Sound;
	XInput* m_XInput;

	Fade2DObject* m_PushButtom;

	Sprite2D* m_SelectFrame;
	Sprite2D* m_Start_Logo;
	Sprite2D* m_KeyGuid_Logo;
};

#endif
