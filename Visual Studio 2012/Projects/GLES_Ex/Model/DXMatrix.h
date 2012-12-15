#ifndef DXMATRIX_H
#define DXMATRIX_H

#include "DXVector.h"
#include "DXQuaternion.h"


//-----------------------------------------------------------------
//							Forward Declaration 
//-----------------------------------------------------------------
class DXMatrix44;

//******************************************************************
//							DXMatrix33 Declaration
//******************************************************************
class DXMatrix33
{
public:
	DXMatrix33();
	DXMatrix33(const DXMatrix33& _mtx33);
	DXMatrix33(const DXMatrix44& _mtx44);
	DXMatrix33::DXMatrix33(const DXVector3 &_column1,const DXVector3 &_column2,
														const DXVector3 &_column3);

	void SetRows(const DXVector3& _vec1, const DXVector3& _vec2, const DXVector3& _vec3);
	
	DXVector3 GetRow(const unsigned _row)const;
	DXVector3 GetColumn(const unsigned _column)const;
	void SetColumns(const DXVector3& _column1,const DXVector3& _column2, const DXVector3& _column3);
	void Clean();
	void ToIdentity();
	DXMatrix33& Inverse();
	friend DXMatrix33 DXMatrix33Inverse(DXMatrix33& _mtx33);
	DXMatrix33& Transpose();
	friend DXMatrix33 DXMatrix33Transpose(const DXMatrix33& _mtx33);
	DXMatrix33 Adjoint()const;
	float Determinant()const;
	float Trace()const;


	//	Transformation----
	// convert Qauternion to Rotation matrix
	DXMatrix33& SetRotation(const DXQuaternion& _quat);
	// convert euler rotation to Matrix rotation
	DXMatrix33& SetRotation(float& _yRotate, float& _xRotate, float& _zRotate);
	// convert axis angle rotation to rotation matrix
	DXMatrix33& SetRotation(const DXVector3& _axis, float _angle);
	DXMatrix33& Scale(const DXVector3& _scale);
	DXMatrix33& SetRotationX(const float& _angle);
	DXMatrix33& SetRotationY(const float& _angle);
	DXMatrix33& SetRotationZ(const float& _angle);
	void GetFixedAngles(float& _z, float& _x,float& _y)const;
	void GetAxisAngle(DXVector3& _axis, float& _angle)const;
	DXQuaternion GetQuaternion()const;
	bool IsIdentity()const;
	
	//	Overloaded Operators
	DXMatrix33& operator=(const DXMatrix33& _mtx);
	float operator()(unsigned int _i, unsigned int _j)const;
	bool operator==(const DXMatrix33& _mtx)const;
	bool operator!=(const DXMatrix33& _mtx)const;
	DXVector3 operator*(const DXVector3& _vec)const;
	
	

	DXMatrix33& operator*=(const DXMatrix33& _mtx33);
	
	DXMatrix33 operator*(const DXMatrix33& _mtx33);
	
	friend DXVector3 operator*(const DXVector3& _vec3, 
									const DXMatrix33& _mtx33);
	
	friend float Determinant(const DXMatrix33& _mtx33);

	DXMatrix33& operator*=(const float& _scaler);
	operator float *(){return m_v;}
	DXMatrix33& operator+=(const DXMatrix33& _mtx);
	DXMatrix33 operator+(const DXMatrix33& _mtx)const;
	DXMatrix33 operator-(const DXMatrix33& _mtx)const;
	DXMatrix33& operator-=(const DXMatrix33& _mtx);
	void Clear();

	static DXMatrix33 Identity;

private:
	float m_v[9];
};


//******************************************************************
//							DXMatrix44 Declaration
//******************************************************************
class DXMatrix44
{

public:
	//------------------- member functions------------------------
	
	//Set the matrix with 0 entries
	DXMatrix44();
	DXMatrix44(const DXQuaternion& _quat);
	DXMatrix44(const DXMatrix33& _mtx33);
	
