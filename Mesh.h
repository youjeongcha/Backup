//Mesh/Model
//쉽게 메시를 그리기 위한 메시 객체 구조를 만든다.

#pragma once
#include <vector>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Texture.h"

class Mesh
{
private:
	ID3D11DeviceContext* deviceContext;

	VertexBuffer<ModelVertex> vertexBuffer;
	IndexBuffer indexBuffer;
	std::vector<Texture> textures;

	XMMATRIX transformMatrix;

public:
	Mesh(ID3D11Device* device, ID3D11DeviceContext* deviceContext, std::vector<ModelVertex>& vertices, std::vector<DWORD>& indices, std::vector<Texture>& textures, const XMMATRIX& transformMatrix) : deviceContext(deviceContext), transformMatrix(transformMatrix), textures(textures)
	{
		HRESULT hr = vertexBuffer.Initialize(device, vertices.data(), vertices.size());
		COM_ERROR_IF_FAILED(hr, "Failed to Initialize vertex buffer for mesh.");

		hr = indexBuffer.Initialize(device, indices.data(), indices.size());
		COM_ERROR_IF_FAILED(hr, "Failed to Initialize index buffer for mesh.");
	}

	Mesh(const Mesh& mesh)
	{
		deviceContext = mesh.deviceContext;
		transformMatrix = mesh.transformMatrix;
		vertexBuffer = mesh.vertexBuffer;
		indexBuffer = mesh.indexBuffer;
		textures = mesh.textures;
	}

	const XMMATRIX& GetTransformMatrix() const { return transformMatrix; }

	void Draw()
	{
		deviceContext->PSSetShaderResources(0, 1, textures[0].GetTextureResourceViewAddress());
		UINT offset = 0;
		deviceContext->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), vertexBuffer.StridePtr(), &offset);
		deviceContext->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT::DXGI_FORMAT_R32_UINT, 0);
		deviceContext->DrawIndexed(indexBuffer.IndexCount(), 0u, 0);
	}
};