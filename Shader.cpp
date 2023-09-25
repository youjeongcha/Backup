#include "Shader.h"

bool VertexShader::Initialize(ID3D11Device* pDevice, std::wstring fileName, D3D11_INPUT_ELEMENT_DESC* layoutDesc, UINT numElements)
{
    Microsoft::WRL::ComPtr<ID3D10Blob> errorBlob, vertexBuffer;
    //정점 셰이더 컴파일, vs_5_0(vertex shader 5.0) DirectX 11에서는 5.0 버전을 사용.
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

    //정점 셰이더 생성
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
    // 픽셀 셰이더 컴파일, ps_5_0(pixel shader 5.f) DirectX 11에서는 5.0 버전을 사용.
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

    //픽셀 셰이더 생성
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
