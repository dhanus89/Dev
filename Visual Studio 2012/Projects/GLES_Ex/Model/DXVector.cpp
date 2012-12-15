#include "DXVector.h"
#include "DXMath.h"
#include <cassert>
//------------------------------------------------------------------
//							DXVector2 Definition
//------------------------------------------------------------------

DXVector2 DXVector2::xAxis(1.0f, 0.0f);
DXVector2 DXVector2::yAxis(0.0f, 1.0f);

DXVector2::DXVector2(float _x, float _y)
{
	m_x = _x; m_y = _y;
}

float DXVector2::Dot(const DXVector2 &_vec)const
{
	return (m_x * _vec.m_x) + (m_y * _vec.m_y);
	
}

void DXVector2::Set(const DXVector2& _vec)
{
	m_x = _vec.m_x;
	m_y = _vec.m_y;
}

void DXVector2::Set(float& _x, float& _y)
{
	m_x = _x; m_y = _y;
}

DXVector2& DXVector2::Normalize()
{
	// validate this is not a normalized vector

	float length = LengthSqr();
	if(DXMath::IsZero(1.0f - length))
		return *this;
	length = 1.0f / sqrtf(length);
	m_x *= length;
	m_y *= length;
	return *this;
}

float DXVector2::Length()const
{
	return sqrtf(LengthSqr());
}

float DXVector2::LengthSqr()const
{
	return (m_x*m_x) + (m_y*m_y);
}

bool DXVector2::operator!=(const DXVector2& _vec)const
{
	if(DXMath::IsEqual(m_x, _vec.m_x) && DXMath::IsEqual(m_x, _vec.m_y))
		return false;
	return true;
}

DXVector2 DXVector2::operator-(const DXVector2& _vec)const{
	return DXVector2(m_x - _vec.m_x, m_y - _vec.m_y);
}

DXVector2& DXVector2::operator-=(const DXVector2& _vec)
{
	m_x -= _vec.m_x;
	m_y -= _vec.m_y;
	return *this;
}

DXVector2 DXVector2::operator+(const DXVector2& _vec)const
{
	return DXVector2(m_x + _vec.m_x, m_y + _vec.m_y);
}

DXVector2& DXVector2::operator+=(const DXVector2& _vec)
{
	m_x += _vec.m_x;
	m_y += _vec.m_y;
	return *this;
}

DXVector2 operator*(float _scaler, const DXVector2& _vec)
{
	return DXVector2(_vec.m_x * _scaler,_vec.m_y * _scaler);
}

DXVector2& DXVector2::operator*=(float _scaler)
{
	m_x *= _scaler; m_y *= _scaler;
	return *this;
}

DXVector2 DXVector2::operator/(float _scaler)const
{
	float mul = 1/_scaler;
	return DXVector2(m_x * mul, m_y * mul);
}

DXVector2& DXVector2::operator/= (float _scaler)
{
	float mul = 1/_scaler;
	m_x *= mul; m_y *= mul;
	return *this;
}

bool DXVector2::operator==(const DXVector2& _vec)const
{
	if(DXMath::IsEqual(m_x, _vec.m_x) && DXMath::IsEqual(m_y, _vec.m_y))
		return true;
	return false;
}

std::ostream& operator<<(std::ostream& out, const DXVector2& vec)
{
	out << vec.m_x << ","<< vec.m_y <<std::endl;
	return out;
}

//------------------------------------------------------------------
// return a dot product with the perpendicular vector
//------------------------------------------------------------------
float DXVector2::PerpDot(const DXVector2& _vec)const
{
	// perpendcidular vector DOT _vec
	return (m_x * _vec.m_y) -(m_y * _vec.m_x);

}



//-----------------------------------------------------------------------------
//							DXVector3 Defintion 
//-----------------------------------------------------------------------------

DXVector3 DXVector3::xAxis(1.0f, 0.0f, 0.0f);
DXVector3 DXVector3::yAxis(0.0f, 1.0f, 0.0f);
DXVector3 DXVector3::zAxis(1.0f, 0.0f, 1.0f);
DXVector3 DXVector3::origin(0.0f, 0.0f, 0.0f);
DXVector3 DXVector3::Max(FLT_MAX, FLT_MAX, FLT_MAX);
DXVector3 DXVector3::Min(-FLT_MAX, -FLT_MAX, -FLT_MAX);

void DXVector3::ToZero()
{
	m_x = m_y = m_z = 0.0f;
}

DXVector3 DXVector3::operator+(const DXVector3 &_vec3)const
{
	return DXVector3(m_x + _vec3.m_x, m_y + _vec3.m_y, m_z + _vec3.m_z);
}

