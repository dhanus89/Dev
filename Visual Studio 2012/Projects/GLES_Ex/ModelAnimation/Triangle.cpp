#include <string>
#include <windows.h>
#include "Window.h"
#include "Shader.h"
#include "DXVector.h"
#include "DXMatrix.h"
#include "DXMathhelper.h"
#include "DXAnimation.h"
#include "Texture.h"
#include "DXQuaternion.h"
#include "Targa.h"
#include "Mesh.h"
#include "DXTimer.h"
int WINAPI WinMain(HINSTANCE hInstance,   HINSTANCE hPrevInstance,   LPSTR cmdLine,  int cmdShow)

{
	Window wnd(hInstance);
	if(!wnd.InitWindow(800, 600))return 0;
	DXTimer timer;
	timer.Start();

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

	CMesh mesh;
	if(!mesh.LoadM3DModel("Data/Models/soldier.m3d"))
		return 0;
	//if(!mesh.LoadMshFromTxtFile("Data/Models/skull2.txt"))
	//	return 0;
	//mesh.BuildMeshVBO(true);
	DXMatrix44 viewMtx;
	DXMath::LookAtRH(DXVector3(0.0f,0.0f,5.0f),DXVector3(0.0f,0.0f,0.0f),DXVector3(0.0f,1.0f,0.0f), viewMtx);
	DXMatrix44 projMtx = DXMatrix44::Identity;
	DXMath::PerspectiveGL(60.0f,800.0f,600.0f,0.01f,1000.0f, projMtx);
	glClearColor(0.0f,0.0f,0.0f,0.0f);

	GLint uniformLoc;
	
	uniformLoc = glGetUniformLocation(shaderProg, "viewMtx");
	glUniformMatrix4fv(uniformLoc,1,GL_FALSE, reinterpret_cast<float*>(&viewMtx(0,0)));

	uniformLoc = glGetUniformLocation(shaderProg, "projMtx");
	glUniformMatrix4fv(uniformLoc,1,GL_FALSE, reinterpret_cast<float*>(&projMtx(0,0)));

	uniformLoc = glGetUniformLocation(shaderProg, "lightDir");
	glUniform3f(uniformLoc,0.0f,-1.0f,0.5f);

	/********************************************************
	Load the texture
	*********************************************************/
	GLuint textureId;
	glGenTextures(1,&textureId);
	//GLubyte pxl[4 * 3] = { 255 ,0   ,0,
	//					   0   ,255 ,0,
	//					   0   ,0   ,255,
	//					   255 ,255 ,0};

	TargaImg img;

	if(!img.LoadImg("Data/grass.tga"))return 0;
	const unsigned char *pxl = &(img.GetImageData()[0]);
	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,img.GetWidth(),img.GetHeight(),0,GL_RGB,GL_UNSIGNED_BYTE,pxl);

	//set the min and mag filter.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,textureId);
	GLuint texLoc = glGetAttribLocation(shaderProg, "vTex");
	GLuint posLoc = glGetAttribLocation(shaderProg, "vPosition");
	GLuint samplerLoc = glGetUniformLocation(shaderProg, "s_tex");

	GLuint normalLoc = glGetAttribLocation(shaderProg, "vNormal");
	glUniform1i(samplerLoc,0);//set the texture sample to the bounded texture (0)
	glVertexAttribPointer(posLoc,3,GL_FLOAT,GL_FALSE,12* sizeof(float), &mesh.GetVertexSysMem()[0]);
	glVertexAttribPointer(normalLoc, 3,GL_FLOAT, GL_FALSE, 12 * sizeof(float),&mesh.GetVertexSysMem()[mesh.GetNormalOffset()]);
	glVertexAttribPointer(texLoc,2,GL_FLOAT, GL_TRUE, 12 * sizeof(float),&mesh.GetVertexSysMem()[mesh.GetTexOffset()]);
	glEnableVertexAttribArray(posLoc);
	glEnableVertexAttribArray(normalLoc);

	uniformLoc = glGetUniformLocation(shaderProg, "worldMtx");
	float rotate = DXMath::DegreeToRadian(180.0f);

	

	// Animation Specfifics
	DXQuaternion q0(DXQuaternion::Identity);
	DXQuaternion q1(DXMath::DegreeToRadian(180.0f), DXVector3(0.0f,2.0f,0.0f));
	DXQuaternion q2(DXMath::DegreeToRadian(0.0f), DXVector3(0.0f,0.0f,0.0f));
	DXQuaternion q3(DXMath::DegreeToRadian(0.0f), DXVector3(0.0f,0.0f,0.0f));

	BoneAnimation bAnim;
	bAnim.keyFrames.resize(5);
	bAnim.keyFrames[0].timePos = 0.0f;
	bAnim.keyFrames[0].pos = DXVector3(0.0f,-5.0f,-5.0f);
	bAnim.keyFrames[0].scale = DXVector3(0.05f,0.05f,0.05f);
	bAnim.keyFrames[0].rotate = q0;

	bAnim.keyFrames[1].timePos = 0.30f;
	bAnim.keyFrames[1].pos = DXVector3(0.0f,-5.0f,-5.0f);
	bAnim.keyFrames[1].scale = DXVector3(0.05f,0.05f,0.05f);
	bAnim.keyFrames[1].rotate = q1;

	bAnim.keyFrames[2].timePos = 1.0f;
	bAnim.keyFrames[2].pos = DXVector3(0.0f,-5.0f,-5.0f);
	bAnim.keyFrames[2].scale = DXVector3(0.05f,0.05f,0.05f);
	bAnim.keyFrames[2].rotate = q2;

	bAnim.keyFrames[3].timePos = 1.30f;
	bAnim.keyFrames[3].pos = DXVector3(0.0f,-5.0f,-5.0f);
	bAnim.keyFrames[3].scale = DXVector3(0.05f,0.05f,0.05f);
	bAnim.keyFrames[3].rotate = q3;

	bAnim.keyFrames[4].timePos = 2.0f;
	bAnim.keyFrames[4].pos = DXVector3(0.0f,-5.0f,-5.0f);
	bAnim.keyFrames[4].scale = DXVector3(0.05f,0.05f,0.05f);
	bAnim.keyFrames[4].rotate = q0;

	DXMatrix44 worldMtx;
	//DXMatrix44RotationY(worldMtx, rotate);

	worldMtx.SetTranslation(0.0f,-20.0f,-5.0f);
	worldMtx.SetDiagonal(1.0f,1.0f,1.0f);
	DXMatrix44 scale;
	DXMatrix44 rotateMtx = DXMatrix44::Identity;
	scale.SetDiagonal(0.06f,0.06f,0.06f,1.0f);
	glViewport(0,0,800,600);
	//worldMtx = scale  * worldMtx;
	//rotateMtx.RotateY(rotate);
	//worldMtx = rotateMtx * worldMtx ;
	float timeAnimPos(0.0f);
	//worldMtx.ToIdentity();
	while(wnd.IsRunning())
	{
		wnd.ProcessMsg();
		rotate = DXMath::DegreeToRadian(180.0f);
		timer.Tick();
		// do the rendering here.
		timeAnimPos+= timer.GetDeltaTime();
		if(timeAnimPos >=bAnim.GetEndTime())
			timeAnimPos = 0.0f;
		bAnim.Interpolate(timeAnimPos,worldMtx);
		//DXMatrix44AffineTransform(bAnim.keyFrames.back().scale,
			//bAnim.keyFrames.back().rotate,bAnim.keyFrames.back().pos, worldMtx);

		if(rotate > DXMath::DegreeToRadian(360.0f))
			rotate -= DXMath::DegreeToRadian(360.0f);
		if(rotate < DXMath::DegreeToRadian(-360.0f))
			rotate += DXMath::DegreeToRadian(360.0f);
	//	rotateMtx.RotateY(rotate);
//		worldMtx =  worldMtx * rotateMtx;
		glUniformMatrix4fv(uniformLoc,1,GL_FALSE, reinterpret_cast<float*>(&worldMtx(0,0)));

		glClear(GL_COLOR_BUFFER_BIT);
		
		glDrawElements(GL_TRIANGLES, mesh.GetIndexCount(), GL_UNSIGNED_SHORT, &mesh.GetIndexSysMem()[0]);
		eglSwapBuffers(*wnd.GetEGLDisplay(), *wnd.GetEGLSurface());
	}
	glDeleteTextures(1, &textureId);
	glDeleteProgram(shaderProg);
}