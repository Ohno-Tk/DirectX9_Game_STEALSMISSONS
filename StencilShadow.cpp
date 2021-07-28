/*=============================================================================

�X�e���V���V���h�E[ StencilShadow.cpp ]

-------------------------------------------------------------------------------

��  Create
	2017/11/09
=============================================================================*/

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "FrameworkBase\Common.h"
#include "FrameworkBase\RendererDirectX.h"
#include "FrameworkBase\Game.h"
#include "FrameworkBase\ModelManagerDirectX.h"
#include "Object.h"
#include "StencilShadow.h"

/*-----------------------------------------------------------------------------
Function:   StencilShadow* StencilShadow::Create(char* modelFileName)
Parameter:  char* modelFileName
              ���f���̃t�@�C����
Overview:   ����
-----------------------------------------------------------------------------*/
StencilShadow* StencilShadow::Create(char* modelFileName)
{
	auto object = new StencilShadow;

	object->m_ModelFilePath = modelFileName;

	object->Initialize();

	return object;
}

void StencilShadow::Initialize(void)
{
	MakeVerTex(); // ���_�̍쐬
}

void StencilShadow::Uninitialize(void)
{
	SAFE_RELEASE(m_VertexBuffer);

	Object::Release();	//	�I�u�W�F�N�g���g�̉��
}

void StencilShadow::Draw(void)
{
	LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();

	Device->SetVertexShader(NULL);
	Device->SetPixelShader(NULL);
	
	//	���[���h���W�ϊ�
	WorldTransform(Device);
	
	// �\�ʕ`��
	Device->SetRenderState(D3DRS_STENCILENABLE, TRUE);
	Device->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	Device->SetRenderState(D3DRS_COLORWRITEENABLE, 0);
	Device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
	Device->SetRenderState(D3DRS_STENCILREF, 1);
	Device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);
	Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	
	ModelDraw(Device);
	
	// ���ʕ`��
	Device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_DECR);
	Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	
	ModelDraw(Device);
	
	Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	Device->SetRenderState(D3DRS_COLORWRITEENABLE, 0xf);
	Device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
	
	// 2D�|���S���`��
	Polygon2DDraw( Device);
	
	Device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	Device->SetRenderState(D3DRS_STENCILENABLE, FALSE);
}

/*-----------------------------------------------------------------------------
Function:   void StencilShadow::ModelDraw(LPDIRECT3DDEVICE9 Device)
Parameter:  LPDIRECT3DDEVICE9 Device
              �f�o�C�X
Overview:   ���f���`��
-----------------------------------------------------------------------------*/
void StencilShadow::ModelDraw(LPDIRECT3DDEVICE9 Device)
{
	D3DMATERIAL9 materialDefault;

	ModelManagerDirectX* ModelManager = Game::GetInstance()->GetModelManager();

	// ���f���̎擾
	m_ModelParam = ModelManager->GetModelParam(m_ModelFilePath);

	WorldTransform(Device);

	//	���݃f�o�C�X�ɐݒ肳��Ă���}�e���A�����̎擾
	Device->GetMaterial(&materialDefault);

	// ���݂̃}�e���A�����擾
	Device->GetMaterial(&materialDefault);

	// �}�e���A���ւ̃|�C���^���擾
	m_ModelParam.Material = (D3DXMATERIAL*)m_ModelParam.BufferMaterial->GetBufferPointer();

	for (int CountMaterial = 0; CountMaterial < (int)m_ModelParam.NumMaterial; CountMaterial++)
	{
		// �f�o�C�X�Ƀ}�e���A���̐ݒ�
		Device->SetMaterial(&m_ModelParam.Material[CountMaterial].MatD3D);

		// �e�N�X�`���̐ݒ�
		Device->SetTexture(0, m_ModelParam.Texture[CountMaterial]);

		// �`��
		m_ModelParam.Mesh->DrawSubset(CountMaterial);
	}

	// �}�e���A�������ɖ߂�
	Device->SetMaterial(&materialDefault);
}

/*-----------------------------------------------------------------------------
Function:   void StencilShadow::Polygon2DDraw(LPDIRECT3DDEVICE9 Device)
Parameter:  LPDIRECT3DDEVICE9 Device
              �f�o�C�X
Overview:   �S���2D�|���S���`��
-----------------------------------------------------------------------------*/
void StencilShadow::Polygon2DDraw(LPDIRECT3DDEVICE9 Device)
{
	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	Device->SetStreamSource(0, m_VertexBuffer, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	Device->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	Device->SetTexture(0, NULL);

	// �`��
	Device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

/*-----------------------------------------------------------------------------
Function:   void StencilShadow::MakeVerTex(void)
Parameter:  
Overview:   ���_�̍쐬
-----------------------------------------------------------------------------*/
void StencilShadow::MakeVerTex(void)
{
	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();

	// ���_�o�b�t�@�̐���
	if (FAILED(Device->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_VertexBuffer, NULL)))
	{
		MessageBox(NULL, "���_�o�b�t�@�̐����Ɏ��s", "StencilShadow.cpp", MB_OK | MB_ICONHAND);
	}

	// ���_����ݒ�
	VERTEX_2D* pVtx;

	// �o�b�t�@�����b�N���A���z�A�h���X���擾
	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

	//	���_���W
	pVtx[0].Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].Pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].Pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].Pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	for(unsigned int CountVertex = 0; CountVertex < NUM_VERTEX; CountVertex++)
	{
		pVtx[CountVertex].Rhw = 1.0f; //	���W�ϊ��ςݒ��_�t���O
		pVtx[CountVertex].Color = D3DXCOLOR(0.0f,0.0f,0.0f,0.4f); // ���_�J���[
	}

	// �e�N�X�`�����W
	pVtx[0].Tex = D3DXVECTOR2(0, 0);
	pVtx[1].Tex = D3DXVECTOR2(1, 0);
	pVtx[2].Tex = D3DXVECTOR2(0, 1);
	pVtx[3].Tex = D3DXVECTOR2(1, 1);

	//	�o�b�t�@���A�����b�N
	m_VertexBuffer->Unlock();
}

/*-----------------------------------------------------------------------------
Function:   void StencilShadow::WorldTransform(LPDIRECT3DDEVICE9 Device)
Parameter:  LPDIRECT3DDEVICE9 Device
              �f�o�C�X
Overview:   �S���2D�|���S���`��
-----------------------------------------------------------------------------*/
void StencilShadow::WorldTransform(LPDIRECT3DDEVICE9 Device)
{
	D3DXMATRIX matrixPosition;

	D3DXVECTOR3 position = Object::GetPosition();

	D3DXMatrixIdentity(&m_MatrixWorld);

	D3DXMatrixTranslation(&matrixPosition,
		position.x,	//	X���ړ�
		position.y,	//	Y���ړ�
		position.z);	//	Z���ړ�

	D3DXMatrixMultiply(&m_MatrixWorld, &m_MatrixWorld, &matrixPosition);

	Device->SetTransform(D3DTS_WORLD, &m_MatrixWorld);
}