/*=============================================================================

�����n[ Physics.cpp ]

-------------------------------------------------------------------------------

��  Create
2017/11/28
=============================================================================*/

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "RendererDirectX.h"
#include "Physics.h"

/*-----------------------------------------------------------------------------
Macro
-----------------------------------------------------------------------------*/
#define GRRAVITY (9.8f)

/*-----------------------------------------------------------------------------
�Ε�����
-----------------------------------------------------------------------------*/
void Physics::ObliqueProjectile(D3DXVECTOR3* Out, D3DXVECTOR3* Velocity)
{
	D3DXVECTOR3 f = D3DXVECTOR3(0.0f, 0.0f, 0.0f );

	// �d��
	f.y -= GRRAVITY * m_Mass;

	// ��R��
	f.x -= Velocity->x * 0.01f;
	f.y -= Velocity->y * 0.01f;
	f.z -= Velocity->z * 0.01f;

	// ����
	Velocity->x += f.x / m_Mass;
	Velocity->y += f.y / m_Mass;
	Velocity->z += f.z / m_Mass;

	// �ړ�
	Out->x += Velocity->x * 0.03f;
	Out->y += Velocity->y * 0.03f;
	Out->z += Velocity->z * 0.03f;
}