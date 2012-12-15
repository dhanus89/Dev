#ifndef DXTRANSFORM_H
#define DXTRANSFORM_H
#include "DXMatrix.h"
#include "DXMath.h"
#include "DXVector.h"
#include "DXTransform.h"
#include <math.h>

namespace DXTransform{

	void ComputeNormal(const DXVector3& _p0, const DXVector3& _p1,
		const DXVector3& _p2, DXVector3& _out);

#pragma region Documentation
	/// <summary>Look at rh.</summary>
	///
	/// <param name="_pos">   The position. </param>
	/// <param name="_target">Target for the. </param>
	/// <param name="_up">	  The up. </param>
	/// <param name="_mtxOut">[in,out] The mtx out. </param>
#pragma endregion
	void LookAtRH(const DXVector3 &_pos, const DXVector3 &_target, DXVector3 _up, DXMatrix44 &_mtxOut);

	/// <summary>Opengl Perspective .</summary>
	///
	/// <param name="_fov">   The fov. </param>
	/// <param name="_width"> The width. </param>
	/// <param name="_height">The height. </param>
	/// <param name="_near">  The near. </param>
	/// <param name="_far">   The far. </param>
	/// <param name="_mtxOut">[in,out] The mtx out. </param>
	void PerspectiveGL(float _fov,float _width, float _height, float _near, float _far, DXMatrix44& _mtxOut);

	void PerspectiveLH(float _fov, float _width, float _height,float _far, float _near, DXMatrix44& _mtxOut);


	

}// end of name space DXTransform


#endif