float DXVector3::operator()(unsigned int _i)const
{
	switch(_i)
	{
	case 0: return m_x;
	case 1: return m_y;
	case 2: return m_z;
	default: return m_x;
	}
}


bool DXVector3::operator<(const DXVector3& _vec)const
{
	for(unsigned int i = 0; i < 3; ++i)
	{
		if((*this)(i) > _vec(i))return false;
	}
	return true;
}

bool DXVector3::operator>(const DXVector3& _vec)const{
	if(_vec < (*this))return true;
	return false;
}

DXVector3 operator-(const DXVector3& _vecA, const DXVector3 &_vecB)
{
	return DXVector3(_vecA.m_x - _vecB.m_x, _vecA.m_y - _vecB.m_y, _vecA.m_z - _vecB.m_z);
}

DXVector3 operator-(const DXVector3& _vec3)
{
	return DXVector3(-_vec3.m_x, -_vec3.m_y, _vec3.m_z);
}

DXVector3& DXVector3::operator*= (const float& _real)
{
	m_x *= _real;
	m_y *= _real;
	m_z *= _real;
	return *this;
}

DXVector3 VectorMin(const DXVector3& _vec1, const DXVector3& _vec2)
{
	DXVector3 rslt;
	rslt.m_x = (_vec1.m_x < _vec2.m_x) ? _vec1.m_x : _vec2.m_x;
	rslt.m_y = (_vec1.m_y < _vec2.m_y) ? _vec1.m_y : _vec2.m_y;
	rslt.m_z = (_vec1.m_z < _vec2.m_z) ? _vec1.m_z : _vec2.m_z;
	return rslt;
}

DXVector3 VectorMax(const DXVector3& _vec1, const DXVector3& _vec2)
{
	DXVector3 rslt;
	rslt.m_x = (_vec1.m_x > _vec2.m_x) ? _vec1.m_x : _vec2.m_x;
	rslt.m_y = (_vec1.m_y > _vec2.m_y) ? _vec1.m_y : _vec2.m_y;
	rslt.m_z = (_vec1.m_z > _vec2.m_z) ? _vec1.m_z : _vec2.m_z;
	return rslt;
}

DXVector3& DXVector3::operator-=(const DXVector3 &_vec3)
{
	m_x -= _vec3.m_x;
	m_y -= _vec3.m_y;
	m_z -= _vec3.m_z;
	return *this;
}

DXVector3& DXVector3::operator=(const DXVector4& _vec4)
{
	m_x = _vec4.m_x;
	m_y = _vec4.m_y;
	m_z = _vec4.m_z;
	return *this;
}

DXVector3 DXVector3::operator*(float _scaler)const
{
	return DXVector3(m_x * _scaler, m_y * _scaler, m_z * _scaler);
}

DXVector3::DXVector3(const DXVector3& vec3)
{
	m_x = vec3.m_x;
	m_y = vec3.m_y;
	m_z = vec3.m_z;
}

float ScalerTripleProduct(const DXVector3& _vecCross1, const DXVector3& _vecCross2, const DXVector3& _vecDot)
{
	return _vecCross1.Cross(_vecCross2).Dot(_vecDot);
}

DXVector3& DXVector3::operator=(const DXVector3& _vec3)
{
	m_x = _vec3.m_x;
	m_y = _vec3.m_y;
	m_z = _vec3.m_z;
	return *this;
}

DXVector3 operator*(float _scale, const DXVector3& _vec3)
{
	return DXVector3(_vec3.m_x * _scale, _vec3.m_y * _scale, _vec3.m_z * _scale);
}

DXVector3& DXVector3::operator+=(const DXVector3 &_vec)
{
	m_x += _vec.m_x;
	m_y += _vec.m_y;
	m_z += _vec.m_z;
	return *this;
}

DXVector3::DXVector3(float _x, float _y, float _z)
{
	m_x = _x; m_y = _y; m_z = _z;
}

DXVector3 DXVector3::Cross(const DXVector3& _vec3)const
{
	DXVector3 result;
	result.m_x = (m_y * _vec3.m_z) - (m_z * _vec3.m_y);
	result.m_y = (m_z * _vec3.m_x)-(m_x * _vec3.m_z);
	result.m_z = (m_x * _vec3.m_y)-(m_y * _vec3.m_x);
	return result;
}

DXVector3 DXVector3::operator*(const DXVector3& _vec3)const
{
	return DXVector3(m_x*_vec3.m_x, m_y*_vec3.m_y, m_z*_vec3.m_z);
}

float DXVector3::Length()const
{
	return sqrtf(Dot(*this));
}


DXVector3& DXVector3::Normalize()
{
	float length = LengthSqr();
	assert(length > 0);
	if(DXMath::IsZero(1.0f-length)) return *this;
	length = 1.0f / sqrtf(length);
	m_x *= length;
	m_y *= length;
	m_z *= length;

	return *this;
}

