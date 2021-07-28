/*=============================================================================

�����_���[(DirectX)[ RendererDirectX.h ]

-------------------------------------------------------------------------------

��  Create
	2017/10/14
=============================================================================*/

#ifndef _RENDERERDIRECTX_H_
#define _RENDERERDIRECTX_H_

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include <d3dx9.h>
#include <Xinput.h>
#include "Renderer.h"

/*-----------------------------------------------------------------------------
Macro
-----------------------------------------------------------------------------*/
//	���_�t�H�[�}�b�g
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)	//	2D
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 | D3DFVF_NORMAL)	//	3D

#define NUM_VERTEX ( 4 )	//	���_��
#define NUM_POLYGON ( 2 )	//	�|���S����

#define SAFE_RELEASE(p) if(p){ p->Release(); p = NULL; }// �|�C���^�̉�������}�N��

/*-----------------------------------------------------------------------------
Library
[�\���v���p�e�B]->[�����J�[]->[����]->[�ǉ��̈ˑ��t�@�C��]�ɋL�q���Ă��\
-----------------------------------------------------------------------------*/
#pragma comment(lib , "d3d9.lib")
#define DIRECTINPUT_VERSION (0x0800)
#include <dinput.h>
#include <XAudio2.h>

#pragma comment(lib, "xinput.lib")	//	XInput
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")

/*-----------------------------------------------------------------------------
Struct
-----------------------------------------------------------------------------*/
struct VERTEX_2D
{
	D3DXVECTOR3 Pos;	//	���_���W
	float Rhw;			//	���W�ϊ��ςݒ��_�t���O�iDirectX�ɂ����Ȃ��d�l�j�K��1.0f������
	D3DCOLOR Color;		//	���_�J���[
	D3DXVECTOR2 Tex;	//	�e�N�X�`�����W
};

struct VERTEX_3D
{
	D3DXVECTOR3 Pos;	//	���_���W
	D3DXVECTOR3 Nor;	//	�@��
	D3DCOLOR Color;		//	���_�J���[
	D3DXVECTOR2 Tex;	//	�e�N�X�`�����W
};

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class RendererDirectX:public Renderer
{
public:
	RendererDirectX();

	HRESULT Initialize(HWND hWnd)override;
	void Uninitialize(void)override;
	void DrawBegin(void)override;
	void DrawEnd(void)override;

	void Normal(void); // �ʏ펞
	void WireFrame(void); // ���C���[�t���[��

	//	Getter
	static LPDIRECT3DDEVICE9 GetDevice(void) { return m_D3DDevice; }

private:
	//	�f�o�C�X�̏�����
	HRESULT SetUpDevice(D3DPRESENT_PARAMETERS d3dpp, D3DDISPLAYMODE d3ddm, HWND Wnd, bool Window);
	void SetRenderState(void);			//	�����_�[�X�e�[�g�̐ݒ�
	void SetSamplerState(void);			//	�T���v���[�X�e�[�g�̐ݒ�
	void SetTextureStageState(void);	//	�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	void InitRenderTarget(void);		 // �����_�[�^�[�Q�b�g�̏�����
	void Polygon2DInitialize(void);
	void Polygon2DDraw(void);
	void PolygonScreenInit(void);
	void PolygonScreenDraw(void);

#ifdef _DEBUG
	void DrawFPS(void); // FPS�\��
#endif

private:
	static D3DXCOLOR m_BackBufferColor;	//	�o�b�N�o�b�t�@�F
	static LPDIRECT3DDEVICE9 m_D3DDevice;	// Device�I�u�W�F�N�g(�`��ɕK�v)

	LPDIRECT3D9 m_D3D;	// Direct3D�I�u�W�F�N�g

	LPDIRECT3DTEXTURE9 m_BlurTexture_1;// �e�N�X�`��
    LPDIRECT3DSURFACE9 m_BlurSurface_1;// �T�[�t�F�X
	LPDIRECT3DTEXTURE9 m_BlurTexture_2;
    LPDIRECT3DSURFACE9 m_BlurSurface_2;
    LPDIRECT3DSURFACE9 m_BackBufferSurface;// �o�b�N�o�b�t�@
	LPDIRECT3DVERTEXBUFFER9 m_VertexBuffer;
	LPDIRECT3DVERTEXBUFFER9 m_VertexBuffer2;

#ifdef _DEBUG
	LPD3DXFONT m_Font;	// �t�H���g�ւ̃|�C���^
#endif
};

#endif
