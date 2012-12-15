#ifndef DXMATH_H
#define DXMATH_H
#include <float.h>
#include <random>
#include <math.h>

namespace DXMath{
const float EPSILION = 1.0e-6f;
const float PI  = 3.1415926535897932384626433832795f;
const float HALFPI = 1.5707963267948966192313216916398f;
const float TWOPI =  2.0f * PI;
const float Infinity = FLT_MAX;
  
inline bool IsZero(float a)
{
	return (fabsf(a) <= EPSILION);
}

inline void SinCos(const float& angle, float& sinTheta, float& cosTheta)
{
	sinTheta  = sinf(angle);
	cosTheta = cosf(angle);
}

/// <summary>Query if '_a' and _b are equal.</summary>
///
/// <param name="_a">a. </param>
/// <param name="_b">b. </param>
///
/// <returns>true if equal, false if not.</returns>
inline bool IsEqual(float _a, float _b)
{
	return IsZero(_a - _b);// return true if they are equal

}

inline float DegreeToRadian(float _angle)
{
	float recip = 1.0f / 180.0f;
	return (_angle * PI) * recip;
}

template<typename T>
inline T Min(T _arg1, T _arg2)
{
	return (_arg1 < _arg2) ? _arg1 : _arg2;
}

template<typename T>
inline T Max(T _arg1, T _arg2)
{
	return (_arg1 > _arg2) ? _arg1 : _arg2;
}

inline float RadianToDegree(float _radian)
{
	float recip = 1.0 / PI;
	return (_radian * 180.0f) * recip;
}

template<class T>
T Clamp(const T& _val, const T& _min, const T& _max)
{
	return _val < _min ? _min : (_val > _max ? _max : _min);
}

inline float LerpPercentage(const float& _t, const float& _start, const float& _end)
{
		float per = _t - _start;
		per /= (_end - _start);
		return per;
}

///-------------------------------------------------------------------------------------------------
/// <summary>Gets the random.</summary>
///
/// <returns> the randm number between zero (inclusive) and 1(exclusive).
/// 		  [0,1)</returns>
///-------------------------------------------------------------------------------------------------
inline float RandZeroIncToOneExcf()
{
	return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

/// <summary>Return a random number between the minimum(inclusive) and max(exclusive)
/// 		 [min, max).</summary>
///
/// <param name="_minInc">The minimum. </param>
/// <param name="_maxExc">The maximum. </param>
///
/// <returns>.</returns>
inline float Randf(const float& _minInc, const float& _maxExc)
{
	return _minInc+ (RandZeroIncToOneExcf() * (_maxExc - _minInc));
}

///-------------------------------------------------------------------------------------------------
/// <summary>	Convert the cartessian coordiante to 
/// 			polar Angle [0,2*PI) in radian. </summary>
///
/// <param name="_x">	The x coordinate. </param>
/// <param name="_y">	The y coordinate. </param>
///
/// <returns>	. </returns>
///-------------------------------------------------------------------------------------------------
float AngleFromXY(const float _x, const float _y);

}// end of name space




#endif