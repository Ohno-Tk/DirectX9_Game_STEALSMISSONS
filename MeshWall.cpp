/*=============================================================================

���b�V����[ MeshWall.cpp ]

-------------------------------------------------------------------------------

��  Create
	2017/07/06
=============================================================================*/

/*-----------------------------------------------------------------------------
	Header
-----------------------------------------------------------------------------*/
#include "FrameworkBase\Common.h"
#include "FrameworkBase\RendererDirectX.h"
#include "FrameworkBase\Game.h"
#include "FrameworkBase\TextureManagerDirectX.h"
#include "FrameworkBase\CameraDirectX.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Object.h"
#include "MeshWall.h"

/*-----------------------------------------------------------------------------
	Macro
-----------------------------------------------------------------------------*/
#define TEXTURE_ID (TEXTURE_PATH"GAME/Wall.jpg")
#define MODEL_VERTEXSHADER_PATH (SHADER_PATH"MeshWall_Vertex.hlsl")
#define MODEL_PIXELSHADER_PATH (SHADER_PATH"MeshWall_Pixel.hlsl")

/*-----------------------------------------------------------------------------
	Static
-----------------------------------------------------------------------------*/
LPDIRECT3DTEXTURE9 MeshWall::m_Texture = NULL;

/*-----------------------------------------------------------------------------
Namespace
-----------------------------------------------------------------------------*/
using namespace std;

MeshWall::MeshWall(int Priolity)
	:Object(Priolity)
	,m_VertexBuffer(NULL)
	,m_IndexBuffer(NULL)
	,m_Rotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	,m_NumBlock_X(0)
	,m_NumBlock_Y(0)
	,m_NumVertex(0)
	,m_NumIndexBuffer(0)
	,m_SizeBlock_X(0.0f)
	,m_SizeBlock_Z(0.0f)
	,m_Color(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))
{}

MeshWall *MeshWall::Create(D3DXVECTOR3 Pos, float Rot, UINT NumBlock_X, UINT NumBlock_Y, float SizeBlock_X, float SizeBlock_Y)
{
	auto object = new MeshWall;

	object->SetPosition(Pos);

	object->m_Rotation = D3DXVECTOR3(0.0f, Rot, 0.0f);

	object->m_NumBlock_X = NumBlock_X;
	object->m_NumBlock_Y = NumBlock_Y;

	object->SetVertexCount(NumBlock_X, NumBlock_Y);

	object->SetIndexBufferCount(NumBlock_X, NumBlock_Y);

	object->m_TexturePath = TEXTURE_ID;

	object->m_SizeBlock_X = SizeBlock_X;
	object->m_SizeBlock_Z = SizeBlock_Y;

	object->Initialize();

	return object;
}

void MeshWall::Initialize(void)
{
	LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();

	MakeVerTex(Device);

	MakeIndex(Device);

	m_VertexShader = new VertexShader;
	m_VertexShader->Initialize(MODEL_VERTEXSHADER_PATH);

	m_PixelShader = new PixelShader;
	m_PixelShader->Initialize(MODEL_PIXELSHADER_PATH);
}

void MeshWall::Uninitialize(void)
{
	SAFE_RELEASE(m_VertexBuffer);

	SAFE_RELEASE(m_IndexBuffer);

	SAFE_UNINIT(m_VertexShader);
	SAFE_UNINIT(m_PixelShader);

	Object::Release();	//	�I�u�W�F�N�g���g�̉��
}

void MeshWall::Update(void)
{
	SetVerTex();
}

