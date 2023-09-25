//DirectX 11 Graphics ��ü ����
//DirectX 11 ������� ��(Scene)�� �������ϱ� ���� �׷��Ƚ� ��ü
//ComPtr�� �̿��Ͽ� COM ��ü�� �ڿ�(�޸�) ������ �����ϰ� �Ҵ� �� ������ �� �� �ִ�(COM�� ����Ʈ ������)
#pragma once
#pragma comment(lib, "DXGI.lib")
#pragma comment(lib, "d3d11.lib")
#include <wrl/client.h> // Microsoft::WRL::ComPtr �� ����ϱ� ���� �߰�.
#include <d3d11.h>
#include "WindowContainer.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
//3D������
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
	//3D ������
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthStencilView;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> depthStencilBuffer;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilState;

	//���� ���� ����
	VertexBuffer<VertexColor> vertexBuffer;
	VertexShader vertexShader;
	PixelShader pixelShader;

	//�ε��� ���� ����
	IndexBuffer indexBuffer;

	//3D������ ����
	ConstantBuffer<Matrices> constantMatricesBuffer;
	DXGameObject cameraObj;

public:
	virtual bool Initialize(WindowContainer* pWindowContainer) override;
	virtual void Update() override;
	virtual void RenderFrame() override;

private:
	bool InitializeDirectX(HWND hWnd, bool fullScreen);

	//���� ���� ����
	bool InitializeShader();
	bool InitializeScene();
};

