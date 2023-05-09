#include "WinApiEngine.h"


//���� ����
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

namespace ENGINE
{
	ENGINE::WinApiEngine::WinApiEngine(HINSTANCE hInstance, std::wstring title, INT32 per_x, INT32 per_y, UINT width, UINT height) : isInit(false), title(title), x(0), y(0), width(width), height(height)
	{
		WNDCLASSEXW wcex =
		{
			sizeof(WNDCLASSEX),		//�� ����ü�� ũ��
			CS_HREDRAW | CS_VREDRAW,	//�������� �������, (CS_HREDRAW | CS_VREDRAW : �������� ũ�Ⱑ ����Ǹ� �ٽ� �׸���.
			WndProc,					//������ �޽��� ó���� ����� ���ν���
			0,							//cvClsExtra : Ŭ������ ���� ���� �޸� �Ҵ�
			0,							//cbWndExtra : �����츦 ���� ���� �޸� �Ҵ�. �Ϲ������� ���X
			hInstance,					//�ش� ���ø����̼��� �ν��Ͻ� �ڵ�
			0, 0, 0,					//������, Ŀ��, ������ ���� ����
			NULL,						//�޴� �̸�, �޴��� ��� ���θ� ����
			L"2DEngineWindowClass",	//������ Ŭ���� �̸�, ������ ������ �̿�
			NULL						//���� ������ ����

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
		RegisterClassExW(&wcex); //������ Ŭ������ ���


		HWND hWnd = CreateWindow(
			TEXT("2DEngineWindowClass"), title.c_str(), 
			WS_SYSMENU | WS_MINIMIZEBOX, 
			CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, 
			nullptr, nullptr, hInstance, nullptr);


		if (!hWnd)
			return;

		//�ʱ�ȭ

		RECT rcWindow, rcClient;
		GetWindowRect(hWnd, &rcWindow);
		GetClientRect(hWnd, &rcClient);
		//CreateWindow�� ���ڷ� ���� �ʺ�, ���� ���� ����ũ �� ����� ũ�⸦ ������ ���̱� ������.
		//�� ���� ���� ���Ͽ� ������ ����� ���ϴ� Ŭ���̾�Ʈ �������� �ٽ� �����.
		UINT32 cx = (rcWindow.right - rcWindow.left) - (rcClient.right - rcClient.left);
		UINT32 cy= (rcWindow.bottom - rcWindow.top) - (rcClient.bottom - rcClient.top);

		int screenWidth = GetSystemMetrics(SM_CXFULLSCREEN); //SM_CXFULLSCREEN ��ü ȭ���� �ʺ�
		int screenHeight= GetSystemMetrics(SM_CYFULLSCREEN); //SM_CXFULLSCREEN ��ü ȭ���� ����
		per_x = clamp(per_x, 0, 100); //per_x, per_y �� ������ 0~100 ���̷� ����.
		per_y = clamp(per_y, 0, 100);
		x = per_x * 0.01f * (screenWidth - width); //�����츦 �����(Screen) ������ Ư�� ��ġ�� ����.
		y = per_y * 0.01f * (screenHeight - height);

		MoveWindow(hWnd, x, y, width + cx, height + cy, false); //Window�� ��ġ �� ũ�⸦ �缳��

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
			//�޼��� ť�κ��� �޼����� �������� �Լ�
			if (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
			{
				/*if (WM_QUIT == msg.message)
					break;*/ //�ʿ� X?

				TranslateMessage(&msg); //���� Ű �ڵ带 WM_CHAR���� ��밡���� ���ڷ� ��ȯ.
				DispatchMessage(&msg); //�߻��� �޽����� WndProc()�� �߼�, WndProc()�� ȣ��.
			}
			else
			{
				/*Scene Render*/

				/*
				checkTime = GetTickCount64(); //5��� ������ �ð��� ī���� ����. (������ ��� ����� �ʿ�)
				if (limitTime <= checkTime)
				{
					//DeltaTime�̶� ���� '�� ������(�ϳ��� ����) ���̿� �ɸ��� �ð�' 
					//���� ms ������ �ٲ۴ٸ� ���� int �������� �۵��ϴ� �Լ����� ���� �� �ٲپ�� ��
					//((18067343 - 18067343) + 33) * 0.001f       ��ǻ� �и����� ���̰� ���� ����.
					//(checkTime - limitTime)������ �ɸ��� �ð����� ���ؼ� ����ؾ���
					float deltaTime = ((checkTime - limitTime) + fps) * 0.001f; //1000ms�� ������ second�� ���� ����
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