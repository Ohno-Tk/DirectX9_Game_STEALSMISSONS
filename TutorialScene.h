/*=============================================================================

チュートリアルシーン[ TutorialScene.h ]

-------------------------------------------------------------------------------
■  Author
Ohno Takuya

■  Create
2017/11/13
=============================================================================*/

#ifndef _TUTORIALSCENE_H_
#define _TUTORIALSCENE_H_

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "FrameworkBase\Scene.h"

class XInput;
class Fade2DObject;

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class TutorialScene:public Scene
{
public:
	void Initialize(void)override;
	void Uninitialize(void)override;
	void Update(void)override;
	void Draw(void)override;

private:
	void SceneChange(void); // シーンを変える

private:
	XInput* m_XInput;
	Fade2DObject* m_PushButtom;
};

#endif
