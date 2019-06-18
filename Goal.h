/*=============================================================================

ゴール地点[ Goal.h ]

-------------------------------------------------------------------------------
■  Author
Ohno Takuya

■  Create
2017/11/15
=============================================================================*/

#ifndef _GOAL_H_
#define _GOAL_H_

class VertexShader;
class PixelShader;

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class Goal:public Object
{
public:
	Goal(int Priolity = 4):Object(Priolity),m_SphereRadius(2.0f),m_Rotation(D3DXVECTOR3(0.0f,0.0f,0.0f)){}

	static Goal* Create(D3DXVECTOR3 pos);

	void Initialize(void)override;
	void Uninitialize(void)override;
	void Update(void)override;
	void Draw(void)override;

private:
	void Collision(void); // 衝突判定
	void WorldTransform(void);// ワールド座標変換
	void ConfigShader(LPDIRECT3DDEVICE9 device);// シェーダーの設定

private:
	D3DXVECTOR3	m_Rotation;	//	回転
	float m_SphereRadius; // 球判定時のの半径

	D3DXMATRIX m_MatrixWorld;

	MODEL_PARAM m_ModelParam;	//	モデル構造体

	VertexShader* m_VertexShader;
	PixelShader* m_PixelShader;

	LPDIRECT3DVERTEXDECLARATION9 m_VertexDeclaration;
};

#endif
