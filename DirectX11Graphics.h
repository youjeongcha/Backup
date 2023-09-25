//DirectX 11 Graphics 객체 생성
//DirectX 11 기반으로 씬(Scene)을 렌더링하기 위한 그래픽스 객체
//ComPtr을 이용하여 COM 객체의 자원(메모리) 관리를 안전하게 할당 및 해제를 할 수 있다(COM용 스마트 포인터)
#pragma once
#pragma comment(lib, "DXGI.lib")
#pragma comment(lib, "d3d11.lib")
#include <wrl/client.h> // Microsoft::WRL::ComPtr 를 사용하기 위해 추가.
#include <d3d11.h>
#include "WindowContainer.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
//3D렌더링
#include "ConstantBuffer.h"
#include "DXGameObject.h"
#include "Components/DXCamera.h"

class DirectX11Graphics final : public Graphics
{
private:
	Timer* timer = nullptr;
	Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;
	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerState;
	//3D 렌더링
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthStencilView;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> depthStencilBuffer;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilState;

	//정점 버퍼 관련
	VertexBuffer<VertexColor> vertexBuffer;
	VertexShader vertexShader;
	PixelShader pixelShader;

	//인덱스 버퍼 관련
	IndexBuffer indexBuffer;

	//3D렌더링 관련
	ConstantBuffer<Matrices> constantMatricesBuffer;
	DXGameObject cameraObj;

public:
	virtual bool Initialize(WindowContainer* pWindowContainer) override;
	virtual void Update() override;
	virtual void RenderFrame() override;

private:
	bool InitializeDirectX(HWND hWnd, bool fullScreen);

	//정점 버퍼 관련
	bool InitializeShader();
	bool InitializeScene();
};