void MeshWall::Draw(void)
{
	LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();


	D3DVERTEXELEMENT9 elements[] = {
	{0 ,0 ,D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
	{0 ,12 ,D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
	{0 ,24 ,D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0},
	{0 ,36 ,D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
	D3DDECL_END()
	};
	RendererDirectX::GetDevice()->CreateVertexDeclaration(elements,&m_VertexDeclaration);

	Device->SetStreamSource(0, m_VertexBuffer, 0, sizeof(VERTEX_3D));

	Device->SetIndices(m_IndexBuffer);

	Device->SetFVF(FVF_VERTEX_3D);

	UINT samplerIndex0 = m_PixelShader->GetPixelShaderConstantTable()->GetSamplerIndex("sampler0");
	TextureManagerDirectX* manager = Game::GetInstance()->GetTextureManager();
	Device->SetTexture(samplerIndex0, manager->GetTextureInfo(m_TexturePath).Texture);

	Device->SetVertexShader(m_VertexShader->GetVertexShader());
	Device->SetPixelShader(m_PixelShader->GetPixelShader());

	WorldTransform(Device);
	ConfigShader(Device);

	Device->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_NumIndexBuffer, 0, m_NumIndexBuffer - 2);

}

/*-----------------------------------------------------------------------------
���_�̍쐬
-----------------------------------------------------------------------------*/
void MeshWall::MakeVerTex(LPDIRECT3DDEVICE9 Device)
{

	if (FAILED(Device->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * m_NumVertex, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_VertexBuffer, NULL)))
	{
		MessageBox(NULL, "���_�o�b�t�@�̐����G���[", "MeshWall.cpp", MB_OK | MB_ICONHAND);
	}

	// �\���̂̃|�C���^�錾
	VERTEX_3D* pVtx;

	D3DXVECTOR3 position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	int Index = 0;

	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);


	//	�c
	for (UINT i = 0; i < m_NumBlock_Y + 1; i++)
	{

		Index = i * (m_NumBlock_X + 1);

		//	��
		for (UINT j = 0; j < (m_NumBlock_X + 1) * 2; j++)
		{

			//	���W
			position.x = (m_SizeBlock_X * m_NumBlock_X / 2) - m_NumBlock_X * m_SizeBlock_X + (m_SizeBlock_X * j);
			position.y = (m_SizeBlock_Z * m_NumBlock_Y / 2) - (m_SizeBlock_Z * i);
			position.z = 0.0f;
			
			pVtx[j + Index].Pos = position;//	���_���W
			
			pVtx[j + Index].Nor = D3DXVECTOR3(1.0f, 0.0f, 1.0f);//	�@��
			
			pVtx[j + Index].Color = m_Color;//	���_�F
		
			pVtx[j + Index].Tex = D3DXVECTOR2((float)j, (float)i);//	�e�N�X�`�����W

		}
	}

	//	�o�b�t�@�̃A�����b�N
	m_VertexBuffer->Unlock();

}

void MeshWall::SetVerTex(void)
{
	int Index = 0;

	// �\���̂̃|�C���^�錾
	VERTEX_3D* pVtx;

	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);


	//	�c
	for (UINT i = 0; i < m_NumBlock_Y + 1; i++)
	{

		Index = i * (m_NumBlock_X + 1);

		//	��
		for (UINT j = 0; j < (m_NumBlock_X + 1) * 2; j++)
		{						
			pVtx[j + Index].Nor = m_Normal;//	�@��
		}
	}

	//	�o�b�t�@�̃A�����b�N
	m_VertexBuffer->Unlock();

}

/*-----------------------------------------------------------------------------
�C���f�b�N�X�o�b�t�@�̍쐬
-----------------------------------------------------------------------------*/
void MeshWall::MakeIndex(LPDIRECT3DDEVICE9 Device)
{

	HRESULT hr;

	WORD* pIdx;

	//	�C���f�b�N�X�o�b�t�@�̐���
	hr = Device->CreateIndexBuffer(
		sizeof(WORD) * m_NumIndexBuffer,	//	�o�b�t�@��
		D3DUSAGE_WRITEONLY,	//	�g�p���@�t���O
		D3DFMT_INDEX16, //	�C���f�b�N�X�t�H�[�}�b�g
		D3DPOOL_MANAGED, //	�������̊Ǘ����@
		&m_IndexBuffer,	//	�C���f�b�N�X�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^�̃A�h���X
		NULL);


	if (FAILED(hr))
	{

		MessageBox(NULL, "�C���f�b�N�X�o�b�t�@�̐������s", "MeshWall.cpp", MB_OK | MB_ICONHAND);
	}


	//	�C���f�b�N�X�o�b�t�@�����b�N
	m_IndexBuffer->Lock(0, 0, (void**)&pIdx, 0);

	//	���v���𗠖ʂƂ���
	//	�c
	for (UINT Cnt1 = 0; Cnt1 < m_NumBlock_Y; Cnt1++)
	{

		//	�͂��߂���Ȃ�������
		//	�k�ރ|���S��
		if (Cnt1 != 0)
		{

			//	1�_�ł�
			pIdx[0] = (WORD)((Cnt1 + 1) * (m_NumBlock_X + 1));

			pIdx++;	//	�|�C���^�����炷
		}

		//	2�_�ł�
		pIdx[0] = (WORD)((Cnt1 + 1) * (m_NumBlock_X + 1));
		pIdx[1] = (WORD)((Cnt1 + 1) * (m_NumBlock_X + 1) - (m_NumBlock_X + 1));

		pIdx += 2;	//	�|�C���^�����炷

		//	��
		for (UINT Cnt2 = 0; Cnt2 < m_NumBlock_X; Cnt2++)
		{

			//	2�_�ł�
			pIdx[0] = (WORD)(((Cnt1 + 1) * (m_NumBlock_X + 1) + 1) + Cnt2);
			pIdx[1] = (WORD)(((Cnt1 + 1) * (m_NumBlock_X + 1) + 1) - (m_NumBlock_X + 1) + Cnt2);

			pIdx += 2;	//	�|�C���^�����炷

		}

		//	�Ōザ��Ȃ�������
		//	�k�ރ|���S��
		if (Cnt1 != m_NumBlock_Y - 1)
		{

			//	1�_�ł�
			pIdx[0] = (WORD)((Cnt1 + 1) * (m_NumBlock_X + 1) - 1);

			pIdx++;	//	�|�C���^�����炷
		}
	}

	//	�C���f�b�N�X�o�b�t�@�̃A�����b�N
	m_IndexBuffer->Unlock();

}

