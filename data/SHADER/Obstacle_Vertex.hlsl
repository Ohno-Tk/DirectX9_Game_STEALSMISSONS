float4x4 mtxWVP; //  WorldViewProjectionMatrix
float4x4 mtxWIT; //  WorldInverse
float4x4 mtxW;


struct IN_VERTEX
{ // ���͗p
    float3 posL:POSITION0;
	float3 normalL:NORMAL0;
	float2 uv:TEXCOORD0;
};

struct OUT_VERTEX
{ // �o�͗p
    float4 posH:POSITION0;
	float2 uv:TEXCOORD0;
	float3 normalW:TEXCOORD1;
};

OUT_VERTEX main(IN_VERTEX inVertex)
{
    OUT_VERTEX outVertex = (OUT_VERTEX)0;

	// ���W�v�Z
	outVertex.posH = mul(float4(inVertex.posL, 1.0f),mtxWVP);
	
	// �e�N�X�`�����WUV
	outVertex.uv = inVertex.uv;
	
	// �@���v�Z
	outVertex.normalW = normalize(mul(float4(inVertex.normalL, 0.0f), mtxWIT).xyz);

	return outVertex;
}