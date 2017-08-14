#define M_PI 3.14159265359

sampler AlbedoSampler;
sampler NormalSampler;
sampler MetallicSampler;
sampler RoughnessSampler;

sampler EnviromentSampler;
sampler IrradianceSampler;

float3 g_LightPosition;
float4 g_LightColor;
float4 vViewPosition;

struct PS_INPUT
{
	float3 Normal	: NORMAL0;
	float2 TexCoord : TEXCOORD0;
	float3x3 TBN	: TEXCOORD1;
	float4 PosWorld : NORMAL1;
	float4 ViewPos	: NORMAL2;
	float4 ViewNormal : NORMAL3; // Direccion de vista normalizada.
};

float3 Diffuse(float3 albedoColor)
{
	return albedoColor / M_PI;
}

float NormalDistribution_GGX(float a, float NdH)
{
	//GGX isotropico
	float a2 = a*a;
	float NdH2 = NdH * NdH;

	float denominador = NdH2 * (a2 - 1.0f) + 1.0f;
	denominador *= denominador;
	denominador *= M_PI;

	return a2 / denominador;
}

float3 Fresnel_Schlick(float3 specularColor, float3 v, float3 h)
{
	//el factor de fresnel lo conocemos como el color especular.
	return (specularColor + (1.0 - specularColor) * pow(1.0f - saturate(dot(v, h)), 5));
}

float Geometric_Smith_Schlick_GGX(float a, float NdV, float NdL)
{
	//GGX smith schlick
	float k = a * 0.5f;
	float GV = NdV / (NdV * (1.0 - k) + k);
	float GL = NdL / (NdV * (1.0 - k) + k);
	return GV * GL;
}

//especular difuso, se puede calcular como blinn phong.
//esta es una forma más perrona.
float Specular_D(float a, float NdH)
{
	return NormalDistribution_GGX(a, NdH);
}

//el color, la vista, y el half.
float3 Specular_F(float3 specularColor, float3 v, float3 h)
{
	return Fresnel_Schlick(specularColor, v, h);
}

//Specular fresnel con roughmess
float3 Specular_F_Roughness(float3 f0, float3 v, float3 h, float a)
{
	return (f0 + (max(1.0 - a, f0) - f0) *  pow(1.0f - saturate(dot(v, h)), 5));
}

float Specular_G(float a,
	float NdV,
	float NdL,
	float NdH,
	float VdH,
	float LdV)
{
	return Geometric_Smith_Schlick_GGX(a, NdV, NdL);
}

float3 Specular(float3 specularColor,
	float3 h,
	float3 v,
	float3 lightDir,
	float a,
	float NdL,
	float NdV,
	float NdH,
	float VdH,
	float LdV)
{
	float D = Specular_D(a, NdH);
	float3 F = Specular_F(specularColor, v, h);
	float G = Specular_G(a, NdV, NdL, NdH, VdH, LdV);

	return (D*F*G) / (4.0 * NdV * NdL + 0.0001f);
}

float3  ComputeLight(float3 albedoColor,
	float3 specularColor,
	float3 normal,
	float roughness,
	float3 lightPosition,
	float3 lightColor,
	float3 lightDir,
	float3 viewDir)
{
	// Calculamos los vectores del BRDF.
	//Normal dot light.
	float NdL = saturate(dot(normal, lightDir));
	// Normal dot view.
	float NdV = saturate(dot(normal, viewDir));
	// half.
	float3 h = normalize(lightDir + viewDir);
	// Normal dot half.
	float NdH = saturate(dot(normal, h));
	// View dot half.
	float VdH = saturate(dot(viewDir, h));
	// Light dot view.
	float LdV = saturate(dot(lightDir, viewDir));

	// Factor minimo de roughness, se limita a un pequeño delta por que no podemos permitir que haya un 0.
	float a = max(0.001f, roughness * roughness);

	float3 ColorDiffuse = Diffuse(albedoColor);
	float3 ColorSpecular = Specular(specularColor,
		h,
		viewDir,
		lightDir,
		a,
		NdL, NdV, NdH, VdH, LdV);

	return lightColor * NdL * (ColorDiffuse * (1.0f - ColorSpecular) + ColorSpecular);
}

struct PS_OUTPUT
{
	float4 position  : COLOR0;
	float4 normal    : COLOR1;
	float4 color     : COLOR2;
};

PS_OUTPUT ps_main(PS_INPUT Input)
{
	// Albedo y Normal son estandar.
	float3 albedoColor = tex2D(AlbedoSampler, Input.TexCoord).xyz;

	float3 normal = tex2D(NormalSampler, Input.TexCoord).xyz;
	normal = normalize(2.0f * normal - 1.0f);
	normal = normalize(mul(normal, Input.TBN));

	//Metallic - Disney BRDF.
	float metallic = tex2D(MetallicSampler, Input.TexCoord).x;

	//Inversa para convertir de Glossiness a Roughness.
	float roughness = 1.0 - tex2D(RoughnessSampler, Input.TexCoord).x;

	//Corrección de gama.
	albedoColor = pow(albedoColor, 2.2);

	//Calculamos los parametros de color real.
	float3 realAlbedo = albedoColor - (albedoColor * metallic);
	float3 realSpecularColor = lerp(0.03f, albedoColor, metallic);

	float3 pos = Input.PosWorld / Input.PosWorld.w;
	float3 viewDir = normalize(vViewPosition.xyz - pos);
	float3 lightDir = normalize(g_LightPosition - pos);

	float3 light1 = ComputeLight(realAlbedo,
		realSpecularColor,
		normal,
		roughness,
		g_LightPosition,
		g_LightColor.xyz,
		lightDir,
		viewDir);

	float mipIndex = roughness * roughness * 9.0;
	float3 reflectVector = reflect(normal, -viewDir);
	float4 EnvVector = float4(reflectVector.xyz, mipIndex);
	float3 envColor = texCUBElod(EnviromentSampler, EnvVector);
	float3 irradiance = texCUBE(IrradianceSampler, normal);

	float3 envFresnel = Specular_F_Roughness(realSpecularColor, normal, viewDir, roughness * roughness);
	envColor = envColor * envFresnel;

	envColor = pow(envColor, 2.2);
	irradiance = pow(irradiance, 2.2) * 0.03f;

	light1 *= 50;
	float4 FinalColor = float4(light1 + envColor + irradiance, 1);
	//FinalColor = pow(FinalColor, 1.0 / 2.2);

	PS_OUTPUT Output = (PS_OUTPUT)0;
	Output.position = Input.PosWorld;
	Output.normal = float4(normal, 0);
	Output.color = float4(FinalColor.xyz, 1);

	return Output;
}