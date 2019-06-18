/*=============================================================================

頂点シェーダー[ VertexShader.cpp ]

-------------------------------------------------------------------------------
■  Author
Ohno Takuya

■  Create
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

	// シェーダーファイル読み込み
	hr = D3DXCompileShaderFromFile(filePath.c_str(), // ファイル名
		NULL,NULL,
		entryFunction.c_str(), // エントリー関数
		"vs_3_0", // バーテックスシェーダーバージョン
		0,
		&code, // バイナリコード
		&error, // エラー文字(成功はNULL)
		&m_VertexShaderConstantTable); // コンスタントテーブルを管理してくれる人のアドレス
	if(FAILED(hr))
	{
		MessageBox(NULL, (LPCSTR)error->GetBufferPointer(), "D3DXCompileShaderFromFile(VertexShader)", MB_OK);
		OutputDebugString((LPCSTR)error->GetBufferPointer());

		error->Release();
		return E_FAIL;
	}

	// バーテックスシェーダーの生成
	hr = device->CreateVertexShader((LPDWORD)code->GetBufferPointer(),&m_VertexShader);
	if(FAILED(hr))
	{
		MessageBox(NULL, "バーテックスシェーダーの生成に失敗", "エラー", MB_OK);

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