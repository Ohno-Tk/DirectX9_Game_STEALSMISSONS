/*=============================================================================

���_�V�F�[�_�[[ VertexShader.cpp ]

-------------------------------------------------------------------------------

��  Create
2017/11/16
=============================================================================*/

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include <Windows.h>
#include "FrameworkBase\Common.h"
#include "FrameworkBase\RendererDirectX.h"
#include "VertexShader.h"

/*-----------------------------------------------------------------------------
Namespace
-----------------------------------------------------------------------------*/
using namespace std;


VertexShader::VertexShader():m_VertexShader(NULL),
m_VertexShaderConstantTable(NULL){}

HRESULT VertexShader::Initialize(string filePath, string entryFunction)
{	
	HRESULT hr;
	LPD3DXBUFFER error = NULL;
	LPD3DXBUFFER code = NULL;

	LPDIRECT3DDEVICE9 device = RendererDirectX::GetDevice();

	// �V�F�[�_�[�t�@�C���ǂݍ���
	hr = D3DXCompileShaderFromFile(filePath.c_str(), // �t�@�C����
		NULL,NULL,
		entryFunction.c_str(), // �G���g���[�֐�
		"vs_3_0", // �o�[�e�b�N�X�V�F�[�_�[�o�[�W����
		0,
		&code, // �o�C�i���R�[�h
		&error, // �G���[����(������NULL)
		&m_VertexShaderConstantTable); // �R���X�^���g�e�[�u�����Ǘ����Ă����l�̃A�h���X
	if(FAILED(hr))
	{
		MessageBox(NULL, (LPCSTR)error->GetBufferPointer(), "D3DXCompileShaderFromFile(VertexShader)", MB_OK);
		OutputDebugString((LPCSTR)error->GetBufferPointer());

		error->Release();
		return E_FAIL;
	}

	// �o�[�e�b�N�X�V�F�[�_�[�̐���
	hr = device->CreateVertexShader((LPDWORD)code->GetBufferPointer(),&m_VertexShader);
	if(FAILED(hr))
	{
		MessageBox(NULL, "�o�[�e�b�N�X�V�F�[�_�[�̐����Ɏ��s", "�G���[", MB_OK);

		m_VertexShader->Release();
		code->Release();	
		error->Release();
		return E_FAIL;
	}

	if(code){code->Release();}	
	if(error){error->Release();}

	return S_OK;
}

void VertexShader::Uninitialize(void)
{
	SAFE_RELEASE(m_VertexShader);

	SAFE_RELEASE(m_VertexShaderConstantTable);
}