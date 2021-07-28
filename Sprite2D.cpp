/*=============================================================================

2D�`��[ Sprite2D.cpp ]

-------------------------------------------------------------------------------

��  Create
2017/11/17
=============================================================================*/

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "FrameworkBase\Common.h"
#include "FrameworkBase\RendererDirectX.h"
#include "FrameworkBase\Game.h"
#include "FrameworkBase\TextureManagerDirectX.h"
#include "Object.h"
#include "Sprite2D.h"

/*-----------------------------------------------------------------------------
Namespace
-----------------------------------------------------------------------------*/
using namespace std;


Sprite2D::Sprite2D(int Priolity):Object(Priolity)
{
	m_VertexBuffer = NULL;

	m_Size = D3DXVECTOR2(0.0f,0.0f);
	m_Color = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
}

/*-----------------------------------------------------------------------------
Function:   Sprite2D* Sprite2D::Create(D3DXVECTOR3 position, D3DXVECTOR2 size, char* texturePath,D3DXVECTOR4 color, int priolity)
Parameter:  D3DXVECTOR3 positon
              ���W
            D3DXVECTOR2 size
			  �傫��
            char* texturePath
			  �e�N�X�`���̃p�X
			 D3DXVECTOR4 color
			  �F
			int priolity
			  �D��x
Overview:   ����
-----------------------------------------------------------------------------*/
Sprite2D* Sprite2D::Create(D3DXVECTOR3 position, D3DXVECTOR2 size, char* texturePath, D3DXVECTOR4 color, int priolity)
{
	auto object = new Sprite2D(priolity);

	object->SetPosition(position);
	object->m_Size = size;
	object->m_TexturePath = texturePath;
	object->m_Color = (D3DXCOLOR)color;

	object->Initialize();

	return object;
}

void Sprite2D::Initialize(void)
{
	LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();

	MakeVertex(Device);
}

void Sprite2D::Uninitialize(void)
{
	SAFE_RELEASE(m_VertexBuffer);

	Object::Release();
}

void Sprite2D::Update(void)
{
	SetVertex();
}

void Sprite2D::Draw(void)
{
	LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();


	Device->SetVertexShader(NULL);
	Device->SetPixelShader(NULL);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	Device->SetStreamSource(0, m_VertexBuffer, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	Device->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	Device->SetTexture(0, Game::GetInstance()->GetTextureManager()->GetTextureInfo(m_TexturePath).Texture);

	// �`��
	Device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

void Sprite2D::MakeVertex(LPDIRECT3DDEVICE9 Device)
{
	D3DXVECTOR3 position = Object::GetPosition();


	// ���_�o�b�t�@�̐���
	if (FAILED(Device->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_VertexBuffer, NULL)))
	{
		MessageBox(NULL, "���_�o�b�t�@�̐����Ɏ��s", "Sprite2D.cpp", MB_OK | MB_ICONHAND);
	}

	// ���_����ݒ�
	VERTEX_2D* Vtx;

	// �o�b�t�@�����b�N���A���z�A�h���X���擾
	m_VertexBuffer->Lock(0, 0, (void**)&Vtx, 0);

	//	���_���W
	Vtx[0].Pos = D3DXVECTOR3(position.x           , position.y, 0.0f);
	Vtx[1].Pos = D3DXVECTOR3(position.x + m_Size.x, position.y, 0.0f);
	Vtx[2].Pos = D3DXVECTOR3(position.x           , position.y + m_Size.y, 0.0f);
	Vtx[3].Pos = D3DXVECTOR3(position.x + m_Size.x, position.y + m_Size.y, 0.0f);

	for(unsigned int CountVertex = 0; CountVertex < NUM_VERTEX; CountVertex++)
	{
		Vtx[CountVertex].Rhw = 1.0f;//	���W�ϊ��ςݒ��_�t���O
		Vtx[CountVertex].Color = m_Color;// ���_�J���[
	}

	// �e�N�X�`�����W
	Vtx[0].Tex = D3DXVECTOR2(0, 0);
	Vtx[1].Tex = D3DXVECTOR2(1, 0);
	Vtx[2].Tex = D3DXVECTOR2(0, 1);
	Vtx[3].Tex = D3DXVECTOR2(1, 1);

	//	�o�b�t�@���A�����b�N
	m_VertexBuffer->Unlock();

}

void Sprite2D::SetVertex(void)
{
	D3DXVECTOR3 position = Object::GetPosition();


	VERTEX_2D* Vtx;

	m_VertexBuffer->Lock(0, 0, (void**)&Vtx, 0);

	//	���_���W
	Vtx[0].Pos = D3DXVECTOR3(position.x           , position.y, 0.0f);
	Vtx[1].Pos = D3DXVECTOR3(position.x + m_Size.x, position.y, 0.0f);
	Vtx[2].Pos = D3DXVECTOR3(position.x           , position.y + m_Size.y, 0.0f);
	Vtx[3].Pos = D3DXVECTOR3(position.x + m_Size.x, position.y + m_Size.y, 0.0f);

	for(unsigned int CountVertex = 0; CountVertex < NUM_VERTEX; CountVertex++)
	{
		Vtx[CountVertex].Color = m_Color;// ���_�J���[
	}


	//	�o�b�t�@���A�����b�N
	m_VertexBuffer->Unlock();

}