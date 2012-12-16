#ifndef MATHHELPER_H
#define MATHHELPER_H

typedef struct _Vector3
{
	float x,y,z;
}Vector3;



extern float Vec3Dot(struct _Vector3 _vec1,struct _Vector3 _vec2);

#endif