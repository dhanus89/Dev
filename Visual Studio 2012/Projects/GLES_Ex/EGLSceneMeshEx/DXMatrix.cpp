#include "DXMatrix.h"
#include "DXMath.h"

//******************************************************************
//							DXMatrix33 Definition
//******************************************************************

DXMatrix33 DXMatrix33::Identity(DXVector3(1.0f,0.0f,0.0f), DXVector3(0.0f,1.0f, 0.0f), DXVector3(0.0f, 0.0f, 1.0f));


//------------------------------------------------------------------
// name: DXMatrix33::DXMatrix33(const DXMatrix33& _mtx33)
//------------------------------------------------------------------
DXMatrix33::DXMatrix33(const DXMatrix33& _mtx33)
{
	m_v[0] = _mtx33.m_v[0];
	m_v[1] = _mtx33.m_v[1];
	m_v[2] = _mtx33.m_v[2];
	m_v[3] = _mtx33.m_v[3];
	m_v[4] = _mtx33.m_v[4];
	m_v[5] = _mtx33.m_v[5];
	m_v[6] = _mtx33.m_v[6];
	m_v[7] = _mtx33.m_v[7];
	m_v[8] = _mtx33.m_v[8];
}
 

DXMatrix33::DXMatrix33()
{
	memset(m_v, 0, sizeof(float) * 9);
}


DXMatrix33::DXMatrix33(const DXVector3 &_column1,const DXVector3 &_column2,
												const DXVector3 &_column3)
{
	SetColumns(_column1,_column2,_column3);
}


//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
DXMatrix33::DXMatrix33(const DXMatrix44& _mtx44)
{
	m_v[0] = _mtx44(0,0);
	m_v[1] = _mtx44(1,0);
	m_v[2] = _mtx44(2,0);

	m_v[3] = _mtx44(0,1);
	m_v[4] = _mtx44(1,1);
	m_v[5] = _mtx44(2,1);
	
	m_v[6] = _mtx44(0,2);
	m_v[7] = _mtx44(1,2);
	m_v[8] = _mtx44(2,2);
}

//------------------------------------------------------------------
// void DXMatrix33::SetRows(const DXVector3& _vec1, 
//				const DXVector3& _vec2, const DXVector3& _vec3) 
//------------------------------------------------------------------
 
void DXMatrix33::SetRows(const DXVector3& _row1, 
				const DXVector3& _row2, const DXVector3& _row3)
{
	m_v[0] = _row1.m_x;
	m_v[3] = _row1.m_y;
	m_v[6] = _row1.m_z;

	m_v[1] = _row2.m_x;
	m_v[4] = _row2.m_y;
	m_v[7] = _row2.m_z;

	m_v[2] = _row3.m_x;
	m_v[5] = _row3.m_y;
	m_v[8] = _row3.m_z;
}
 

//------------------------------------------------------------------
// void DXMatrix33::SetColumns(const DXVector3& _vec1,const DXVector3& _vec2,
//											const DXVector3& _vec3)
//------------------------------------------------------------------
void DXMatrix33::SetColumns(const DXVector3& _column1,const DXVector3& _column2,
	const DXVector3& _column3)
{
	m_v[0] = _column1.m_x;
	m_v[1] = _column1.m_y;
	m_v[2] = _column1.m_z;

	m_v[3] = _column2.m_x;
	m_v[4] = _column2.m_y;
	m_v[5] = _column2.m_z;

	m_v[6] = _column3.m_x;
	m_v[7] = _column3.m_y;
	m_v[8] = _column3.m_z;
}
 

DXVector3 operator* (const DXVector3 &_vec3, const DXMatrix33 &_mtx)
{
	float x = (_vec3.m_x * _mtx(0,0)) + (_vec3.m_y * _mtx(1,0)) + (_vec3.m_z *_mtx(2,0) );
	float y = (_vec3.m_x * _mtx(0,1)) + (_vec3.m_y * _mtx(1,1)) + (_vec3.m_z *_mtx(2,1) );
	float z = (_vec3.m_x * _mtx(0,3)) + (_vec3.m_y * _mtx(1,3)) + (_vec3.m_z *_mtx(2,3) );
	return DXVector3(x,y,z);
}

//------------------------------------------------------------------
// void DXMatrix33::Clean()
// desc: clean the elemensts that are close to zero
//------------------------------------------------------------------
void DXMatrix33::Clean()
{
	for(int i = 0; i < 9; ++i)
	{
		if(DXMath::IsZero(m_v[i]))
			m_v[i] = 0.0f;
	}
}
 
//Done
DXVector3 DXMatrix33::operator*(const DXVector3& _vec3)const
{
	float x = (m_v[0] * _vec3.m_x) + (m_v[3] * _vec3.m_y) + (m_v[6] * _vec3.m_z);
	float y = (m_v[1] * _vec3.m_x) + (m_v[4] * _vec3.m_y) + (m_v[7] * _vec3.m_z);
	float z = (m_v[2] * _vec3.m_x) + (m_v[5] * _vec3.m_y) + (m_v[8] * _vec3.m_z);
	return DXVector3(x, y,z);
}


//-----------------------------------------------------------------------------
//Done
//-----------------------------------------------------------------------------
float DXMatrix33::operator()(unsigned int _row, unsigned int _column)const
{
	// validate row and column
	if((_row < 0 || _row > 2) || (_column < 0 || _column > 2))
		return m_v[0];// return the first element.
	return m_v[(_column * 3) + _row];
}

//------------------------------------------------------------------
// void DXMatrix33::Identity()
//------------------------------------------------------------------
 //Done
void DXMatrix33::ToIdentity()
{
	m_v[0] = m_v[4] = m_v[8] = 1.0f;
	m_v[1] = m_v[2] = m_v[3] = m_v[5] = m_v[6] = m_v[7] = 0.0f;
}
 

//------------------------------------------------------------------
// DXMatrix33& DXMatrix33::Inverse()
//Done
//------------------------------------------------------------------
 DXMatrix33& DXMatrix33::Inverse()
{
	*this  = ::DXMatrix33Inverse(*this);
	return *this;
}
 
