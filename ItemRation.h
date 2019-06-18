/*=============================================================================

アイテム( レーション )[ ItemRation.h ]

-------------------------------------------------------------------------------
■  Author
Ohno Takuya

■  Create
2018/01/22
=============================================================================*/

#ifndef _ITEMRATION_H_
#define _ITEMRATION_H_

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "Item.h"

class VertexShader;
class PixelShader;

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class ItemRation:public Item
{
public:
	ItemRation(int priolity = 3);

	static ItemRation* Create(D3DXVECTOR3 position);// 生成

	void Initialize(void)override;
	void Uninitialize(void)override;
	void Update(void)override;
	void Draw(void)override;

private:
	bool Collision(void)override;// 当たり判定
	void WorldTransform(LPDIRECT3DDEVICE9 Device);// ワールド座標変換
	void ConfigShader(LPDIRECT3DDEVICE9 device);// シェーダーの設定

private:
	D3DXVECTOR3	m_Rotation;// 回転
	D3DXMATRIX m_MatrixWorld;

	MODEL_PARAM m_ModelParam;

	VertexShader* m_VertexShader;
	PixelShader* m_PixelShader;

	LPDIRECT3DVERTEXDECLARATION9 m_VertexDeclaration;
};

#endif
