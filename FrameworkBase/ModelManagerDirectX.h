/*=============================================================================

モデル管理[ ModelManager.h ]

-------------------------------------------------------------------------------
■  Author
	Ohno Takuya

■  Create
	2017/08/25
=============================================================================*/

#ifndef _MODELMANAGER_H_
#define _MODELMANAGER_H_

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include <unordered_map>

/*-----------------------------------------------------------------------------
Struct
-----------------------------------------------------------------------------*/
struct MODEL_PARAM
{
	DWORD				NumMaterial;	//	マテリアル情報の数
	LPD3DXBUFFER		BufferMaterial;	//	マテリアル情報
	LPD3DXBUFFER        AdjacecyBuffer; //  隣接バッファ
	D3DXMATERIAL*		Material;		//	マテリアルポインタ
	LPD3DXMESH			Mesh;			//	メッシュ情報
	LPD3DXMESH			CloneMesh;
	LPDIRECT3DTEXTURE9*	Texture;		//	テクスチャのポインタ
};

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class ModelManagerDirectX
{
public:
	void Initialize(void);
	void Uninitialize(void){UnloadAll();}

	//	Getter
	const MODEL_PARAM GetModelParam(std::string fileName)const;

private:
	void Load(std::string fileName); // モデルのロード
	void UnloadAll(void); // モデルの全削除

private:
	MODEL_PARAM m_Model; // モデル構造体

	std::unordered_map< std::string, MODEL_PARAM > m_Model_Map;
}; 

#endif