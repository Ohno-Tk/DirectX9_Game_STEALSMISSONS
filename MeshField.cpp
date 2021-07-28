/*=============================================================================

���b�V���t�B�[���h[ MeshField.cpp ]

-------------------------------------------------------------------------------

��  Created Date
	2017/06/13
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
#include "MeshField.h"

/*-----------------------------------------------------------------------------
Macro
-----------------------------------------------------------------------------*/
#define MODEL_VERTEXSHADER_PATH (SHADER_PATH"Mesh_Vertex.hlsl")
#define MODEL_PIXELSHADER_PATH (SHADER_PATH"Mesh_Pixel.hlsl")

/*-----------------------------------------------------------------------------
	Static
-----------------------------------------------------------------------------*/
LPDIRECT3DTEXTURE9 MeshField::m_Texture = NULL;	// �e�N�X�`��

/*-----------------------------------------------------------------------------
Namespace
-----------------------------------------------------------------------------*/
using namespace std;


MeshField::MeshField(int Priolity) : Object(Priolity)
{
	m_VertexBuffer = NULL;
	m_IndexBuffer = NULL;

	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_TexturePositon = D3DXVECTOR2(0.0f, 0.0f);

	m_NumBlock_X = 0;
	m_NumBlock_Y = 0;
	m_NumVertex = 0;
	m_NumIndexBuffer = 0;

	m_IndexBackDraw = IDXBACK_DRAW_CLOCKWISE;
}

MeshField* MeshField::Create(D3DXVECTOR3 Pos, UINT NumBlock_X, UINT NumBlock_Z, float SizeBlock_X, float SizeBlock_Z, char* tecturePath)
{
	auto *object = new MeshField;

	object->SetPosition( Pos );

	object->m_NumBlock_X = NumBlock_X;
	object->m_NumBlock_Y = NumBlock_Z;

	object->SetVertexCount( NumBlock_X , NumBlock_Z );
	object->SetIndexBufferCount( NumBlock_X , NumBlock_Z );

	object->m_IndexBackDraw = IDXBACK_DRAW_CLOCKWISE;

	object->m_SizeBlock_X = SizeBlock_X;
	object->m_SizeBlock_Z = SizeBlock_Z;

	object->m_TexturePath = tecturePath;

	object->Initialize();

	return object;
}

void MeshField::Initialize(void)
{
	LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();
		
	MakeVerTex(Device);

	MakeIndex(Device);

	m_VertexShader = new VertexShader;
	m_VertexShader->Initialize(MODEL_VERTEXSHADER_PATH);

	m_PixelShader = new PixelShader;
	m_PixelShader->Initialize(MODEL_PIXELSHADER_PATH);

}

void MeshField::Uninitialize(void)
{
	SAFE_RELEASE(m_VertexBuffer);

	SAFE_RELEASE(m_IndexBuffer);

	SAFE_UNINIT(m_VertexShader);
	SAFE_UNINIT(m_PixelShader);

	Object::Release();	//	�I�u�W�F�N�g���g�̉��
}

