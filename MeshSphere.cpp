/*=============================================================================

���b�V����[ MeshSphere.cpp ]

-------------------------------------------------------------------------------
��  Author
	Ohno Takuya

��  Created Date
	2017/05/12
=============================================================================*/

/*-----------------------------------------------------------------------------
	Header
-----------------------------------------------------------------------------*/
#include "FrameworkBase\Common.h"
#include "FrameworkBase\RendererDirectX.h"
#include "FrameworkBase\Game.h"
#include "FrameworkBase\TextureManagerDirectX.h"
#include "Object.h"
#include "MeshSphere.h"

/*-----------------------------------------------------------------------------
	Static
-----------------------------------------------------------------------------*/
LPDIRECT3DTEXTURE9 MeshSphere::m_Texture = NULL;

/*-----------------------------------------------------------------------------
Namespace
-----------------------------------------------------------------------------*/
using namespace std;


MeshSphere::MeshSphere(int Priolity) : Object(Priolity)
{
	m_VertexBuffer = NULL;
	m_IndexBuffer = NULL;

	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_TexturePositon = D3DXVECTOR2(0.0f, 0.0f);

	m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

	m_NumBlock_X = 0;
	m_NumBlock_Y = 0;
	m_NumVertex = 0;
	m_NumIndexBuffer = 0;

	m_Radius = 0.0f;

	m_IndexBackDraw = IDXBACK_DRAW_CLOCKWISE;

}

MeshSphere *MeshSphere::Create(D3DXVECTOR3 Pos, UINT NumBlock_X, UINT NumBlock_Y, float Radius, IDXBACK_DRAW IdxBack, char* TexturePath, D3DXCOLOR color)
{
	auto *object = new MeshSphere;

	object->SetPosition( Pos );

	object->m_NumBlock_X = NumBlock_X;
	object->m_NumBlock_Y = NumBlock_Y;

	object->SetVertexCount(NumBlock_X, NumBlock_Y);

	object->SetIndexBufferCount(NumBlock_X, NumBlock_Y);

	object->m_IndexBackDraw = IdxBack;

	object->m_TexturePath = TexturePath;

	object->m_Radius = Radius;

	object->m_Color = color;


	object->Initialize();

	return object;
}

void MeshSphere::Initialize(void)
{
	LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();

	MakeVerTex(Device);

	MakeIndex(Device);

	SetObjeType(OBJECT_TYPEMESHSPHERE);
}

void MeshSphere::Uninitialize(void)
{
	SAFE_RELEASE(m_VertexBuffer);

	SAFE_RELEASE(m_IndexBuffer);

	Object::Release();	//	�I�u�W�F�N�g���g�̉��
}

void MeshSphere::Draw(void)
{
	LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();


	Device->SetStreamSource(0, m_VertexBuffer, 0, sizeof(VERTEX_3D));

	Device->SetIndices(m_IndexBuffer);

	Device->SetFVF(FVF_VERTEX_3D);

	TextureManagerDirectX* manager = Game::GetInstance()->GetTextureManager();
	LPDIRECT3DTEXTURE9 texture = manager->GetTextureInfo(m_TexturePath).Texture;

	Device->SetTexture(0, texture);

	WorldTransform(Device);

	Device->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_NumIndexBuffer, 0, m_NumIndexBuffer - 2);
}

