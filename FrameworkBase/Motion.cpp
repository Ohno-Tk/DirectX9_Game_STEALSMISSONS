/*=============================================================================

���[�V����[ Motion.cpp ]

-------------------------------------------------------------------------------

��  Created Date
	2017/08/07
=============================================================================*/

/*-----------------------------------------------------------------------------
	Warning Prevention
-----------------------------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS

/*-----------------------------------------------------------------------------
	Header
-----------------------------------------------------------------------------*/
#include "RendererDirectX.h"
#include "Common.h"
#include "Game.h"
#include "Mathematics.h"
#include "ModelManagerDirectX.h"
#include "FileManager.h"
#include "../Object.h"
#include "CameraDirectX.h"
#include "../VertexShader.h"
#include "../PixelShader.h"
#include "Motion.h"

/*-----------------------------------------------------------------------------
	Macro
-----------------------------------------------------------------------------*/
#define TEXTURE_PATH "data/TEXTURE/"	//	�e�N�X�`���̃p�X
#define MODEL_VERTEXSHADER_PATH (SHADER_PATH"Motion_Vertex.hlsl")
#define MODEL_PIXELSHADER_PATH (SHADER_PATH"Motion_Pixel.hlsl")

/*-----------------------------------------------------------------------------
	static
-----------------------------------------------------------------------------*/
char Motion::m_Buffer[] = {};
char* Motion::m_FileToken[MAX_TOKEN] = {
	"SCRIPT",
	"END_SCRIPT",
	"NUM_MODEL",
	"MODEL_FILENAME",
	"CHARACTERSET",
	"END_CHARACTERSET",
	"PARTSSET",
	"END_PARTSSET",
	"INDEX",
	"PARENT",
	"POS",
	"ROT",
	"MOTIONSET",
	"END_MOTIONSET",
	"LOOP",
	"NUM_KEY",
	"KEYSET",
	"END_KEYSET",
	"FRAME",
	"KEY",
	"END_KEY",
	"=",
	"���̍s�͐�Ώ����Ȃ����ƁI",
};

Motion::Motion(int Priolity):Object(Priolity)
{
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	m_MotionIndex = 0;
	m_NumKeyCount = 0;
	m_MotionCount = 0;

	m_MotionEnd = false;

	m_TextFileName = NULL;

	for(int i = 0 ; i < MAX_MOTION ; i++)
	{
		m_CharacterData.Motion[i].Loop = 0;
		m_CharacterData.Motion[i].NumKey = 0;
		m_CharacterData.Motion[i].Frame = NULL;
		m_CharacterData.Motion[i].Next = NULL;

		m_BlendMotion[i].Loop = 0;
		m_BlendMotion[i].NumKey = 0;
		m_BlendMotion[i].Frame = NULL;
		m_BlendMotion[i].Next = NULL;
	}

	m_BlendNumKey = 0;
	m_BlendMotionIndex = 0;
	m_BlendUpdateCount = 0;
	m_MotionBlendFrame = 0;
}

Motion *Motion::Create(const int Priolity, char* TextFileName)
{
	auto motion = new Motion(Priolity);

	motion->m_TextFileName = TextFileName;

	motion->Initialize();

	return motion;
}

void Motion::Initialize( void )
{
	ReadText();	//	�e�L�X�g�t�@�C���̓ǂݍ���

	m_VertexShader = new VertexShader;
	m_VertexShader->Initialize(MODEL_VERTEXSHADER_PATH);

	m_PixelShader = new PixelShader;
	m_PixelShader->Initialize(MODEL_PIXELSHADER_PATH);
}

