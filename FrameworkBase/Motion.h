/*=============================================================================

モーション[ Motion.h ]

-------------------------------------------------------------------------------
■  Author
	Ohno Takuya

■  Create
	2017/08/07
=============================================================================*/

#ifndef _MOTION_H_
#define _MOTION_H_

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include <stdio.h>

/*-----------------------------------------------------------------------------
Macro
-----------------------------------------------------------------------------*/
#define MAX_MOTION (10)	//	最大モーション数

/*-----------------------------------------------------------------------------

-----------------------------------------------------------------------------*/
class MotionCharacterData;
class VertexShader;
class PixelShader;

/*-----------------------------------------------------------------------------
	Class
-----------------------------------------------------------------------------*/
class Motion:public Object
{
public:
	Motion(int Priolity);

	static Motion *Create(const int Priolity, char* TextFileName);

	void Initialize(void)override;
	void Uninitialize(void)override;
	void Update(void)override;
	void Draw(void)override;

	//	Setter
	void SetTextFileName(char *data) { m_TextFileName = data; }
	void SetMotionIndex(const int index);
	void SetRotation(const D3DXVECTOR3 rot) { m_Rotation = rot; }
	void SetPartsRotation(const int index, const D3DXVECTOR3 rot){ m_CharacterData.PartInfo[index].OffsetRot = rot; }

	//	Getter
	D3DXVECTOR3 GetRotation(void) { return m_Rotation; }
	D3DXVECTOR3 GetPartsPosition(const int index){ return m_CharacterData.PartInfo[index].OffsetPos; }
	D3DXVECTOR3 GetPartsRotation(const int index){ return m_CharacterData.PartInfo[index].OffsetRot; }
	D3DXMATRIX GetPartsMatrix(const int index){ return m_CharacterData.PartInfo[index].MatrixWorld; }
	bool GetMotionEnd(void) { return m_MotionEnd; }
	D3DXMATRIX GetMatrix(void){return m_MtxWorld;}

private:
	void MotionInterpolation(void);	//	モーション補間
	void MotionBlend(void);	//	モーションブレンド
	void WorldTransform(LPDIRECT3DDEVICE9 Device);//	ワールド座標変換
	void PartWorldTransform(const int cntmodel, LPDIRECT3DDEVICE9 Device);	//	パーツごとのワールド座標変換
	void ReadText(void);											//	テキストファイルの読み込み
	void ReadNumModel(FILE *fp);									//	モデル数の読み込み
	void ReadModelFileName(FILE *fp);								//	モデルファイル名の読み込み
	void LoadModel(const int nummodel, char *modelfilename);		//	モデルのロード
	void ReadCharacterInfo(FILE *fp);								//	キャラクタ情報の読み込み
	void ReadPartsSet(FILE *fp);									//	キャラクタのパーツ情報の読み込み
	void ReadMotion(FILE *fp);										//	モーション情報の読み込み
	void InitializePartsData(void);
	void InitializeMotionData(int countMotion);
	bool MatchFileToken(char* buffer, char* fileToken);		// ファイルトークンの一致
	bool MisMatchFileToken(char* buffer, char* fileToken); // ファイルトークンの不一致
	virtual void ConfigShader(LPDIRECT3DDEVICE9 device);


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
		EQUAL,
		LAST_WORD,
		MAX_TOKEN
	};

	struct KEYINFO
	{
		D3DXVECTOR3 *Pos;
		D3DXVECTOR3 *Rot;
	};

	struct PART
	{
		int					Index;		//	パーツ番号
		int					Parent;		//	親子構造
		D3DXVECTOR3			OffsetPos;	//	初期座標
		D3DXVECTOR3			OffsetRot;	//	初期回転
		D3DXVECTOR3			Pos;		//	補間座標
		D3DXVECTOR3			Rot;		//	補間回転
		D3DXVECTOR3			Scale;
		D3DXMATRIX			MatrixWorld;	//	ワールドマトリクス
		D3DXMATRIX			MatrixScl;		//	拡大マトリクス
		D3DXMATRIX			MatrixRot;		//	回転マトリクス
		D3DXMATRIX			MatrixPos;		//	座標マトリクス
		MODEL_PARAM			ModelParam;
	};

	struct MOTION
	{
		int Loop;		//	ループするか
		int NumKey;		//	キー数
		int *Frame;		//	フレーム数
		KEYINFO *Next;	//	次の場所
	};

	struct CHARACTERDATA
	{
		PART* PartInfo; // パーツ情報
		MOTION Motion[MAX_MOTION]; // モーション情報
		int NumModel; // モデル数
	};

	D3DXMATRIX	m_MtxWorld;	//	ワールドマトリクス

	D3DXVECTOR3 m_Rotation;	//	回転
	D3DXVECTOR3 m_Scale;	//	拡大

	int m_MotionIndex;	//	モーション番号
	int m_NumKeyCount;	//	キー数
	int m_MotionCount;	//	モーションカウンタ

	static char* m_FileToken[MAX_TOKEN];	//	トークン
	static char m_Buffer[256];		//	テキストデータ読み込みのバッファ
	char* m_TextFileName;	//	テキストのファイル名

	CHARACTERDATA m_CharacterData; // キャラクター情報

	bool m_MotionEnd;

	int m_BlendMotionIndex;
	int m_BlendNumKey;
	int m_BlendUpdateCount;
	int m_MotionBlendFrame;
	MOTION m_BlendMotion[MAX_MOTION];

	VertexShader* m_VertexShader;
	PixelShader* m_PixelShader;

	LPDIRECT3DVERTEXDECLARATION9 m_VertexDeclaration;
};

#endif