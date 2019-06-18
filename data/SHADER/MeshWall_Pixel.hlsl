/*-----------------------------------------------------------------------------
Macro
-----------------------------------------------------------------------------*/
#define LIGHT_NUM (9)

/*-----------------------------------------------------------------------------
Struct
-----------------------------------------------------------------------------*/
struct IN_VERTEX
{ // “ü—Í—p
    float4 posH:POSITION0;
	float2 uv:TEXCOORD0;
	float3 normalW:TEXCOORD1;
	float3 posW:TEXCOORD2;
};

/*-----------------------------------------------------------------------------
Global
-----------------------------------------------------------------------------*/
sampler sampler0;
float3 lightDirW;


float4 main(IN_VERTEX invertex):COLOR0
{
	float4 lightAmbient = float4(0.2f,0.2f,0.2f,1.0f);
	float4 lightDiffuse = float4(1.0f,1.0f,1.0f,1.0f);

	float l = max(dot( invertex.normalW, -lightDirW), 0.0f);
	float4 color = (float4((lightDiffuse * l).rgb ,1.0f) + lightAmbient) * float4(1.0f, 1.0f, 1.0f, 1.0f);
	
	return tex2D(sampler0, invertex.uv) * float4(color.rgb, 1.0f);
}