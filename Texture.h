#pragma once
//#pragma comment(lib, "DirectXTex.lib")	//아래 include 추가 종속성 설정하지 않으면 라이브러리 찾아줘야 한다.
#include <DirectXTex.h>
#include <wrl/client.h>
#include <d3d11.h>
#include "Color.h"
#include "Log.h"

class Texture
{
private:
	Microsoft::WRL::ComPtr<ID3D11Resource> texture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> textureView;

public:
	Texture(ID3D11Device* device, const Color& color);
	Texture(ID3D11Device* device, const std::string& filename);

	ID3D11ShaderResourceView* GetTextureResourceView();
	ID3D11ShaderResourceView** GetTextureResourceViewAddress();

private:
	bool LoadFromTextureFile(const std::string& filename, DirectX::ScratchImage& scratchImage);
	void InitializeColorTexture(ID3D11Device* device, const Color& color);
};

