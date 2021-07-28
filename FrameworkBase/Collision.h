/*=============================================================================

�Փ˔���[ Collision.h ]

-------------------------------------------------------------------------------

��  Create
	2017/10/18
=============================================================================*/

#ifndef _COLLISION_H_
#define _COLLISION_H_

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
2D
-----------------------------------------------------------------------------*/
class Collision_Rectangle
{	//	��`
public:
	Collision_Rectangle(const D3DXVECTOR3 Pos, const D3DXVECTOR3 Size) :m_Pos(Pos), m_Size(Size) {}

	//	�Փ˔���
	bool Judge(const D3DXVECTOR3 OtherPos, const D3DXVECTOR3 OtherSize);

private:
	D3DXVECTOR3 m_Pos; // ���W
	D3DXVECTOR3 m_Size; // �傫��
};

class Collision_Circle
{	//	�~
public:
	Collision_Circle(const D3DXVECTOR3 Pos, const float Radius) :m_Pos(Pos), m_Radius(Radius) {}

	//	�Փ˔���
	bool Judge(const D3DXVECTOR3 OtherPos, const float OtherRadius);

private:
	D3DXVECTOR3 m_Pos; // ���W
	float m_Radius;	 // ���a
};

/*-----------------------------------------------------------------------------
3D
-----------------------------------------------------------------------------*/
class Collision_Sphere
{	//	��
public:
	Collision_Sphere(const D3DXVECTOR3 Pos, const float Radius) :m_Pos(Pos), m_Radius(Radius) {}

	//	�Փ˔���
	bool Judge(const D3DXVECTOR3 OtherPos, const float OtherRadius);

private:
	D3DXVECTOR3 m_Pos; // ���W
	float m_Radius;	 // ���a
};

#endif
