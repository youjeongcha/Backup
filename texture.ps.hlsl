struct PixelInput
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float2 texcoord : TEXCOORDO;
};

Texture2D tex : TEXCOORD : register(t0);
SamplerState sample : SAMPLER : register(s0);

float4 main(PixelInput input) : SV_TARGET
{
	return input.color * tex.Sample(sample, input.texcoord);
}