/*=============================================================================

オブジェクト生成[ Object.h ]

-------------------------------------------------------------------------------
■  Author
Ohno Takuya

■  Create
2017/11/11
=============================================================================*/

#ifndef _OBJECT_H_
#define _OBJECT_H_

/*-----------------------------------------------------------------------------
	Macro
-----------------------------------------------------------------------------*/
#define PRIOLITY_MAX (6) //	優先順位

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class Object
{
public:
	enum OBJECT_TYPE
	{
		OBJECT_TYPE_NONE = 0,	//	なし
		OBJECT_TYPE_PLAYER,     // プレイヤー
		OBJECT_TYPE_ENEMY,		//	敵
		OBJECT_TYPEMESHSPHERE,	//	メッシュ球
		OBJECT_TYPE_CONTROLPOINT, // 制御点
		OBJECT_TYPE_VISION, // 視界
		OBJECT_TYPE_OBSTACLE, // 障害物
		OBJECT_TYPE_MAX			//	最大数
	};

	Object(int Priolity);

	virtual void Initialize(void) = 0;
	virtual void Uninitialize(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	static void UpdateAll(void); //	全オブジェクトの更新
	static void DrawAll(void); // 全オブジェクトの描画
	static void ReleaseAll(void); // 全オブジェクトの解放

	// Setter
	void SetPosition(const D3DXVECTOR3 position) { m_Position = position; }

	//	Getter
	D3DXVECTOR3 GetPosition(void) { return m_Position; }
	D3DXVECTOR3* GetPositionPointer(void) { return &m_Position; }

	const OBJECT_TYPE GetObjeType(void)const{ return m_ObjectType; }

	static Object *GetList(int Priority) { return m_Top[Priority]; }
	Object *GetNext(void) { return m_Next; }

private:
	D3DXVECTOR3 m_Position;	//	座標
	bool m_DeleteFlag;	//	削除フラグ

	OBJECT_TYPE m_ObjectType; // オブジェクトの種類

	static Object* m_Top[PRIOLITY_MAX];	//	先頭のポインタ
	Object* m_Next;	//	次のポインタ

protected:
	// Setter
	void SetObjeType(const OBJECT_TYPE objectType) { m_ObjectType = objectType; }

	void Release(void) { m_DeleteFlag = true; }	//	リリース
};

#endif
