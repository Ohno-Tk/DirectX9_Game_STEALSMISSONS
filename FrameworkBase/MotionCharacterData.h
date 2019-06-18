/*=============================================================================

モーションキャラクターデータ[ MotionCharacterData.h ]
(Maybe-Later:Uninitializeでエラーを吐いている)
-------------------------------------------------------------------------------
■  Author
Ohno Takuya

■  Create
2017/11/13
=============================================================================*/

#ifndef _MOTIONCHARACTERDATA_H_
#define _MOTIONCHARACTERDATA_H_

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include <fstream>
#include "ModelManagerDirectX.h"

/*-----------------------------------------------------------------------------
Macro
-----------------------------------------------------------------------------*/
#define MAX_MOTION (10)	//	最大モーション数

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class MotionCharacterData
{
public:
	struct KEYINFO
	{
		D3DXVECTOR3* Position;
		D3DXVECTOR3* Rotation;
	};

	struct PART
	{
		int			Index;			//	パーツ番号
		int			Parent;			//	親子構造
		D3DXVECTOR3	OffsetPosition;	//	初期座標
		D3DXVECTOR3	OffsetRotation;	//	初期回転
		D3DXVECTOR3	Position;		//	補間座標
		D3DXVECTOR3	Rotation;		//	補間回転
		D3DXVECTOR3	Scale;			//	拡大
		D3DXMATRIX	MatrixWorld;	//	ワールドマトリクス
		D3DXMATRIX	MatrixRotation;	//	回転マトリクス
		D3DXMATRIX	MatrixPosition;	//	座標マトリクス
		D3DXMATRIX	MatrixScale;	//	拡大マトリクス		
		MODEL_PARAM	ModelParam; // モデル情報
	};

	struct MOTION
	{
		int Loop;		//	ループするか
		int NumKey;		//	キー数
		int* Frame; // フレーム数
		KEYINFO *Next;	//	次の場所
	};

	struct CHARACTERDATA
	{
		PART* PartInfo; // パーツ情報
		MOTION Motion[MAX_MOTION]; // モーション情報
		int NumModel; // モデル数
	};

public:
	MotionCharacterData();

	void Initialize(void);
	void Uninitialize(void){ UnloadAll(); }

	// Getter
	const CHARACTERDATA GetCharacterData(std::string motionFilePass)const;

private:
	void Load(std::string motionFilePass);		// モーションデータロード
	void UnloadAll(void);						// モーションキャラクターデータの全削除
	void InitCharaData(void);					// キャラクターデータの初期化
	void InitMotionData(const int countMotion);	// モーションデータの初期化

	void ReadText(std::string motionFilePass);							//	テキストファイルの読み込み
	void ReadNumModel(void);											//	モデル数の読み込み
	void ReadModelFileName(void);										// モデルファイル名の読み込み
	void LoadModel(const int nummodel, std::string modelfilename);		//	モデルのロード
	void ReadCharacterInfo(void);										//	キャラクタ情報の読み込み
	void ReadPartsSet(void);											//	キャラクタのパーツ情報の読み込み
	void ReadMotion(void);												//	モーション情報の読み込み

	bool MatchFileToken(std::string buffer, std::string fileToken);		// ファイルトークンの一致
	bool MisMatchFileToken(std::string buffer, std::string fileToken); // ファイルトークンの不一致

private:
	enum TOKEN
	{
		SCRIPT = 0,
		END_SCRIPT,
		NUM_MODEL,
		MODEL_FILENAME,
		CHARACTERSET,
		END_CHARACTERSET,
		PARTSSET,
		END_PARTSSET,
		INDEX,
		PARENT,
		POS,
		ROT,
		MOTIONSET,
		END_MOTIONSET,
		LOOP,
		NUMKEY,
		KEYSET,
		END_KEYSET,
		FRAME,
		KEY,
		END_KEY,
		LAST_WORD,
		MAX_TOKEN
	};

	CHARACTERDATA m_CharacterData; // キャラクター情報

	std::string m_Buffer;
	std::vector<std::string> m_TextFileToken;	// ファイルトークン
	std::ifstream m_ReadFile;					// ファイルを読み込む
	std::unordered_map< std::string, CHARACTERDATA > m_Motion_Map;
};

#endif
