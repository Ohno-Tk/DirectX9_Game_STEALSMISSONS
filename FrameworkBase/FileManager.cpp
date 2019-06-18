/*=============================================================================

ファイル管理[ FileManager.cpp ]

-------------------------------------------------------------------------------
■  Author
	Ohno Takuya

■  Create
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
              ファイル名
            const ios_base::openmode Mode
			  ファイルの開くときのモード
Overview:   ファイルの読み込み
-----------------------------------------------------------------------------*/
ifstream FileManager::ReadFile(string fileName, const ios_base::openmode mode)
{
	ifstream readingFile(fileName.c_str(), mode);

	// エラーチェック
	fileName += "が開けませんでした";
	if (!readingFile){ Debug::Assert(fileName, "FileManager.cpp", "37"); }

	fileName.clear();
	string().swap(fileName);

	return readingFile;
}

/*-----------------------------------------------------------------------------
Function:   ofstream FileManager::WriteFile(const string fileName, const ios_base::openmode mode)
Parameter:  const string FileName
              ファイル名
            const ios_base::openmode Mode
			  ファイルの開くときのモード
Overview:   ファイルの読み込み
-----------------------------------------------------------------------------*/
ofstream FileManager::WriteFile(string fileName, const ios_base::openmode mode)
{
	ofstream writeingFile(fileName.c_str(), mode);

	// エラーチェック
	fileName += "が開けませんでした";
	if (!writeingFile){ Debug::Assert("FileManager.cpp", "54", fileName + "が開けませんでした"); }

	fileName.clear();
	string().swap(fileName);

	return writeingFile;
}
