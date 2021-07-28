/*=============================================================================

�A�C�e��( ���[�V���� )[ ItemRation.cpp ]

-------------------------------------------------------------------------------

��  Create
2018/01/22
=============================================================================*/

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "FrameworkBase\Common.h"
#include "FrameworkBase\RendererDirectX.h"
#include "FrameworkBase\ModelManagerDirectX.h"
#include "FrameworkBase\Game.h"
#include "FrameworkBase\Collision.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "FrameworkBase\Game.h"
#include "FrameworkBase\CameraDirectX.h"
#include "GameScene.h"
#include "Object.h"
#include "Player.h"
#include "ItemGetUIRation.h"
#include "ItemUI.h"
#include "ItemRation.h"

/*-----------------------------------------------------------------------------
Macro
-----------------------------------------------------------------------------*/
#define MODEL_FILEPATH (MODEL_PATH"Ration.x")
#define MODEL_VERTEXSHADER_PATH (SHADER_PATH"LightingOff_Vertex.hlsl")
#define MODEL_PIXELSHADER_PATH (SHADER_PATH"LightingOff_Pixel.hlsl")
#define ROTATION_SPEED (-2.5f)// ��]�X�s�[�h
#define SCALE (1.0f)// �g��l
#define SHHERE_RADIUS (1.0f)// ���̔��a


/*-----------------------------------------------------------------------------
�R���X�g���N�^
-----------------------------------------------------------------------------*/
ItemRation::ItemRation(int priolity)
	:Item(priolity)
	,m_Rotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{}

/*-----------------------------------------------------------------------------
������
-----------------------------------------------------------------------------*/
void ItemRation::Initialize(void)
{
	m_ModelParam = Game::GetInstance()->GetModelManager()->GetModelParam(MODEL_FILEPATH);

	Item::SetItemGetUI(ItemGetUIRation::Create(Item::GetPosition()));

		D3DVERTEXELEMENT9 elements[] = {
		{0 ,0 ,D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{0 ,12 ,D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
		{0 ,24 ,D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
		D3DDECL_END()
	};
	RendererDirectX::GetDevice()->CreateVertexDeclaration(elements,&m_VertexDeclaration);

	HRESULT hr;
	// �N���[���̍쐬
	hr = m_ModelParam.Mesh->CloneMesh(D3DXMESH_MANAGED | D3DXMESH_WRITEONLY, elements, RendererDirectX::GetDevice(), &m_ModelParam.CloneMesh);
	if (FAILED(hr))
	{
		MessageBox(NULL, "���b�V���̍œK���Ɏ��s", "ItemRation.cpp", MB_OK);
	}


	m_VertexShader = new VertexShader;
	m_VertexShader->Initialize(MODEL_VERTEXSHADER_PATH);

	m_PixelShader = new PixelShader;
	m_PixelShader->Initialize(MODEL_PIXELSHADER_PATH);
}

/*-----------------------------------------------------------------------------
�I��
-----------------------------------------------------------------------------*/
void ItemRation::Uninitialize(void)
{
	Item::Uninitialize();

	SAFE_UNINIT(m_VertexShader);
	SAFE_UNINIT(m_PixelShader);
}

/*-----------------------------------------------------------------------------
�X�V
-----------------------------------------------------------------------------*/
void ItemRation::Update(void)
{
	if(!Item::GetActive()){ return; }

	Item::Update();

	m_Rotation.y += ROTATION_SPEED;
}

/*-----------------------------------------------------------------------------
�`��
-----------------------------------------------------------------------------*/
void ItemRation::Draw(void)
{
	if(!Item::GetActive()){ return; }


	D3DMATERIAL9 materialDefault;

	LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();

	WorldTransform(Device);// ���[���h���W�ϊ�

	ConfigShader(Device);// �V�F�[�_�[�̐ݒ�

	Device->SetVertexShader(m_VertexShader->GetVertexShader());
	Device->SetPixelShader(m_PixelShader->GetPixelShader());

	// ���݃f�o�C�X�ɐݒ肳��Ă���}�e���A�����̎擾
	Device->GetMaterial(&materialDefault);

	// �}�e���A���ւ̃|�C���^���擾
	m_ModelParam.Material = (D3DXMATERIAL*)m_ModelParam.BufferMaterial->GetBufferPointer();

	UINT samplerIndex0 = m_PixelShader->GetPixelShaderConstantTable()->GetSamplerIndex("sampler0");

	for (int CountMaterial = 0; CountMaterial < (int)m_ModelParam.NumMaterial; CountMaterial++)
	{
		m_VertexShader->GetVertexShaderConstantTable()->SetValue(RendererDirectX::GetDevice(), "Diffuse", &m_ModelParam.Material[CountMaterial].MatD3D.Diffuse, sizeof(m_ModelParam.Material[CountMaterial].MatD3D.Diffuse));

		// �f�o�C�X�Ƀ}�e���A���̐ݒ�
		Device->SetMaterial(&m_ModelParam.Material[CountMaterial].MatD3D);

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
void ItemRation::WorldTransform(LPDIRECT3DDEVICE9 Device)
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
����
-----------------------------------------------------------------------------*/
ItemRation* ItemRation::Create(D3DXVECTOR3 position)
{
	auto object = new ItemRation;

	object->SetPosition(position);
	object->Initialize();

	return object;
}

/*-----------------------------------------------------------------------------
�����蔻��
-----------------------------------------------------------------------------*/
bool ItemRation::Collision(void)
{

	D3DXVECTOR3 position = Object::GetPosition();
	Player* player = GameScene::GetPlayer();

	Collision_Sphere CollisionSphere(position, SHHERE_RADIUS);

	if (CollisionSphere.Judge(player->GetPosition(), player->GetSphereRadius()))
	{ // �Փ˔���
		
		Item::SetActive(false);
		Item::GetItemGetUI()->SetActive(true);
		GameScene::GetItemUI()->PlusNowPossession(1);

		return true;
	}

	return false;
}

void ItemRation::ConfigShader(LPDIRECT3DDEVICE9 device)
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
	D3DXVECTOR3 lightDirL;
	D3DXMATRIX mtxWorldInv;
	D3DXMatrixInverse(&mtxWorldInv, NULL, &m_MatrixWorld);
	D3DXVec3TransformNormal(&lightDirL, &lightDirW, &mtxWorldInv);
	D3DXVec3Normalize(&lightDirL, & lightDirL);
	vetexShaderConstantTable->SetValue(device, "lightDirL", &lightDirL, sizeof(lightDirL));


}