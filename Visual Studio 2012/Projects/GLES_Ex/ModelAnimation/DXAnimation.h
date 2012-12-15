#ifndef DXANIMATION_H
#define DXANIMATION_H
#include <vector>
#include <map>
#include <string>
#include "DXMath.h"
#include "DXMatrix.h"


struct KeyFrame
{
	float timePos;
	DXVector3 scale,pos;
	DXQuaternion rotate;
};

///-------------------------------------------------------------------------------------------------
/// <summary> containes all the key frame data for specific bone in the ascending order of the
///			  key frame time
/// </summary>
///-------------------------------------------------------------------------------------------------
struct BoneAnimation
{
	inline float GetStartTime(void)const;
	inline float GetEndTime(void)const;
	void Interpolate(float _t, DXMatrix44& _mtx)const;
	std::vector<KeyFrame>keyFrames;
};



///-------------------------------------------------------------------------------------------------
/// <summary> DXAnimationClip </summary>
///
///-------------------------------------------------------------------------------------------------
class DXAnimationClip
{
public:
	float GetClipEndTime(void)const;
	float GetClipStartTime(void)const;
	void Interpolate(float _t, std::vector<DXMatrix44>& boneTransform)const;
private:
	std::vector<BoneAnimation> m_boneAnimation;
};



class SkinnedData
{
public:
	unsigned int GetBoneCount()const;
	float GetClipStartTime(void)const;
	float GetClipEndTime(void)const;
	unsigned int GetAnimationCount(void)const;
private:
	std::map<std::string, DXAnimationClip> m_animation;
	std::vector<DXMatrix44> m_boneOffsets;
	std::vector<int> m_boneHierarchy;
};

#endif // !ANIMATION_H
