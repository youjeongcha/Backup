#include "DirectX11Graphics.h"

bool DirectX11Graphics::Initialize(WindowContainer* pWindowContainer)
{
    Window* pWindow = pWindowContainer->GetWindow();
    screenWidth = pWindow->GetScreenWidth();
    screenHeight = pWindow->GetScreenHeight();

    if (!InitializeDirectX(pWindow->GetHWND(), pWindow->IsFullScreen()))
        return false;

    timer = pWindowContainer->GetTimer();

    //���� ���� ����
    if (!InitializeShader())
        return false;
    if (!InitializeScene())
        return false;

    return true;
}

void DirectX11Graphics::Update()
{
    static float accel = 1.0f;
    const float deltaTime = timer->GetMilisecondsElapesed();

    if (Input::GetKeyboard()->IsDown(VK_SHIFT)) 
        accel = 5.0f; // Shift Key Down, �̵� 5�� ����.
    if (Input::GetKeyboard()->IsUp(VK_SHIFT)) 
        accel = 1.0f;

    // ī�޶� ��(W)/��(S)/��(A)/��(D) �̵�.
    if (Input::GetKeyboard()->IsPressed('D')) 
        cameraObj.GetTransform()->AdjustPosition(cameraObj.GetTransform()->GetRight() * deltaTime * 0.01f * accel);
    if (Input::GetKeyboard()->IsPressed('A')) 
        cameraObj.GetTransform()->AdjustPosition(-cameraObj.GetTransform()->GetRight() * deltaTime * 0.01f * accel);
    if (Input::GetKeyboard()->IsPressed('W')) 
        cameraObj.GetTransform()->AdjustPosition(cameraObj.GetTransform()->GetUp() * deltaTime * 0.01f * accel);
    if (Input::GetKeyboard()->IsPressed('S')) 
        cameraObj.GetTransform()->AdjustPosition(-cameraObj.GetTransform()->GetUp() * deltaTime * 0.01f * accel);

    MouseEvent mouseEvent = Input::GetMouse()->ReadEvent();

    switch (mouseEvent.eventType)
    {
    case MouseEventType::WheelVertical: // ī�޶� ��(wheel up)/��(wheel down) �̵�.
    {
        cameraObj.GetTransform()->AdjustPosition(cameraObj.GetTransform()->GetForward() * deltaTime * mouseEvent.y * accel);
        break;
    }
    case MouseEventType::RawMove:
    {
        if (Input::GetMouse()->IsDown(ButtonType::Right)) // ī�޶� X,Y �� ȸ��(���콺 ������ Ŭ�� & ���콺 �̵�)
        {
            XMVECTOR v = XMVectorSet(mouseEvent.y, mouseEvent.x, 0.0f, 0.0f) * deltaTime * 0.1f;
            cameraObj.GetTransform()->AdjustRotation(v);
        }
        break;
    }
    }

}

