/*=============================================================================

�^�C�g���w�i[ TitleBackGround.cpp ]

-------------------------------------------------------------------------------

��  Create
2018/01/27
=============================================================================*/

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "FrameworkBase\Common.h"
#include "FrameworkBase\RendererDirectX.h"
#include "FrameworkBase\Game.h"
#include "FrameworkBase\TextureManagerDirectX.h"
#include "FrameworkBase\CameraDirectX.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Object.h"
#include "TitleBackGround.h"

/*-----------------------------------------------------------------------------
Macro
-----------------------------------------------------------------------------*/
#define OBJECT_TEXTURE_PATH (TEXTURE_PATH"TITLE/Wall000.jpg")
#define MODEL_VERTEXSHADER_PATH (SHADER_PATH"TitleMeshWall_Vertex.hlsl")
#define MODEL_PIXELSHADER_PATH (SHADER_PATH"TitleMeshWall_Pixel.hlsl")
#define TEX_SPEED (-0.05f)

/*-----------------------------------------------------------------------------
Static
-----------------------------------------------------------------------------*/
LPDIRECT3DTEXTURE9 TitleBackGround::m_Texture = NULL;


/*-----------------------------------------------------------------------------
�R���X�g���N�^
-----------------------------------------------------------------------------*/
TitleBackGround::TitleBackGround(int priolity)
	:Object(priolity)
	,m_NumBlock_X(10)
	,m_NumBlock_Y(10)
	,m_SizeBlock_X(7.0f)
	,m_SizeBlock_Z(9.0f)
	,m_TexCoord(0.0f)
	,m_Normal(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{}

/*-----------------------------------------------------------------------------
����
-----------------------------------------------------------------------------*/
TitleBackGround* TitleBackGround::Create(D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
	auto object = new TitleBackGround;

	object->SetPosition(position);
	object->m_Rotation = rotation;

	object->Initialize();

	return object;
}

/*-----------------------------------------------------------------------------
������
-----------------------------------------------------------------------------*/
void TitleBackGround::Initialize(void)
{
	LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();

	m_NumVertex = (m_NumBlock_X + 1) * (m_NumBlock_Y + 1);
	m_NumIndexBuffer = (2 + 2 * m_NumBlock_X) * m_NumBlock_Y + (m_NumBlock_Y - 1) * 2;


	MakeVerTex(Device);

	MakeIndex(Device);


	m_VertexShader = new VertexShader;
	m_VertexShader->Initialize(MODEL_VERTEXSHADER_PATH);

	m_PixelShader = new PixelShader;
	m_PixelShader->Initialize(MODEL_PIXELSHADER_PATH);
}

/*-----------------------------------------------------------------------------
�I��
-----------------------------------------------------------------------------*/
void TitleBackGround::Uninitialize(void)
{
	SAFE_RELEASE(m_VertexBuffer);

	SAFE_RELEASE(m_IndexBuffer);

	SAFE_UNINIT(m_VertexShader);
	SAFE_UNINIT(m_PixelShader);

	Object::Release();	//	�I�u�W�F�N�g���g�̉��
}

/*-----------------------------------------------------------------------------
�X�V
-----------------------------------------------------------------------------*/
void TitleBackGround::Update(void)
{
	m_TexCoord += TEX_SPEED;

	ChangeVerTex();
}

/*-----------------------------------------------------------------------------
�`��
-----------------------------------------------------------------------------*/
void TitleBackGround::Draw(void)
{
	LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();


	D3DVERTEXELEMENT9 elements[] = {
	{0 ,0 ,D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
	{0 ,12 ,D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
	{0 ,24 ,D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
	D3DDECL_END()
	};
	RendererDirectX::GetDevice()->CreateVertexDeclaration(elements,&m_VertexDeclaration);


	Device->SetStreamSource(0, m_VertexBuffer, 0, sizeof(VERTEX_3D));

	Device->SetIndices(m_IndexBuffer);

	Device->SetFVF(FVF_VERTEX_3D);

	UINT samplerIndex0 = m_PixelShader->GetPixelShaderConstantTable()->GetSamplerIndex("sampler0");
	Device->SetTexture(samplerIndex0, Game::GetInstance()->GetTextureManager()->GetTextureInfo(OBJECT_TEXTURE_PATH).Texture);

	WorldTransform(Device);
	ConfigShader(Device);

	Device->SetVertexShader(m_VertexShader->GetVertexShader());
	Device->SetPixelShader(m_PixelShader->GetPixelShader());

	Device->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_NumIndexBuffer, 0, m_NumIndexBuffer - 2);

}

/*-----------------------------------------------------------------------------
���[���h���W�ϊ�
-----------------------------------------------------------------------------*/
void TitleBackGround::WorldTransform(LPDIRECT3DDEVICE9 Device)
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

//	Device->SetTransform(D3DTS_WORLD, &m_MatrixWorld);

}

void TitleBackGround::ConfigShader(LPDIRECT3DDEVICE9 device)
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


	D3DXVECTOR3 lightDirW(0.0f,0.0f, -1.0f);
	vetexShaderConstantTable->SetValue(device, "lightDirW", &lightDirW, sizeof(lightDirW));


}

/*-----------------------------------------------------------------------------
���_�̍쐬
-----------------------------------------------------------------------------*/
void TitleBackGround::MakeVerTex(LPDIRECT3DDEVICE9 Device)
{

	if (FAILED(Device->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * m_NumVertex, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_VertexBuffer, NULL)))
	{
		MessageBox(NULL, "���_�o�b�t�@�̐����G���[", "TitleBackGround.cpp", MB_OK | MB_ICONHAND);
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
			
			pVtx[j + Index].Nor = D3DXVECTOR3(0.0f, -1.0f, -1.0f);//	�@��
			
			pVtx[j + Index].Color = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);//	���_�F
		
			pVtx[j + Index].Tex = D3DXVECTOR2((float)j, (float)i);//	�e�N�X�`�����W

		}
	}

	//	�o�b�t�@�̃A�����b�N
	m_VertexBuffer->Unlock();

}

/*-----------------------------------------------------------------------------
���_�̕ύX
-----------------------------------------------------------------------------*/
void TitleBackGround::ChangeVerTex(void)
{
	VERTEX_3D* pVtx;

	int Index = 0;

	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);


	//	�c
	for (UINT i = 0; i < m_NumBlock_Y + 1; i++)
	{

		Index = i * (m_NumBlock_X + 1);

		//	��
		for (UINT j = 0; j < (m_NumBlock_X + 1) * 2; j++)
		{	
			pVtx[j + Index].Nor = m_Normal;
			pVtx[j + Index].Tex = D3DXVECTOR2((float)j, (float)i + m_TexCoord);//	�e�N�X�`�����W
		}
	}

	//	�o�b�t�@�̃A�����b�N
	m_VertexBuffer->Unlock();
}

/*-----------------------------------------------------------------------------
�C���f�b�N�X�o�b�t�@�̍쐬
-----------------------------------------------------------------------------*/
void TitleBackGround::MakeIndex(LPDIRECT3DDEVICE9 Device)
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

		MessageBox(NULL, "�C���f�b�N�X�o�b�t�@�̐������s", "TitleBackGround.cpp", MB_OK | MB_ICONHAND);
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