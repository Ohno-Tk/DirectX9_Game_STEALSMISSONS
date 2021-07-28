/*=============================================================================

��Q��( �R���e�i )[ ObstacleContainer.cpp ]

-------------------------------------------------------------------------------
��  Create
2018/01/17
=============================================================================*/

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "FrameworkBase\Common.h"
#include "FrameworkBase\RendererDirectX.h"
#include "FrameworkBase\ModelManagerDirectX.h"
#include "FrameworkBase\Collision.h"
#include "FrameworkBase\Game.h"
#include "FrameworkBase\CameraDirectX.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "GameScene.h"
#include "Object.h"
#include "SpriteModeX.h"
#include "Player.h"
#include "Enemy.h"
#include "ObstacleContainer.h"

/*-----------------------------------------------------------------------------
Macro
-----------------------------------------------------------------------------*/
#define OBJECT_MODEL_PATH  (MODEL_PATH"Container.x")
#define MODEL_VERTEXSHADER_PATH (SHADER_PATH"ObstacleContainer_Vertex.hlsl")
#define MODEL_PIXELSHADER_PATH (SHADER_PATH"ObstacleContainer_Pixel.hlsl")
#define SCALE (1.0f)// �g��l


ObstacleContainer::ObstacleContainer(int Priolity)
	:Object(Priolity)
	,m_SphereRadius(5.0f)
	,m_Rotation(D3DXVECTOR3(0.0f,0.0f,0.0f)){}

ObstacleContainer* ObstacleContainer::Create(D3DXVECTOR3 pos)
{
	auto object = new ObstacleContainer;

	object->SetPosition(pos);
	object->Initialize();

	return object;
}

void ObstacleContainer::Initialize(void)
{
	SetObjeType(OBJECT_TYPE_OBSTACLE);
	
	m_ModelParam = Game::GetInstance()->GetModelManager()->GetModelParam(OBJECT_MODEL_PATH);


	m_VertexShader = new VertexShader;
	m_VertexShader->Initialize(MODEL_VERTEXSHADER_PATH);

	m_PixelShader = new PixelShader;
	m_PixelShader->Initialize(MODEL_PIXELSHADER_PATH);
}

void ObstacleContainer::Uninitialize(void)
{
	SAFE_UNINIT(m_VertexShader);
	SAFE_UNINIT(m_PixelShader);
	Object::Release();
}

void ObstacleContainer::Update(void)
{
	Collision(); // �Փ˔���
}

void ObstacleContainer::Draw(void)
{
	D3DMATERIAL9 materialDefault;

	LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();


	D3DVERTEXELEMENT9 elements[] = {
	{0 ,0 ,D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
	{0 ,12 ,D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
	{0 ,24 ,D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
	D3DDECL_END()
	};
	RendererDirectX::GetDevice()->CreateVertexDeclaration(elements,&m_VertexDeclaration);

	WorldTransform(Device);// ���[���h���W�ϊ�

	ConfigShader(Device);// �V�F�[�_�[�̐ݒ�

	Device->SetVertexShader(m_VertexShader->GetVertexShader());
	Device->SetPixelShader(m_PixelShader->GetPixelShader());

	// ���݃f�o�C�X�ɐݒ肳��Ă���}�e���A�����̎擾
	Device->GetMaterial(&materialDefault);

	// �}�e���A���ւ̃|�C���^���擾
	m_ModelParam.Material = (D3DXMATERIAL*)m_ModelParam.BufferMaterial->GetBufferPointer();

	for (int CountMaterial = 0; CountMaterial < (int)m_ModelParam.NumMaterial; CountMaterial++)
	{
		m_PixelShader->GetPixelShaderConstantTable()->SetValue(RendererDirectX::GetDevice(), "Diffuse", &m_ModelParam.Material[CountMaterial].MatD3D.Diffuse, sizeof(m_ModelParam.Material[CountMaterial].MatD3D.Diffuse));

		// �f�o�C�X�Ƀ}�e���A���̐ݒ�
		Device->SetMaterial(&m_ModelParam.Material[CountMaterial].MatD3D);


		UINT samplerIndex0 = m_PixelShader->GetPixelShaderConstantTable()->GetSamplerIndex("sampler0");
		// �e�N�X�`���̐ݒ�
		Device->SetTexture(samplerIndex0, m_ModelParam.Texture[CountMaterial]);

		// �`��
		m_ModelParam.Mesh->DrawSubset(CountMaterial);
	}

	// �}�e���A�������ɖ߂�
	Device->SetMaterial(&materialDefault);
}

/*-----------------------------------------------------------------------------
���[���h���W�ϊ�
-----------------------------------------------------------------------------*/
void ObstacleContainer::WorldTransform(LPDIRECT3DDEVICE9 Device)
{
	D3DXVECTOR3 Position = Object::GetPosition();


	D3DXMATRIX matrixScale, matrixRotation, matrixPosition;

	D3DXMatrixIdentity(&m_MatrixWorld);	//	�s���P�ʍs��ɂ���

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


/*-----------------------------------------------------------------------------
Function:   void ObstacleContainer::Collision(void)
Parameter:  
Overview:   �Փ˔���
-----------------------------------------------------------------------------*/
void ObstacleContainer::Collision(void)
{
	D3DXVECTOR3 position = Object::GetPosition();
	Player* player = GameScene::GetPlayer();

	Collision_Sphere CollisionSphere(position, m_SphereRadius);

	if (CollisionSphere.Judge(player->GetPosition(), player->GetSphereRadius()))
	{ // �Փ˔���
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

void ObstacleContainer::ConfigShader(LPDIRECT3DDEVICE9 device)
{
	LPD3DXCONSTANTTABLE vetexShaderConstantTable = m_VertexShader->GetVertexShaderConstantTable();
	LPD3DXCONSTANTTABLE pixelShaderConstantTable = m_PixelShader->GetPixelShaderConstantTable();

	vetexShaderConstantTable->SetMatrix(device, "mtxW", &m_MatrixWorld);

	D3DXMATRIX mtxWVP = m_MatrixWorld * Game::GetInstance()->GetCamera()->GetViewMatrix() * Game::GetInstance()->GetCamera()->GetProjectionMatrix();
	vetexShaderConstantTable->SetMatrix(device, "mtxWVP", &mtxWVP);

	D3DXMATRIX mtxInv;
	D3DXMatrixInverse(&mtxInv, NULL, &m_MatrixWorld);
	D3DXMatrixTranspose(&mtxInv, &mtxInv);
	vetexShaderConstantTable->SetMatrix(device, "mtxWIT", &mtxInv);


	D3DXVECTOR3 Pos[9] = {D3DXVECTOR3(-90.0f, 30.0f,   95.0f), D3DXVECTOR3(21.0f, 30.0f,   95.0f), D3DXVECTOR3(125.0f, 30.0f,   95.0f),
						  D3DXVECTOR3(-90.0f, 30.0f,  -15.0f), D3DXVECTOR3(21.0f, 30.0f,  -15.0f), D3DXVECTOR3(125.0f, 30.0f,  -15.0f),
						  D3DXVECTOR3(-90.0f, 30.0f, -120.0f), D3DXVECTOR3(21.0f, 30.0f, -115.0f), D3DXVECTOR3(125.0f, 30.0f, -115.0f)};
	pixelShaderConstantTable->SetValue(device, "LightPosW", Pos, sizeof(Pos));

}