/*=============================================================================

�Փ˔���[ Collision.cpp ]

-------------------------------------------------------------------------------

��  Create
	2017/10/18
=============================================================================*/

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "RendererDirectX.h"
#include "Collision.h"

/*-----------------------------------------------------------------------------
Rectangle
-----------------------------------------------------------------------------*/
bool Collision_Rectangle::Judge(const D3DXVECTOR3 OtherPos, const D3DXVECTOR3 OtherSize)
{

	float x[] = { m_Pos.x , m_Pos.x + m_Size.x , OtherPos.x , OtherPos.x + OtherSize.x };
	float y[] = { m_Pos.y , m_Pos.y + m_Size.y , OtherPos.y , OtherPos.y + OtherSize.y };

	if (x[0] < x[3] && x[2] < x[1] && y[0] < y[3] && y[2] < y[1]){ return true; }

	return false;
}

/*-----------------------------------------------------------------------------
Circle
-----------------------------------------------------------------------------*/
bool Collision_Circle::Judge(const D3DXVECTOR3 OtherPos, const float OtherRadius)
{
	float Pos[] = { (OtherPos.x - m_Pos.x) * (OtherPos.x - m_Pos.x) ,
		            (OtherPos.y - m_Pos.y) * (OtherPos.y - m_Pos.y) };

	float Radius = (m_Radius + OtherRadius) * (m_Radius + OtherRadius);

	if (Pos[0] + Pos[1] <= Radius){ return true; }

	return false;
}

/*-----------------------------------------------------------------------------
Sphere
-----------------------------------------------------------------------------*/
bool Collision_Sphere::Judge(const D3DXVECTOR3 OtherPos, const float OtherRadius)
{
	float Pos[] = { (OtherPos.x - m_Pos.x) * (OtherPos.x - m_Pos.x) ,
		(OtherPos.y - m_Pos.y) * (OtherPos.y - m_Pos.y) ,
		(OtherPos.z - m_Pos.z) * (OtherPos.z - m_Pos.z) };

	float Radius = (m_Radius + OtherRadius) * (m_Radius + OtherRadius);

	if (Pos[0] + Pos[1] + Pos[2] <= Radius){ return true; }

	return false;
}