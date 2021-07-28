/*=============================================================================

�f�o�b�O�p[ Debug.h ]

-------------------------------------------------------------------------------


��  Create
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
	PATTERN_NETWORK = 0, // �l�b�g���[�N
	PATTERN_WARNING, // �x��
};

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class Debug
{
public:
	static void Assert(std::string message); // Assert�o��
	static void Assert(std::string message, std::string filename, std::string line);

	static void Log(std::string message); // �R���\�[���o��
	static void Log(std::string message, PROCESSPATTERN pattern);
	template <class T> static void Log(std::string message, T value){
		std::cout << message << value << std::endl;
	}
};

#endif
