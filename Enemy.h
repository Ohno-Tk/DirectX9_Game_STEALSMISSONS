/*=============================================================================

�G[ Enemy.h ]

-------------------------------------------------------------------------------

��  Create
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
		D3DXVECTOR3 ControlPoint;	//	����_
		D3DXVECTOR3 ControlVector;	//	�ڐ��x�N�g��
		D3DXVECTOR3 ControlVectorNext;
		D3DXVECTOR3 InitControlVector;	//	�ڐ��x�N�g��
		D3DXVECTOR3 InitControlVectorNext;
		int FrameTime;	//	�t���[������
		int WaitTime;	//	�ҋ@����
		float Rot;			//	�p�x
	};

	Enemy(int Priolity = 3);

	static Enemy* Create(char* filename); // ����

	bool VisionRangeCollision(D3DXVECTOR3 Position, int Angle, int Distance); //	���E�̔���
	bool AttackRangeCollision(D3DXVECTOR3 Position, int Angle, int Distance); // �U������
	bool AttackCollision(D3DXVECTOR3 Position); // �U���̔���
	bool DistanceWithinCollision(float distance); // ��苗���ȓ��̔���

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
	void RoadFile(void); //	�t�@�C���̓ǂݎ��
	bool ObstacleCollision(D3DXVECTOR3 aabbmin, D3DXVECTOR3 aabbmax, D3DXMATRIX inverse);

private:
	D3DXVECTOR3 m_OldPosision;
	D3DXVECTOR3 m_FrontVector;

	int m_NumLinear;	//	������Ԃ��邩
	int m_CountLinear;
	int m_VisionAngle; // ���E�p�x
	int m_VisionDistance; // ���E����
	int m_AttackRange; // �U���͈�
	int m_AttackPower; // �U����

	float m_NowRotation;

	char* m_FileName;//	�t�@�C����

	LINEAR* m_Linear; // ��ԍ\����

	StencilShadow* m_Shadow; // �e
	HeadMark* m_HeadMark;
	Vision* m_Vision;
};

#endif
