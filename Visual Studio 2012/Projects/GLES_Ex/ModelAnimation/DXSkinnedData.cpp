#include "DXSkinnedData.h"
#include "DXMeshData.h"

///--------		DXSkinnedData Definition   ---------------

void DXSkinnedData::GetFinalTransform(const std::string& _clipName,float _timePos, std::vector<DXMatrix44&> _finalTransform)const
{
	const size_t numBones = m_boneOffsetList.size();
	if(numBones <= 0) return;
	std::map<std::string, DXAnimationClip>::const_iterator animClip = m_animClipList.find(_clipName);
	std::vector<DXMatrix44> toparentTransform(numBones);
	(*animClip).second.Interpolate(_timePos,toparentTransform);
	_finalTransform.resize(numBones);
	// transform all the bones to the root space..
	std::vector<DXMatrix44> toRootTrans(numBones);
	toRootTrans[0]=toparentTransform[0];
	unsigned int i = 0;
	for(; i < numBones;++i)
	{
		DXMatrix44 toParent = toRootTrans[i];
		int parentIndex = m_boneHierarchyList[i];
		DXMatrix44 parentToRoot = toRootTrans[parentIndex];
		toRootTrans[i] = toParent * parentToRoot;
	}// nxt bones
	for(i = 0; i < numBones;++i )
	{
		_finalTransform[i] = m_boneOffsetList[i] * toRootTrans[i];
	}
}





