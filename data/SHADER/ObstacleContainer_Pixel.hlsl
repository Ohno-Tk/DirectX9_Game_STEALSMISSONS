/*-----------------------------------------------------------------------------
Macro
-----------------------------------------------------------------------------*/
#define LIGHT_NUM (9)

/*-----------------------------------------------------------------------------
Struct
-----------------------------------------------------------------------------*/
struct IN_VERTEX
{ // �o�͗p
    float4 posH:POSITION0;
	float2 uv:TEXCOORD0;
	float3 normalW:TEXCOORD1;
	float3 posW:TEXCOORD2;
};

/*-----------------------------------------------------------------------------
Global
-----------------------------------------------------------------------------*/
sampler sampler0;
float4 Diffuse;// �f�B�t���[�Y��
float3 LightPosW[LIGHT_NUM];


float4 main(IN_VERTEX invertex):COLOR0
{
	float4 lightAmbient = float4(0.3f,0.3f,0.3f,1.0f);
	float4 lightDiffuse = float4(1.0f,1.0f,1.0f,1.0f);
	
	float3 Attenuation = float3(0.7f, 0.3f, 0.0f);

	float l[LIGHT_NUM];
	float d[LIGHT_NUM];
	float A[LIGHT_NUM];
	float4 color[LIGHT_NUM];
	float4 attColor = float4(0.0f, 0.0f, 0.0f, 0.0f);
	
	for(int i = 0; i < LIGHT_NUM; i++)
	{
		// �����v�Z
	    l[i] = max(dot(invertex.normalW, normalize(LightPosW[i] - invertex.posW)), 0.0f);
	    
	    // �����𑪂�
	    d[i] = distance(invertex.posW, LightPosW[i]);
	    
	    //�������̌v�Z
	    A[i] = Attenuation.x + Attenuation.y * d[i] + Attenuation.z * d[i] * d[i]; // �͈͂Ɋ܂܂ꂽ�����𖾂邭�������
	    	    
	    //�F�v�Z
	    color[i] = (float4(lightDiffuse.rgb ,1.0f) + lightAmbient) * float4(1.0f, 1.0f, 1.0f, 1.0f);
	    
	    // �������܂߂��F�v�Z
		attColor = attColor + float4(color[i].rgb * l[i] / A[i], 1.0f);
	}
	
	return tex2D(sampler0, invertex.uv) * attColor;
}