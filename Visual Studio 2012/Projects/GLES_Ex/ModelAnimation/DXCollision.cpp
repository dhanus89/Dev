#include "DXCollision.h"
#include "DXMath.h"

namespace DXCollision{
bool RaySphereIntersect(const DXVector3& _origin,const DXVector3& _dir,const DXSphere& _sphere,float& _tOut, DXVector3& _pointOut )
{
	DXVector3 m = _origin - _sphere.center;
	float b = m.Dot(_dir);
	float c = m.Dot(m) - _sphere.radius * _sphere.radius;

	// no interscection if the ray origin is out side the sphere (s > 0) 
	// and ray is pointing away from the sphere (b > 0)
	if((c > 0.0f) && (b > 0.0f))return false;

	float discriminant(b*b - c);
	// check for negatie discriminant(ray is missing the the sphere)
	if(discriminant < 0.0f)return false;
	// find the smallest t, intersecting the sphere
	_tOut = -b - sqrtf(discriminant);
	// check if the ray started inside the sphere
	if(_tOut < 0.0f) _tOut = 0.0f;
	_pointOut = _origin + (_tOut* _dir);
	return true;
}

bool RayAABBIntersect(const DXVector3& _rayOrigin, const DXVector3& _rayDir, const DXAABB& _aabb, float& _tMin, DXVector3& _point)
{
	_tMin = 0.0f;
	float tMax(FLT_MAX);

	for(unsigned int i = 0; i < 3;++i)
	{
		if(abs(_rayDir(i)) < DXMath::EPSILION)// avodide division by zero (when ray is parallel)
		{
			// check if the ray origin is not within the slab ( ray does not intersect) 
			if(_rayOrigin(i) < _aabb.min(i) || _rayOrigin(i) > _aabb.max(i))
				return false;
		}//
		else
		{
			float invDivide = 1.0f/_rayDir(i);
			float t1((_aabb.min(i) - _rayOrigin(i)) * invDivide);
			float t2((_aabb.max(i) - _rayOrigin(i)) * invDivide);

			// make sure t1 has the smallest value
			if(t1 > t2) std::swap(t1,t2);
			if(t1 > _tMin)_tMin = t1;
			if(t2 > tMax)tMax = t2;

			if(t1 > t2)return false;
		}
	}
	_point = _rayOrigin + _rayDir * _tMin;
	return true;
}

bool RayIntersectTriangle(const DXVector3& _rayOrigin,const DXVector3& _rayDir, const DXVector3 _triPos[3],float& _u, float& _v, float& _w, float& _t)
{
	DXVector3 e1 = _triPos[1] - _triPos[0];
	DXVector3 e2 = _triPos[2] - _triPos[0];
	DXVector3 m = _rayOrigin - _triPos[0];

	float sndDeter = 1.0f / ScalerTripleProduct(_rayDir, e2,e1);
	DXVector3 m_X_e1 = m.Cross(e1);
	_u = ScalerTripleProduct(_rayDir, e2, m) * sndDeter;
	if(_u < 0.0f || _u > 1.0f)return false;

	_v = m_X_e1.Dot(_rayDir) * sndDeter;
	if(_v < 0.0f || _v > 1.0f || _u +_v > 1.0f)return false;
	_w = 1.0f - _u +_v;
	_t = m_X_e1.Dot(e2) * sndDeter;

	return true;
}

}// endof name space DXCollision