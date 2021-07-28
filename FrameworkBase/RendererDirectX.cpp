/*=============================================================================

�����_���[(DirectX)[ RendererDirectX.cpp ]

-------------------------------------------------------------------------------

��  Create
	2017/10/14
=============================================================================*/

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "Renderer.h"
#include "Common.h"
#include "GameLoop.h"
#include "RendererDirectX.h"

/*-----------------------------------------------------------------------------
Macro
-----------------------------------------------------------------------------*/
#define ENABLE_RENDERTARGET
#undef ENABLE_RENDERTARGET

/*-----------------------------------------------------------------------------
Static
-----------------------------------------------------------------------------*/
D3DXCOLOR RendererDirectX::m_BackBufferColor = D3DCOLOR_RGBA(0, 0, 0, 0);
LPDIRECT3DDEVICE9 RendererDirectX::m_D3DDevice = NULL;


RendererDirectX::RendererDirectX():
m_D3D(NULL),
m_BlurTexture_1(NULL),
m_BlurSurface_1(NULL),
m_BlurTexture_2(NULL),
m_BlurSurface_2(NULL),
m_BackBufferSurface(NULL),
m_VertexBuffer(NULL),
m_VertexBuffer2(NULL){}

HRESULT RendererDirectX::Initialize(HWND hWnd)
{
	HRESULT hr;

	D3DPRESENT_PARAMETERS d3dpp = {};
	D3DDISPLAYMODE d3ddm = {};


	// Direct3D�I�u�W�F�N�g�̍쐬
	m_D3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (!m_D3D)
	{
		MessageBox(NULL, "Direct3D�I�u�W�F�N�g�̍쐬�Ɏ��s", "RendererDirectX.cpp", MB_OK | MB_ICONHAND);
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	hr = m_D3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);
	if (FAILED(hr))
	{
		MessageBox(NULL, "�f�B�X�v���C���[�h�̎擾�Ɏ��s", "RendererDirectX.cpp", MB_OK | MB_ICONHAND);
		return E_FAIL;
	}

	hr = SetUpDevice(d3dpp, d3ddm, hWnd, true);	//	�f�o�C�X�̏�����
	if (FAILED(hr))
	{
		MessageBox(NULL, "�f�o�C�X�̏������Ɏ��s", "RendererDirectX.cpp", MB_OK | MB_ICONHAND);
		return E_FAIL;
	}

	SetRenderState();	//	�����_�[�X�e�[�g�̐ݒ�

	SetSamplerState();	//	�T���v���[�X�e�[�g�̐ݒ�

	SetTextureStageState();	//	�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�

#ifdef ENABLE_RENDERTARGET
	InitRenderTarget(); // �����_�[�^�[�Q�b�g�̏�����
	Polygon2DInitialize();
	PolygonScreenInit();
#endif

#ifdef _DEBUG
	// �f�o�b�O���\���p�t�H���g�𐶐�
	D3DXCreateFont(m_D3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_Font);
#endif

	return S_OK;
}

void RendererDirectX::Uninitialize(void)
{
#ifdef _DEBUG
	SAFE_RELEASE(m_Font);// ���\���p�t�H���g
#endif

	SAFE_RELEASE(m_D3D);//	Direct3D�I�u�W�F�N�g

	SAFE_RELEASE(m_D3DDevice);// �f�o�C�X�̔j��

#ifdef ENABLE_RENDERTARGET
	SAFE_RELEASE(m_BlurTexture_1);
	SAFE_RELEASE(m_BlurSurface_1);
	SAFE_RELEASE(m_BlurTexture_2);
	SAFE_RELEASE(m_BlurSurface_2);
	SAFE_RELEASE(m_BackBufferSurface);
	SAFE_RELEASE(m_VertexBuffer);
	SAFE_RELEASE(m_VertexBuffer2);
#endif
}

void RendererDirectX::DrawBegin(void)
{
#ifdef ENABLE_RENDERTARGET
	m_D3DDevice->SetRenderTarget(0, m_BlurSurface_2);
#endif

	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	m_D3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL), m_BackBufferColor, 1.0f, 0);

	m_D3DDevice->BeginScene(); // DirectX�ɂ��`��̊J�n
}

