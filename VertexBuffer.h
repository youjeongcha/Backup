//���� ����
//���� ���ۿ� �ۼ��� ���� �����͸� �̿��Ͽ� ������ �������� ���

#pragma once
#include <wrl/client.h> // Microsoft::WRL::ComPtr�� ����ϱ� ���� �߰�.
#include <d3d11.h>
#include <memory>
#include "Vertex.h"


//���ø� �ش� Ŭ���� ���� T�� ���� ������ �Ǵ�. Vertex�� ����ؼ� ���� class�ΰ�? üũ�ϰ� ��� Ȥ�� ���� ���
template<typename T, typename = std::enable_if<std::is_base_of<Vertex, T>::value>>
class VertexBuffer
{
private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
	UINT stride, vertexCount;

public:
	VertexBuffer() : buffer(nullptr), stride(sizeof(T)), vertexCount(0) { }
	VertexBuffer(const VertexBuffer<T>& rhs)
	{
		buffer = rhs.buffer;
		stride = rhs.stride;
		vertexCount = rhs.vertexCount;
	}

	VertexBuffer<T>& operator=(const VertexBuffer<T>& rhs)
	{
		buffer = rhs.buffer;
		stride = rhs.stride;
		vertexCount = rhs.vertexCount;
		return *this;
	}

	HRESULT Initialize(ID3D11Device* device, T* vertices, UINT vertexCount)
	{
		if (nullptr != buffer.Get())
			buffer.Reset();

		this->vertexCount = vertexCount;
		D3D11_BUFFER_DESC vertexBufferDesc = { 0 };
		vertexBufferDesc.ByteWidth = stride * vertexCount; //������ ũ��
		vertexBufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		vertexBufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA vertexBufferData = { 0 };
		vertexBufferData.pSysMem = vertices; //������
		return device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, buffer.GetAddressOf());
	}

	ID3D11Buffer* Get() const { return buffer.Get(); }
	ID3D11Buffer* const* GetAddressOf() const { return buffer.GetAddressOf(); }

	UINT VertexCount() const { return vertexCount; }

	const UINT Stride() const { return stride; }
	const UINT* StridePtr() const { return &stride; }
};

