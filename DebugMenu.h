/*=============================================================================

�f�o�b�O���j���[[ DebugMenu.h ]

-------------------------------------------------------------------------------

��  Create
2017/12/19
=============================================================================*/

#ifndef _DEBUGMENU_H_
#define _DEBUGMENU_H_

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class DebugMenu
{
public:
	static void Initialize(void);
	static void Uninitialize(void);
	static void Update(void);
	static void Draw(void);

	static bool GameBreak(void){ return m_GameStop; }

private:
	static LPD3DXFONT m_Font;

	static bool m_GameStop;
	static bool m_Active;
	static bool m_WireFrameActive;
	static bool m_VisionActive;
	static bool m_ControlPointActive;
};

#endif
