/*=============================================================================

モデル管理[ ModelManagerDirectX.cpp ]

-------------------------------------------------------------------------------
■  Author
	Ohno Takuya

■  Create
	2017/08/25
=============================================================================*/

/*-----------------------------------------------------------------------------
Warning Prevention
-----------------------------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include <string.h>
#include "Common.h"
#include "Debug.h"
#include "RendererDirectX.h"
#include "ModelManagerDirectX.h"

/*-----------------------------------------------------------------------------
Namespace
-----------------------------------------------------------------------------*/
using namespace std;


void ModelManagerDirectX::Initialize(void)
{
	Load(MODEL_PATH"Goal.x");
	Load(MODEL_PATH"Pillar.x");
	Load(MODEL_PATH"StecilShadow.x");
	Load(MODEL_PATH"Container.x");
	Load(MODEL_PATH"FolkLift.x");
	Load(MODEL_PATH"Ration.x");
	Load(MODEL_PATH"Lift.x");
}

/*-----------------------------------------------------------------------------
Function:   void ModelManagerDirectX::Load(string fileName)
Parameter:  string fileName
			  テクスチャのパス
Overview:   モデルのロード
-----------------------------------------------------------------------------*/
void ModelManagerDirectX::Load(string fileName)
{
	//	同じファイルが存在するかのチェック
	auto it = m_Model_Map.find(fileName);

	if (it == m_Model_Map.end())
	{	//	存在しなかったら

		HRESULT hr;

		//	デバイスの取得
		LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();

		// Xファイルの読み込み
		hr = D3DXLoadMeshFromX(fileName.c_str(), // ファイル名
			D3DXMESH_SYSTEMMEM,
			Device, // デバイス
			&m_Model.AdjacecyBuffer, // 隣接バッファ
			&m_Model.BufferMaterial, // マテリアル情報を格納
			NULL,
			&m_Model.NumMaterial, // マテリアル数
			&m_Model.Mesh);	 //	メッシュ

		if (FAILED(hr))
		{
			fileName += "が読み込めませんでした";
			Debug::Assert(fileName, "ModelManagerDirectX.cpp", "");
			return;
		}


		//	テクスチャの読み込み
		m_Model.Material = (D3DXMATERIAL*)m_Model.BufferMaterial->GetBufferPointer();
		m_Model.Texture = new LPDIRECT3DTEXTURE9[m_Model.NumMaterial];
		for (int i = 0; i < (int)m_Model.NumMaterial; i++)
		{

			m_Model.Texture[i] = NULL;

			if (m_Model.Material[i].pTextureFilename)
			{
				char filePath[MAX_PATH];
				strcpy(filePath, TEXTURE_PATH);
				strcat(filePath, m_Model.Material[i].pTextureFilename);

				hr = D3DXCreateTextureFromFile(Device, filePath, &m_Model.Texture[i]);

				if (FAILED(hr))
				{
					Debug::Assert(fileName+"の"+filePath+"が読み込めませんでした", "ModelManagerDirectX.cpp", "");
					return;
				}
			}
			else
			{
				hr = D3DXCreateTextureFromFile(Device, TEXTURE_PATH"GAME/White.png", &m_Model.Texture[i]);
			}
		}

		// メッシュの最適化
		hr = m_Model.Mesh->OptimizeInplace(D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_VERTEXCACHE,
			(DWORD*)m_Model.AdjacecyBuffer->GetBufferPointer(), NULL, NULL, NULL);

		if (FAILED(hr))
		{
			MessageBox(NULL, "メッシュの最適化に失敗", "ModelManagerDirectX.cpp", MB_OK);
		}

		SAFE_RELEASE(m_Model.AdjacecyBuffer);

		//	キーと値を連結させる
		m_Model_Map[fileName] = m_Model;
	}
}

/*-----------------------------------------------------------------------------
Function:   void TextureManagerDirectX::UnloadAll(void)
Overview:   モデルの全削除
-----------------------------------------------------------------------------*/
void ModelManagerDirectX::UnloadAll(void)
{
	for (auto it = m_Model_Map.begin(); it != m_Model_Map.end(); ++it)
	{
		for (unsigned int i = 0; i < it->second.NumMaterial; i++)
		{
			if (it->second.Texture[i] == NULL){ continue; }

			SAFE_RELEASE(it->second.Texture[i]);
		}

		SAFE_ARRAYDELETE(it->second.Texture);

		SAFE_RELEASE(it->second.Mesh);

		SAFE_RELEASE(it->second.BufferMaterial);
	}

	m_Model_Map.clear(); // 全要素の削除
}

/*-----------------------------------------------------------------------------
Function:   const MODEL_PARAM ModelManagerDirectX::GetModelParam(string fileName)const
Parameter:  string fileName
			  テクスチャのパス
Overview:   モデル取得
-----------------------------------------------------------------------------*/
const MODEL_PARAM ModelManagerDirectX::GetModelParam(string fileName)const
{

	//	ファイルが存在するかのチェック
	auto it = m_Model_Map.find(fileName);

	if (it != m_Model_Map.end())
	{//	存在していたら


		return it->second;
	} 

	fileName += "が取得できませんでした";
	Debug::Assert(fileName, "ModelManagerDirectX.cpp", "");

	MODEL_PARAM error;

	return error;
}
