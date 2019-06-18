/*=============================================================================

フェードオブジェクト(2D)[ Fade2DObject.cpp ]

-------------------------------------------------------------------------------
■  Author
Ohno Takuya

■  Create
2017/11/17
=============================================================================*/

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "FrameworkBase\Common.h"
#include "FrameworkBase\RendererDirectX.h"
#include "Object.h"
#include "Sprite2D.h"
#include "Fade2DObject.h"

/*-----------------------------------------------------------------------------
Namespace
-----------------------------------------------------------------------------*/
using namespace std;


Fade2DObject::Fade2DObject(int Priolity):Sprite2D(Priolity),
m_FadeState(FADE_IN),
m_UpperLimit(1.0f),
m_LowerLimit(0.0f),
m_FadeRate(1.0f / 60),
m_FadeFlag(true){}

/*-----------------------------------------------------------------------------
Function:   Fade2DObject* Fade2DObject::Create(D3DXVECTOR3 position, D3DXVECTOR2 size, string texturePath, float upperLimit, float lowerLimit)
Parameter:  D3DXVECTOR3 position
              座標
            D3DXVECTOR2 size
			  大きさ
            string texturePath
			  テクスチャのパス
			float upperLimit
			  上限
			float lowerLimit
			  下限
			float fadeRate
			  フェードする割合
Overview:   生成
-----------------------------------------------------------------------------*/
Fade2DObject* Fade2DObject::Create(D3DXVECTOR3 position, D3DXVECTOR2 size, char* texturePath, float upperLimit, float lowerLimit, D3DXVECTOR4 color, float fadeRate)
{
	auto object = new Fade2DObject;

	object->SetPosition(position);
	object->SetSize(size);
	object->SetTexturePath(texturePath);
	object->SetColor((D3DXCOLOR)color);
	object->m_UpperLimit = upperLimit;
	object->m_LowerLimit = lowerLimit;
	object->m_FadeRate = fadeRate;

	object->Initialize();

	return object;
}

void Fade2DObject::Initialize(void)
{
	Sprite2D::Initialize();
}

void Fade2DObject::Uninitialize(void)
{
	Sprite2D::Uninitialize();
}

void Fade2DObject::Update(void)
{
	if(!m_FadeFlag){ return; }

	Sprite2D::Update();

	Fade();
}

void Fade2DObject::Draw(void)
{
	Sprite2D::Draw();
}

void Fade2DObject::Fade(void)
{
	D3DXCOLOR color = Sprite2D::GetColor();

	if(m_FadeState == FADE_IN)
	{
		color.a -= m_FadeRate;

		if(color.a < m_LowerLimit)
		{
			color.a = m_LowerLimit;
			m_FadeState = FADE_OUT;
		}
	}
	else if(m_FadeState == FADE_OUT)
	{
		color.a += m_FadeRate;

		if(color.a > m_UpperLimit)
		{
			color.a = m_UpperLimit;
			m_FadeState = FADE_IN;
		}
	}

	Sprite2D::SetColor(color);
}

void Fade2DObject::SetTexturePath(char* filePath)
{
	Sprite2D::SetTexturePath(filePath);
}