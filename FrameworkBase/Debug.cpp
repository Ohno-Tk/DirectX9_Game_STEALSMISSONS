/*=============================================================================

�f�o�b�O�p[ Debug.cpp ]

-------------------------------------------------------------------------------


��  Create
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
              �R���\�[���ɕ\�������镶����
Overview:   �������A�T�[�g���A���s���ɃG���[���b�Z�[�W���L�^
-----------------------------------------------------------------------------*/
void Debug::Assert(string message)
{
	// �e�L�X�g�o��
	ofstream ofs(ERROR_FILENAME,ios::app);
	ofs << message.c_str() << endl;
	ofs.close();

	// �R���\�[���o��
	Console::SetColor(CONSOLE_RED);
	cout << "�G���[���b�Z�[�W" << endl;
	cout << message << endl;

	assert(!"�R���\�[���ɃG���[��\�����܂� and ErrorLog.txt�ɏo�͂��܂�");
}

/*-----------------------------------------------------------------------------
Function:   void CDebug::Assert(string message, string filename, string line)
Parameter:  string message
              �R���\�[���ɕ\�������镶����
            string filename
              �R���\�[���ɃG���[�t�@�C����\��
            string line
              �R���\�[���ɍs����\��
Overview:   �������A�T�[�g���A���s���ɃG���[���b�Z�[�W���L�^
-----------------------------------------------------------------------------*/
void Debug::Assert(string message, string filename, string line)
{
	// �e�L�X�g�o��
	ofstream ofs(ERROR_FILENAME,ios::out);
	ofs << filename.c_str() << "  " << line.c_str() << "�s��" << "  " << message.c_str() << endl;
	ofs.close();
	
	// �R���\�[���o��
	Console::SetColor(CONSOLE_RED);
	cout << "�G���[���b�Z�[�W" << endl;
	cout << "�t�@�C���� : " << filename << endl;
	cout << "�s�� : " << line << endl;

	assert(!"�R���\�[���ɃG���[��\�����܂� and ErrorLog.txt�ɏo�͂��܂�");
}

/*-----------------------------------------------------------------------------
Function:   void Debug::Log(string message)
Parameter:  string message
              �R���\�[���ɕ\�������镶����
Overview:   �R���\�[���Ƀ��O���b�Z�[�W���o��
-----------------------------------------------------------------------------*/
void Debug::Log(string message)
{
	cout << message << endl;
}

/*-----------------------------------------------------------------------------
Function:   void Debug::Log(string message, PROCESSPATTERN pattern)
Parameter:  string message
              �R���\�[���ɕ\�������镶����
            PROCESSPATTERN pattern
			  �R���\�[���̕����F��ς���
Overview:   �R���\�[���ɕ\�������镶����
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

	Console::SetColor();	//	�F�����ɖ߂�
}
