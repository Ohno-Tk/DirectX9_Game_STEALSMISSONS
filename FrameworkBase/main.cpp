/*=============================================================================

	���C���֐�[ main.cpp ]

-------------------------------------------------------------------------------

��  Create
	2017/10/14
=============================================================================*/

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "Common.h"
#include "GameLoop.h"
#include "../resource.h"

/*-----------------------------------------------------------------------------
Macro
-----------------------------------------------------------------------------*/
#define CLASS_NAME     "�A�E��i"			//	WindowClassName
#define WINDOW_NAME    "STEALTH MISSION"	//	WindowName
#define ICON_DATA (LoadIcon(g_Instance,MAKEINTRESOURCE(IDI_ICON1)))

/*-----------------------------------------------------------------------------
Prototype
-----------------------------------------------------------------------------*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void Init(void);
bool Loop(void); // ���[�v����
int Uninit(void);
void InitWindow(void); // �E�B���h�E�̏�����
void WindowCreate(void); // �E�B���h�E�̐���

/*-----------------------------------------------------------------------------
Global
-----------------------------------------------------------------------------*/
WNDCLASSEX g_Wcex = {};
MSG g_Msg = {};
HINSTANCE g_Instance = NULL;
HWND g_hWnd = NULL;	//	�E�C���h�E�n���h��( ���C���n���h�� )
int g_CmdShow = 0;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpCmdLine, int nCmdShow)
{
	g_Instance = hInstance;
	g_CmdShow = nCmdShow;

#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	Init();

	while (Loop());

	int Param = Uninit();

#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif

	return Param;
}

/*-----------------------------------------------------------------------------
				�E�C���h�E�v���V�[�W��
		( CALLBACK:Win32API�֐����Ăяo���Ƃ��̋K�� )
		hWnd :   �E�C���h�E�̃n���h��
		uMsg :   ���b�Z�[�W�̎��ʎq
		wParam : ���b�Z�[�W�̍ŏ��̃p�����[�^
		lParam : ���b�Z�[�W�̂Q�Ԗڂ̃p�����[�^
-------------------------------------------------------------------------------*/
LRESULT CALLBACK WndProc( HWND hWnd , UINT uMsg , WPARAM wParam , LPARAM lParam )
{
	UINT nSelect;
	static HDC hDC;
	static PAINTSTRUCT ps;	//	�`����i�[�p

	switch( uMsg )
	{
	case WM_DESTROY:		//	�E�C���h�E�j���̃��b�Z�[�W

		PostQuitMessage( 0 );//	"WM_QUIT"���b�Z�[�W��Ԃ�
		break;

	case WM_KEYDOWN:	//	�L�[����
		switch( wParam )
		{
			case VK_ESCAPE:	//	ESCAPE�L�[
			nSelect = MessageBox( NULL , "�A�v���P�[�V�������I�����܂����H" , "�I�����b�Z�[�W" , MB_YESNO | MB_ICONQUESTION );

			if (nSelect == IDYES)
			{
				DestroyWindow(hWnd);
			}

			break;
		}
	}

	return DefWindowProc( hWnd , uMsg , wParam , lParam );	//	����̏������
}

void Init(void)
{
	InitWindow(); // �E�B���h�E�̏�����
	WindowCreate(); // �E�B���h�E�̐���

	GameLoop::Instance()->Init(g_Instance, g_hWnd);
}

/*-----------------------------------------------------------------------------
Function:   bool Loop(void)
Return:     return true;
              ���[�v���s
            return false;
			  ���[�v�I��
Overview:   ���[�v����
-----------------------------------------------------------------------------*/
bool Loop(void)
{
	//	���b�Z�[�W���[�v
	//	��P�����F���b�Z�[�W���
	//	��Q�����F�E�C���h�E�̃n���h��
	//	��R�����F�ŏ��̃��b�Z�[�W
	//	��S�����F�Ō�̃��b�Z�[�W
	if (PeekMessage(&g_Msg, NULL, 0, 0, PM_REMOVE) != 0)
	{
		//	Windows�̏���
		if (g_Msg.message == WM_QUIT){ return false; }
		else
		{
			//	�Ăяo�����X���b�h�̃��b�Z�[�W�L���[����
			//	���b�Z�[�W�̖|��Ƒ��o
			TranslateMessage(&g_Msg);
			DispatchMessage(&g_Msg);
		}
	}
	else
	{
		GameLoop::Instance()->ClockFps();
	}

	return true;
}

int Uninit(void)
{
	GameLoop::Instance()->Uninit();
	GameLoop::Destroy(); // �C���X�^���X�j��

	//	�E�C���h�E�N���X�̓o�^������
	//	�������F���N���X��
	//	�������F�A�v���P�[�V�����C���X�^���X
	UnregisterClass(CLASS_NAME, g_Wcex.hInstance);

	return (int)g_Msg.wParam;
}

