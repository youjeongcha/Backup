#include "DirectX11Graphics.h"

bool DirectX11Graphics::Initialize(WindowContainer* pWindowContainer)
{
    Window* pWindow = pWindowContainer->GetWindow();
    screenWidth = pWindow->GetScreenWidth();
    screenHeight = pWindow->GetScreenHeight();

    if (!InitializeDirectX(pWindow->GetHWND(), pWindow->IsFullScreen()))
        return false;

    timer = pWindowContainer->GetTimer();

    //정점 버퍼 관련
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
        accel = 5.0f; // Shift Key Down, 이동 5배 가속.
    if (Input::GetKeyboard()->IsUp(VK_SHIFT)) 
        accel = 1.0f;

    // 카메라 상(W)/하(S)/좌(A)/우(D) 이동.
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
    case MouseEventType::WheelVertical: // 카메라 앞(wheel up)/뒤(wheel down) 이동.
    {
        cameraObj.GetTransform()->AdjustPosition(cameraObj.GetTransform()->GetForward() * deltaTime * mouseEvent.y * accel);
        break;
    }
    case MouseEventType::RawMove:
    {
        if (Input::GetMouse()->IsDown(ButtonType::Right)) // 카메라 X,Y 축 회전(마우스 오른쪽 클릭 & 마우스 이동)
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
    float color[4] = { 0.0f, 0.0f, 1.0f, 1.0f }; //파란색.
    // 백 버퍼(백 서피스)를 지운다.
    deviceContext->ClearRenderTargetView(renderTargetView.Get(), color);

    // 3D렌더링 관련
    // 깊이/스텐실 버퍼를 지운다.
    deviceContext->ClearDepthStencilView(depthStencilView.Get(), D3D11_CLEAR_FLAG::D3D11_CLEAR_DEPTH | D3D11_CLEAR_FLAG::D3D11_CLEAR_STENCIL, 1.0f, 0);

    // TODO::여기에 코드 작성

    deviceContext->OMSetDepthStencilState(depthStencilState.Get(), 0);
    /*
    // 정점버퍼 관련
    // 셰이더 적용.
    deviceContext->IASetInputLayout(vertexShader.GetInputLayout());
    deviceContext->VSSetShader(vertexShader.GetShader(), NULL, 0);
    deviceContext->PSSetShader(pixelShader.GetShader(), NULL, 0);
    // 3D 렌더링 관련
    constantMatricesBuffer.data.world = DirectX::XMMatrixIdentity();
    constantMatricesBuffer.data.viewProjection = cameraObj.GetComponent<DXCamera>()->GetViewProjectionMatrix();
    constantMatricesBuffer.ApplyChanges();
    deviceContext->VSSetConstantBuffers(0, 1, constantMatricesBuffer.GetAddressOf());

    //텍스처 매핑 관련
    deviceContext->PSSetShaderResources(0, 1, texture->GetTextureResourceViewAddress());*/
    deviceContext->PSSetSamplers(0, 1, samplerState.GetAddressOf());

    // =====================조명 관련========================
    constantLightBuffer.data.material.ambient = { 1.0f, 1.0f, 1.0f, 1.0f }; // 환경광 (흰색)
   // constantLightBuffer.data.material.diffuse = { 1.0f, 1.0f, 1.0f, 1.0f }; // 난반사광 (흰색)
    constantLightBuffer.data.material.diffuse = { 1.5f, 0.5f, 1.5f, 1.0f }; // 난반사광(주황)
   // constantLightBuffer.data.material.diffuse = { 0.8f, 0.75f, 1.5f, 1.5f }; // 난반사광(파랑)
    constantLightBuffer.data.material.specular = { 1.0f, 1.0f, 1.0f, 1.0f }; // 정반사광 (흰색)
   // constantLightBuffer.data.material.specularPower = 50.0f;
    constantLightBuffer.data.material.specularPower = 10.0f;

    //빛이 비춰지지 않는 면은 새까만 색으로 칠해져, 물체를 구별 할 수 없기 때문에 전역 환경광은 검정(0,0,0)을 사용하지 않는다.
    constantLightBuffer.data.globalAmbient = { 0.1f, 0.1f, 0.1f, 1.0f }; // 전역 환경광(검정색)
    //constantLightBuffer.data.light_color = { 1.0f, 1.0f, 1.0f, 1.0f }; // 빛의 색(흰색)
    constantLightBuffer.data.light_color = { 1.5f, 1.0f, 0.0f, 1.5f }; // 빛의 색(노랑)
    //constantLightBuffer.data.light_color = { 1.5f, 1.0f, 1.0f, 1.5f }; // 빛의 색(보라)
    //XMStoreFloat4(&constantLightBuffer.data.light_direction, XMVector3Normalize(XMVectorSet(1.0f, -1.0f, 1.0f, 0.0f))); // 빛의 방향
    XMStoreFloat4(&constantLightBuffer.data.light_direction, XMVector3Normalize(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f))); // 빛의 방향
    XMStoreFloat4(&constantLightBuffer.data.comPosition, cameraObj.GetTransform()->GetPosition()); // 카메라의 위치.

    if (constantLightBuffer.ApplyChanges())
        deviceContext->PSSetConstantBuffers(0, 1, constantLightBuffer.GetAddressOf());
   
    //=======================================================
    
    // 정점 버퍼 적용.
    //UINT offsets = 0;
    //deviceContext->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), vertexBuffer.StridePtr(), &offsets);
    //deviceContext->IASetVertexBuffers(0, 1, texVertexBuffer.GetAddressOf(), texVertexBuffer.StridePtr(), &offsets);
    //deviceContext->IASetVertexBuffers(0, 1, modelVertexBuffer.GetAddressOf(), modelVertexBuffer.StridePtr(), &offsets);
    // 정점 버퍼를 이용하여 그린다.
    //deviceContext->Draw(vertexBuffer.VertexCount(), 0);

    // 인덱스 버퍼 관련
    // 인덱스 버퍼 적용. DWORD(unsigned long) : R32_UNIT
    //deviceContext->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT::DXGI_FORMAT_R32_UINT, 0);
    // 인덱스 버퍼를 이용하여 그린다.
    //deviceContext->DrawIndexed(indexBuffer.IndexCount(), 0, 0);

    //=======================================================
    
    //Mesh-관련 : 셰이더 적용
    deviceContext->IASetInputLayout(vertexShader.GetInputLayout());
    deviceContext->VSSetShader(vertexShader.GetShader(), NULL, 0);
    deviceContext->PSSetShader(pixelShader.GetShader(), NULL, 0);

    // GameObject Primitive Mesh Draw
    //절두체 컬링 관련
    frustum.ConstructFrustum();
    if (frustum.IsInFrustumBoundsSphere(primitiveObj.GetTransform()->GetPosition(), XMVectorGetX(primitiveObj.GetTransform()->GetScale()/*bounds*/)))
        primitiveObj.Draw(cameraObj.GetComponent<DXCamera>()->GetViewProjectionMatrix());


    swapChain->Present(NULL, NULL);
}

