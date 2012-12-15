#include "DXGeometry.h"
#include "DXMatrix.h"

DXFrustum::DXFrustum(const DXPlane& _left,const DXPlane& _right, const DXPlane& _top, const DXPlane& _bottom, const DXPlane& _near, DXPlane& _far)
{
	plane[0] = _left;
	plane[1] = _right;
	plane[2] = _top;
	plane[3] = _bottom;
	plane[4] = _near;
	plane[5] = _far;
}


//==========================================================
//	Plane Specifics
//==========================================================

DXPlane::DXPlane() : m_normal(0.0f,0.0f,0.0f),m_dist(0.0f)
{

}

DXPlane::DXPlane(DXVector4 _vec4) : m_normal(_vec4.m_x,_vec4.m_y,_vec4.m_z),
									m_dist(_vec4.m_w)
{

}

DXPlane::DXPlane(const DXVector3& _normal, float _dist) : 
	m_normal(_normal), m_dist(_dist)
{

}

void ConstructPlane(const DXVector3& _p1,const DXVector3& _p2, const DXVector3& _p3)
{
	DXPlane plane;
	DXVector3 e0 = _p2 - _p1;
	DXVector3 e1 = _p3 - _p1;

	plane.m_normal = e1.Cross(e0);
	plane.m_normal.Normalize();

	plane.m_dist = -(plane.m_normal.Dot(_p1));

}



void DXTransformPlane(const DXPlane& _planeIn,DXPlane& _planeOut,DXMatrix44 _mtx4x4, bool _mtxInvTras)
{
	if(!_mtxInvTras)
	//	_mtx4x4.AffineInverse().Transpose();

	DXVector4 plane(_planeIn.m_normal,_planeIn.m_dist);
	_mtx4x4.Transform(plane);
	_planeOut.m_normal = plane;
	_planeOut.m_dist = plane.m_w;
}

void DXTrasformFrustum(const DXFrustum& _frustumIn, DXFrustum& _frustumOut, DXMatrix44 _mtx)
{
	_mtx.AffineInverse().Transpose();
	for(unsigned int i = 0; i < 6; i++)
	{
		DXTransformPlane(_frustumIn.plane[i], _frustumOut.plane[i],_mtx,true);
	}
}