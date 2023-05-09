#include "WinApiEngine.h"


//전방 선언
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

namespace ENGINE
{
	ENGINE::WinApiEngine::WinApiEngine(HINSTANCE hInstance, std::wstring title, INT32 per_x, INT32 per_y, UINT width, UINT height) : isInit(false), title(title), x(0), y(0), width(width), height(height)
	{
		WNDCLASSEXW wcex =
		{
			sizeof(WNDCLASSEX),		//이 구조체의 크기
			CS_HREDRAW | CS_VREDRAW,	//윈도우의 출력형태, (CS_HREDRAW | CS_VREDRAW : 윈도우의 크기가 변경되면 다시 그린다.
			WndProc,					//윈도우 메시지 처리에 사용할 프로시저
			0,							//cvClsExtra : 클래스를 위한 여분 메모리 할당
			0,							//cbWndExtra : 윈도우를 위한 여분 메모리 할당. 일반적으로 사용X
			hInstance,					//해당 어플리케이션의 인스턴스 핸들
			0, 0, 0,					//아이콘, 커서, 윈도우 배경색 설정
			NULL,						//메뉴 이름, 메뉴의 사용 여부를 결정
			L"2DEngineWindowClass",	//윈도우 클래스 이름, 윈도우 생성시 이용
			NULL						//작은 아이콘 설정

			/*wcex.cbSize = sizeof(WNDCLASSEX);

			wcex.style          = CS_HREDRAW | CS_VREDRAW;
			wcex.lpfnWndProc    = WndProc;
			wcex.cbClsExtra     = 0;
			wcex.cbWndExtra     = 0;
			wcex.hInstance      = hInstance;
			wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPICIRCUSCHARLIE));
			wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
			//wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
			wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
			wcex.lpszMenuName = NULL;   //MAKEINTRESOURCEW(IDC_WINAPICIRCUSCHARLIE);
			wcex.lpszClassName = szWindowClass;
			wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
			*/
		};
		RegisterClassExW(&wcex); //윈도우 클래스를 등록


		HWND hWnd = CreateWindow(
			TEXT("2DEngineWindowClass"), title.c_str(), 
			WS_SYSMENU | WS_MINIMIZEBOX, 
			CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, 
			nullptr, nullptr, hInstance, nullptr);


		if (!hWnd)
			return;

		//초기화

		RECT rcWindow, rcClient;
		GetWindowRect(hWnd, &rcWindow);
		GetClientRect(hWnd, &rcClient);
		//CreateWindow의 인자로 들어가는 너비, 높이 값은 데스크 바 등등의 크기를 포함한 값이기 때문에.
		//그 차이 값을 구하여 윈도우 사이즈를 원하는 클라이언트 영역으로 다시 만든다.
		UINT32 cx = (rcWindow.right - rcWindow.left) - (rcClient.right - rcClient.left);
		UINT32 cy= (rcWindow.bottom - rcWindow.top) - (rcClient.bottom - rcClient.top);

		int screenWidth = GetSystemMetrics(SM_CXFULLSCREEN); //SM_CXFULLSCREEN 전체 화면의 너비
		int screenHeight= GetSystemMetrics(SM_CYFULLSCREEN); //SM_CXFULLSCREEN 전체 화면의 높이
		per_x = clamp(per_x, 0, 100); //per_x, per_y 값 범위를 0~100 사이로 제한.
		per_y = clamp(per_y, 0, 100);
		x = per_x * 0.01f * (screenWidth - width); //윈도우를 모니터(Screen) 범위의 특정 위치로 변경.
		y = per_y * 0.01f * (screenHeight - height);

		MoveWindow(hWnd, x, y, width + cx, height + cy, false); //Window의 위치 및 크기를 재설정

		ShowWindow(hWnd, SW_SHOWDEFAULT);
		UpdateWindow(hWnd);

		srand((unsigned)time(NULL));
		/*Scene iInitialized*/

		isInit = TRUE;
	}

	WinApiEngine::~WinApiEngine() { Release(); }

	int WinApiEngine::Run()
	{
		if (!isInit)
			return -1;

		MSG msg;
		ZeroMemory(&msg, sizeof(msg));
		
		while (WM_QUIT != msg.message) //Game Loop
		{
			//메세지 큐로부터 메세지를 가져오는 함수
			if (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
			{
				/*if (WM_QUIT == msg.message)
					break;*/ //필요 X?

				TranslateMessage(&msg); //가상 키 코드를 WM_CHAR에서 사용가능한 문자로 변환.
				DispatchMessage(&msg); //발생한 메시지를 WndProc()에 발송, WndProc()가 호출.
			}
			else
			{
				/*Scene Render*/

				/*
				checkTime = GetTickCount64(); //5억년 가량의 시간을 카운팅 가능. (서버의 경우 고려가 필요)
				if (limitTime <= checkTime)
				{
					//DeltaTime이란 값은 '각 프레임(하나의 루프) 사이에 걸리는 시간' 
					//만약 ms 단위로 바꾼다면 현재 int 기준으로 작동하던 함수들의 기준 다 바꾸어야 함
					//((18067343 - 18067343) + 33) * 0.001f       사실상 밀리초의 차이가 거의 없다.
					//(checkTime - limitTime)루프에 걸리는 시간까지 더해서 고려해야함
					float deltaTime = ((checkTime - limitTime) + fps) * 0.001f; //1000ms를 나눠서 second로 단위 변경
					limitTime = checkTime + fps;


					GMMgr->Update(deltaTime);
					GMMgr->Draw();
					*/
			}
		}
		Release();
		return (int)msg.wParam;
	}

	void WinApiEngine::Release()
	{
		/* Scene Destory */
	}
} //namespace ENGINE

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM IParam)
{
	switch (iMessage)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return(DefWindowProc(hWnd, iMessage, wParam, IParam));
	}

	return 0;
}