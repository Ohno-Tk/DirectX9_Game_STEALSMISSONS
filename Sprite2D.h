/*=============================================================================

2D描画[ Sprite2D.h ]
( Maybe-Later:std::stringのメモリ解放が出来ていない )
-------------------------------------------------------------------------------
■  Author
Ohno Takuya

■  Create
2017/11/17
=============================================================================*/

#ifndef _SPRITE2D_H_
#define _SPRITE2D_H_

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class Sprite2D:public Object
{
public:
	Sprite2D(int Priolity);

	static Sprite2D* Create(D3DXVECTOR3 position, D3DXVECTOR2 size, char* texturePath, D3DXVECTOR4 color = D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f), int priolity = 3);

	void Initialize(void)override;
	void Uninitialize(void)override;
	void Update(void)override;
	void Draw(void)override;

	// Setter
	void SetSize(const D3DXVECTOR2 size){ m_Size = size; }
	void SetColor(const D3DXCOLOR color){ m_Color = color; }
	void SetAlphaColor(const float value){ m_Color.a = value; }

	// Getter
	const LPDIRECT3DVERTEXBUFFER9 GetVertexBuffer(void)const{ return m_VertexBuffer; }
	D3DXVECTOR2 GetSize(void){ return m_Size; }
	D3DXCOLOR GetColor(void){ return m_Color; }

private:
	void MakeVertex(LPDIRECT3DDEVICE9 Device);// 頂点の作成
	virtual void SetVertex(void); // 頂点の変更

private:
	LPDIRECT3DVERTEXBUFFER9 m_VertexBuffer; // 頂点バッファ

	D3DXVECTOR2 m_Size;	//	大きさ
	D3DXCOLOR m_Color;	//	色

	char* m_TexturePath; // テクスチャのパス

protected:
	void SetTexturePath(char* texturePath){ m_TexturePath = texturePath; }
};

#endif