//------------------------------------------------------------------
// Name: DXMatrix33 DXMatrix33Inverse(DXMatrix33 &_mtx33) (friend)
//Done
//------------------------------------------------------------------
DXMatrix33 DXMatrix33Inverse(DXMatrix33 &_mtx33)
{
	// compute the determinant.
	float cofactor0 = (_mtx33.m_v[4] * _mtx33.m_v[8]) - (_mtx33.m_v[5] * _mtx33.m_v[7]);
	float cofactor3 = (_mtx33.m_v[7] * _mtx33.m_v[2]) - (_mtx33.m_v[1] * _mtx33.m_v[8]);
	float cofactor6 = (_mtx33.m_v[1] * _mtx33.m_v[5]) - (_mtx33.m_v[2] * _mtx33.m_v[4]);

	float det = _mtx33.m_v[0]*cofactor0 + _mtx33.m_v[3]*cofactor3 + _mtx33.m_v[6]*cofactor6;
	
	DXMatrix33 result;
	if(DXMath::IsZero(det)){
		result.Clear();
		return result;
	}
	
	det = 1.0f / det;
	result.m_v[0] = det * cofactor0;
	result.m_v[1] = det * cofactor3;
	result.m_v[2] = det * cofactor6;

	// adjoint of 3,4,5 entries is the cofactor of entries 1,4,7

	result.m_v[3] = det * ((_mtx33.m_v[5]*_mtx33.m_v[6]) - (_mtx33.m_v[3]*_mtx33.m_v[8]));
	result.m_v[4] = det * ((_mtx33.m_v[0]*_mtx33.m_v[8]) - (_mtx33.m_v[6]*_mtx33.m_v[2]));
	result.m_v[5] = det * ((_mtx33.m_v[3]*_mtx33.m_v[2]) - (_mtx33.m_v[0]*_mtx33.m_v[5]));

	// adjoint of 6,7,8 is the cofactor of 2,5,8.
	result.m_v[6] = det * ((_mtx33.m_v[3]*_mtx33.m_v[7]) - (_mtx33.m_v[6]*_mtx33.m_v[4]));
	result.m_v[7] = det * ((_mtx33.m_v[6]*_mtx33.m_v[1]) - (_mtx33.m_v[0]*_mtx33.m_v[7]));
	result.m_v[8] = det * ((_mtx33.m_v[0]*_mtx33.m_v[4]) - (_mtx33.m_v[3]*_mtx33.m_v[1]));

	return result;
}
 
//------------------------------------------------------------------
//	DXMatrix33& DXMatrix33::Transpose()
//done
//------------------------------------------------------------------
DXMatrix33& DXMatrix33::Transpose()
{
	*this = ::DXMatrix33Transpose(*this);
	return *this;
}
 
//------------------------------------------------------------------
// friend DXMatrix33 DXMatrix33Transpose(const DXMatrix33& _mtx33)
//Done
//------------------------------------------------------------------
DXMatrix33 DXMatrix33Transpose(const DXMatrix33& _mtx33)
{
	DXMatrix33 result;
	result.m_v[0] = _mtx33.m_v[0];
	result.m_v[1] = _mtx33.m_v[3];
	result.m_v[2] = _mtx33.m_v[6];

	result.m_v[3] = _mtx33.m_v[1];
	result.m_v[4] = _mtx33.m_v[4];
	result.m_v[5] = _mtx33.m_v[7];

	result.m_v[1] = _mtx33.m_v[2];
	result.m_v[7] = _mtx33.m_v[5];
	result.m_v[4] = _mtx33.m_v[8];
	return result;
}
 
//------------------------------------------------------------------
// DXMatrix33 Adjoint()const
//Done
//------------------------------------------------------------------
DXMatrix33 DXMatrix33::Adjoint()const
{
	DXMatrix33 adjoint;

	adjoint.m_v[0] = (m_v[4] * m_v[8]) - (m_v[5] * m_v[7]);
	adjoint.m_v[1] = (m_v[2] * m_v[7]) - (m_v[1] * m_v[8]);
	adjoint.m_v[2] = (m_v[1] * m_v[5]) - (m_v[4] * m_v[2]);

	adjoint.m_v[3] = (m_v[5]*m_v[6]) - (m_v[3] * m_v[8]);
	adjoint.m_v[4] = (m_v[0]*m_v[8]) - (m_v[2] * m_v[6]);
	adjoint.m_v[5] = (m_v[2] * m_v[3]) - (m_v[0] * m_v[5]);

	adjoint.m_v[6] = (m_v[7]*m_v[3]) - (m_v[4]*m_v[6]);
	adjoint.m_v[5] = (m_v[1]*m_v[6]) - (m_v[0]*m_v[7]);
	adjoint.m_v[8] = (m_v[0]*m_v[4]) - (m_v[1]*m_v[3]);

	return adjoint;
}
 
//------------------------------------------------------------------
// float DXMatrix33::Determinant()const
//done
//------------------------------------------------------------------
float DXMatrix33::Determinant()const
{
	// compute the determinant.
	return ::Determinant(*this);
}

//done
float Determinant(const DXMatrix33& _mtx33)
{
	float cofactor0 = (_mtx33.m_v[4] * _mtx33.m_v[8]) - (_mtx33.m_v[5] * _mtx33.m_v[7]);
	float cofactor3 = (_mtx33.m_v[7] * _mtx33.m_v[2]) - (_mtx33.m_v[1] * _mtx33.m_v[8]);
	float cofactor6 = (_mtx33.m_v[1] * _mtx33.m_v[5]) - (_mtx33.m_v[2] * _mtx33.m_v[4]);

	return (_mtx33.m_v[0]*cofactor0 + _mtx33.m_v[3]*cofactor3 + _mtx33.m_v[6]*cofactor6);
}

//------------------------------------------------------------------
// float DXMatrix33::Trace()const
//done
//------------------------------------------------------------------
float DXMatrix33::Trace()const
{
	return m_v[0] * m_v[4] * m_v[8];
}
 
//------------------------------------------------------------------
// DXMatrix33& DXMatrix33::Rotation(const DXQuaternion& _quat)
//------------------------------------------------------------------ 
DXMatrix33& DXMatrix33::SetRotation(const DXQuaternion& _quat)
{
	return *this;
}
 
//done
void DXMatrix33::Clear()
{
	memset(m_v,0.0f,sizeof(float) * 9); 
}

//done
DXMatrix33& DXMatrix33::operator=(const DXMatrix33& _mtx33)
{
	m_v[0] = _mtx33.m_v[0];
	m_v[1] = _mtx33.m_v[1];
	m_v[2] = _mtx33.m_v[2];
	m_v[3] = _mtx33.m_v[3];
	m_v[4] = _mtx33.m_v[4];
	m_v[5] = _mtx33.m_v[5];
	m_v[6] = _mtx33.m_v[6];
	m_v[7] = _mtx33.m_v[7];

	return *this;
}

//-----------------------------------------------------------------------------
// Name: DXVector3 DXMatrix33::GetRows(const int& _i)const
// Desc: Return the specified row of the matrix 
// Note: it is a zero based indexing.
//		 return the 1st row if the specfied row is out of range 
//Done
//-----------------------------------------------------------------------------
DXVector3 DXMatrix33::GetRow(const unsigned int _row)const
{
	
	if(_row==0)
	{
		return DXVector3(m_v[0],m_v[3],m_v[6]);
	}
	else if(_row == 1)
	{
		return DXVector3(m_v[1],m_v[4],m_v[7]);
	}
	else if(_row == 2)
	{
		return DXVector3(m_v[2],m_v[5],m_v[8]);
	}
	return DXVector3(m_v[0],m_v[3],m_v[6]);
}

//-----------------------------------------------------------------------------
// Name: DXVector3 DXMatrix33::GetRows(const int& _i)const
// Desc: Return the specified row of the matrix 
// Note: it is a 0 based indexing not zero based. 
//		 return the 1st column if the specfied row is out of range 
//-----------------------------------------------------------------------------
DXVector3 DXMatrix33::GetColumn(const unsigned int _column)const
{
	DXVector3 vec;
	if(_column==0)
	{
		return DXVector3(m_v[0],m_v[1],m_v[2]);
	}
	else if((_column == 1))
	{
		return DXVector3(m_v[5],m_v[4],m_v[5]);
	}
	else if((_column == 2))
	{
		return DXVector3(m_v[6],m_v[7],m_v[8]);
	}
	return DXVector3(m_v[0],m_v[1],m_v[2]);
}

