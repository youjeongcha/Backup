//정범 버퍼
//정점 버퍼에 작성된 정점 데이터를 이용하여 폴리곤 렌더링에 사용

#pragma once
#include <wrl/client.h> // Microsoft::WRL::ComPtr를 사용하기 위해 추가.
#include <d3d11.h>
#include <memory>
#include "Vertex.h"


//템플릿 해당 클래스 내의 T의 제한 조건을 건다. Vertex를 상속해서 만든 class인가? 체크하고 통과 혹은 에러 띄움
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
		vertexBufferDesc.ByteWidth = stride * vertexCount; //버퍼의 크기
		vertexBufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		vertexBufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA vertexBufferData = { 0 };
		vertexBufferData.pSysMem = vertices; //데이터
		return device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, buffer.GetAddressOf());
	}

	ID3D11Buffer* Get() const { return buffer.Get(); }
	ID3D11Buffer* const* GetAddressOf() const { return buffer.GetAddressOf(); }

	UINT VertexCount() const { return vertexCount; }

	const UINT Stride() const { return stride; }
	const UINT* StridePtr() const { return &stride; }
};

