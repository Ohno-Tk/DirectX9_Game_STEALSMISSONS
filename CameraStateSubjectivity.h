/*=============================================================================

ÉJÉÅÉâèÛë‘(éÂäœ)[ CameraStateSubjectivity.h ]

-------------------------------------------------------------------------------
Å°  Author
Ohno Takuya

Å°  Create
2018/01/19
=============================================================================*/

#ifndef _CAMERASTATESUBJECIVITY_H_
#define _CAMERASTATESUBJECIVITY_H_

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "CameraState.h"

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class CameraStateSubjectivity:public CameraState
{
public:
	CameraStateSubjectivity(CameraDirectX* owner);

	void Update(void)override;

private:
	CameraDirectX* m_Owner;
};

#endif
