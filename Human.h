/*=============================================================================

人型[ Human.h ]

-------------------------------------------------------------------------------
■  Author
	Ohno Takuya

■  Create
	2017/11/08
=============================================================================*/

#ifndef _HUMAN_H_
#define _HUMAN_H_

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "FrameworkBase\RendererDirectX.h"
#include "FrameworkBase\ModelManagerDirectX.h"
#include "FrameworkBase\MotionCharacterData.h"
#include "Object.h"
#include "FrameworkBase\Motion.h"

/*-----------------------------------------------------------------------------

-----------------------------------------------------------------------------*/
class HumanState;

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class Human:public Motion
{
public:
	Human(int Priolity);

	void Initialize(void)override;
	void Uninitialize(void)override;
	void Update(void)override;
	void Draw(void)override;

	void SetState(HumanState* state); // 状態のセット

	// Setter
	void SetActive(bool flag){ m_Active = flag; }

private:
	bool m_Active;

	HumanState* m_State; // 状態

};

#endif