void MeshField::Draw(void)
{
	LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();


	D3DVERTEXELEMENT9 elements[] = {
	{0 ,0 ,D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
	{0 ,12 ,D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
	{0 ,24 ,D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
	D3DDECL_END()
	};
	Device->CreateVertexDeclaration(elements,&m_VertexDeclaration);

	Device->SetStreamSource(0, m_VertexBuffer, 0, sizeof(VERTEX_3D));

	Device->SetIndices(m_IndexBuffer);

	Device->SetFVF(FVF_VERTEX_3D);

	UINT samplerIndex0 = m_PixelShader->GetPixelShaderConstantTable()->GetSamplerIndex("sampler0");
	Device->SetTexture(samplerIndex0, Game::GetInstance()->GetTextureManager()->GetTextureInfo(m_TexturePath).Texture);

	WorldTransform(Device);
	ConfigShader(Device);

	Device->SetVertexShader(m_VertexShader->GetVertexShader());
	Device->SetPixelShader(m_PixelShader->GetPixelShader());

	Device->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_NumIndexBuffer, 0, m_NumIndexBuffer - 2);

}

/*-----------------------------------------------------------------------------
���_�̍쐬
-----------------------------------------------------------------------------*/
void MeshField::MakeVerTex(LPDIRECT3DDEVICE9 Device)
{

	if (FAILED(Device->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * m_NumVertex, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_VertexBuffer, NULL)))
	{
		MessageBox(NULL, "���_�o�b�t�@�̐����G���[", "MeshField.cpp", MB_OK | MB_ICONHAND);
	}

	
	// �\���̂̃|�C���^�錾
	VERTEX_3D* pVtx;

	D3DXVECTOR3 position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	���_���W

	D3DXVECTOR3 Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		//	�@���̌v�Z����
	D3DXVECTOR3 Normal_X = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	X���W�@��
	D3DXVECTOR3 Normal_Z = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	Z���W�@��

	D3DXVECTOR3 Direction_X = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 Direction_Z = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	int Index = 0;


	//	���UV���W�����߂�
	m_TexturePositon.x = 1.0f / m_NumBlock_X;
	m_TexturePositon.y = 1.0f / m_NumBlock_Y;


	//	�o�b�t�@�����b�N�����z�A�h���X���擾����
	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);


	//	�c
	for (UINT i = 0; i < m_NumBlock_Y + 1; i++)
	{

		Index = i * (m_NumBlock_X + 1 );

		//	��
		for (UINT j = 0; j < (m_NumBlock_X + 1) * 2; j++)
		{

			//	���W�̐ݒ�
			position.x = (m_SizeBlock_X * m_NumBlock_X / 2) - m_NumBlock_X * m_SizeBlock_X + (m_SizeBlock_X * j);
			position.y = 0.0f;
			position.z = (m_SizeBlock_Z * m_NumBlock_Y / 2) - (m_SizeBlock_Z * i);


			//	���_���W�̐ݒ�
			pVtx[j + Index].Pos = position;

			pVtx[j + Index].Nor = D3DXVECTOR3(0.0f,1.0f,0.0f);


			//	���_�F�̐ݒ�
			pVtx[j + Index].Color = D3DCOLOR_RGBA(255, 255, 255, 255);


			//	�e�N�X�`�����W�̐ݒ�
			pVtx[j + Index].Tex = D3DXVECTOR2((float)j, (float)i);

		}
	}


	//	�@���̌v�Z
	//	�c
/*	for (UINT i = 1; i <= m_NumBlock_Y; i++)
	{

		Index = i * (m_NumBlock_X + 1);

		//	��
		for (UINT j = 1; j <= m_NumBlock_X; j++)
		{

			//	X���@��( �I�_����n�_������ )
			Direction_X = pVtx[j + Index + 1].Pos - pVtx[j + Index - 1].Pos;
			
			//	y��x�ɑ΂���@���x�N�g��
/*			Normal_X.x = -Direction_X.y;
			Normal_X.y = Direction_X.x;
			Normal_X.z = 0.0f;

			//	Z���@��( �I�_����n�_������ )
			Direction_Z = pVtx[j + Index - m_NumBlock_X].Pos - pVtx[j + Index + m_NumBlock_X].Pos;
			
			//	y��z�ɑ΂���@���x�N�g��
			Normal_Z.x = 0.0f;
			Normal_Z.y = Direction_Z.z;
			Normal_Z.z = -Direction_Z.y;

			//	�x�N�g���̍���
			Normal = Normal_X + Normal_Z;

			//	�P�ʍs��ɂ���
			D3DXVec3Normalize(&Normal, &Normal);


			//	�@���̐ݒ�
			pVtx[j + Index].Nor = Normal;

		}
	}*/

	//	�o�b�t�@�̃A�����b�N
	m_VertexBuffer->Unlock();

}

