#include <fstream>
#include "Mesh.h"

CMesh::CMesh() : m_vertexCount(0), m_indexCount(0), m_vboHandle(0)
{

}

CMesh::~CMesh()
{
	Release();
}

void CMesh::Release()
{
	m_vboHandle = m_indexCount = m_vertexCount = 0;
	m_vertex.clear();
	m_index.clear();
}

void CMesh::AddVertex(const DXVector3& _vec3, const DXVector3& _normal)
{
	m_vertex.push_back(_vec3.m_x);
	m_vertex.push_back(_vec3.m_y);
	m_vertex.push_back(_vec3.m_z);

	m_vertex.push_back(_normal.m_x);
	m_vertex.push_back(_normal.m_y);
	m_vertex.push_back(_normal.m_z);
	m_vertexCount++;
}

void CMesh::Addindex(const int _i)
{
	m_index.push_back(_i);
	m_indexCount++;
}

bool CMesh::BuildMeshVBO(bool _releaseOriginal /* = true */)
{

	if(_releaseOriginal)
		ReleaseSysMem();
	return true;
}

void CMesh::ReleaseSysMem(void)
{
	m_index.clear();
	m_vertex.clear();
	// NOTE, note clear the vertex and index count for rnedering purpose.
}

std::vector<float>& CMesh::GetVertexSysMem()
{
	return m_vertex;
}

std::vector<GLushort>& CMesh::GetIndexSysMem()
{
	return m_index;
}

bool CMesh::LoadMshFromTxtFile(const std::string& _fileName)
{
	std::ifstream fIn(_fileName);
	if(!fIn.good())return false;
	m_vertexCount  = 0;
	m_indexCount = 0;
	std::string ignore;
	fIn>>ignore>>m_vertexCount;
	fIn>>ignore >> m_indexCount;

	fIn >> ignore>>ignore>>ignore>>ignore;
	unsigned int i = 0;
	float tmpData;
	for(unsigned int offset = 0; i < m_vertexCount; ++i)
	{
		fIn >> tmpData;
		m_vertex.push_back(tmpData);

		fIn >> tmpData;
		m_vertex.push_back(tmpData);

		fIn >> tmpData;
		m_vertex.push_back(-tmpData);

		fIn >> tmpData;
		m_vertex.push_back(tmpData);

		fIn >> tmpData;
		m_vertex.push_back(tmpData);

		fIn >> tmpData;
		m_vertex.push_back(-tmpData);
	
	}

	// retirve the index
	fIn >> ignore >> ignore >> ignore;
	float swap;
	for(i = 0; i < m_indexCount; ++i)
	{
		fIn >> tmpData;
		m_index.push_back(tmpData);

		fIn >> tmpData;
		fIn >> swap;
		m_index.push_back(swap);
		m_index.push_back(tmpData);
	}
	m_indexCount *= 3;
	fIn.close();
	return true;
}