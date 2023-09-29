#include "Texture.h"

Texture::Texture(ID3D11Device* device, const Color& color)
{
    InitializeColorTexture(device, color);
}

Texture::Texture(ID3D11Device* device, const std::string& filename)
{
    DirectX::ScratchImage image;

    if (LoadFromTextureFile(filename, image))
    {
        HRESULT hr = DirectX::CreateShaderResourceView(device, image.GetImages(), image.GetImageCount(), image.GetMetadata(), textureView.GetAddressOf());
        COM_ERROR_IF_FAILED(hr, "Failed to create shader resource view");
        return;
    }
    InitializeColorTexture(device, Colors::UnhandledTextureColor);
}

ID3D11ShaderResourceView* Texture::GetTextureResourceView()
{
    return textureView.Get();
}

ID3D11ShaderResourceView** Texture::GetTextureResourceViewAddress()
{
    return textureView.GetAddressOf();
}

bool Texture::LoadFromTextureFile(const std::string& filename, DirectX::ScratchImage& scratchImage)
{
    HRESULT hr = E_FAIL;
    std::string extention = StringHelper::GetFileExtention(filename);
    std::wstring w_filename = StringHelper::StringToWideString(filename);

    if ("dds" == extention)
        hr = DirectX::LoadFromDDSFile(w_filename.c_str(), DirectX::DDS_FLAGS_NONE, nullptr, scratchImage);
    else if ("tga" == extention)
        hr = DirectX::LoadFromTGAFile(w_filename.c_str(), nullptr, scratchImage);
    else
        hr = DirectX::LoadFromWICFile(w_filename.c_str(), DirectX::WIC_FLAGS::WIC_FLAGS_NONE, nullptr, scratchImage);

    if (FAILED(hr))
        return false;

    return true;
}

void Texture::InitializeColorTexture(ID3D11Device* device, const Color& color)
{
    CD3D11_TEXTURE2D_DESC texDesc(DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM, 1u, 1u);
    ID3D11Texture2D* p2DTexture = nullptr;
    D3D11_SUBRESOURCE_DATA data = { 0 };
    data.pSysMem = &color;
    data.SysMemPitch = sizeof(Color);
    HRESULT hr = device->CreateTexture2D(&texDesc, &data, &p2DTexture);
    COM_ERROR_IF_FAILED(hr, "Failed to Initialize texture from color data.");

    texture = static_cast<ID3D11Texture2D*>(p2DTexture);
    CD3D11_SHADER_RESOURCE_VIEW_DESC srvDesc(D3D11_SRV_DIMENSION::D3D11_SRV_DIMENSION_TEXTURE2D, texDesc.Format);
    hr = device->CreateShaderResourceView(texture.Get(), &srvDesc, textureView.GetAddressOf());
    COM_ERROR_IF_FAILED(hr, "Failed to create resource view from texture generated from color data.");
}
