/*=============================================================================

Xモデル描画[ SpriteModeLX.cpp ]

-------------------------------------------------------------------------------
■  Author
	Ohno Takuya

■  Create
	2017/08/25
=============================================================================*/

/*-----------------------------------------------------------------------------
	Header
-----------------------------------------------------------------------------*/
#include "FrameworkBase\Common.h"
#include "FrameworkBase\RendererDirectX.h"
#include "FrameworkBase\Game.h"
#include "FrameworkBase\ModelManagerDirectX.h"
#include "FrameworkBase\Game.h"
#include "FrameworkBase\CameraDirectX.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Object.h"
#include "SpriteModeX.h"

/*-----------------------------------------------------------------------------
Macro
-----------------------------------------------------------------------------*/
#define MODEL_VERTEXSHADER_PATH (SHADER_PATH"Obstacle_Vertex.hlsl")
#define MODEL_PIXELSHADER_PATH (SHADER_PATH"Obstacle_Pixel.hlsl")

/*-----------------------------------------------------------------------------
Namespace
-----------------------------------------------------------------------------*/
using namespace std;


SpriteModelX::SpriteModelX(int Priolity) :Object(Priolity)
{
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	回転
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);	//	拡大率
}

/*-----------------------------------------------------------------------------
Function:   SpriteModelX* SpriteModelX::Create(D3DXVECTOR3 position, char* modelFilePath, int priolity)
Parameter:  D3DXVECTOR3 position
              座標
            D3DXVECTOR2 size
			  大きさ
            string modelFilePath
			  モデルのパス
			int priolity
			  優先度
Overview:   生成
-----------------------------------------------------------------------------*/
SpriteModelX* SpriteModelX::Create(D3DXVECTOR3 position, D3DXVECTOR3 rotation, char* modelFilePath, int priolity)
{
	auto object = new SpriteModelX(priolity);

	object->SetPosition(position);
	object->m_Rotation = rotation;
	object->m_ModelFilePath = modelFilePath;

	object->Initialize();

	return object;
}

void SpriteModelX::Initialize(void)
{
	m_VertexShader = new VertexShader;
	m_VertexShader->Initialize(MODEL_VERTEXSHADER_PATH);

	m_PixelShader = new PixelShader;
	m_PixelShader->Initialize(MODEL_PIXELSHADER_PATH);
}

void SpriteModelX::Uninitialize(void)
{
	Object::Release();
}

void SpriteModelX::Draw(void)
{
	D3DMATERIAL9 materialDefault;

	LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();

	ModelManagerDirectX* manager = Game::GetInstance()->GetModelManager();
	m_ModelParam = manager->GetModelParam(m_ModelFilePath);

	WorldTransform(Device);
	ConfigShader(Device);


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
		//	アンビエント光の設定
//		m_ModelParam.Material[CountMaterial].MatD3D.Ambient = m_ModelParam.Material[CountMaterial].MatD3D.Diffuse;

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
Function:   void SpriteModelX::WorldTransform(LPDIRECT3DDEVICE9 Device)
Parameter:  LPDIRECT3DDEVICE9 Device
			  デバイス
Overview:   ワールド座標変換
-----------------------------------------------------------------------------*/
void SpriteModelX::WorldTransform(LPDIRECT3DDEVICE9 Device)
{
	D3DXVECTOR3 Position = Object::GetPosition();


	D3DXMATRIX matrixScale, matrixRotation, matrixPosition;

	D3DXMatrixIdentity(&m_MatrixWorld);	//	行列を単位行列にする

	//	拡大行列を作る
	D3DXMatrixScaling(&matrixScale,	//拡大行列が作られる
		m_Scale.x,	//	X軸拡大
		m_Scale.y,	//	Y軸拡大
		m_Scale.z);	//	Z軸拡大

	//	回転行列を作る
	D3DXMatrixRotationYawPitchRoll(&matrixRotation,	//	回転行列が作られる
		D3DXToRadian(m_Rotation.y), //	Y軸回転
		D3DXToRadian(m_Rotation.x), //	X軸回転
		D3DXToRadian(m_Rotation.z)); //	Z軸回転

	//	平行移動行列を作る
	D3DXMatrixTranslation(&matrixPosition,
		Position.x,	//	X軸移動
		Position.y,	//	Y軸移動
		Position.z);	//	Z軸移動


	//	各行列をかける
	D3DXMatrixMultiply(&m_MatrixWorld, &m_MatrixWorld, &matrixScale);
	D3DXMatrixMultiply(&m_MatrixWorld, &m_MatrixWorld, &matrixRotation);
	D3DXMatrixMultiply(&m_MatrixWorld, &m_MatrixWorld, &matrixPosition);
}

void SpriteModelX::ConfigShader(LPDIRECT3DDEVICE9 device)
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

	D3DXVECTOR3 lightDirW(0.0f,-1.0f, 0.0f);
	pixelShaderConstantTable->SetValue(device, "lightDirW", &lightDirW, sizeof(lightDirW));
}