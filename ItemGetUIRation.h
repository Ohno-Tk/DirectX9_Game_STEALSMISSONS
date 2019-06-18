/*=============================================================================

アイテム取得UI( レーション )[ ItemGetUIRation.h ]

-------------------------------------------------------------------------------
■  Author
Ohno Takuya

■  Create
2018/01/22
=============================================================================*/

#ifndef _ITEMGETUIRATION_H_
#define _ITEMGETUIRATION_H_

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "ItemGetUI.h"

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class ItemGetUIRation:public ItemGetUI
{
public:
	ItemGetUIRation(int priolity = 4);

	static ItemGetUIRation* Create(D3DXVECTOR3 position);// 生成

	void Initialize(void)override;
	void Uninitialize(void)override;
	void Update(void)override;
	void Draw(void)override;

private:
	void MakeVertex(void);// 頂点の作成
	void SetVertex(void);// 頂点の変更
	void WorldTransform(LPDIRECT3DDEVICE9 Device);// ワールド座標変換

private:
	LPDIRECT3DVERTEXBUFFER9 m_VertexBuffer;
	D3DXMATRIX m_MatrixWorld;

	int m_FrameTime;
	float m_EndPosition;
};

#endif
