#ifndef DXSKINNEDDATA_H
#define DXSKINNEDDATA_H
#include <vector>
#include <map>
#include <string>
#include "DXMatrix.h"
#include "DXAnimation.h"
///-------------------------------------------------------------------------------------------------
/// <summary> DXSkinnedData </summary>
///-------------------------------------------------------------------------------------------------
class DXSkinnedData
{
public:

	unsigned int GetBoneCount(void)const;
	///-------------------------------------------------------------------------------------------------
	/// <summary> Get Clip Start time</summary>
	///
	/// <param name=" clipName"> name of clip </param>
	///
	/// <returns> return the clip Start time, else return -1.0f if
	///			  clip not exit
	/// </returns>
	///-------------------------------------------------------------------------------------------------
	float GetClipStartStime(const std::string& _clipName)const;

	///-------------------------------------------------------------------------------------------------
	/// <summary> Get Clip End time</summary>
	///
	/// <param name=" clipName"> name of clip </param>
	///
	/// <returns> return the clip End time, else return -1.0f if
	///			  clip not exit
	/// </returns>
	///-------------------------------------------------------------------------------------------------
	float GetClipEndTime(const std::string& _clipName)const;
///-------------------------------------------------------------------------------------------------
/// <summary> 
///			Set the Given list of animations
/// </summary>
///
/// <param name=" ">      </param>
///-------------------------------------------------------------------------------------------------
	void Set(const std::vector<unsigned int>& _boneHierarchy, std::vector<DXMatrix44>& _boneOffsets,
		std::map<std::string, DXAnimationClip>& _animClips);

	///-------------------------------------------------------------------------------------------------
	/// <summary> Get the final transform </summary>
	/// <param name=" "> </param>
	/// <returns> </returns>
	///-------------------------------------------------------------------------------------------------
	void GetFinalTransform(const std::string& _clipName,float _timePos,
		std::vector<DXMatrix44&> _finalTransform)const;
private:
	std::vector<DXMatrix44> m_boneOffsetList;
	std::vector<unsigned int>m_boneHierarchyList;
	std::map<std::string,DXAnimationClip> m_animClipList;
};

#endif