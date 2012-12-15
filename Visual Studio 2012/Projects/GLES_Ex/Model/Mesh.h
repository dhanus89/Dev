#ifndef MESH_H
#define MESH_H
#include <vector>
#include <string>

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include "DXVector.h"
#include "M3DModel.h"
#include "LightHelper.h"
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
	bool LoadM3DModel(const std::string& _fileName);
	unsigned short GetVertexOffset()const{return m_vOffset;}
	unsigned short GetTexOffset()const{return m_texOffset;}
	unsigned short GetTanOffset()const{return m_tanOffset;}
	unsigned short GetNormalOffset()const{return m_normalOffset;}
private:
	// hiden interface
	CMesh(const CMesh& _cMesh);
	CMesh& operator=(const CMesh& _cMesh);

	// private Helper functions
	void ReleaseSysMem(void);


	// sys mem
	std::vector<float>m_vertex;
	std::size_t m_modelType;
	std::vector<GLushort> m_index;
	std::vector<Material>m_mat;
	std::size_t m_vStride;
	unsigned short m_vOffset, m_texOffset, m_tanOffset,m_normalOffset; 
	unsigned int m_vertexCount, m_indexCount;
	GLuint m_vboHandle;
};

#endif