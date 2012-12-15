// Author: Senthuran (aka: Dhanus)
// VertexShader
attribute vec4 vPosition;
attribute vec3 vNormal;
//attribute vec3 vTex;
uniform  mediump mat4 worldMtx;  // read from right to left
uniform  mediump mat4 viewMtx;
uniform  mediump mat4 projMtx;
uniform  vec3 lightDir;
varying  vec4 vColor;

//light helper function




varying vec2 v_texCoord;
void main()
{
	//v_texCoord = vTex; 
	gl_Position = projMtx * viewMtx * worldMtx * vPosition;
	vColor = dot(vNormal,vec3(0.0,0.5,-0.5)) * vec4(0.8,0.7,0.9,1.0) + vec4(0.3,0.3,0.3,0.6);
	vColor.r = clamp(vColor.r, 0.0,1.0);
	vColor.g = clamp(vColor.g, 0.0,1.0);
	vColor.b = clamp(vColor.b, 0.0,1.0);
	vColor.a = clamp(vColor.a, 0.0,1.0);

}

