// WinAPI_Chess.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#include <Windows.h>
#include "framework.h"
#include "GameManager.h"
#include "WndClassCreate.h"
#include "resource.h"
//#include "Resource.h"

#define GMMgr GameManager::Get_Instance()


// 전역 변수:
LRESULT CALLBACK WndProc_Main(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;                                // 현재 인스턴스입니다.
LPCTSTR IpszClassMain = TEXT("Chess");
BitMapManager BitMapMgr_Main;


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    // TODO: 여기에 코드를 입력합니다.
    HWND hWnd_Main;
    MSG msg;
    WndClassCreate WndClassMain(hInstance, IpszClassMain, WHITE_BRUSH);
    g_hInst = hInstance;


    //메인 창 등록
    WndClassMain.WndClass.lpfnWndProc = WndProc_Main;	//프로세스 함수 호출
    RegisterClass(&WndClassMain.WndClass);


    hWnd_Main = CreateWindow(IpszClassMain, IpszClassMain, WS_SYSMENU | WS_MINIMIZEBOX, MAIN_X, MAIN_Y, MAIN_W, MAIN_H,
        NULL, (HMENU)NULL, hInstance, NULL);
    
    //메인 and 서브 창 초기화는 여기서
    GMMgr->Init(&BitMapMgr_Main, hWnd_Main);

    ShowWindow(hWnd_Main, nCmdShow);

    //SetForegroundWindow(hWnd_Main); //컴퓨터 그래픽스 ppt 확인

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int) msg.wParam;
}


LRESULT CALLBACK WndProc_Main(HWND hWnd_Main, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    POINT Point;

    switch (message)
    {
    case WM_LBUTTONDOWN:
        Point.x = LOWORD(lParam);
        Point.y = HIWORD(lParam);

        if (GMMgr->ColliderCheck(Point))
            InvalidateRect(hWnd_Main, NULL, true); //이미지를 클릭하면 화면 지우고 다시 그려야 > 시각화

        return 0;
    case WM_PAINT:
        hdc = BeginPaint(hWnd_Main, &ps);
        GMMgr->Draw(hdc, g_hInst);
        EndPaint(hWnd_Main, &ps);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd_Main, message, wParam, lParam);
    }
    return 0;
}