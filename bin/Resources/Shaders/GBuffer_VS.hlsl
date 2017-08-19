cbuffer bufferVista : register (b0)
{
	float4x4 matView;
}

cbuffer bufferProj : register (b1)
{
	float4x4 matProjection;
}

cbuffer bufferWorld : register (b2)
{
	float4x4 matWorld;
	float4 Color;
}

struct VS_INPUT
{
	float4 Position : POSITION;
	float2 TexCoord : TEXCOORD0;
	float3 Normal	: NORMAL;
	float3 BiNormal : BINORMAL;
	float3 Tangent	: TANGENT;

};

struct VS_OUTPUT
{
	float4 Position : SV_Position;
	float3 Normal	: TEXCOORD0;
	float2 TexCoord : TEXCOORD1;
	float3x3 TBN	: TEXCOORD5;
	float4 PosWorld : TEXCOORD2;
	float4 ViewPos	: TEXCOORD3;
	float4 ViewNormal : TEXCOORD4; // Direccion de vista normalizada.
};

VS_OUTPUT vs_main(VS_INPUT Input)
{
	VS_OUTPUT Output = (VS_OUTPUT)0;

	Output.PosWorld = mul(float4(Input.Position.xyz, 1.0), matWorld);
	Output.Position = mul(Output.PosWorld, matView);
	Output.Position = mul(Output.Position, matProjection);
	Output.TexCoord = Input.TexCoord;

	Output.ViewPos = mul(Output.PosWorld, matView);
	Output.ViewNormal = mul(float4(Input.Normal, 0), matView);
	Output.Normal = mul(float4(Input.Normal, 0), matWorld).xyz;

	Output.TBN[0] = Input.Tangent;
	Output.TBN[1] = Input.BiNormal;
	Output.TBN[2] = Input.Normal;

	return(Output);
}