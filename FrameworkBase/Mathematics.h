/*=============================================================================

	���w�n�֐�[ Mathematics.h ]

-------------------------------------------------------------------------------

��  Creat
	2017/10/16
=============================================================================*/

#ifndef _MATHEMATICS_H_
#define _MATHEMATICS_H_

/*-----------------------------------------------------------------------------
Macro
-----------------------------------------------------------------------------*/
#define PI ((float)3.141592654f)	//	�~����
#define DegreeToRadian( degree ) ((degree) * (PI / 180.0f))//	�p�x�����߂�
#define RadianToDegree( radian ) ((radian) * (180.0f / PI))//	�x�����߂�

/*-----------------------------------------------------------------------------
Struct
-----------------------------------------------------------------------------*/
struct VECTOR2
{
public:
	VECTOR2(float x = 0.0f, float y = 0.0f) :x(x), y(y) {}

	//�����^�Ƃ̌v�Z
	const VECTOR2 operator + (const VECTOR2 &f) const { return VECTOR2(x + f.x, y + f.y); }//���Z
	const VECTOR2 operator - (const VECTOR2 &f) const { return VECTOR2(x - f.x, y - f.y); }//���Z
	const VECTOR2 operator * (const VECTOR2 &f) const { return VECTOR2(x * f.x, y * f.y); }//��Z
	const VECTOR2 operator / (const VECTOR2 &f) const { return VECTOR2(x / f.x, y / f.y); }//���Z

	const VECTOR2 operator - () const{ return VECTOR2(x * -1.0f, y * -1.0f); }//��O��-��t�����Ƃ�

	VECTOR2 &operator = (const VECTOR2 &f) { x = f.x; y = f.y; return *this; }//���
	VECTOR2 &operator += (const VECTOR2 &f) { x += f.x; y += f.y; return *this; }//�{�C�R�[��
	VECTOR2 &operator -= (const VECTOR2 &f) { x -= f.x; y -= f.y; return *this; }//�|�C�R�[��
	VECTOR2 &operator *= (const VECTOR2 &f) { x *= f.x; y *= f.y; return *this; }//�~�C�R�[��
	VECTOR2 &operator /= (const VECTOR2 &f) { x /= f.x; y /= f.y; return *this; }//���C�R�[��

public:
	float x, y;
};

struct VECTOR3
{
public:
	VECTOR3(float x = 0.0f, float y = 0.0f, float z = 0.0f) :x(x), y(y), z(z) {}

	//�����^�Ƃ̌v�Z
	const VECTOR3 operator + (const VECTOR3 &f) const { return VECTOR3(x + f.x, y + f.y, z + f.z); }//���Z
	const VECTOR3 operator - (const VECTOR3 &f) const { return VECTOR3(x - f.x, y - f.y, z - f.z); }//���Z
	const VECTOR3 operator * (const VECTOR3 &f) const { return VECTOR3(x * f.x, y * f.y, z * f.z); }//��Z
	const VECTOR3 operator / (const VECTOR3 &f) const { return VECTOR3(x / f.x, y / f.y, z / f.z); }//���Z

	const VECTOR3 operator - () const { return VECTOR3(x * -1.0f, y * -1.0f, z * -1.0f); }	//��O��-��t�����Ƃ�

	VECTOR3 &operator = (const VECTOR3 &f) { x = f.x; y = f.y; z = f.z; return *this; }	//���
	VECTOR3 &operator += (const VECTOR3 &f) { x += f.x; y += f.y; z += f.z; return *this; }	//�{�C�R�[��
	VECTOR3 &operator -= (const VECTOR3 &f) { x -= f.x; y -= f.y; z -= f.z; return *this; }	//�|�C�R�[��
	VECTOR3 &operator *= (const VECTOR3 &f) { x *= f.x; y *= f.y; z *= f.z; return *this; }	//�~�C�R�[��
	VECTOR3 &operator /= (const VECTOR3 &f) { x /= f.x; y /= f.y; z /= f.z; return *this; }	//���C�R�[��

																							//����
	float dot(const VECTOR3 &r) const {
		return x * r.x + y * r.y + z * r.z;
	}
	//�O��
	VECTOR3 cross(const VECTOR3 &r) const {
		return VECTOR3(y * r.z - z * r.y, z * r.x - x * r.z, x * r.y - y * r.x);
	}
	//����
	float length() const {
		return sqrtf(lengthSq());
	}
	//������
	float lengthSq() const {
		return x * x + y * y + z * z;
	}

public:
	float x, y, z;
};

