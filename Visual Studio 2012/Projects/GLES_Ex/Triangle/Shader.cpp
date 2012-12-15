#include "Shader.h"

GLuint CompileShader(GLenum _type, const char* _shaderSrc){
	GLuint shader;
	GLint compStatus;
	shader = glCreateShader(_type);
	if(!shader)return 0;// validate shader creation.
	glShaderSource(shader, 1, &_shaderSrc, NULL);// load the shader to GL
	glCompileShader(shader);// compile the shader
	// validate the shader has been compiled succesfully
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compStatus);
	if(!compStatus)
	{
		// out put to log file.
		GLint logLen(0);
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLen);
		if(logLen > 1)// validate the log file to be written
		{
			char* log = (char*)malloc(sizeof(char)*logLen);
			glGetShaderInfoLog(shader, logLen,NULL, log);
			esLogMessage("Error Copilining Shader:\n%s\n", log);
			free(log);
		}
		glDeleteShader(shader);
		return 0;
	}
	return shader;
}

int ReadShaderFromFileTxt(const std::string& _filename,std::string& _outSource)
{
	std::ifstream fIn(_filename);
	// validate file opened
	if(!fIn.good())return 0;//failed

	// read the file
	_outSource.assign(std::istreambuf_iterator<char>(fIn),std::istreambuf_iterator<char>());
	fIn.close();
	return 1;// success
}


void CleanUp(GLuint *_shaderProgram, GLuint* _vtxShader, GLuint* _fragShader)
{
	if(_shaderProgram)
	{
		if(_vtxShader)
			glDetachShader(*_shaderProgram, *_vtxShader);
		if(_fragShader)
			glDetachShader(*_shaderProgram, *_fragShader);
		glDeleteShader(*_shaderProgram);
		*_shaderProgram = 0;
	}
	if(_vtxShader)
	{
		glDeleteShader(*_vtxShader);
		*_vtxShader = 0;
	}
	if(_fragShader)
	{
		glDeleteShader(*_fragShader);
		*_fragShader = 0;
	}
}