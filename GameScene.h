/*=============================================================================

ゲームシーン[ GameScene.h ]

-------------------------------------------------------------------------------
■  Author
Ohno Takuya

■  Create
2017/11/11
=============================================================================*/

#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "FrameworkBase\Scene.h"

/*-----------------------------------------------------------------------------
Macro
-----------------------------------------------------------------------------*/
#define MESHWALL_NUM (4)

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class DirectXKeyboard;
class SoundDirectX;
class Player;
class MeshField;
class MeshWall;
class Goal;
class ItemUI;

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class GameScene:public Scene
{
public:
	void Initialize(void)override;
	void Uninitialize(void)override;
	void Update(void)override;
	void Draw(void)override;

	// ゲーム条件
	static void GameClear(void){ m_GameClear = true; }
	static void GameOver(void){ m_GameOver = true; }

	// Getter
	static Player* GetPlayer(void){return m_Player;}
	static MeshField* GetMeshField(void) { return m_MeshField; }
	static MeshWall* GetMeshWall(const int index) { return m_MeshWall[index]; }
	static ItemUI* GetItemUI(void){ return m_ItemUI; }

private:
	void SceneChange(void); // シーンを変える

private:
	static bool m_GameClear; // ゲームクリア
	static bool m_GameOver; // ゲームオーバー
	bool m_SceneChangeFlag;

	static Player* m_Player; // プレイヤー
	static MeshField* m_MeshField; // メッシュフィールド
	static MeshWall* m_MeshWall[MESHWALL_NUM]; // メッシュウォール
	static Goal* m_Goal; // ゴール
	static ItemUI* m_ItemUI;

	DirectXKeyboard* m_KeyBoard;
	SoundDirectX* m_Sound;
};

#endif
