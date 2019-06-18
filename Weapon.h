/*=============================================================================

武器[ Weapon.h ]

-------------------------------------------------------------------------------
■  Author
Ohno Takuya

■  Create
2017/11/19
=============================================================================*/

#ifndef _WEAPON_H_
#define _WEAPON_H_

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class Weapon:public Object
{
public:
	Weapon(int priolity);

	void Initialize(void)override{}
	void Uninitialize(void)override{ Object::Release(); }
	void Update(void)override{}
	void Draw(void)override;

	// Setter
	void SetRotaiton(const D3DXVECTOR3 rotation) { m_Rotation = rotation; }
	void SetOwnerMatrix(D3DXMATRIX matrix){ m_OwnerMatrix = matrix; }
	void SetModelPath(char* modelFilePath){ m_ModelFilePath = modelFilePath; }

private:
	void WorldTransform(LPDIRECT3DDEVICE9 Device);	//	ワールド座標変換

private:
	D3DXVECTOR3	m_Rotation;	//	回転
	D3DXVECTOR3	m_Scale;	//	拡大率

	D3DXMATRIX m_MatrixWorld;
	D3DXMATRIX m_OwnerMatrix; // 所有者のマトリクス

	MODEL_PARAM m_ModelParam;
	char* m_ModelFilePath;
};

#endif
