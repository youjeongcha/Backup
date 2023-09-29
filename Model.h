#pragma once
#include "Mesh.h"
#include "ConstantBuffer.h"

class Model abstract
{
protected:
	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;

	std::unique_ptr<Mesh> mesh;
	ConstantBuffer<Matrices>* vsConstantBuffer;

public:
	void Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, ConstantBuffer<Matrices>& vsConstantBuffer);
	void Draw(const XMMATRIX& worldMatrix, const XMMATRIX& viewProjectionMatrix);
};