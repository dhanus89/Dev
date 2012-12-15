#ifndef DXCOLLISION_H
#define DXCOLLISION_H
#include "DXVector.h"
struct DXSphere
{
	DXVector3 center;
	float radius;
};

struct DXAABB
{
	DXVector3 min;
	DXVector3 max;
};

namespace DXCollision{
///-------------------------------------------------------------------------------------------------
/// <summary>	Ray sphere intersect. </summary>
///
/// <param name="_origin">  	The ray origin. </param>
/// <param name="_dir">			The ray dir. </param>
/// <param name="_sphere">  	The sphere to be intected. </param>
/// <param name="_tOut">		[in,out] The t at intersection. </param>
/// <param name="_pointOut">	[in,out] The point at it intersected. </param>
///
/// <returns>	true if it succeeds, false if it fails. </returns>
///-------------------------------------------------------------------------------------------------
bool RaySphereIntersect(const DXVector3& _origin,const DXVector3& _dir,const DXSphere& _sphere,float& _tOut, DXVector3& _pointOut );


bool RayAABBIntersect(const DXVector3& _rayOrigin, const DXVector3& _rayDir, const DXAABB& _aabb, float& _tMin, float& _tMax);

bool RayIntersectTriangle(const DXVector3& _rayOrigin,const DXVector3& _rayDir, const DXVector3 _triPos[3],float& _u, float& _v, float& _w);

}// end of namespace DXCollison.
#endif