/*-----------------------------------------------------------------------------
�C���f�b�N�X�o�b�t�@�̍쐬
-----------------------------------------------------------------------------*/
void MeshField::MakeIndex(LPDIRECT3DDEVICE9 Device)
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
		MessageBox(NULL, "�C���f�b�N�X�o�b�t�@�̐������s", "MeshField.cpp", MB_OK | MB_ICONHAND);
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

			}	//	end of for

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
			if (Cnt1 != 0){
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
void MeshField::WorldTransform(LPDIRECT3DDEVICE9 Device)
{
	D3DXVECTOR3 Position = Object::GetPosition();


	D3DXMATRIX matrixScale, matrixRotation, matrixPosision;

	D3DXMatrixIdentity(&m_MatrixWorld);	//	�s���P�ʍs��ɂ���


	//	�g��s������
	D3DXMatrixScaling(&matrixScale,	//�g��s�񂪍����
		1.0f,	//	X���g��
		1.0f,	//	Y���g��
		1.0f);	//	Z���g��

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


	//	�|���Ă�����
	D3DXMatrixMultiply(&m_MatrixWorld, &m_MatrixWorld, &matrixScale);
	D3DXMatrixMultiply(&m_MatrixWorld, &m_MatrixWorld, &matrixRotation);
	D3DXMatrixMultiply(&m_MatrixWorld, &m_MatrixWorld, &matrixPosision);
}

void MeshField::ConfigShader(LPDIRECT3DDEVICE9 device)
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
						  D3DXVECTOR3(-90.0f, 30.0f, -115.0f), D3DXVECTOR3(21.0f, 30.0f, -115.0f), D3DXVECTOR3(125.0f, 30.0f, -115.0f)};
	pixelShaderConstantTable->SetValue(device, "LightPosW", Pos, sizeof(Pos));
	pixelShaderConstantTable->SetValue(device, "CameraEyeW", Game::GetInstance()->GetCamera()->GetPositionEye(), sizeof(D3DXVECTOR3));
}

