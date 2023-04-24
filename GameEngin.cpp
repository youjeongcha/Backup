// GameEngin.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "GameEngin.h"
#include "GameManager.h"


#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
//BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
//INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_GAMEENGIN, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);


    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_SYSMENU | WS_MINIMIZEBOX,
        MAIN_X, MAIN_Y, MAIN_W, MAIN_H, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);


    MSG msg;
    HDC m_frontDC = GetDC(hWnd);
    ULONGLONG checkTime, limitTime = GetTickCount64();

    int fps = 1000 / 30; //초당 프레임 수

    //게임 초기화
    GMMgr->Init(hWnd, m_frontDC);


    while (1)
    {
        if (PeekMessage(& msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (WM_QUIT == msg.message)
                break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            checkTime = GetTickCount64(); //5억년 가량의 시간을 카운팅 가능. (서버의 경우 고려가 필요)

            if (limitTime <= checkTime)
            {
                //DeltaTime이란 값은 '각 프레임(하나의 루프) 사이에 걸리는 시간' 
                //만약 ms 단위로 바꾼다면 현재 int 기준으로 작동하던 함수들의 기준 다 바꾸어야 함
                //((18067343 - 18067343) + 33) * 0.001f       사실상 밀리초의 차이가 거의 없다.
                //(checkTime - limitTime)루프에 걸리는 시간까지 더해서 고려해야함
                float deltaTime = ((checkTime - limitTime) + fps) * 0.001f;  //1000ms를 나눠서 second로 단위 변경
                limitTime = checkTime + fps;

                GMMgr->Update(deltaTime);
                GMMgr->Draw(m_frontDC);
            }
        }
    }

    ReleaseDC(hWnd, m_frontDC);

    return (int) msg.wParam;
}



ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GAMEENGIN));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName = NULL;//MAKEINTRESOURCEW(IDC_GAMEENGIN);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}