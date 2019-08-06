uniform extern float4x4	gWVP;
uniform extern float4x4	gWorld;
uniform extern float3	gLightDir;
uniform extern float3	gOutlineColor;
uniform extern float	gOutlineThickness;
uniform extern float3	gAmbientColor;
uniform extern float	gAmbientPower;
uniform extern texture	gTex;

/* ~~~~~~~~~~ Texture Sampler States ~~~~~~~~~~ */
sampler TexS = sampler_state
{
	Texture  = <gTex>;
	Filter   = MIN_MAG_MIP_LINEAR;
	AddressU = WRAP;
	AddressV = WRAP;
};


/* ~~~~~~~~~~ Data Structures ~~~~~~~~~~ */
struct VS_OutlineIn
{
	float4 posL : POSITION0;
	float3 normal : NORMAL0;
};

struct VS_OutlineOut
{
	float4 posH : POSITION0;
};

struct VS_ToonIn
{
	float4 posL : POSITION0;
	float3 normal : NORMAL0;
	float2 tex0 : TEXCOORD0;
};

struct VS_ToonOut
{
	float4 posH : POSITION0;
	float3 normal : TEXCOORD0;
	float2 tex0 : TEXCOORD1;
};


/* ~~~~~~~~~~ Outline Vertex Shader ~~~~~~~~~~ */
VS_OutlineOut OutlineVS(VS_OutlineIn input)
{
	VS_OutlineOut output = (VS_OutlineOut)0;
	
	float4 normal = float4(normalize(mul(input.normal, (float3x3)gWorld)), 0.0f);
	float4 pos = input.posL + (gOutlineThickness * normal);
	output.posH = mul(pos, gWVP);
	
	return output;
}

/* ~~~~~~~~~~ Outline Pixel Shader ~~~~~~~~~~ */
float4 OutlinePS(VS_OutlineOut input) : COLOR
{
	return float4(gOutlineColor, 1.0f);
}

/* ~~~~~~~~~~ Toon Vertex Shader ~~~~~~~~~~ */
VS_ToonOut ToonVS(VS_ToonIn input)
{
	VS_ToonOut output = (VS_ToonOut)0;
	
	output.posH = mul(input.posL, gWVP);
	output.tex0 = input.tex0;
	output.normal = normalize(mul(input.normal, (float3x3)gWorld));
	
	return output;
}

/* ~~~~~~~~~~ Toon Pixel Shader ~~~~~~~~~~ */
float4 ToonPS(VS_ToonOut input) : COLOR
{
	float i = dot(normalize(gLightDir), input.normal);
	if(i < 0)
		i = 0;

	float4 c = tex2D(TexS, input.tex0);
	
	if(i > 0.7f)
		c = float4(1.0f,1.0f,1.0f,1.0f) * c;
	else if(i > 0.45f)
		c = float4(0.7f,0.7f,0.7f,1.0f) * c;
	else if(i > 0.2f)
		c = float4(0.35f,0.35f,0.35f,1.0f) * c;
	else
		c = float4(0.1f, 0.1f, 0.1f, 1.0f) * c;
	
	return c + float4((gAmbientColor * gAmbientPower), 1.0f);
}


/* ~~~~~~~~~~ Techniques ~~~~~~~~~~ */
technique ToonTech
{
	pass p0
	{
		vertexShader = compile vs_3_0 OutlineVS();
		pixelShader  = compile ps_3_0 OutlinePS();
		
		CullMode = CW;
	}
	
	pass p1
	{
		vertexShader = compile vs_3_0 ToonVS();
		pixelShader  = compile ps_3_0 ToonPS();
		
		CullMode = CCW;
	}
}