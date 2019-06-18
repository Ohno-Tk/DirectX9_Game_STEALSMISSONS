/*=============================================================================

メッシュ球[ MeshSphere.h ]
( Maybe-Later:std::stringのメモリ解放が出来ていない )
-------------------------------------------------------------------------------
■  Author
	Ohno Takuya

■  Create
	2017/05/12
=============================================================================*/

#ifndef _MESHSPHERE_H_
#define _MESHSPHERE_H_

/*-----------------------------------------------------------------------------
	Class
-----------------------------------------------------------------------------*/
class MeshSphere : public Object
{
public:
	enum IDXBACK_DRAW
	{	//	どっち周りで描画させるか

		IDXBACK_DRAW_CLOCKWISE = 0,	//	時計回り
		IDXBACK_DRAW_INV_CLOCKWISE	//	逆時計回り

	};

	MeshSphere(int Priolity = 5);

	static MeshSphere* Create(D3DXVECTOR3 Pos, UINT NumBlock_X, UINT NumBlock_Y, float Radius, IDXBACK_DRAW IdxBack, char* TexturePath,D3DXCOLOR color = D3DXCOLOR(1.0f,1.0f,1.0f,0.5f));

	void Initialize(void)override;
	void Uninitialize(void)override;
	void Update(void)override {}
	void Draw(void)override;

	// Setter
	void SetColor(const D3DXCOLOR color) { m_Color = color; }//	色
	void SetRotation(const D3DXVECTOR3 rotation){ m_Rotation = rotation; }// 回転
	void SetTexturePath(char* texturePath){ m_TexturePath = texturePath; }// テクスチャのパス

	// Getter	
	D3DXVECTOR3 GetRotation(void) {return m_Rotation;}//	回転

private:
	void MakeVerTex(LPDIRECT3DDEVICE9 Device);		//	頂点の作成
	void MakeIndex(LPDIRECT3DDEVICE9 Device);		//	インデックスバッファの作成
	void WorldTransform(LPDIRECT3DDEVICE9 Device);	//	ワールド座標変換
	void SetVerTex(void);							//	頂点の変更

private:
	static LPDIRECT3DTEXTURE9 m_Texture;	// テクスチャ
	LPDIRECT3DVERTEXBUFFER9	m_VertexBuffer;	// 頂点バッファ
	LPDIRECT3DINDEXBUFFER9	m_IndexBuffer;	//	インデックスバッファ

	D3DXVECTOR3	m_Rotation;		// 回転

	D3DXVECTOR2 m_TexturePositon;		//	テクスチャ座標

	D3DXCOLOR m_Color;			//	色

	D3DXMATRIX	m_MatrixWorld;		// ワールドマトリックス

	UINT m_NumBlock_X;	//	横の枚数
	UINT m_NumBlock_Y;	//	縦の枚数

	int m_NumVertex;		//	頂点数
	int m_NumIndexBuffer;	//	インデックスバッファ数

	float m_Radius;		//	半径

	IDXBACK_DRAW m_IndexBackDraw;	//	どっち周りで描画させるか

	char* m_TexturePath;//	テクスチャパス

protected:
	// Setter
	void SetNumBlock(const UINT numBlockX, const UINT numBlockY);//	枚数
	void SetVertexCount(const UINT NumBlock_X, const UINT NumBlock_Y);// 頂点数の計算
	void SetIndexBufferCount(const UINT NumBlock_X, const UINT NumBlock_Y);// インデックスバッファの計算
	void SetIndexBackDraw(const IDXBACK_DRAW indexBackDraw){ m_IndexBackDraw = indexBackDraw; }//	どっち周りで描画させるか
	void SetRadius(const float radius) { m_Radius = radius; }//	半径

};

#endif