/*-----------------------------------------------------------------------------
Macro
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
Struct
-----------------------------------------------------------------------------*/
struct IN_VERTEX
{ // 出力用
    float4 posH:POSITION0;
	float2 uv:TEXCOORD0;
	float3 normalW:TEXCOORD1;
};

/*-----------------------------------------------------------------------------
Global
-----------------------------------------------------------------------------*/
sampler sampler0;
float4 Diffuse;// ディフューズ光
float3 lightDirW;


float4 main(IN_VERTEX invertex):COLOR0
{
	float4 lightAmbient = float4(0.3f,0.3f,0.3f,1.0f);
	float4 lightDiffuse = float4(0.2f,0.2f,0.2f,1.0f);

	float l = max(dot( invertex.normalW, -lightDirW), 0.0f);
	float4 color = (float4((lightDiffuse * l).rgb ,1.0f) + lightAmbient) * Diffuse;

	return tex2D(sampler0, invertex.uv) * float4(color.rgb, 1.0f);
}