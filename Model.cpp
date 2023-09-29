#include "Model.h"

void Model::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, ConstantBuffer<Matrices>& vsConstantBuffer)
{
	this->device = device;
	this->deviceContext = deviceContext;
	this->vsConstantBuffer = &vsConstantBuffer;
}

void Model::Draw(const XMMATRIX& worldMatrix, const XMMATRIX& viewProjectionMatrix)
{
	deviceContext->VSSetConstantBuffers(0, 1, vsConstantBuffer->GetAddressOf());
	vsConstantBuffer->data.world = mesh->GetTransformMatrix() * worldMatrix;
	vsConstantBuffer->data.viewProjection = viewProjectionMatrix;
	vsConstantBuffer->ApplyChanges();
	mesh->Draw();
}