void DirectX11Graphics::RenderFrame()
{
    float color[4] = { 0.0f, 0.0f, 1.0f, 1.0f }; //�Ķ���.
    // �� ����(�� ���ǽ�)�� �����.
    deviceContext->ClearRenderTargetView(renderTargetView.Get(), color);

    // 3D������ ����
    // ����/���ٽ� ���۸� �����.
    deviceContext->ClearDepthStencilView(depthStencilView.Get(), D3D11_CLEAR_FLAG::D3D11_CLEAR_DEPTH | D3D11_CLEAR_FLAG::D3D11_CLEAR_STENCIL, 1.0f, 0);

    // TODO::���⿡ �ڵ� �ۼ�

    deviceContext->OMSetDepthStencilState(depthStencilState.Get(), 0);
    /*
    // �������� ����
    // ���̴� ����.
    deviceContext->IASetInputLayout(vertexShader.GetInputLayout());
    deviceContext->VSSetShader(vertexShader.GetShader(), NULL, 0);
    deviceContext->PSSetShader(pixelShader.GetShader(), NULL, 0);
    // 3D ������ ����
    constantMatricesBuffer.data.world = DirectX::XMMatrixIdentity();
    constantMatricesBuffer.data.viewProjection = cameraObj.GetComponent<DXCamera>()->GetViewProjectionMatrix();
    constantMatricesBuffer.ApplyChanges();
    deviceContext->VSSetConstantBuffers(0, 1, constantMatricesBuffer.GetAddressOf());

    //�ؽ�ó ���� ����
    deviceContext->PSSetShaderResources(0, 1, texture->GetTextureResourceViewAddress());*/
    deviceContext->PSSetSamplers(0, 1, samplerState.GetAddressOf());

    // =====================���� ����========================
    constantLightBuffer.data.material.ambient = { 1.0f, 1.0f, 1.0f, 1.0f }; // ȯ�汤 (���)
   // constantLightBuffer.data.material.diffuse = { 1.0f, 1.0f, 1.0f, 1.0f }; // ���ݻ籤 (���)
    constantLightBuffer.data.material.diffuse = { 1.5f, 0.5f, 1.5f, 1.0f }; // ���ݻ籤(��Ȳ)
   // constantLightBuffer.data.material.diffuse = { 0.8f, 0.75f, 1.5f, 1.5f }; // ���ݻ籤(�Ķ�)
    constantLightBuffer.data.material.specular = { 1.0f, 1.0f, 1.0f, 1.0f }; // ���ݻ籤 (���)
   // constantLightBuffer.data.material.specularPower = 50.0f;
    constantLightBuffer.data.material.specularPower = 10.0f;

    //���� �������� �ʴ� ���� ��� ������ ĥ����, ��ü�� ���� �� �� ���� ������ ���� ȯ�汤�� ����(0,0,0)�� ������� �ʴ´�.
    constantLightBuffer.data.globalAmbient = { 0.1f, 0.1f, 0.1f, 1.0f }; // ���� ȯ�汤(������)
    //constantLightBuffer.data.light_color = { 1.0f, 1.0f, 1.0f, 1.0f }; // ���� ��(���)
    constantLightBuffer.data.light_color = { 1.5f, 1.0f, 0.0f, 1.5f }; // ���� ��(���)
    //constantLightBuffer.data.light_color = { 1.5f, 1.0f, 1.0f, 1.5f }; // ���� ��(����)
    //XMStoreFloat4(&constantLightBuffer.data.light_direction, XMVector3Normalize(XMVectorSet(1.0f, -1.0f, 1.0f, 0.0f))); // ���� ����
    XMStoreFloat4(&constantLightBuffer.data.light_direction, XMVector3Normalize(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f))); // ���� ����
    XMStoreFloat4(&constantLightBuffer.data.comPosition, cameraObj.GetTransform()->GetPosition()); // ī�޶��� ��ġ.

    if (constantLightBuffer.ApplyChanges())
        deviceContext->PSSetConstantBuffers(0, 1, constantLightBuffer.GetAddressOf());
   
    //=======================================================
    
    // ���� ���� ����.
    //UINT offsets = 0;
    //deviceContext->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), vertexBuffer.StridePtr(), &offsets);
    //deviceContext->IASetVertexBuffers(0, 1, texVertexBuffer.GetAddressOf(), texVertexBuffer.StridePtr(), &offsets);
    //deviceContext->IASetVertexBuffers(0, 1, modelVertexBuffer.GetAddressOf(), modelVertexBuffer.StridePtr(), &offsets);
    // ���� ���۸� �̿��Ͽ� �׸���.
    //deviceContext->Draw(vertexBuffer.VertexCount(), 0);

    // �ε��� ���� ����
    // �ε��� ���� ����. DWORD(unsigned long) : R32_UNIT
    //deviceContext->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT::DXGI_FORMAT_R32_UINT, 0);
    // �ε��� ���۸� �̿��Ͽ� �׸���.
    //deviceContext->DrawIndexed(indexBuffer.IndexCount(), 0, 0);

    //=======================================================
    
    //Mesh-���� : ���̴� ����
    deviceContext->IASetInputLayout(vertexShader.GetInputLayout());
    deviceContext->VSSetShader(vertexShader.GetShader(), NULL, 0);
    deviceContext->PSSetShader(pixelShader.GetShader(), NULL, 0);

    // GameObject Primitive Mesh Draw
    //����ü �ø� ����
    frustum.ConstructFrustum();
    if (frustum.IsInFrustumBoundsSphere(primitiveObj.GetTransform()->GetPosition(), XMVectorGetX(primitiveObj.GetTransform()->GetScale()/*bounds*/)))
        primitiveObj.Draw(cameraObj.GetComponent<DXCamera>()->GetViewProjectionMatrix());


    swapChain->Present(NULL, NULL);
}