float DXVector3::LengthSqr()const
{
	return Dot(*this);
}

float DXVector3::Dot(const DXVector3&_vec3)const
{
	return (m_x*_vec3.m_x) + (m_y*_vec3.m_y) + (m_z*_vec3.m_z);
}



std::ostream& operator<<(std::ostream& _out, const DXVector3& _vec3)
{
	return _out<<_vec3.m_x <<","<<_vec3.m_y<<","<<_vec3.m_z;
}

// global
DXVector3 DXVec3Replicate(float _val)
{
	return DXVector3(_val,_val,_val);
}


DXVector4 operator-(const DXVector4& _vec)
{
	return DXVector4(-_vec.m_x, -_vec.m_y, -_vec.m_z, _vec.m_w);
}

//***************************************************************************
//						DXVector4 Definition
//***************************************************************************

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
DXVector4::DXVector4(float _x, float _y, float _z, float _w)
{
	Set(_x, _y,_z,_w);
}

DXVector4::DXVector4(const DXVector3& _vec3, const float& _w)
{
	Set(_vec3, _w);
}

void DXVector4::Set(float _x, float _y, float _z, float _w)
{
	m_x = _x, m_y = _y, m_z = _z, m_w = _w;
}

void DXVector4::Set(const DXVector3& _vec3, const float& _w)
{
	m_x = _vec3.m_x;
	m_y = _vec3.m_y;
	m_z = _vec3.m_z;
	m_w = _w;
}

float DXVector4::Dot(const DXVector4& _vec4)const
{
	return ((m_x * _vec4.m_x)+(m_y * _vec4.m_y)+(m_z * _vec4.m_z)+(m_w * _vec4.m_w));
}

float DXVector4::LengthSqr()const
{
	return Dot(*this);
}

float DXVector4::Length()const
{
	return sqrtf(Dot(*this));
}

DXVector4& DXVector4::Normalize()
{
	// check if it is aready normalized
	float lengthSqr = LengthSqr();
	if(DXMath::IsZero(1.0f - lengthSqr))
		return *this;
	// receiprocial 
	lengthSqr = 1.0f / sqrtf(lengthSqr);

	m_x *= lengthSqr;
	m_y *= lengthSqr;
	m_z *= lengthSqr;
	m_w *= lengthSqr;

	return *this;
}

DXVector4& DXVector4::operator=(const DXVector4& _vec4)
{
	m_x = _vec4.m_x;
	m_y = _vec4.m_y;
	m_z = _vec4.m_z;
	m_w = _vec4.m_w;
	return *this;
}

DXVector4 operator-(const DXVector4& _vecA, const DXVector4 &_vecB)
{
	return DXVector4(_vecA.m_x - _vecB.m_x,_vecA.m_y - _vecB.m_y,
		_vecA.m_z - _vecB.m_z,_vecA.m_w - _vecB.m_w);  
}

DXVector4& DXVector4::operator-=(const DXVector4 &_vec4)
{
	m_x -= _vec4.m_x;
	m_y -= _vec4.m_y;
	m_z -= _vec4.m_z;
	m_w -= _vec4.m_w;
	return *this;
}

DXVector4 DXVector4::operator+(const DXVector4 &_vec4)const
{
	return DXVector4(m_x + _vec4.m_x, m_y + _vec4.m_y,
		m_z + _vec4.m_z,m_w + _vec4.m_w);  
}

DXVector4& DXVector4::operator+=(const DXVector4 &_vec4)
{
	m_x += _vec4.m_x;
	m_y += _vec4.m_y;
	m_z += _vec4.m_z;
	m_w += _vec4.m_w;
	return *this;
}

void DXVector4::ToZero()
{
	Set(0.0f, 0.0f, 0.0f,0.0f);
}

DXVector4 DXVector4::operator*(float _scaler)const
{
	return DXVector4(m_x * _scaler,m_y * _scaler,
		m_z * _scaler,m_w * _scaler);  
}

DXVector4 DXVector4::operator*=(float _scaler)
{
	m_x *= _scaler;
	m_y *= _scaler;
	m_z *= _scaler;
	m_w *= _scaler;
	return *this; 
}

DXVector4 operator*(float _scale, const DXVector4& _vec4)
{
	return _vec4 * _scale;
}

std::ostream& operator<<(std::ostream& _out, const DXVector4& _vec4)
{
	return _out<<_vec4.m_x <<","<<_vec4.m_y<<","<<_vec4.m_z <<""<<_vec4.m_w;
}

DXVector4 DXVec4Replicate(float _val)
{
	return DXVector4(_val,_val,_val,_val);
}