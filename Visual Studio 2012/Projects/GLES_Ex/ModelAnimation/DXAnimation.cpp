#include "DXAnimation.h"

//	BoneAnimation Definition
float BoneAnimation::GetStartTime(void)const
{
	return keyFrames[0].timePos;
}

float BoneAnimation::GetEndTime(void)const
{
	return keyFrames[keyFrames.size()-1].timePos;
}

void BoneAnimation::Interpolate(float _t, DXMatrix44& _mtx)const
{
	if(_t <= GetStartTime())// before / begin frame
	{

		DXMatrix44AffineTransform(keyFrames.front().scale,
			keyFrames.front().rotate,keyFrames.front().pos, _mtx);
	}
	else if (_t >= GetEndTime())// last / past the last frame.
	{

		DXMatrix44AffineTransform(keyFrames.back().scale,
			keyFrames.back().rotate,keyFrames.back().pos, _mtx);
	}
	else// in between two frames
	{
		// find the approopriate start and end frame and then interpolate
		for(unsigned int kp = 0; kp < keyFrames.size()-1;++kp)
		{
			if(_t >= keyFrames[kp].timePos && _t <= keyFrames[kp+1].timePos)// if its valid bouding key frames
			{
				// linely interpolate
				float per = DXMath::LerpPercentage(_t, keyFrames[kp].timePos, keyFrames[kp+1].timePos);
				DXVector3 scale(LerpVec3(per, keyFrames[kp].scale, keyFrames[kp+1].scale));
				DXQuaternion rotate;
				DXQuaternionSlerp(rotate,keyFrames[kp].rotate, keyFrames[kp+1].rotate,per);
				DXVector3 pos(LerpVec3(per, keyFrames[kp].pos, keyFrames[kp+1].pos));
				DXMatrix44AffineTransform(scale,rotate,pos, _mtx);
			}// next pair
		}// next key frame
	}
}



//===============================================================
// SkinnedData Definition
//===============================================================
unsigned int SkinnedData::GetBoneCount(void)const
{
	return m_boneHierarchy.size();
}




