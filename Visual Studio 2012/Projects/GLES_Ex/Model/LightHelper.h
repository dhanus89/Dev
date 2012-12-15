#ifndef LIGHTHELPER_H
#define LIGHTHELPER_H
#include <string>
struct Material
{
	float ambient[3];
	float diffuse[3];
	float spec[4];// the fourth compoenent holds the spec power.
	float reflect[3];
	bool alphaClip;
	std::string fxTypeName;
	std::string diffMapName;
	std::string normalMapName;
};









#endif