#ifndef M3DMODEL_H
#define M3DMODEL_H
#include <string>
#include <winstring.h>
#include <fstream>
#include <vector>
#include "LightHelper.h"
#include "DXMeshData.h"
//enum ModelType{M3DModel};

class M3DModel
{
public:
	///-------------------------------------------------------------------------------------------------
	/// <summary> Load the given M3d format file </summary>
	///
	/// <param name="_filename ">  </param>
	///
	/// <returns> true if succedded, else failes</returns>
	///-------------------------------------------------------------------------------------------------
	bool LoadM3DModel(const std::string& _fileName, std::vector<float>& _vertices, std::size_t& _vSize, std::vector<unsigned short>& _index,
		unsigned short& _vtxOffset, unsigned short& _texOffset, unsigned short& _tanOffset, unsigned short& _normalOffset);


	///-------------------------------------------------------------------------------------------------
	/// <summary> release the loaded Geometry.</summary>
	///-------------------------------------------------------------------------------------------------
	void Release();
private:
	struct Subset
	{
		Subset() : id(-1), vertexStart(0), vertexCount(0), faceStart(0), faceCount(0){}
		unsigned int id;
		unsigned int vertexStart;
		unsigned int vertexCount;
		unsigned int faceStart;
		unsigned int faceCount;
	};

	//Helper Functions
	bool ProcessSubsetTable(std::ifstream& _fin, unsigned int _numSubsets, std::vector<Subset>& _subSet);
	bool ProcessVertices(std::ifstream& _fin, unsigned& _vertexCount, std::vector<float>& _vertex,
			unsigned short& _vOffset,unsigned short& _tanOffset, unsigned short& _texOffset,unsigned short& _nOffset);
	bool ProcessMaterials(std::ifstream& _fin, unsigned int _mateialsCount, std::vector<Material>& _mat);
	bool ProcessTriangles(std::ifstream& _fin, unsigned int _triCount, std::vector<unsigned short>&indices);
	
	bool ProcessSkinnedMeshData(std::ifstream& _fin, unsigned int _numVertices, 
		std::vector<MeshVertex::PosNormalTexTanSkinned>& _vertices);

	std::vector<MeshVertex::PosTanNormalTex> m_vertices;
	std::vector<Subset> m_subset;
	std::vector<unsigned short>m_indices;

};

#endif