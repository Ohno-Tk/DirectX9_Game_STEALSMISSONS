/*=============================================================================

敵[ Enemy.h ]

-------------------------------------------------------------------------------
■  Author
Ohno Takuya

■  Create
2017/11/11
=============================================================================*/

#ifndef _ENEMY_H_
#define _ENEMY_H_

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "Human.h"

/*-----------------------------------------------------------------------------

-----------------------------------------------------------------------------*/
class StencilShadow;
class HeadMark;
class Vision;

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class Enemy:public Human
{
public:
	struct LINEAR
	{
		D3DXVECTOR3 ControlPoint;	//	制御点
		D3DXVECTOR3 ControlVector;	//	接線ベクトル
		D3DXVECTOR3 ControlVectorNext;
		D3DXVECTOR3 InitControlVector;	//	接線ベクトル
		D3DXVECTOR3 InitControlVectorNext;
		int FrameTime;	//	フレーム時間
		int WaitTime;	//	待機時間
		float Rot;			//	角度
	};

	Enemy(int Priolity = 3);

	static Enemy* Create(char* filename); // 生成

	bool VisionRangeCollision(D3DXVECTOR3 Position, int Angle, int Distance); //	視界の判定
	bool AttackRangeCollision(D3DXVECTOR3 Position, int Angle, int Distance); // 攻撃判定
	bool AttackCollision(D3DXVECTOR3 Position); // 攻撃の判定
	bool DistanceWithinCollision(float distance); // 一定距離以内の判定

	// Setter
	void SetOldPosition(void){ Object::SetPosition(m_OldPosision); }
	void SetCountNumLinear(const int countLinear){ m_CountLinear = countLinear; }
	void SetNowRotation(const float rotation){ m_NowRotation = rotation; }
	void SetHeadMarkActive(const bool flag);
	void SetHeadMarkTextureChange(char* texturePath);

	// Getter
	D3DXVECTOR3 GetFrontVector(void){ return m_FrontVector; }
	LINEAR GetLinearStruct(const unsigned int index){return m_Linear[index];}
	int GetVisionAngle(void){ return m_VisionAngle; }
	int GetVisionDistance(void){ return m_VisionDistance; }
	int GetAttackRange(void){ return m_AttackRange; }
	int GetNumLinear(void){return m_NumLinear;}
	int GetCountLinear(void){ return m_CountLinear; }
	float GetNowRotation(void){ return m_NowRotation; }

private:
	void Initialize(void)override;
	void Uninitialize(void)override;
	void Update(void)override;
	void Draw(void)override;
	void RoadFile(void); //	ファイルの読み取り
	bool ObstacleCollision(D3DXVECTOR3 aabbmin, D3DXVECTOR3 aabbmax, D3DXMATRIX inverse);

private:
	D3DXVECTOR3 m_OldPosision;
	D3DXVECTOR3 m_FrontVector;

	int m_NumLinear;	//	いくつ補間するか
	int m_CountLinear;
	int m_VisionAngle; // 視界角度
	int m_VisionDistance; // 視界距離
	int m_AttackRange; // 攻撃範囲
	int m_AttackPower; // 攻撃力

	float m_NowRotation;

	char* m_FileName;//	ファイル名

	LINEAR* m_Linear; // 補間構造体

	StencilShadow* m_Shadow; // 影
	HeadMark* m_HeadMark;
	Vision* m_Vision;
};

#endif