//------------------------------------------------------------------
// DXMatrix33& DXMatrix33::SetRotation()
// desc: set rotation from the given euler angle
//------------------------------------------------------------------
DXMatrix33& DXMatrix33::SetRotation(float& _yRotate, float& _xRotate,
													float& _zRotate)
{
	float cosX, sinX;
	DXMath::SinCos(_xRotate, sinX, cosX);

	float sinY, cosY;
	DXMath::SinCos(_yRotate, sinY, cosY);


	float sinZ, cosZ;
	DXMath::SinCos(_zRotate, sinZ, cosZ);

	//first column
	m_v[0] = cosY * cosZ + sinY * sinX * sinZ;
	m_v[3] = sinZ * cosX;
	m_v[6] = -sinY * cosZ + cosY * sinX * sinZ;

	//second column
	m_v[1] = -cosY * sinZ + sinY * sinX * cosZ;
	m_v[4] = cosZ * cosX;
	m_v[7] = sinZ * sinY +  cosY * sinX * cosZ;

	//third column
	m_v[2] = sinY * cosX;
	m_v[5] = -sinX;
	m_v[8] = cosY * cosX;

	return *this;
}

//------------------------------------------------------------------
// DXMatrix33& DXMatrix33::SetScale(const DXVector3& _scale)
//------------------------------------------------------------------
DXMatrix33& DXMatrix33::Scale(const DXVector3& _scale)
{
	m_v[0] = _scale.m_x;
	m_v[4] = _scale.m_y;
	m_v[8] = _scale.m_z;
	m_v[1] = m_v[2] = m_v[3] = m_v[5] = m_v[6] = m_v[7] = 0.0f;
	return *this;
}
 
//------------------------------------------------------------------
// Name: DXMatrix33& DXMatrix33::SetRotationX(float& _angle)
// Desc: Set the matrix to raotation matrix around the X axis.
//done
//------------------------------------------------------------------
DXMatrix33& DXMatrix33::SetRotationX(const float& _angle)
{
	float sinTheta, cosTheta;
	DXMath::SinCos(_angle,sinTheta, cosTheta);
	m_v[0] = 1.0f;
	m_v[1] = m_v[2] = m_v[3] = m_v[6] = 0.0f;

	m_v[4] = m_v[8] = cosTheta;
	m_v[5] = sinTheta;
	m_v[7] = -sinTheta;
	return *this;
}

//done
DXMatrix33& DXMatrix33::SetRotationY(const float& _angle)
{
	float sinTheta, cosTheta;
	DXMath::SinCos(_angle,sinTheta, cosTheta);
	m_v[4] = 1.0f;
	m_v[3] = m_v[5] = m_v[1] = m_v[7] = 0.0f;

	m_v[0] = m_v[8] = cosTheta;
	m_v[6] = sinTheta;
	m_v[2] = -sinTheta;
	return *this;
}

//done
DXMatrix33& DXMatrix33::SetRotationZ(const float& _angle)
{
	float sinTheta, cosTheta;
	DXMath::SinCos(_angle,sinTheta, cosTheta);
	m_v[8] = 1.0f;
	m_v[2] = m_v[5] = m_v[6] = m_v[7] = 0.0f;

	m_v[0] = m_v[4] = cosTheta;
	m_v[1] = sinTheta;
	m_v[3] = -sinTheta;
	return *this;
}

//-----------------------------------------------------------------------------
// Name: void DXMatrix33::GetFixedAngles(float& _z, float& _x,float& _y)
// Desc: Get Fixed Angle format of this rotation matrix.
//-----------------------------------------------------------------------------
void DXMatrix33::GetFixedAngles(float& _z, float& _x,float& _y)const
{
	// need to implemenet the code.
}

//-----------------------------------------------------------------------------
// Name: void DXMatrix33::GetAxisAngle(DXVector3& _axis, float& _angle)
// Desc: Get the Axis angle format of this rotation matrix
//-----------------------------------------------------------------------------
void DXMatrix33::GetAxisAngle(DXVector3& _axis, float& _angle)const
{
	// calculate the trace. 
	float trace = Trace();
	// costeta = 1/2 (trace - 1)
	float cosTheta = (0.5f * trace) - 0.5f;
	_angle = acosf(cosTheta);
	
	// if the angle is 0 then the axis can be arbitrary set. (set the X axis)
	if(DXMath::IsZero(_angle))
		_axis = DXVector3::xAxis;
	
	// if the angle lies in the range of 0 and pi.
	else if(_angle < DXMath::PI - DXMath::EPSILION)
	{
		// m32 - m-23, m13-m31,m21-m12
		_axis.Set(m_v[7] - m_v[5], m_v[2] - m_v[6], m_v[3] - m_v[1]);
		_axis.Normalize();
	}
	else //the angle is  180 degree
	{
		float *vec = (float*)this;
		// comput the largest diagonal elements to the smallest
		unsigned int i = 0;
		if(m_v[4] > m_v[0])
			i = 1;
		if(m_v[8] > m_v[i + 3 * i])// check with the last cached largest value.
			i = 2;
		unsigned int j = (i + 1) %3;
		unsigned int k = (j + 1) %3;

		float s = sqrtf(m_v[i + 3 * i] - m_v[j+ 3 * j] - m_v[k + 3 * k] + 1.0f);
		vec[i] = 0.5f * s;
		float recip = 1.0f/s;
		vec[j] = (m_v[i + 3 *j]) * recip;
		vec[k] = (m_v[k + 3 * i]) * recip;
	}
}



//-----------------------------------------------------------------------------
//						DXMatrix44 Definition
//-----------------------------------------------------------------------------

DXMatrix44 DXMatrix44::Identity(DXVector4(1.0f, 0.0f, 0.0f, 0.0f), DXVector4(0.0f, 1.0f, 0.0f, 0.0f),
								DXVector4(0.0f, 0.0f, 1.0f, 0.0f), DXVector4(0.0f, 0.0f, 0.0f,1.0f));



DXMatrix44::DXMatrix44()
{
	memset(m_v,0.0f, sizeof(float)*16);
}

DXMatrix44::DXMatrix44(const DXVector4& _column1,const DXVector4& _column2,
	const DXVector4& _column3,const DXVector4& _column4)
{
	SetColumns(_column1,_column2,_column3,_column4);
}

const float& DXMatrix44::operator() (unsigned int _row, unsigned int _column)const
{
	return m_v[_column * 4 + _row];
}

float& DXMatrix44::operator() (unsigned int _row, unsigned int _column)
{
	return m_v[_column * 4 + _row];
}

DXMatrix44& DXMatrix44::SetDiagonal(const float& _x, const float& _y, const float& _z, const float& _w)
{
	m_v[0] = _x; m_v[5] = _y; m_v[10] = _x; m_v[15] = _w;
	return *this;
}

