#pragma pack_matrix(row_major)

cbuffer Constants
{
	matrix worldMatrix;
	matrix viewProjectionMatrix;
};

struct VertexInput
{
	float3 position : POSITION;
	float4 color : COLOR;
	float2 texcoord : TEXCOORD0;
};

struct VertexOutput
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float2 texcoord : TEXCOORD0;
};

VertexOutput main(VertexInput input)
{
	VertexOutput output;
	// world Transform
	output.position = mul(float4(input.position, 1.0f), worldMatrix);
	// view*projection Transform
	output.position = mul(output.position, viewProjectionMatrix);
	output.color = input.color;
	output.texcoord = input.texcoord;
	return output;
}