/*-----------------------------------------------------------------------------
Function:   void InitWindow(void)
Overview:   �E�B���h�E�̏�����
-----------------------------------------------------------------------------*/
void InitWindow(void)
{
	//	�E�C���h�E�̃p�[�c�o�^
	g_Wcex.cbSize = sizeof(WNDCLASSEX);					//	WNDCLASSEX�̃������T�C�Y���w��
	g_Wcex.style = CS_CLASSDC;							//	�\������E�C���h�E�̃X�^�C����ݒ�
	g_Wcex.lpfnWndProc = WndProc;						//	�E�B���h�E�v���V�[�W���̃A�h���X( �֐��� )���w��@�v���g�^�C�v�錾�����֐��������i�d�v�I�I�j
	g_Wcex.cbClsExtra = 0;								//	�ʏ�͎g�p���Ȃ��̂�" 0 "���w��
	g_Wcex.cbWndExtra = 0;								//	�ʏ�͎g�p���Ȃ��̂�" 0 "���w��
	g_Wcex.hInstance = g_Instance;						//	WinMain�̃p�����[�^�̃C���X�^���X�n���h����ݒ�
	g_Wcex.hIcon = ICON_DATA;								//	�g�p����A�C�R�����w��( Windows�������Ă���A�C�R�����g���Ȃ� )
	g_Wcex.hCursor = LoadCursor(NULL, IDC_ARROW);		//	�}�E�X�J�[�\�����w��	�i���Ƃł͂��Ȃ��j
	g_Wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);	//	�E�C���h�E�̃N���C�A���g�̈�̔w�i�F��ݒ�	�i���Ƃł͂��Ȃ��j
	g_Wcex.lpszMenuName = NULL;							//	Windows�ɂ��郁�j���[��ݒ�
	g_Wcex.lpszClassName = CLASS_NAME;					//	�E�C���h�E�N���X�̖��O	�i�d�v�I�I�j
	g_Wcex.hIconSm = NULL;								//	�������A�C�R�����ݒ肳�ꂽ�ꍇ�̏����L�q	�i���Ƃł͂��Ȃ��j

	//	�E�C���h�E�N���X�̓o�^
	RegisterClassEx(&g_Wcex);	//	�I���W�i���̃E�C���h�E�p�[�c�̖��O������( �J�X�^���E�C���h�E�p�̐ݒ� )
}

/*-----------------------------------------------------------------------------
Function:   void WindowCreate(void)
Overview:   �E�B���h�E�̐���
-----------------------------------------------------------------------------*/
void WindowCreate(void)
{
	const int Windowstyle = WS_OVERLAPPEDWINDOW ^ WS_MINIMIZEBOX ^ WS_THICKFRAME;

	//	�`��̈�̃T�C�Y����E�C���h�E�̋�`���擾
	RECT cr = { 0 , 0 , SCREEN_WIDTH , SCREEN_HEIGHT };
	AdjustWindowRect(&cr, Windowstyle, FALSE);

	RECT dr;
	GetWindowRect(GetDesktopWindow(), &dr);

	int dw = dr.right - dr.left;
	int dh = dr.bottom - dr.top;

	int ww = cr.right - cr.left;
	int wh = cr.bottom - cr.top;

	int wx = ww > dw ? 0 : (dw - ww) / 2;
	int wy = wh > dh ? 0 : (dh - wh) / 2;

	//	�E�C���h�E�̍쐬
	g_hWnd = CreateWindowEx(0,	//	�g���E�C���h�E�X�^�C���i�@������Ɛݒ肷��@�j
		CLASS_NAME,				//	�E�C���h�E�N���X�̖��O
		WINDOW_NAME,			//	�E�C���h�E�̖��O
		Windowstyle,			//	�E�C���h�E�X�^�C��
		wx,						//	�E�C���h�E�̍���w���W
		wy,						//	�E�C���h�E�̍���x���W
		ww,						//	�E�C���h�E�̕��i�@�t���[�������킹�����@�j
		wh,						//	�E�C���h�E�̍����i�@�t���[�������킹�������@�j
		NULL,					//	�e�E�C���h�E�̃n���h���i�@�|�C���^�@�j
		NULL,					//	���j���[�n���h���܂��͎q�E�C���h�EID
		g_Instance,				//	�C���X�^���X�n���h��
		NULL);					//	�E�C���h�E�쐬�f�[�^

	//	�E�C���h�E�̕\��
	ShowWindow(g_hWnd, g_CmdShow);	//	�w�肳�ꂽ�E�C���h�E�̕\��
	UpdateWindow(g_hWnd);			//	�E�C���h�E�̏�Ԃ𒼂��ɔ��f
}
