// WinAPI_Chess.cpp : 애플리케이션에 대한 진입점을 정의합니다.


//--- Chess 네트워크 추가 ---
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "ws2_32.lib")  //원속 라이브러리 사용을 알린다.
#include <WinSock2.h>              //윈속 사용을 위하여 헤더 파일 추가
#include <iostream>
#include <vector>
#include "framework.h"
//#include "packet.h"
//--------------------------


//--- 기존 ---
//#include <Windows.h>
//#include "framework.h"
#include "GameManager.h"
#include "WndClassCreate.h"
#include "resource.h"



#define GMMgr GameManager::Get_Instance()


//--- Chess 네트워크 추가 ---

#define IDC_TCPIPCLIENTNONBLOCKINGSOCKET			109
#define MAX_LOADSTRING 100

// WM_USER 초과한 값을 사용하여 개인적인 윈도우 메시지를 만들어 사용할 수 있다.
#define WM_SOCKET (WM_USER + 1)
#define BUFSIZE 256

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

SOCKET g_sock;
std::string g_strChat;
std::vector<std::string> g_vLog;



void AddLog(const char* str);
void ErrorQuit(const char* caption);
void ErrorDisplay(HWND hWnd, const char* caption);
void ErrorDisplay(HWND hWnd, const int& errorCode, const char* caption);
void SocketProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
//-----------------------------------



