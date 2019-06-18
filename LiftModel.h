/*=============================================================================

リフトモデル[ LiftModel.h ]

-------------------------------------------------------------------------------
■  Author
Ohno Takuya

■  Create
2018/02/07
=============================================================================*/

#ifndef _LIFTMODEL_H_
#define _LIFTMODEL_H_

class VertexShader;
class PixelShader;

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class LiftModel:public Object
{
public:
	LiftModel(int Priolity = 3);

	static LiftModel* Create(void);

	void Initialize(void)override;
	void Uninitialize(void)override;
	void Update(void)override{}
	void Draw(void)override;

private:
	void WorldTransform(LPDIRECT3DDEVICE9 Device);// ワールド座標変換
	void ConfigShader(LPDIRECT3DDEVICE9 Device);// シェーダーの設定

private:
	D3DXMATRIX m_MatrixWorld;

	MODEL_PARAM m_ModelParam;	//	モデル構造体

	VertexShader* m_VertexShader;
	PixelShader* m_PixelShader;

	LPDIRECT3DVERTEXDECLARATION9 m_VertexDeclaration;
};

#endif
