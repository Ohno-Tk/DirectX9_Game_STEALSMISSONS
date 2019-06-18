/*=============================================================================

テクスチャ(DirectX)[ TextureManagerDirectX.h ]

-------------------------------------------------------------------------------
■  Author
	Ohno Takuya

■  Create
	2017/10/22
=============================================================================*/

#ifndef _TEXTUREDIRECTX_H_
#define _TEXTUREDIRECTX_H_

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include <unordered_map>

/*-----------------------------------------------------------------------------
	Struct
-----------------------------------------------------------------------------*/
struct TEXTUREINFO
{
	LPDIRECT3DTEXTURE9 Texture;	//	テクスチャのポインタ
	D3DXVECTOR2 Size;			//	大きさ
	D3DXVECTOR2 Div;			//	分割数
};

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class TextureManagerDirectX
{
public:
	void Initialize(void);
	void Uninitialize(void){UnloadAll();}

	//	Getter
	const TEXTUREINFO GetTextureInfo(std::string fileName)const;

private:
	void Load(std::string FileName, D3DXVECTOR2 Div = D3DXVECTOR2(1.f, 1.f)); // テクスチャの読み込み
	void UnloadAll(void); // テクスチャの全削除

private:
	TEXTUREINFO m_TextureInfo;	//	テクスチャ情報

	std::unordered_map< std::string, TEXTUREINFO > m_Texture_Map;
};

#endif
