#ifndef SHADER_H
#define SHADER_H
#include <stdlib.h>
#include <string>
#include <fstream>
#include "esUtil.h"

/*!***********************************************************************************************
 * @fn	int ReadShaderFromFileTxt(const std::string& _filename, const std::string& _outSource);
 *
 * @brief	Reads shader from txt file.
 *
 * @param	_filename 	Filename of the file.
 * @param	_outSource	The shader.
 *
 * @return	0 if failed, 1 success.
 *************************************************************************************************/
int ReadShaderFromFileTxt(const std::string& _filename, std::string& _outSource);



/*!***********************************************************************************************
 * @fn	GLuint CompileShader(GLenum _type, const char* _shaderSrc)
 *
 * @brief	compile the given shader in to GL.
 *
 * @param	_type	  	The type.
 * @param	_shaderSrc	The shader source.
 *
 * @return	The shader handle.
 *************************************************************************************************/
GLuint CompileShader(GLenum _type, const char* _shaderSrc);

/*!***********************************************************************************************
 * @fn	void OutputShaderErrLog(GLuint &_shaderId);
 *
 * @brief	Output shader log, if the comilation failed.
 *
 * @param [in]	_shaderId	Identifier for the shader.
 *************************************************************************************************/

/*!***********************************************************************************************
 * @fn	void CleanUp(GLuint &_shaderProgram, GLuint& _vtxShader, GLuint& _fragShader);
 *
 * @brief	detach and delete the shader
 *
 * @param [in,out]	_shaderProgram	The shader program, set it to 0.
 * @param [in,out]	_vtxShader	  	The vertex shader, set it to 0.
 * @param [in,out]	_fragShader   	The fragment shader, set it to 0.
 *************************************************************************************************/
void CleanUp(GLuint *_shaderProgram, GLuint* _vtxShader, GLuint* _fragShader);


#endif