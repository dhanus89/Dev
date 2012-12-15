#include "Texture.h"
#include <EGL/egl.h>
#include <GLES2/gl2.h>
CTextureManager::CTextureManager()
{

}

CTextureManager::~CTextureManager()
{
	Release();
}

void CTextureManager::Release()
{
	for(size_t i = 0; i < m_texhandle.size(); ++i)
	{
		glDeleteTexture(m_texhandle[i]);
	}
	m_texhandle.clear();
}


