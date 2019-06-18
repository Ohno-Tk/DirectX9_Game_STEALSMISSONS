/*=============================================================================

敵[ Enemy.cpp ]

-------------------------------------------------------------------------------
■  Author
Ohno Takuya

■  Create
2017/11/11
=============================================================================*/

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "FrameworkBase\Common.h"
#include "FrameworkBase\Debug.h"
#include "FrameworkBase\RendererDirectX.h"
#include "FrameworkBase\FileManager.h"
#include "FrameworkBase\ModelManagerDirectX.h"
#include "FrameworkBase\Mathematics.h"
#include "FrameworkBase\Collision.h"
#include "GameScene.h"
#include "Object.h"
#include "SpriteModeX.h"
#include "MeshSphere.h"
#include "StencilShadow.h"
#include "HeadMark.h"
#include "Vision.h"
#include "Player.h"
#include "ControlPoint.h"
#include "Enemy.h"
#include "EnemyStatePatrol.h"

/*-----------------------------------------------------------------------------
Macro
-----------------------------------------------------------------------------*/
#define ENEMY_MOTION_PATH (MOTION_PATH"Enemy.txt")

/*-----------------------------------------------------------------------------
Namespace
-----------------------------------------------------------------------------*/
using namespace std;

float t = 0.0f;

Enemy::Enemy(int Priolity):Human(Priolity)
{
	m_OldPosision = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_FrontVector = D3DXVECTOR3(0.0f,0.0f,0.0f);

	m_NumLinear = 0;
	m_CountLinear = 0;
	m_VisionAngle = 50;
	m_VisionDistance = 45;
	m_AttackRange = 14;
	m_AttackPower = 10;

	m_NowRotation = 0.0f;

	m_Linear = NULL;
	m_Shadow = NULL;
	m_HeadMark = NULL;
}

/*-----------------------------------------------------------------------------
Function:   Enemy* Enemy::Create(char* filename)
Parameter:  char* filename
              テキストファイル名
Overview:   生成
-----------------------------------------------------------------------------*/
Enemy* Enemy::Create(char* filename)
{
	auto object = new Enemy;

	object->m_FileName = filename;

	object->SetTextFileName(ENEMY_MOTION_PATH);

	object->Initialize();

	return object;
}

void Enemy::Initialize(void)
{
	Human::Initialize();

	RoadFile(); // ファイルの読み取り

	D3DXVECTOR3 position = Object::GetPosition();

	SetObjeType(OBJECT_TYPE_ENEMY); // オブジェクト種類のセット

	Human::SetState(new EnemyStatePatrol(this));

	m_Shadow = StencilShadow::Create(MODEL_PATH"StecilShadow.x"); // 影の生成
	m_HeadMark = HeadMark::Create(D3DXVECTOR3(position.x, position.y + 15.0f, position.z));
	m_Vision = Vision::Create(m_VisionDistance, m_VisionAngle);
}

void Enemy::Uninitialize(void)
{
	Human::Uninitialize();

	m_Shadow = NULL;
	m_HeadMark = NULL;
	m_Vision = NULL;

	SAFE_ARRAYDELETE(m_Linear);
}

void Enemy::Update(void)
{
	D3DXVECTOR3 position = Object::GetPosition();
	D3DXMATRIX headMatrix = Motion::GetPartsMatrix(1);

	m_OldPosision = position;

	Human::Update();

	m_Shadow->SetPosition(position);
	m_HeadMark->SetPosition(D3DXVECTOR3(position.x, position.y + 15.0f, position.z));
	m_Vision->SetOwnerMatrix(headMatrix);

	VisionRangeCollision(position, m_VisionAngle, m_VisionDistance);
	t++;
}

void Enemy::Draw(void)
{
	Human::Draw();
}

