//DirectX ���̴�
//DirectX 11���� ���� ������������ �����Ǿ�, �ƹ��� ������ �������� ������ �ϴ��� �ݵ�� ���̴��� ���ľ߸� �Ѵ�.

#pragma once
#pragma comment(lib, "d3dcompiler.lib")
#include <wrl/client.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include "Log.h"

class VertexShader
{
private:
	Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader;

public:
	bool Initialize(ID3D11Device* pDevice, std::wstring fileName, D3D11_INPUT_ELEMENT_DESC* layoutDesc, UINT numElements);
	ID3D11VertexShader* GetShader() const { return vertexShader.Get(); }
	ID3D11InputLayout* GetInputLayout() const { return inputLayout.Get(); }
};

class PixelShader
{
private:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader;

public:
	bool Initialize(ID3D11Device* pDevice, std::wstring fileName);
	ID3D11PixelShader* GetShader() const { return pixelShader.Get(); }
};