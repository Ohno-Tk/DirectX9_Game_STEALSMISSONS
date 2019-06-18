float4x4 mtxWVP; //  WorldViewProjectionMatrix
float4x4 mtxWIT; //  WorldInverse
float4x4 mtxW;
float4 Diffuse;// �f�B�t���[�Y��
float3 lightDirL;

struct IN_VERTEX
{ // ���͗p
    float3 posL:POSITION0;
	float2 uv:TEXCOORD0;
};

struct OUT_VERTEX
{ // �o�͗p
    float4 posH:POSITION0;
	float4 color:COLOR0;
	float2 uv:TEXCOORD0;
};

OUT_VERTEX main(IN_VERTEX inVertex)
{
    OUT_VERTEX outVertex = (OUT_VERTEX)0;

	// ���W�v�Z
	outVertex.posH = mul(float4(inVertex.posL, 1.0f),mtxWVP);
	
	// �e�N�X�`�����WUV
	outVertex.uv = inVertex.uv;
	
	float4 lightAmbient = float4(0.3f,0.3f,0.3f,1.0f);
	float4 lightDiffuse = float4(1.0f,1.0f,1.0f,1.0f);

	// �@���v�Z
//    float l = max(dot( inVertex.normalL, -lightDirL), 0.0f);
	outVertex.color = (float4((lightDiffuse).rgb ,1.0f) + lightAmbient) * Diffuse;
	
	// ���[���h���W�v�Z
//	outVertex.posW = mul(float4(inVertex.posL, 1.0f), mtxW);

	return outVertex;
}