bool DirectX11Graphics::InitializeDirectX(HWND hWnd, bool fullScreen)
{
    try
    {
        // Swap Chain ������ ���� Description ����ü ����.
        DXGI_SWAP_CHAIN_DESC scd = { 0 };
        scd.BufferDesc.Width = screenWidth; //�� ������ ũ�� ����.
        scd.BufferDesc.Height = screenHeight;
        scd.BufferDesc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;

        // (0 / 1) : 1�ʿ� �ִ��� ���� �׸��� �Ѵ�.
        scd.BufferDesc.RefreshRate.Numerator = 0;
        scd.BufferDesc.RefreshRate.Denominator = 1;

        scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED; //���� �ֻ� �� ��� �ֻ�(�������� ����)
        scd.BufferDesc.Scaling = DXGI_MODE_SCALING::DXGI_MODE_SCALING_UNSPECIFIED; //�̹����� ����Ϳ� �°� Ȯ��/��� �ϴ� ���(�������� ����)
    
        // MSAA(Multi Sample Anti Aliasing)�� ������� ����
        scd.SampleDesc.Count = 1;
        scd.SampleDesc.Quality = 0;

        scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // �� ���� ���ó(�뵵) ����.
        scd.BufferCount = 1; // �� ���۸� 1�� ���.

        scd.OutputWindow = hWnd; // �������� �̷���� ������(�� �ڵ�)�� ����.
        scd.Windowed = !fullScreen;

        scd.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_DISCARD; // �� ���� ������ ���(present, ȭ�鿡 ���)�� ������ ������(discard)
        scd.Flags = 0;

        // feature level : ��� ������ DirectX�� ����� ���ΰ�.
        // ����� ���� ��ǻ�͸� �����ϱ� ���Ͽ� ���� ������ DirectX ������ �߰�.
        D3D_FEATURE_LEVEL featureLevels[] =
        {
            D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0,
            D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0,
            D3D_FEATURE_LEVEL_9_3, D3D_FEATURE_LEVEL_9_2, D3D_FEATURE_LEVEL_9_1
        };
        UINT featureLevelCount = ARRAYSIZE(featureLevels);

        // ========== DirectX11 Device, Device Context, Swap Chain ���� ==========
        HRESULT hr = D3D11CreateDeviceAndSwapChain(NULL,
            D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE,
            NULL, // D3D_DRIVER_TYPE_SOFTWARE�� �ƴ϶�� �ݵ�� NULL �̾�� �ϰ� �ƴϸ� NULL�̸� �ȵȴ�.
            NULL, // ��Ÿ�� ������ ���� flags
            featureLevels,
            featureLevelCount,
            D3D11_SDK_VERSION,
            &scd,
            swapChain.GetAddressOf(),
            device.GetAddressOf(),
            NULL, // �����Ǵ� ��� ����(feature level) output
            deviceContext.GetAddressOf());
        COM_ERROR_IF_FAILED(hr, "Failed to create device and swap chain.");
        // =====================================

        // =========== �� ���� ���� ============
        Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
        // SwapChain�� �̿��Ͽ� �� ���۸� �����´�
        hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backBuffer.GetAddressOf()));
        COM_ERROR_IF_FAILED(hr, "Failed to GetBuffer.");
        // �� ���۸� RenderTargetView�� ����.
        hr = device->CreateRenderTargetView(backBuffer.Get(), NULL, renderTargetView.GetAddressOf());
        COM_ERROR_IF_FAILED(hr, "Failed to create render target view.");
        // =====================================

        // ============ ����Ʈ ���� ============
        // ����Ʈ ������ �������� ���� ���, �� �۾��� ���� ����.
        CD3D11_VIEWPORT viewport(0.0f, 0.0f, static_cast<float>(screenWidth), static_cast<float>(screenHeight));
        deviceContext->RSSetViewports(1, &viewport); // NumViewports(1) : �� ��Ʈ�� ��.
        // =====================================

        // ========= �����Ͷ����� ���� =========
        // Rasterizer State�� ���� �������� �ʾƵ� �⺻������ �����Ǿ� �ִ�, �ٸ� ���� ������ ����.
        CD3D11_RASTERIZER_DESC rasterDesc(D3D11_DEFAULT);
        //rasterDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID; ���� ������ ä���.
        // rasterDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK; �ĸ� �ø�.
        // rasterDesc.FrontCounterClockwise = false; �ݽð����(Counter Clock wise) �׸��⸦ �޸�����.
        hr = device->CreateRasterizerState(&rasterDesc, rasterizerState.GetAddressOf());
        COM_ERROR_IF_FAILED(hr, "Failed to create rasterizer state");
        // =====================================

        // =====================================
        // ====== ����/���Ľ� State ���� =======
        // ���� ���� ���O, ���ٽ� ���� ���X
        CD3D11_DEPTH_STENCIL_DESC depthStencilDesc(D3D11_DEFAULT);
        depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
        hr = device->CreateDepthStencilState(&depthStencilDesc, depthStencilState.GetAddressOf());
        COM_ERROR_IF_FAILED(hr, "Failed to create depth stencil state.");
        // =====================================

        // ======= ����/���ٽ� ���� ���� ========
        // Mip Level : �Ӹ�, ������ �׸��� �پ��� ������� ����� ��, �������� �ӵ��� ���̰� �ٸ������ �ٿ��ش�.
        CD3D11_TEXTURE2D_DESC depthBufferDesc(DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT, screenWidth, screenHeight);
        depthBufferDesc.MipLevels = 1;
        // ����/���ٽ� ���۷� ����� ���̱� ������ depth/stencil�� bind
        depthBufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;
        hr = device->CreateTexture2D(&depthBufferDesc, NULL, depthStencilBuffer.GetAddressOf());
        COM_ERROR_IF_FAILED(hr, "Failed to create depth stencil buffer.");

        hr = device->CreateDepthStencilView(depthStencilBuffer.Get(), NULL, depthStencilView.GetAddressOf());
        COM_ERROR_IF_FAILED(hr, "Failed to create depth stencil view.");
        // =====================================

        // NumViews(1) : ���� ü���� ���� �� �� ���۸� 1�� ������� �Ͽ��� ������,
        //               ���� Ÿ�� �� �ϳ��� ���.
        deviceContext->OMSetRenderTargets(1, renderTargetView.GetAddressOf(), depthStencilView.Get());
        deviceContext->RSSetState(rasterizerState.Get());
        deviceContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

        // =====================================
        
        // �ؽ�ó ���� ����
        // ========= ���÷� State ���� ==========
        CD3D11_SAMPLER_DESC samplerDesc(D3D11_DEFAULT);
        samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
        samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
        samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
        hr = device->CreateSamplerState(&samplerDesc, samplerState.GetAddressOf());
        COM_ERROR_IF_FAILED(hr, "Failed to create sampler state.");

        // =====================================


    } // try
    catch (COMException& exception)
    {
        Log::ErrorMsg(exception);
        return false;
    }

    return true;
}

