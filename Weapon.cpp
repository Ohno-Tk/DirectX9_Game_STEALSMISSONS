/*=============================================================================

武器[ Weapon.cpp ]

-------------------------------------------------------------------------------
■  Author
Ohno Takuya

■  Create
2017/11/19
=============================================================================*/

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "FrameworkBase\RendererDirectX.h"
#include "FrameworkBase\Common.h"
#include "FrameworkBase\Game.h"
#include "FrameworkBase\ModelManagerDirectX.h"
#include "Object.h"
#include "Weapon.h"


Weapon::Weapon(int priolity):Object(priolity)
{
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	D3DXMatrixIdentity(&m_OwnerMatrix);
}

void Weapon::Draw(void)
{
	D3DMATERIAL9 materialDefault;

	LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();

	ModelManagerDirectX* manager = Game::GetInstance()->GetModelManager();
	m_ModelParam = manager->GetModelParam(m_ModelFilePath);

	WorldTransform(Device);

	// 現在デバイスに設定されているマテリアル情報の取得
	Device->GetMaterial(&materialDefault);

	// マテリアルへのポインタを取得
	m_ModelParam.Material = (D3DXMATERIAL*)m_ModelParam.BufferMaterial->GetBufferPointer();

	for (int CountMaterial = 0; CountMaterial < (int)m_ModelParam.NumMaterial; CountMaterial++)
	{
		//	アンビエント光の設定
		m_ModelParam.Material[CountMaterial].MatD3D.Ambient = m_ModelParam.Material[CountMaterial].MatD3D.Diffuse;

		// デバイスにマテリアルの設定
		Device->SetMaterial(&m_ModelParam.Material[CountMaterial].MatD3D);

		// テクスチャの設定
		Device->SetTexture(0, m_ModelParam.Texture[CountMaterial]);

		// 描画
		m_ModelParam.Mesh->DrawSubset(CountMaterial);
	}

	// マテリアルを元に戻す
	Device->SetMaterial(&materialDefault);
}

void Weapon::WorldTransform(LPDIRECT3DDEVICE9 Device)
{
	D3DXVECTOR3 position = Object::GetPosition();

	D3DXMATRIX matrixScale, matrixRotation, matrixPosition;

	D3DXMatrixIdentity(&m_MatrixWorld);

	D3DXMatrixScaling(&matrixScale,
		m_Scale.x,	//	X軸拡大
		m_Scale.y,	//	Y軸拡大
		m_Scale.z);	//	Z軸拡大

	D3DXMatrixRotationYawPitchRoll(&matrixRotation,
		D3DXToRadian(m_Rotation.y), //	Y軸回転
		D3DXToRadian(m_Rotation.x), //	X軸回転
		D3DXToRadian(m_Rotation.z)); //	Z軸回転

	D3DXMatrixTranslation(&matrixPosition,
		position.x,	//	X軸移動
		position.y,	//	Y軸移動
		position.z);	//	Z軸移動

	D3DXMatrixMultiply(&m_MatrixWorld, &m_MatrixWorld, &matrixScale);
	D3DXMatrixMultiply(&m_MatrixWorld, &m_MatrixWorld, &matrixRotation);
	D3DXMatrixMultiply(&m_MatrixWorld, &m_MatrixWorld, &matrixPosition);

	D3DXMatrixMultiply(&m_MatrixWorld, &m_MatrixWorld, &m_OwnerMatrix); // 親のマトリクスのかける

	//	デバイスにワールド変換行列を設定
	Device->SetTransform(D3DTS_WORLD, &m_MatrixWorld);
}