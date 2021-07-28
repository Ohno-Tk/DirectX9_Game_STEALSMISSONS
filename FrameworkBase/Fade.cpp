/*=============================================================================

�t�F�[�h[ Fade.cpp ]

-------------------------------------------------------------------------------


��  Created Date
	2017/08/25
=============================================================================*/

/*-----------------------------------------------------------------------------
	Header
-----------------------------------------------------------------------------*/
#include "Common.h"
#include "RendererDirectX.h"
#include "TextureManagerDirectX.h"
#include "Game.h"
#include "Scene.h"
#include "Fade.h"

/*-----------------------------------------------------------------------------
	Macro
-----------------------------------------------------------------------------*/
#define OBJECT_TEXTURE_PATH (TEXTURE_PATH"Fade.jpg")
#define FADE_RATE ( 1.0f / 60 )	//	�ǂ̂��炢�Ńt�F�[�h������̂�

/*-----------------------------------------------------------------------------
	Static
-----------------------------------------------------------------------------*/
Fade::FADE_STATE Fade::m_Fade = FADE_NONE;	//	�t�F�[�h���
Scene *Fade::m_Scene = NULL;			//	��ʑJ�ڂ̃|�C���^

void Fade::Initialize(void)
{
	MakeVerTex();	//	���_�̍쐬
}

void Fade::Uninitialize(void)
{
	SAFE_RELEASE(m_VtxBuff);

	m_Scene = NULL;
}

void Fade::Update(void)
{
	if(m_Fade == FADE_NONE){return;}

	AlphaFade();	//	���l�̃t�F�[�h

	SetVerTex();	//	���_�̕ύX
}

void Fade::Draw(void)
{
	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();


	Device->SetVertexShader(NULL);
	Device->SetPixelShader(NULL);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	Device->SetStreamSource(0, m_VtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	Device->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	Device->SetTexture(0, Game::GetInstance()->GetTextureManager()->GetTextureInfo(OBJECT_TEXTURE_PATH).Texture);
	//Device->SetTexture(0, NULL);

	// �`��
	Device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

/*-----------------------------------------------------------------------------
���_�̍쐬
-----------------------------------------------------------------------------*/
void Fade::MakeVerTex(void)
{
	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();


	// ���_�o�b�t�@�̐���
	if (FAILED(Device->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_VtxBuff, NULL)))
	{
		MessageBox(NULL, "���_�o�b�t�@�̐����Ɏ��s", "Fade.cpp", MB_OK | MB_ICONHAND);
		return;
	}


	// ���_����ݒ�
	// �\���̂̃|�C���^�錾
	VERTEX_2D* pVtx;

	// �o�b�t�@�����b�N���A���z�A�h���X���擾
	m_VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//	���_���W�̐ݒ�
	pVtx[0].Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].Pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].Pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].Pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	for(unsigned int CountVertex = 0; CountVertex < NUM_VERTEX; CountVertex++)
	{
		pVtx[CountVertex].Rhw = 1.0f;//	���W�ϊ��ςݒ��_�t���O�̐ݒ�
		pVtx[CountVertex].Color = m_Color;//	���_�F
	}

	//	�e�N�X�`�����W�̐ݒ�
	pVtx[0].Tex = D3DXVECTOR2(0, 0);
	pVtx[1].Tex = D3DXVECTOR2(1, 0);
	pVtx[2].Tex = D3DXVECTOR2(0, 1);
	pVtx[3].Tex = D3DXVECTOR2(1, 1);

	//	�o�b�t�@���A�����b�N
	m_VtxBuff->Unlock();
}

/*-----------------------------------------------------------------------------
���_�̕ύX
-----------------------------------------------------------------------------*/
void Fade::SetVerTex(void)
{
	// ���_����ݒ�
	// �\���̂̃|�C���^�錾
	VERTEX_2D* pVtx;

	// �o�b�t�@�����b�N���A���z�A�h���X���擾
	m_VtxBuff->Lock(0, 0, (void**)&pVtx, 0);


	//	���_�F�̐ݒ�
	for(unsigned int CountVertex = 0; CountVertex < NUM_VERTEX; CountVertex++)
	{
		pVtx[CountVertex].Color = m_Color;
	}

	//	�o�b�t�@���A�����b�N
	m_VtxBuff->Unlock();
}

/*-----------------------------------------------------------------------------
���l�̃t�F�[�h
-----------------------------------------------------------------------------*/
void Fade::AlphaFade(void)
{
	if (m_Fade == FADE_IN)
	{	//	�t�F�[�h�C�����̏���

		m_Color.a -= FADE_RATE;	//	a�l�����Z���Č��̉�ʂ𕂂��яオ�点��

		if (m_Color.a < 0.0f)
		{	//	�t�F�[�h�C���̏I��

			m_Color.a = 0.0f;
			m_Fade = FADE_NONE;
		}
	}

	else if (m_Fade == FADE_OUT)
	{	//	�t�F�[�h�A�E�g���̏���

		m_Color.a += FADE_RATE;	//	a�l�����Z���Č��̉�ʂ������Ă���

		if (m_Color.a > 1.0f)
		{	//	�t�F�[�h�A�E�g�̏I��

			m_Color.a = 1.0f;
			m_Fade = FADE_IN;	//	�t�F�[�h�C���ɏ����̐؂�ւ�

			//	�J�ڂ̐ݒ�
			Game::GetInstance()->SetScene(m_Scene);
		}
	}
}