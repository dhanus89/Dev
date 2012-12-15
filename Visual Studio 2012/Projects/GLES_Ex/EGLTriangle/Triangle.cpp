#include <string>
#include <windows.h>
#include "Window.h"
#include "Shader.h"
#include "DXVector.h"
#include "DXMatrix.h"
#include "DXTransform.h"
#include "Texture.h"

int WINAPI WinMain(HINSTANCE hInstance,   HINSTANCE hPrevInstance,   LPSTR cmdLine,  int cmdShow)

{
	Window wnd(hInstance);
	if(!wnd.InitWindow(800, 480))return 0;


	/*****************************************************************
	Load The shader
	******************************************************************/
	std::string shaderSrc;
	if(!ReadShaderFromFileTxt("Data/Shader/tri.vert",shaderSrc))return 0;
	GLint vtxShaderObj = CompileShader(GL_VERTEX_SHADER, shaderSrc.c_str());
	if(!vtxShaderObj)return 0;
	
	shaderSrc.clear();
	if(!ReadShaderFromFileTxt("Data/Shader/tri.frag", shaderSrc))return 0;
	GLint fragShaderObj = CompileShader(GL_FRAGMENT_SHADER, shaderSrc.c_str());
	if(!fragShaderObj){glDeleteShader(vtxShaderObj);return 0;}

	GLint shaderProg = glCreateProgram();
	if(!shaderProg)
	{
		glDeleteShader(vtxShaderObj);
		glDeleteShader(fragShaderObj);
		return 0;
	}
	glAttachShader(shaderProg, vtxShaderObj);
	glAttachShader(shaderProg, fragShaderObj);
	glLinkProgram(shaderProg);
	glUseProgram(shaderProg);
	// dont need the shader aany more
	glDeleteShader(fragShaderObj);
	glDeleteShader(vtxShaderObj);

	// create the vertices////   {CCW}
	float vertices[15] = {-2.0f,-2.0f,0.0f,0.0f,0.0f,
						  2.0f,-2.0f,0.0f,1.0f,0.0f,
						  0.0f,2.0f,0.0f,0.5f,1.0f};
	GLushort indices[3] = {0,1,2};
	DXMatrix44 worldMtx = DXMatrix44::Identity;
	DXMatrix44 viewMtx;
	DXTransform::LookAtRH(DXVector3(0.0f,0.0f,5.0f),DXVector3(0.0f,0.0f,0.0f),DXVector3(0.0f,1.0f,0.0f), viewMtx);
	DXMatrix44 projMtx = DXMatrix44::Identity;
	DXTransform::PerspectiveGL(60.0f,800.0f,480.0f,0.01f,100.0f, projMtx);
	glClearColor(0.0f,0.0f,0.0f,0.0f);

	GLint uniformLoc = glGetUniformLocation(shaderProg, "worldMtx");
	glUniformMatrix4fv(uniformLoc,1,GL_FALSE, reinterpret_cast<float*>(&worldMtx(0,0)));
	
	uniformLoc = glGetUniformLocation(shaderProg, "viewMtx");
	glUniformMatrix4fv(uniformLoc,1,GL_FALSE, reinterpret_cast<float*>(&viewMtx(0,0)));

	uniformLoc = glGetUniformLocation(shaderProg, "projMtx");
	glUniformMatrix4fv(uniformLoc,1,GL_FALSE, reinterpret_cast<float*>(&projMtx(0,0)));

	/********************************************************
	Load and set up the texture
	*********************************************************/
	GLuint textureId;
	GLubyte pxl[4 * 3] = { 255 ,0   ,0,
						   0   ,255 ,0,
						   0   ,0   ,255,
						   255 ,255 ,0};


	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,2,2,0,GL_RGB,GL_UNSIGNED_BYTE,pxl);

	//set the min and mag filter.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D,textureId);
	GLuint texLoc = glGetAttribLocation(shaderProg, "vTex");
	GLuint posLoc = glGetAttribLocation(shaderProg, "vPosition");
	GLuint samplerLoc = glGetUniformLocation(shaderProg, "s_tex");
	glUniform1i(samplerLoc,0);
	
	glVertexAttribPointer(posLoc,3,GL_FLOAT,GL_FALSE, 3 * sizeof(GLfloat), vertices);
	glVertexAttribPointer(texLoc, 2,GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),&vertices[3]);
	glEnableVertexAttribArray(posLoc);
	glEnableVertexAttribArray(texLoc);

	while(wnd.IsRunning())
	{
		wnd.ProcessMsg();
		// do the rendering here..
		glViewport(0,0,800,480);
		
		glClear(GL_COLOR_BUFFER_BIT);
		
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, indices);
		eglSwapBuffers(*wnd.GetEGLDisplay(), *wnd.GetEGLSurface());
	}
	glDeleteTextures(1, &textureId);
	glDeleteProgram(shaderProg);
}