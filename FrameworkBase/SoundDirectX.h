/*=============================================================================

サウンド(DirectX)[ ConfigWindows.h ]

-------------------------------------------------------------------------------
■  Author
	Ohno Takuya

■  Create
	2017/10/15
=============================================================================*/

#ifndef _SOUND_H_
#define _SOUND_H_

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "RendererDirectX.h"

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class SoundDirectX
{
public:
	SoundDirectX();

	// サウンドファイル
	enum SOUND_LABEL
	{
		SOUND_BGM_TITLESCENE = 0,	//	タイトルBGM
		SOUND_BGM_GAMESCENE,		// ゲームBGM
		SOUND_SE_TITLEGUN,	//	タイトル銃音
		SOUND_SE_SELECT,		// 選択移動音
		SOUND_SE_EXIT,		// 終了音
		SOUND_SE_GAMECLEAR,		// ゲームクリア
		SOUND_SE_GAMEOVER,		// ゲームオーバー
		SOUND_SE_FOUND,	//	発見音
		SOUND_SE_CALL,	//	call音
		SOUND_SE_HEAL,	// 回復音
		SOUND_SE_GETITEM,// アイテム取得
		SOUND_LABEL_MAX

	};

	HRESULT Initialize(void);	//	初期化
	void Uninitialize(void);	//	終了

	HRESULT Play(SOUND_LABEL label);					//	音楽再生
	void Stop(SOUND_LABEL label);						//	何番目の音を止める
	void Stop(void);									//	停止
	void SetVolume(SOUND_LABEL label, float fValue);	//	ボリューム設定

private:
	// パラメータ構造体
	struct PARAM
	{
		char *pFilename;	// ファイル名
		int nCntLoop;		// ループカウンタ

	};

	HRESULT CheckChunk(HANDLE hFile, DWORD dwFormat, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *m_pXAudio2;									// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *m_pMasteringVoice;				// マスターボイス
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// ソースボイス
	BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// オーディオデータサイズ

	static PARAM m_aParam[SOUND_LABEL_MAX];					// パラメータ
};

#endif