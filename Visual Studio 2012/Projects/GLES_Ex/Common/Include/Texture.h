#ifndef TEXTURES_H
#define TEXTURES_H
#include <vector>
class CTextureManager
{
	public:
		CTextureManager();
		
		~CTextureManager(void);
		
		///<summary>Release all the resources owned by this object</summary>
		void Release();	
		
		///<summary>Get the textures</summary>
		///<return> return handle to the texture if its found else null.</return>
		GLint* GetTexture(int _texIndex)const;
		
	private:
		GLint m_texBaseFmt;
		std::vector<GLuint> m_texhandle;
};


#endif