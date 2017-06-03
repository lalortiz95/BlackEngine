Texture2D DiffuseTexture : register(t0);
SamplerState DiffuseSampler : register(s0);

struct PS_INPUT
{
	float4 position : SV_POSITION;
	float2 texCoord : TEXCOORD0;
};

float4 PSMain(PS_INPUT psInput) : SV_Target
{
	//return float4 (psInput.texCoord, 0.0f, 1.0f);
	//psInput.texCoord.y = -psInput.texCoord.y;

	return DiffuseTexture.Sample(DiffuseSampler, psInput.texCoord);
};