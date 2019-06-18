/*=============================================================================

�J�������( �Ǐ] )[ CameraStateFollow.h ]

-------------------------------------------------------------------------------
��  Author
Ohno Takuya

��  Create
2017/11/22
=============================================================================*/

#ifndef _CAMERASTATEFOLLOW_H_
#define _CAMERASTATEFOLLOW_H_

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "CameraState.h"

/*-----------------------------------------------------------------------------

-----------------------------------------------------------------------------*/
class CameraDirectX;

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class CameraStateFollow:public CameraState
{
public:
	CameraStateFollow(CameraDirectX* owner);

	void Update(void)override;

private:
	CameraDirectX* m_Owner;

};

#endif
