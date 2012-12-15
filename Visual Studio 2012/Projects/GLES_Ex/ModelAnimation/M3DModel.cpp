#include <iostream>
#include "M3DModel.h"

bool M3DModel::LoadM3DModel(const std::string& _fileName, std::vector<float>& _vertices, std::size_t& _vSize, std::vector<unsigned short>& _index,
				  unsigned short& _vtxOffset, unsigned short& _texOffset, unsigned short& _tanOffset, unsigned short& _normalOffset)
{
	std::ifstream fIn;
	fIn.open(_fileName);
	if(!fIn.good()){
		std::cerr << "File Name " << _fileName << "doesnt exit" << std::endl;
		return false;
	}
	unsigned int numtriangles = 0, numVertices = 0, numMaterials = 0,numBones = 0, numAnimClip = 0;
	std::string ignore;
	fIn >> ignore >> ignore >>numMaterials >> ignore >> numVertices >> ignore >> numtriangles >> ignore >> numBones >> ignore >> numAnimClip;
	std::vector<Material> mat;
	ProcessMaterials(fIn,numMaterials,mat);
	std::vector<Subset> subset;
	ProcessSubsetTable(fIn,numMaterials,subset);
	ProcessVertices(fIn,numVertices,_vertices, _vtxOffset, _tanOffset, _texOffset, _normalOffset);
	
	
	ProcessTriangles(fIn,numtriangles,_index);
	//ProcessSubsetTable(fIn,numS);
	return true;
}

bool M3DModel::ProcessMaterials(std::ifstream& _fin, unsigned int _mateialsCount, std::vector<Material>& _mat)
{
	std::string ignore;
	_mat.resize(_mateialsCount);

	std::string diffMapName, normalMapName;
	_fin >> ignore;
	// process the materials
	for(unsigned i = 0; i < _mateialsCount; ++i)
	{
		_fin >> ignore >> _mat[i].ambient[0]>> _mat[i].ambient[1] >> _mat[i].ambient[2];
		_fin >> ignore >> _mat[i].diffuse[0]>> _mat[i].diffuse[1] >> _mat[i].diffuse[2];
		_fin >> ignore >> _mat[i].spec[0]>> _mat[i].spec[1] >> _mat[i].spec[2] >>ignore>> _mat[i].spec[3];
		_fin >> ignore >> _mat[i].reflect[0]>> _mat[i].reflect[1] >> _mat[i].reflect[2];
		_fin >> ignore >> _mat[i].alphaClip;
		_fin >> ignore >> _mat[i].fxTypeName;
		_fin >> ignore >> _mat[i].diffMapName;
		_fin >> ignore >> _mat[i].normalMapName;

	}// nxt materails
	return true;// success.
}

bool M3DModel::ProcessSubsetTable(std::ifstream& _fin, unsigned int _numSubsets, std::vector<Subset>& _subSet)
{
	std::string ignore;
	_subSet.resize(_numSubsets);
	_fin >> ignore;
	for(unsigned int  i = 0; i < _numSubsets; ++i)
	{
		_fin >> ignore >> _subSet[i].id;
		_fin >> ignore >> _subSet[i].vertexStart;
		_fin >> ignore >> _subSet[i].vertexCount;
		_fin >> ignore >> _subSet[i].faceStart;
		_fin >> ignore >> _subSet[i].faceCount;
	}// nxt subset
	return true;// success
}

void M3DModel::Release()
{
	m_vertices.clear();
	m_subset.clear();

	m_indices.clear();
}

bool M3DModel::ProcessVertices(std::ifstream& _fin, unsigned& _vertexCount, std::vector<float>& _vertex,
							   unsigned short& _vOffset,unsigned short& _tanOffset, unsigned short& _texOffset,unsigned short& _nOffset)
{
	std::string ignore;
	_vertex.resize(_vertexCount * 12);
	_vOffset = 0;
	_tanOffset = 3;
	_nOffset = _tanOffset + 4;
	_texOffset = _nOffset+3;
	_fin >> ignore;
	for(unsigned i = 0; i < _vertexCount;++i)
	{
		_fin >> ignore >> _vertex[i*12] >>_vertex[i*12+1] >> _vertex[i*12+2];
		_vertex[i*12+2]*=-1;
		_fin >> ignore >>_vertex[i*12+3] >> _vertex[i*12+4] >> _vertex[i*12+5] >> _vertex[i*12+6];
		_vertex[i*12+5] *=-1;
		_fin >> ignore >> _vertex[i*12+7] >> _vertex[i*12+8]>> _vertex[i*12+9];
		_vertex[i*12+9] *= -1;
		_fin >> ignore >>_vertex[i*12+10] >> _vertex[i*12+11];
		_fin >> ignore >>ignore >>ignore >>ignore >> ignore;
		_fin >> ignore >>ignore >>ignore >>ignore >> ignore;
	}// nxt vertex
	return true;
}

bool M3DModel::ProcessTriangles(std::ifstream& _fin, unsigned int _triCount, std::vector<unsigned short>& _indices)
{
	std::string ignore;
	_fin >> ignore;
	_indices.resize(_triCount*3);
	for(unsigned i = 0; i < _triCount; ++i)
	{
		_fin>>_indices[i*3 + 0];
		_fin >>_indices[i*3+2];
		_fin >> _indices[i*3+1];
	}// nxt indices
	return true;
}

bool M3DModel::ProcessSkinnedMeshData(std::ifstream& _fin, unsigned int _numVertices, std::vector<MeshVertex::PosNormalTexTanSkinned>& _vertices)
{
	std::string ignore;
	_vertices.resize(_numVertices);
	_fin >> ignore;
	int boneIndices[4];
	float weights[4];


	for(unsigned int i = 0; i < _numVertices;++i)
	{
		_fin >> ignore >> _vertices[i].pos.m_x >> _vertices[i].pos.m_y >> _vertices[i].pos.m_z;

	}// nxt vertices
}
