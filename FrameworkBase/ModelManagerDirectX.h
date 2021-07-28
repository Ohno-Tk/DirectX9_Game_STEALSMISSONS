/*=============================================================================

���f���Ǘ�[ ModelManager.h ]

-------------------------------------------------------------------------------

��  Create
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
	DWORD				NumMaterial;	//	�}�e���A�����̐�
	LPD3DXBUFFER		BufferMaterial;	//	�}�e���A�����
	LPD3DXBUFFER        AdjacecyBuffer; //  �אڃo�b�t�@
	D3DXMATERIAL*		Material;		//	�}�e���A���|�C���^
	LPD3DXMESH			Mesh;			//	���b�V�����
	LPD3DXMESH			CloneMesh;
	LPDIRECT3DTEXTURE9*	Texture;		//	�e�N�X�`���̃|�C���^
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
	void Load(std::string fileName); // ���f���̃��[�h
	void UnloadAll(void); // ���f���̑S�폜

private:
	MODEL_PARAM m_Model; // ���f���\����

	std::unordered_map< std::string, MODEL_PARAM > m_Model_Map;
}; 

#endif