void RendererDirectX::DrawEnd(void)
{
#ifdef _DEBUG
	DrawFPS(); // FPS�\��
#endif

	m_D3DDevice->EndScene(); // DirectX�ɂ��`��̏I��

#ifdef ENABLE_RENDERTARGET
	m_D3DDevice->SetTexture(0, m_BlurTexture_1);

	// 2D�|���S���`��
	Polygon2DDraw();

	m_D3DDevice->EndScene();

	m_D3DDevice->SetRenderTarget(0, m_BackBufferSurface);

	m_D3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL), m_BackBufferColor, 1.0f, 0);

	m_D3DDevice->BeginScene();

	m_D3DDevice->SetTexture(0, m_BlurTexture_2);

	//2D�|���S���`��
	PolygonScreenDraw();

	m_D3DDevice->EndScene();


	// ����ւ�
	LPDIRECT3DTEXTURE9 texture;
	texture = m_BlurTexture_1;
	m_BlurTexture_1 = m_BlurTexture_2;
	m_BlurTexture_2 = texture;

	LPDIRECT3DSURFACE9 surface;
	surface = m_BlurSurface_1;
	m_BlurSurface_1 = m_BlurSurface_2;
	m_BlurSurface_2 = surface;
#endif
	
	m_D3DDevice->Present(NULL, NULL, NULL, NULL); // �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
}

/*-----------------------------------------------------------------------------
Function:   void RendererDirectX::SetTextureStageState(void)
Parameter:  D3DPRESENT_PARAMETERS d3dpp, D3DDISPLAYMODE d3ddm, HWND Wnd, bool Window
Overview:   �f�o�C�X�̏�����
-----------------------------------------------------------------------------*/
HRESULT RendererDirectX::SetUpDevice(D3DPRESENT_PARAMETERS d3dpp, D3DDISPLAYMODE d3ddm, HWND Wnd, bool Window)
{
	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));							// ���[�N���[���N���A
	d3dpp.BackBufferCount = 1;									// �o�b�N�o�b�t�@�̐�
	d3dpp.BackBufferWidth = SCREEN_WIDTH;						// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;						// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;						// �J���[���[�h�̎w��
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					// �f���M���ɓ������ăt���b�v����
	d3dpp.EnableAutoDepthStencil = TRUE;						// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.Windowed = Window;									// �E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// ���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// �C���^�[�o��


	HRESULT hr;

	// �f�o�C�X�̐���
	// �f�B�X�v���C�A�_�v�^��\�����߂̃f�o�C�X���쐬
	// �`��ƒ��_�������n�[�h�E�F�A�ōs�Ȃ�
	hr = m_D3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		Wnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &m_D3DDevice);
	if (FAILED(hr))
	{
		// ��L�̐ݒ肪���s������
		// �`����n�[�h�E�F�A�ōs���A���_������CPU�ōs�Ȃ�
		hr = m_D3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			Wnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &m_D3DDevice);
		if (FAILED(hr))
		{
			// ��L�̐ݒ肪���s������
			// �`��ƒ��_������CPU�ōs�Ȃ�
			hr = m_D3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF, Wnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp, &m_D3DDevice);
			if (FAILED(hr))
			{

				MessageBox(NULL, "�f�o�C�X�̐����Ɏ��s", "RendererDirectX.cpp", MB_OK | MB_ICONHAND);
				return E_FAIL;
			}
		}
	}

	return S_OK;
}

/*-----------------------------------------------------------------------------
Function:   void RendererDirectX::SetTextureStageState(void)
Overview:   �����_�[�X�e�[�g�̐ݒ�
-----------------------------------------------------------------------------*/
void RendererDirectX::SetRenderState(void)
{
	m_D3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW); // �J�����O���s��Ȃ�
	m_D3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE); // Z�o�b�t�@���g�p
	m_D3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE); // ���u�����h���s��
	m_D3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA); // ���\�[�X�J���[�̎w��
	m_D3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��
}

/*-----------------------------------------------------------------------------
Function:   void RendererDirectX::SetTextureStageState(void)
Overview:   �T���v���[�X�e�[�g�̐ݒ�
-----------------------------------------------------------------------------*/
void RendererDirectX::SetSamplerState(void)
{
	m_D3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP); // �e�N�X�`���t�l�̌J��Ԃ��ݒ�
	m_D3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP); // �e�N�X�`���u�l�̌J��Ԃ��ݒ�
	m_D3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���g�厞�̕�Ԑݒ�
	m_D3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���k�����̕�Ԑݒ�
}

