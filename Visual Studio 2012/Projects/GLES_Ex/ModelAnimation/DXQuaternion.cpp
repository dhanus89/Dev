#include "DXQuaternion.h"
#include "DXMath.h"
#include "DXVector.h"
#include "DXMatrix.h"


DXQuaternion DXQuaternion::Identity(DXQuaternion(1.0f,0.0f,0.0f,0.0f));
DXQuaternion DXQuaternion::Zero(DXQuaternion(0.0f,0.0f,0.0f,0.0f));	

DXQuaternion::DXQuaternion() : m_w(0.0f), m_x(0.0f), m_y(0.0f),m_z(0.0f)
{

}

DXQuaternion::DXQuaternion(float _w, float _x, float _y, float _z) :
	m_w(_w), m_x(_x), m_y(_y), m_z(_z)
{

}

DXQuaternion::DXQuaternion(float _angle, DXVector3& _axis)
{
	float lengthSqr = _axis.LengthSqr();

	if(DXMath::IsZero(lengthSqr))
	{
		ToIdentity();
		return;
	}
	_angle *= 0.5f;
	float cos,sin;
	DXMath::SinCos(_angle,sin,cos);
	float scaleFact = sin/sqrtf(lengthSqr);
	m_w = cos;
	m_x = scaleFact * _axis.m_x;
	m_y = scaleFact* _axis.m_y;
	m_z = scaleFact* _axis.m_z;
}

float DXQuaternion::LengthSqr(void)const
{
	return m_w*m_w + m_x * m_x + m_y*m_y + m_z*m_z;
}

bool DXQuaternion::IsUnit()const
{
	return LengthSqr() == 1.0f;
}

DXQuaternion& DXQuaternion::ToIdentity()
{
	m_w = 1.0f;
	m_x = m_y= m_z=0.0f;
	return *this;
}

//@ friend DXQuaternionLerp
void DXQuaternionLerp(DXQuaternion& _result, const DXQuaternion& _from,
							 const DXQuaternion& _end, float _t)
{
	_result = ((_end - _from) * _t) + _from;
	_result.Normalize();
}

DXQuaternion& DXQuaternion::Normalize()
{
	float recpMag = 1.0f /Magnitude();
	m_w *= recpMag ,m_x *= recpMag, m_y *= recpMag, m_z *= recpMag;	
	return *this;
}

float DXQuaternion::Magnitude()const
{
	return sqrtf(m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w);
}

//@ friend DXQuaternionSlerp
void DXQuaternionSlerp( DXQuaternion& _result, const DXQuaternion& _start, 
							   DXQuaternion _end, float _t)
{


	// get cos of "angle" between quaternions
	float cosTheta = _start.Dot( _end );

	// initialize result
	_result = _t*_end;

	// if "angle" between quaternions is less than 90 degrees
	if ( cosTheta >= DXMath::EPSILION )
	{
		// use standard interpolation
		_result += (1.0f-_t)*_start;
	}
	else
	{
		// otherwise, take the shorter path
		_result += (_t-1.0f)*_start;
	}

	return;
	
	//find the shortest arc to interpolate

}

///@ friend
DXQuaternion operator*(const float& _scaler, const DXQuaternion& _quat )
{
	return DXQuaternion(_quat.m_w*_scaler,_quat.m_y*_scaler, _quat.m_y*_scaler, _quat.m_z*_scaler);
}

DXQuaternion& DXQuaternion::operator=(const DXQuaternion& _quat)
{
	m_w = _quat.m_w, m_x = _quat.m_x, m_y = _quat.m_y, m_z = _quat.m_z;
	return *this;
}

float DXQuaternion::Dot(const DXQuaternion& _quat)const
{
	return (m_w *_quat.m_w)+(m_x * _quat.m_x)+(m_y * _quat.m_y)+(m_z * _quat.m_z);
}

DXQuaternion DXQuaternion::operator-(const DXQuaternion& _quat)const
{
	return DXQuaternion(m_w - _quat.m_w, m_x - _quat.m_x, m_y - _quat.m_y, m_z - _quat.m_z);
}

DXQuaternion DXQuaternion::operator+(const DXQuaternion& _quat)const
{
	return DXQuaternion(m_w + _quat.m_w, m_x + _quat.m_x, m_y + _quat.m_y, m_z - _quat.m_z);
}

DXQuaternion& DXQuaternion::operator+=(const DXQuaternion& _quat)
{
	m_w += _quat.m_w;
	m_x += _quat.m_x;
	m_y += _quat.m_y;
	m_z	+= _quat.m_z;
	return *this;
}

DXQuaternion& DXQuaternion::operator*=(float _scaler)
{
	m_w *= _scaler, m_x*=_scaler, m_y*=_scaler, m_z*=_scaler;
	return *this;
}
DXQuaternion DXQuaternion::operator*(float _scaler)const
{
	return DXQuaternion(m_w *_scaler, m_x*_scaler, m_y * _scaler, m_z*_scaler);
}