//float& DXMatrix44::operator()(unsigned int& _row,unsigned int& _column)
//{
//	return m_v[_column * 3 + _row];
//}

//float DXMatrix44::operator()(unsigned int _row, unsigned int _column)const
//{
//	return m_v[_column * 3 + _row];
//}

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
DXMatrix44::DXMatrix44(const DXQuaternion& _quat)
{
	// need to implement.
}

//-----------------------------------------------------------------------------
//done
//-----------------------------------------------------------------------------
DXMatrix44::DXMatrix44(const DXMatrix33& _mtx33)
{
	// set up the last row and the last column
	m_v[3] = m_v[7] = m_v[11] = m_v[12] = m_v[13] = m_v[14] = 0.0f;
	m_v[15] = 1.0f;

	m_v[0] = _mtx33(0,0);
	m_v[1] = _mtx33(1,0);
	m_v[2] = _mtx33(2,0);

	m_v[4] = _mtx33(0,1);
	m_v[5] = _mtx33(1,1);
	m_v[6] = _mtx33(2,1);
	
	m_v[8] = _mtx33(0,2);
	m_v[9] = _mtx33(1,2);
	m_v[10] = _mtx33(2,2);
}

//done
DXMatrix44& DXMatrix44::Transpose()
{
	m_v[0] = m_v[0];
	m_v[4] = m_v[1];
	m_v[8] = m_v[2];
	m_v[12] = m_v[3];

	m_v[1] = m_v[4];
	m_v[5] = m_v[5];
	m_v[9] = m_v[6];
	m_v[13] = m_v[7];

	m_v[2] = m_v[8];
	m_v[6] = m_v[9];
	m_v[10] = m_v[10];
	m_v[14] = m_v[11];

	m_v[3] = m_v[12];
	m_v[7] = m_v[13];
	m_v[11] = m_v[14];
	m_v[15] = m_v[15];

	return *this;
}

//done
DXMatrix44::DXMatrix44(const DXMatrix44& _mtx44)
{
	m_v[0] = _mtx44.m_v[0];
	m_v[1] = _mtx44.m_v[1];
	m_v[2] = _mtx44.m_v[2];
	m_v[3] = _mtx44.m_v[3];
	m_v[4] = _mtx44.m_v[4];
	m_v[5] = _mtx44.m_v[5];
	m_v[6] = _mtx44.m_v[6];
	m_v[7] = _mtx44.m_v[7];
	m_v[8] = _mtx44.m_v[8];
	m_v[9] = _mtx44.m_v[9];
	m_v[10] = _mtx44.m_v[10];
	m_v[11] = _mtx44.m_v[11];
	m_v[12] = _mtx44.m_v[12];
	m_v[13] = _mtx44.m_v[13];
	m_v[14] = _mtx44.m_v[14];
	m_v[15] = _mtx44.m_v[15];
}
//done
void DXMatrix44::Clear()
{
	memset(m_v, 0.0f, sizeof(float) * 16);
}

void DXMatrix44::SetColumn(const float _x,const float _y,const float _z,const float _w, unsigned int _column)
{
	if(_column > 3)
		return;
	switch(_column)
	{
	case 0:
		m_v[0] = _x; m_v[1] = _y; m_v[2] = _z;m_v[3] = _w;
		break;

	case 1:
		m_v[4] = _x; m_v[5] = _y; m_v[6] = _z;m_v[7] = _w;
		break;

	case 2:
		m_v[8] = _x; m_v[9] = _y; m_v[10] = _z; m_v[11] = _w;
		break;

	case 3:
		m_v[12] = _x; m_v[13] = _y; m_v[14] = _z; m_v[15] = _w;
		break;
	}
}

void DXMatrix44::SetColumn(const DXVector3& _vec3, unsigned int _column)
{
	if(_column > 3)
		return;
	switch(_column)
	{
		case 0:
			m_v[0] = _vec3.m_x; m_v[1] = _vec3.m_y; m_v[2] = _vec3.m_z;
		break;

		case 1:
			m_v[4] = _vec3.m_x; m_v[5] = _vec3.m_y; m_v[6] = _vec3.m_z;
		break;

		case 2:
			m_v[8] = _vec3.m_x; m_v[9] = _vec3.m_y; m_v[10] = _vec3.m_z;
		break;

		case 3:
			m_v[12] = _vec3.m_x; m_v[13] = _vec3.m_y; m_v[14] = _vec3.m_z;
		break;
	}
}

void DXMatrix44::SetColumn(const DXVector4& _vec4, unsigned int _column)
{
	if(_column > 3)
		return;
	switch(_column)
	{
	case 0:
		m_v[0] = _vec4.m_x; m_v[1] = _vec4.m_y; m_v[2] = _vec4.m_z; m_v[3] = _vec4.m_w;
		break;

	case 1:
		m_v[4] = _vec4.m_x; m_v[5] = _vec4.m_y; m_v[6] = _vec4.m_z; m_v[7] = _vec4.m_w;
		break;

	case 2:
		m_v[8] = _vec4.m_x; m_v[9] = _vec4.m_y; m_v[10] = _vec4.m_z; m_v[11] = _vec4.m_w;
		break;

	case 3:
		m_v[12] = _vec4.m_x; m_v[13] = _vec4.m_y; m_v[14] = _vec4.m_z; m_v[15] = _vec4.m_w;
		break;
	}
}

void DXMatrix44::SetRow(const float _x, const float _y, const float _z, const float _w, unsigned int _row)
{
	if(_row > 3)
		return;
	switch(_row)
	{
	case 0:
		m_v[0] = _x; m_v[4] = _y; m_v[8] = _z; m_v[12]  = _w;
			break;

	case 1:
		m_v[1] = _x; m_v[5] = _y; m_v[9] = _z; m_v[13]  = _w;
		break;

	case 2:
		m_v[2] = _x; m_v[6] = _y; m_v[10] = _z; m_v[14]  = _w;
		break;

	case 3:
		m_v[3] = _x; m_v[7] = _y; m_v[11] = _z; m_v[15]  = _w;
		break;
	}
}

void DXMatrix44::SetRow(const DXVector3& _vec3, unsigned int _row)
{
	if(_row > 3)
		return;
	switch(_row)
	{
	case 0:
		m_v[0] = _vec3.m_x; m_v[4] = _vec3.m_y; m_v[8] = _vec3.m_z;
		break;

	case 1:
		m_v[1] = _vec3.m_x; m_v[5] = _vec3.m_y; m_v[9] = _vec3.m_z;
		break;

	case 2:
		m_v[2] = _vec3.m_x; m_v[6] = _vec3.m_y; m_v[10] = _vec3.m_z;
		break;

	case 3:
		m_v[3] = _vec3.m_x; m_v[7] = _vec3.m_y; m_v[11] = _vec3.m_z;
		break;
	}
}

