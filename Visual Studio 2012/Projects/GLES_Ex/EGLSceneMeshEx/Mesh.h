#ifndef MESH_H
#define MESH_H
#include <vector>
#include <string>
#include "DXVector.h"
#include <EGL/egl.h>
#include <GLES2/gl2.h>
class CMesh
{
public:
	CMesh();
	~CMesh();
	void Release(void);
	void AddVertex(const DXVector3& _vec3, const DXVector3& _normal);
	void Addindex(const int _i);
	std::vector<float>& GetVertexSysMem();
	std::vector<GLushort>& GetIndexSysMem();
	bool BuildMeshVBO(bool _releaseOriginal = true);
	void ReserveVertex();
	void ReserveIndex();
	bool LoadMshFromTxtFile(const std::string& _fileName);
	unsigned GetVertexCount()const {return m_vertexCount;}
	unsigned GetIndexCount()const {return m_indexCount;}
private:
	// hiden interface
	CMesh(const CMesh& _cMesh);
	CMesh& operator=(const CMesh& _cMesh);

	// private Helper functions
	void ReleaseSysMem(void);


	// sys mem
	std::vector<float>m_vertex;
	std::vector<GLushort> m_index;

	unsigned int m_vertexCount, m_indexCount;
	GLuint m_vboHandle;
};

#endif