/*=============================================================================

���ݏ������A�C�e��[ NowPossessionItem.cpp ]

-------------------------------------------------------------------------------

��  Create
2018/01/24
=============================================================================*/

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "FrameworkBase\Common.h"
#include "FrameworkBase\RendererDirectX.h"
#include "FrameworkBase\Game.h"
#include "FrameworkBase\TextureManagerDirectX.h"
#include "Object.h"
#include "ItemPossession.h"

/*-----------------------------------------------------------------------------
Macro
-----------------------------------------------------------------------------*/
#define OBJECT_TEXTURE_PATH (TEXTURE_PATH"GAME/Number003.png")
#define BUNKATUSU ( 0.1f )	//	�e�N�X�`���̕�����


ItemPossession::ItemPossession(int priolity)
	:Object(priolity)
	,m_VertexBuffer(NULL)
	,m_Size(D3DXVECTOR2(40.0f, 40.0f))
	,m_Digit(0)
	,m_TexCoord(0.0f)
	,m_Possession(0)
{}

/*-----------------------------------------------------------------------------
����
-----------------------------------------------------------------------------*/
ItemPossession* ItemPossession::Create(D3DXVECTOR3 position, unsigned int digit)
{
	auto object = new ItemPossession;

	object->SetPosition(position);
	object->m_Digit = digit;
	object->Initialize();

	return object;
}

/*-----------------------------------------------------------------------------
������
-----------------------------------------------------------------------------*/
void ItemPossession::Initialize(void)
{
	MakeVertex();
}

/*-----------------------------------------------------------------------------
�I��
-----------------------------------------------------------------------------*/
void ItemPossession::Uninitialize(void)
{
	SAFE_RELEASE(m_VertexBuffer);
	Object::Release();
}

/*-----------------------------------------------------------------------------
�X�V
-----------------------------------------------------------------------------*/
void ItemPossession::Update(void)
{
	SetVertex();
}

/*-----------------------------------------------------------------------------
�`��
-----------------------------------------------------------------------------*/
void ItemPossession::Draw(void)
{
	LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();


	Device->SetStreamSource(0, m_VertexBuffer, 0, sizeof(VERTEX_2D));

	Device->SetFVF(FVF_VERTEX_2D);

	Device->SetTexture(0, Game::GetInstance()->GetTextureManager()->GetTextureInfo(OBJECT_TEXTURE_PATH).Texture);

	for(unsigned int i = 0; i < m_Digit; i++)
	{
		Device->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * NUM_VERTEX, NUM_POLYGON);
	}
}

/*-----------------------------------------------------------------------------
���_�̍쐬
-----------------------------------------------------------------------------*/
void ItemPossession::MakeVertex(void)
{
	D3DXVECTOR3 position = Object::GetPosition();
	LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();

	// ���_�o�b�t�@�̐���
	if (FAILED(Device->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX * m_Digit, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_VertexBuffer, NULL)))
	{
		MessageBox(NULL, "���_�o�b�t�@�̐����Ɏ��s", "NowPossessionItem.cpp", MB_OK | MB_ICONHAND);
	}

	// ���_����ݒ�
	VERTEX_2D* Vtx;

	// �o�b�t�@�����b�N���A���z�A�h���X���擾
	m_VertexBuffer->Lock(0, 0, (void**)&Vtx, 0);


	for(unsigned int i = 0; i < m_Digit; i++)
	{

		//	���_���W
		Vtx[0].Pos = D3DXVECTOR3(position.x            - m_Size.x * i, position.y, 0.0f);
		Vtx[1].Pos = D3DXVECTOR3(position.x + m_Size.x - m_Size.x * i, position.y, 0.0f);
		Vtx[2].Pos = D3DXVECTOR3(position.x            - m_Size.x * i, position.y + m_Size.y, 0.0f);
		Vtx[3].Pos = D3DXVECTOR3(position.x + m_Size.x - m_Size.x * i, position.y + m_Size.y, 0.0f);

		for(unsigned int j = 0; j < NUM_VERTEX; j++)
		{
			Vtx[j].Rhw = 1.0f;//	���W�ϊ��ςݒ��_�t���O
			Vtx[j].Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);// ���_�J���[
		}

		// �e�N�X�`�����W
		Vtx[0].Tex = D3DXVECTOR2( m_TexCoord             , 0 );
		Vtx[1].Tex = D3DXVECTOR2( m_TexCoord + BUNKATUSU , 0 );
		Vtx[2].Tex = D3DXVECTOR2( m_TexCoord             , 1 );
		Vtx[3].Tex = D3DXVECTOR2( m_TexCoord + BUNKATUSU , 1 );

		Vtx += 4;
	}

	//	�o�b�t�@���A�����b�N
	m_VertexBuffer->Unlock();

}

/*-----------------------------------------------------------------------------
���_�̕ύX
-----------------------------------------------------------------------------*/
void ItemPossession::SetVertex(void)
{
	int Number;		//	������\������ϐ�
	int Value = m_Possession;		//	�l�̕ێ�


	D3DXVECTOR3 position = Object::GetPosition();

	// ���_����ݒ�
	VERTEX_2D* Vtx;

	// �o�b�t�@�����b�N���A���z�A�h���X���擾
	m_VertexBuffer->Lock(0, 0, (void**)&Vtx, 0);


	for(unsigned int i = 0; i < m_Digit; i++)
	{
		Number = Value % 10;
		Value /= 10;
		m_TexCoord = Number * BUNKATUSU;


		//	���_���W
		Vtx[0].Pos = D3DXVECTOR3(position.x            - m_Size.x * i, position.y, 0.0f);
		Vtx[1].Pos = D3DXVECTOR3(position.x + m_Size.x - m_Size.x * i, position.y, 0.0f);
		Vtx[2].Pos = D3DXVECTOR3(position.x            - m_Size.x * i, position.y + m_Size.y, 0.0f);
		Vtx[3].Pos = D3DXVECTOR3(position.x + m_Size.x - m_Size.x * i, position.y + m_Size.y, 0.0f);

		// �e�N�X�`�����W
		Vtx[0].Tex = D3DXVECTOR2( m_TexCoord             , 0 );
		Vtx[1].Tex = D3DXVECTOR2( m_TexCoord + BUNKATUSU , 0 );
		Vtx[2].Tex = D3DXVECTOR2( m_TexCoord             , 1 );
		Vtx[3].Tex = D3DXVECTOR2( m_TexCoord + BUNKATUSU , 1 );

		Vtx += 4;

	}

	//	�o�b�t�@���A�����b�N
	m_VertexBuffer->Unlock();

}

/*-----------------------------------------------------------------------------
�����̐ݒ�
-----------------------------------------------------------------------------*/
void ItemPossession::SetPossession(int possession)
{
	m_Possession = possession;
}