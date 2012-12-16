#include "MathHelper.h"
float Vec3Dot( Vector3 _vec1,  Vector3 _vec2)
{
	return (_vec1.x * _vec2.x + _vec1.y * _vec2.y + _vec1.z * _vec2.z);
}
