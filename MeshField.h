/*=============================================================================

メッシュフィールド[ MeshField.h ]
( Maybe-Later:std::stringのメモリ解放が出来ていない )
-------------------------------------------------------------------------------
■  Author
	Ohno Takuya

■  Created Date
	2017/06/13
=============================================================================*/

#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

class VertexShader;
class PixelShader;

/*-----------------------------------------------------------------------------
	Class
-----------------------------------------------------------------------------*/
class MeshField:public Object
{
public:
	enum IDXBACK_DRAW
	{	//	どっち周りで描画させるか

		IDXBACK_DRAW_CLOCKWISE = 0,	//	時計回り
		IDXBACK_DRAW_INV_CLOCKWISE	//	逆時計回り

	};

	MeshField(int Priolity = 1);

	static MeshField* Create(D3DXVECTOR3 Pos , UINT NumBlock_X , UINT NumBlock_Z , float SizeBlock_X , float SizeBlock_Z, char* tecturePath);	//	生成

	float GetHeight(D3DXVECTOR3 Position);	//	乗っている凹凸の高さ取得

	// Setter
	void SetRotation(const D3DXVECTOR3 rotation){ m_Rotation = rotation; }

private:
	void Initialize(void)override;
	void Uninitialize(void)override;
	void Update(void)override {}
	void Draw(void)override;

	void MakeVerTex(LPDIRECT3DDEVICE9 Device);//	頂点の作成
	void MakeIndex(LPDIRECT3DDEVICE9 Device);	//	インデックスバッファの作成
	void WorldTransform(LPDIRECT3DDEVICE9 Device);	//	ワールド座標変換
	void ConfigShader(LPDIRECT3DDEVICE9 device);// シェーダーの設定

	//	頂点数の計算
	void SetVertexCount(const UINT NumBlock_X, const UINT NumBlock_Y);
	//	インデックスバッファの計算
	void SetIndexBufferCount(const UINT NumBlock_X, const UINT NumBlock_Y);

private:
	static LPDIRECT3DTEXTURE9 m_Texture;	// テクスチャ
	LPDIRECT3DVERTEXBUFFER9	m_VertexBuffer;	// 頂点バッファ
	LPDIRECT3DINDEXBUFFER9	m_IndexBuffer;	//	インデックスバッファ

	D3DXVECTOR3	m_Rotation;		// 回転
	D3DXMATRIX m_MatrixWorld;
	D3DXVECTOR2 m_TexturePositon;	//	テクスチャ座標

	UINT m_NumBlock_X;	//	横の枚数
	UINT m_NumBlock_Y;	//	縦の枚数

	int m_NumVertex;		//	頂点数
	int m_NumIndexBuffer;	//	インデックスバッファ数

	float m_SizeBlock_X;		//	横の大きさ
	float m_SizeBlock_Z;		//	横の大きさ

	IDXBACK_DRAW m_IndexBackDraw;	//	どっち周りで描画させるか

	char* m_TexturePath;	//	テクスチャパス

	VertexShader* m_VertexShader;
	PixelShader* m_PixelShader;

	LPDIRECT3DVERTEXDECLARATION9 m_VertexDeclaration;
};

#endif