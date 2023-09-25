#include "WindowContainer.h" //Window.h를 안에서 인클루드 했다.

Window::Window() :
	hInstance(NULL),
	hWnd(NULL),
	fullScreen(false)
{
	ZeroMemory(&windowDesc, sizeof(windowDesc));
}

Window::~Window()
{
	//전체화면일 경우 세팅을 윈도우로 되돌려 준다.
	if (fullScreen)
		ChangeDisplaySettings(NULL, 0);

	//창(Windows) 제거
	if (hWnd)
	{
		DestroyWindow(hWnd);
		hWnd = NULL;
	}

	//인스턴스 핸들 제거
	if (hInstance)
	{
		UnregisterClass(windowDesc.title, hInstance);
		hInstance = NULL;
	}
	pContainer = nullptr;
}

bool Window::Intialize(WindowContainer* pContainer, HINSTANCE hInstance, LPCWSTR title, UINT width, UINT height, bool fullScreen)
{
	this->pContainer = pContainer;
	this->fullScreen = fullScreen;

	DescriptionWindow(title, width, height);
	RegisterWindowClass();
	return CreateAndShowWindow(pContainer);
}

void Window::Processing()
{
	MSG msg;
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}

		if (WM_QUIT == msg.message)
			break;

		if (!pContainer->Update())
			break;

		pContainer->RenderFrame();
	}
}

void Window::DescriptionWindow(LPCWSTR title, UINT width, UINT height)
{
	windowDesc.title = title;
	// WS_CLIPSIBLINGS : 특정 자식 창이 WM_PAINT 메시지를 받으면 업데이트할 자식 창의 영역에서 겹치는 다른 모든 자식 창을 클립합니다.
	// WS_CLIPCHILDREN : 부모 창 내에서 그리기를 수행할 때 자식 창이 차지하는 영역을 제외. 이 스타일은 부모 창을 만들 때 사용됩니다.
	// WS_POPUP : 팝업 창 스타일, WS_CHILD 스타일과 함께 사용할 수 없다. 반드시 WNDCLASSEXW.hbrBackground를 설정해야 한다.
	windowDesc.dwStyle = WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP;
	if (fullScreen)
	{
		// 모니터의 화면 해상도를 알아온다.
		windowDesc.width = GetSystemMetrics(SM_CXSCREEN);
		windowDesc.height = GetSystemMetrics(SM_CYSCREEN);
		screenWidth = windowDesc.width;
		screenHeight = windowDesc.height;

		// 전체화면 모드를 위한 세팅.
		DEVMODE dmScreenSettings;
		ZeroMemory(&dmScreenSettings, sizeof(dmScreenSettings));

		// 전체화면일 경우 디스플레이 장치의 색상 해상도 최대 크기를 픽셀당 32비트 설정.
		// ex)1:흑백, 4:16색, 8:256색, 16:2^15색, 24,31:2^24색.
		// DM_BITSPERPEL : dmBitsPerPel
		// DM_PELSWIDTH : dmPelsWidth
		// DM_PELSHEIGHT : dmPelsHeight
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)windowDesc.width;
		dmScreenSettings.dmPelsHeight = (unsigned long)windowDesc.height;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Full Screen에 맞는 디스플레이 설정으로 변경.
		// CDS : Change Display Settings
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
	}
	else
	{
		// 창 모드일 경우 caption과 system menu를 추가.
		windowDesc.dwStyle |= WS_CAPTION | WS_SYSMENU;
		screenWidth = width;
		screenHeight = height;
		RECT rcClient;
		SetRect(&rcClient, 0, 0, width, height);
		// client 영역을 설정한 크기로 만들기 위해 windows 크기를 resize 한다.
		AdjustWindowRectEx(&rcClient, windowDesc.dwStyle, false, WS_EX_APPWINDOW);
		windowDesc.width = rcClient.right - rcClient.left;
		windowDesc.height = rcClient.bottom - rcClient.top;

		// windows를 모니터 중앙에 배치.
		windowDesc.x = (GetSystemMetrics(SM_CXSCREEN) - windowDesc.width) / 2;
		windowDesc.y = (GetSystemMetrics(SM_CYSCREEN) - windowDesc.height) / 2;
	}
} // DescriptionWindow()

void Window::RegisterWindowClass()
{
	WNDCLASSEXW wcex = {
	sizeof(WNDCLASSEX),
	CS_HREDRAW | CS_VREDRAW | CS_OWNDC, // CS_OWNDC : 윈도우 클래스의 각 창에 대해 고유한 디바이스 컨텍스트를 할당.
	WndProc,
	0, 0,
	this->hInstance,
	LoadIcon(NULL, IDI_WINLOGO),
	LoadCursor(NULL, IDC_ARROW),
	(HBRUSH)GetStockObject(WHITE_BRUSH),
	NULL,
	windowDesc.title,
	LoadIcon(NULL, IDI_WINLOGO) };
	RegisterClassExW(&wcex);

}

bool Window::CreateAndShowWindow(WindowContainer* pContainer)
{
	hWnd = CreateWindowEx(
		WS_EX_APPWINDOW,
		windowDesc.title,
		windowDesc.title,
		windowDesc.dwStyle,
		windowDesc.x, windowDesc.y,
		windowDesc.width, windowDesc.height,
		NULL, // 부모 window 핸들.
		NULL, // 메뉴 또는 자식 window 핸들.
		this->hInstance,
		pContainer); // window 생성 때 보내는 lParam
	if (!hWnd)
	{
		std::wstring msg = L"Failed to CreateWindowEx : ";
		msg += windowDesc.title;
		Log::ErrorMsg(GetLastError(), msg);
		return false;
	}
	ShowWindow(hWnd, SW_SHOW);
	SetForegroundWindow(hWnd);// 이 창(Windows)을 가장 앞으로 위치.
	SetFocus(hWnd);// 이 창(Windows)에 포커스.
	return true;
}

LRESULT CALLBACK HandleMsgRedirect(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		// WM_CREATE이전에 발생하는 메시지.
	case WM_NCCREATE:
	{
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		WindowContainer* pContainer = reinterpret_cast<WindowContainer*>(pCreate->lpCreateParams);
		if (!pContainer)
		{
			Log::ErrorMsg("Critical Error : Pointer to window container is null.");
			exit(-1);
		}
		// SetWindowLongPtr : 지정된 창의 속성을 변경.
		// GWLP_USERDATA : 사용자 데이터를 설정, 창을 만든 응용 프로그램에서 사용하기 위한 것.
		// GWLP_WNDPROC : 윈도우 프로시저를 새로 설정.
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pContainer));
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(HandleMsgRedirect));
		Log::Output("Window 생성 성공.\n");
	}
	default: return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}


HWND Window::GetHWND()
{
	return hWnd;
}

int Window::GetWidth()
{
	return windowDesc.width;
}

int Window::GetHeight()
{
	return windowDesc.height;
}

int Window::GetScreenWidth()
{
	return screenWidth;
}

int Window::GetScreenHeight()
{
	return screenHeight;
}

bool Window::IsFullScreen()
{
	return fullScreen;
}

LRESULT CALLBACK HandleMsgRedirect(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	// 닫기 버튼을 눌렀을 경우 호출.
	case WM_CLOSE: PostQuitMessage(0); return 0;
	default:
	{
		// GWLP_USERDATA를 WindowContainer*로 Set 했기 때문에 해당 타입으로 Get 할 수 있다.
		WindowContainer* const pContainer = reinterpret_cast<WindowContainer*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
		return pContainer->MessageHandler(hWnd, uMsg, wParam, lParam);
	}
	}
}
