/*=============================================================================

視界( デバッグ用 )[ Vision.h ]

-------------------------------------------------------------------------------
■  Author
Ohno Takuya

■  Create
2017/11/28
=============================================================================*/

#ifndef _VISION_H_
#define _VISION_H_

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class Vision:public Object
{
public:
	Vision(int priolity = 5):Object(priolity), m_Active(false), m_VisionDistance(0.0f), m_Angle(0.0f), m_Rotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f)){}

	static Vision* Create(float VisionDistance, float Angle);

	void Initialize(void)override;
	void Uninitialize(void)override;
	void Update(void)override{}
	void Draw(void)override;

	// Setter
	void SetActive(const bool flag){ m_Active = flag; }
	void SetOwnerMatrix(D3DXMATRIX matrix){ m_OwnerMatrix = matrix; }

private:
	void MakeVerTex(void);						//	頂点の作成
	void WorldTransform(LPDIRECT3DDEVICE9 Device);	//	ワールド座標変換

private:
	LPDIRECT3DVERTEXBUFFER9 m_VertexBuffer;
	D3DXVECTOR3 m_Rotation;

	D3DXMATRIX m_OwnerMatrix; // 所有者のマトリクス

	bool m_Active;
	float m_VisionDistance;	//	視覚距離
	float m_Angle;			//	角度
};

#endif
