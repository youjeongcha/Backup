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
};

struct VertexOutput
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

VertexOutput main(VertexInput input)
{
	VertexOutput output;
	output.position = mul(float4(input.position, 1.0f), worldMatrix);
	output.position = mul(output.position, viewProjectionMatrix);
	output.color = input.color;
	return output;
}