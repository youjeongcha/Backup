#include "WindowContainer.h" //Window.h�� �ȿ��� ��Ŭ��� �ߴ�.

Window::Window() :
	hInstance(NULL),
	hWnd(NULL),
	fullScreen(false)
{
	ZeroMemory(&windowDesc, sizeof(windowDesc));
}

Window::~Window()
{
	//��üȭ���� ��� ������ ������� �ǵ��� �ش�.
	if (fullScreen)
		ChangeDisplaySettings(NULL, 0);

	//â(Windows) ����
	if (hWnd)
	{
		DestroyWindow(hWnd);
		hWnd = NULL;
	}

	//�ν��Ͻ� �ڵ� ����
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
	// WS_CLIPSIBLINGS : Ư�� �ڽ� â�� WM_PAINT �޽����� ������ ������Ʈ�� �ڽ� â�� �������� ��ġ�� �ٸ� ��� �ڽ� â�� Ŭ���մϴ�.
	// WS_CLIPCHILDREN : �θ� â ������ �׸��⸦ ������ �� �ڽ� â�� �����ϴ� ������ ����. �� ��Ÿ���� �θ� â�� ���� �� ���˴ϴ�.
	// WS_POPUP : �˾� â ��Ÿ��, WS_CHILD ��Ÿ�ϰ� �Բ� ����� �� ����. �ݵ�� WNDCLASSEXW.hbrBackground�� �����ؾ� �Ѵ�.
	windowDesc.dwStyle = WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP;
	if (fullScreen)
	{
		// ������� ȭ�� �ػ󵵸� �˾ƿ´�.
		windowDesc.width = GetSystemMetrics(SM_CXSCREEN);
		windowDesc.height = GetSystemMetrics(SM_CYSCREEN);
		screenWidth = windowDesc.width;
		screenHeight = windowDesc.height;

		// ��üȭ�� ��带 ���� ����.
		DEVMODE dmScreenSettings;
		ZeroMemory(&dmScreenSettings, sizeof(dmScreenSettings));

		// ��üȭ���� ��� ���÷��� ��ġ�� ���� �ػ� �ִ� ũ�⸦ �ȼ��� 32��Ʈ ����.
		// ex)1:���, 4:16��, 8:256��, 16:2^15��, 24,31:2^24��.
		// DM_BITSPERPEL : dmBitsPerPel
		// DM_PELSWIDTH : dmPelsWidth
		// DM_PELSHEIGHT : dmPelsHeight
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)windowDesc.width;
		dmScreenSettings.dmPelsHeight = (unsigned long)windowDesc.height;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Full Screen�� �´� ���÷��� �������� ����.
		// CDS : Change Display Settings
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
	}
	else
	{
		// â ����� ��� caption�� system menu�� �߰�.
		windowDesc.dwStyle |= WS_CAPTION | WS_SYSMENU;
		screenWidth = width;
		screenHeight = height;
		RECT rcClient;
		SetRect(&rcClient, 0, 0, width, height);
		// client ������ ������ ũ��� ����� ���� windows ũ�⸦ resize �Ѵ�.
		AdjustWindowRectEx(&rcClient, windowDesc.dwStyle, false, WS_EX_APPWINDOW);
		windowDesc.width = rcClient.right - rcClient.left;
		windowDesc.height = rcClient.bottom - rcClient.top;

		// windows�� ����� �߾ӿ� ��ġ.
		windowDesc.x = (GetSystemMetrics(SM_CXSCREEN) - windowDesc.width) / 2;
		windowDesc.y = (GetSystemMetrics(SM_CYSCREEN) - windowDesc.height) / 2;
	}
} // DescriptionWindow()

void Window::RegisterWindowClass()
{
	WNDCLASSEXW wcex = {
	sizeof(WNDCLASSEX),
	CS_HREDRAW | CS_VREDRAW | CS_OWNDC, // CS_OWNDC : ������ Ŭ������ �� â�� ���� ������ ����̽� ���ؽ�Ʈ�� �Ҵ�.
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
		NULL, // �θ� window �ڵ�.
		NULL, // �޴� �Ǵ� �ڽ� window �ڵ�.
		this->hInstance,
		pContainer); // window ���� �� ������ lParam
	if (!hWnd)
	{
		std::wstring msg = L"Failed to CreateWindowEx : ";
		msg += windowDesc.title;
		Log::ErrorMsg(GetLastError(), msg);
		return false;
	}
	ShowWindow(hWnd, SW_SHOW);
	SetForegroundWindow(hWnd);// �� â(Windows)�� ���� ������ ��ġ.
	SetFocus(hWnd);// �� â(Windows)�� ��Ŀ��.
	return true;
}

LRESULT CALLBACK HandleMsgRedirect(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		// WM_CREATE������ �߻��ϴ� �޽���.
	case WM_NCCREATE:
	{
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		WindowContainer* pContainer = reinterpret_cast<WindowContainer*>(pCreate->lpCreateParams);
		if (!pContainer)
		{
			Log::ErrorMsg("Critical Error : Pointer to window container is null.");
			exit(-1);
		}
		// SetWindowLongPtr : ������ â�� �Ӽ��� ����.
		// GWLP_USERDATA : ����� �����͸� ����, â�� ���� ���� ���α׷����� ����ϱ� ���� ��.
		// GWLP_WNDPROC : ������ ���ν����� ���� ����.
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pContainer));
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(HandleMsgRedirect));
		Log::Output("Window ���� ����.\n");
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
	// �ݱ� ��ư�� ������ ��� ȣ��.
	case WM_CLOSE: PostQuitMessage(0); return 0;
	default:
	{
		// GWLP_USERDATA�� WindowContainer*�� Set �߱� ������ �ش� Ÿ������ Get �� �� �ִ�.
		WindowContainer* const pContainer = reinterpret_cast<WindowContainer*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
		return pContainer->MessageHandler(hWnd, uMsg, wParam, lParam);
	}
	}
}
