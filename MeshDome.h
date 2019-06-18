/*=============================================================================

メッシュ半球[ MeshDome.h ]
( Maybe-Later:std::stringのメモリ解放が出来ていない )
-------------------------------------------------------------------------------
■  Author
	Ohno Takuya

■  Create
	2017/05/12
=============================================================================*/

#ifndef _MESHDOME_H_
#define _MESHDOME_H_

/*-----------------------------------------------------------------------------
	Class
-----------------------------------------------------------------------------*/
class MeshDome : public Object
{
public:
	typedef enum
	{	//	どっち周りで描画させるか

		IDXBACK_DRAW_CLOCKWISE = 0,	//	時計回り
		IDXBACK_DRAW_INV_CLOCKWISE	//	逆時計回り

	}IDXBACK_DRAW;

	MeshDome(int Priolity = 1);		//	コンストラクタ

	static MeshDome* Create(D3DXVECTOR3 Pos, UINT NumBlock_X, UINT NumBlock_Y, float Radius, IDXBACK_DRAW IdxBack, char* TextureName);

	void Initialize(void)override;
	void Uninitialize(void)override;
	void Update(void)override{}
	void Draw(void)override;

	// Setter
	void SetRot(const D3DXVECTOR3 Rot) { m_Rotation = Rot; };		//	回転のセット

	//	テクスチャパスのセット
	void SetTexture(char* texturePath) { m_TexturePath = texturePath; }

private:
	void MakeVerTex(LPDIRECT3DDEVICE9 Device);	//	頂点の作成
	void MakeIndex(LPDIRECT3DDEVICE9 Device);	//	インデックスバッファの作成
	void WorldTransform(LPDIRECT3DDEVICE9 Device);		//	ワールド座標変換

private:
	static LPDIRECT3DTEXTURE9 m_Texture;	// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_VertexBuffer;		// 頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9	m_IndexBuffer;		//	インデックスバッファインタフェースへのポインタのアドレス

	D3DXVECTOR3	m_Rotation;			// 回転
	D3DXVECTOR3	m_Scale;			// 拡大率

	D3DXVECTOR2 m_TexturePositon;		//	テクスチャ座標

	D3DXMATRIX	m_MatixWorld;		// ワールドマトリックス

	UINT m_NumBlock_X;	//	横の枚数
	UINT m_NumBlock_Y;	//	縦の枚数

	int m_NumVertex;		//	頂点数
	int m_NumIndexBuffer;	//	インデックスバッファ数

	float m_Radius;	//	半径

	IDXBACK_DRAW m_IndexBackDraw;	//	どっち周りで描画させるか

	char* m_TexturePath;//	テクスチャパス

protected:
	//	縦横の枚数のセット
	void SetNumBlock(const UINT NumBlock_X, const UINT NumBlock_Y) { m_NumBlock_X = NumBlock_X; m_NumBlock_Y = NumBlock_Y; };

	//	頂点数の計算
	void SetVertexCount(const UINT NumBlock_X, const UINT NumBlock_Y) { m_NumVertex = (NumBlock_X + 1) * (NumBlock_Y + 1); };

	//	インデックスバッファの計算
	void SetIndexBufferCount(const UINT NumBlock_X, const UINT NumBlock_Y) { m_NumIndexBuffer = (2 + 2 * NumBlock_X) * NumBlock_Y + (NumBlock_Y - 1) * 2; };

	//	どっち周りで描画させるか
	void SetIndexBackDraw(const IDXBACK_DRAW IdxBackDraw) { m_IndexBackDraw = IdxBackDraw; };

};

#endif