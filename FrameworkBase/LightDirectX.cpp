/*=============================================================================

���C�g(DirectX)[ LightDirectX.cpp ]

-------------------------------------------------------------------------------

��  Create
	2017/10/16
=============================================================================*/

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "RendererDirectX.h"
#include "LightDirectX.h"

LightDirectX::LightDirectX()
{
	ZeroMemory(&m_Light, sizeof(D3DLIGHT9));
}

void LightDirectX::DirectionalLight(void)
{
	LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();

	m_Light.Type = D3DLIGHT_DIRECTIONAL;
	m_Light.Diffuse = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);//���s�����̐F
	m_Light.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�����̐F

	D3DXVECTOR3 vecDir(0.0f, 1.0f, 1.0f);//���s�����̌���
	D3DXVec3Normalize((D3DXVECTOR3 *)&m_Light.Direction, &vecDir);

//	Device->SetLight(0, &m_Light);

	Device->LightEnable(0, TRUE);//���C�g��ON�ɂ���

	Device->SetRenderState(D3DRS_LIGHTING, TRUE);//�S�̂̃��C�g��L���ɂ���
}

void LightDirectX::PointLight(void)
{
	LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();

	m_Light.Type = D3DLIGHT_POINT;

	m_Light.Position.x = 0.0f;
	m_Light.Position.y = 0.0f;
	m_Light.Position.z = 0.0f;
	m_Light.Falloff = 10.0f;
	m_Light.Direction = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//���s�����̐F
	m_Light.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�����̐F
	m_Light.Specular = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

	m_Light.Attenuation0 = 1.0f;
	m_Light.Range = 350.0f;

	Device->SetLight(0, &m_Light);

	Device->LightEnable(0, TRUE);
}