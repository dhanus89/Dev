#ifndef DXQUATERNION_H
#define DXQUATERNION_H

//  [6/25/2012 Dhanus]
#include <iostream>
#include "DXEulerAngles.h"

//Forward Declaration--------------------------------------
class DXVector3;
class DXMatrix33;
class DXMatrix44;

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
	DXQuaternion& Normalize();
	float Magnitude()const;
	void Set(float _zAxisAngle,float _xAxisAngle, float _yAxisAngle);
	void Set(float _angleInDegree, DXVector3& _axis);
	DXQuaternion& ToIdentity();
	DXVector3 Rotate(const DXVector3& vec3)const;
	void ToZero();
	float LengthSqr(void)const;
	friend DXQuaternion RotationQuaternion(const DXQuaternion& _from, 
		const DXQuaternion& _to);

	friend void DXQuaternionLerp(DXQuaternion& _result, const DXQuaternion& _from,
		const DXQuaternion& _end, float _t);

	friend void DXQuaternionSlerp( DXQuaternion& _result,const DXQuaternion& _start, 
		 DXQuaternion _end, float _t);

	friend DXQuaternion operator*(const float& _scaler, const DXQuaternion& _quat);

	void ToRotation(const DXVector3& _vecFrom, const DXVector3& _vecTo);

	//overloaded operators
	bool operator==(const DXQuaternion &_quat)const;
	bool operator!=(const DXQuaternion &_quat)const;
	DXQuaternion operator+(const DXQuaternion& _quat)const;
	DXQuaternion& operator+=(const DXQuaternion& _quat);
	DXQuaternion& operator-(DXQuaternion& _quat)const;
	DXQuaternion& operator-=(DXQuaternion& _quat);
	DXQuaternion operator*(float _scale)const;
	DXQuaternion operator-(const DXQuaternion& _quat)const;
	DXQuaternion& operator*=(float _scale);
	DXQuaternion operator*(const DXQuaternion& _quat)const;
	DXQuaternion& operator*=(const DXQuaternion& _quat);
	DXQuaternion operator/(float _scale);
	DXQuaternion& operator/=(float _scale);
	void GetAxisAngle(DXVector3& _axis, float& _angle)const;
	DXQuaternion& operator=(const DXQuaternion& _quat);
	friend std::ostream& operator<<(std::ostream& _out, const DXQuaternion& _quat);
	DXQuaternion& Clean();

#pragma endregion

	//public static variales
	static DXQuaternion Identity;
	static DXQuaternion Zero;

	// public memeber variable
	float m_w;//cos(theta/2)
	float m_x;//sin(theta/2) * x
	float m_y;//sin(theta/2) * y
	float m_z;//sin(theta/2) * z;
};
#endif