void DXMatrix44::SetRow(const DXVector4& _vec4, unsigned int _row)
{
	if(_row > 3)
		return;
	switch(_row)
	{
	case 0:
		m_v[0] = _vec4.m_x; m_v[4] = _vec4.m_y; m_v[8] = _vec4.m_z; m_v[12] = _vec4.m_w;
		break;

	case 1:
		m_v[1] = _vec4.m_x; m_v[5] = _vec4.m_y; m_v[9] = _vec4.m_z; m_v[13] = _vec4.m_w;
		break;

	case 2:
		m_v[2] = _vec4.m_x; m_v[6] = _vec4.m_y; m_v[10] = _vec4.m_z; m_v[14] = _vec4.m_w;
		break;

	case 3:
		m_v[3] = _vec4.m_x; m_v[7] = _vec4.m_y; m_v[11] = _vec4.m_z; m_v[15] = _vec4.m_w;
		break;
	}
}


void DXMatrix44::SetColumns(const DXVector4& _column1,const DXVector4& _column2,
	const DXVector4& _column3,const DXVector4& _column4)
{
	m_v[0] = _column1.m_x;
	m_v[1] = _column1.m_y;
	m_v[2] = _column1.m_z;
	m_v[3] = _column1.m_w;


	m_v[4] = _column2.m_x;
	m_v[5] = _column2.m_y;
	m_v[6] = _column2.m_z;
	m_v[7] = _column2.m_w;

	m_v[8] = _column3.m_x;
	m_v[9] = _column3.m_y;
	m_v[10] = _column3.m_z;
	m_v[11] = _column3.m_w;

	m_v[12] = _column4.m_x;
	m_v[13] = _column4.m_y;
	m_v[14] = _column4.m_z;
	m_v[15] = _column4.m_w;
}


//-----------------------------------------------------------------------------
// Name: DXVector3 DXMatrix44::GetTranslation()const
// Desc: return the transation poertion of this affine transform matrix
//-----------------------------------------------------------------------------
DXVector3 DXMatrix44::GetTranslation()const
{
	return DXVector3(m_v[12], m_v[13], m_v[14]);
}

//-----------------------------------------------------------------------------
// Name:  DXMatrix33 DXMatrix44::GetRotation()const
// Desc: Return the rotation portion of the affine transfomration. 
//-----------------------------------------------------------------------------
DXMatrix33 DXMatrix44::GetRotation()const
{
	return DXMatrix33(*this);
}

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
DXMatrix44 DXMatrix44AffineInverse(const DXMatrix44& _mtx44)
{
	DXMatrix44 result;
	// comput the determinanat of the rotation portion of the matrix
	// Affine Inverse formula

	// | R^inv , R^inv * T^inv |
	// |   0   ,      1        |

	// compute the determinant.
	float cofactor0 = (_mtx44.m_v[5] * _mtx44.m_v[10]) - (_mtx44.m_v[6] * _mtx44.m_v[9]);
	float cofactor4 = (_mtx44.m_v[2] * _mtx44.m_v[9]) - (_mtx44.m_v[1] * _mtx44.m_v[10]);
	float cofactor8 = (_mtx44.m_v[1] * _mtx44.m_v[6]) - (_mtx44.m_v[5] * _mtx44.m_v[2]);

	float det = _mtx44.m_v[0]*cofactor0 + _mtx44.m_v[4]*cofactor4 + _mtx44.m_v[8]*cofactor8;
	
	// is this singular matrix.
	if(DXMath::IsZero(det)){
		result.Clear();
		return result;
	}

	// comput the inverse of the rotation portion (upper 3 * 3)
	float invDet = 1.0f/ det;
	result.m_v[0] = invDet * cofactor0;
	result.m_v[1] = invDet * cofactor4;
	result.m_v[2] = invDet * cofactor8;

	result.m_v[4] = invDet * ((_mtx44.m_v[6] * _mtx44.m_v[8]) - (_mtx44.m_v[4] * _mtx44.m_v[10]));
	result.m_v[5] = invDet * ((_mtx44.m_v[0] * _mtx44.m_v[10]) - (_mtx44.m_v[2] * _mtx44.m_v[8]));
	result.m_v[6] = invDet * ((_mtx44.m_v[2] * _mtx44.m_v[4]) - (_mtx44.m_v[0] * _mtx44.m_v[6]));

	result.m_v[7] = invDet * ((_mtx44.m_v[4] * _mtx44.m_v[9]) - (_mtx44.m_v[5] * _mtx44.m_v[8]));
	result.m_v[9] = invDet * ((_mtx44.m_v[1] * _mtx44.m_v[8]) - (_mtx44.m_v[0] * _mtx44.m_v[9]));
	result.m_v[10] = invDet * ((_mtx44.m_v[0] * _mtx44.m_v[5]) - (_mtx44.m_v[1] * _mtx44.m_v[4]));

	// multiply the inverse translation by the inverse rotation for the
	// translation portion

	result.m_v[12] =  -result.m_v[0]*_mtx44.m_v[12] - result.m_v[4]*_mtx44.m_v[13] - result.m_v[8]*_mtx44.m_v[14];
	result.m_v[13] =  -result.m_v[1]*_mtx44.m_v[12] - result.m_v[5]*_mtx44.m_v[13] - result.m_v[9]*_mtx44.m_v[14];
	result.m_v[14] = -result.m_v[2]*_mtx44.m_v[12] - result.m_v[6]*_mtx44.m_v[13] - result.m_v[10]*_mtx44.m_v[14];
	result.m_v[15] = 1.0f;
	return result;
}

DXMatrix44& DXMatrix44::ToAffineInverse()
{
	*this = ::DXMatrix44AffineInverse(*this);
	return *this;
}

void DXMatrix44::RotateX(const float &_angle)
{
	float sine,cos;
	DXMath::SinCos(_angle,sine,cos);

	m_v[5] = m_v[10] = cos;
	m_v[6] = -sine;
	m_v[9] = sine;
}

void DXMatrix44::RotateY(const float &_angle)
{
	float sine,cos;
	DXMath::SinCos(_angle,sine,cos);
	m_v[0] = m_v[10] = cos;
	m_v[2] = sine;
	m_v[8] = -sine;
}

void DXMatrix44RotationY(DXMatrix44& _mtxOut, const float& _angle)
{
	_mtxOut.m_v[5] = _mtxOut.m_v[15] = 1.0f;
	_mtxOut.m_v[1] = _mtxOut.m_v[3] = _mtxOut.m_v[4] = _mtxOut.m_v[6] = _mtxOut.m_v[7] = _mtxOut.m_v[9]  = _mtxOut.m_v[10] = 0.0f;
	_mtxOut.m_v[11] = _mtxOut.m_v[12] = _mtxOut.m_v[13] = _mtxOut.m_v[14] = 0;

	float sine,cos;
	DXMath::SinCos(_angle,sine,cos);
	_mtxOut.m_v[0] = _mtxOut.m_v[10] = cos;
	_mtxOut.m_v[2] = sine;
	_mtxOut.m_v[8] = -sine;
}
// 0  1  2  3
// 4  5  6  7
// 8  9  10 11
// 12 13 14 15


// 0  4  8  12  
// 1  5  9  13
// 2  6  10 14
// 3  7  11 15

void DXMatrix44::RotateZ(const float &_angle)
{
	float sine,cos;
	DXMath::SinCos(_angle,sine,cos);
	m_v[0] = m_v[5] = cos;
	m_v[1] = sine;
	m_v[4] = -sine;
}




