//Vertex.h
#pragma once
#include <DirectXMath.h>
using namespace DirectX;

struct Vertex
{
	XMFLOAT3 pos;

	Vertex() : pos(0.0f, 0.0f, 0.0f) {}
	Vertex(float x, float y, float z) :pos(x, y, z) {}
};


struct VertexColor : Vertex
{
	XMFLOAT4 color;

	VertexColor() : color(1.0f, 1.0f, 1.0f, 1.0f) {}
	VertexColor(float x, float y, float z, float r, float g, float b, float a) : Vertex(x, y, z), color(r, g, b, a) {}
	VertexColor(float x, float y, float z, float r, float g, float b) : VertexColor(x, y, z, r, g, b, 1.0f) {}
};