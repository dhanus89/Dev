uniform mediump mat4 gBoneTrans[96];
 
 struct SkinnedVtxIn
 {
	attribute vec2 tex;
	attribute vec3 posL; // position
	attribute vec3 normalL;
	attribute vec3 weights;
	attribute vec4 tangent;
	attribute int boneIndices[4];
 };

 void main(SkinnedVtxIn _sVin)
 {

	float weights[4] = {0.0,0.0,0.0,0.0};
	weights[0] = _sVin.weights.x;
	weights[1] = _sVin.weights.y;
	weights[2] = _sVin.weights.z;
	weights[3] = 1.0 - weights[0] + weights[1] + weights[2];

	//	Vertex Blending
	mediump vec3 posL;
	mediump vec3 normalL;
	mediump vec3 tangentL;

	for(int i = 0; i < 4; ++i)
	{
		posL += (weights[i] * gBoneTrans[_sVin.boneIndices[i]] * vec4(_sVin.posL,1.0)).xyz;

		// transform the normal and the tangent (NOTE: we assume the matrix 
		// does not contain non-uniform scale).
		normalL += (weights[i] * (float3x3)gBoneTrans[_sVin.boneIndices[i]] * _sVin.normalL);
		tangentL += (weights[i] * (float3x3)gBoneTrans[_sVin.boneIndices[i]] * _sVin.tangent);
	}

	// transform  to world space.

 }
