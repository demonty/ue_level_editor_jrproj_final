uniform extern float4x4 gWVP;
uniform extern float4x4 gWorld;
uniform extern float3	gPlayerPos;
uniform extern float3	gColor;
uniform extern texture	gTex;
uniform extern float	gIntensity;
uniform extern float	gSmoothStart;
uniform extern float	gSmoothEnd;


/* ~~~~~~~~~~ Notes ~~~~~~~~~~ */
// Light Blue Shade:	(0.19f,0.60f,0.57f)
// Light Red Shade:		(0.74f,0.23f,0.23f)


/* ~~~~~~~~~~ Texture Sampler States ~~~~~~~~~~ */
sampler TexS = sampler_state
{
	Texture  = <gTex>;
	Filter   = MIN_MAG_MIP_LINEAR;
	AddressU = WRAP;
	AddressV = WRAP;
};


/* ~~~~~~~~~~ Data Structures ~~~~~~~~~~ */
struct VS_RimIn
{
	float4 posL : POSITION0;
	float3 normal: NORMAL0;
	float2 tex0 : TEXCOORD0;
};

struct VS_RimOut
{
	float4 posH : POSITION0;
	float2 tex0 : TEXCOORD0;
	float3 normal : TEXCOORD1;
	float3 posW : TEXCOORD2;
};


/* ~~~~~~~~~~ Rim Vertex Shader ~~~~~~~~~~ */
VS_RimOut RimVS(VS_RimIn input)
{
	VS_RimOut output = (VS_RimOut)0;
	
	output.posH = mul(input.posL, gWVP);
	output.tex0 = input.tex0;
	output.posW = mul(input.posL, gWorld);
	output.normal = normalize(mul(input.normal, gWorld));
	
	return output;
}

/* ~~~~~~~~~~ Returns the dot-product ~~~~~~~~~~ */
float DotProduct(float3 pos, float3 normal)
{
	float3 dir = normalize(gPlayerPos - pos);
	return dot(dir, normal);
}

/* ~~~~~~~~~~ Rim Pixel Shader ~~~~~~~~~~ */
float4 RimPS(VS_RimOut input) : COLOR
{	
	float3 c = tex2D(TexS, input.tex0).rgb;
	float3 n = input.normal;
	float3 v = normalize(gPlayerPos - input.posW);
	float rim = smoothstep(gSmoothStart, gSmoothEnd, 1 - dot(n,v));
	
	return float4(c , 1.0f) + float4(rim * gColor * gIntensity, 1.0f);
}


/* ~~~~~~~~~~ Techniques ~~~~~~~~~~ */
technique RimTech
{
	pass p0
	{
		vertexShader = compile vs_3_0 RimVS();
		pixelShader  = compile ps_3_0 RimPS();
	}
}