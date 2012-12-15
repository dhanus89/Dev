#ifndef DXQUATERNION_H
#define DXQUATERNION_H

//  [6/25/2012 Dhanus]

#include "DXVector.h"
#include "DXEulerAngles.h"
#include <iostream>

//Forward Declaration--------------------------------------
class DXVector3;
class DXMatrix33;

class DXQuaternion
{
public:
#pragma region 
	//Constructor
	DXQuaternion(float _w, float _x, float _y, float _z);
	DXQuaternion(float _angle, DXVector3& _axis);
	DXQuaternion();
	DXQuaternion(const DXMatrix33& _rotationMtx33);
	void Set(const DXMatrix33& _rotationMtx33);
	float Dot(const DXQuaternion& _quat)const;
	bool IsUnit()const;
	DXQuaternion GetInverse()const;
	DXQuaternion& ToConjugate();
	bool IsZero()const;
	void SetToRotateAboutX(float _theta);
	void SetToRotateAboutY(float _theta);
	void SetToRotateAboutZ(float _theta);
	void Normalize();
	float Magnitude()const;
	void Set(float _zAxisAngle,float _xAxisAngle, float _yAxisAngle);
	void Set(float _angleInDegree, DXVector3& _axis);
	DXQuaternion& ToIdentity();
	DXVector3 Rotate(const DXVector3& vec3)const;
	void ToZero();

	friend DXQuaternion RotationQuaternion(const DXQuaternion& _from, 
		const DXQuaternion& _to);

	friend void Lerp(DXQuaternion& _result, const DXQuaternion& _from,
		const DXQuaternion& _end, float _t);

	friend void Slerp( DXQuaternion& _result, const DXQuaternion& _start, 
		const DXQuaternion& _end, float _t);

	void ToRotation(const DXVector3& _vecFrom, const DXVector3& _vecTo);

	//overloaded operators
	bool operator==(const DXQuaternion &_quat)const;
	bool operator!=(const DXQuaternion &_quat)const;
	DXQuaternion operator+(DXQuaternion& _quat)const;
	DXQuaternion& operator+=(DXQuaternion& _quat);
	DXQuaternion operator-(DXQuaternion& _quat)const;
	DXQuaternion& operator-=(DXQuaternion& _quat);
	DXQuaternion operator*(float _scale)const;
	friend DXQuaternion operator*(float _scale, const DXQuaternion& _quat);
	DXQuaternion& operator*=(float _scale);
	DXQuaternion operator*(const DXQuaternion& _quat)const;
	DXQuaternion& operator*=(const DXQuaternion& _quat);
	DXQuaternion operator/(float _scale);
	DXQuaternion& operator/=(float _scale);
	void GetAxisAngle(DXVector3& _axis, float& _angle)const;
	friend std::ostream& operator<<(std::ostream& _out, const DXQuaternion& _quat);
	DXQuaternion& Clean();

#pragma endregion

	//public static variales
	static DXQuaternion identity;
	static DXQuaternion zero;

	// public memeber variable
	float m_w;//cos(theta/2)
	float m_x;//sin(theta/2) * x
	float m_y;//sin(theta/2) * y
	float m_z;//sin(theta/2) * z;
};
#endif