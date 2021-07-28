/*=============================================================================

[ KeyGuidScene.h ]

-------------------------------------------------------------------------------

��  Create
2018/02/23
=============================================================================*/

#ifndef _KEYGUIDSCENE_H_
#define _KEYGUIDSCENE_H_

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "FrameworkBase\Scene.h"

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class KeyGuidScene:public Scene
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
