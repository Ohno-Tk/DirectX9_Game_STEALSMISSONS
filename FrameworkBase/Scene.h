/*=============================================================================

âÊñ ëJà⁄[ Scene.h ]

-------------------------------------------------------------------------------
Å°  Author
	Ohno Takuya

Å°  Create
	2017/10/15
=============================================================================*/

#ifndef _SCENE_H_
#define _SCENE_H_

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class Scene
{
public:
	virtual void Initialize(void) = 0;
	virtual void Uninitialize(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
};

class TestScene:public Scene
{
public:
	void Initialize(void)override;
	void Uninitialize(void)override;
	void Update(void)override;
	void Draw(void)override;
};

#endif
