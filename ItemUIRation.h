/*=============================================================================

アイテム表示UI( レーション )[ ItemUIRation.h ]

-------------------------------------------------------------------------------
■  Author
Ohno Takuya

■  Create
2018/01/24
=============================================================================*/

#ifndef _ITEMUIRATION_H_
#define _ITEMUIRATION_H_

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "ItemUI.h"

class ItemPossession;

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class ItemUIRation:public ItemUI
{
public:
	ItemUIRation(int priolity = 4);

	static ItemUIRation* Create(D3DXVECTOR3 position);// 生成

	void Initialize(void)override;
	void Uninitialize(void)override;
	void Update(void)override;
	void Draw(void)override;

	void PlusNowPossession(const unsigned int plusValue);// 現在所持数追加
	void SubNowPossession(const unsigned int subValue);	 // 現在所持数減算

	void Use(void)override;// 使用

private:
	void MakeVertex(void);// 頂点の作成
	void SetVertex(void);// 頂点の変更

private:
	LPDIRECT3DVERTEXBUFFER9 m_VertexBuffer;
	D3DXVECTOR2 m_Size;

	unsigned int m_NowPossession;// 現在所持数
	unsigned int m_MaxPossession;// 最大所持数

	ItemPossession* m_NowPossessionUI;
	ItemPossession* m_MaxPossessionUI;
};

#endif
