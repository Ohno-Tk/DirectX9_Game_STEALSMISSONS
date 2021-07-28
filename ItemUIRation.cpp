/*=============================================================================

�A�C�e���\��UI( ���[�V���� )[ ItemUIRation.cpp ]

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
#include "GameScene.h"
#include "Player.h"
#include "Object.h"
#include "ItemPossession.h"
#include "ItemUIRation.h"

/*-----------------------------------------------------------------------------
Macro
-----------------------------------------------------------------------------*/
#define OBJECT_TEXTURE_PATH (TEXTURE_PATH"GAME/Ration_UI.png")


/*-----------------------------------------------------------------------------
�R���X�g���N�^
-----------------------------------------------------------------------------*/
ItemUIRation::ItemUIRation(int priolity)
	:ItemUI(priolity)
	,m_VertexBuffer(NULL)
	,m_Size(D3DXVECTOR2(250.0f, 120.0f))
	,m_NowPossession(NULL)
	,m_MaxPossession(NULL)
{}

/*-----------------------------------------------------------------------------
����
-----------------------------------------------------------------------------*/
ItemUIRation* ItemUIRation::Create(D3DXVECTOR3 position)
{
	auto object = new ItemUIRation;

	object->SetPosition(position);
	object->Initialize();

	return object;
}

/*-----------------------------------------------------------------------------
������
-----------------------------------------------------------------------------*/
void ItemUIRation::Initialize(void)
{
	m_NowPossessionUI = ItemPossession::Create(D3DXVECTOR3( 60.0f, 515.0f,0.0f), 1);
	m_MaxPossessionUI = ItemPossession::Create(D3DXVECTOR3(120.0f, 515.0f,0.0f), 1);
	m_MaxPossessionUI->SetPossession(2);

	SetItemID(ITEM_ID_RATION);

	MakeVertex();
}

/*-----------------------------------------------------------------------------
�I��
-----------------------------------------------------------------------------*/
void ItemUIRation::Uninitialize(void)
{
	m_NowPossessionUI = NULL;
	m_MaxPossessionUI = NULL;

	ItemUI::Uninitialize();
}

/*-----------------------------------------------------------------------------
�X�V
-----------------------------------------------------------------------------*/
void ItemUIRation::Update(void)
{
	SetVertex();
}

/*-----------------------------------------------------------------------------
�`��
-----------------------------------------------------------------------------*/
void ItemUIRation::Draw(void)
{
	LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();


	Device->SetVertexShader(NULL);
	Device->SetPixelShader(NULL);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	Device->SetStreamSource(0, m_VertexBuffer, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	Device->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	Device->SetTexture(0, Game::GetInstance()->GetTextureManager()->GetTextureInfo(OBJECT_TEXTURE_PATH).Texture);

	// �`��
	Device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

/*-----------------------------------------------------------------------------
���_�̍쐬
-----------------------------------------------------------------------------*/
void ItemUIRation::MakeVertex(void)
{
	D3DXVECTOR3 position = Object::GetPosition();
	LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();

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
		Vtx[CountVertex].Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);// ���_�J���[
	}

	// �e�N�X�`�����W
	Vtx[0].Tex = D3DXVECTOR2(0, 0);
	Vtx[1].Tex = D3DXVECTOR2(1, 0);
	Vtx[2].Tex = D3DXVECTOR2(0, 1);
	Vtx[3].Tex = D3DXVECTOR2(1, 1);

	//	�o�b�t�@���A�����b�N
	m_VertexBuffer->Unlock();

}

/*-----------------------------------------------------------------------------
���_�̕ύX
-----------------------------------------------------------------------------*/
void ItemUIRation::SetVertex(void)
{
	D3DXVECTOR3 position = Object::GetPosition();

	// ���_����ݒ�
	VERTEX_2D* Vtx;

	// �o�b�t�@�����b�N���A���z�A�h���X���擾
	m_VertexBuffer->Lock(0, 0, (void**)&Vtx, 0);

	//	���_���W
	Vtx[0].Pos = D3DXVECTOR3(position.x           , position.y, 0.0f);
	Vtx[1].Pos = D3DXVECTOR3(position.x + m_Size.x, position.y, 0.0f);
	Vtx[2].Pos = D3DXVECTOR3(position.x           , position.y + m_Size.y, 0.0f);
	Vtx[3].Pos = D3DXVECTOR3(position.x + m_Size.x, position.y + m_Size.y, 0.0f);

	//	�o�b�t�@���A�����b�N
	m_VertexBuffer->Unlock();
}

/*-----------------------------------------------------------------------------
���ݏ������ǉ�
-----------------------------------------------------------------------------*/
void ItemUIRation::PlusNowPossession(const unsigned int plusValue)
{
	m_NowPossession += plusValue;

	m_NowPossessionUI->SetPossession(m_NowPossession);
}

/*-----------------------------------------------------------------------------
���ݏ��������Z
-----------------------------------------------------------------------------*/
void ItemUIRation::SubNowPossession(const unsigned int subValue)
{
	m_NowPossession -= subValue;

	m_NowPossessionUI->SetPossession(m_NowPossession);
}

/*-----------------------------------------------------------------------------
���ݏ��������Z
-----------------------------------------------------------------------------*/
void ItemUIRation::Use(void)
{

	if(m_NowPossession == 0 || GameScene::GetPlayer()->GetHitPoint() >= GameScene::GetPlayer()->GetMaxHitPoint()){ return; }

	SubNowPossession(1);

	GameScene::GetPlayer()->HitPointRecovery(100);
}