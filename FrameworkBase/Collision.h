/*=============================================================================

è’ìÀîªíË[ Collision.h ]

-------------------------------------------------------------------------------
Å°  Author
	Ohno Takuya

Å°  Create
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
{	//	ãÈå`
public:
	Collision_Rectangle(const D3DXVECTOR3 Pos, const D3DXVECTOR3 Size) :m_Pos(Pos), m_Size(Size) {}

	//	è’ìÀîªíË
	bool Judge(const D3DXVECTOR3 OtherPos, const D3DXVECTOR3 OtherSize);

private:
	D3DXVECTOR3 m_Pos; // ç¿ïW
	D3DXVECTOR3 m_Size; // ëÂÇ´Ç≥
};

class Collision_Circle
{	//	â~
public:
	Collision_Circle(const D3DXVECTOR3 Pos, const float Radius) :m_Pos(Pos), m_Radius(Radius) {}

	//	è’ìÀîªíË
	bool Judge(const D3DXVECTOR3 OtherPos, const float OtherRadius);

private:
	D3DXVECTOR3 m_Pos; // ç¿ïW
	float m_Radius;	 // îºåa
};

/*-----------------------------------------------------------------------------
3D
-----------------------------------------------------------------------------*/
class Collision_Sphere
{	//	ãÖ
public:
	Collision_Sphere(const D3DXVECTOR3 Pos, const float Radius) :m_Pos(Pos), m_Radius(Radius) {}

	//	è’ìÀîªíË
	bool Judge(const D3DXVECTOR3 OtherPos, const float OtherRadius);

private:
	D3DXVECTOR3 m_Pos; // ç¿ïW
	float m_Radius;	 // îºåa
};

#endif
