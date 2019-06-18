/*=============================================================================

デバッグ用[ Debug.h ]

-------------------------------------------------------------------------------
■  Author
	Ohno Takuya

■  Create
	2017/10/15
=============================================================================*/

#ifndef _DEBUG_H_
#define _DEBUG_H_

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include <iostream>

/*-----------------------------------------------------------------------------
Enum
-----------------------------------------------------------------------------*/
enum PROCESSPATTERN
{
	PATTERN_NETWORK = 0, // ネットワーク
	PATTERN_WARNING, // 警告
};

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class Debug
{
public:
	static void Assert(std::string message); // Assert出力
	static void Assert(std::string message, std::string filename, std::string line);

	static void Log(std::string message); // コンソール出力
	static void Log(std::string message, PROCESSPATTERN pattern);
	template <class T> static void Log(std::string message, T value){
		std::cout << message << value << std::endl;
	}
};

#endif
