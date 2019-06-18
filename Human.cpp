/*=============================================================================

lŒ^[ Human.cpp ]

-------------------------------------------------------------------------------
¡  Author
	Ohno Takuya

¡  Create
	2017/11/08
=============================================================================*/

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "FrameworkBase\Common.h"
#include "Human.h"
#include "HumanState.h"


Human::Human(int Priolity):Motion(Priolity)
{
	m_Active = true;
	m_State = new HumanStateNull;
}

void Human::Initialize(void)
{
	Motion::Initialize();
}

void Human::Uninitialize(void)
{
	Motion::Uninitialize();

	SAFE_UNINIT(m_State);
}

void Human::Update(void)
{
	Motion::Update();

	D3DXVECTOR3 position = Object::GetPosition();

	m_State->Update(position);
}

void Human::Draw(void)
{
	if(m_Active)
	{
		Motion::Draw();
	}
}

void Human::SetState(HumanState* state)
{
	SAFE_UNINIT(m_State);

	m_State = state;
}