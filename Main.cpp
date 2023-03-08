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
LRESULT CALLBACK WndProc_Sub(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProc_Sub_Promotion(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;                                // 현재 인스턴스입니다.
LPCTSTR IpszClassMain = TEXT("Chess");
LPCTSTR IpszClassSub = TEXT("Turn");
LPCTSTR IpszClassSub_Promotion = TEXT("Promotion");
BitMapManager BitMapMgr_Main;
BitMapManager BitMapMgr_Sub;
BitMapManager BitMapMgr_Sub_Promotion;


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    // TODO: 여기에 코드를 입력합니다.
    HWND hWnd_Main;
    HWND hWnd_Sub;
    HWND hWnd_Sub_Promotion;
    MSG msg;
    WndClassCreate WndClassMain(hInstance, IpszClassMain, BLACK_BRUSH);
    WndClassCreate WndClassSub(hInstance, IpszClassSub, WHITE_BRUSH);
    WndClassCreate WndClassSub_Promotion(hInstance, IpszClassSub_Promotion, BLACK_BRUSH);
    g_hInst = hInstance;

    //---------------------------------------

    //메인 창 등록
    WndClassMain.WndClass.lpfnWndProc = WndProc_Main;	//프로세스 함수 호출
    RegisterClass(&WndClassMain.WndClass);

    //서브 창 등록
    WndClassSub.WndClass.lpfnWndProc = WndProc_Sub;
    RegisterClass(&WndClassSub.WndClass);

    //서브 창 등록 
    WndClassSub_Promotion.WndClass.lpfnWndProc = WndProc_Sub_Promotion;
    RegisterClass(&WndClassSub_Promotion.WndClass);

    //---------------------------------------

    //메인
    hWnd_Main = CreateWindow(IpszClassMain, IpszClassMain, WS_SYSMENU | WS_MINIMIZEBOX, MAIN_X, MAIN_Y, MAIN_W, MAIN_H,
        NULL, (HMENU)NULL, hInstance, NULL);

    //서브 일정 단계가 지나고 출력하도록(턴 조절)
    hWnd_Sub = CreateWindow(IpszClassSub, IpszClassSub, WS_OVERLAPPED | WS_MINIMIZEBOX, SUB_X, SUB_Y, SUB_W, SUB_H,
        NULL, (HMENU)NULL, hInstance, NULL);  //부모 클래스를 받으면 부모 클래스가 상위 노출이 안된다.  
    
    //서브 일정 단계가 지나고 출력하도록(Pawn 승진)
    //hWnd_Sub_Promotion = CreateWindow(IpszClassSub_Promotion, IpszClassSub_Promotion, WS_OVERLAPPED | WS_MINIMIZEBOX, SUB_X, SUB_Y, SUB_W, SUB_H,
        //NULL, (HMENU)NULL, hInstance, NULL);
    
    //---------------------------------------

    //메인 and 서브 창 초기화는 여기서
    GMMgr->Init(&BitMapMgr_Main, &BitMapMgr_Sub, &BitMapMgr_Sub_Promotion, hWnd_Main, hWnd_Sub, nCmdShow, IpszClassSub_Promotion, hInstance);

    ShowWindow(hWnd_Main, nCmdShow);
    ShowWindow(hWnd_Sub, nCmdShow);
    //ShowWindow(hWnd_Sub_Promotion, nCmdShow);

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
        {
            InvalidateRect(hWnd_Main, NULL, true); //이미지를 클릭하면 화면 지우고 다시 그려야 > 시각화

            //서브 Promotion window 생성 시기
            if ((GMMgr->Get_GameStopCheck() == true) && (GMMgr->Get_GameEndCheck() == false))
            {
                //서브 일정 단계가 지나고 출력하도록(Pawn 승진)
                GMMgr->SubPromotion();
                //InvalidateRect(GMMgr->Get_HWND_Sub_Promotion(), NULL, true);
            }
        }

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

LRESULT CALLBACK WndProc_Sub(HWND hWnd_Sub, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    POINT Point;

    switch (iMessage)
    {
    case WM_PAINT:
        hdc = BeginPaint(GMMgr->Get_HWND_Sub(), &ps);
        GMMgr->SubDraw(hdc);
        EndPaint(hWnd_Sub, &ps);
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return(DefWindowProc(hWnd_Sub, iMessage, wParam, lParam));
}

LRESULT CALLBACK WndProc_Sub_Promotion(HWND hWnd_Sub_Promotion, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    POINT Point;


    switch (iMessage)
    {
    case WM_LBUTTONDOWN:
        Point.x = LOWORD(lParam);
        Point.y = HIWORD(lParam);

        if (GMMgr->ColliderCheck_SubPromotion(Point))
        {
            //승진 기물을 선택하면 window를 지운다.
            DestroyWindow(hWnd_Sub_Promotion);
        }
        return 0;
    case WM_PAINT:
        hdc = BeginPaint(hWnd_Sub_Promotion, &ps);
        GMMgr->SubPromotionDraw(hdc);
        EndPaint(hWnd_Sub_Promotion, &ps);
        return 0;

    case WM_DESTROY:
        //PostQuitMessage(0);
        return 0;
    }

    return(DefWindowProc(hWnd_Sub_Promotion, iMessage, wParam, lParam));
}