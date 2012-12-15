#include "DXTransform.h"


namespace DXTransform{
void ComputeNormal(const DXVector3& _p0, const DXVector3& _p1,
	const DXVector3& _p2, DXVector3& _out)
{
	DXVector3 edge1 (_p1 - _p0);
	DXVector3 edge2(_p2 - _p0);
	_out = edge1.Cross(edge2);
	_out.Normalize();

}


void LookAtRH(const DXVector3 &_pos, const DXVector3 &_target, DXVector3 _up, DXMatrix44 &_mtxOut)
{
	DXVector3 look = (_target - _pos);
	look.Normalize();
	_up.Normalize();
	
	DXVector3 right = look.Cross(_up);
	right.Normalize();
	_up = right.Cross(look);
	_up.Normalize();


	_mtxOut.SetRow(DXVector3(right),0);// set the first row
	_mtxOut.SetRow(DXVector3(_up),1);// set the second row
	_mtxOut.SetRow(-1.0f * look,2);// set the thrid row
	_mtxOut.SetRow(DXVector3(0.0f,0.0f,0.0f),3);
	_mtxOut.SetColumn(DXVector3(-1.0f * right.Dot(_pos),-1.0f * _up.Dot(_pos),look.Dot(_pos)),3);
	_mtxOut(3,3) = 1.0f;
	/*_mtxOut.SetColumns(DXVector4(right,0.0f),DXVector4(_up,0.0f),
		DXVector4(-1.0f * look,0.0f), DXVector4(-1.0f * right.Dot(_pos),-1.0f * _up.Dot(_pos),look.Dot(_pos),1.0f));*/
}

//----------------------------------------------------------------
// Name: 
// Desc: OpenGl perspective Projection
//----------------------------------------------------------------
void PerspectiveGL(float _fov,float _width, float _height, float _near, float _far, DXMatrix44& _mtxOut)
{
	// avoid divide by  zero
	if(DXMath::IsZero(_near))
		_near = 1.0f;

	float ar = _width / _height;// aspect ratio
	_fov = atanf(_fov / 2);
	float invNearMinusFar = 1.0f/ (_near - _far);
	memset(&_mtxOut,0,sizeof(DXMatrix44));
	_mtxOut.SetDiagonal(_fov / ar,_fov,(_near + _far) * invNearMinusFar,1.0f);
	_mtxOut(2,3) = (2 * _near * _far) * (invNearMinusFar);
	_mtxOut(3,2) = -1.0f;
}

void PerspectiveLH(float _fov, float _width, float _height,float _far, float _near, DXMatrix44& _mtxOut)
{
	// avoide divide by 0.
	if(DXMath::IsZero(_near))
		_near = 1.0f;
	float ar = _width / _height;
	_fov = atanf(_fov/2);
	float invFarMinusNear = 1.0f / (_far - _near);
	memset(&_mtxOut, 0, sizeof(DXMatrix44));
	_mtxOut.SetDiagonal(_fov/ar,_fov,_far* invFarMinusNear,1.0f);
	_mtxOut.SetColumn(DXVector4(0.0f,0.0f,-_far*invFarMinusNear * _near,0.0f),3);
}
}// end of DXTransform name space