bool DirectX11Graphics::InitializeDirectX(HWND hWnd, bool fullScreen)
{
    try
    {
        // Swap Chain 생성에 사용된 Description 구조체 설정.
        DXGI_SWAP_CHAIN_DESC scd = { 0 };
        scd.BufferDesc.Width = screenWidth; //백 버퍼의 크기 설정.
        scd.BufferDesc.Height = screenHeight;
        scd.BufferDesc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;

        // (0 / 1) : 1초에 최대한 빨리 그리게 한다.
        scd.BufferDesc.RefreshRate.Numerator = 0;
        scd.BufferDesc.RefreshRate.Denominator = 1;

        scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED; //순차 주사 대 비월 주사(지정하지 않음)
        scd.BufferDesc.Scaling = DXGI_MODE_SCALING::DXGI_MODE_SCALING_UNSPECIFIED; //이미지를 모니터에 맞게 확대/축소 하는 방식(지정하지 않음)
    
        // MSAA(Multi Sample Anti Aliasing)를 사용하지 않음
        scd.SampleDesc.Count = 1;
        scd.SampleDesc.Quality = 0;

        scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // 백 버퍼 사용처(용도) 설정.
        scd.BufferCount = 1; // 백 버퍼를 1개 사용.

        scd.OutputWindow = hWnd; // 랜더링이 이루어질 윈도우(의 핸들)를 설정.
        scd.Windowed = !fullScreen;

        scd.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_DISCARD; // 백 버퍼 내용을 사용(present, 화면에 출력)후 내용을 버린다(discard)
        scd.Flags = 0;

        // feature level : 어느 버전의 DirectX를 사용할 것인가.
        // 사양이 낮은 컴퓨터를 지원하기 위하여 하위 버전의 DirectX 버전을 추가.
        D3D_FEATURE_LEVEL featureLevels[] =
        {
            D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0,
            D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0,
            D3D_FEATURE_LEVEL_9_3, D3D_FEATURE_LEVEL_9_2, D3D_FEATURE_LEVEL_9_1
        };
        UINT featureLevelCount = ARRAYSIZE(featureLevels);

        // ========== DirectX11 Device, Device Context, Swap Chain 생성 ==========
        HRESULT hr = D3D11CreateDeviceAndSwapChain(NULL,
            D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE,
            NULL, // D3D_DRIVER_TYPE_SOFTWARE가 아니라면 반드시 NULL 이어야 하고 아니면 NULL이면 안된다.
            NULL, // 런타임 계층에 대한 flags
            featureLevels,
            featureLevelCount,
            D3D11_SDK_VERSION,
            &scd,
            swapChain.GetAddressOf(),
            device.GetAddressOf(),
            NULL, // 지원되는 기능 수준(feature level) output
            deviceContext.GetAddressOf());
        COM_ERROR_IF_FAILED(hr, "Failed to create device and swap chain.");
        // =====================================

        // =========== 백 버퍼 생성 ============
        Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
        // SwapChain을 이용하여 백 버퍼를 가져온다
        hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backBuffer.GetAddressOf()));
        COM_ERROR_IF_FAILED(hr, "Failed to GetBuffer.");
        // 백 버퍼를 RenderTargetView에 연결.
        hr = device->CreateRenderTargetView(backBuffer.Get(), NULL, renderTargetView.GetAddressOf());
        COM_ERROR_IF_FAILED(hr, "Failed to create render target view.");
        // =====================================

        // ============ 뷰포트 설정 ============
        // 뷰포트 설정을 변경하지 않을 경우, 이 작업은 생략 가능.
        CD3D11_VIEWPORT viewport(0.0f, 0.0f, static_cast<float>(screenWidth), static_cast<float>(screenHeight));
        deviceContext->RSSetViewports(1, &viewport); // NumViewports(1) : 뷰 포트의 수.
        // =====================================

        // ========= 래스터라이즈 생성 =========
        // Rasterizer State는 직접 설정하지 않아도 기본적으로 설정되어 있다, 다만 제어 권한이 없다.
        CD3D11_RASTERIZER_DESC rasterDesc(D3D11_DEFAULT);
        //rasterDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID; 면을 색으로 채우기.
        // rasterDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK; 후면 컬링.
        // rasterDesc.FrontCounterClockwise = false; 반시계방향(Counter Clock wise) 그리기를 뒷면으로.
        hr = device->CreateRasterizerState(&rasterDesc, rasterizerState.GetAddressOf());
        COM_ERROR_IF_FAILED(hr, "Failed to create rasterizer state");
        // =====================================

        // =====================================
        // ====== 깊이/스탠실 State 생성 =======
        // 깊이 버퍼 사용O, 스텐실 버퍼 사용X
        CD3D11_DEPTH_STENCIL_DESC depthStencilDesc(D3D11_DEFAULT);
        depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
        hr = device->CreateDepthStencilState(&depthStencilDesc, depthStencilState.GetAddressOf());
        COM_ERROR_IF_FAILED(hr, "Failed to create depth stencil state.");
        // =====================================

        // ======= 깊이/스텐실 버퍼 생성 ========
        // Mip Level : 밉맵, 동일한 그림을 다양한 사이즈로 만드는 것, 랜더링의 속도를 높이고 앨리어싱을 줄여준다.
        CD3D11_TEXTURE2D_DESC depthBufferDesc(DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT, screenWidth, screenHeight);
        depthBufferDesc.MipLevels = 1;
        // 깊이/스텐실 버퍼로 사용할 것이기 때문에 depth/stencil로 bind
        depthBufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;
        hr = device->CreateTexture2D(&depthBufferDesc, NULL, depthStencilBuffer.GetAddressOf());
        COM_ERROR_IF_FAILED(hr, "Failed to create depth stencil buffer.");

        hr = device->CreateDepthStencilView(depthStencilBuffer.Get(), NULL, depthStencilView.GetAddressOf());
        COM_ERROR_IF_FAILED(hr, "Failed to create depth stencil view.");
        // =====================================

        // NumViews(1) : 스왑 체인을 만들 때 백 버퍼를 1개 사용으로 하였기 때문에,
        //               랜더 타겟 뷰 하나만 사용.
        deviceContext->OMSetRenderTargets(1, renderTargetView.GetAddressOf(), depthStencilView.Get());
        deviceContext->RSSetState(rasterizerState.Get());
        deviceContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

        // =====================================
        
        // 텍스처 매핑 관련
        // ========= 샘플러 State 생성 ==========
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
            //정점버퍼 관련(삼각형 그리기)
             //VertexColor(0.0f, 0.1f, 0.0f, 1.0f, 0.0f, 0.0f), // top middle(red)
             //VertexColor(0.1f, -0.1f, 0.0f, 0.0f, 1.0f, 0.0f), // bottom right(green)
             //VertexColor(-0.1f, -0.1f, 0.0f, 0.0f, 1.0f, 1.0f), // bottom left(cyan)

            //인덱스 버퍼 관련(사각형 그리기)
             //VertexColor(-0.3f, 0.3f, 0.0f, 1.0f, 0.0f, 0.0f), // top left(red)
             //VertexColor(0.3f, 0.3f, 0.0f, 0.0f, 1.0f, 0.0f), // top right(green)
             //VertexColor(0.3f, -0.3f, 0.0f, 0.0f, 1.0f, 1.0f), // bottom right(cyan)
             //VertexColor(-0.3f, -0.3f, 0.0f, 1.0f, 1.0f, 0.0f), // bottom left(yellow)

            //3D 렌더링
             //VertexColor(-0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f),  // 0 top far left
             //VertexColor(0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f),   // 1 top far right
             //VertexColor(0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f),  // 2 top near right
             //VertexColor(-0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f), // 3 top near left

             //VertexColor(-0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 1.0f),  // 4 bottom far left
             //VertexColor(0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 1.0f),   // 5 bottom far right
             //VertexColor(0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f),  // 6 bottom near right
             //VertexColor(-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f), // 7 bottom near left

            //텍스처 매핑
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
            //인덱스 버퍼 관련
            //0, 1, 2,
            //0, 2, 3

            //3D 렌더링 관련
            //0,1,2,  0,2,3, // top
            //7,6,5,  7,5,4, // bottom
            //3,2,6,  3,6,7, // front
            //1,0,4,  1,4,5, // back
            //2,1,5,  2,5,6, // right
            //0,3,7,  0,7,4  // left

            // 텍스처 매핑
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

        // 텍스처 매핑
       // texture = std::make_unique<Texture>(device.Get(), "Textures\\box.jpg");
        texture = std::make_unique<Texture>(device.Get(), "Textures\\ink.png");

        // 조명 관련
        hr = constantLightBuffer.Initialize(device.Get(), deviceContext.Get());
        COM_ERROR_IF_FAILED(hr, "Failed to initalize directional light constant buffer.");

        //3D 렌더링 관련
        hr = constantMatricesBuffer.Initialize(device.Get(), deviceContext.Get());
        COM_ERROR_IF_FAILED(hr, "Failed to initalize world/view/projection constant buffer.");
        
        cameraObj.AddComponent<DXCamera>()->SetProjection(screenWidth, screenHeight, 0.1f, 1000.0f);
        cameraObj.GetTransform()->SetPosition({ 0.0f, 1.5f, -3.0f });
        cameraObj.GetTransform()->SetLookAt({ 0.0f, 0.0f, 0.0f });
        */

        //=====================================================
        // Mesh 관련 코드 정리

        // 3D 렌더링 관련
        HRESULT hr = constantMatricesBuffer.Initialize(device.Get(), deviceContext.Get());
        COM_ERROR_IF_FAILED(hr, "Failed to initialize world constant buffer.");

        // 조명 관련
        hr = constantLightBuffer.Initialize(device.Get(), deviceContext.Get());
        COM_ERROR_IF_FAILED(hr, "Failed to initalize directional light constant buffer.");

        // 3D 렌더링 관련
        cameraObj.AddComponent<DXCamera>()->SetProjection(screenWidth, screenHeight, 0.1f, 1000.0f);
        cameraObj.GetTransform()->SetPosition({ 0.0f, 1.5f, -3.0f });
        cameraObj.GetTransform()->SetLookAt({ 0.0f, 0, 0 });

       // primitive = std::make_unique<PrimitiveCube>();
        primitive = std::make_unique<PrimitiveShpher>();
        primitive->Initialize(device.Get(), deviceContext.Get(), constantMatricesBuffer);
        primitive->MakePrimitive();
        primitiveObj.AddComponent<DXMeshRenderer>()->SetModel(primitive.get());

        // =========== 절두체 컬링 =============
        frustum.Initialize(cameraObj.GetComponent<DXCamera>());
    }
    catch (COMException& exception)
    {
        Log::ErrorMsg(exception);
        return false;
    }
    return true;
}