// 전역 변수:
LRESULT CALLBACK WndProc_Main(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProc_Sub(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProc_Sub_Promotion(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;                                // 현재 인스턴스입니다.
LPCTSTR IpszClassMain = TEXT("Chess");
LPCTSTR IpszClassSub = TEXT("Turn");
LPCTSTR IpszClassSub_Promotion = TEXT("Promotion");
//BitMapManager BitMapMgr_Main;
//BitMapManager BitMapMgr_Sub;
//BitMapManager BitMapMgr_Sub_Promotion;


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
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
    GMMgr->Init(hWnd_Main, hWnd_Sub, nCmdShow, IpszClassSub_Promotion, hInstance);

    ShowWindow(hWnd_Main, nCmdShow);
    ShowWindow(hWnd_Sub, nCmdShow);
    //ShowWindow(hWnd_Sub_Promotion, nCmdShow);

    //SetForegroundWindow(hWnd_Main); //컴퓨터 그래픽스 ppt 확인

    /*
    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }*/


    //--- Chess 네트워크 추가 ---

     // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_TCPIPCLIENTNONBLOCKINGSOCKET, szWindowClass, MAX_LOADSTRING);
    //MyRegisterClass(hInstance);

    /*
    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_SYSMENU, CW_USEDEFAULT, 0, 800, 600, nullptr, nullptr,
        hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);*/

    //
    // 윈속 초기화.
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
        return -1;

    // 서버 접속을 위한 소켓 생성.
    g_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (INVALID_SOCKET == g_sock)
        ErrorQuit("socket()");
    
    // WSAAsyncSelect() : 데스크톱 응용프로그램에서 사용, 해당 소켓을 논브롤킹(비동기) 소켓으로 만들어 준다.
    //int retval = WSAAsyncSelect(g_sock, hWnd, WM_SOCKET, FD_CONNECT);
    int retval = WSAAsyncSelect(g_sock, hWnd_Main, WM_SOCKET, FD_CONNECT);
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
    //
    //MSG msg;
    
    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    

    // 윈속 종료.
    WSACleanup();
    

    return (int) msg.wParam;
}


LRESULT CALLBACK WndProc_Main(HWND hWnd_Main, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    POINT Point;

    switch (message)
    {
    case WM_SOCKET:
        SocketProc(hWnd_Main, message, wParam, lParam);
        
        //printf("대기중");
        
        //PostQuitMessage(0);


        break;
    case WM_LBUTTONDOWN:
        Point.x = LOWORD(lParam);
        Point.y = HIWORD(lParam);

        //승진 진행 턴일때는 패스
        if (GMMgr->Get_IsPromotion())
            break;

        if (GMMgr->ColliderCheck(Point))
        {
            InvalidateRect(hWnd_Main, NULL, false); //이미지를 클릭하면 화면 지우고 다시 그려야 > 시각화

            ////서브 Promotion window 생성 시기
            //if ((GMMgr->Get_GameStopCheck() == true) && (GMMgr->Get_GameEndCheck() == false))
            //{
            //    //서브 일정 단계가 지나고 출력하도록(Pawn 승진)
            //    GMMgr->SubPromotion();
            //}

            //Wait_Turn인 상태일때 플레이어의 턴이 끝난것
            //턴 종료 데이터 보내기.
            //if (GMMgr->GetPlayerState() == WAIT_TURN)
            if (GMMgr->Get_IsSend_Sever())
            {
                //플레이어 턴 끝나고 한번만 데이터 보내게끔 조절
                GMMgr->Set_IsSend_Sever(false);

                //승리체크
                if (GMMgr->Get_IsWinCheck())
                {
                    WINCHECKPACKET send_packet;
                    //발송할 데이터 패킷에 적용
                    send_packet.packetType = PacketType_WinCheck;
                    send_packet.packetSize = sizeof(WINCHECKPACKET);
                    send_packet.winTeam = GMMgr->Get_PlayerTurn(); //현재 플레이어가 무슨 팀인지. (이름이 요상한건 네트워크 작업 이전의 작동 때문. 그때는 턴 전환 시켜서 썼으니까.)
                    //움직이기 전 말 좌표 + 움직일 좌표 알려주기
                    GMMgr->SetMoveData_ToServer(send_packet.m_iX, send_packet.m_iY, send_packet.m_moveRect);

                    send(g_sock, (char*)&send_packet, send_packet.packetSize, 0);
                }
                //이동해서 승진 정보 보내기
                else if (GMMgr->Get_IsPromotion())
                {
                    MOVEPROMOTIONOBJECTPACKET send_packet;
                    //발송할 데이터 패킷에 적용
                    send_packet.packetType = PacketType_MovePromotionObject;
                    send_packet.packetSize = sizeof(MOVEPROMOTIONOBJECTPACKET);
                    //움직이기 전 말 좌표 + 움직일 좌표 알려주기
                    GMMgr->SetMoveData_ToServer(send_packet.m_iX, send_packet.m_iY, send_packet.m_moveRect);

                    send(g_sock, (char*)&send_packet, send_packet.packetSize, 0);
                }
                else
                {
                    MOVEOBJECTPACKET send_packet;
                    //발송할 데이터 패킷에 적용
                    send_packet.packetType = PacketType_MoveObject;
                    send_packet.packetSize = sizeof(MOVEOBJECTPACKET);
                    //움직이기 전 말 좌표 + 움직일 좌표 알려주기
                    GMMgr->SetMoveData_ToServer(send_packet.m_iX, send_packet.m_iY, send_packet.m_moveRect);

                    int test = send(g_sock, (char*)&send_packet, send_packet.packetSize, 0);
                }
            }
        }
        return 0;
    case WM_PAINT:
        hdc = BeginPaint(hWnd_Main, &ps);
        GMMgr->Draw(hdc);
        EndPaint(hWnd_Main, &ps);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
       // return DefWindowProc(hWnd_Main, message, wParam, lParam);

         //멀티바이트 문자 집합 사용으로 DefWindowPRoc( => DefWindowPRocW
        return DefWindowProcW(hWnd_Main, message, wParam, lParam);
    }
    return 0;
}

HWND sub = 0;
// 흑백 차례 보여주는 창
LRESULT CALLBACK WndProc_Sub(HWND hWnd_Sub, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    POINT Point;

    switch (iMessage)
    {
    case WM_CREATE:
        sub = hWnd_Sub;
        break;
    case WM_PAINT:
    {
        hdc = BeginPaint(GMMgr->Get_HWND_Sub(), &ps);

        RECT clientRect_Sub = GMMgr->Get_ClientRect_Sub();
        //---------더블버퍼링----------
        HBITMAP backBitmap = GMMgr->MyCreateDIBSection(hdc, clientRect_Sub.right + 1, clientRect_Sub.bottom + 1);
        SelectObject(hdc, backBitmap);
        GMMgr->SubDraw(hdc);
        


        // 서브창에서 대기중 표시 띄우기
        GMMgr->DrawTurnState(hdc);
        //PiecesMgr->DrawPawnPromotion(hdc);


     
        BitBlt(hdc, 0, 0, clientRect_Sub.right + 1, clientRect_Sub.bottom + 1, hdc, 0, 0, SRCCOPY);
        DeleteObject(backBitmap);
        //----------------------------

        EndPaint(GMMgr->Get_HWND_Sub(), &ps);
        return 0;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return(DefWindowProc(hWnd_Sub, iMessage, wParam, lParam));
}

// 폰이 승진할때 뜨는 이벤트 창
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

            //승진 정보를 보낸다.
            PROMOTIONPACKET send_packet;
            //발송할 데이터 패킷에 적용
            send_packet.packetType = PacketType_Promotion;
            send_packet.packetSize = sizeof(PROMOTIONPACKET);
            send_packet.promotion = (PROMOTION_RECT)PiecesMgr->Get_Promotion();
            //send_packet.erasePeice = PiecesMgr->GetErasePawn();

            send(g_sock, (char*)&send_packet, send_packet.packetSize, 0);
        }
        return 0;
    case WM_PAINT:
        hdc = BeginPaint(hWnd_Sub_Promotion, &ps);

        GMMgr->SubPromotionDraw(hdc);
        EndPaint(hWnd_Sub_Promotion, &ps);
        return 0;

 /*   case WM_DESTROY:
        PostQuitMessage(0);
        return 0;*/
    }

    //return(DefWindowProc(hWnd_Sub_Promotion, iMessage, wParam, lParam));
    //멀티바이트 문자 집합 사용으로 DefWindowPRoc( => DefWindowPRocW
    return DefWindowProcW(hWnd_Sub_Promotion, iMessage, wParam, lParam);
}



//--- Chess 네트워크 추가 ---


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
        //char buf[sizeof(BASEPACKET) + 1000];
        char buf[sizeof(BASEPACKET) + sizeof(MOVEOBJECTPACKET)];
        ZeroMemory(&buf, sizeof(buf));

        // 첫 번째 수신: 패킷 헤더
        int retval = recv(g_sock, buf, sizeof(BASEPACKET), 0); //retval에 실제로 전달받은 데이터의 크기가 리턴
        //int retval = recv(g_sock, buf, sizeof(b), 0); //retval에 실제로 전달받은 데이터의 크기가 리턴
        BASEPACKET* recv_packet = (BASEPACKET*)buf;
        //패킷 사이즈에서 내가 받은 데이터 크기를 빼준다. (전송되면서 데이터 누락이 발생한 경우 이어서 받기 위해)
        int size = recv_packet->packetSize - retval;  
        
        // 두 번째 수신: 나머지 데이터(타입별로 추가 데이터가 buf에 들어온다.)
        retval = recv(g_sock, buf + retval, size, 0);



        //패킷의 타입에 따라 
        switch (recv_packet->packetType)
        {
        case PacketType_SetTeam: //팀 설정
        {
            SETTEAMPACKET* teampack = (SETTEAMPACKET*)buf;
            //teampack->packetType = PacketType_SetTeam;
            GMMgr->DelayAccess(teampack->playerTeam); // 대기 - 기물 색 정하지 않고
            break;
        }
        case PacketType_SetTurn:
        {
            SETTURNPACKET* setTurnpack = (SETTURNPACKET*)buf;

            GMMgr->SetTurn(setTurnpack->setTurn);
            break;
        }
        case PacketType_MoveObject:
        {
            MOVEOBJECTPACKET* movepack = (MOVEOBJECTPACKET*)buf;

            GMMgr->SetTurn(movepack->setTurn);

            PiecesMgr->MovePiece_FromServer(movepack->m_iX, movepack->m_iY, movepack->m_moveRect);
            break;
        }
        case PacketType_MovePromotionObject:
        {
            //폰이 승진하기 위해 한 칸 움직이는 것.(서버에서 받아와 클라이언트들에 뿌려주기 때문에 가능)
            GMMgr->Set_IsPromotion(true);

            MOVEPROMOTIONOBJECTPACKET* onlyMovepack = (MOVEPROMOTIONOBJECTPACKET*)buf;

            PiecesMgr->MovePiece_FromServer(onlyMovepack->m_iX, onlyMovepack->m_iY, onlyMovepack->m_moveRect);


            //플레이어 턴인 쪽에만 승진 가능하게
            if (GMMgr->Get_PalyerState() == MY_TURN)
                GMMgr->SubPromotion();
            break;
        }
        case PacketType_Promotion:
        {
            PROMOTIONPACKET* promotionpack = (PROMOTIONPACKET*)buf;
            GMMgr->SetTurn(promotionpack->setTurn);

            PiecesMgr->Promotion(promotionpack->promotion);

            // GMMgr->Set_GameStopCheck(false);
            GMMgr->Set_IsPromotion(false); //위치 맞나 확인
            break;
        }
        case PacketType_WinCheck:
        {
            WINCHECKPACKET* promotionpack = (WINCHECKPACKET*)buf;
            
            //진짜 싫은데 코드를 이렇게 짜놔서 어떻게 할수가 없는 그런 상황
            //m_PlayerTurn이 현재 플레이어의 팀을 가지고 있음.
            //그런데 wincheck 문구는 m_PlayerTurn로 나타나게 되어있어서 승패 나뉘면 이걸 바꿔줘야 함...

            PiecesMgr->MovePiece_FromServer(promotionpack->m_iX, promotionpack->m_iY, promotionpack->m_moveRect);

            GMMgr->Set_WinTeam(promotionpack->winTeam);


            GMMgr->Set_GameStopCheck(true);
            GMMgr->Set_GameEndCheck(true);

            break;
        }
        }
        //타입을 검사 다시 버퍼를 패킷으로 전환하고 맞는 타이밍에 딜레이 처리
        //msg.append(buf);
    }
    break;
    }
    msg.append("\0");
    AddLog(msg.c_str());
    InvalidateRect(hWnd, NULL, true);
    if (sub)
        InvalidateRect(sub, NULL, true);
}