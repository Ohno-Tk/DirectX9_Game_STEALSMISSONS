/*=============================================================================

メッシュ壁[ MeshWall.h ]
( Maybe-Later:std::stringのメモリ解放が出来ていない )
-------------------------------------------------------------------------------
■  Author
	Ohno Takuya

■  Create
	2017/07/06
=============================================================================*/

#ifndef _MESHWALL_H_
#define _MESHWALL_H_

class VertexShader;
class PixelShader;

/*-----------------------------------------------------------------------------
	Class
-----------------------------------------------------------------------------*/
class MeshWall : public Object
{
public:
	MeshWall(int Priolity = 1);

	static MeshWall *Create(D3DXVECTOR3 Pos, float Rot, UINT NumBlock_X, UINT NumBlock_Y, float SizeBlock_X, float SizeBlock_Y);

	D3DXVECTOR3 CollisionMeshWall(D3DXVECTOR3 Position, D3DXVECTOR3 FrontVector);	//	壁ずり

	void Initialize(void)override;
	void Uninitialize(void)override;
	void Update(void)override;
	void Draw(void)override;

	// Setter
	void SetNormal(D3DXVECTOR3 normal){ m_Normal = normal; }

private:
	void MakeVerTex(LPDIRECT3DDEVICE9 Device);	//	頂点の作成
	void SetVerTex(void);// 頂点の変更
	void MakeIndex(LPDIRECT3DDEVICE9 Device);	//	インデックスバッファの作成
	void WorldTransform(LPDIRECT3DDEVICE9 Device);	//	ワールド座標変換
	void ConfigShader(LPDIRECT3DDEVICE9 device);// シェーダーの設定

	//	頂点数の計算
	void SetVertexCount(const UINT NumBlock_X, const UINT NumBlock_Y);
	//	インデックスバッファの計算
	void SetIndexBufferCount(const UINT NumBlock_X, const UINT NumBlock_Y);

private:
	static LPDIRECT3DTEXTURE9	m_Texture;		// テクスチャ
	LPDIRECT3DVERTEXBUFFER9		m_VertexBuffer;	// 頂点バッファ
	LPDIRECT3DINDEXBUFFER9		m_IndexBuffer;	//	インデックスバッファ

	D3DXVECTOR3 m_Normal;
	D3DXVECTOR3	m_Rotation;	// 回転

	D3DXCOLOR m_Color;		//	色

	D3DXMATRIX	m_MatrixWorld;	// ワールドマトリックス

	UINT m_NumBlock_X;		//	横の枚数
	UINT m_NumBlock_Y;		//	縦の枚数

	int m_NumVertex;			//	頂点数
	int m_NumIndexBuffer;		//	インデックスバッファ数

	float m_SizeBlock_X;	//	横の大きさ
	float m_SizeBlock_Z;	//	横の大きさ

	char* m_TexturePath;	//	テクスチャパス

	VertexShader* m_VertexShader;
	PixelShader* m_PixelShader;

	LPDIRECT3DVERTEXDECLARATION9 m_VertexDeclaration;

};

#endif