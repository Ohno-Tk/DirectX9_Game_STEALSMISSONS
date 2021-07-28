/*=============================================================================

���b�V���G�t�F�N�g[ MeshEffect.cpp ]

-------------------------------------------------------------------------------

��  Create
2017/11/13
=============================================================================*/

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include <assert.h>
#include "FrameworkBase\Common.h"
#include "FrameworkBase\RendererDirectX.h"
#include "FrameworkBase\Game.h"
#include "FrameworkBase\TextureManagerDirectX.h"
#include "Object.h"
#include "MeshEffect.h"

MeshEffect::MeshEffect(int Priolity):Object(Priolity)
{
	m_VertexBuffer = NULL;
	m_IndexBuffer = NULL;

	m_TopPosition = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_ButtomPosition = D3DXVECTOR3(0.0f,0.0f,0.0f);

	m_TexturePositon = D3DXVECTOR2(0.0f,0.0f);

	m_NumBlock_X = 0;
	m_NumBlock_Y = 1;

	m_NumVertex = 0;
	m_NumIndexBuffer = 0;
}

/*-----------------------------------------------------------------------------
Function:   MeshEffect* MeshEffect::Create(UINT numBlock_X)
Parameter:  UINT numBlock_X
              ���̖���
Overview:   ����
-----------------------------------------------------------------------------*/
MeshEffect* MeshEffect::Create(UINT numBlock_X)
{
	auto object = new MeshEffect;

	object->m_NumBlock_X = numBlock_X;

	object->Initialize();

	return object;
}

void MeshEffect::Initialize(void)
{
	SetVertexCount(m_NumBlock_X, m_NumBlock_Y); // ���_���̌v�Z
	SetIndexBufferCount(m_NumBlock_X, m_NumBlock_Y);   // �C���f�b�N�X�o�b�t�@�̌v�Z


	LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();

	MakeVerTex(Device); // ���_�̍쐬
	MakeIndex(Device);  // �C���f�b�N�X�o�b�t�@�̍쐬

	// ������
	for(int i = 0; i < m_NumVertex; i++)
	{
		m_VertexPosition.push_back(D3DXVECTOR3(0.0f,0.0f,0.0f));
	}
}

void MeshEffect::Uninitialize(void)
{
	m_VertexPosition.clear(); // �v�f�̉��
	std::vector<D3DXVECTOR3>().swap(m_VertexPosition); // �������̉��

	SAFE_RELEASE(m_VertexBuffer);

	SAFE_RELEASE(m_IndexBuffer);

	Object::Release();
}

void MeshEffect::Update(void)
{
	for(unsigned int i = 0; i < m_NumBlock_X; i++)
	{
		m_VertexPosition[i*2] = m_VertexPosition[i*2+2];
		m_VertexPosition[i*2+1] = m_VertexPosition[i*2+3];
	}
	m_VertexPosition[m_NumBlock_X*2] = m_TopPosition;
	m_VertexPosition[m_NumBlock_X*2+1] = m_ButtomPosition;

	SetUpVerTex(); // ���_�̐ݒ�
}

void MeshEffect::Draw(void)
{
	LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();


	Device->SetStreamSource(0, m_VertexBuffer, 0, sizeof(VERTEX_3D));

	Device->SetIndices(m_IndexBuffer);

	Device->SetFVF(FVF_VERTEX_3D);

	auto textureManager = Game::GetInstance()->GetTextureManager();
	Device->SetTexture(0, NULL);

	WorldTransform(Device);

	// �J�����Ooff
	Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	Device->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_NumIndexBuffer, 0, m_NumIndexBuffer - 2);

	// �J�����Oon
	Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

