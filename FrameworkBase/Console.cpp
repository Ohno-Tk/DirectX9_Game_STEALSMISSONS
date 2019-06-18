/*=============================================================================

	コンソール[ Console.cpp ]

-------------------------------------------------------------------------------
■  Author
	Ohno Takuya

■  Create
	2017/10/15
=============================================================================*/

/*-----------------------------------------------------------------------------
Warning Prevention
-----------------------------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include "Common.h"
#include "Console.h"

/*-----------------------------------------------------------------------------
Namespace
-----------------------------------------------------------------------------*/
using namespace std;

/*-----------------------------------------------------------------------------
Static
-----------------------------------------------------------------------------*/
HANDLE Console::ConsoleHandle = 0;

void Console::Init(void)
{
	AllocConsole();	// コンソールを作成

	freopen("CON", "r", stdin);     // 標準入力の割り当て
	freopen("CON", "w", stdout);    // 標準出力の割り当て

	ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // コンソールハンドル取得
}

void Console::Uninit(void)
{
	FreeConsole();	//	コンソールの解放
}

void Console::SetColor(CONSOLECOLOR text, CONSOLECOLOR background)
{
	WORD attr = 0; //  API に渡すアトリビュート

	if (text & CONSOLE_INTENSITY) { attr |= FOREGROUND_INTENSITY; }
	if (text & CONSOLE_RED_MASK) { attr |= FOREGROUND_RED; }
	if (text & CONSOLE_GREEN_MASK) { attr |= FOREGROUND_GREEN; }
	if (text & CONSOLE_BLUE_MASK) { attr |= FOREGROUND_BLUE; }

	if (background & CONSOLE_INTENSITY) { attr |= BACKGROUND_INTENSITY; }
	if (background & CONSOLE_RED_MASK) { attr |= BACKGROUND_RED; }
	if (background & CONSOLE_GREEN_MASK) { attr |= BACKGROUND_GREEN; }
	if (background & CONSOLE_BLUE_MASK) { attr |= BACKGROUND_BLUE; }

	SetConsoleTextAttribute(ConsoleHandle, attr);
}
