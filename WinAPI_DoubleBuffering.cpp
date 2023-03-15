// WinAPI_DoubleBuffering.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#pragma comment(lib, "msimg32.lib")
#include "framework.h"
#include "WinAPI_DoubleBuffering.h"
//#include "BitMapMananger.h"

//#define BitMapMgr BitMapMananger::GetInstance()

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

HBITMAP Chess, Dog; //추가
float g_nX = 0; //추가

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
//BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
//INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void Draw(HWND hWnd, HDC hdc);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINAPIDOUBLEBUFFERING, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);


    //윈도우를 생성하는 별도를 함수를 지니지 않고. hWnd와 핸들을 WinMain에서 생성.
    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_SYSMENU | WS_MINIMIZEBOX,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);


    MSG msg;
    //window가 생성되고 루프문에 들어가기 전에 세팅을 해준다.
    Chess = (HBITMAP)LoadImage(NULL, L"block_w_00.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    Dog = (HBITMAP)LoadImage(NULL, L"00.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

    HDC hdc = GetDC(hWnd);

    //ULONGLONG 꺼질 일 없는 서버의 윈도우즈가 부팅된 이후부터 시간을 저장하고 있어야 하기 때문에
    ULONGLONG checkTime, limitTime = GetTickCount64(); 
    //GetTickCount64(); 
    //윈도우즈가 부팅된 이후부터 시간이 카운팅되는 함수이며 수치는 1ms 단위로 카운팅된다.즉, 윈도우즈 부팅 후 1초가 지났다면 반환 값은 1000이 된다.
    int fps = 1000 / 30; //1초에 30번 화면을 갱신한다.
    float timer = 0; //게임이 시작되고 몇 초가 지났는지 기록이 가능하다.

    // 기본 메시지 루프입니다:
    while (1)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) //기존의 메세지 CheckMessage는 getch()처럼 입력 받을때까지 대기하는 성질이 있어서. 입력을 받지 않으면 false를 리턴하여 다음 작업을 수행하는 PeekMessage를 사용한다.
        {
            if (WM_QUIT == msg.message) break; //PostQuitMessage가 되면 WM_QUIT를 발생시키므로 루프문 안에서 실행이 된다.

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            checkTime = GetTickCount64();
            if (limitTime <= checkTime) //oldClock과 유사. 
            {
                float deltaTime = ((checkTime - limitTime) + fps) * 0.001f; //1000s를 나눠서 second로 단위 변경
                limitTime = checkTime + fps;

                timer += deltaTime;
                if (GetAsyncKeyState(VK_RIGHT))
                {
                    g_nX += 200 * deltaTime; //컴퓨터마다 사양이 다르므로 키를 눌렀을 때 작동하는 시간이 다를 수 있어서 어떤 환경에서든 동일한 시간에 움직일 수 있도록 하기 위해
                }
                if (GetAsyncKeyState(VK_LEFT))
                {
                    g_nX -= 200 * deltaTime;
                }

                //Draw가 매번 호출되면 메모리 소비가 장난 아니기 때문에 몇 ms에 그림을 그릴지 지정
                Draw(hWnd, hdc);
            }
        }
    }

    //메모리 해제 여기서
    DeleteObject(Chess);
    DeleteObject(Dog);

    ReleaseDC(hWnd, hdc);

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPIDOUBLEBUFFERING));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//

//더블 버퍼링
HBITMAP MyCreateDIBSection(HDC hdc, int width, int height)
{
    BITMAPINFO bm_info;
    ZeroMemory(&bm_info.bmiHeader, sizeof(BITMAPINFOHEADER));

    bm_info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    //color bits : 1, 4, 8, 16, 24, 32
    //1:흑백, 4:16색, 8:256색, 16:2^15색, 24,31:2^24색
    bm_info.bmiHeader.biBitCount = 24;
    bm_info.bmiHeader.biWidth = width; //너비, 비트맵의 가로 픽셀 수
    bm_info.bmiHeader.biHeight = height; //높이, 비트맵의 세로 픽셀 수
    bm_info.bmiHeader.biPlanes = 1; //1로 고정, 반드시 1이어야 한다

    LPVOID pBits;

    //DIB(장치 독립적 비트맵, GID 함수를 사용할 수 없다.)를 DDB(장치 종속적 비트맵, GDI 함수를 사용할 수 있다.)처럼 행동할 수 있게 하여 GDI 함수를 사용할 수 있다.
    return CreateDIBSection(hdc, &bm_info, DIB_RGB_COLORS, (void**)&pBits, NULL, 0);
}
//더블 버퍼링
void Draw(HWND hWnd, HDC hdc)
{
    RECT clientRect;
    GetClientRect(hWnd, &clientRect); //윈도우의 클라이언트의 영역을 알려준다.

    HBITMAP backBitmap = MyCreateDIBSection(hdc, clientRect.right + 1, clientRect.bottom + 1);
    HDC backDC = CreateCompatibleDC(hdc);
    SelectObject(backDC, backBitmap);

    HDC memDC = CreateCompatibleDC(hdc);
    HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, Chess);
    TransparentBlt(backDC, 100 + g_nX, 100, 125, 125, memDC, 0, 0, 125, 125, RGB(255, 0, 255));

    SelectObject(memDC, oldBitmap);


    oldBitmap = (HBITMAP)SelectObject(memDC, Dog);

    BitBlt(backDC, 0, 0, 145, 245, memDC, 0, 0, SRCCOPY);
    StretchBlt(backDC, 200, 200, 245, 345, memDC, 0, 0, 145, 245, SRCCOPY);
    SelectObject(memDC, oldBitmap);
    DeleteDC(memDC);

    BitBlt(hdc, 0, 0, clientRect.right + 1, clientRect.bottom + 1, backDC, 0, 0, SRCCOPY);

    DeleteObject(backDC);
    DeleteObject(backBitmap);
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