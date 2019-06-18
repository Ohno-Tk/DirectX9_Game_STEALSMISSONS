/*=============================================================================

	数学系関数[ Mathematics.h ]

-------------------------------------------------------------------------------
■  Author
	Ohno Takuya

■  Creat
	2017/10/16
=============================================================================*/

#ifndef _MATHEMATICS_H_
#define _MATHEMATICS_H_

/*-----------------------------------------------------------------------------
Macro
-----------------------------------------------------------------------------*/
#define PI ((float)3.141592654f)	//	円周率
#define DegreeToRadian( degree ) ((degree) * (PI / 180.0f))//	角度を求める
#define RadianToDegree( radian ) ((radian) * (180.0f / PI))//	度を求める

/*-----------------------------------------------------------------------------
Struct
-----------------------------------------------------------------------------*/
struct VECTOR2
{
public:
	VECTOR2(float x = 0.0f, float y = 0.0f) :x(x), y(y) {}

	//同じ型との計算
	const VECTOR2 operator + (const VECTOR2 &f) const { return VECTOR2(x + f.x, y + f.y); }//加算
	const VECTOR2 operator - (const VECTOR2 &f) const { return VECTOR2(x - f.x, y - f.y); }//減算
	const VECTOR2 operator * (const VECTOR2 &f) const { return VECTOR2(x * f.x, y * f.y); }//乗算
	const VECTOR2 operator / (const VECTOR2 &f) const { return VECTOR2(x / f.x, y / f.y); }//除算

	const VECTOR2 operator - () const{ return VECTOR2(x * -1.0f, y * -1.0f); }//手前に-を付けたとき

	VECTOR2 &operator = (const VECTOR2 &f) { x = f.x; y = f.y; return *this; }//代入
	VECTOR2 &operator += (const VECTOR2 &f) { x += f.x; y += f.y; return *this; }//＋イコール
	VECTOR2 &operator -= (const VECTOR2 &f) { x -= f.x; y -= f.y; return *this; }//－イコール
	VECTOR2 &operator *= (const VECTOR2 &f) { x *= f.x; y *= f.y; return *this; }//×イコール
	VECTOR2 &operator /= (const VECTOR2 &f) { x /= f.x; y /= f.y; return *this; }//÷イコール

public:
	float x, y;
};

struct VECTOR3
{
public:
	VECTOR3(float x = 0.0f, float y = 0.0f, float z = 0.0f) :x(x), y(y), z(z) {}

	//同じ型との計算
	const VECTOR3 operator + (const VECTOR3 &f) const { return VECTOR3(x + f.x, y + f.y, z + f.z); }//加算
	const VECTOR3 operator - (const VECTOR3 &f) const { return VECTOR3(x - f.x, y - f.y, z - f.z); }//減算
	const VECTOR3 operator * (const VECTOR3 &f) const { return VECTOR3(x * f.x, y * f.y, z * f.z); }//乗算
	const VECTOR3 operator / (const VECTOR3 &f) const { return VECTOR3(x / f.x, y / f.y, z / f.z); }//除算

	const VECTOR3 operator - () const { return VECTOR3(x * -1.0f, y * -1.0f, z * -1.0f); }	//手前に-を付けたとき

	VECTOR3 &operator = (const VECTOR3 &f) { x = f.x; y = f.y; z = f.z; return *this; }	//代入
	VECTOR3 &operator += (const VECTOR3 &f) { x += f.x; y += f.y; z += f.z; return *this; }	//＋イコール
	VECTOR3 &operator -= (const VECTOR3 &f) { x -= f.x; y -= f.y; z -= f.z; return *this; }	//－イコール
	VECTOR3 &operator *= (const VECTOR3 &f) { x *= f.x; y *= f.y; z *= f.z; return *this; }	//×イコール
	VECTOR3 &operator /= (const VECTOR3 &f) { x /= f.x; y /= f.y; z /= f.z; return *this; }	//÷イコール

																							//内積
	float dot(const VECTOR3 &r) const {
		return x * r.x + y * r.y + z * r.z;
	}
	//外積
	VECTOR3 cross(const VECTOR3 &r) const {
		return VECTOR3(y * r.z - z * r.y, z * r.x - x * r.z, x * r.y - y * r.x);
	}
	//長さ
	float length() const {
		return sqrtf(lengthSq());
	}
	//平方根
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

