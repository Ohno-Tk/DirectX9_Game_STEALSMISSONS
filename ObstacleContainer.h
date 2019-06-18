/*=============================================================================

障害物( コンテナ )[ ObstacleContainer.h ]

-------------------------------------------------------------------------------
■  Author
Ohno Takuya

■  Create
2018/01/17
=============================================================================*/

#ifndef _OBSTACLECONTAINER_H_
#define _OBSTACLECONTAINER_H_

class VertexShader;
class PixelShader;

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class ObstacleContainer:public Object
{
public:
	ObstacleContainer(int Priolity = 2);

	static ObstacleContainer* Create(D3DXVECTOR3 pos);

	void Initialize(void)override;
	void Uninitialize(void)override;
	void Update(void)override;
	void Draw(void)override;

private:
	void Collision(void); // 衝突判定
	void WorldTransform(LPDIRECT3DDEVICE9 Device);// ワールド座標変換
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
