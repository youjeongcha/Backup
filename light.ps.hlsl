//방향성 광원
//정반사광(Specular Light), 난반사광(Diffuse Light), 환경광(Ambiet Light)을 포함한 방향성 광원 셰이더를 이요하여 물체에 음영 처리
cbuffer Constants : register(b0)
{
	float4 cameraPosition;
	float4 lightColor;
	float4 lightDirection;
	float4 globalAmbient;
	float4 materialAmbient;
	float4 materialDiffuse;
	float4 materialSpecular;
	float materialSpecularPower;
};

float4 Diffuse(float4 color, float3 L, float3 N)
{
	float NdotL = max(0, dot(N, L));
	return color * NdotL;
}

float4 Specular(float4 color, float3 V, float3 L, float3 N)
{
	// Phong Light
	float3 R = normalize(reflect(-L, N));
	float RdotV = max(0, dot(R, V));
	return color * pow(RdotV, materialSpecularPower);
}

struct PixelInput
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float2 texcoord : TEXCOORD0;
	float3 normal : NORMAL;
	float4 worldPosition : TEXCOORD1;
};

Texture2D tex : TEXCOORD : register(t0);
SamplerState sample : SAMPLER : register(s0);

float4 main(PixelInput input) : SV_TARGET
{
	float3 V = normalize(cameraPosition - input.worldPosition).xyz;
	float3 L = -lightDirection.xyz;
	float3 N = normalize(input.normal);

	// calculate ambient
	float4 ambientLight = materialAmbient * globalAmbient;

	// calculate diffuse
	float4 diffuseLight = Diffuse(lightColor, L, N);
	diffuseLight = materialDiffuse * saturate(diffuseLight);

	// calculate specular
	float4 specularLight = Specular(lightColor, V, L, N);
	specularLight = materialSpecular * saturate(specularLight);
	float4 color = input.color * tex.Sample(sample, input.texcoord);
	float4 finalColor = (ambientLight + diffuseLight + specularLight) * color;
	return finalColor;
}