struct VECTOR4
{
public:
	VECTOR4(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f) :x(x), y(y), z(z), w(w) {}

	//�����^�Ƃ̌v�Z
	const VECTOR4 operator + (const VECTOR4 &f) const { return VECTOR4(x + f.x, y + f.y, z + f.z, w + f.w); }//���Z
	const VECTOR4 operator - (const VECTOR4 &f) const { return VECTOR4(x - f.x, y - f.y, z - f.z, w - f.w); }//���Z
	const VECTOR4 operator * (const VECTOR4 &f) const { return VECTOR4(x * f.x, y * f.y, z * f.z, w * f.w); }//��Z
	const VECTOR4 operator / (const VECTOR4 &f) const { return VECTOR4(x / f.x, y / f.y, z / f.z, w / f.w); }//���Z

	const VECTOR4 operator - () const { return VECTOR4(x * -1.0f, y * -1.0f, z * -1.0f, w * -1.0f); }	//��O��-��t�����Ƃ�

	VECTOR4 &operator = (const VECTOR4 &f) { x = f.x; y = f.y; z = f.z; w = f.w; return *this; }	//���
	VECTOR4 &operator += (const VECTOR4 &f) { x += f.x; y += f.y; z += f.z; w += f.w; return *this; }	//�{�C�R�[��
	VECTOR4 &operator -= (const VECTOR4 &f) { x -= f.x; y -= f.y; z -= f.z; w -= f.w; return *this; }	//�|�C�R�[��
	VECTOR4 &operator *= (const VECTOR4 &f) { x *= f.x; y *= f.y; z *= f.z; w *= f.w; return *this; }	//�~�C�R�[��
	VECTOR4 &operator /= (const VECTOR4 &f) { x /= f.x; y /= f.y; z /= f.z; w /= f.w; return *this; }	//���C�R�[��

public:
	float x, y, z, w;
};


/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class Angle2Vector
{// 2�̃x�N�g���̂Ȃ��p�x�����߂�
public:
	Angle2Vector(D3DXVECTOR3 VectorA) :m_VectorA(VectorA) {}

	float Angle(D3DXVECTOR3 VectorB);
private:
	D3DXVECTOR3 m_VectorA;
};

class CubicExpressionInterpolation
{// 3�������
public:
	CubicExpressionInterpolation(int FrameCount) :m_Count(FrameCount) {}

	void Interpolation(D3DXVECTOR3* Out, D3DXVECTOR3 Start, D3DXVECTOR3 End, int Time);
	void Interpolation(float* Out, float Start, float End, int Time);

private:
	int m_Count;
};

class LinearInterpolation
{// ���`���
public:
	LinearInterpolation(int FrameCount) :m_Count(FrameCount) {}

	// ���
	void Interpolation(D3DXVECTOR3* Out, D3DXVECTOR3 Start, D3DXVECTOR3 End, int Time);
	void Interpolation(float* Out, float Start, float End, int Time);

private:
	int m_Count;
};

class HermiteInterpolation
{// �G���~�[�g���
public:
	HermiteInterpolation(int FrameCount):m_Count(FrameCount){}

	// ���
	void Interpolation(D3DXVECTOR3* Out, D3DXVECTOR3 Pos1, D3DXVECTOR3 Vector1, D3DXVECTOR3 Pos2, D3DXVECTOR3 Vector2, int Time);

private:
	int m_Count;
};

class AstroidCurve
{// �A�X�e���C�h�Ȑ�
public:
	AstroidCurve(D3DXVECTOR3 op, float rotvalue, float radius);

	//	�Ȑ��v�Z
	D3DXVECTOR3 Curve(void);

private:
	D3DXVECTOR3 m_OriginPoint;	//	���_

	float m_Rot;				//	�p�x
	float m_RotValue;			//	�p�x�ω���
	float m_Radius;				//	���a
};

class InvoluteCurve
{// �C���{�����[�g�Ȑ�
public:
	InvoluteCurve(D3DXVECTOR3 op, float rotvalue, float radius);

	//	�Ȑ��v�Z
	D3DXVECTOR3 Curve(void);

private:
	D3DXVECTOR3 m_OriginPoint;	//	���_

	float m_Rot;				//	�p�x
	float m_RotValue;			//	�p�x�ω���
	float m_Radius;				//	���a
};

#endif