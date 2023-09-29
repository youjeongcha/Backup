#pragma pack_matrix(row_major)

cbuffer constants
{
	matrix worldMatrix;
	matrix viewProjectionMatrix;
};

struct VertexInput
{
	float3 position : POSITION;
	float4 color : COLOR;
	float2 texcoord : TEXCOORD0;
	float3 normal : NORMAL;
};

struct VertexOutput
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float2 texcoord : TEXCOORD0;
	float3 normal : NORMAL;
	float4 worldPosition : TEXCOORD1;
};

VertexOutput main(VertexInput input)
{
	VertexOutput output;
	output.worldPosition = mul(float4(input.position, 1.0f), worldMatrix);
	output.normal = mul(input.normal, (float3x3)worldMatrix);
	output.position = mul(output.worldPosition, viewProjectionMatrix);
	output.color = input.color;
	output.texcoord = input.texcoord;
	return output;
}