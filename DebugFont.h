/*=============================================================================

デバッグ文字表示[ DebugFont.h ]

-------------------------------------------------------------------------------
■  Author
Ohno Takuya

■  Create
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

	static void ClarText(void);			//	文字の消去
	static void AddText(char *Text);	//	文字の追加

private:
	static char m_Text[1024];

	static LPD3DXFONT m_Font;	// フォントへのポインタ
};

#endif