/*-----------------------------------------------------------------------------
Function:   void MeshEffect::MakeVerTex(LPDIRECT3DDEVICE9 Device)
Parameter:  LPDIRECT3DDEVICE9 Device
              �f�o�C�X
Overview:   ���_�̍쐬
-----------------------------------------------------------------------------*/
void MeshEffect::MakeVerTex(LPDIRECT3DDEVICE9 Device)
{
	if (FAILED(Device->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * m_NumVertex, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_VertexBuffer, NULL)))
	{
		MessageBox(NULL, "���_�o�b�t�@�̐����G���[", "MeshEffect.cpp", MB_OK | MB_ICONHAND);
	}
}

/*-----------------------------------------------------------------------------
Function:   void MeshEffect::SetUpVerTex(void)
Overview:   ���_�̐ݒ�
-----------------------------------------------------------------------------*/
void MeshEffect::SetUpVerTex(void)
{
	int Index = 0;
	VERTEX_3D* pVtx;

	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

	//	�c
	for (UINT i = 0; i < m_NumBlock_Y; i++)
	{

		Index = i * (m_NumBlock_X + 1);

		//	��
		for (UINT j = 0; j < (m_NumBlock_X + 1) * 2; j++)
		{
			//	���_���W
			pVtx[j + Index].Pos = m_VertexPosition[j + Index];

			//	�@��
			pVtx[j + Index].Nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//	���_�F
			pVtx[j + Index].Color = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

			//	�e�N�X�`�����W
			pVtx[j + Index].Tex = D3DXVECTOR2((float)j, (float)i);
		}
	}

	m_VertexBuffer->Unlock();
}

/*-----------------------------------------------------------------------------
Function:   void MeshEffect::MakeIndex(LPDIRECT3DDEVICE9 Device)
Parameter:  LPDIRECT3DDEVICE9 Device
              �f�o�C�X
Overview:   �C���f�b�N�X�o�b�t�@�̍쐬
-----------------------------------------------------------------------------*/
void MeshEffect::MakeIndex(LPDIRECT3DDEVICE9 Device)
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
		MessageBox(NULL, "�C���f�b�N�X�o�b�t�@�̐������s", "MeshEffect.cpp", MB_OK | MB_ICONHAND);
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
Function:   void MeshEffect::SetIdxVerTex(const UINT NumBlock_X, const UINT NumBlock_Y)
Parameter:  const UINT NumBlock_X
              ���̖���
            const UINT NumBlock_Y
              �c�̖���
Overview:   ���_���̌v�Z
-----------------------------------------------------------------------------*/
void MeshEffect::SetVertexCount(const UINT NumBlock_X, const UINT NumBlock_Y)
{
	m_NumVertex = (NumBlock_X + 1) * (NumBlock_Y + 1);
}

/*-----------------------------------------------------------------------------
Function:   void MeshEffect::SetIndexBufferCount(const UINT NumBlock_X, const UINT NumBlock_Y)
Parameter:  const UINT NumBlock_X
              ���̖���
            const UINT NumBlock_Y
              �c�̖���
Overview:   �C���f�b�N�X�o�b�t�@�̌v�Z
-----------------------------------------------------------------------------*/
void MeshEffect::SetIndexBufferCount(const UINT NumBlock_X, const UINT NumBlock_Y)
{
	m_NumIndexBuffer = (2 + 2 * NumBlock_X) * NumBlock_Y + (NumBlock_Y - 1) * 2;
}

/*-----------------------------------------------------------------------------
Function:   void MeshEffect::WorldTransform(LPDIRECT3DDEVICE9 Device)
Parameter:  LPDIRECT3DDEVICE9 Device
              �f�o�C�X
Overview:   ���[���h���W�ϊ�
-----------------------------------------------------------------------------*/
void MeshEffect::WorldTransform(LPDIRECT3DDEVICE9 Device)
{
	D3DXMATRIX matrixWorld;

	D3DXMatrixIdentity(&matrixWorld);	//	�s���P�ʍs��ɂ���

	//	�f�o�C�X�Ƀ��[���h�ϊ��s���ݒ�
	Device->SetTransform(D3DTS_WORLD, &matrixWorld);
}