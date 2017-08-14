float4x4 matView;
float4x4 matViewProjection;
float4x4 matWorld;

struct VS_INPUT
{
	float4 Position : POSITION0;
	float2 TexCoord : TEXCOORD0;
	float3 Normal	: NORMAL;
	float3 BiNormal : BINORMAL;
	float3 Tangent	: TANGENT;

};

struct VS_OUTPUT
{
	float4 Position : POSITION0;
	float3 Normal	: NORMAL0;
	float2 TexCoord : TEXCOORD0;
	float3x3 TBN	: TEXCOORD1;
	float4 PosWorld : NORMAL1;
	float4 ViewPos	: NORMAL2;
	float4 ViewNormal : NORMAL3; // Direccion de vista normalizada.
};

VS_OUTPUT vs_main(VS_INPUT Input)
{
	VS_OUTPUT Output = (VS_OUTPUT)0;

	Output.PosWorld = mul(float4(Input.Position.xyz, 1.0), matWorld);
	Output.Position = mul(Output.PosWorld, matViewProjection);
	Output.TexCoord = Input.TexCoord;

	Output.ViewPos = mul(Output.PosWorld, matView);
	Output.ViewNormal = mul(float4(Input.Normal, 0), matView);
	Output.Normal = mul(Input.Normal, matWorld);

	Output.TBN[0] = Input.Tangent;
	Output.TBN[1] = Input.BiNormal;
	Output.TBN[2] = Input.Normal;

	return(Output);
}