//done
void DXMatrix44::ToIdentity()
{
	m_v[0] = m_v[5] = m_v[10] = m_v[15] =  1.0f;
	m_v[1] = m_v[2] = m_v[3] = m_v[4] = m_v[6] = m_v[7] = m_v[8] = m_v[9] = 0.0f;
	m_v[11] = m_v[12] = m_v[13]= m_v[14]= 0.0f;
}

//-----------------------------------------------------------------------------
// Name: DXVector3 DXMatrix44::TransformPoint(const DXVector3& _point) (including
//		 translation)
//done
//-----------------------------------------------------------------------------
DXVector3 DXMatrix44::TransformPoint(const DXVector3& _point)const
{
	DXVector3* _pPoint = &TransformVec(_point);
	_pPoint->m_x += m_v[12];
	_pPoint->m_y += m_v[13];
	_pPoint->m_z += m_v[14];
	return *_pPoint;
}


//-----------------------------------------------------------------------------
// Name: DXVector3 DXMatrix44::TransformVec(const DXVector3& _vec3)
// Desc: transform the vector (no translation).
//done
//-----------------------------------------------------------------------------
DXVector3 DXMatrix44::TransformVec(const DXVector3& _vec3)const
{
	DXVector3 vec3;
	vec3.m_x = _vec3.m_x * m_v[0] + _vec3.m_y * m_v[4] + _vec3.m_z * m_v[8];
	vec3.m_y = _vec3.m_x * m_v[1] + _vec3.m_y * m_v[5] + _vec3.m_z * m_v[9];
	vec3.m_z = _vec3.m_x * m_v[2] + _vec3.m_y * m_v[6] + _vec3.m_z * m_v[10];
	return vec3;
}

DXVector3 DXMatrix44::TransformNormal(const DXVector3& _vec3)const
{
	DXMatrix33 mtx33(*this);
	return (mtx33.Inverse().Transpose()) * _vec3;
}

DXVector4 DXMatrix44::TransformNormal(const DXVector4& _vec4)const
{
	DXVector3 rslt = TransformNormal(DXVector3(_vec4.m_x, _vec4.m_y,_vec4.m_z));
	return DXVector4(rslt, 0.0f);
}

DXVector4 DXMatrix44::GetRow(unsigned int _row)const
{
	// 0   1  2  3
	// 4   5  6  7
	// 8   9 10 11
	// 12 13 14 15
	switch(_row)
	{
	case 0:
		return DXVector4(m_v[0], m_v[4], m_v[8], m_v[12]);

	case 1:
		return DXVector4(m_v[1], m_v[5], m_v[9], m_v[13]);
	break;

	case 2:
		return DXVector4(m_v[2], m_v[6], m_v[10], m_v[14]);

	case 3:
		return DXVector4(m_v[3], m_v[7], m_v[11], m_v[15]);

	default:
		return DXVector4(m_v[0], m_v[4], m_v[8], m_v[12]);
	}
}


DXVector4 DXMatrix44::Transform(const DXVector4& _vec4)const
{
	DXVector4 vec4;
	vec4.m_x = _vec4.m_x * m_v[0] + _vec4.m_y * m_v[1] + _vec4.m_z * m_v[2] + m_v[3];
	vec4.m_y = _vec4.m_x * m_v[4] + _vec4.m_y * m_v[5] + _vec4.m_z * m_v[6] + m_v[7];
	vec4.m_z = _vec4.m_x * m_v[8] + _vec4.m_y * m_v[9] + _vec4.m_z * m_v[10] + m_v[11];
	return vec4;
}

DXMatrix44& DXMatrix44::SetTranslation(const DXVector3& _transVec3)
{
	m_v[12] = _transVec3.m_x;
	m_v[13] = _transVec3.m_y;
	m_v[14] = _transVec3.m_z;
	m_v[15] = 1.0f;

	return *this;
}


DXMatrix44 DXMatrix44::operator+(const DXMatrix44& _mtx44)const
{
	DXMatrix44 rslt(_mtx44);
	rslt.m_v[0] = m_v[0] + _mtx44.m_v[0];
	rslt.m_v[1] = m_v[1] +_mtx44.m_v[1];
	rslt.m_v[2] = m_v[2] +_mtx44.m_v[2];
	rslt.m_v[3] = m_v[3] +_mtx44.m_v[3];
	rslt.m_v[4] = m_v[4] +_mtx44.m_v[4];
	rslt.m_v[5] = m_v[5] +_mtx44.m_v[5];
	rslt.m_v[6] = m_v[6] +_mtx44.m_v[6];
	rslt.m_v[7] = m_v[7] +_mtx44.m_v[7];
	rslt.m_v[8] = m_v[8] +_mtx44.m_v[8];
	rslt.m_v[9] = m_v[9] +_mtx44.m_v[9];
	rslt.m_v[10] = m_v[10] +_mtx44.m_v[10];
	rslt.m_v[11] = m_v[11] +_mtx44.m_v[11];
	rslt.m_v[12] = m_v[12] +_mtx44.m_v[12];
	rslt.m_v[13] = m_v[13] +_mtx44.m_v[13];
	rslt.m_v[14] = m_v[14] +_mtx44.m_v[14];
	rslt.m_v[15] = m_v[15] +_mtx44.m_v[15];
	return rslt;
}

DXMatrix44& DXMatrix44::operator+=(const DXMatrix44& _mtx44)
{
	
	m_v[0] += _mtx44.m_v[0];
	m_v[1] +=_mtx44.m_v[1];
	m_v[2] +=_mtx44.m_v[2];
	m_v[3] +=_mtx44.m_v[3];
	m_v[4] +=_mtx44.m_v[4];
	m_v[5] +=_mtx44.m_v[5];
	m_v[6] +=_mtx44.m_v[6];
	m_v[7] +=_mtx44.m_v[7];
	m_v[8] +=_mtx44.m_v[8];
	m_v[9] +=_mtx44.m_v[9];
	m_v[10] +=_mtx44.m_v[10];
	m_v[11] +=_mtx44.m_v[11];
	m_v[12] +=_mtx44.m_v[12];
	m_v[13] +=_mtx44.m_v[13];
	m_v[14] +=_mtx44.m_v[14];
	m_v[15] +=_mtx44.m_v[15];

	return *this;
}

