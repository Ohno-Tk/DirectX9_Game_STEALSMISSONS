/*=============================================================================

ステンシルシャドウ[ StencilShadow.h ]
( Maybe-Later:std::stringのメモリ解放が出来ていない )
-------------------------------------------------------------------------------
■  Author
	Ohno Takuya

■  Create
	2017/11/09
=============================================================================*/

#ifndef _STENCILSHADOW_H_
#define _STENCILSHADOW_H_

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class StencilShadow:public Object
{
public:
	StencilShadow(int Priolity = 1):Object(Priolity),m_VertexBuffer(NULL){}

	static StencilShadow* Create(char* modelFileName);

private:
	void Initialize(void)override;
	void Uninitialize(void)override;
	void Update(void)override{}
	void Draw(void)override;

	void Polygon2DDraw(LPDIRECT3DDEVICE9 Device); // 全画面2Dポリゴン描画
	void ModelDraw(LPDIRECT3DDEVICE9 Device); // モデル描画
	void MakeVerTex(void); // 頂点の作成
	void WorldTransform(LPDIRECT3DDEVICE9 Device);	//	ワールド座標変換

private:
	LPDIRECT3DVERTEXBUFFER9 m_VertexBuffer;	//	頂点バッファ

	D3DXMATRIX m_MatrixWorld;

	char* m_ModelFilePath;	//	モデルのパス

	MODEL_PARAM m_ModelParam;	//	モデル構造体
};

#endif
