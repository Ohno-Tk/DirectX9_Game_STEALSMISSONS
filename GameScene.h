/*=============================================================================

�Q�[���V�[��[ GameScene.h ]

-------------------------------------------------------------------------------

��  Create
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

	// �Q�[������
	static void GameClear(void){ m_GameClear = true; }
	static void GameOver(void){ m_GameOver = true; }

	// Getter
	static Player* GetPlayer(void){return m_Player;}
	static MeshField* GetMeshField(void) { return m_MeshField; }
	static MeshWall* GetMeshWall(const int index) { return m_MeshWall[index]; }
	static ItemUI* GetItemUI(void){ return m_ItemUI; }

private:
	void SceneChange(void); // �V�[����ς���

private:
	static bool m_GameClear; // �Q�[���N���A
	static bool m_GameOver; // �Q�[���I�[�o�[
	bool m_SceneChangeFlag;

	static Player* m_Player; // �v���C���[
	static MeshField* m_MeshField; // ���b�V���t�B�[���h
	static MeshWall* m_MeshWall[MESHWALL_NUM]; // ���b�V���E�H�[��
	static Goal* m_Goal; // �S�[��
	static ItemUI* m_ItemUI;

	DirectXKeyboard* m_KeyBoard;
	SoundDirectX* m_Sound;
};

#endif
