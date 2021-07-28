/*=============================================================================

�l�^��ԑJ��[ HumanState.h ]

-------------------------------------------------------------------------------

��  Create
2017/11/09
=============================================================================*/

#ifndef _HUMANSTATE_H_
#define _HUMANSTATE_H_

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class HumanState
{
public:
	virtual void Uninitialize(void) = 0;
	virtual void Update(D3DXVECTOR3 position) = 0;
};

class HumanStateNull:public HumanState
{
public:
	void Uninitialize(void)override{}
	void Update(D3DXVECTOR3 position)override{}
};

#endif
