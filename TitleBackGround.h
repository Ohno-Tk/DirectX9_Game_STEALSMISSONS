/*=============================================================================

タイトル背景[ TitleBackGround.h ]

-------------------------------------------------------------------------------
■  Author
Ohno Takuya

■  Create
2018/01/27
=============================================================================*/

#ifndef _TITLEBACKGROUND_H_
#define _TITLEBACKGROUND_H_

class VertexShader;
class PixelShader;

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class TitleBackGround:public Object
{
public:
	TitleBackGround(int priolity = 1);// コンストラクタ

	static TitleBackGround *Create(D3DXVECTOR3 position, D3DXVECTOR3 rotation);// 生成

	void Initialize(void)override;// 初期化
	void Uninitialize(void)override;// 終了
	void Update(void)override;// 更新
	void Draw(void)override;// 描画

	// Setter
	void SetNormal(D3DXVECTOR3 normal){ m_Normal = normal; }

private:
	void MakeVerTex(LPDIRECT3DDEVICE9 Device);	//	頂点の作成
	void ChangeVerTex(void);	//	頂点の変更
	void MakeIndex(LPDIRECT3DDEVICE9 Device);	//	インデックスバッファの作成
	void WorldTransform(LPDIRECT3DDEVICE9 Device);	//	ワールド座標変換
	void ConfigShader(LPDIRECT3DDEVICE9 device);// シェーダーの設定

private:
	static LPDIRECT3DTEXTURE9	m_Texture;		// テクスチャ
	LPDIRECT3DVERTEXBUFFER9		m_VertexBuffer;	// 頂点バッファ
	LPDIRECT3DINDEXBUFFER9		m_IndexBuffer;	//	インデックスバッファ

	D3DXVECTOR3 m_Normal;
	D3DXVECTOR3	m_Rotation;	// 回転
	D3DXMATRIX	m_MatrixWorld;

	int m_NumVertex;			//	頂点数
	int m_NumIndexBuffer;		//	インデックスバッファ数
	UINT m_NumBlock_X;		//	横の枚数
	UINT m_NumBlock_Y;		//	縦の枚数
	float m_SizeBlock_X;	//	横の大きさ
	float m_SizeBlock_Z;	//	横の大きさ

	float m_TexCoord;

	VertexShader* m_VertexShader;
	PixelShader* m_PixelShader;
	LPDIRECT3DVERTEXDECLARATION9 m_VertexDeclaration;
};

#endif
