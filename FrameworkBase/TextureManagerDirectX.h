/*=============================================================================

�e�N�X�`��(DirectX)[ TextureManagerDirectX.h ]

-------------------------------------------------------------------------------

��  Create
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
	LPDIRECT3DTEXTURE9 Texture;	//	�e�N�X�`���̃|�C���^
	D3DXVECTOR2 Size;			//	�傫��
	D3DXVECTOR2 Div;			//	������
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
	void Load(std::string FileName, D3DXVECTOR2 Div = D3DXVECTOR2(1.f, 1.f)); // �e�N�X�`���̓ǂݍ���
	void UnloadAll(void); // �e�N�X�`���̑S�폜

private:
	TEXTUREINFO m_TextureInfo;	//	�e�N�X�`�����

	std::unordered_map< std::string, TEXTUREINFO > m_Texture_Map;
};

#endif