/*-----------------------------------------------------------------------------
Function:   void Enemy::VisionRangeCollision(D3DXVECTOR3 Position, int Angle, int Distance)
Parameter:  D3DXVECTOR3 Position
              座標
			int Angle
			  角度
			int Distance
			  距離
Overview:   範囲の判定
-----------------------------------------------------------------------------*/
bool Enemy::VisionRangeCollision(D3DXVECTOR3 Position, int Angle, int Distance)
{
	D3DXVECTOR3 Rot = Motion::GetRotation();

	D3DXVECTOR3 PlayerPos = GameScene::GetPlayer()->GetPosition();

	//	敵から自分へのベクトル
	D3DXVECTOR3 VectorEnemyPlayer = PlayerPos - Position;

	//	自分の正面ベクトル
	D3DXVECTOR3 FrontPosition;
	float i , j;
	i = sinf(D3DXToRadian(Rot.y));
	j = cosf(D3DXToRadian(Rot.y));
	FrontPosition.x = Position.x - i * Distance;
	FrontPosition.y = 0.0f;
	FrontPosition.z = Position.z - j * Distance;
	m_FrontVector = FrontPosition - Position;

	// 前方の角度を決める
	float w = Angle / 180.0f; 
	float EnemyAngle = 1 - w;

	//	2つのベクトルのなす角度を求める
	Angle2Vector angle2vector(VectorEnemyPlayer);
	float AngleVector = angle2vector.Angle(m_FrontVector);

	if( int(AngleVector) < EnemyAngle)
	{	//	角度を判定

		float Len;
		Len = D3DXVec3Length( &VectorEnemyPlayer);	//	長さを求める

		if( int(Len) < Distance )
		{	//	距離の判定

/*			for (int CntPriolity = 0; CntPriolity < PRIOLITY_MAX; CntPriolity++)
			{
				Object *object = Object::GetList(CntPriolity);
				while (object != NULL)
				{
					if (object->GetObjeType() == Object::OBJECT_TYPE_OBSTACLE)
					{
						Obstacle *obstacle = (Obstacle*)object;

						D3DXVECTOR3 aabbmin = D3DXVECTOR3( -8.285f, 0.04232f, -8.285f );
						D3DXVECTOR3 aabbmax = D3DXVECTOR3( 8.285f, 16.61232f, 8.285f );
						D3DXMATRIX inverseMatrix;
						D3DXMATRIX aabbMatrix = obstacle->GetMatrix();
						D3DXMatrixInverse( &inverseMatrix, 0, &aabbMatrix );

						if(ObstacleCollision(aabbmin, aabbmax, inverseMatrix))
						{
							return true;
						}
					}
					object = object->GetNext();
				}
			}*/
//			Debug::Log("見つかった ただの判定");
			return true;
		}
	}

	return false;
}

bool Enemy::AttackRangeCollision(D3DXVECTOR3 Position, int Angle, int Distance)
{
	D3DXVECTOR3 Rot = Motion::GetRotation();

	D3DXVECTOR3 PlayerPos = GameScene::GetPlayer()->GetPosition();

	//	敵から自分へのベクトル
	D3DXVECTOR3 VectorEnemyPlayer = PlayerPos - Position;

	//	自分の正面ベクトル
	D3DXVECTOR3 FrontPosition;
	float i , j;
	i = sinf(D3DXToRadian(Rot.y));
	j = cosf(D3DXToRadian(Rot.y));
	FrontPosition.x = Position.x - i * Distance;
	FrontPosition.y = 0.0f;
	FrontPosition.z = Position.z - j * Distance;
	m_FrontVector = FrontPosition - Position;

	// 前方の角度を決める
	float w = Angle / 180.0f; 
	float EnemyAngle = 1 - w;

	//	2つのベクトルのなす角度を求める
	Angle2Vector angle2vector(VectorEnemyPlayer);
	float AngleVector = angle2vector.Angle(m_FrontVector);

	if( int(AngleVector) < EnemyAngle)
	{	//	角度を判定

		float Len;
		Len = D3DXVec3Length( &VectorEnemyPlayer);	//	長さを求める

		if( int(Len) < Distance )
		{	//	距離の判定
			return true;
		}
	}

	return false;
}

bool Enemy::AttackCollision(D3DXVECTOR3 Position)
{
	Player* player = GameScene::GetPlayer();

	Collision_Sphere CollisionSphere(Position, 5.0f);

	if (CollisionSphere.Judge(player->GetPosition(), player->GetSphereRadius()))
	{ // 衝突判定
		player->AttackHit(m_AttackPower);
		return true;
	}

	return false;
}

bool Enemy::DistanceWithinCollision(float distance)
{
	D3DXVECTOR3 PlayerPos = GameScene::GetPlayer()->GetPosition();

	//	敵から自分へのベクトル
	D3DXVECTOR3 VectorEnemyPlayer = PlayerPos - Object::GetPosition();

	float length;
	length = D3DXVec3Length( &VectorEnemyPlayer);

	if( int(length) > distance )
	{
		return true;
	}

	return false;
}