	//同じ型との計算
	const VECTOR4 operator + (const VECTOR4 &f) const { return VECTOR4(x + f.x, y + f.y, z + f.z, w + f.w); }//加算
	const VECTOR4 operator - (const VECTOR4 &f) const { return VECTOR4(x - f.x, y - f.y, z - f.z, w - f.w); }//減算
	const VECTOR4 operator * (const VECTOR4 &f) const { return VECTOR4(x * f.x, y * f.y, z * f.z, w * f.w); }//乗算
	const VECTOR4 operator / (const VECTOR4 &f) const { return VECTOR4(x / f.x, y / f.y, z / f.z, w / f.w); }//除算

	const VECTOR4 operator - () const { return VECTOR4(x * -1.0f, y * -1.0f, z * -1.0f, w * -1.0f); }	//手前に-を付けたとき

	VECTOR4 &operator = (const VECTOR4 &f) { x = f.x; y = f.y; z = f.z; w = f.w; return *this; }	//代入
	VECTOR4 &operator += (const VECTOR4 &f) { x += f.x; y += f.y; z += f.z; w += f.w; return *this; }	//＋イコール
	VECTOR4 &operator -= (const VECTOR4 &f) { x -= f.x; y -= f.y; z -= f.z; w -= f.w; return *this; }	//－イコール
	VECTOR4 &operator *= (const VECTOR4 &f) { x *= f.x; y *= f.y; z *= f.z; w *= f.w; return *this; }	//×イコール
	VECTOR4 &operator /= (const VECTOR4 &f) { x /= f.x; y /= f.y; z /= f.z; w /= f.w; return *this; }	//÷イコール

public:
	float x, y, z, w;
};


/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class Angle2Vector
{// 2つのベクトルのなす角度を求める
public:
	Angle2Vector(D3DXVECTOR3 VectorA) :m_VectorA(VectorA) {}

	float Angle(D3DXVECTOR3 VectorB);
private:
	D3DXVECTOR3 m_VectorA;
};

class CubicExpressionInterpolation
{// 3次式補間
public:
	CubicExpressionInterpolation(int FrameCount) :m_Count(FrameCount) {}

	void Interpolation(D3DXVECTOR3* Out, D3DXVECTOR3 Start, D3DXVECTOR3 End, int Time);
	void Interpolation(float* Out, float Start, float End, int Time);

private:
	int m_Count;
};

class LinearInterpolation
{// 線形補間
public:
	LinearInterpolation(int FrameCount) :m_Count(FrameCount) {}

	// 補間
	void Interpolation(D3DXVECTOR3* Out, D3DXVECTOR3 Start, D3DXVECTOR3 End, int Time);
	void Interpolation(float* Out, float Start, float End, int Time);

private:
	int m_Count;
};

class HermiteInterpolation
{// エルミート補間
public:
	HermiteInterpolation(int FrameCount):m_Count(FrameCount){}

	// 補間
	void Interpolation(D3DXVECTOR3* Out, D3DXVECTOR3 Pos1, D3DXVECTOR3 Vector1, D3DXVECTOR3 Pos2, D3DXVECTOR3 Vector2, int Time);

private:
	int m_Count;
};

class AstroidCurve
{// アステロイド曲線
public:
	AstroidCurve(D3DXVECTOR3 op, float rotvalue, float radius);

	//	曲線計算
	D3DXVECTOR3 Curve(void);

private:
	D3DXVECTOR3 m_OriginPoint;	//	原点

	float m_Rot;				//	角度
	float m_RotValue;			//	角度変化量
	float m_Radius;				//	半径
};

class InvoluteCurve
{// インボリュート曲線
public:
	InvoluteCurve(D3DXVECTOR3 op, float rotvalue, float radius);

	//	曲線計算
	D3DXVECTOR3 Curve(void);

private:
	D3DXVECTOR3 m_OriginPoint;	//	原点

	float m_Rot;				//	角度
	float m_RotValue;			//	角度変化量
	float m_Radius;				//	半径
};

#endif