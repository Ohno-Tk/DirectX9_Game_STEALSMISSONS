/*=============================================================================

テクスチャ(DirectX)[ TextureDirectX.cpp ]

-------------------------------------------------------------------------------
■  Author
	Ohno Takuya

■  Create
	2017/10/22
=============================================================================*/

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "Common.h"
#include "Debug.h"
#include "RendererDirectX.h"
#include "TextureManagerDirectX.h"

/*-----------------------------------------------------------------------------
Namespace
-----------------------------------------------------------------------------*/
using namespace std;

void TextureManagerDirectX::Initialize(void)
{
	Load(TEXTURE_PATH"Fade.jpg");
	Load(TEXTURE_PATH"effect000.jpg");
	Load(TEXTURE_PATH"TITLE/PushEnter.png");
	Load(TEXTURE_PATH"TITLE/Title_Logo.png");
	Load(TEXTURE_PATH"TITLE/Wall000.jpg");
	Load(TEXTURE_PATH"TITLE/PushBButtom.png");
	Load(TEXTURE_PATH"TITLE/PushEnter.png");
	Load(TEXTURE_PATH"TITLE/Start_logo.png");
	Load(TEXTURE_PATH"TITLE/KeyGuid_logo.png");
	Load(TEXTURE_PATH"TUTORIAL/Communication_UI.png");
	Load(TEXTURE_PATH"TUTORIAL/Colonel.png");
	Load(TEXTURE_PATH"TUTORIAL/Snake.png");
	Load(TEXTURE_PATH"TUTORIAL/Description.png");
	Load(TEXTURE_PATH"TUTORIAL/BButtom.png");
	Load(TEXTURE_PATH"GAME/White.png");
	Load(TEXTURE_PATH"GAME/Mark_Find.png");
	Load(TEXTURE_PATH"GAME/field.jpg");
	Load(TEXTURE_PATH"GAME/Wall.jpg");
	Load(TEXTURE_PATH"GAME/GuageBar_Frame.png");
	Load(TEXTURE_PATH"GAME/GuageBar.png");
	Load(TEXTURE_PATH"GAME/Life_logo.png");
	Load(TEXTURE_PATH"GAME/Mark_Question.png");
	Load(TEXTURE_PATH"GAME/ItemGetUI_Ration.png");
	Load(TEXTURE_PATH"GAME/Number003.png");
	Load(TEXTURE_PATH"GAME/Ration_UI.png");
	Load(TEXTURE_PATH"RESULT/ClearLogo.png");
	Load(TEXTURE_PATH"RESULT/Retry.png");
	Load(TEXTURE_PATH"RESULT/End.png");
	Load(TEXTURE_PATH"RESULT/GameOver_Bg.jpg");
	Load(TEXTURE_PATH"RESULT/Continue.png");
	Load(TEXTURE_PATH"RESULT/GameClear_Bg.jpg");
	Load(TEXTURE_PATH"RESULT/GameOver_Logo.png");
	Load(TEXTURE_PATH"GUID/KeyGuid.jpg");
}

/*-----------------------------------------------------------------------------
Function:   void TextureManagerDirectX::Load(string FileName, D3DXVECTOR2 Div)
Parameter:  string FileName
			  テクスチャのパス
            D3DXVECTOR2 Div
			  テクスチャの分割数
Overview:   テクスチャの読み込み
-----------------------------------------------------------------------------*/
void TextureManagerDirectX::Load(string FileName, D3DXVECTOR2 Div)
{
	m_TextureInfo.Div = Div;

	//	同じファイルが存在するかの検索
	auto it = m_Texture_Map.find(FileName);

	if (it == m_Texture_Map.end())
	{	//	存在しなかったら

		HRESULT hr;

		LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();

		hr = D3DXCreateTextureFromFile(Device, FileName.c_str(), &m_TextureInfo.Texture);

		if (FAILED(hr))
		{
			MessageBox(NULL, "テクスチャが読み込めませんでした", "TextureDirectX.cpp", MB_OK | MB_ICONHAND);
			return;
		}

		//テクスチャ詳細情報取得
		D3DXIMAGE_INFO ImageInfo;
		D3DXGetImageInfoFromFile(FileName.c_str(), &ImageInfo);
		m_TextureInfo.Size.x = ImageInfo.Width / Div.x;
		m_TextureInfo.Size.y = ImageInfo.Height / Div.y;


		//	キーと値を連結させる
		m_Texture_Map[FileName] = m_TextureInfo;
	}
}

/*-----------------------------------------------------------------------------
Function:   void TextureManagerDirectX::UnloadAll(void)
Overview:   テクスチャの全削除
-----------------------------------------------------------------------------*/
void TextureManagerDirectX::UnloadAll(void)
{
	for (auto it = m_Texture_Map.begin(); it != m_Texture_Map.end(); ++it)
	{
		SAFE_RELEASE(it->second.Texture);
	}

	m_Texture_Map.clear();	//	全要素の削除
}

/*-----------------------------------------------------------------------------
Function:   const TEXTUREINFO TextureManagerDirectX::GetTextureInfo(string fileName)const
Parameter:  string fileName
			  テクスチャのパス
Overview:   テクスチャ情報の取得
-----------------------------------------------------------------------------*/
const TEXTUREINFO TextureManagerDirectX::GetTextureInfo(string fileName)const
{
	//	ファイルが存在するかのチェック
	auto it = m_Texture_Map.find(fileName);

	if (it != m_Texture_Map.end()){ return it->second; } //	存在していたら

	Debug::Assert(fileName+"が取得できませんでした", "TextureDirectX.cpp", "");

	TEXTUREINFO error;

	return error;
}