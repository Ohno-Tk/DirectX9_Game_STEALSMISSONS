/*=============================================================================

共通部分[ Common.h ]
( 次回使用時はRenderer.hの次にインクルードする
 メモリリーク検出がd3dxmath.hの前に記述するとエラーを検出)
-------------------------------------------------------------------------------
■  Author
Ohno Takuya

■  Create
2017/11/11
=============================================================================*/

#ifndef _COMMON_H_
#define _COMMON_H_

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#ifdef _DEBUG
	#include <crtdbg.h>
#endif
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <windows.h>

/*-----------------------------------------------------------------------------
Macro
-----------------------------------------------------------------------------*/
//#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)	//	メモリリーク検出(出力デバッグに表示される)

#define SCREEN_WIDTH   ( 800 ) // 画面サイズ(横)
#define SCREEN_HEIGHT  ( 600 ) // 画面サイズ(縦)

#define TEXTURE_PATH "data/TEXTURE/" // テクスチャのパス
#define MODEL_PATH   "data/MODEL/"   // モデルのパス
#define MOTION_PATH  "data/MOTION/"	 //	モーションのパス
#define SHADER_PATH  "data/SHADER/"  // シェーダーのパス

#define SAFE_UNINIT(p)      if(p){ p->Uninitialize(); delete p; p = NULL; }// ポインタの終了処理マクロ
#define SAFE_DELETE(p)      if(p){ delete p; p = NULL; }             // ポインタの解放処理マクロ
#define SAFE_ARRAYDELETE(p) if(p){ delete[] p; p = NULL; }           // 配列の解放マクロ

#define ENABLE_SOUND
#undef ENABLE_SOUND

#define ENABLE_XINPUT
//#undef ENABLE_XINPUT

#endif
