uniform extern float4x4 gWVP;
uniform extern texture	gTex;

static float3 gGlowColor = {0.75f, 0.75f, 1.0f};
static float  gOffset = 0.5f;

sampler TexS = sampler_state
{
	Texture   = <gTex>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = POINT;
	AddressU  = WRAP;
	AddressV  = WRAP;
};

// Output Structs  ---------------------------
struct VS_OUTPUT
{
	float4 posH : POSITION0;
	float2 texCoord : TEXCOORD0;
};

struct VS_GLOW
{
	float4 posH : POSITION0;
	float3 normal : NORMAL0;
};
// -------------------------------------------

// GlowVS & GlowPS draw the object normally
VS_OUTPUT GlowVS(float3 posW : POSITION0, float2 tex0 : TEXCOORD0)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	
	output.posH = mul(float4(posW, 1.0f), gWVP);
	output.texCoord = tex0;
	
	return output;
}

float4 GlowPS(float2 tex0 : TEXCOORD0, float3 normal : NORMAL0) : COLOR
{
	float3 c = tex2D(TexS, tex0).rgb;
	return float4(c, 1.0f);
}

// GlowOffsetPS & GlowOffsetVS draw the object scaled up and alphad out
VS_GLOW GlowOffsetVS(float3 posW : POSITION0, float4 normal : NORMAL0)
{
	VS_GLOW output = (VS_GLOW)0;
	
	output.normal = mul(normal, gWVP).xyz; // Translate normal into world coordinates
	
	float4 pos = float4(posW, 1.0f);
	pos += (gOffset * normalize(float4(normal.xyz, 0.0f))); // balloon effect
	float4 posH = mul(pos, gWVP); // Transform to homogeneous clip space
	output.posH = posH;
	
	return output;
}

float4 GlowOffsetPS(float2 tex0 : TEXCOORD0, float3 normal : NORMAL0) : COLOR
{
	return float4(gGlowColor, 0.75f);
}

technique GlowTech
{
	pass p0
	{
		vertexShader = compile vs_3_0 GlowVS();
		pixelShader  = compile ps_3_0 GlowPS();
	}
	pass p1
	{
		vertexShader = compile vs_3_0 GlowOffsetVS();
		pixelShader  = compile ps_3_0 GlowOffsetPS();
		
		AlphaBlendEnable = true;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;
	}
}