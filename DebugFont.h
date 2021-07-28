/*=============================================================================

�f�o�b�O�����\��[ DebugFont.h ]

-------------------------------------------------------------------------------

��  Create
2017/06/21
=============================================================================*/

#ifndef _DEBUGFONT_H_
#define _DEBUGFONT_H_

/*-----------------------------------------------------------------------------
	Class
-----------------------------------------------------------------------------*/
class DebugFont
{
public:
	static void Initialize(void);
	static void Uninitialize(void);
	static void Draw(void);

	static void ClarText(void);			//	�����̏���
	static void AddText(char *Text);	//	�����̒ǉ�

private:
	static char m_Text[1024];

	static LPD3DXFONT m_Font;	// �t�H���g�ւ̃|�C���^
};

#endif