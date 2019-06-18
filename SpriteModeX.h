/*=============================================================================

Xモデル描画[ SpriteModeX.h ]
( Maybe-Later:std::stringのメモリ解放が出来ていない )
-------------------------------------------------------------------------------
■  Author
	Ohno Takuya

■  Create
	2017/08/25
=============================================================================*/

#ifndef _SPRITEMODELX_H_
#define _SPRITEMODELX_H_

class VertexShader;
class PixelShader;

/*-----------------------------------------------------------------------------
	Class
-----------------------------------------------------------------------------*/
class SpriteModelX:public Object
{
public:
	SpriteModelX(int Priolity);

	static SpriteModelX* Create(D3DXVECTOR3 position, D3DXVECTOR3 rotation, char* modelFilePath, int priolity = 3);

	void Initialize(void)override;
	void Uninitialize(void)override;
	void Update(void)override {}
	void Draw(void)override;

	//	Setter
	void SetRotation(const D3DXVECTOR3 Rot) { m_Rotation = Rot; }
	void SetScale(const D3DXVECTOR3 Scl) { m_Scale = Scl; }
	void SetModelFileName(char* modelFilePath) { m_ModelFilePath = modelFilePath; }

	//	Getter
	D3DXVECTOR3 GetRotation(void) { return m_Rotation; }
	D3DXVECTOR3 GetScale(void) { return m_Scale; }
	D3DXMATRIX GetMatrix(void){ return m_MatrixWorld; }

private:
	void WorldTransform(LPDIRECT3DDEVICE9 Device);	//	ワールド座標変換
	void ConfigShader(LPDIRECT3DDEVICE9 device);// シェーダーの設定

private:
	D3DXVECTOR3	m_Rotation;	//	回転
	D3DXVECTOR3	m_Scale;	//	拡大率

	D3DXMATRIX m_MatrixWorld;

	MODEL_PARAM m_ModelParam;	//	モデル構造体
	char* m_ModelFilePath;	//	モデルのパス

	VertexShader* m_VertexShader;
	PixelShader* m_PixelShader;

	LPDIRECT3DVERTEXDECLARATION9 m_VertexDeclaration;
};

#endif