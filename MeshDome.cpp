/*=============================================================================

���b�V������[ MeshDome.cpp ]

-------------------------------------------------------------------------------

��  Create
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
#include "MeshDome.h"

/*-----------------------------------------------------------------------------
	Static
-----------------------------------------------------------------------------*/
LPDIRECT3DTEXTURE9 MeshDome::m_Texture = NULL;	// �e�N�X�`��

/*-----------------------------------------------------------------------------
Namespace
-----------------------------------------------------------------------------*/
using namespace std;


MeshDome::MeshDome(int Priolity) : Object(Priolity)
{
	m_VertexBuffer = NULL;
	m_IndexBuffer = NULL;

	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	m_TexturePositon = D3DXVECTOR2(0.0f, 0.0f);

	m_NumBlock_X = 0;
	m_NumBlock_Y = 0;
	m_NumVertex = 0;
	m_NumIndexBuffer = 0;

	m_Radius = 0.0f;

	m_IndexBackDraw = IDXBACK_DRAW_CLOCKWISE;
}

MeshDome *MeshDome::Create(D3DXVECTOR3 Pos, UINT NumBlock_X, UINT NumBlock_Y, float Radius, IDXBACK_DRAW IdxBack, char* TextureName)
{
	auto object= new MeshDome;

	object->SetPosition( Pos );

	object->SetNumBlock( NumBlock_X , NumBlock_Y );

	object->SetVertexCount( NumBlock_X , NumBlock_Y );

	object->SetIndexBufferCount( NumBlock_X , NumBlock_Y );

	object->SetIndexBackDraw( IdxBack );

	object->SetTexture( TextureName );

	object->m_Radius = Radius;

	object->Initialize();

	return object;
}

void MeshDome::Initialize(void)
{
	LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();
	
	MakeVerTex(Device);
		
	MakeIndex(Device);
}

void MeshDome::Uninitialize(void)
{
	SAFE_RELEASE(m_VertexBuffer);

	SAFE_RELEASE(m_IndexBuffer);

	Object::Release();	//	�I�u�W�F�N�g���g�̉��
}

void MeshDome::Draw(void)
{
	LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();


	Device->SetStreamSource(0, m_VertexBuffer, 0, sizeof(VERTEX_3D));

	Device->SetIndices(m_IndexBuffer);

	Device->SetFVF(FVF_VERTEX_3D);

	TextureManagerDirectX* manager = Game::GetInstance()->GetTextureManager();
	Device->SetTexture(0, manager->GetTextureInfo(m_TexturePath).Texture);

	WorldTransform(Device);

	Device->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_NumIndexBuffer, 0, m_NumIndexBuffer - 2);

}

/*-----------------------------------------------------------------------------
���_�̍쐬
-----------------------------------------------------------------------------*/
void MeshDome::MakeVerTex(LPDIRECT3DDEVICE9 Device)
{

	if (FAILED(Device->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * m_NumVertex, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_VertexBuffer, NULL)))
	{
		MessageBox(NULL, "���_�o�b�t�@�̐����G���[", "MeshDome.cpp", MB_OK | MB_ICONHAND);
	}

	//	���z�A�h���X���擾����|�C���^�ϐ�
	VERTEX_3D* pVtx;

	//	���W�̊i�[�ϐ�
	D3DXVECTOR3 Pos;

	//	360�x�̈���̊p�x���߂�
	float Rot_XZ = 360.0f / m_NumBlock_X;

	//	90�x�̈���̊p�x���߂�
	float Rot_Y = 90.0f / m_NumBlock_Y;

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
			pVtx[0].Nor = D3DXVECTOR3(0.0f, 10.0f, 0.0f);


			//	���_�F�̐ݒ�
			pVtx[0].Color = D3DCOLOR_RGBA(255, 255, 255, 255);


			//	�e�N�X�`�����W�̐ݒ�
			pVtx[0].Tex = D3DXVECTOR2(Cnt2 * m_TexturePositon.x, Cnt1 * m_TexturePositon.y);

			pVtx++;	//	�|�C���^�����炷

		}
	}

	//	�o�b�t�@�̃A�����b�N
	m_VertexBuffer->Unlock();

}

/*-----------------------------------------------------------------------------
�C���f�b�N�X�o�b�t�@�̍쐬
-----------------------------------------------------------------------------*/
void MeshDome::MakeIndex(LPDIRECT3DDEVICE9 Device)
{

	HRESULT hr;

	WORD* pIdx;	//	�|�C���^�ϐ�

	//	�C���f�b�N�X�o�b�t�@�̐���
	hr = Device->CreateIndexBuffer(
		sizeof(WORD) * m_NumIndexBuffer,	//	�o�b�t�@��
		D3DUSAGE_WRITEONLY,	//	�g�p���@�t���O
		D3DFMT_INDEX16, //	�C���f�b�N�X�t�H�[�}�b�g
		D3DPOOL_MANAGED, //	�������̊Ǘ����@
		&m_IndexBuffer,	//	�C���f�b�N�X�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^�̃A�h���X
		NULL);


	//	�C���f�b�N�X�o�b�t�@�̃G���[�`�F�b�N
	if (FAILED(hr))
	{
		MessageBox(NULL, "�C���f�b�N�X�o�b�t�@�̐������s", "Mesh.cpp", MB_OK | MB_ICONHAND);
	}


	//	�C���f�b�N�X�o�b�t�@�����b�N
	m_IndexBuffer->Lock(0, 0, (void**)&pIdx, 0);


	if (m_IndexBackDraw == IDXBACK_DRAW_CLOCKWISE)
	{	//	���v���

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
	}
	else
	{

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
void MeshDome::WorldTransform(LPDIRECT3DDEVICE9 Device)
{
	D3DXVECTOR3 Position = Object::GetPosition();


	D3DXMATRIX matrixScale, matrixRotation, matrixPosision;

	D3DXMatrixIdentity(&m_MatixWorld);	//	�s���P�ʍs��ɂ���


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
	D3DXMatrixTranslation(&matrixPosision,
		Position.x,	//	X���ړ�
		Position.y,	//	Y���ړ�
		Position.z);	//	Z���ړ�


	//	�|����
	D3DXMatrixMultiply(&m_MatixWorld, &m_MatixWorld, &matrixScale);
	D3DXMatrixMultiply(&m_MatixWorld, &m_MatixWorld, &matrixRotation);
	D3DXMatrixMultiply(&m_MatixWorld, &m_MatixWorld, &matrixPosision);

	//	�f�o�C�X�Ƀ��[���h�ϊ��s���ݒ�
	Device->SetTransform(D3DTS_WORLD, &m_MatixWorld);

}