
//-----------------------------------------------------------------------
// Author: Dhanus
//-----------------------------------------------------------------------

#ifndef DXVECTOR_H
#define DXVECTOR_H
#include <iostream>

// forward declaration
class DXVector2;
class DXVector3;
class DXVector4;


class DXVector2
{
public:

#pragma region
	DXVector2(float _x = 0.0f, float _y  = 0.0f);
	float Dot(const DXVector2 &_vec)const;
	DXVector2& Normalize();
	float Length()const;
	float LengthSqr()const;
	void Set(const DXVector2& _vec);
	void Set(float& _x, float& _y);

	// overloaded operators
	float operator[](unsigned int _i)const {return (&m_x)[_i];}
	bool operator==(const DXVector2& _vec)const;
	bool operator!=(const DXVector2& _vec)const;
	DXVector2 operator-(const DXVector2& _vec)const;
	DXVector2& operator-=(const DXVector2& vec);
	DXVector2 operator+(const DXVector2& _vec)const;
	DXVector2& operator+=(const DXVector2& vec);

	friend DXVector2 operator*(float _scaler, const DXVector2& _vec);
	DXVector2& operator*=(float _scaler);
	DXVector2	operator/(float _scaler)const;
	DXVector2& operator/= (float _scaler);	
	friend std::ostream& operator<<(std::ostream& out, const DXVector2& vec);

	//cross prodcut and perpedicular equivalent.
	DXVector2 Perpendicular()const {return DXVector2(-m_y, m_x);}
	friend DXVector2 Cross(const DXVector2& vec1, const DXVector2& vec2);
	float PerpDot(const DXVector2& _vec)const;	

	bool IsZero();	
	inline void Zero();// s all aelements to zero

#pragma endregion

	static DXVector2 xAxis;
	static DXVector2 yAxis;

	// member varibales
	float m_x, m_y;
};



class DXVector3
{
public:
	//-------------------- Public memeber function -------------------------
#pragma region
	DXVector3& Normalize();
	explicit DXVector3(float x = 0.0f, float y = 0.0f, float z = 0.0f );
	DXVector3(const DXVector3& vec3);
	DXVector3& operator=(const DXVector3& _vec3);
	DXVector3 Cross(const DXVector3& _vec3)const;
	float Dot(const DXVector3& _vec3)const;
	float Length()const;
	float LengthSqr()const;
	friend DXVector3 operator-(const DXVector3& _vecA, const DXVector3 &_vecB);
	friend DXVector3 operator-(const DXVector3& _vec3);
	friend float ScalerTripleProduct(const DXVector3& _vecCross1, const DXVector3& _vecCross2, const DXVector3& _vecDot);
	float operator()(unsigned int _i)const;
	bool operator<(const DXVector3& _vec)const;
	bool operator>(const DXVector3& _vec)const;
	DXVector3& operator-=(const DXVector3 &_vec3);
	DXVector3 operator+(const DXVector3 &_vec3)const;
	DXVector3& operator=(const DXVector4& _vec4);
	DXVector3& operator+=(const DXVector3 &_vec);
	void Set(float _x, float _y, float _z){m_x = _x; m_y = _y; m_z = _z;}
	void ToZero();
	DXVector3 operator*(float _scaler)const;
	DXVector3 operator*(const DXVector3& _pVec3)const;
	DXVector3& operator*= (const float& _real);
	friend std::ostream& operator<<(std::ostream& out, const DXVector3& vec);

	friend DXVector3 operator*(float _scale, const DXVector3& _vec3);

	void BarycentricCoordinates( float &_r, float &_s, float& _t, const DXVector2& _point,
		const DXVector2& _p0, const DXVector2& _p1, const DXVector2& _p2);


	// other helper function

#pragma region Documentation
	/// <summary>return the vector that has minimum components 
	/// 		 of these two vector</summary>
	///
	/// <param name="_vec1">The first vector. </param>
	/// <param name="_vec2">The second vector. </param>
	///
	/// <returns>.</returns>
#pragma endregion
	friend DXVector3 VectorMin(const DXVector3& _vec1,const DXVector3& _vec2 );

#pragma region Documentation
	/// <summary>Vector maximum.</summary>
	///
	/// <param name="_vec1">The first vector. </param>
	/// <param name="_vec2">The second vector. </param>
	///
	/// <returns>.</returns>
#pragma endregion
	friend DXVector3 VectorMax(const DXVector3& _vec1,const DXVector3& _vec2 );

#pragma endregion	
	//staic memebrs
	static DXVector3 xAxis;
	static DXVector3 yAxis;
	static DXVector3 zAxis;
	static DXVector3 origin;
	static DXVector3 Max;
	static DXVector3 Min;

	//--------------------- Public Members variables------------------------
	float m_x, m_y ,m_z;
};

///-------------------------------------------------------------------------------------------------
/// <summary>	Construct a vector with same value.
/// 			ex, DXVector(_val,_val,_val) </summary>
///
/// <param name="_val"> The value. </param>
///
/// <returns> Replciated vector	. </returns>
///-------------------------------------------------------------------------------------------------
DXVector3 DXVec3Replicate(float _val);

class DXVector4
{
public:

#pragma region 
	// Constructor
	DXVector4(float _x = 0.0f, float _y = 0.0f, float z = 0.0f, float _w = 0.0f);
	DXVector4(const DXVector3& _vec3, const float& _w);
 	inline void Set(float _x, float _y, float _z, float _w);
	inline void Set(const DXVector3& _vec3, const float& _w);
	DXVector4& Normalize();
	//vector operations
	float Dot(const DXVector4& _vec4)const;
	float LengthSqr()const;
	float Length()const;
	DXVector4& operator=(const DXVector4& _vec4);
	friend DXVector4 operator-(const DXVector4& _vecA, const DXVector4 &_vecB);
	friend DXVector4 operator-(const DXVector4& _vec4);
	DXVector4& operator-=(const DXVector4 &_vec4);
	DXVector4 operator+(const DXVector4 &_vec4)const;
	DXVector4& operator+=(const DXVector4 &_vec4);
	
	void ToZero();
	DXVector4 operator*(float _scaler)const;
	DXVector4 operator*=(float _scaler);
	friend DXVector4 operator*(float _scale, const DXVector4& _vec4);

#pragma endregion

	float m_x, m_y, m_z, m_w;
};
///-------------------------------------------------------------------------------------------------
/// <summary>	Construct a vector with same value.
/// 			ex, DXVector(_val,_val,_val, _val) </summary>
///
/// <param name="_val"> The value. </param>
///
/// <returns> Replciated vector	. </returns>
///-------------------------------------------------------------------------------------------------
DXVector4 DXVec4Replicate(float _val);

#endif