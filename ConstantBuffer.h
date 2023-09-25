#pragma once
#include "Log.h"
#include "Constant.h"
#include <wrl/client.h>
#include <d3d11.h>

template<typename T>
class ConstantBuffer
{
private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
	ID3D11DeviceContext* deviceContext;

	ConstantBuffer(const ConstantBuffer& rhs);

public:
	ConstantBuffer() : buffer(nullptr), deviceContext(nullptr) {}

	// ��� ���Ǹ� ���� public ������ ����.
	T data;

	HRESULT Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext)
	{
		this->deviceContext = deviceContext;

		if (nullptr != buffer.Get()) 
			buffer.Reset();

		D3D11_BUFFER_DESC desc = { 0 };
		// ���̴��� cbuffer(constant buffer)�� 16byte������ ����.
		desc.ByteWidth = static_cast<UINT>(sizeof(T) + (16 - (sizeof(T) % 16)));
		// �� �����Ӹ��� ������Ʈ �Ǳ� ������ ����(dynamic)���� ����.
		desc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
		// CPU�� ����(write)�� �ϱ� ������ ��뿡 �����.
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;

		return device->CreateBuffer(&desc, NULL, buffer.GetAddressOf());
	}

	bool ApplyChanges()
	{
		D3D11_MAPPED_SUBRESOURCE resource;
		HRESULT hr = deviceContext->Map(buffer.Get(), 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &resource);

		if (FAILED(hr))
		{
			Log::ErrorMsg(hr, "Failed to map(memory lock) constant buffer.");
			return false;
		}

		CopyMemory(resource.pData, &data, sizeof(T));
		deviceContext->Unmap(buffer.Get(), 0);

		return true;
	}

	ID3D11Buffer* Get() const
	{
		return buffer.Get();
	}
	ID3D11Buffer* const* GetAddressOf() const
	{
		return buffer.GetAddressOf();
	}
};