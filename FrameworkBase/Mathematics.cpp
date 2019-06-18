/*=============================================================================

		���w�n�֐�[ Mathematics.cpp ]

-------------------------------------------------------------------------------
	��  Author
		Ohno Takuya

	��  Created Date
		2017/07/20
=============================================================================*/

/*-----------------------------------------------------------------------------
	Header
-----------------------------------------------------------------------------*/
#include "RendererDirectX.h"
#include "Mathematics.h"

/*-----------------------------------------------------------------------------
2�̃x�N�g���̂Ȃ��p�x�����߂�
-----------------------------------------------------------------------------*/
float Angle2Vector::Angle(D3DXVECTOR3 VectorB)
{
	//	���������߂�
	float len1 = D3DXVec3Length(&m_VectorA);
	float len2 = D3DXVec3Length(&VectorB);

	//	�p�x�����߂�
	float angle = (float)(acos(D3DXVec3Dot(&VectorB, &m_VectorA) / (len1*len2)));

	return angle;
}

/*-----------------------------------------------------------------------------
�O�������
-----------------------------------------------------------------------------*/
void CubicExpressionInterpolation::Interpolation(D3DXVECTOR3* Out, D3DXVECTOR3 Start, D3DXVECTOR3 End, int Time)
{
	float t = (float)m_Count / Time;
	float rate = t * t * ( 3.0f - 2.0f * t );

	*Out = Start * (1.0f - rate) + End * rate;
}
void CubicExpressionInterpolation::Interpolation(float* Out, float Start, float End, int Time)
{
	float t = (float)m_Count / Time;
	float rate = t * t * ( 3.0f - 2.0f * t );

	*Out = Start * (1.0f - rate) + End * rate;
}


/*-----------------------------------------------------------------------------
���`���
-----------------------------------------------------------------------------*/
void LinearInterpolation::Interpolation(D3DXVECTOR3* Out, D3DXVECTOR3 Start, D3DXVECTOR3 End, int Time)
{
	float rate = (float)m_Count / Time;

	*Out = Start * (1.0f - rate) + End * rate;
}

void LinearInterpolation::Interpolation(float* Out, float Start, float End, int Time)
{
	float rate = (float)m_Count / Time;

	*Out = Start * (1.0f - rate) + End * rate;
}

/*-----------------------------------------------------------------------------
�G���~�[�g���
-----------------------------------------------------------------------------*/
void HermiteInterpolation::Interpolation(D3DXVECTOR3* Out, D3DXVECTOR3 Pos1, D3DXVECTOR3 Vector1, D3DXVECTOR3 Pos2, D3DXVECTOR3 Vector2, int Time)
{
	float h00, h01, h10, h11;
	float rate = (float)m_Count / Time;

	h00 = (2 * rate * rate * rate) - (3 * rate * rate) + 1;
	h01 = (-2 * rate * rate * rate) + (3 * rate * rate);
	h10 = (rate * rate * rate) - (2 * rate * rate) + rate;
	h11 = (rate * rate * rate) - (rate * rate);

	*Out = h00 * Pos1 + h01 * Pos2 + h10 * Vector1 + h11 * Vector2;
}

/*-----------------------------------------------------------------------------
�A�X�e���C�h�Ȑ�
-----------------------------------------------------------------------------*/
AstroidCurve::AstroidCurve(D3DXVECTOR3 op, float rotvalue, float radius)
{
	m_OriginPoint = op;	

	m_Rot = 0.0f;
	m_RotValue = rotvalue;
	m_Radius = radius;
}

D3DXVECTOR3 AstroidCurve::Curve(void)
{

	D3DXVECTOR3 pos;
	
	float Cos3 = cosf(DegreeToRadian(m_Rot))*cosf(DegreeToRadian(m_Rot))*cosf(DegreeToRadian(m_Rot));
	float Sin3 = sinf(DegreeToRadian(m_Rot))*sinf(DegreeToRadian(m_Rot))*sinf(DegreeToRadian(m_Rot));

	pos.x = Cos3 * m_Radius + m_OriginPoint.x;
	pos.y = Sin3 * m_Radius + m_OriginPoint.y;
	pos.z = m_OriginPoint.z;

	m_Rot += m_RotValue;

	return pos;
}

/*-----------------------------------------------------------------------------
�C���{�����[�g�Ȑ�
-----------------------------------------------------------------------------*/
InvoluteCurve::InvoluteCurve(D3DXVECTOR3 op, float rotvalue, float radius)
{
	m_OriginPoint = op;		//	���_

	m_Rot = 0.0f;			//	�p�x
	m_RotValue = rotvalue;	//	�p�x�ω���
	m_Radius = radius;		//	���a
}

D3DXVECTOR3 InvoluteCurve::Curve(void)
{

	D3DXVECTOR3 pos;

	pos.x = (m_Radius * (sinf(DegreeToRadian(m_Rot)) - m_Rot * cosf(DegreeToRadian(m_Rot))) * -1) + m_OriginPoint.x;
	pos.y = (m_Radius * (cosf(DegreeToRadian(m_Rot)) + m_Rot * sinf(DegreeToRadian(m_Rot))) * -1) + m_OriginPoint.y;
	pos.z = m_OriginPoint.z;

	m_Rot += m_RotValue;

	return pos;
}
