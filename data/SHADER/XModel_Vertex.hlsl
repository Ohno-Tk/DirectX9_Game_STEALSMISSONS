float4x4 mtxWVP; //  WorldViewProjectionMatrix
float4x4 mtxWIT; //  WorldInverse
float4x4 mtxW;

struct IN_VERTEX
{ // 入力用
    float3 posL:POSITION0;
	float3 normalL:NORMAL0;
	float2 uv:TEXCOORD0;
};

struct OUT_VERTEX
{ // 出力用
    float4 posH:POSITION0;
	float2 uv:TEXCOORD0;
	float3 normalW:TEXCOORD1;
	float3 posW:TEXCOORD2;
};

OUT_VERTEX main(IN_VERTEX inVertex)
{
    OUT_VERTEX outVertex = (OUT_VERTEX)0;

	// 座標計算
	outVertex.posH = mul(float4(inVertex.posL, 1.0f),mtxWVP);
	
	// テクスチャ座標UV
	outVertex.uv = inVertex.uv;
	
	float4 lightAmbient = float4(0.3f,0.3f,0.3f,1.0f);
	float4 lightDiffuse = float4(0.2f,0.2f,0.2f,1.0f);

	// 法線計算
	outVertex.normalW = normalize(mul(float4(inVertex.normalL, 0.0f), mtxWIT).xyz);
	
	// ワールド座標計算
	outVertex.posW = mul(float4(inVertex.posL, 1.0f), mtxW);

	return outVertex;
}