DXMatrix44 DXMatrix44::operator*(const DXMatrix44& _mtx44)const
{
	DXMatrix44 rslt;
	//column 1
	rslt.m_v[0] = (m_v[0] * _mtx44.m_v[0]) + (m_v[4] * _mtx44.m_v[1]) + (m_v[8] * _mtx44.m_v[2]) + (m_v[12] * _mtx44.m_v[3]);
	rslt.m_v[1] = (m_v[1] * _mtx44.m_v[0]) + (m_v[5] * _mtx44.m_v[1]) + (m_v[9] * _mtx44.m_v[2]) + (m_v[13] * _mtx44.m_v[3]);
	rslt.m_v[2] = (m_v[2] * _mtx44.m_v[0]) + (m_v[6] * _mtx44.m_v[1]) + (m_v[10] * _mtx44.m_v[2]) + (m_v[14] * _mtx44.m_v[3]);
	rslt.m_v[3] = (m_v[3] * _mtx44.m_v[0]) + (m_v[7] * _mtx44.m_v[1]) + (m_v[11] * _mtx44.m_v[2]) + (m_v[15] * _mtx44.m_v[3]);

	rslt.m_v[4] = (m_v[0] * _mtx44.m_v[4]) + (m_v[4] * _mtx44.m_v[5]) + (m_v[8] * _mtx44.m_v[6]) + (m_v[12] * _mtx44.m_v[7]);
	rslt.m_v[5] = (m_v[1] * _mtx44.m_v[4]) + (m_v[5] * _mtx44.m_v[5]) + (m_v[9] * _mtx44.m_v[6]) + (m_v[13] * _mtx44.m_v[7]);
	rslt.m_v[6] = (m_v[2] * _mtx44.m_v[4]) + (m_v[6] * _mtx44.m_v[5]) + (m_v[10] * _mtx44.m_v[6]) + (m_v[14] * _mtx44.m_v[7]);
	rslt.m_v[7] = (m_v[3] * _mtx44.m_v[4]) + (m_v[7] * _mtx44.m_v[5]) + (m_v[11] * _mtx44.m_v[6]) + (m_v[15] * _mtx44.m_v[7]);

	rslt.m_v[8] = (m_v[0] * _mtx44.m_v[8]) + (m_v[4] * _mtx44.m_v[9]) + (m_v[8] * _mtx44.m_v[10]) + (m_v[12] * _mtx44.m_v[11]);
	rslt.m_v[9] = (m_v[1] * _mtx44.m_v[8]) + (m_v[5] * _mtx44.m_v[9]) + (m_v[9] * _mtx44.m_v[10]) + (m_v[13] * _mtx44.m_v[11]);
	rslt.m_v[10] = (m_v[2] * _mtx44.m_v[8]) + (m_v[6] * _mtx44.m_v[9]) + (m_v[10] * _mtx44.m_v[10]) + (m_v[14] * _mtx44.m_v[11]);
	rslt.m_v[11] = (m_v[3] * _mtx44.m_v[8]) + (m_v[7] * _mtx44.m_v[9]) + (m_v[11] * _mtx44.m_v[10]) + (m_v[15] * _mtx44.m_v[11]);

	rslt.m_v[12] = (m_v[0] * _mtx44.m_v[12]) + (m_v[4] * _mtx44.m_v[13]) + (m_v[8] * _mtx44.m_v[14]) + (m_v[12] * _mtx44.m_v[15]);
	rslt.m_v[13] = (m_v[1] * _mtx44.m_v[12]) + (m_v[5] * _mtx44.m_v[13]) + (m_v[9] * _mtx44.m_v[14]) + (m_v[13] * _mtx44.m_v[15]);
	rslt.m_v[14] = (m_v[2] * _mtx44.m_v[12]) + (m_v[6] * _mtx44.m_v[13]) + (m_v[10] * _mtx44.m_v[14]) + (m_v[14] * _mtx44.m_v[15]);
	rslt.m_v[15] = (m_v[3] * _mtx44.m_v[12]) + (m_v[7] * _mtx44.m_v[13]) + (m_v[11] * _mtx44.m_v[14]) + (m_v[15] * _mtx44.m_v[15]);
	return rslt;
}

DXMatrix44 DXMatrix44::operator*(float _scaler)const
{
	DXMatrix44 rslt;
	rslt.m_v[0] *= _scaler;
	rslt.m_v[1] *= _scaler;
	rslt.m_v[2] *=_scaler;
	rslt.m_v[3] *= _scaler;
	rslt.m_v[4] *= _scaler;
	rslt.m_v[5] *= _scaler;
	rslt.m_v[6] *= _scaler;
	rslt.m_v[7] *= _scaler;
	rslt.m_v[8] *= _scaler;
	rslt.m_v[9] *= _scaler;
	rslt.m_v[10] *= _scaler;
	rslt.m_v[11] *= _scaler;
	rslt.m_v[12] *= _scaler;
	rslt.m_v[13] *= _scaler;
	rslt.m_v[14] *= _scaler;
	rslt.m_v[15] *= _scaler;
	return rslt;
}

float DXMatrix44::Trace()const
{
	return (m_v[0] * m_v[5] * m_v[10] * m_v[15]);
}

DXMatrix44& DXMatrix44::operator*=(float _scaler)
{
	m_v[0] *= _scaler;
	m_v[1] *= _scaler;
	m_v[2] *= _scaler;
	m_v[3] *= _scaler;
	m_v[4] *= _scaler;
	m_v[5] *= _scaler;
	m_v[6] *= _scaler;
	m_v[7] *= _scaler;
	m_v[8] *= _scaler;
	m_v[9] *= _scaler;
	m_v[10] *= _scaler;
	m_v[11] *= _scaler;
	m_v[12] *= _scaler;
	m_v[13] *= _scaler;
	m_v[14] *= _scaler;
	m_v[15] *= _scaler;
	return *this;
}

DXMatrix44& DXMatrix44::operator*=(const DXMatrix44& _mtx4)
{
	//1st column
	m_v[0] =  (m_v[0] * _mtx4.m_v[0]) + (m_v[4] * _mtx4.m_v[1]) + (m_v[8] *  m_v[2]) + (m_v[2] *  m_v[3]);
	m_v[1] =  (m_v[1] * _mtx4.m_v[0]) + (m_v[5] * _mtx4.m_v[1]) + (m_v[9] *  m_v[2]) + (m_v[13] * m_v[3]);
	m_v[2] =  (m_v[2] * _mtx4.m_v[0]) + (m_v[6] * _mtx4.m_v[1]) + (m_v[10] * m_v[2]) + (m_v[14] * m_v[3]);
	m_v[3] =  (m_v[3] * _mtx4.m_v[0]) + (m_v[7] * _mtx4.m_v[1]) + (m_v[11] * m_v[2]) + (m_v[15] * m_v[3]);

	//2nd column
	m_v[4] =  (m_v[0] * _mtx4.m_v[4]) + (m_v[4] * _mtx4.m_v[5]) + (m_v[8] *  m_v[6]) + (m_v[12] * m_v[7]);
	m_v[5] =  (m_v[1] * _mtx4.m_v[4]) + (m_v[5] * _mtx4.m_v[5]) + (m_v[9] *  m_v[6]) + (m_v[13] * m_v[7]);
	m_v[6] =  (m_v[2] * _mtx4.m_v[4]) + (m_v[6] * _mtx4.m_v[5]) + (m_v[10] * m_v[6]) + (m_v[14] * m_v[7]);
	m_v[7] =  (m_v[3] * _mtx4.m_v[4]) + (m_v[7] * _mtx4.m_v[5]) + (m_v[11] * m_v[6]) + (m_v[15] * m_v[7]);


	//3rd column
	m_v[8] =  (m_v[0] * _mtx4.m_v[8]) + (m_v[4] * _mtx4.m_v[9]) + (m_v[8] *  m_v[10]) + (m_v[12] * m_v[11]);
	m_v[9] =  (m_v[1] * _mtx4.m_v[8]) + (m_v[5] * _mtx4.m_v[9]) + (m_v[9] *  m_v[10]) + (m_v[13] * m_v[11]);
	m_v[10] = (m_v[2] * _mtx4.m_v[8]) + (m_v[6] * _mtx4.m_v[9]) + (m_v[10] * m_v[10]) + (m_v[14] * m_v[11]);
	m_v[11] = (m_v[3] * _mtx4.m_v[8]) + (m_v[7] * _mtx4.m_v[9]) + (m_v[11] * m_v[10]) + (m_v[15] * m_v[11]);


	//4th column
	m_v[12] = (m_v[0] *  _mtx4.m_v[12]) + (m_v[4] *_mtx4.m_v[13]) + (m_v[8] *  m_v[14]) + (m_v[12] * m_v[15]);
	m_v[13] = (m_v[1] *  _mtx4.m_v[12]) + (m_v[5] *_mtx4.m_v[13]) + (m_v[9] *  m_v[14]) + (m_v[13] * m_v[15]);
	m_v[14] = (m_v[2] *  _mtx4.m_v[12]) + (m_v[6] *_mtx4.m_v[13]) + (m_v[10] * m_v[14]) + (m_v[14] * m_v[15]);
	m_v[15] = (m_v[3] *  _mtx4.m_v[12]) + (m_v[7] *_mtx4.m_v[13]) + (m_v[11] * m_v[14]) + (m_v[15] * m_v[15]);

	return *this;
}

