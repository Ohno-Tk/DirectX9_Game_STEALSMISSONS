/*=============================================================================

ゲームループ[ GameLoop.h ]
(シングルトンパターン)

-------------------------------------------------------------------------------
■  Author
Ohno Takuya

■  Create
2017/11/11
=============================================================================*/

#ifndef _GAMELOOP_H_
#define _GAMELOOP_H_

/*-----------------------------------------------------------------------------
Library
[構成プロパティ]->[リンカー]->[入力]->[追加の依存ファイル]に記述しても可能
-----------------------------------------------------------------------------*/
#pragma comment( lib , "winmm.lib" )

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class GameLoop
{
public:
	static GameLoop* Instance(void); // インスタンス生成
	static void Destroy(void); // インスタンス破棄

	void Init(HINSTANCE hInstance, HWND hWnd); // 初期化
	void ClockFps(void); //	FPS計測
	void Uninit(void); // 終了

	// Getter
	const int GetFPS(void){ return m_CountFPS; } // FPS取得

private:
	GameLoop();

private:
	static GameLoop* m_Instance;

	DWORD m_FrameCount;
	DWORD m_CurrentTime; // 現在の時間
	DWORD m_ExecLastTime; // 現在の時刻をミリ単位で取得
	DWORD m_FPSLastTime;
	int m_CountFPS; //	FPSカウンタ
};

#endif
