/*=============================================================================

		デバッグ文字表示[ DebugFont.cpp ]

-------------------------------------------------------------------------------
	■  Author
		Ohno Takuya

	■  Created Date
		2017/06/21
------------------------------------------------------------------------------- 
	■  Update
		2017/09/14
=============================================================================*/

/*-----------------------------------------------------------------------------
	Warning Prevention
-----------------------------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS

/*-----------------------------------------------------------------------------
	Header
-----------------------------------------------------------------------------*/
#include <string.h>
#include "FrameworkBase\RendererDirectX.h"
#include "FrameworkBase\Common.h"
#include "DebugFont.h"

/*-----------------------------------------------------------------------------
	Static
-----------------------------------------------------------------------------*/
char DebugFont::m_Text[] = {};
LPD3DXFONT DebugFont::m_Font = NULL;

void DebugFont::Initialize(void)
{
	LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();


	D3DXCreateFont(Device, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_Font);
}

void DebugFont::Uninitialize(void)
{
	SAFE_RELEASE(m_Font);
}

void DebugFont::Draw(void)
{

	RECT rect = { 0, 30, SCREEN_WIDTH, SCREEN_HEIGHT };


	m_Font->DrawText(NULL, m_Text, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

}

/*-----------------------------------------------------------------------------
文字の消去
-----------------------------------------------------------------------------*/
void DebugFont::ClarText(void)
{
	strcpy(m_Text, "");
}

/*-----------------------------------------------------------------------------
文字の追加
-----------------------------------------------------------------------------*/
void DebugFont::AddText(char *Text)
{
	strcat(m_Text, Text);
}