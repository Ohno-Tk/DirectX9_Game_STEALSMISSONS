/*=============================================================================

�t�@�C���Ǘ�[ FileManager.cpp ]

-------------------------------------------------------------------------------


��  Create
	2017/08/25
=============================================================================*/

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "Common.h"
#include "Debug.h"
#include "FileManager.h"

/*-----------------------------------------------------------------------------
Namespace
-----------------------------------------------------------------------------*/
using namespace std;

/*-----------------------------------------------------------------------------
Function:   ifstream FileManager::ReadFile(string fileName, const ios_base::openmode mode)
Parameter:  string FileName
              �t�@�C����
            const ios_base::openmode Mode
			  �t�@�C���̊J���Ƃ��̃��[�h
Overview:   �t�@�C���̓ǂݍ���
-----------------------------------------------------------------------------*/
ifstream FileManager::ReadFile(string fileName, const ios_base::openmode mode)
{
	ifstream readingFile(fileName.c_str(), mode);

	// �G���[�`�F�b�N
	fileName += "���J���܂���ł���";
	if (!readingFile){ Debug::Assert(fileName, "FileManager.cpp", "37"); }

	fileName.clear();
	string().swap(fileName);

	return readingFile;
}

/*-----------------------------------------------------------------------------
Function:   ofstream FileManager::WriteFile(const string fileName, const ios_base::openmode mode)
Parameter:  const string FileName
              �t�@�C����
            const ios_base::openmode Mode
			  �t�@�C���̊J���Ƃ��̃��[�h
Overview:   �t�@�C���̓ǂݍ���
-----------------------------------------------------------------------------*/
ofstream FileManager::WriteFile(string fileName, const ios_base::openmode mode)
{
	ofstream writeingFile(fileName.c_str(), mode);

	// �G���[�`�F�b�N
	fileName += "���J���܂���ł���";
	if (!writeingFile){ Debug::Assert("FileManager.cpp", "54", fileName + "���J���܂���ł���"); }

	fileName.clear();
	string().swap(fileName);

	return writeingFile;
}
