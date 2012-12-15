//////////////////////////////////////////////////////////////////////////
// Author : Dhanus
// Created:
//////////////////////////////////////////////////////////////////////////
#include <cstdlib>
#include <string>
#include "esUtil.h"
#include "Shader.h"

typedef struct 
{
	GLuint programObject;
}UserData;

/*!***********************************************************************************************
 * @fn	int Init()
 *
 * @brief	Initialises the rendering states.
 *
 * @return	1(succeded) / 0 (failed).
 *************************************************************************************************/

int Init(ESContext* _esContext)
{
	if(!_esContext)return 0;
	UserData *pUsrData = (UserData*) _esContext->userData;
	if(!pUsrData)return 0;
	GLuint vtxShader(0), fragShader(0), shaderProgram(0);
	GLint linked(0);

	//load the shader from the file
	std::string vtxShaderSrc;
	// read the shader form the txt file
	if(!ReadShaderFromFileTxt("Data/Shader/tri.vert",vtxShaderSrc))
		return 0;
	vtxShader = CompileShader(GL_VERTEX_SHADER,vtxShaderSrc.c_str());
	if(!vtxShader)
		return false;
	
	std::string fragShaderSrc;
	if(!ReadShaderFromFileTxt("Data/Shader/tri.frag", fragShaderSrc))
		return false;
	fragShader = CompileShader(GL_FRAGMENT_SHADER, fragShaderSrc.c_str());
	if(!fragShader){
		CleanUp(0,&vtxShader,0);
		return false;
	}

	// create the program Object
	shaderProgram = glCreateProgram();
	if(!shaderProgram)// failed?
	{
		glDeleteShader(vtxShader);
		glDeleteShader(fragShader);
		return false;
	}
	glAttachShader(shaderProgram,vtxShader);
	glAttachShader(shaderProgram, fragShader);
	glBindAttribLocation(shaderProgram, 0, "vPosition");
	// link the shader
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram,GL_LINK_STATUS, &linked);
	if(!linked)
	{
		CleanUp(&shaderProgram, &vtxShader, &fragShader);
		return 0;
	}

	pUsrData->programObject = shaderProgram;

	return 1;
}

void Draw(ESContext *esContext)
{
	if(!esContext)return;// validate
	UserData *pUsrData = (UserData*)esContext->userData;
	if(!pUsrData)// validate
		return;
	 float vertices[] = {0.0f,0.5f,0.0f,
							   -0.5f,-0.5f,0.0f,
								0.5f,-0.5f,0.0f};
	glViewport(0,0,esContext->width, esContext->height);
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(pUsrData->programObject);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, 0, vertices);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

int main(int argc, char* argv[])
{
	ESContext esContext;
	UserData usrData;
	esInitContext(&esContext);
	esContext.userData = &usrData;
	esCreateWindow(&esContext, "GlES EXxample", 600,480, ES_WINDOW_RGB);
	if(!Init(&esContext))return 0;
	esRegisterDrawFunc(&esContext, Draw);
	esMainLoop(&esContext);
}


