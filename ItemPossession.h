/*=============================================================================

現在所持数アイテム[ NowPossessionItem.h ]

-------------------------------------------------------------------------------
■  Author
Ohno Takuya

■  Create
2018/01/24
=============================================================================*/

#ifndef _NOWPOSSESSIONITEM_H_
#define _NOWPOSSESSIONITEM_H_

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class ItemPossession:public Object
{
public:
	ItemPossession(int priolity = 4);

	static ItemPossession* Create(D3DXVECTOR3 position, unsigned int digit);// 生成

	void Initialize(void);
	void Uninitialize(void);
	void Update(void);
	void Draw(void);

	void SetPossession(int possession);// 所持数の設定

private:
	void MakeVertex(void);// 頂点の作成
	void SetVertex(void);// 頂点の変更

private:
	LPDIRECT3DVERTEXBUFFER9 m_VertexBuffer;
	D3DXVECTOR2 m_Size;
	unsigned int m_Digit;// 桁数
	unsigned int m_Possession;
	float m_TexCoord;// テクスチャ座標
};

#endif