/*-----------------------------------------------------------------------------
Function:   void RendererDirectX::SetTextureStageState(void)
Overview:   �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
-----------------------------------------------------------------------------*/
void RendererDirectX::SetTextureStageState(void)
{
	m_D3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// �A���t�@�u�����f�B���O����(�����l��D3DTOP_SELECTARG1)
	m_D3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// �ŏ��̃A���t�@����(�����l��D3DTA_TEXTURE�A�e�N�X�`�����Ȃ��ꍇ��D3DTA_DIFFUSE)
	m_D3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);	// �Q�Ԗڂ̃A���t�@����(�����l��D3DTA_CURRENT)
}

#ifdef _DEBUG
/*-----------------------------------------------------------------------------
Function:   void RendererDirectX::DrawFPS(void)
Overview:   FPS�\��
-----------------------------------------------------------------------------*/
void RendererDirectX::DrawFPS(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[256];
	int nCountFPS;

	// FPS�擾
	nCountFPS = GameLoop::Instance()->GetFPS();
	wsprintf(str, "FPS:%d\n", nCountFPS);

	// �e�L�X�g�`��
	m_Font->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}
#endif

/*-----------------------------------------------------------------------------
Function:   void RendererDirectX::Normal(void)
Overview:   ���C���[�t���[��
-----------------------------------------------------------------------------*/
void RendererDirectX::Normal(void)
{
	m_D3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_FORCE_DWORD);
}

/*-----------------------------------------------------------------------------
Function:   void RendererDirectX::WireFrame(void)
Overview:   �ʏ펞
-----------------------------------------------------------------------------*/
void RendererDirectX::WireFrame(void)
{
	m_D3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
}

/*-----------------------------------------------------------------------------
Function:   void RendererDirectX::InitRenderTarget(void)
Overview:   �����_�[�^�[�Q�b�g�̏�����
-----------------------------------------------------------------------------*/
void RendererDirectX::InitRenderTarget(void)
{
	D3DXCreateTexture(m_D3DDevice,SCREEN_WIDTH, // �e�N�X�`���̃s�N�Z����(��)
	 SCREEN_HEIGHT, // �e�N�X�`���̃s�N�Z����(�c)
	 1, // �~�b�v�}�b�v�̃��x����
	 D3DUSAGE_RENDERTARGET, // �ǂ������p�r�Ŏg�p���邩
	 D3DFMT_A8R8G8B8, // �s�N�Z���t�H�[�}�b�g
	 D3DPOOL_DEFAULT,
	 &m_BlurTexture_1);

	// �T�[�t�F�[�X�̎擾
	m_BlurTexture_1->GetSurfaceLevel(0, &m_BlurSurface_1);

	D3DXCreateTexture(m_D3DDevice, SCREEN_WIDTH, SCREEN_HEIGHT, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_BlurTexture_2);

	m_BlurTexture_2->GetSurfaceLevel(0, &m_BlurSurface_2);

	// �o�b�N�o�b�t�@�̃T�[�t�F�[�X���擾
	m_D3DDevice->GetRenderTarget(0, &m_BackBufferSurface);

}

void RendererDirectX::Polygon2DInitialize(void)
{
	if (FAILED(m_D3DDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_VertexBuffer, NULL)))
	{
		MessageBox(NULL, "���_�o�b�t�@�̐����Ɏ��s", "RendererDirectX.cpp", MB_OK | MB_ICONHAND);
		return;
	}

	// ���_����ݒ�
	VERTEX_2D* pVtx;

	// �o�b�t�@�����b�N���A���z�A�h���X���擾
	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);


	//	���_���W
 // �u���[��������  ���_�������傫������
	pVtx[0].Pos = D3DXVECTOR3( -10.0f            ,-10.0f, 0.0f);
	pVtx[1].Pos = D3DXVECTOR3( SCREEN_WIDTH+10.0f,-10.0f, 0.0f);
	pVtx[2].Pos = D3DXVECTOR3( -10.0f            , SCREEN_HEIGHT+10.0f, 0.0f);
	pVtx[3].Pos = D3DXVECTOR3( SCREEN_WIDTH+10.0f, SCREEN_HEIGHT+10.0f, 0.0f);


