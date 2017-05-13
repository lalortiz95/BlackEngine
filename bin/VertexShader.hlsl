cbuffer bufferVista : register (b0)
{
	float4x4 matView;
}

cbuffer bufferProj : register (b1)
{
	float4x4 matProj;
}

cbuffer bufferWorld : register (b2)
{
	float4x4 matWorld;
	float4 Color;
}

struct VS_INPUT
{
	float3 pos : POSITION0;
	float2 texCoord : TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 pos : SV_POSITION;
	float2 texCoord : TEXCOORD0;
};

VS_OUTPUT VSMain(VS_INPUT vs_input)
{
	VS_OUTPUT output;

	output.pos = mul(float4(vs_input.pos, 1.0), matWorld);
	output.pos = mul(output.pos, matView);
	output.pos = mul(output.pos, matProj);

	output.texCoord = vs_input.texCoord;
	return output;
}