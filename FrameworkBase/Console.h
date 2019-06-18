/*=============================================================================

	コンソール[ Console.h ]

-------------------------------------------------------------------------------
■  Author
	Ohno Takuya

■  Create
	2017/10/15
------------------------------------------------------------------------------- 
■  Update
	2017/10/28
=============================================================================*/

#ifndef _CONSOLE_H_
#define _CONSOLE_H_

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include <io.h>
#include <Fcntl.h>

/*-----------------------------------------------------------------------------
Enum
-----------------------------------------------------------------------------*/
enum CONSOLECOLOR
{
	CONSOLE_BLACK = 0x00,
	CONSOLE_DARK_BLUE = 0x01,
	CONSOLE__DARK_GREEN = 0x02,
	CONSOLE_DARK_CYAN = 0x03,
	CONSOLE_DARK_RED = 0x04,
	CONSOLE_DARK_VIOLET = 0x05,
	CONSOLE_DARK_YELLOW = 0x06,
	CONSOLE_GRAY = 0x07,
	CONSOLE_LIGHT_GRAY = 0x08,
	CONSOLE_BLUE = 0x09,
	CONSOLE_GREEN = 0x0a,
	CONSOLE_CYAN = 0x0b,
	CONSOLE_RED = 0x0c,
	CONSOLE_VIOLET = 0x0d,
	CONSOLE_YELLOW = 0x0e,
	CONSOLE_WHITE = 0x0f,
	CONSOLE_INTENSITY = 0x08, //	高輝度マスク
	CONSOLE_RED_MASK = 0x04,
	CONSOLE_GREEN_MASK = 0x02,
	CONSOLE_BLUE_MASK = 0x01,
};

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class Console
{
public:
	static void Init(void);
	static void Uninit(void);

	static void SetColor(CONSOLECOLOR text = CONSOLE_GRAY, CONSOLECOLOR background = CONSOLE_BLACK);

private:
	static HANDLE ConsoleHandle; // コンソールハンドル
};

#endif
