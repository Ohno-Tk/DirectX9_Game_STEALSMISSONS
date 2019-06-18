/*=============================================================================

ピクセルシェーダー[ PixelShader.cpp ]

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

	// ピクセルシェーダーファイルの読み込み
	hr = D3DXCompileShaderFromFile(filePath.c_str(), // ファイル名
		NULL,NULL,
		entryFunction.c_str(), // エントリー関数
		"ps_3_0", // シェーダーバージョン
		0,
		&code, // バイナリコード
		&error, // エラー文字(成功はNULL)
		&m_PixelShaderConstantTable); // コンスタントテーブルを管理してくれる人のアドレス
	if(FAILED(hr))
	{
		MessageBox(NULL, (LPCSTR)error->GetBufferPointer(), "D3DXCompileShaderFromFile(PixelShader)", MB_OK);
		OutputDebugString((LPCSTR)error->GetBufferPointer());
		
		error->Release();
	}

	// ピクセルシェーダーの生成
	hr = device->CreatePixelShader((LPDWORD)code->GetBufferPointer(),&m_PixelShader);
	if(FAILED(hr))
	{
		MessageBox(NULL, "ピクセルシェーダーの生成に失敗", "エラー", MB_OK);

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