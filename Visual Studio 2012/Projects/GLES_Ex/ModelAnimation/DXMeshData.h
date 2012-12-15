#ifndef DXMESHDATA_H
#define DXMESHDATA_H
#include "DXVector.h"

namespace MeshVertex
{
	struct PosTanNormalTex
	{
		float pos[3];
		float tangent[4];
		float normal[3];
		float tex[2];
	};

	struct PosNormalTexTanSkinned
	{
		DXVector2 tex;
		DXVector3 pos,normal,weights;
		DXVector4 tangentU;
		unsigned char boneIndex[4];
	};
}



#endif