void Motion::Uninitialize( void )
{
	for(int i = 0 ; i < MAX_MOTION ; i++)
	{
		for(int j = 0 ; j < m_CharacterData.Motion[i].NumKey ; j++)
		{
			if(m_CharacterData.Motion[i].Next[j].Pos != NULL)
			{	//	���W

				delete m_CharacterData.Motion[i].Next[j].Pos;	//	���
				m_CharacterData.Motion[i].Next[j].Pos = NULL;
			}

			if(m_CharacterData.Motion[i].Next[j].Rot != NULL)
			{	//	��]

				delete m_CharacterData.Motion[i].Next[j].Rot;	//	���
				m_CharacterData.Motion[i].Next[j].Rot = NULL;
			}
		}

		if(m_CharacterData.Motion[i].Frame != NULL)
		{	//	���[�v���邩

			delete m_CharacterData.Motion[i].Frame;	//	���
			m_CharacterData.Motion[i].Frame = NULL;
		}

		if(m_CharacterData.Motion[i].Next != NULL)
		{	//	���̏ꏊ

			delete m_CharacterData.Motion[i].Next;	//	���
			m_CharacterData.Motion[i].Next = NULL;
		}
	}

	for(int i = 0 ; i < m_CharacterData.NumModel ; i++)
	{
		for(int j = 0 ; j < (int)m_CharacterData.PartInfo[i].ModelParam.NumMaterial ; j++)
		{
			if(m_CharacterData.PartInfo[i].ModelParam.Texture[j] != NULL)
			{	//	�e�N�X�`��

				m_CharacterData.PartInfo[i].ModelParam.Texture[j]->Release();	//	���
				m_CharacterData.PartInfo[i].ModelParam.Texture[j] = NULL;
			}
		}

		delete[] m_CharacterData.PartInfo[i].ModelParam.Texture;	//	���

		if(m_CharacterData.PartInfo[i].ModelParam.Mesh != NULL)
		{	//	���b�V�����

			m_CharacterData.PartInfo[i].ModelParam.Mesh->Release();	//	���
			m_CharacterData.PartInfo[i].ModelParam.Mesh = NULL;
		}

		if(m_CharacterData.PartInfo[i].ModelParam.BufferMaterial != NULL)
		{	//	�}�e���A�����

			m_CharacterData.PartInfo[i].ModelParam.BufferMaterial->Release();	//	���
			m_CharacterData.PartInfo[i].ModelParam.BufferMaterial = NULL;
		}
	}

	if(m_CharacterData.PartInfo != NULL)
	{	//	�L�����N�^�[���

		delete[] m_CharacterData.PartInfo;	//	���
		m_CharacterData.PartInfo = NULL;
	}

	SAFE_UNINIT(m_VertexShader);
	SAFE_UNINIT(m_PixelShader);

	Object::Release();	//	�I�u�W�F�N�g�̉��

}

void Motion::Update( void )
{
	MotionInterpolation();
//	MotionBlend();
}