bool DirectX11Graphics::InitializeShader()
{
    D3D11_INPUT_ELEMENT_DESC inputLayout[] = {
        { "POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0 },
        {"TEXCOORD", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0 },
        {"NORMAL", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0 }
    };

    UINT numElements = ARRAYSIZE(inputLayout);
    //if (!vertexShader.Initialize(device.Get(), L"color.vs.hlsl", inputLayout, numElements))
    //if (!vertexShader.Initialize(device.Get(), L"texture.vs.hlsl", inputLayout, numElements))
    if (!vertexShader.Initialize(device.Get(), L"light.vs.hlsl", inputLayout, numElements))
        return false;
   // if (!pixelShader.Initialize(device.Get(), L"color.ps.hlsl"))
    //if (!pixelShader.Initialize(device.Get(), L"texture.ps.hlsl"))
    if (!pixelShader.Initialize(device.Get(), L"light.ps.hlsl"))
        return false;
    return true;
}

bool DirectX11Graphics::InitializeScene()
{
    try
    {
        //VertexColor vertices[] = {
        //VertexTexture vertices[] = {
        /*
        ModelVertex vertices[] = {
            //�������� ����(�ﰢ�� �׸���)
             //VertexColor(0.0f, 0.1f, 0.0f, 1.0f, 0.0f, 0.0f), // top middle(red)
             //VertexColor(0.1f, -0.1f, 0.0f, 0.0f, 1.0f, 0.0f), // bottom right(green)
             //VertexColor(-0.1f, -0.1f, 0.0f, 0.0f, 1.0f, 1.0f), // bottom left(cyan)

            //�ε��� ���� ����(�簢�� �׸���)
             //VertexColor(-0.3f, 0.3f, 0.0f, 1.0f, 0.0f, 0.0f), // top left(red)
             //VertexColor(0.3f, 0.3f, 0.0f, 0.0f, 1.0f, 0.0f), // top right(green)
             //VertexColor(0.3f, -0.3f, 0.0f, 0.0f, 1.0f, 1.0f), // bottom right(cyan)
             //VertexColor(-0.3f, -0.3f, 0.0f, 1.0f, 1.0f, 0.0f), // bottom left(yellow)

            //3D ������
             //VertexColor(-0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f),  // 0 top far left
             //VertexColor(0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f),   // 1 top far right
             //VertexColor(0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f),  // 2 top near right
             //VertexColor(-0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f), // 3 top near left

             //VertexColor(-0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 1.0f),  // 4 bottom far left
             //VertexColor(0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 1.0f),   // 5 bottom far right
             //VertexColor(0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f),  // 6 bottom near right
             //VertexColor(-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f), // 7 bottom near left

            //�ؽ�ó ����
             ModelVertex(-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,     -0.5f, 0.5f, 0.5f),   // 0 top far left
             ModelVertex(0.5f, 0.5f, 0.5f, 1.0f, 0.0f,      0.5f, 0.5f, 0.5f),    // 1 top far right
             ModelVertex(0.5f, 0.5f, -0.5f, 1.0f, 1.0f,     0.5f, 0.5f, -0.5f),   // 2 top near right
             ModelVertex(-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,     -0.5f, 0.5f, -0.5f),  // 3 top near left

             ModelVertex(-0.5f, -0.5f, 0.5f, 0.0f, 1.0f,    -0.5f, -0.5f, 0.5f),  // 4 bottom far left
             ModelVertex(0.5f, -0.5f, 0.5f, 1.0f, 1.0f,    0.5f, -0.5f, 0.5f),   // 5 bottom far right
             ModelVertex(0.5f, -0.5f, -0.5f, 1.0f, 0.0f,    0.5f, -0.5f, -0.5f),  // 6 bottom near right
             ModelVertex(-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,    -0.5f, -0.5f, -0.5f), // 7 bottom near left

             ModelVertex(0.5f, -0.5f, 0.5f, 0.0f, 0.0f,    0.5f, -0.5f, 0.5f),   // 8 other bottom far right
             ModelVertex(0.5f, -0.5f, -0.5f, 0.0f, 1.0f,    0.5f, -0.5f, 0.5f),  // 9 other bottom near right
             ModelVertex(-0.5f, -0.5f, -0.5f, 1.0f, 1.0f,    -0.5f, -0.5f, -0.5f), // 10 other bottom near left
             ModelVertex(-0.5f, -0.5f, 0.5f, 1.0f, 0.0f,    -0.5f, -0.5f, 0.5f),  // 11 other bottom far left
        };
        UINT vertexCount = ARRAYSIZE(vertices);
       // HRESULT hr = vertexBuffer.Initialize(device.Get(), vertices, vertexCount);
       // HRESULT hr = texVertexBuffer.Initialize(device.Get(), vertices, vertexCount);
        HRESULT hr = modelVertexBuffer.Initialize(device.Get(), vertices, vertexCount);
        COM_ERROR_IF_FAILED(hr, "Failed to initialize vertex buffer.");

        
        DWORD indices[] =
        {
            //�ε��� ���� ����
            //0, 1, 2,
            //0, 2, 3

            //3D ������ ����
            //0,1,2,  0,2,3, // top
            //7,6,5,  7,5,4, // bottom
            //3,2,6,  3,6,7, // front
            //1,0,4,  1,4,5, // back
            //2,1,5,  2,5,6, // right
            //0,3,7,  0,7,4  // left

            // �ؽ�ó ����
            0,1,2,  0,2,3, // top
            7,6,5,  7,5,4, // bottom
            3,2,6,  3,6,7, // front
            1,0,4,  1,4,5, // back
            2,1,8,  2,8,9, // right
            0,3,10,  0,10,11  // left
        };

        UINT indexCount ARRAYSIZE(indices);
        hr = indexBuffer.Initialize(device.Get(), indices, indexCount);
        COM_ERROR_IF_FAILED(hr, "Failed to initialize index buffer");

        // �ؽ�ó ����
       // texture = std::make_unique<Texture>(device.Get(), "Textures\\box.jpg");
        texture = std::make_unique<Texture>(device.Get(), "Textures\\ink.png");

        // ���� ����
        hr = constantLightBuffer.Initialize(device.Get(), deviceContext.Get());
        COM_ERROR_IF_FAILED(hr, "Failed to initalize directional light constant buffer.");

        //3D ������ ����
        hr = constantMatricesBuffer.Initialize(device.Get(), deviceContext.Get());
        COM_ERROR_IF_FAILED(hr, "Failed to initalize world/view/projection constant buffer.");
        
        cameraObj.AddComponent<DXCamera>()->SetProjection(screenWidth, screenHeight, 0.1f, 1000.0f);
        cameraObj.GetTransform()->SetPosition({ 0.0f, 1.5f, -3.0f });
        cameraObj.GetTransform()->SetLookAt({ 0.0f, 0.0f, 0.0f });
        */

        //=====================================================
        // Mesh ���� �ڵ� ����

        // 3D ������ ����
        HRESULT hr = constantMatricesBuffer.Initialize(device.Get(), deviceContext.Get());
        COM_ERROR_IF_FAILED(hr, "Failed to initialize world constant buffer.");

        // ���� ����
        hr = constantLightBuffer.Initialize(device.Get(), deviceContext.Get());
        COM_ERROR_IF_FAILED(hr, "Failed to initalize directional light constant buffer.");

        // 3D ������ ����
        cameraObj.AddComponent<DXCamera>()->SetProjection(screenWidth, screenHeight, 0.1f, 1000.0f);
        cameraObj.GetTransform()->SetPosition({ 0.0f, 1.5f, -3.0f });
        cameraObj.GetTransform()->SetLookAt({ 0.0f, 0, 0 });

       // primitive = std::make_unique<PrimitiveCube>();
        primitive = std::make_unique<PrimitiveShpher>();
        primitive->Initialize(device.Get(), deviceContext.Get(), constantMatricesBuffer);
        primitive->MakePrimitive();
        primitiveObj.AddComponent<DXMeshRenderer>()->SetModel(primitive.get());

        // =========== ����ü �ø� =============
        frustum.Initialize(cameraObj.GetComponent<DXCamera>());
    }
    catch (COMException& exception)
    {
        Log::ErrorMsg(exception);
        return false;
    }
    return true;
}