	DXMatrix44(const DXVector4& _column1,const DXVector4& _column2,
		const DXVector4& _column3,const DXVector4& _column4);
	
	DXMatrix44(const DXMatrix44& _mtx44);
	void ToIdentity();
	void Rotation(const DXMatrix33& _mtx33);


	///-------------------------------------------------------------------------------------------------
	/// <summary> Set the last Column as translation colimn with the last entry 1.0f. </summary>
	/// 
	///-------------------------------------------------------------------------------------------------	
	DXMatrix44& SetTranslation(const DXVector3& _transVec3);
	
	///-------------------------------------------------------------------------------------------------
	/// <summary> Set the last Column as translation colimn with the last entry 1.0f. </summary>
	/// 
	///-------------------------------------------------------------------------------------------------	
	DXMatrix44& SetTranslation(const float &_x, const float &_y, const float &_z);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Transform the 3d point, by assuming 4d vector with w = 1.0f.   </summary>
	///
	/// <param name="_point">	The point. </param>
	///
	/// <returns> the transform point </returns>
	///-------------------------------------------------------------------------------------------------	
	DXVector3 TransformPoint(const DXVector3& _point)const;
	
	///-------------------------------------------------------------------------------------------------
	/// <summary>	Transform vector ( no translation). </summary>
	///
	/// <param name="_vec3">	The third vector. </param>
	///
	/// <returns> Transform vector </returns>
	///-------------------------------------------------------------------------------------------------
	DXVector3 TransformVec(const DXVector3& _vec3) const;

	DXVector3 TransformNormal(const DXVector3& _vec3)const;

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Transform normal by inverse transpose of this matrix. </summary>
	///
	/// <param name="_vec3">	The third vector. </param>
	///
	/// <returns>the traform normal with w = 0.0f </returns>
	///-------------------------------------------------------------------------------------------------
	DXVector4 DXMatrix44::TransformNormal(const DXVector4& _vec4)const;
	friend DXMatrix44 DXMatrix44AffineInverse(const DXMatrix44& _mat44);
	DXVector4 Transform(const DXVector4& _vec4)const;
	DXMatrix44& ToAffineInverse();
	DXVector3 GetTranslation()const;
	DXMatrix33 GetRotation()const;
	DXMatrix44& Transpose();

	/// <summary>	Clears this object to its blank/initial state. </summary>
	void Clear();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Sets a row. </summary>
	///
	/// <param name="_vec3">	The third vector. </param>
	/// <param name="_row"> 	The row based on 0 indexed. </param>
	///-------------------------------------------------------------------------------------------------
	void SetRow(const DXVector3& _vec3, unsigned int _row);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Sets a row. </summary>
	///
	/// <param name="_x">  	The x coordinate. </param>
	/// <param name="_y">  	The y coordinate. </param>
	/// <param name="_z">  	The z coordinate. </param>
	/// <param name="_w">  	The w. </param>
	/// <param name="_row">	The row based on 0 indexed. </param>
	///-------------------------------------------------------------------------------------------------
	void SetRow(const float _x, const float _y, const float _z, const float _w, unsigned int _row);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Sets a row. </summary>
	///
	/// <param name="_vec4">	The fourth vector. </param>
	/// <param name="_row"> 	The row based on 0 indexed. </param>
	///-------------------------------------------------------------------------------------------------
	void SetRow(const DXVector4& _vec4, unsigned int _row);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Sets a column. </summary>
	///
	/// <param name="_vec3">  	The third vector. </param>
	/// <param name="_column">	The column based on 0 indexed. </param>
	///-------------------------------------------------------------------------------------------------
	void SetColumn(const DXVector3& _vec3, unsigned int _column);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Sets a column. </summary>
	///
	/// <param name="_x">	  	The x coordinate. </param>
	/// <param name="_y">	  	The y coordinate. </param>
	/// <param name="_z">	  	The z coordinate. </param>
	/// <param name="_w">	  	The w. </param>
	/// <param name="_column">	The column based on 0 indexed. </param>
	///-------------------------------------------------------------------------------------------------
	void DXMatrix44::SetColumn(const float _x,const float _y,const float _z,const float _w, unsigned int _column);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Sets a column. </summary>
	///
	/// <param name="_vec4">  	The fourth vector. </param>
	/// <param name="_column">	The column based on 0 indexed. </param>
	///-------------------------------------------------------------------------------------------------
	void SetColumn(const DXVector4& _vec4, unsigned int _column);

