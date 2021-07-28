/*=============================================================================

	�R���\�[��[ Console.cpp ]

-------------------------------------------------------------------------------


��  Create
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
	AllocConsole();	// �R���\�[�����쐬

	freopen("CON", "r", stdin);     // �W�����͂̊��蓖��
	freopen("CON", "w", stdout);    // �W���o�͂̊��蓖��

	ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // �R���\�[���n���h���擾
}

void Console::Uninit(void)
{
	FreeConsole();	//	�R���\�[���̉��
}

void Console::SetColor(CONSOLECOLOR text, CONSOLECOLOR background)
{
	WORD attr = 0; //  API �ɓn���A�g���r���[�g

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
