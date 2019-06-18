/*=============================================================================

メッシュエフェクト[ MeshEffect.h ]

-------------------------------------------------------------------------------
■  Author
Ohno Takuya

■  Create
2017/11/13
=============================================================================*/

#ifndef _MESHEFFECT_H_
#define _MESHEFFECT_H_

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class MeshEffect:public Object
{
public:
	MeshEffect(int Priolity = 4);

	static MeshEffect* Create(UINT numBlock_X);

	void Initialize(void)override;
	void Uninitialize(void)override;
	void Update(void)override;
	void Draw(void)override;

	// Setter
	void SetVertexPosition(const D3DXVECTOR3 topPosition, const D3DXVECTOR3 bottomPosition){ m_TopPosition = topPosition; m_ButtomPosition = bottomPosition; }

private:
	void MakeVerTex(LPDIRECT3DDEVICE9 Device);	// 頂点の作成
	void SetUpVerTex(void);	                    // 頂点の設定
	void MakeIndex(LPDIRECT3DDEVICE9 Device);   // インデックスバッファの作成
	void SetVertexCount(const UINT NumBlock_X, const UINT NumBlock_Y); // 頂点数の計算
	void SetIndexBufferCount(const UINT NumBlock_X, const UINT NumBlock_Y);   // インデックスバッファの計算
	void WorldTransform(LPDIRECT3DDEVICE9 Device);                     // ワールド座標変換

private:
	LPDIRECT3DVERTEXBUFFER9 m_VertexBuffer; //	頂点バッファ
	LPDIRECT3DINDEXBUFFER9	m_IndexBuffer; //	インデックスバッファ

	D3DXVECTOR3 m_TopPosition;
	D3DXVECTOR3 m_ButtomPosition;

	D3DXVECTOR2 m_TexturePositon;	//	テクスチャ座標

	UINT m_NumBlock_X;		//	横の枚数
	UINT m_NumBlock_Y;		//	縦の枚数

	int m_NumVertex;		//	頂点数
	int m_NumIndexBuffer;	//	インデックスバッファ数

	std::vector<D3DXVECTOR3> m_VertexPosition;
};

#endif
