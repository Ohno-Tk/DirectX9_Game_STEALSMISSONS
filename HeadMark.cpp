/*=============================================================================

����}�[�N[ HeadMark.cpp ]

-------------------------------------------------------------------------------

��  Create
2017/11/24
=============================================================================*/

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "FrameworkBase\RendererDirectX.h"
#include "FrameworkBase\Common.h"
#include "FrameworkBase\Game.h"
#include "FrameworkBase\TextureManagerDirectX.h"
#include "FrameworkBase\CameraDirectX.h"
#include "Object.h"
#include "HeadMark.h"


HeadMark::HeadMark(int priolity):Object(priolity),
m_VertexBuffer(NULL),
m_Active(false),
m_Scale(D3DXVECTOR3(1.0f,1.0f,1.0f)),
m_Size(D3DXVECTOR2(6.0f, 8.0f)),
m_TexturePath(TEXTURE_PATH"GAME/Mark_Find.png"){}

HeadMark* HeadMark::Create(D3DXVECTOR3 position)
{
	auto object = new HeadMark;

	object->SetPosition(position);

	object->Initialize();

	return object;
}

void HeadMark::Initialize(void)
{
	LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();

	MakeVertex(Device);
}

void HeadMark::Uninitialize(void)
{
	SAFE_RELEASE(m_VertexBuffer);
}

void HeadMark::Draw(void)
{
	if(!m_Active){ return; }


	LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();

	Device->SetVertexShader(NULL);
	Device->SetPixelShader(NULL);

	Device->SetStreamSource(0, m_VertexBuffer, 0, sizeof(VERTEX_3D));

	Device->SetFVF(FVF_VERTEX_3D);

	Device->SetTexture(0, Game::GetInstance()->GetTextureManager()->GetTextureInfo(m_TexturePath).Texture);

	WorldTransform(Device);

	// �S�̂̃��C�g�𖳌��ɂ���
	Device->SetRenderState(D3DRS_LIGHTING, FALSE);

	Device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	//	�S�̂̃��C�g��L���ɂ���
	Device->SetRenderState(D3DRS_LIGHTING, TRUE);
}

void HeadMark::MakeVertex(LPDIRECT3DDEVICE9 Device)
{
	if (FAILED(Device->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_VertexBuffer, NULL)))
	{
		MessageBox(NULL, "���_�o�b�t�@�̐����Ɏ��s", "HeadMark.cpp", MB_OK | MB_ICONHAND);
	}

	VERTEX_3D* Vtx;

	m_VertexBuffer->Lock(0, 0, (void**)&Vtx, 0);


	Vtx[0].Pos = D3DXVECTOR3(-m_Size.x, m_Size.y, 0.0f);
	Vtx[1].Pos = D3DXVECTOR3(m_Size.x , m_Size.y, 0.0f);
	Vtx[2].Pos = D3DXVECTOR3(-m_Size.x, 0.0f, 0.0f);
	Vtx[3].Pos = D3DXVECTOR3(m_Size.x , 0.0f, 0.0f);

	for(unsigned int i = 0; i < NUM_VERTEX; i++)
	{
		Vtx[i].Nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		Vtx[i].Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	Vtx[0].Tex = D3DXVECTOR2(0, 0);
	Vtx[1].Tex = D3DXVECTOR2(1, 0);
	Vtx[2].Tex = D3DXVECTOR2(0, 1);
	Vtx[3].Tex = D3DXVECTOR2(1, 1);

	m_VertexBuffer->Unlock();
}

void HeadMark::WorldTransform(LPDIRECT3DDEVICE9 Device)
{
	D3DXVECTOR3 Position = Object::GetPosition();

	//	�r���[�s��̋t�s����擾
	D3DXMATRIX mtxViewInverse = Game::GetInstance()->GetCamera()->GetInversedView();


	D3DXMATRIX mtxWorld, mtxScl, mtxPos;

	D3DXMatrixIdentity(&mtxWorld);

	D3DXMatrixScaling(&mtxScl,
		m_Scale.x,
		m_Scale.y,
		m_Scale.z);

	D3DXMatrixTranslation(&mtxPos,
		Position.x,
		Position.y,
		Position.z);

	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxViewInverse);

	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxPos);

	Device->SetTransform(D3DTS_WORLD, &mtxWorld);
}