	//overloaded operators
	float& operator()(unsigned int _row, unsigned int _column);

	///-------------------------------------------------------------------------------------------------
	/// <summary> access the component of the matrix with given row and
	/// 		  column (0 indexed) </summary>
	///
	/// <returns>	The result of the operation. </returns>
	///-------------------------------------------------------------------------------------------------
	const float& operator()(unsigned int _row, unsigned int _column)const;


	
	inline DXMatrix44& SetDiagonal(const float& _x, const float& _y, const float& _z, const float& _w = 1.0f);
	DXMatrix44 operator+(const DXMatrix44& _mtx44)const;
	DXMatrix44& operator+=(const DXMatrix44& _mtx44);
	DXMatrix44 operator*(const DXMatrix44& _mtx44)const;
	DXMatrix44 operator*(float _scaler)const;
	DXMatrix44& operator*=(float _scaler);
	DXMatrix44 operator=(const DXMatrix44& _mtx44);
	DXMatrix44& operator*=(const DXMatrix44& _mtx44);
	DXMatrix44 operator-(const DXMatrix44& _mtx44)const;
	DXMatrix44& operator-=(const DXMatrix44& _mtx44);
	DXMatrix44 operator/(float _scaler)const;
	DXMatrix44& operator/=(float _scaler);
	DXVector3 operator*(const DXVector3 &_vec3)const;
	DXMatrix44& SetRotation(const DXMatrix33& _rotMtx);
	DXMatrix44& SetRotation(const DXMatrix44& _rotMtx);
	void SetColumns(const DXVector4& _column1,const DXVector4& _column2,
				const DXVector4& _column3,const DXVector4& _column4);

	DXVector4 GetRow(unsigned int _row)const;
	void RotateX(const float &_angle);
	void RotateY(const float &_angle);
	void RotateZ(const float &_angle);

	float Trace()const;


	// friend helper function

	///------------------------------------------------------------------------------------------
	/// <summary>	Dx translation mtx 4 x coordinate 4. </summary>
	///
	/// <param name="_x"> The x coordinate. </param>
	/// <param name="_y"> The y coordinate. </param>
	/// <param name="_z"> The z coordinate. </param>
	///
	/// <returns> </returns>
	///------------------------------------------------------------------------------------------
	friend DXMatrix44 DXTranslationMtx4X4(const float _x,const float _y,const float _z);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Dx translation mtx 4 x coordinate 4. </summary>
	///
	/// <param name="_vec">	The vector. </param>
	///
	/// <returns>	. </returns>
	///-------------------------------------------------------------------------------------------------
	friend DXMatrix44 DXTranslationMtx4X4(const DXVector3& _vec);

	///------------------------------------------------------------------------------------------
	/// <summary>	Dx scale mtx 4 x coordinate 4. </summary>
	///
	/// <param name="_x"> The x coordinate. </param>
	/// <param name="_y"> The y coordinate. </param>
	/// <param name="_z"> The z coordinate. </param>
	///
	/// <returns> </returns>
	///------------------------------------------------------------------------------------------
	friend DXMatrix44 DXScaleMtx4X4(const float _x, const float _y,const float _z);
	friend void DXMatrix44RotationY(DXMatrix44& _mtxOut, const float& _angleInRadian);

	
	static DXMatrix44 Identity;

// --------------------------member varibales----------------------
private:
	float m_v[16];
};




#endif