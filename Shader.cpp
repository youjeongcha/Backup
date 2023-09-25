#include "Shader.h"

bool VertexShader::Initialize(ID3D11Device* pDevice, std::wstring fileName, D3D11_INPUT_ELEMENT_DESC* layoutDesc, UINT numElements)
{
    Microsoft::WRL::ComPtr<ID3D10Blob> errorBlob, vertexBuffer;
    //���� ���̴� ������, vs_5_0(vertex shader 5.0) DirectX 11������ 5.0 ������ ���.
    HRESULT hr = D3DCompileFromFile(fileName.c_str(), NULL, NULL, "main", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, vertexBuffer.GetAddressOf(), errorBlob.GetAddressOf());

    if (FAILED(hr))
    {
        std::wstring msg = L"Failed to complie shader : ";
        if (nullptr == errorBlob.Get())
            msg += fileName;
        else
            msg += StringHelper::StringToWideString((char*)errorBlob->GetBufferPointer());
        Log::ErrorMsg(hr, msg);
        return false;
    }

    //���� ���̴� ����
    hr = pDevice->CreateVertexShader(vertexBuffer.Get()->GetBufferPointer(), vertexBuffer.Get()->GetBufferSize(), NULL, vertexShader.GetAddressOf());

    if (FAILED(hr))
    {
        std::wstring msg = L"Failed to create vertex shader : ";
        msg += fileName;
        Log::ErrorMsg(hr, msg);
        return false;
    }

    hr = pDevice->CreateInputLayout(layoutDesc, numElements, vertexBuffer->GetBufferPointer(), vertexBuffer->GetBufferSize(), inputLayout.GetAddressOf());

    if (FAILED(hr))
    {
        Log::ErrorMsg(hr, "Failed to create input layout.");
        return false;
    }

    return true;
} // VertexShader::Initialize()

bool PixelShader::Initialize(ID3D11Device* pDevice, std::wstring fileName)
{
    Microsoft::WRL::ComPtr<ID3D10Blob> errorBlob, pixelBuffer;
    // �ȼ� ���̴� ������, ps_5_0(pixel shader 5.f) DirectX 11������ 5.0 ������ ���.
    HRESULT hr = D3DCompileFromFile(fileName.c_str(), NULL, NULL, "main", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, pixelBuffer.GetAddressOf(), errorBlob.GetAddressOf());

    if (FAILED(hr))
    {
        std::wstring msg = L"Failed to complie shader : ";

        if (nullptr == errorBlob.Get())
            msg += fileName;
        else
            msg += StringHelper::StringToWideString((char*)errorBlob->GetBufferPointer());

        Log::ErrorMsg(hr, msg);
        return false;
    }

    //�ȼ� ���̴� ����
    hr = pDevice->CreatePixelShader(pixelBuffer.Get()->GetBufferPointer(), pixelBuffer.Get()->GetBufferSize(), NULL, pixelShader.GetAddressOf());

    if (FAILED(hr))
    {
        std::wstring msg = L"Failed to create pixel shader : ";
        msg += fileName;
        Log::ErrorMsg(hr, msg);
        return false;
    }

    return true;
}