/*-----------------------------------------------------------------------------
����Ă��鉚�ʂ̍����擾
-----------------------------------------------------------------------------*/
float MeshField::GetHeight(D3DXVECTOR3 Position)
{

	// �\���̂̃|�C���^�錾
	VERTEX_3D* pVtx;

	// �|���S��3���_�p
	D3DXVECTOR3 P0 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	�����̒��_
	D3DXVECTOR3 P1 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	�����̏�̒��_
	D3DXVECTOR3 P2 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	�����ׂ̗̒��_

	// ���_�����_
	D3DXVECTOR3 v01 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	���_�̏c�̃x�N�g��
	D3DXVECTOR3 v12 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	���_�̉��̃x�N�g��
	D3DXVECTOR3 v20 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	���_�̎΂߂̃x�N�g��
	
	//	���_����v���C���[�̃x�N�g��
	D3DXVECTOR3 v0P = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 v1P = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 v2P = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	//	1�s�̒��_��
	int NumLineVertex = m_NumBlock_X + 1;


	//	�o�b�t�@�����b�N�����z�A�h���X���擾����
	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);


	//	�c
	for (UINT i = 0; i <= m_NumBlock_Y; i++)
	{

		//	��
		for (UINT j = 0; j <= m_NumBlock_X; j++)
		{

			/*-------------------------------------
						  1�|���S��
			-------------------------------------*/		
			//	�|���S����3���_�����߂�
			P0 = pVtx[NumLineVertex * (i + 1) + j].Pos;
			P1 = pVtx[NumLineVertex * i + j].Pos;
			P2 = pVtx[NumLineVertex * (i + 1) + (j + 1)].Pos;

			// vc0���߂�
			v01 = P1 - P0;
			v0P = Position - P0;

			D3DXVECTOR3 VC0 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �@���x�N�g���p
			D3DXVec3Cross(&VC0, &v01, &v0P);

			//	Position���O�p�`�|���S���̒��ɂ��邩�̔���
			if( VC0.y >= 0.0f )
			{

				// vc1���߂�
				v12 = P2 - P1;
				v1P = Position - P1;

				D3DXVECTOR3 VC1 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �@���x�N�g���p
				D3DXVec3Cross(&VC1, &v12, &v1P);

				if( VC1.y >= 0.0f )
				{

					// vc2���߂�
					v20 = P0 - P2;
					v2P = Position - P2;

					D3DXVECTOR3 VC2 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �@���x�N�g���p
					D3DXVec3Cross(&VC2, &v20, &v2P);

					if( VC2.y >= 0.0f )
					{

						//	�@���̌v�Z
						D3DXVECTOR3 N = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	�@��
						D3DXVECTOR3 V01 = P1 - P0;
						D3DXVECTOR3 V02 = P2 - P0;
						D3DXVec3Cross(&N, &v01, &V02);
						D3DXVec3Normalize(&N, &N);	//	�P�ʃx�N�g���ɕϊ�

						//	�����̌v�Z
						Position.y = P0.y - ((Position.x - P0.x) * N.x + (Position.z - P0.z) * N.z) / N.y;

						//	�o�b�t�@�̃A�����b�N
						m_VertexBuffer->Unlock();

						return Position.y;
						
					}
				}
			}

			/*-------------------------------------
						  2�|���S��
			-------------------------------------*/
			//	�|���S����3���_�����߂�
			P0 = pVtx[NumLineVertex * i + (j + 1)].Pos;
			P1 = pVtx[NumLineVertex * (i + 1) + (j + 1)].Pos;
			P2 = pVtx[NumLineVertex * i + j].Pos;

			// vc0���߂�
			v01 = P1 - P0;
			v0P = Position - P0;

			D3DXVec3Cross(&VC0, &v01, &v0P);

			//	���W���O�p�`�|���S���̒��ɂ��邩�̔���
			if( VC0.y >= 0.0f ){

				// vc1���߂�
				v12 = P2 - P1;
				v1P = Position - P1;

				D3DXVECTOR3 VC1 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				D3DXVec3Cross(&VC1, &v12, &v1P);

				if( VC1.y >= 0.0f )
				{

					// vc2���߂�
					v20 = P0 - P2;
					v2P = Position - P2;

					D3DXVECTOR3 VC2 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					D3DXVec3Cross(&VC2, &v20, &v2P);

					if( VC2.y >= 0.0f )
					{

						//	�@���̌v�Z
						D3DXVECTOR3 N = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	�@��
						D3DXVECTOR3 V01 = P1 - P0;
						D3DXVECTOR3 V02 = P2 - P0;
						D3DXVec3Cross(&N, &v01, &V02);
						D3DXVec3Normalize(&N, &N);	//	�P�ʃx�N�g���ɕϊ�

						//	�����̌v�Z
						Position.y = P0.y - ((Position.x - P0.x) * N.x + (Position.z - P0.z) * N.z) / N.y;

						//	�o�b�t�@�̃A�����b�N
						m_VertexBuffer->Unlock();

						return Position.y;
						
					}
				}
			}
		}
	}

	//	�o�b�t�@�̃A�����b�N
	m_VertexBuffer->Unlock();

	return 0;
}

/*-----------------------------------------------------------------------------
���_���̌v�Z
-----------------------------------------------------------------------------*/
void MeshField::SetVertexCount(const UINT NumBlock_X, const UINT NumBlock_Y)
{
	m_NumVertex = (NumBlock_X + 1) * (NumBlock_Y + 1);
}

/*-----------------------------------------------------------------------------
�C���f�b�N�X�o�b�t�@�̌v�Z
-----------------------------------------------------------------------------*/
void MeshField::SetIndexBufferCount(const UINT NumBlock_X, const UINT NumBlock_Y)
{
	m_NumIndexBuffer = (2 + 2 * NumBlock_X) * NumBlock_Y + (NumBlock_Y - 1) * 2;
}