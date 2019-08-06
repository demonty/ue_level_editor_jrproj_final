uniform extern float4x4 gWVP;
uniform extern float4x4 gWorld;
uniform extern float3 	gLightPos;
uniform extern texture 	gTex;


/* ~~~~~~~~~~ Texture Sampler States ~~~~~~~~~~ */
sampler TexS = sampler_state
{
	Texture  = <gTex>;
	Filter 	 = MIN_MAG_MIP_LINEAR;
	AddressU = WRAP;
	AddressV = WRAP;
};


/* ~~~~~~~~~~ Data Structures ~~~~~~~~~~ */
struct VS_DiffuseIn
{
	float4 posL	: POSITION0;
	float3 normal : NORMAL0;
	float2 tex0	: TEXCOORD0;
};

struct VS_DiffuseOut
{
	float4 posH : POSITION0;
	float shade : TEXCOORD0;
	float2 tex0 : TEXCOORD1;
};


/* ~~~~~~~~~~ Returns the Dot-Product ~~~~~~~~~~ */
float DotProduct(float3 posW, float3 normal)
{
	float3 dir = normalize(gLightPos - posW);
	return dot(dir, normal);
}


/* ~~~~~~~~~~ Diffuse Vertex Shader ~~~~~~~~~~ */
VS_DiffuseOut DiffuseVS(VS_DiffuseIn input)
{
	VS_DiffuseOut output = (VS_DiffuseOut)0;
	
	output.posH = mul(input.posL, gWVP);
	output.tex0 = input.tex0;
	
	float3 posW = mul(input.posL, gWorld).xyz;
	float3 normal = normalize(mul(input.normal, (float3x3)gWorld));
	
	output.shade = DotProduct(posW, normal);
	
	return output;
}

/* ~~~~~~~~~~ Diffuse Pixel Shader ~~~~~~~~~~ */
float4 DiffusePS(VS_DiffuseOut input) : COLOR
{
	float4 color = tex2D(TexS, input.tex0);
	color *= input.shade;
	
	return color;
}


/* ~~~~~~~~~~ Techniques ~~~~~~~~~~ */
technique DiffuseTech
{
	pass p0
	{
		vertexShader = compile vs_3_0 DiffuseVS();
		pixelShader  = compile ps_3_0 DiffusePS();
	}
}