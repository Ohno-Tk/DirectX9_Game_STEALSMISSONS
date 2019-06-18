/*=============================================================================

デバッグ用[ Debug.cpp ]

-------------------------------------------------------------------------------
■  Author
	Ohno Takuya

■  Create
	2017/10/15
=============================================================================*/

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include <assert.h>
#include <fstream>
#include "Common.h"
#include "Console.h"
#include "Debug.h"

/*-----------------------------------------------------------------------------
Macro
-----------------------------------------------------------------------------*/
#define ERROR_FILENAME ("data/ErrorLog.txt")

/*-----------------------------------------------------------------------------
Namespace
-----------------------------------------------------------------------------*/
using namespace std;


/*-----------------------------------------------------------------------------
Function:   void CDebug::Assert(string message)
Parameter:  string message
              コンソールに表示させる文字列
Overview:   条件をアサートし、失敗時にエラーメッセージを記録
-----------------------------------------------------------------------------*/
void Debug::Assert(string message)
{
	// テキスト出力
	ofstream ofs(ERROR_FILENAME,ios::app);
	ofs << message.c_str() << endl;
	ofs.close();

	// コンソール出力
	Console::SetColor(CONSOLE_RED);
	cout << "エラーメッセージ" << endl;
	cout << message << endl;

	assert(!"コンソールにエラーを表示します and ErrorLog.txtに出力します");
}

/*-----------------------------------------------------------------------------
Function:   void CDebug::Assert(string message, string filename, string line)
Parameter:  string message
              コンソールに表示させる文字列
            string filename
              コンソールにエラーファイルを表示
            string line
              コンソールに行数を表示
Overview:   条件をアサートし、失敗時にエラーメッセージを記録
-----------------------------------------------------------------------------*/
void Debug::Assert(string message, string filename, string line)
{
	// テキスト出力
	ofstream ofs(ERROR_FILENAME,ios::out);
	ofs << filename.c_str() << "  " << line.c_str() << "行目" << "  " << message.c_str() << endl;
	ofs.close();
	
	// コンソール出力
	Console::SetColor(CONSOLE_RED);
	cout << "エラーメッセージ" << endl;
	cout << "ファイル名 : " << filename << endl;
	cout << "行数 : " << line << endl;

	assert(!"コンソールにエラーを表示します and ErrorLog.txtに出力します");
}

/*-----------------------------------------------------------------------------
Function:   void Debug::Log(string message)
Parameter:  string message
              コンソールに表示させる文字列
Overview:   コンソールにログメッセージを出力
-----------------------------------------------------------------------------*/
void Debug::Log(string message)
{
	cout << message << endl;
}

/*-----------------------------------------------------------------------------
Function:   void Debug::Log(string message, PROCESSPATTERN pattern)
Parameter:  string message
              コンソールに表示させる文字列
            PROCESSPATTERN pattern
			  コンソールの文字色を変える
Overview:   コンソールに表示させる文字列
-----------------------------------------------------------------------------*/
void Debug::Log(string message, PROCESSPATTERN pattern)
{
	switch (pattern)
	{
	case PATTERN_NETWORK:
		Console::SetColor(CONSOLE_GREEN);
		break;
	case PATTERN_WARNING:
		Console::SetColor(CONSOLE_YELLOW);
		break;
	}

	cout << message << endl;

	Console::SetColor();	//	色を元に戻す
}
