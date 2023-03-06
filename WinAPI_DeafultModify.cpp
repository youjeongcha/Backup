// WinAPI_DeafultModify.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "WinAPI_DeafultModify.h"
#include <string>

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
//INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{//아래 두 코드 지워도 되는 코드. 하는 일 없다. 찜찜하면 두기.
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINAPIDEAFULTMODIFY, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    //키를 입력 받았는가만 체크를 한다. 지워야 무슨 킨지 확인 가능
    //HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPIDEAFULTMODIFY));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        //if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPIDEAFULTMODIFY));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1); //color 배경색 지정
    wcex.lpszMenuName = NULL; //or 0 //MAKEINTRESOURCEW(IDC_WINAPIDEAFULTMODIFY);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_SYSMENU |
       WS_MINIMIZEBOX,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
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

TCHAR str[256]; //글자 입력 받기
char g_buf[256]; //타이머 //전역 변수

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    SYSTEMTIME time; //지역 변수

    switch (message)
    {
        //case WM_COMMAND:
//    {
//        int wmId = LOWORD(wParam);
//        // 메뉴 선택을 구문 분석합니다:
//        switch (wmId)
//        {
//        case IDM_ABOUT:
//            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
//            break;
//        case IDM_EXIT:
//            DestroyWindow(hWnd);
//            break;
//        default:
//            return DefWindowProc(hWnd, message, wParam, lParam);
//        }
//    }
//    break;
    case WM_LBUTTONDOWN:
    {
        if (MessageBox(hWnd, L"내용", L"Title", MB_OK) == IDOK)
        {
            //수행 할 내용
        }
        break;
    }
    case WM_CREATE: 
    {
        SetTimer(hWnd, 1, 1000, NULL);
        break;
    }
    case WM_TIMER:
    {
        switch (wParam)
        {
        case 1:
            GetLocalTime(&time);
            sprintf_s(g_buf, "%d년 %d월 %d일 %d시 %d분 %d초", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
            InvalidateRect(hWnd, NULL, true);
            break;
        }
        break;
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다..
     
        /*
        //-----------------------------------------------------------

        SetTextColor(hdc, RGB(255, 0, 0)); //글자색
        SetBkColor(hdc, RGB(0, 0, 0)); //글자 배경색

        //-----------------------------------------------------------

        //TextOut()을 이용하여 문자 출력.
        std::wstring str = L"TEST test TEST";
        TextOut(hdc, 10, 10, str.c_str(), str.length());

        //DrawText()를 이용하여 문자 출력
        str = L"TEST test TEST test TEST test TEST test TEST test TEST test TEST";
        RECT rect = { 100, 100, 400, 300 };
        DrawText(hdc, str.c_str(), -1, &rect, DT_CENTER | DT_WORDBREAK);
        
        //-----------------------------------------------------------

        //SetPixel()로 붉은 점 찍기
        for (int i = 0; 10 > i; i++)
            SetPixel(hdc, 10 + 10 * i, 10, RGB(255, 0, 0));

        //MoveToEx()와 LineTo()를 이용하여 선 긋기
        MoveToEx(hdc, 10, 60, NULL);
        LineTo(hdc, 100, 20);

        //Rectangle()을 이용하여 사각형 그리기
        Rectangle(hdc, 10, 100, 100, 150);

        //Ellipse()를 이용하여 타원 그리기
        Ellipse(hdc, 10, 160, 100, 210);

        //-----------------------------------------------------------
        //시간 체크
        TextOutA(hdc, 10, 10, g_buf, strlen(g_buf));
        EndPaint(hWnd, &ps);
        */
        //-----------------------------------------------------------
        //이미지
        HDC memDC = CreateCompatibleDC(hdc);
        HBITMAP myBitmap = (HBITMAP)LoadImage(NULL, L"00.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        HBITMAP OldBitmap = (HBITMAP)SelectObject(memDC, myBitmap);
        BitBlt(hdc, 0, 0, 145, 245, memDC, 0, 0, SRCCOPY);
        StretchBlt(hdc, 200, 200, 245, 345, memDC, 0, 0, 145, 245, SRCCOPY);
        SelectObject(memDC, OldBitmap);
        DeleteObject(myBitmap);
        DeleteDC(memDC);

        EndPaint(hWnd, &ps);
    } break;
    case WM_CHAR:
    {
        int len = lstrlen(str);
        str[len] = (TCHAR)wParam;
        str[len + 1] = 0;
        HDC hdc = GetDC(hWnd);
        TextOut(hdc, 100, 100, str, lstrlen(str));
        ReleaseDC(hWnd, hdc);
    } break;
    case WM_DESTROY:
        KillTimer(hWnd, 1);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam); //절대 지우지 말것 WinAPI를 옮겼을 때 옮기는 것이나. 옮긴 좌표 따라 출력 하는 등 기본 처리를 함
    }
    return 0;
}



//// 정보 대화 상자의 메시지 처리기입니다.
//INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
//{
//    UNREFERENCED_PARAMETER(lParam);
//    switch (message)
//    {
//    case WM_INITDIALOG:
//        return (INT_PTR)TRUE;
//
//    case WM_COMMAND:
//        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
//        {
//            EndDialog(hDlg, LOWORD(wParam));
//            return (INT_PTR)TRUE;
//        }
//        break;
//    }
//    return (INT_PTR)FALSE;
//}
