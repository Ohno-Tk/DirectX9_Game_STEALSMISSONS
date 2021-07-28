/*=============================================================================

�s�N�Z���V�F�[�_�[[ PixelShader.cpp ]

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
#include "PixelShader.h"

/*-----------------------------------------------------------------------------
Namespace
-----------------------------------------------------------------------------*/
using namespace std;


PixelShader::PixelShader():m_PixelShader(NULL),
m_PixelShaderConstantTable(NULL){}

void PixelShader::Initialize(string filePath, string entryFunction)
{
	HRESULT hr;
	LPD3DXBUFFER error = NULL;
	LPD3DXBUFFER code = NULL;

	LPDIRECT3DDEVICE9 device = RendererDirectX::GetDevice();

	// �s�N�Z���V�F�[�_�[�t�@�C���̓ǂݍ���
	hr = D3DXCompileShaderFromFile(filePath.c_str(), // �t�@�C����
		NULL,NULL,
		entryFunction.c_str(), // �G���g���[�֐�
		"ps_3_0", // �V�F�[�_�[�o�[�W����
		0,
		&code, // �o�C�i���R�[�h
		&error, // �G���[����(������NULL)
		&m_PixelShaderConstantTable); // �R���X�^���g�e�[�u�����Ǘ����Ă����l�̃A�h���X
	if(FAILED(hr))
	{
		MessageBox(NULL, (LPCSTR)error->GetBufferPointer(), "D3DXCompileShaderFromFile(PixelShader)", MB_OK);
		OutputDebugString((LPCSTR)error->GetBufferPointer());
		
		error->Release();
	}

	// �s�N�Z���V�F�[�_�[�̐���
	hr = device->CreatePixelShader((LPDWORD)code->GetBufferPointer(),&m_PixelShader);
	if(FAILED(hr))
	{
		MessageBox(NULL, "�s�N�Z���V�F�[�_�[�̐����Ɏ��s", "�G���[", MB_OK);

		if(m_PixelShader){m_PixelShader->Release();}
		if(code){code->Release();}	
		if(error){error->Release();}
	}

	if(code){code->Release();}
	if(error){error->Release();}
}

void PixelShader::Uninitialize(void)
{
	SAFE_RELEASE(m_PixelShader);

	SAFE_RELEASE(m_PixelShaderConstantTable);	
}