DXMatrix44 DXMatrix44::operator-(const DXMatrix44& _mtx44)const
{
	DXMatrix44 rslt(_mtx44);
	rslt.m_v[0] = m_v[0] - _mtx44.m_v[0];
	rslt.m_v[1] = m_v[1] - _mtx44.m_v[1];
	rslt.m_v[2] = m_v[2] - _mtx44.m_v[2];
	rslt.m_v[3] = m_v[3] - _mtx44.m_v[3];
	rslt.m_v[4] = m_v[4] - _mtx44.m_v[4];
	rslt.m_v[5] = m_v[5] - _mtx44.m_v[5];
	rslt.m_v[6] = m_v[6] - _mtx44.m_v[6];
	rslt.m_v[7] = m_v[7] - _mtx44.m_v[7];
	rslt.m_v[8] = m_v[8] - _mtx44.m_v[8];
	rslt.m_v[9] = m_v[9] - _mtx44.m_v[9];
	rslt.m_v[10] = m_v[10] - _mtx44.m_v[10];
	rslt.m_v[11] = m_v[11] - _mtx44.m_v[11];
	rslt.m_v[12] = m_v[12] - _mtx44.m_v[12];
	rslt.m_v[13] = m_v[13] - _mtx44.m_v[13];
	rslt.m_v[14] = m_v[14] - _mtx44.m_v[14];
	rslt.m_v[15] = m_v[15] - _mtx44.m_v[15];
	return rslt;
}

DXMatrix44& DXMatrix44::operator-=(const DXMatrix44& _mtx44)
{
	m_v[0] -= _mtx44.m_v[0];
	m_v[1] -=_mtx44.m_v[1];
	m_v[2] -=_mtx44.m_v[2];
	m_v[3] -=_mtx44.m_v[3];
	m_v[4] -=_mtx44.m_v[4];
	m_v[5] -=_mtx44.m_v[5];
	m_v[6] -=_mtx44.m_v[6];
	m_v[7] -=_mtx44.m_v[7];
	m_v[8] -=_mtx44.m_v[8];
	m_v[9] -=_mtx44.m_v[9];
	m_v[10] -=_mtx44.m_v[10];
	m_v[11] -=_mtx44.m_v[11];
	m_v[12] -=_mtx44.m_v[12];
	m_v[13] -=_mtx44.m_v[13];
	m_v[14] -=_mtx44.m_v[14];
	m_v[15] -=_mtx44.m_v[15];

	return *this;
}

DXMatrix44 DXMatrix44::operator/(float _scaler)const
{
	_scaler = 1.0f/ _scaler;
	return (*this) * _scaler;
}

//float& DXMatrix44::operator ()(unsigned int& _row,unsigned int& _column)
//{
//	return m_v[_column * 3 + _row];
//}

DXMatrix44& DXMatrix44::operator/=(float _scaler)
{
	_scaler = 1.0f / _scaler;
	(*this) *= _scaler;
	return *this;
}

DXVector3 DXMatrix44::operator*(const DXVector3& _vec3)const
{
	float x = ((DXVector3)m_v[0]).Dot(_vec3);
	float y = ((DXVector3)m_v[4]).Dot(_vec3);
	float z = ((DXVector3)m_v[8]).Dot(_vec3);
	return DXVector3(x, y, z);
}

DXMatrix44& DXMatrix44::SetTranslation(const float &_x, const float &_y, const float &_z)
{
	m_v[12] = _x, m_v[13] = _y, m_v[14] = _z; m_v[15] = 1.0f;
	return *this;
}

//----------------------------------------------------------------
// Name: DXMatrix44& DXMatrix44::SetRotation(const DXMatrix33& _rotMtx)
// Desc: copy the rotation portion of the given 3x3 matrix (the remaining
//		 entries are unlatered).
// Done
//----------------------------------------------------------------
DXMatrix44& DXMatrix44::SetRotation(const DXMatrix33& _rotMtx)
{
	m_v[0] = _rotMtx(0,0);
	m_v[1] = _rotMtx(1,0);
	m_v[2] = _rotMtx(2,0);

	m_v[4] = _rotMtx(0,1);
	m_v[5] = _rotMtx(1,1);
	m_v[6] = _rotMtx(2,1);

	m_v[8] = _rotMtx(0,2);
	m_v[9] = _rotMtx(1,2);
	m_v[10] = _rotMtx(2,2);

	return *this;
}

DXMatrix44& DXMatrix44::SetRotation(const DXMatrix44& _rotMtx)
{
	m_v[0] = _rotMtx.m_v[0];
	m_v[1] = _rotMtx.m_v[1];
	m_v[2] = _rotMtx.m_v[2];

	m_v[4] = _rotMtx.m_v[4];
	m_v[5] = _rotMtx.m_v[5];
	m_v[6] = _rotMtx.m_v[6];

	m_v[8] = _rotMtx.m_v[8];
	m_v[9] = _rotMtx.m_v[9];
	m_v[10] = _rotMtx.m_v[10];

	return *this;
}

DXMatrix44 DXTranslationMtx4X4(const float _x,const float _y, const float _z )
{
	DXMatrix44 mtx = DXMatrix44::Identity;
	mtx.SetTranslation(_x,_y,_z);
	return mtx;
}

DXMatrix44 DXTranslationMtx4X4(const DXVector3& _vec3)
{
	DXMatrix44 mtx = DXMatrix44::Identity;
	mtx.SetTranslation(_vec3);
	return mtx;
}

DXMatrix44 DXScaleMtx4X4(const float _x, const float _y,const float _z)
{
	DXMatrix44 mtx;
	mtx.SetDiagonal(_x, _y, _z, 1.0f);
	return mtx;
}