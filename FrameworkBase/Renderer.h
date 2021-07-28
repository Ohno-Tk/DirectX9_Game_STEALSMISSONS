/*=============================================================================

�����_���[[ Renderer.h ]

-------------------------------------------------------------------------------

��  Create
	2017/10/14
=============================================================================*/

#ifndef _RENDERER_H_
#define _RENDERER_H_

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include <Windows.h>

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class Renderer
{
public:
	virtual HRESULT Initialize(HWND hWnd) = 0;
	virtual void Uninitialize(void) = 0;
	virtual void DrawBegin(void) = 0;
	virtual void DrawEnd(void) = 0;

	virtual void Normal(void) = 0; // �ʏ펞
	virtual void WireFrame(void) = 0; // ���C���[�t���[��
};

#endif
