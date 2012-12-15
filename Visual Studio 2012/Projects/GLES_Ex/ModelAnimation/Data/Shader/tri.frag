precision mediump float;
varying vec2 v_texCoord;
uniform sampler2D s_tex;
varying  vec4 vColor;
void main()
{

	gl_FragColor = vColor * texture2D(s_tex, v_texCoord) * vec4(2.0,2.0,1.8,1.8);
}