void Motion::Draw( void )
{
	LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();

	D3DMATERIAL9 materialDefault;
	Device->GetMaterial(&materialDefault);

	D3DVERTEXELEMENT9 elements[] = {
	{0 ,0 ,D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
	{0 ,12 ,D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
	{0 ,24 ,D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
	D3DDECL_END()
	};
	RendererDirectX::GetDevice()->CreateVertexDeclaration(elements,&m_VertexDeclaration);


	WorldTransform(Device);
	ConfigShader(Device);// �V�F�[�_�[�̐ݒ�

	Device->SetVertexShader(m_VertexShader->GetVertexShader());
	Device->SetPixelShader(m_PixelShader->GetPixelShader());

	UINT samplerIndex0 = m_PixelShader->GetPixelShaderConstantTable()->GetSamplerIndex("sampler0");

	for(int i = 0 ; i < m_CharacterData.NumModel ; i++)
	{

		PartWorldTransform(i, Device);

		for(int j = 0 ; j < (int)m_CharacterData.PartInfo[i].ModelParam.NumMaterial ; j++)
		{
			m_PixelShader->GetPixelShaderConstantTable()->SetValue(RendererDirectX::GetDevice(), "MaterialDiffuse", &m_CharacterData.PartInfo[i].ModelParam.Material[j].MatD3D.Diffuse, sizeof(m_CharacterData.PartInfo[i].ModelParam.Material[j].MatD3D.Diffuse));

			Device->SetMaterial(&m_CharacterData.PartInfo[i].ModelParam.Material[j].MatD3D);

			Device->SetTexture(samplerIndex0, m_CharacterData.PartInfo[i].ModelParam.Texture[j]);

			m_CharacterData.PartInfo[i].ModelParam.Mesh->DrawSubset(j);
		}
		Device->SetMaterial(&materialDefault);
	}
}

void Motion::ConfigShader(LPDIRECT3DDEVICE9 device)
{
	LPD3DXCONSTANTTABLE vetexShaderConstantTable = m_VertexShader->GetVertexShaderConstantTable();
	LPD3DXCONSTANTTABLE pixelShaderConstantTable = m_PixelShader->GetPixelShaderConstantTable();

	D3DXVECTOR3 Pos[9] = {D3DXVECTOR3(-90.0f, 30.0f,   95.0f), D3DXVECTOR3(21.0f, 30.0f,   95.0f), D3DXVECTOR3(125.0f, 30.0f,   95.0f),
						  D3DXVECTOR3(-90.0f, 30.0f,  -15.0f), D3DXVECTOR3(21.0f, 30.0f,  -15.0f), D3DXVECTOR3(125.0f, 30.0f,  -15.0f),
						  D3DXVECTOR3(-90.0f, 30.0f, -115.0f), D3DXVECTOR3(21.0f, 30.0f, -115.0f), D3DXVECTOR3(125.0f, 30.0f, -115.0f)};
	pixelShaderConstantTable->SetValue(device, "LightPosW", Pos, sizeof(Pos));
	pixelShaderConstantTable->SetValue(device, "CameraEyeW", Game::GetInstance()->GetCamera()->GetPositionEye(), sizeof(D3DXVECTOR3));
}

/*-----------------------------------------------------------------------------
���[�V�������
-----------------------------------------------------------------------------*/
void Motion::MotionInterpolation(void)
{
	LinearInterpolation position(m_MotionCount);
	LinearInterpolation rotation(m_MotionCount);


	int NumkeyNext = (m_NumKeyCount + 1) % m_CharacterData.Motion[m_MotionIndex].NumKey;

	for (UINT i = 0; i < (UINT)m_CharacterData.NumModel; i++)
	{
		position.Interpolation(&m_CharacterData.PartInfo[i].Pos, m_CharacterData.Motion[m_MotionIndex].Next[m_NumKeyCount].Pos[i], m_CharacterData.Motion[m_MotionIndex].Next[NumkeyNext].Pos[i], m_CharacterData.Motion[m_MotionIndex].Frame[m_NumKeyCount]);
		rotation.Interpolation(&m_CharacterData.PartInfo[i].Rot, m_CharacterData.Motion[m_MotionIndex].Next[m_NumKeyCount].Rot[i], m_CharacterData.Motion[m_MotionIndex].Next[NumkeyNext].Rot[i], m_CharacterData.Motion[m_MotionIndex].Frame[m_NumKeyCount]);
	}

	m_MotionCount++;

	if ( m_MotionCount > m_CharacterData.Motion[m_MotionIndex].Frame[m_NumKeyCount] )
	{
		m_MotionCount = 0;
		m_NumKeyCount++;

		if (m_NumKeyCount == m_CharacterData.Motion[m_MotionIndex].NumKey)
		{
			m_NumKeyCount = 0;
		}

		else if (m_NumKeyCount == m_CharacterData.Motion[m_MotionIndex].NumKey - 1 && m_CharacterData.Motion[m_MotionIndex].Loop == 0)
		{
			m_MotionIndex = 0;
			m_NumKeyCount = 0;
			m_MotionEnd = true;
		}
	}
}

/*-----------------------------------------------------------------------------
���[�V�����u�����h
-----------------------------------------------------------------------------*/
void Motion::MotionBlend(void)
{
	/*float rate = (float)m_UpdateCount / m_Motion[m_MotionIndex].Frame[m_NumKeyCount];
	float blendRate = (float)m_BlendUpdateCount / m_BlendMotion[m_BlendMotionIndex].Frame[m_BlendNumKey];
	float motionBlendRate = (float)m_MotionBlendFrame / ((m_Motion[m_MotionIndex].Frame[m_NumKeyCount] + m_BlendMotion[m_BlendMotionIndex].Frame[m_BlendNumKey]) * 0.5f);

	int NumkeyNext = (m_NumKeyCount + 1) % m_Motion[m_MotionIndex].NumKey;
	int NumBlendKeyNext = (m_BlendNumKey + 1) % m_Motion[m_MotionIndex].NumKey;

	for (int i = 0; i < m_NumModel; i++)
	{
		D3DXVECTOR3 pos = m_Motion[m_MotionIndex].Next[m_NumKeyCount].Pos[i] * (1.0f - rate) + m_Motion[m_MotionIndex].Next[NumkeyNext].Pos[i] * rate;
		D3DXVECTOR3 rot = m_Motion[m_MotionIndex].Next[m_NumKeyCount].Rot[i] * (1.0f - rate) + m_Motion[m_MotionIndex].Next[NumkeyNext].Rot[i] * rate;

		D3DXVECTOR3 blendPos = m_BlendMotion[m_BlendMotionIndex].Next[m_BlendNumKey].Pos[i] * (1.0f - blendRate) + m_BlendMotion[m_BlendMotionIndex].Next[NumBlendKeyNext].Pos[i] * blendRate;
		D3DXVECTOR3 blendRot = m_BlendMotion[m_BlendMotionIndex].Next[m_BlendNumKey].Rot[i] * (1.0f - blendRate) + m_BlendMotion[m_BlendMotionIndex].Next[NumBlendKeyNext].Rot[i] * blendRate;

		m_PartInfo[i].Pos = pos * (1.0f - motionBlendRate) + blendPos * motionBlendRate;
		m_PartInfo[i].Rot = rot * (1.0f - motionBlendRate) + blendRot * motionBlendRate;
	}

	m_UpdateCount++;
	m_BlendUpdateCount++;
	m_MotionBlendFrame++;

	if (m_Motion[m_MotionIndex].Frame[m_NumKeyCount] < m_UpdateCount)
	{
		m_UpdateCount = 0;
		m_NumKeyCount++;

		if (m_NumKeyCount == m_Motion[m_MotionIndex].NumKey)
		{
			m_NumKeyCount = 0;
		}

		else if (m_NumKeyCount == m_Motion[m_MotionIndex].NumKey - 1 && m_Motion[m_MotionIndex].Loop == 0)
		{
			m_MotionIndex = 0;
			m_NumKeyCount = 0;
		}
	}

	if (m_BlendMotion[m_BlendMotionIndex].Frame[m_BlendNumKey] < m_BlendUpdateCount)
	{
		m_BlendUpdateCount = 0;
		m_BlendNumKey++;

		if (m_BlendNumKey == m_BlendMotion[m_BlendMotionIndex].NumKey)
		{
			m_BlendNumKey = 0;
		}

		else if (m_BlendNumKey == m_BlendMotion[m_BlendMotionIndex].NumKey - 1 && m_BlendMotion[m_BlendMotionIndex].Loop == 0)
		{
			m_BlendMotionIndex = 0;
			m_BlendNumKey = 0;
		}
	}*/
}

/*-----------------------------------------------------------------------------
���[���h���W�ϊ�
-----------------------------------------------------------------------------*/
void Motion::WorldTransform(LPDIRECT3DDEVICE9 Device)
{
	D3DXVECTOR3 Position = Object::GetPosition();

	D3DXMATRIX	MatrixScale;
	D3DXMATRIX	MatrixRotation;
	D3DXMATRIX	MatrixPosition;


	D3DXMatrixIdentity(&m_MtxWorld);

	D3DXMatrixScaling(&MatrixScale,
		m_Scale.x,
		m_Scale.y,
		m_Scale.z);

	D3DXMatrixRotationYawPitchRoll(&MatrixRotation,
		D3DXToRadian(m_Rotation.y),
		D3DXToRadian(m_Rotation.x),
		D3DXToRadian(m_Rotation.z));

	D3DXMatrixTranslation(&MatrixPosition,
		Position.x,
		Position.y,
		Position.z);

	D3DXMatrixMultiply(&m_MtxWorld, &m_MtxWorld, &MatrixScale);
	D3DXMatrixMultiply(&m_MtxWorld, &m_MtxWorld, &MatrixRotation);
	D3DXMatrixMultiply(&m_MtxWorld, &m_MtxWorld, &MatrixPosition);
}

/*-----------------------------------------------------------------------------
�p�[�c���Ƃ̃��[���h���W�ϊ�
-----------------------------------------------------------------------------*/
void Motion::PartWorldTransform(const int cntmodel, LPDIRECT3DDEVICE9 Device)
{
	D3DXMatrixIdentity(&m_CharacterData.PartInfo[cntmodel].MatrixWorld);

	D3DXMatrixScaling(&m_CharacterData.PartInfo[cntmodel].MatrixScl,
		m_CharacterData.PartInfo[cntmodel].Scale.x,
		m_CharacterData.PartInfo[cntmodel].Scale.y,
		m_CharacterData.PartInfo[cntmodel].Scale.z);

	D3DXMatrixRotationYawPitchRoll(&m_CharacterData.PartInfo[cntmodel].MatrixRot,
		m_CharacterData.PartInfo[cntmodel].Rot.y + m_CharacterData.PartInfo[cntmodel].OffsetRot.y,
		m_CharacterData.PartInfo[cntmodel].Rot.x + m_CharacterData.PartInfo[cntmodel].OffsetRot.x,
		m_CharacterData.PartInfo[cntmodel].Rot.z + m_CharacterData.PartInfo[cntmodel].OffsetRot.z);

	D3DXMatrixTranslation(&m_CharacterData.PartInfo[cntmodel].MatrixPos,
		m_CharacterData.PartInfo[cntmodel].Pos.x + m_CharacterData.PartInfo[cntmodel].OffsetPos.x,
		m_CharacterData.PartInfo[cntmodel].Pos.y + m_CharacterData.PartInfo[cntmodel].OffsetPos.y,
		m_CharacterData.PartInfo[cntmodel].Pos.z + m_CharacterData.PartInfo[cntmodel].OffsetPos.z);

	D3DXMatrixMultiply(&m_CharacterData.PartInfo[cntmodel].MatrixWorld, &m_CharacterData.PartInfo[cntmodel].MatrixWorld, &m_CharacterData.PartInfo[cntmodel].MatrixScl);
	D3DXMatrixMultiply(&m_CharacterData.PartInfo[cntmodel].MatrixWorld, &m_CharacterData.PartInfo[cntmodel].MatrixWorld, &m_CharacterData.PartInfo[cntmodel].MatrixRot);
	D3DXMatrixMultiply(&m_CharacterData.PartInfo[cntmodel].MatrixWorld, &m_CharacterData.PartInfo[cntmodel].MatrixWorld, &m_CharacterData.PartInfo[cntmodel].MatrixPos);

	if (m_CharacterData.PartInfo[cntmodel].Parent == -1)
	{	//	�e�q�\����-1��������

		D3DXMatrixMultiply(&m_CharacterData.PartInfo[cntmodel].MatrixWorld, &m_CharacterData.PartInfo[cntmodel].MatrixWorld, &m_MtxWorld);
	}
	else
	{
		D3DXMatrixMultiply(&m_CharacterData.PartInfo[cntmodel].MatrixWorld, &m_CharacterData.PartInfo[cntmodel].MatrixWorld, &m_CharacterData.PartInfo[m_CharacterData.PartInfo[cntmodel].Parent].MatrixWorld);
	}

	m_VertexShader->GetVertexShaderConstantTable()->SetMatrix(Device, "mtxW", &m_CharacterData.PartInfo[cntmodel].MatrixWorld);

	D3DXMATRIX mtxWVP = m_CharacterData.PartInfo[cntmodel].MatrixWorld * Game::GetInstance()->GetCamera()->GetViewProjectionMatrix();
	m_VertexShader->GetVertexShaderConstantTable()->SetMatrix(Device, "mtxWVP", &mtxWVP);

	D3DXMATRIX mtxInv;
	D3DXMatrixInverse(&mtxInv, NULL, &m_CharacterData.PartInfo[cntmodel].MatrixWorld);
	D3DXMatrixTranspose(&mtxInv, &mtxInv);
	m_VertexShader->GetVertexShaderConstantTable()->SetMatrix(Device, "mtxWIT", &mtxInv);
//	Device->SetTransform(D3DTS_WORLD, &m_CharacterData.PartInfo[cntmodel].MatrixWorld);
}

/*-----------------------------------------------------------------------------
���[�V�����ԍ��̃Z�b�g
-----------------------------------------------------------------------------*/
void Motion::SetMotionIndex(const int index)
{
	if (m_MotionIndex == index)
	{
		return;
	}

	m_MotionIndex = index;
	m_MotionCount = 0;
	m_NumKeyCount = 0;
}

/*-----------------------------------------------------------------------------
�e�L�X�g�t�@�C���̓ǂݍ���
-----------------------------------------------------------------------------*/
void Motion::ReadText(void)
{

	FILE* fp = fopen(m_TextFileName, "rt");

	if (fp == NULL)
	{	//	�G���[�`�F�b�N
		MessageBox(NULL, "���[�V�����f�[�^�擾�Ɏ��s", "Motion.cpp", MB_OK | MB_ICONHAND);
		return;
	}

	for(;;)
	{
		fscanf( fp , "%s" , m_Buffer );

		if( MatchFileToken(m_Buffer , m_FileToken[SCRIPT]) )
		{	//	SCRIPT�̌���

			ReadNumModel(fp);		//	���f�����̓ǂݍ���
			ReadModelFileName(fp);	//	���f���t�@�C�����̓ǂݍ���
			ReadCharacterInfo(fp);	//	�L�����N�^���̓ǂݍ���
			ReadMotion(fp);			//	���[�V�������̓ǂݍ���
		}

		//	END_SCRIPT�̌���
		else if( MatchFileToken(m_Buffer , m_FileToken[LAST_WORD]) ){ break; }
	}

	fclose(fp);
}

/*-----------------------------------------------------------------------------
���f�����̓ǂݍ���
-----------------------------------------------------------------------------*/
void Motion::ReadNumModel(FILE *fp)
{
	for(;;)
	{
		fscanf( fp , "%s" , m_Buffer );

		if( MatchFileToken(m_Buffer , m_FileToken[NUM_MODEL]) )
		{	//	NUM_MODEL�̌���

			fscanf( fp , "%s" , m_Buffer ); // �u = �v

			fscanf( fp , "%d" , &m_CharacterData.NumModel );	//	���f�����̓ǂݍ���

			m_CharacterData.PartInfo = new PART[m_CharacterData.NumModel];

			InitializePartsData();
			break;
		}
	}
}

/*-----------------------------------------------------------------------------
���f���t�@�C�����̓ǂݍ���
-----------------------------------------------------------------------------*/
void Motion::ReadModelFileName(FILE *fp)
{
	int nummodel = 0;

	while(nummodel != m_CharacterData.NumModel)
	{	//	���f������

		fscanf( fp , "%s" , m_Buffer );

		if( MatchFileToken(m_Buffer , m_FileToken[MODEL_FILENAME]) )
		{	//	MODEL_FILENAME�̌���

			fscanf( fp , "%s" , m_Buffer );	//�u = �v 

			fscanf( fp , "%s" , &m_Buffer );	//	���f���t�@�C�����̓ǂݍ���

			LoadModel(nummodel, m_Buffer);		//	���f���̃��[�h
			nummodel++;
		}
	}
}

/*-----------------------------------------------------------------------------
���f���̃��[�h
-----------------------------------------------------------------------------*/
void Motion::LoadModel(const int nummodel, char *modelfilename)
{
	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();

	HRESULT hr;

	// �ǂݍ���
	hr = D3DXLoadMeshFromX(		modelfilename,		//	�t�@�C����
								D3DXMESH_SYSTEMMEM,
								Device,				//	�f�o�C�X
								&m_CharacterData.PartInfo[nummodel].ModelParam.AdjacecyBuffer,					//	�אڃo�b�t�@
								&m_CharacterData.PartInfo[nummodel].ModelParam.BufferMaterial,			//	�}�e���A�������i�[
								NULL,
								&m_CharacterData.PartInfo[nummodel].ModelParam.NumMaterial,				//	�}�e���A����
								&m_CharacterData.PartInfo[nummodel].ModelParam.Mesh );				//	���b�V��

	//	���f���̃G���[�`�F�b�N
	if(FAILED(hr))
	{
		MessageBox( NULL , modelfilename , "Motion.cpp" , MB_OK | MB_ICONHAND );
	}

	//	�}�e���A�����̃|�C���^�Ƃ��ăo�b�t�@�̃A�h���X���擾
	m_CharacterData.PartInfo[nummodel].ModelParam.Material = ( D3DXMATERIAL* )m_CharacterData.PartInfo[nummodel].ModelParam.BufferMaterial->GetBufferPointer();

	//	�e�N�X�`���̓��I�m��
	m_CharacterData.PartInfo[nummodel].ModelParam.Texture = new LPDIRECT3DTEXTURE9[m_CharacterData.PartInfo[nummodel].ModelParam.NumMaterial];


	for(int j = 0 ; j < (int)m_CharacterData.PartInfo[nummodel].ModelParam.NumMaterial ; j++)
	{

		m_CharacterData.PartInfo[nummodel].ModelParam.Texture[j] = NULL;

		if(m_CharacterData.PartInfo[nummodel].ModelParam.Material[j].pTextureFilename)
		{

			char filePath[MAX_PATH];
			strcpy(filePath, TEXTURE_PATH);
			strcat(filePath, m_CharacterData.PartInfo[nummodel].ModelParam.Material[j].pTextureFilename);

			hr = D3DXCreateTextureFromFile( Device, filePath, &m_CharacterData.PartInfo[nummodel].ModelParam.Texture[j]);

			//	�e�N�X�`���̃G���[�`�F�b�N
			if(FAILED(hr))
			{
				MessageBox( NULL , "���f���̃e�N�X�`���p�X�����������ł�" , "Motion.cpp" , MB_OK | MB_ICONHAND );
			}
		}
		else
		{
			hr = D3DXCreateTextureFromFile(Device, TEXTURE_PATH"GAME/White.png", &m_CharacterData.PartInfo[nummodel].ModelParam.Texture[j]);
		}
	}

	// ���b�V���̍œK��
	hr = m_CharacterData.PartInfo[nummodel].ModelParam.Mesh->OptimizeInplace(D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_VERTEXCACHE,
		(DWORD*)m_CharacterData.PartInfo[nummodel].ModelParam.AdjacecyBuffer->GetBufferPointer(), NULL, NULL, NULL);

	if (FAILED(hr))
	{
		MessageBox(NULL, "���b�V���̍œK���Ɏ��s", "Motioncpp", MB_OK);
	}

	SAFE_RELEASE(m_CharacterData.PartInfo[nummodel].ModelParam.AdjacecyBuffer);
}

/*-----------------------------------------------------------------------------
�L�����N�^���̓ǂݍ���
-----------------------------------------------------------------------------*/
void Motion::ReadCharacterInfo(FILE *fp)
{
	while( MisMatchFileToken(m_Buffer, m_FileToken[END_CHARACTERSET]) )
	{
		fscanf( fp , "%s" , m_Buffer );

		if( MatchFileToken(m_Buffer , m_FileToken[CHARACTERSET]) )
		{	//	CHARACTERSET�̌���

			ReadPartsSet(fp);	//	�L�����N�^�̃p�[�c���̓ǂݍ���
		}
	}
}

/*-----------------------------------------------------------------------------
�L�����N�^�̃p�[�c���̓ǂݍ���
-----------------------------------------------------------------------------*/
void Motion::ReadPartsSet(FILE *fp)
{
	int nummodel = 0;

	while( nummodel != m_CharacterData.NumModel )
	{	//	���f������

		fscanf( fp , "%s" , m_Buffer );

		if( MatchFileToken(m_Buffer, m_FileToken[PARTSSET]) )
		{	//	PARTSSET�̌���

			for(;;)
			{
				fscanf( fp , "%s" , m_Buffer );

				if( MatchFileToken(m_Buffer, m_FileToken[INDEX]) )
				{	//	INDEX�̌���
					fscanf( fp , "%s" , m_Buffer );	//�u = �v

					fscanf( fp , "%d" , &m_CharacterData.PartInfo[nummodel].Index );	//	�p�[�c�ԍ��̓ǂݍ���
				}

				else if( MatchFileToken(m_Buffer, m_FileToken[PARENT]) )
				{	//	PARENT�̌���
					fscanf( fp , "%s" , m_Buffer );	//�u = �v

					fscanf( fp , "%d" , &m_CharacterData.PartInfo[nummodel].Parent );	//	�e�q�\���̓ǂݍ���
				}

				else if( MatchFileToken(m_Buffer, m_FileToken[POS]) )
				{	//	POS�̌���
					fscanf( fp , "%s" , m_Buffer );	//�u = �v

					//	���W�̓ǂݍ���
					fscanf( fp , "%f" , &m_CharacterData.PartInfo[nummodel].OffsetPos.x );
					fscanf( fp , "%f" , &m_CharacterData.PartInfo[nummodel].OffsetPos.y );
					fscanf( fp , "%f" , &m_CharacterData.PartInfo[nummodel].OffsetPos.z );
				}

				else if( MatchFileToken(m_Buffer, m_FileToken[ROT]) )
				{	//	ROT�̌���
					fscanf( fp , "%s" , m_Buffer );	//�u = �v

					//	��]�̓ǂݍ���
					fscanf( fp , "%f" , &m_CharacterData.PartInfo[nummodel].OffsetRot.x );
					fscanf( fp , "%f" , &m_CharacterData.PartInfo[nummodel].OffsetRot.y );
					fscanf( fp , "%f" , &m_CharacterData.PartInfo[nummodel].OffsetRot.z );
					break;
				}
			}
		}

		//	END_PARTSSET�̌���
		if(strcmp( m_Buffer , m_FileToken[END_PARTSSET] ) == 0){ nummodel++; }
	}
}

/*-----------------------------------------------------------------------------
���[�V�������̓ǂݍ���
-----------------------------------------------------------------------------*/
void Motion::ReadMotion(FILE *fp)
{
	int cntmotion = 0;

	while(cntmotion != MAX_MOTION)
	{	//	���[�V�������𒴂��Ȃ�������

		fscanf( fp , "%s" , m_Buffer );

		if( MatchFileToken(m_Buffer, m_FileToken[MOTIONSET]) )
		{	//	MOTIONSET�̌���

			for(;;)
			{
				fscanf( fp , "%s" , m_Buffer );

				if( MatchFileToken(m_Buffer, m_FileToken[LOOP]) )
				{	//	LOOP�̌���
					fscanf( fp , "%s" , m_Buffer ); //�u = �v

					fscanf( fp , "%d" , &m_CharacterData.Motion[cntmotion].Loop );	//	���[�v���邩�̓ǂݍ���
				}

				else if( MatchFileToken(m_Buffer, m_FileToken[NUMKEY]) )
				{	//	NUM_KEY�̌���
					fscanf( fp , "%s" , m_Buffer );

					fscanf( fp , "%d" , &m_CharacterData.Motion[cntmotion].NumKey );	//	�L�[���̓ǂݍ���

					m_CharacterData.Motion[cntmotion].Frame = new int[m_CharacterData.Motion[cntmotion].NumKey];

					m_CharacterData.Motion[cntmotion].Next = new KEYINFO[ m_CharacterData.Motion[cntmotion].NumKey ];
					for(int i = 0 ; i < m_CharacterData.Motion[cntmotion].NumKey ; i++ )
					{	//	�L�[����

						m_CharacterData.Motion[cntmotion].Next[i].Pos = new D3DXVECTOR3[m_CharacterData.NumModel];
						m_CharacterData.Motion[cntmotion].Next[i].Rot = new D3DXVECTOR3[m_CharacterData.NumModel];
					}

					InitializeMotionData(cntmotion);
					break;
				}
			}

			int numkey = 0;

			while(numkey != m_CharacterData.Motion[cntmotion].NumKey)
			{	//	�L�[����

				fscanf( fp , "%s" , m_Buffer );

				if( MatchFileToken(m_Buffer, m_FileToken[KEYSET]) )
				{	//	KEYSET�̌���

					int nummodel = 0;

					while( nummodel != m_CharacterData.NumModel )
					{	//	���f������

						fscanf( fp , "%s" , m_Buffer );

						if( MatchFileToken(m_Buffer, m_FileToken[FRAME]) )
						{	//	FRAME�̌���
							fscanf( fp , "%s" , m_Buffer );//�u = �v

							fscanf( fp , "%d" , &m_CharacterData.Motion[cntmotion].Frame[numkey] );//	�t���[�����̓ǂݍ���
						}

						else if( MatchFileToken(m_Buffer, m_FileToken[POS]) )
						{	//	POS�̌���
							fscanf( fp , "%s" , m_Buffer );//�u = �v

							//	���W�̓ǂݍ���
							fscanf( fp , "%f" , &m_CharacterData.Motion[cntmotion].Next[numkey].Pos[nummodel].x );
							fscanf( fp , "%f" , &m_CharacterData.Motion[cntmotion].Next[numkey].Pos[nummodel].y );
							fscanf( fp , "%f" , &m_CharacterData.Motion[cntmotion].Next[numkey].Pos[nummodel].z );
						}

						else if( MatchFileToken(m_Buffer, m_FileToken[ROT]) )
						{	//	ROT�̌���
							fscanf( fp , "%s" , m_Buffer );//�u = �v

							//	��]�̓ǂݍ���
							fscanf( fp , "%f" , &m_CharacterData.Motion[cntmotion].Next[numkey].Rot[nummodel].x );
							fscanf( fp , "%f" , &m_CharacterData.Motion[cntmotion].Next[numkey].Rot[nummodel].y );
							fscanf( fp , "%f" , &m_CharacterData.Motion[cntmotion].Next[numkey].Rot[nummodel].z );
						}

						else if( MatchFileToken(m_Buffer, m_FileToken[END_KEY]) ){ nummodel++; }
					}
				}

				else if( MatchFileToken(m_Buffer, m_FileToken[END_KEYSET]) ){ numkey++; }
			}
		}

		//	END_MOTIONSET�̌���
		if( MatchFileToken(m_Buffer, m_FileToken[END_MOTIONSET]) ){ cntmotion++; }

		//	END_SCRIPT�̌���
		if ( MatchFileToken(m_Buffer, m_FileToken[END_SCRIPT]) )
		{
			for (UINT i = 0; i < MAX_MOTION; i++)
			{
				m_BlendMotion[i] = m_CharacterData.Motion[i];
			}

			for (UINT j = 0; j < (UINT)m_CharacterData.NumModel; j++)
			{
				m_CharacterData.PartInfo[j].Pos = m_CharacterData.Motion[0].Next[0].Pos[j];
				m_CharacterData.PartInfo[j].Rot = m_CharacterData.Motion[0].Next[0].Rot[j];
			}
			break;
		}
	}
}

void Motion::InitializePartsData(void)
{
	for(int i = 0 ; i < m_CharacterData.NumModel ; i++)
	{

		m_CharacterData.PartInfo[i].Index = 0;
		m_CharacterData.PartInfo[i].Parent = 0;
		m_CharacterData.PartInfo[i].OffsetPos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		m_CharacterData.PartInfo[i].OffsetRot = D3DXVECTOR3(0.0f,0.0f,0.0f);
		m_CharacterData.PartInfo[i].Pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		m_CharacterData.PartInfo[i].Rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
		m_CharacterData.PartInfo[i].Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		m_CharacterData.PartInfo[i].ModelParam.Texture = NULL;
		m_CharacterData.PartInfo[i].ModelParam.Mesh = NULL;
		m_CharacterData.PartInfo[i].ModelParam.BufferMaterial = NULL;
		D3DXMatrixIdentity(&m_CharacterData.PartInfo[i].MatrixPos);
		D3DXMatrixIdentity(&m_CharacterData.PartInfo[i].MatrixRot);
		D3DXMatrixIdentity(&m_CharacterData.PartInfo[i].MatrixScl);
		D3DXMatrixIdentity(&m_CharacterData.PartInfo[i].MatrixWorld);
	}
}

void Motion::InitializeMotionData(int countMotion)
{
	for(int j = 0 ; j < m_CharacterData.Motion[countMotion].NumKey ; j++ )
	{
		for(int k = 0 ; k < m_CharacterData.NumModel ; k++ )
		{	//	���f������

			m_CharacterData.Motion[countMotion].Next[j].Pos[k].x = 0.0f;
			m_CharacterData.Motion[countMotion].Next[j].Pos[k].y = 0.0f;
			m_CharacterData.Motion[countMotion].Next[j].Pos[k].z = 0.0f;
			m_CharacterData.Motion[countMotion].Next[j].Rot[k].x = 0.0f;
			m_CharacterData.Motion[countMotion].Next[j].Rot[k].y = 0.0f;
			m_CharacterData.Motion[countMotion].Next[j].Rot[k].z = 0.0f;
		}
	}
}

// �t�@�C���g�[�N���̈�v
bool Motion::MatchFileToken(char* buffer, char* fileToken)
{
	if(strcmp(buffer , fileToken) == 0){ return true; }

	return false;
}

// �t�@�C���g�[�N���̕s��v
bool Motion::MisMatchFileToken(char* buffer, char* fileToken)
{
	if(strcmp(buffer , fileToken) != 0){ return true; }

	return false;
}
