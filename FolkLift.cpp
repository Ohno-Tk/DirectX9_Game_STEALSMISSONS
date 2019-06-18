/*=============================================================================

オブジェクト( フォークリフト )[ FolkLift.cpp ]

-------------------------------------------------------------------------------
■  Author
Ohno Takuya

■  Create
2018/02/04
=============================================================================*/

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "FrameworkBase\RendererDirectX.h"
#include "FrameworkBase\Common.h"
#include "FrameworkBase\ModelManagerDirectX.h"
#include "FrameworkBase\Collision.h"
#include "FrameworkBase\Game.h"
#include "FrameworkBase\CameraDirectX.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "GameScene.h"
#include "Object.h"
#include "Player.h"
#include "Enemy.h"
#include "ObstaclePillar.h"
#include "FolkLift.h"

/*-----------------------------------------------------------------------------
Macro
-----------------------------------------------------------------------------*/
#define OBJECT_MODEL_PATH (MODEL_PATH"FolkLift.x")
#define MODEL_VERTEXSHADER_PATH (SHADER_PATH"Obstacle_Vertex.hlsl")
#define MODEL_PIXELSHADER_PATH (SHADER_PATH"Obstacle_Pixel.hlsl")
#define SCALE (1.0f)// 拡大値


FolkLift* FolkLift::Create(void)
{
	auto object = new FolkLift;
	
	object->Initialize();

	return object;
}

void FolkLift::Initialize(void)
{
	SetObjeType(OBJECT_TYPE_OBSTACLE);

	SetPosition(D3DXVECTOR3(120.0f,0.0f,125.0f));

	m_ModelParam = Game::GetInstance()->GetModelManager()->GetModelParam(OBJECT_MODEL_PATH);


	m_VertexShader = new VertexShader;
	m_VertexShader->Initialize(MODEL_VERTEXSHADER_PATH);

	m_PixelShader = new PixelShader;
	m_PixelShader->Initialize(MODEL_PIXELSHADER_PATH);
}

void FolkLift::Uninitialize(void)
{
	SAFE_UNINIT(m_VertexShader);
	SAFE_UNINIT(m_PixelShader);

	Object::Release();
}

void FolkLift::Update(void)
{
	Collision(); // 衝突判定
}

void FolkLift::Draw(void)
{
	D3DMATERIAL9 materialDefault;

	LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();

	WorldTransform(Device);// ワールド座標変換

	ConfigShader(Device);// シェーダーの設定

	D3DVERTEXELEMENT9 elements[] = {
	{0 ,0 ,D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
	{0 ,12 ,D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
	{0 ,24 ,D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
	D3DDECL_END()
	};
	Device->CreateVertexDeclaration(elements,&m_VertexDeclaration);

	Device->SetVertexShader(m_VertexShader->GetVertexShader());
	Device->SetPixelShader(m_PixelShader->GetPixelShader());

	// 現在デバイスに設定されているマテリアル情報の取得
	Device->GetMaterial(&materialDefault);

	// マテリアルへのポインタを取得
	m_ModelParam.Material = (D3DXMATERIAL*)m_ModelParam.BufferMaterial->GetBufferPointer();

	UINT samplerIndex0 = m_PixelShader->GetPixelShaderConstantTable()->GetSamplerIndex("sampler0");

	for (int CountMaterial = 0; CountMaterial < (int)m_ModelParam.NumMaterial; CountMaterial++)
	{
		m_PixelShader->GetPixelShaderConstantTable()->SetValue(RendererDirectX::GetDevice(), "Diffuse", &m_ModelParam.Material[CountMaterial].MatD3D.Diffuse, sizeof(m_ModelParam.Material[CountMaterial].MatD3D.Diffuse));

		// デバイスにマテリアルの設定
		Device->SetMaterial(&m_ModelParam.Material[CountMaterial].MatD3D);

		// テクスチャの設定
		Device->SetTexture(samplerIndex0, m_ModelParam.Texture[CountMaterial]);

		// 描画
		m_ModelParam.Mesh->DrawSubset(CountMaterial);
	}

	// マテリアルを元に戻す
	Device->SetMaterial(&materialDefault);
}

/*-----------------------------------------------------------------------------
Overview:   衝突判定
-----------------------------------------------------------------------------*/
void FolkLift::Collision(void)
{
	D3DXVECTOR3 position = Object::GetPosition();
	Player* player = GameScene::GetPlayer();

	Collision_Sphere CollisionSphere(position, m_SphereRadius);

	if (CollisionSphere.Judge(player->GetPosition(), player->GetSphereRadius()))
	{ // 衝突判定
		player->SetOldPosition();
	}

	for (int CntPriolity = 0; CntPriolity < PRIOLITY_MAX; CntPriolity++)
	{

		Object *object = Object::GetList(CntPriolity);

		while (object != NULL)
		{

			if (object->GetObjeType() == Object::OBJECT_TYPE_ENEMY)
			{
				Enemy *enemy = (Enemy*)object;
				if(CollisionSphere.Judge(enemy->GetPosition(), 9.0f))
				{
					enemy->SetOldPosition();
				}
			}
			object = object->GetNext();
		}
	}

}

void FolkLift::WorldTransform(LPDIRECT3DDEVICE9 Device)
{
	D3DXVECTOR3 Position = Object::GetPosition();


	D3DXMATRIX matrixScale, matrixRotation, matrixPosition;

	D3DXMatrixIdentity(&m_MatrixWorld);	//	行列を単位行列にする

	D3DXMatrixScaling(&matrixScale,
		SCALE,
		SCALE,
		SCALE);

	D3DXMatrixRotationYawPitchRoll(&matrixRotation,
		D3DXToRadian(m_Rotation.y),
		D3DXToRadian(m_Rotation.x),
		D3DXToRadian(m_Rotation.z));

	D3DXMatrixTranslation(&matrixPosition,
		Position.x,
		Position.y,
		Position.z);

	D3DXMatrixMultiply(&m_MatrixWorld, &m_MatrixWorld, &matrixScale);
	D3DXMatrixMultiply(&m_MatrixWorld, &m_MatrixWorld, &matrixRotation);
	D3DXMatrixMultiply(&m_MatrixWorld, &m_MatrixWorld, &matrixPosition);
}

void FolkLift::ConfigShader(LPDIRECT3DDEVICE9 device)
{
	LPD3DXCONSTANTTABLE vetexShaderConstantTable = m_VertexShader->GetVertexShaderConstantTable();
	LPD3DXCONSTANTTABLE pixelShaderConstantTable = m_PixelShader->GetPixelShaderConstantTable();

	vetexShaderConstantTable->SetMatrix(device, "mtxW", &m_MatrixWorld);

	D3DXMATRIX mtxWVP = m_MatrixWorld * Game::GetInstance()->GetCamera()->GetViewProjectionMatrix();
	vetexShaderConstantTable->SetMatrix(device, "mtxWVP", &mtxWVP);

	D3DXMATRIX mtxInv;
	D3DXMatrixInverse(&mtxInv, NULL, &m_MatrixWorld);
	D3DXMatrixTranspose(&mtxInv, &mtxInv);
	vetexShaderConstantTable->SetMatrix(device, "mtxWIT", &mtxInv);

	D3DXVECTOR3 lightDirW(0.0f,-1.0f, -1.0f);
	pixelShaderConstantTable->SetValue(device, "lightDirW", &lightDirW, sizeof(lightDirW));
}