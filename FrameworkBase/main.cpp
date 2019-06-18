/*=============================================================================

	メイン関数[ main.cpp ]

-------------------------------------------------------------------------------
■  Author
	Ohno Takuya

■  Create
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
#define CLASS_NAME     "就職作品"			//	WindowClassName
#define WINDOW_NAME    "STEALTH MISSION"	//	WindowName
#define ICON_DATA (LoadIcon(g_Instance,MAKEINTRESOURCE(IDI_ICON1)))

/*-----------------------------------------------------------------------------
Prototype
-----------------------------------------------------------------------------*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void Init(void);
bool Loop(void); // ループ部分
int Uninit(void);
void InitWindow(void); // ウィンドウの初期化
void WindowCreate(void); // ウィンドウの生成

/*-----------------------------------------------------------------------------
Global
-----------------------------------------------------------------------------*/
WNDCLASSEX g_Wcex = {};
MSG g_Msg = {};
HINSTANCE g_Instance = NULL;
HWND g_hWnd = NULL;	//	ウインドウハンドル( メインハンドル )
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
				ウインドウプロシージャ
		( CALLBACK:Win32API関数を呼び出すときの規約 )
		hWnd :   ウインドウのハンドル
		uMsg :   メッセージの識別子
		wParam : メッセージの最初のパラメータ
		lParam : メッセージの２番目のパラメータ
-------------------------------------------------------------------------------*/
LRESULT CALLBACK WndProc( HWND hWnd , UINT uMsg , WPARAM wParam , LPARAM lParam )
{
	UINT nSelect;
	static HDC hDC;
	static PAINTSTRUCT ps;	//	描画情報格納用

	switch( uMsg )
	{
	case WM_DESTROY:		//	ウインドウ破棄のメッセージ

		PostQuitMessage( 0 );//	"WM_QUIT"メッセージを返す
		break;

	case WM_KEYDOWN:	//	キー入力
		switch( wParam )
		{
			case VK_ESCAPE:	//	ESCAPEキー
			nSelect = MessageBox( NULL , "アプリケーションを終了しますか？" , "終了メッセージ" , MB_YESNO | MB_ICONQUESTION );

			if (nSelect == IDYES)
			{
				DestroyWindow(hWnd);
			}

			break;
		}
	}

	return DefWindowProc( hWnd , uMsg , wParam , lParam );	//	既定の処理を提供
}

void Init(void)
{
	InitWindow(); // ウィンドウの初期化
	WindowCreate(); // ウィンドウの生成

	GameLoop::Instance()->Init(g_Instance, g_hWnd);
}

/*-----------------------------------------------------------------------------
Function:   bool Loop(void)
Return:     return true;
              ループ続行
            return false;
			  ループ終了
Overview:   ループ部分
-----------------------------------------------------------------------------*/
bool Loop(void)
{
	//	メッセージループ
	//	第１引数：メッセージ情報
	//	第２引数：ウインドウのハンドル
	//	第３引数：最初のメッセージ
	//	第４引数：最後のメッセージ
	if (PeekMessage(&g_Msg, NULL, 0, 0, PM_REMOVE) != 0)
	{
		//	Windowsの処理
		if (g_Msg.message == WM_QUIT){ return false; }
		else
		{
			//	呼び出し側スレッドのメッセージキューから
			//	メッセージの翻訳と送出
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
	GameLoop::Destroy(); // インスタンス破棄

	//	ウインドウクラスの登録を解除
	//	第一引数：メクラス名
	//	第二引数：アプリケーションインスタンス
	UnregisterClass(CLASS_NAME, g_Wcex.hInstance);

	return (int)g_Msg.wParam;
}

/*-----------------------------------------------------------------------------
Function:   void InitWindow(void)
Overview:   ウィンドウの初期化
-----------------------------------------------------------------------------*/
void InitWindow(void)
{
	//	ウインドウのパーツ登録
	g_Wcex.cbSize = sizeof(WNDCLASSEX);					//	WNDCLASSEXのメモリサイズを指定
	g_Wcex.style = CS_CLASSDC;							//	表示するウインドウのスタイルを設定
	g_Wcex.lpfnWndProc = WndProc;						//	ウィンドウプロシージャのアドレス( 関数名 )を指定　プロトタイプ宣言した関数を書く（重要！！）
	g_Wcex.cbClsExtra = 0;								//	通常は使用しないので" 0 "を指定
	g_Wcex.cbWndExtra = 0;								//	通常は使用しないので" 0 "を指定
	g_Wcex.hInstance = g_Instance;						//	WinMainのパラメータのインスタンスハンドルを設定
	g_Wcex.hIcon = ICON_DATA;								//	使用するアイコンを指定( Windowsが持っているアイコンを使うなら )
	g_Wcex.hCursor = LoadCursor(NULL, IDC_ARROW);		//	マウスカーソルを指定	（授業ではやらない）
	g_Wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);	//	ウインドウのクライアント領域の背景色を設定	（授業ではやらない）
	g_Wcex.lpszMenuName = NULL;							//	Windowsにつけるメニューを設定
	g_Wcex.lpszClassName = CLASS_NAME;					//	ウインドウクラスの名前	（重要！！）
	g_Wcex.hIconSm = NULL;								//	小さいアイコンが設定された場合の情報を記述	（授業ではやらない）

	//	ウインドウクラスの登録
	RegisterClassEx(&g_Wcex);	//	オリジナルのウインドウパーツの名前をつける( カスタムウインドウ用の設定 )
}

/*-----------------------------------------------------------------------------
Function:   void WindowCreate(void)
Overview:   ウィンドウの生成
-----------------------------------------------------------------------------*/
void WindowCreate(void)
{
	const int Windowstyle = WS_OVERLAPPEDWINDOW ^ WS_MINIMIZEBOX ^ WS_THICKFRAME;

	//	描画領域のサイズからウインドウの矩形を取得
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

	//	ウインドウの作成
	g_hWnd = CreateWindowEx(0,	//	拡張ウインドウスタイル（　きちんと設定する　）
		CLASS_NAME,				//	ウインドウクラスの名前
		WINDOW_NAME,			//	ウインドウの名前
		Windowstyle,			//	ウインドウスタイル
		wx,						//	ウインドウの左上Ｘ座標
		wy,						//	ウインドウの左上Ｙ座標
		ww,						//	ウインドウの幅（　フレームも合わせた幅　）
		wh,						//	ウインドウの高さ（　フレームも合わせた高さ　）
		NULL,					//	親ウインドウのハンドル（　ポインタ　）
		NULL,					//	メニューハンドルまたは子ウインドウID
		g_Instance,				//	インスタンスハンドル
		NULL);					//	ウインドウ作成データ

	//	ウインドウの表示
	ShowWindow(g_hWnd, g_CmdShow);	//	指定されたウインドウの表示
	UpdateWindow(g_hWnd);			//	ウインドウの状態を直ちに反映
}
