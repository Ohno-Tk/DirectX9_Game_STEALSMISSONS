/*=============================================================================

X���f���`��[ SpriteModeLX.cpp ]

-------------------------------------------------------------------------------
��  Create
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
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	��]
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);	//	�g�嗦
}

/*-----------------------------------------------------------------------------
Function:   SpriteModelX* SpriteModelX::Create(D3DXVECTOR3 position, char* modelFilePath, int priolity)
Parameter:  D3DXVECTOR3 position
              ���W
            D3DXVECTOR2 size
			  �傫��
            string modelFilePath
			  ���f���̃p�X
			int priolity
			  �D��x
Overview:   ����
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



	// ���݃f�o�C�X�ɐݒ肳��Ă���}�e���A�����̎擾
	Device->GetMaterial(&materialDefault);

	// �}�e���A���ւ̃|�C���^���擾
	m_ModelParam.Material = (D3DXMATERIAL*)m_ModelParam.BufferMaterial->GetBufferPointer();

	UINT samplerIndex0 = m_PixelShader->GetPixelShaderConstantTable()->GetSamplerIndex("sampler0");

	for (int CountMaterial = 0; CountMaterial < (int)m_ModelParam.NumMaterial; CountMaterial++)
	{
		m_PixelShader->GetPixelShaderConstantTable()->SetValue(RendererDirectX::GetDevice(), "Diffuse", &m_ModelParam.Material[CountMaterial].MatD3D.Diffuse, sizeof(m_ModelParam.Material[CountMaterial].MatD3D.Diffuse));
		//	�A���r�G���g���̐ݒ�
//		m_ModelParam.Material[CountMaterial].MatD3D.Ambient = m_ModelParam.Material[CountMaterial].MatD3D.Diffuse;

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
Function:   void SpriteModelX::WorldTransform(LPDIRECT3DDEVICE9 Device)
Parameter:  LPDIRECT3DDEVICE9 Device
			  �f�o�C�X
Overview:   ���[���h���W�ϊ�
-----------------------------------------------------------------------------*/
void SpriteModelX::WorldTransform(LPDIRECT3DDEVICE9 Device)
{
	D3DXVECTOR3 Position = Object::GetPosition();


	D3DXMATRIX matrixScale, matrixRotation, matrixPosition;

	D3DXMatrixIdentity(&m_MatrixWorld);	//	�s���P�ʍs��ɂ���

	//	�g��s������
	D3DXMatrixScaling(&matrixScale,	//�g��s�񂪍����
		m_Scale.x,	//	X���g��
		m_Scale.y,	//	Y���g��
		m_Scale.z);	//	Z���g��

	//	��]�s������
	D3DXMatrixRotationYawPitchRoll(&matrixRotation,	//	��]�s�񂪍����
		D3DXToRadian(m_Rotation.y), //	Y����]
		D3DXToRadian(m_Rotation.x), //	X����]
		D3DXToRadian(m_Rotation.z)); //	Z����]

	//	���s�ړ��s������
	D3DXMatrixTranslation(&matrixPosition,
		Position.x,	//	X���ړ�
		Position.y,	//	Y���ړ�
		Position.z);	//	Z���ړ�


	//	�e�s���������
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