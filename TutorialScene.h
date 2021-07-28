/*=============================================================================

�`���[�g���A���V�[��[ TutorialScene.h ]

-------------------------------------------------------------------------------

��  Create
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
	void SceneChange(void); // �V�[����ς���

private:
	XInput* m_XInput;
	Fade2DObject* m_PushButtom;
};

#endif
