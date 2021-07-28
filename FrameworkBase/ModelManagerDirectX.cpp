/*=============================================================================

���f���Ǘ�[ ModelManagerDirectX.cpp ]

-------------------------------------------------------------------------------

��  Create
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
			  �e�N�X�`���̃p�X
Overview:   ���f���̃��[�h
-----------------------------------------------------------------------------*/
void ModelManagerDirectX::Load(string fileName)
{
	//	�����t�@�C�������݂��邩�̃`�F�b�N
	auto it = m_Model_Map.find(fileName);

	if (it == m_Model_Map.end())
	{	//	���݂��Ȃ�������

		HRESULT hr;

		//	�f�o�C�X�̎擾
		LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();

		// X�t�@�C���̓ǂݍ���
		hr = D3DXLoadMeshFromX(fileName.c_str(), // �t�@�C����
			D3DXMESH_SYSTEMMEM,
			Device, // �f�o�C�X
			&m_Model.AdjacecyBuffer, // �אڃo�b�t�@
			&m_Model.BufferMaterial, // �}�e���A�������i�[
			NULL,
			&m_Model.NumMaterial, // �}�e���A����
			&m_Model.Mesh);	 //	���b�V��

		if (FAILED(hr))
		{
			fileName += "���ǂݍ��߂܂���ł���";
			Debug::Assert(fileName, "ModelManagerDirectX.cpp", "");
			return;
		}


		//	�e�N�X�`���̓ǂݍ���
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
					Debug::Assert(fileName+"��"+filePath+"���ǂݍ��߂܂���ł���", "ModelManagerDirectX.cpp", "");
					return;
				}
			}
			else
			{
				hr = D3DXCreateTextureFromFile(Device, TEXTURE_PATH"GAME/White.png", &m_Model.Texture[i]);
			}
		}

		// ���b�V���̍œK��
		hr = m_Model.Mesh->OptimizeInplace(D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_VERTEXCACHE,
			(DWORD*)m_Model.AdjacecyBuffer->GetBufferPointer(), NULL, NULL, NULL);

		if (FAILED(hr))
		{
			MessageBox(NULL, "���b�V���̍œK���Ɏ��s", "ModelManagerDirectX.cpp", MB_OK);
		}

		SAFE_RELEASE(m_Model.AdjacecyBuffer);

		//	�L�[�ƒl��A��������
		m_Model_Map[fileName] = m_Model;
	}
}

/*-----------------------------------------------------------------------------
Function:   void TextureManagerDirectX::UnloadAll(void)
Overview:   ���f���̑S�폜
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

	m_Model_Map.clear(); // �S�v�f�̍폜
}

/*-----------------------------------------------------------------------------
Function:   const MODEL_PARAM ModelManagerDirectX::GetModelParam(string fileName)const
Parameter:  string fileName
			  �e�N�X�`���̃p�X
Overview:   ���f���擾
-----------------------------------------------------------------------------*/
const MODEL_PARAM ModelManagerDirectX::GetModelParam(string fileName)const
{

	//	�t�@�C�������݂��邩�̃`�F�b�N
	auto it = m_Model_Map.find(fileName);

	if (it != m_Model_Map.end())
	{//	���݂��Ă�����


		return it->second;
	} 

	fileName += "���擾�ł��܂���ł���";
	Debug::Assert(fileName, "ModelManagerDirectX.cpp", "");

	MODEL_PARAM error;

	return error;
}