/*-----------------------------------------------------------------------------
���_�̍쐬
-----------------------------------------------------------------------------*/
void MeshSphere::MakeVerTex(LPDIRECT3DDEVICE9 Device)
{

	if (FAILED(Device->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * m_NumVertex, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_VertexBuffer, NULL)))
	{
		MessageBox(NULL, "���_�o�b�t�@�̐����G���[", "MeshSphere.cpp", MB_OK | MB_ICONHAND);
	}


	//	���z�A�h���X���擾����|�C���^�ϐ�
	VERTEX_3D* pVtx;

	//	���W�̊i�[�ϐ�
	D3DXVECTOR3 Pos;


	//	360�x�̈���̊p�x���߂�
	float Rot_XZ = 360.0f / m_NumBlock_X;

	//	180�x�̈���̊p�x���߂�
	float Rot_Y = 180.0f / m_NumBlock_Y;

	//	���UV���W�����߂�
	m_TexturePositon.x = 1.0f / m_NumBlock_X;
	m_TexturePositon.y = 1.0f / m_NumBlock_Y;


	//	�o�b�t�@�����b�N�����z�A�h���X���擾����
	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

	//	�c
	for (UINT Cnt1 = 0; Cnt1 < m_NumBlock_Y + 1; Cnt1++)
	{

		//	�p�x�̐ݒ�
		float ��y = 90 - (Cnt1 * Rot_Y);

		//	�ŏ���90�x���狁�߂�
		//	90�x��������Ă���
		Pos.y = m_Radius * sinf(D3DXToRadian(��y));

		//	��
		for (UINT Cnt2 = 0; Cnt2 < m_NumBlock_X + 1; Cnt2++)
		{
			//	�p�x�̐ݒ�
			float ��xz = Cnt2 * Rot_XZ;

			//	XZ����360�x���߂�
			Pos.x = m_Radius * cosf(D3DXToRadian(��y)) * cosf(D3DXToRadian(��xz));
			Pos.z = m_Radius * cosf(D3DXToRadian(��y)) * sinf(D3DXToRadian(��xz));


			//	���_���W�̐ݒ�
			pVtx[0].Pos = Pos;


			//	�@���̐ݒ�
			pVtx[0].Nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);


			//	���_�F�̐ݒ�
			pVtx[0].Color = m_Color;


			//	�e�N�X�`�����W�̐ݒ�
			pVtx[0].Tex = D3DXVECTOR2(Cnt2 * m_TexturePositon.x, Cnt1 * m_TexturePositon.y);

			pVtx++;	//	�|�C���^�����炷

		}
	}

	//	�o�b�t�@�̃A�����b�N
	m_VertexBuffer->Unlock();

}

/*-----------------------------------------------------------------------------
���_�̕ύX
-----------------------------------------------------------------------------*/
void MeshSphere::SetVerTex(void)
{
	//	���z�A�h���X���擾����|�C���^�ϐ�
	VERTEX_3D* pVtx;

	//	���UV���W�����߂�
	m_TexturePositon.x = 1.0f / m_NumBlock_X;
	m_TexturePositon.y = 1.0f / m_NumBlock_Y;


	//	�o�b�t�@�����b�N�����z�A�h���X���擾����
	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

	//	�c
	for (UINT Cnt1 = 0; Cnt1 < m_NumBlock_Y + 1; Cnt1++)
	{
		//	��
		for (UINT Cnt2 = 0; Cnt2 < m_NumBlock_X + 1; Cnt2++)
		{
			pVtx[0].Color = m_Color;//	���_�F

			pVtx[0].Tex = D3DXVECTOR2(Cnt2 * m_TexturePositon.x, Cnt1 * m_TexturePositon.y);//	�e�N�X�`�����W

			pVtx++;	//	�|�C���^�����炷

		}
	}

	//	�o�b�t�@�̃A�����b�N
	m_VertexBuffer->Unlock();
}

