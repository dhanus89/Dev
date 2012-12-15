#ifndef DXGEOMETRY_H
#define DXGEOMETRY_H
#include "DXVector.h"
#include "DXMatrix.h"




/// <summary>	Dx plane
/// 		using plane eqation Ax + By + Cz + d = 0. </summary>
struct DXPlane
{
	DXVector3 m_normal;// plane normal
	float m_dist;// plane Distance from the origin
	DXPlane(float _nx, float _ny, float _nz,float _dist);
	DXPlane(DXVector4 _vec4);
	DXPlane(const DXVector3& _normal, float _dist);
	DXPlane();
	
};

struct DXFrustum
{
	DXPlane plane[6];// 6 planes
	DXFrustum(const DXPlane& _left,const DXPlane& right, const DXPlane& _top,
		const DXPlane& _bottom, const DXPlane& _near, DXPlane& _far);
};

void ConstructPlane(const DXVector3& _p1,const DXVector3& _p2, const DXVector3& _p3);

///-------------------------------------------------------------------------------------------------
/// <summary>	Dx transform plane. </summary>
///
/// <param name="_planeIn">    The plane in. </param>
/// <param name="_planeOut">   [in,out] The plane out. </param>
/// <param name="_mtx4x4">	   The fourth mtx 4x. </param>
/// <param name="_mtxInvTras"> true if the matrix is inverse transpose. </param>
///-------------------------------------------------------------------------------------------------
void DXTransformPlane(const DXPlane& _planeIn,DXPlane& _planeOut,DXMatrix44 _mtx4x4, bool _mtxInvTras);

void DXTrasformFrustum(const DXFrustum& _planeIn, DXFrustum& _planeOut, DXMatrix44 _mtx);


#endif