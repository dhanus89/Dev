// Author: Senthuran (aka: Dhanus)
// VertexShader

attribute vec4 vPosition;
attribute vec2 vTex;
uniform  mediump mat4 worldMtx;  // read from right to left
uniform  mediump mat4 viewMtx;
uniform  mediump mat4 projMtx;
varying vec2 v_texCoord;
void main()
{
	int i = 0;
	projMtx[i];
	v_texCoord = vTex; 
	gl_Position = projMtx * viewMtx * worldMtx * vPosition;
}

