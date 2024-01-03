// TCP_IP_Client_Non-blockingSocket.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "ws2_32.lib")  //원속 라이브러리 사용을 알린다.
#include <WinSock2.h>              //윈속 사용을 위하여 헤더 파일 추가
#include <iostream>
#include <vector>
#include "framework.h"
#include "TCP_IP_Client_Non-blockingSocket.h"

#define MAX_LOADSTRING 100

// WM_USER 초과한 값을 사용하여 개인적인 윈도우 메시지를 만들어 사용할 수 있다.
#define WM_SOCKET (WM_USER + 1)
#define BUFSIZE 256

// Add
//SOCKET g_sock;
//std::string g_strChat;
//std::vector<std::string> g_vLog;

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// Add
void AddLog(const char* str);
void ErrorQuit(const char* caption);
void ErrorDisplay(HWND hWnd, const char* caption);
void ErrorDisplay(HWND hWnd, const int& errorCode, const char* caption);
void SocketProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);




int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    //UNREFERENCED_PARAMETER(hPrevInstance);
   // UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    //if (!InitInstance(hInstance, nCmdShow))
    //{
    // return FALSE;
    //}


   
    //MSG msg;
    // 기본 메시지 루프입니다:



    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_TCPIPCLIENTNONBLOCKINGSOCKET, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

   // HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
     //   CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_SYSMENU, CW_USEDEFAULT, 0, 800, 600, nullptr, nullptr,
        hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    // 윈속 초기화.
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
        return -1;

    // 서버 접속을 위한 소켓 생성.
    g_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (INVALID_SOCKET == g_sock)
        ErrorQuit("socket()");

    // WSAAsyncSelect() : 데스크톱 응용프로그램에서 사용, 해당 소켓을 논브롤킹(비동기) 소켓으로 만들어 준다.
    int retval = WSAAsyncSelect(g_sock, hWnd, WM_SOCKET, FD_CONNECT);
    if (SOCKET_ERROR == retval)
    {
        closesocket(g_sock);
        ErrorQuit("WSAAsyncSelect()");
    };

    // 서버 접속을 위한, 서버 주소 설정.
    SOCKADDR_IN serveraddr;
    ZeroMemory(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(9000);
    serveraddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

    // 비동기 소켓으로 WM_SOCKET에서 오류 및 FD_CONNECT 메시지 처리, 여기서 오류 처리 X.
    connect(g_sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TCPIPCLIENTNONBLOCKINGSOCKET));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    // 윈속 종료.
    WSACleanup();

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TCPIPCLIENTNONBLOCKINGSOCKET));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName = NULL;//MAKEINTRESOURCEW(IDC_TCPIPCLIENTNONBLOCKINGSOCKET);
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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_SOCKET:
        SocketProc(hWnd, message, wParam, lParam);
        break;
    case WM_CHAR:
    {
        const char& ch = (TCHAR)wParam;
        if ('\n' != ch && '\r' != ch)
        {
            if ('\b' == ch)
            {
                if (0 < g_strChat.length())
                    g_strChat = g_strChat.substr(0, g_strChat.length() - 1);
            }
            else
                g_strChat += ch;
            InvalidateRect(hWnd, NULL, true);
        }
    }
    break;
    case WM_KEYUP:
        if (VK_RETURN == wParam)
        {
            if (0 < g_strChat.length())
            {
                char buf[BUFSIZE + 1];
                strcpy_s(buf, g_strChat.c_str());
                send(g_sock, buf, g_strChat.length(), 0);
                g_strChat.clear();
                //InvalidateRect(hWnd, NULL, true);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            
            //발생한 socket 이벤트의 로그 출력
            for (int i = 0; g_vLog.size() > i; i++)
                TextOut(hdc, 0, i * 20, g_vLog[i].c_str(), g_vLog[i].length());

            // 입력한 문자 출력.
            TextOutA(hdc, 0, 400, g_strChat.c_str(), g_strChat.length());
            
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        //멀티바이트 문자 집합 사용으로 DefWindowPRoc( => DefWindowPRocW
        return DefWindowProcW(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}


//오류 메시지를 메시지 박스에 출력 후 애플리케이션을 종료 시킨다.
void err_quit(const char* msg)
{
    LPVOID lpMsgBuf;
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
        NULL,
        WSAGetLastError(),
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&lpMsgBuf, 0, NULL);

    //msg : 메시지 박스의 타이틀(Caption)
    MessageBox(NULL, (LPCSTR)lpMsgBuf, msg, MB_ICONERROR);

    //메모리 해제, 핸들 무효화
    LocalFree(lpMsgBuf);

    exit(-1);
}

//오류 메시지를 출력하고 애플리케이션을 속행
//사소한 오류가 발생할 경우 사용
void err_display(const char* msg)
{
    LPVOID lpMsgBuf;
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
        NULL,
        WSAGetLastError(),
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&lpMsgBuf, 0, NULL);

    printf("[%s] %s\n", msg, (LPCSTR)lpMsgBuf);

    LocalFree(lpMsgBuf);
}


void AddLog(const char* str)
{
    if (26 <= g_vLog.size())
        g_vLog.erase(g_vLog.begin());

    g_vLog.push_back(str);
}

void ErrorQuit(const char* caption)
{
    LPVOID lpMsgBuf;
    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, WSAGetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);
    MessageBox(NULL, (LPCTSTR)lpMsgBuf, caption, MB_ICONERROR);
    LocalFree(lpMsgBuf);
    exit(-1);
}

void ErrorDisplay(HWND hWnd, const char* caption)
{
    ErrorDisplay(hWnd, WSAGetLastError(), caption);
}

void ErrorDisplay(HWND hWnd, const int& errorCode, const char* caption)
{
    LPVOID lpMsgBuf;
    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, errorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);
    char buf[256];
    ZeroMemory(&buf, sizeof(buf));
    sprintf_s(buf, "[%s] %s", caption, (LPCTSTR)lpMsgBuf);
    AddLog(buf);
    InvalidateRect(hWnd, NULL, true);
    LocalFree(lpMsgBuf);
}

void SocketProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (WSAGETSELECTERROR(lParam)) // 요류 발생 여부 확인.
    {
        ErrorDisplay(hWnd, WSAGETSELECTERROR(lParam), "ERROR");
        closesocket(g_sock);
        return;
    }

    std::string msg;

    switch (WSAGETSELECTEVENT(lParam))
    {
    case FD_CONNECT:
        msg = "FD_CONNECT";
        if (SOCKET_ERROR == WSAAsyncSelect(g_sock, hWnd, WM_SOCKET, FD_CLOSE | FD_READ))
        {
            closesocket(g_sock);
            ErrorQuit("WSAAsyncSelect()");
        };
        break;
    case FD_CLOSE:
        msg = "FD_CLOSE : 서버와 연결이 끊겼습니다."; closesocket(g_sock); 
        break;
    case FD_READ:
    {
        msg = "FD_READ : ";
        char buf[BUFSIZE];
        ZeroMemory(&buf, sizeof(buf));
        int retval = recv(g_sock, buf, BUFSIZE, 0);
        msg.append(buf);
    }
    break;
    }
    msg.append("\0");
    AddLog(msg.c_str());
    InvalidateRect(hWnd, NULL, true);
}