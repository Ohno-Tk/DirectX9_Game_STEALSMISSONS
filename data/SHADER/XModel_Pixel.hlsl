/*-----------------------------------------------------------------------------
Macro
-----------------------------------------------------------------------------*/
#define LIGHT_NUM (9)

/*-----------------------------------------------------------------------------
Struct
-----------------------------------------------------------------------------*/
struct IN_VERTEX
{ // 出力用
    float4 posH:POSITION0;
	float2 uv:TEXCOORD0;
	float3 normalW:TEXCOORD1;
	float3 posW:TEXCOORD2;
};

/*-----------------------------------------------------------------------------
Global
-----------------------------------------------------------------------------*/
sampler sampler0;
float4 Diffuse;// ディフューズ光
float3 LightPosW[LIGHT_NUM];
float3 CameraEyeW;

float4 main(IN_VERTEX invertex):COLOR0
{
	float4 lightAmbient = float4(0.3f,0.3f,0.3f,1.0f);
	float4 lightDiffuse = float4(1.0f,1.0f,1.0f,1.0f);
	
	float3 Attenuation = float3(0.8f, 0.2f, 0.0f);

	float l[LIGHT_NUM];
	float d[LIGHT_NUM];
	float A[LIGHT_NUM];
	float4 color[LIGHT_NUM];
	float4 attColor = float4(0.0f, 0.0f, 0.0f, 0.0f);
	
	for(int i = 0; i < LIGHT_NUM; i++)
	{
		// 光源計算
	    l[i] = max(dot(invertex.normalW, normalize(LightPosW[i] - invertex.posW)), 0.0f);
	    
	    // 距離を測る
	    d[i] = distance(invertex.posW, LightPosW[i]);
	    
	    //減衰率の計算
	    A[i] = Attenuation.x + Attenuation.y * d[i] + Attenuation.z * d[i] * d[i]; // 範囲に含まれた部分を明るくする公式
	    
	     // カメラへのベクトル算出
		float3 toEyeW = normalize(CameraEyeW - invertex.posW);
		
	    // 反射ベクトル算出
		float3 reflection = reflect(normalize(invertex.posW - LightPosW[i]), invertex.normalW);
		
		// スペキュラーの強さを求める
		float specularPow = pow(max(dot(reflection, toEyeW ), 0.0f), 5.0f);
		float4 specular = float4(1.0f, 1.0f, 1.0f, 1.0f) * specularPow;
	    
	    //色計算
	    color[i] = (float4(lightDiffuse.rgb ,1.0f) + lightAmbient + specular) * Diffuse;
	    
	    // 減衰率含めた色計算
		attColor = attColor + float4(color[i].rgb * l[i] / A[i], 1.0f);
	}
	
	return tex2D(sampler0, invertex.uv) * attColor;

}