/*=============================================================================

ゲームループ[ GameLoop.cpp ]

-------------------------------------------------------------------------------
■  Author
Ohno Takuya

■  Create
2017/11/11
=============================================================================*/

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "Common.h"
#include "Game.h"
#include "GameLoop.h"

/*-----------------------------------------------------------------------------
Static
-----------------------------------------------------------------------------*/
GameLoop* GameLoop::m_Instance = NULL;

/*-----------------------------------------------------------------------------
Function:   Game* Game::Instance(void)
Overview:   インスタンス生成
-----------------------------------------------------------------------------*/
GameLoop* GameLoop::Instance(void)
{
	if(!m_Instance)
	{
		m_Instance = new GameLoop;
	}

	return m_Instance;
}

/*-----------------------------------------------------------------------------
Function:   void GameLoop::Destroy(void)
Overview:   インスタンス破棄
-----------------------------------------------------------------------------*/
void GameLoop::Destroy(void)
{
	SAFE_DELETE(m_Instance);
}

GameLoop::GameLoop()
{
	m_FrameCount = 0;
	m_CurrentTime = 0; //	現在の時間
	m_ExecLastTime = 0; // 現在の時刻をミリ単位で取得
	m_FPSLastTime = 0;
	m_CountFPS = 0; // FPSカウンタ
}

void GameLoop::Init(HINSTANCE hInstance, HWND hWnd)
{
	//	分解能の設定（タイマーの精度を良くする）
	timeBeginPeriod(1);

	//	各カウンターの初期化
	m_FrameCount = 0;
	m_CurrentTime = 0;				//	現在の時間
	m_ExecLastTime = timeGetTime();	//	現在の時刻をミリ単位で取得
	m_FPSLastTime = m_ExecLastTime;

	Game::GetInstance()->Init(hInstance, hWnd);
}

void GameLoop::ClockFps(void)
{
	m_CurrentTime = timeGetTime();	//	現在の時刻をミリ単位で取得

	if ((m_CurrentTime - m_FPSLastTime) >= 500)
	{

		m_CountFPS = (m_FrameCount * 1000) / (m_CurrentTime - m_FPSLastTime);
		m_FPSLastTime = m_CurrentTime;
		m_FrameCount = 0;

	}

	if ((m_CurrentTime - m_ExecLastTime) >= (1000 / 60))
	{	//	現在のフレームからどれ位たったのか( 差分計算 )	デバッグで計測したいときはifをコメントアウト

		m_ExecLastTime = m_CurrentTime;	//	処理した時間を保存

		// 更新処理
		Game::GetInstance()->Update();

		// 描画処理
		Game::GetInstance()->Draw();

		m_FrameCount++;

	}
}

void GameLoop::Uninit(void)
{
	Game::GetInstance()->Uninit();
}