/* // �����ڂ₯��   ���_�𓙂�������
	pVtx[0].Pos = D3DXVECTOR3( 0.0f        , 0.0f, 0.0f);
	pVtx[1].Pos = D3DXVECTOR3( SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].Pos = D3DXVECTOR3( 0.0f        , SCREEN_HEIGHT, 0.0f);
	pVtx[3].Pos = D3DXVECTOR3( SCREEN_WIDTH ,SCREEN_HEIGHT, 0.0f);
*/
/* // ���S�ɋ߂Â��悤�ɂȂ�@���_����������������
	pVtx[0].Pos = D3DXVECTOR3( 5.0f              , 5.0f, 0.0f);
	pVtx[1].Pos = D3DXVECTOR3( SCREEN_WIDTH-5.0f , 5.0f, 0.0f);
	pVtx[2].Pos = D3DXVECTOR3( 5.0f              , SCREEN_HEIGHT-5.0f, 0.0f);
	pVtx[3].Pos = D3DXVECTOR3( SCREEN_WIDTH-5.0f , SCREEN_HEIGHT-5.0f, 0.0f);
*/

	for(int i = 0; i < NUM_VERTEX; i++)
	{
		pVtx[i].Rhw = 1.0f;
		pVtx[i].Color = D3DXCOLOR(1.0f,1.0f,1.0f, 0.99f);
	}
	// �e�N�X�`�����W
	pVtx[0].Tex = D3DXVECTOR2(0, 0);
	pVtx[1].Tex = D3DXVECTOR2(1, 0);
	pVtx[2].Tex = D3DXVECTOR2(0, 1);
	pVtx[3].Tex = D3DXVECTOR2(1, 1);

	//	�o�b�t�@���A�����b�N
	m_VertexBuffer->Unlock();
}

void RendererDirectX::Polygon2DDraw(void)
{
	m_D3DDevice->SetStreamSource(0, m_VertexBuffer, 0, sizeof(VERTEX_2D));

	m_D3DDevice->SetFVF(FVF_VERTEX_2D);

	m_D3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

void RendererDirectX::PolygonScreenInit(void)
{
	if (FAILED(m_D3DDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_VertexBuffer2, NULL)))
	{
		MessageBox(NULL, "���_�o�b�t�@�̐����Ɏ��s", "RendererDirectX.cpp", MB_OK | MB_ICONHAND);
		return;
	}

	// ���_����ݒ�
	VERTEX_2D* pVtx;

	// �o�b�t�@�����b�N���A���z�A�h���X���擾
	m_VertexBuffer2->Lock(0, 0, (void**)&pVtx, 0);


	//	���_���W
	pVtx[0].Pos = D3DXVECTOR3( 0.0f        ,  0.0f, 0.0f);
	pVtx[1].Pos = D3DXVECTOR3( SCREEN_WIDTH,  0.0f, 0.0f);
	pVtx[2].Pos = D3DXVECTOR3( 0.0f        , SCREEN_HEIGHT, 0.0f);
	pVtx[3].Pos = D3DXVECTOR3( SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);


	for(int i = 0; i < NUM_VERTEX; i++)
	{
		pVtx[i].Rhw = 1.0f;
		pVtx[i].Color = D3DXCOLOR(1.0f,1.0f,1.0f, 1.0f);
	}
	// �e�N�X�`�����W
	pVtx[0].Tex = D3DXVECTOR2(0, 0);
	pVtx[1].Tex = D3DXVECTOR2(1, 0);
	pVtx[2].Tex = D3DXVECTOR2(0, 1);
	pVtx[3].Tex = D3DXVECTOR2(1, 1);

	//	�o�b�t�@���A�����b�N
	m_VertexBuffer2->Unlock();
}

void RendererDirectX::PolygonScreenDraw(void)
{
	m_D3DDevice->SetStreamSource(0, m_VertexBuffer2, 0, sizeof(VERTEX_2D));

	m_D3DDevice->SetFVF(FVF_VERTEX_2D);

	m_D3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
//	m_D3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	m_D3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	m_D3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
//	m_D3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
}