/*-----------------------------------------------------------------------------
���[���h���W�ϊ�
-----------------------------------------------------------------------------*/
void MeshWall::WorldTransform(LPDIRECT3DDEVICE9 Device)
{
	D3DXVECTOR3 Position = Object::GetPosition();


	D3DXMATRIX matrixScale, matrixRotation, matrixPosition;

	D3DXMatrixIdentity(&m_MatrixWorld);

	D3DXMatrixScaling(&matrixScale,
		1.0f,
		1.0f,
		1.0f);

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

void MeshWall::ConfigShader(LPDIRECT3DDEVICE9 device)
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

	D3DXVECTOR3 Pos[9] = {D3DXVECTOR3(-90.0f, 30.0f,   95.0f), D3DXVECTOR3(21.0f, 30.0f,   95.0f), D3DXVECTOR3(125.0f, 30.0f,   95.0f),
						  D3DXVECTOR3(-90.0f, 30.0f,  -15.0f), D3DXVECTOR3(21.0f, 30.0f,  -15.0f), D3DXVECTOR3(125.0f, 30.0f,  -15.0f),
						  D3DXVECTOR3(-90.0f, 30.0f, -115.0f), D3DXVECTOR3(21.0f, 30.0f, -115.0f), D3DXVECTOR3(125.0f, 30.0f, -115.0f)};
	pixelShaderConstantTable->SetValue(device, "LightPosW", Pos, sizeof(Pos));
	pixelShaderConstantTable->SetValue(device, "CameraEyeW", Game::GetInstance()->GetCamera()->GetPositionEye(), sizeof(D3DXVECTOR3));



}

/*-----------------------------------------------------------------------------
���_���̌v�Z
-----------------------------------------------------------------------------*/
void MeshWall::SetVertexCount(const UINT NumBlock_X, const UINT NumBlock_Y)
{
	m_NumVertex = (NumBlock_X + 1) * (NumBlock_Y + 1);
}

/*-----------------------------------------------------------------------------
�C���f�b�N�X�o�b�t�@�̌v�Z
-----------------------------------------------------------------------------*/
void MeshWall::SetIndexBufferCount(const UINT NumBlock_X, const UINT NumBlock_Y)
{
	m_NumIndexBuffer = (2 + 2 * NumBlock_X) * NumBlock_Y + (NumBlock_Y - 1) * 2;
}

/*-----------------------------------------------------------------------------
�ǂ���
-----------------------------------------------------------------------------*/
D3DXVECTOR3 MeshWall::CollisionMeshWall(D3DXVECTOR3 Position, D3DXVECTOR3 FrontVector)
{
	D3DXVECTOR3 Out = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 InverseFrontVector = FrontVector * -1;
	D3DXVECTOR3 normal = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	
	Out = D3DXVec3Dot(&InverseFrontVector, &normal) * normal;

	return Out;
}