bool Enemy::ObstacleCollision(D3DXVECTOR3 aabbmin, D3DXVECTOR3 aabbmax, D3DXMATRIX inverse)
{
	D3DXVECTOR3 p_l, dir_l;
	D3DXVec3TransformCoord( &p_l, &Motion::GetPosition(), &inverse );
	inverse._41 = 0.0f;
	inverse._42 = 0.0f;
	inverse._43 = 0.0f;
	D3DXVec3TransformCoord( &dir_l, &m_FrontVector, &inverse );

	// 交差判定
	float p[ 3 ], d[ 3 ], min[ 3 ], max[ 3 ];
	memcpy( p, &p_l, sizeof( D3DXVECTOR3 ) );
	memcpy( d, &dir_l, sizeof( D3DXVECTOR3 ) );
	memcpy( min, &aabbmin, sizeof( D3DXVECTOR3 ) );
	memcpy( max, &aabbmax, sizeof( D3DXVECTOR3 ) );

	t = -FLT_MAX;
	float t_max = FLT_MAX;
	int h = 2;

	for ( int i = 0; i < 3; ++i )
	{
		if ( abs( d[ i ] ) < FLT_EPSILON )
		{
			//if(min[i] * d[h] > max[h] * d[i] || min[i] * d[i] > max[i] * d[h])
			//{
			// Debug::Log("見つかった オブジェクトが間にいない");
			// return true;
			//}
								 
		if ( p[ i ] < min[ i ] || p[ i ] > max[ i ] )
		{ // 交差していない
				Debug::Log("見つかった オブジェクトが間にいない");
				return false;
		}
		else
		{
			// スラブとの距離を算出
			// t1が近スラブ、t2が遠スラブとの距離
			float odd = 1.0f / d[ i ];
			float t1 = ( min[ i ] - p[ i ] ) * odd;
			float t2 = ( max[ i ] - p[ i ] ) * odd;
			if ( t1 > t2 )
			{
				float tmp = t1; t1 = t2; t2 = tmp;
			}
									
			if ( t1 > t ) t = t1;
			if ( t2 < t_max ) t_max = t2;

			// スラブ交差チェック
			if ( t >= t_max )
			{
				Debug::Log("見つかった オブジェクトが間にいない");
				return false;
			}
		}
			h = i;
		}
	}
	return true;
}

/*-----------------------------------------------------------------------------
Function:   void Enemy::RoadFile(void)
Overview:   ファイルの読み取り
-----------------------------------------------------------------------------*/
void Enemy::RoadFile(void)
{
	string buff;
	int numlinear = 0;

	FileManager manager;
	ifstream ifs = manager.ReadFile(m_FileName);

	while(!ifs.eof())
	{
		ifs >> buff;

		if (strcmp(buff.c_str(), "NUMLINEAR") == 0)
		{
			ifs >> buff;
			m_NumLinear = stoi(buff.c_str());
			m_Linear = new LINEAR[m_NumLinear];
		}

		else if (strcmp(buff.c_str(), "CONTROLPOINT") == 0)
		{
			ifs >> buff;
			m_Linear[numlinear].ControlPoint.x = stof(buff.c_str());

			ifs >> buff;
			m_Linear[numlinear].ControlPoint.y = stof(buff.c_str());

			ifs >> buff;
			m_Linear[numlinear].ControlPoint.z = stof(buff.c_str());

			ControlPoint::Create(m_Linear[numlinear].ControlPoint);
		}

		else if (strcmp(buff.c_str(), "CONTROLVECTOR_NEXT") == 0)
		{
			ifs >> buff;
			m_Linear[numlinear].InitControlVectorNext.x = stof(buff.c_str());

			ifs >> buff;
			m_Linear[numlinear].InitControlVectorNext.y = stof(buff.c_str());

			ifs >> buff;
			m_Linear[numlinear].InitControlVectorNext.z = stof(buff.c_str());
		}

		else if (strcmp(buff.c_str(), "ROT") == 0)
		{
			ifs >> buff;
			m_Linear[numlinear].Rot = stof(buff.c_str());
		}

		else if (strcmp(buff.c_str(), "FRAME") == 0)
		{
			ifs >> buff;
			m_Linear[numlinear].FrameTime = stoi(buff.c_str());
		}

		else if (strcmp(buff.c_str(), "WAITTIME") == 0)
		{
			ifs >> buff;
			m_Linear[numlinear].WaitTime = stoi(buff.c_str());
			numlinear++;
		}
	}

	ifs.close();

	int LinearNext = 0;

	for (int i = 0; i < m_NumLinear; i++)
	{
		LinearNext = (i + 1) % m_NumLinear;

		m_Linear[i].ControlVector = m_Linear[i].InitControlVector - m_Linear[i].ControlPoint;
	}

	Object::SetPosition(m_Linear[0].ControlPoint);
	Motion::SetRotation(D3DXVECTOR3(0.0f, m_Linear[0].Rot, 0.0f));
}

void Enemy::SetHeadMarkActive(const bool flag)
{
	m_HeadMark->SetActive(flag);
}

void Enemy::SetHeadMarkTextureChange(char* texturePath)
{
	m_HeadMark->SetTexturePath(texturePath);
}