/*-----------------------------------------------------------------------------
�C���f�b�N�X�o�b�t�@�̍쐬
-----------------------------------------------------------------------------*/
void MeshSphere::MakeIndex(LPDIRECT3DDEVICE9 Device)
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
		MessageBox(NULL, "�C���f�b�N�X�o�b�t�@�̐������s", "MeshSpere.cpp", MB_OK | MB_ICONHAND);
	}


	//	�C���f�b�N�X�o�b�t�@�����b�N
	m_IndexBuffer->Lock(0, 0, (void**)&pIdx, 0);


	//	���v���
	if (m_IndexBackDraw == IDXBACK_DRAW_CLOCKWISE)
	{

		//	���v���𗠖ʂƂ���
		//	�c
		for (UINT Cnt1 = 0; Cnt1 < m_NumBlock_Y; Cnt1++)
		{

			//	�͂��߂���Ȃ�������
			//	�k�ރ|���S��
			if (Cnt1 != 0){

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
	}
	else{

		//	�t���v���𗠖ʂƂ���
		//	�c
		for (UINT Cnt1 = 0; Cnt1 < m_NumBlock_Y; Cnt1++)
		{
			//	�͂��߂���Ȃ�������
			//	�k�ރ|���S��
			if (Cnt1 != 0)
			{
				//	1�_�ł�

				pIdx[0] = (WORD)((Cnt1 + 1) * (m_NumBlock_X + 1) - 1);

				pIdx++;	//	�|�C���^�����炷

			}

			//	2�_�ł�
			pIdx[1] = (WORD)((Cnt1 + 1) * (m_NumBlock_X + 1));
			pIdx[0] = (WORD)((Cnt1 + 1) * (m_NumBlock_X + 1) - (m_NumBlock_X + 1));

			pIdx += 2;	//	�|�C���^�����炷

			//	��
			for (UINT Cnt2 = 0; Cnt2 < m_NumBlock_X; Cnt2++)
			{
				//	2�_�ł�
				pIdx[1] = (WORD)(((Cnt1 + 1) * (m_NumBlock_X + 1) + 1) + Cnt2);
				pIdx[0] = (WORD)(((Cnt1 + 1) * (m_NumBlock_X + 1) + 1) - (m_NumBlock_X + 1) + Cnt2);

				pIdx += 2;	//	�|�C���^�����炷

			}

			//	�Ōザ��Ȃ�������
			//	�k�ރ|���S��
			if (Cnt1 != m_NumBlock_Y - 1)
			{
				//	1�_�ł�
				pIdx[0] = (WORD)((Cnt1 + 1) * (m_NumBlock_X + 1));

				pIdx++;	//	�|�C���^�����炷

			}
		}
	}

	//	�C���f�b�N�X�o�b�t�@�̃A�����b�N
	m_IndexBuffer->Unlock();

}

/*-----------------------------------------------------------------------------
���[���h���W�ϊ�
-----------------------------------------------------------------------------*/
void MeshSphere::WorldTransform(LPDIRECT3DDEVICE9 Device)
{
	D3DXVECTOR3 Position = Object::GetPosition();


	D3DXMATRIX matrixScale, matrixRotation, matrixPosision;

	D3DXMatrixIdentity(&m_MatrixWorld);	//	�s���P�ʍs��ɂ���


	//	�g��s������
	D3DXMatrixScaling(&matrixScale,	//�g��s��
		1.0f,	//	X���g��
		1.0f,	//	Y���g��
		1.0f);	//	Z���g��

	//	��]�s������
	D3DXMatrixRotationYawPitchRoll(&matrixRotation,	//	��]�s��
		D3DXToRadian(m_Rotation.y), //	Y����]
		D3DXToRadian(m_Rotation.x), //	X����]
		D3DXToRadian(m_Rotation.z)); //	Z����]

	//	���s�ړ��s������
	D3DXMatrixTranslation(&matrixPosision,
		Position.x,	//	X���ړ�
		Position.y,	//	Y���ړ�
		Position.z);	//	Z���ړ�


	//	�|����
	D3DXMatrixMultiply(&m_MatrixWorld, &m_MatrixWorld, &matrixScale);
	D3DXMatrixMultiply(&m_MatrixWorld, &m_MatrixWorld, &matrixRotation);
	D3DXMatrixMultiply(&m_MatrixWorld, &m_MatrixWorld, &matrixPosision);

	//	�f�o�C�X�Ƀ��[���h�ϊ��s���ݒ�
	Device->SetTransform(D3DTS_WORLD, &m_MatrixWorld);

}

/*-----------------------------------------------------------------------------
���_���̌v�Z
-----------------------------------------------------------------------------*/
void MeshSphere::SetVertexCount(const UINT NumBlock_X, const UINT NumBlock_Y)
{
	m_NumVertex = (NumBlock_X + 1) * (NumBlock_Y + 1);
}

/*-----------------------------------------------------------------------------
�C���f�b�N�X�o�b�t�@�̌v�Z
-----------------------------------------------------------------------------*/
void MeshSphere::SetIndexBufferCount(const UINT NumBlock_X, const UINT NumBlock_Y)
{
	m_NumIndexBuffer = (2 + 2 * NumBlock_X) * NumBlock_Y + (NumBlock_Y - 1) * 2;
}

/*-----------------------------------------------------------------------------
�����̃Z�b�g
-----------------------------------------------------------------------------*/
void MeshSphere::SetNumBlock(const UINT numBlockX, const UINT numBlockY)
{
	m_NumBlock_X = numBlockX;
	m_NumBlock_Y = numBlockY;
}
