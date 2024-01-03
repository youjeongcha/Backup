// TCP_IP_Server_Non-blockingSocket.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//


#define _WINSOCK_DEPRECATED_NO_WARNINGS


#pragma comment(lib, "ws2_32.lib")  //원속 라이브러리 사용을 알린다.
#include <WinSock2.h>              //윈속 사용을 위하여 헤더 파일 추가
#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_BUFFER_SIZE 256
#define BUFSIZE 256

struct SOCKETINFO
{
    SOCKET sock;
    char buf[BUFSIZE + 1];
};

//std::vector<SOCKET> g_vSocket; //전역 변수
//HANDLE g_hMutex; //전역 변수

// listen 소켓을 포함한, 현재 접속한 client의 수
int g_nTotalSockets = 0;
// 논블로킹 소켓으로 만든 소켓의 정보
SOCKETINFO* arrSocketInfo[WSA_MAXIMUM_WAIT_EVENTS];
// 소켓이 어떤 처리를 할 수 있는지에 대한 이벤트
WSAEVENT arrEvent[WSA_MAXIMUM_WAIT_EVENTS];

// 논블로킹 소켓으로 사용할 소켓 정보 추가
bool AddSocketInfo(SOCKET sock);
// 소켓 정보 삭제.
void RemoveSocketInfo(int idex);

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

void err_display(const int& errcode)
{
    LPVOID lpMsgBuf;
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
        NULL, errcode,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&lpMsgBuf, 0, NULL);

    printf("[오류] %s", (LPCTSTR)lpMsgBuf);

    //메모리 해제, 핸들 무효화
    LocalFree(lpMsgBuf);
}



bool AddSocketInfo(SOCKET sock)
{
    if (WSA_MAXIMUM_WAIT_EVENTS <= g_nTotalSockets) {
        printf("[오류] 소켓 정보를 추가할 수 없습니다!\n");
        return false;
    }

    SOCKETINFO* ptr = new SOCKETINFO;
    if (NULL == ptr) {
        printf("[오류] 메모리가 부족합니다.!\n");
        return false;
    }

    WSAEVENT hEvent = WSACreateEvent();
    if (WSA_INVALID_EVENT == hEvent) {
        err_display("WSACreateEvent()");
        return false;
    }

    ptr->sock = sock;
    arrSocketInfo[g_nTotalSockets] = ptr;
    arrEvent[g_nTotalSockets] = hEvent;
    g_nTotalSockets++;

    return true;
}

void RemoveSocketInfo(int index)
{
    SOCKETINFO* ptr = arrSocketInfo[index];

    //클라이언트 정보 얻기
    SOCKADDR_IN addr;
    int addlen = sizeof(addr);
    getpeername(ptr->sock, (SOCKADDR*)&addr, &addlen);
    printf("[TCP 서버] 클라이언트 종료 : IP 주소=%s, 포트 번호%d\n", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));

    closesocket(ptr->sock);
    delete ptr;
    WSACloseEvent(arrEvent[index]);

    // 배열 공간을 한 칸씩, 앞으로 이동
    for (int i = index + 1; g_nTotalSockets > i; i++)
    {
        arrSocketInfo[i - 1] = arrSocketInfo[i];
        arrSocketInfo[i] = nullptr;

        arrEvent[i - 1] = arrEvent[i];
        arrEvent[i] = 0;
    }
    g_nTotalSockets--;
}

int main()
{
    //g_hMutex = CreateMutex(NULL, false, NULL);
    //if (NULL == g_hMutex)
    //    return -1; // 뮤텍스 생성 실패
    //if (GetLastError() == ERROR_ALREADY_EXISTS) // 이미 생성된 뮤텍스가 있습니다!!
    //{
    //    CloseHandle(g_hMutex);
    //    return -1;
    //}
    // 윈속 초기화 (2.2 버전)
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
        return -1;

    //소켓 네트워크 프로그래밍 Code 작성
    //socket() listen_socket 생성
    SOCKET listen_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (INVALID_SOCKET == listen_socket)
        err_quit("socket");

    // 소켓 정보 추가.
    if (FALSE == AddSocketInfo(listen_socket)) return -1;
    // WSAEventSelect() : 콘솔 프로젝트에서 사용, 해당 소켓을 논브롤킹 소켓으로 만들어 준다.
    // FD_ACCEPT : 클라이언트에서 연결 요청이 왔을 때.
    // FD_CONNECT : connect()를 이용하여 서버에서 연결을 수락 했을 때.
    // FD_CLOSE : 해당 소켓이 연결을 해제 했을 때.
    // FD_READ : 소켓을 읽어 들일 데이터가 있을 때.
    // FD_WRITE : send()할 수 있을 때, 소켓의 버퍼가 비어있을 때.
    // listen_socket은 accept()와 closesocket()을 해야할 경우만 이벤트를 받도록 한다.
    int retval = WSAEventSelect(listen_socket, arrEvent[g_nTotalSockets - 1], FD_ACCEPT | FD_CLOSE);
    if (SOCKET_ERROR == retval)
    {
        closesocket(listen_socket);
        err_quit("WSAEventSelect()");
    }

    //계속 작업 진행
    //서버 정보 객체 설정.
    //INADDR_ANY : 자신의 IP를 알아와 주는 메크로 함수
    SOCKADDR_IN serveraddr;
    ZeroMemory(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(9000);
    serveraddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

    // bind() 소켓 설정.
    if (bind(listen_socket, (SOCKADDR*)&serveraddr, sizeof(serveraddr)) == SOCKET_ERROR)
    {
        closesocket(listen_socket);
        WSACleanup();
        err_quit("bind");
    }


    //listen() 수신 대기열 생성.
    if (listen(listen_socket, SOMAXCONN) == SOCKET_ERROR)
    {
        closesocket(listen_socket);
        WSACleanup();
        err_quit("listen");
    }

    int index;
    WSANETWORKEVENTS NetworkEvents;
    SOCKET client_sock;
    SOCKADDR_IN clientaddr;
    int addlen = sizeof(SOCKADDR_IN);
    while (true)
    {
        // TODO: 여기서부터 while문 안의 내용.
        // 현재 페이지의 내용은 반드시 while문 제일 첫 줄에, 순서에 맞게 작성 되어야 한다.
        // 이벤트 객체 관찰.
        // 몇 번째 WSAEVENT배열에 이벤트가 발행했는지 index를 알 수 있다.
        index = WSAWaitForMultipleEvents(g_nTotalSockets, arrEvent, FALSE, WSA_INFINITE, FALSE);

        if (WSA_WAIT_FAILED == index)
        {
            err_display("WSAWaitForMultipleEvents()");
            continue;
        }

        // 반환 값에 WSA_WAIT_EVENT_0를 뺀 값이 배열의 index
        index -= WSA_WAIT_EVENT_0;

        // 구체적인 네트워크 이벤트 알아내기.
        // 해당 소켓에 발행한 이벤트를 WSANETWORKEVENTS 객체를 통해 알아온다.
        retval = WSAEnumNetworkEvents(arrSocketInfo[index]->sock, arrEvent[index], &NetworkEvents);

        if (SOCKET_ERROR == retval)
        {
            err_display("WSAEnumNetworkEvents()");
            continue;
        }

        // FD_ACCEPT 이벤트 처리.
        if (NetworkEvents.lNetworkEvents & FD_ACCEPT)
        {
            // FD_ACCEPT 이벤트에 발생한 오류를 확인.
            if (0 != NetworkEvents.iErrorCode[FD_ACCEPT_BIT])
            {
                err_display(NetworkEvents.iErrorCode[FD_ACCEPT_BIT]);
                continue;
            }

            // accept()
            client_sock = accept(arrSocketInfo[index]->sock, (SOCKADDR*)&clientaddr, &addlen);
            if (INVALID_SOCKET == client_sock)
            {
                err_display("accept()");
                continue;
            }

            printf("[TCP 서버] 클라이언트 접속 : IP 주소=%s, 포트 번호=%d\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

            // 접속 수 제한.
            if (WSA_MAXIMUM_WAIT_EVENTS <= g_nTotalSockets)
            {
                printf("[오류] 더 이상 접속을 받아들일 수 없습니다!\n");
                closesocket(client_sock);
                continue;
            }

            // 클라이언트 소켓 정보 추가
            if (!AddSocketInfo(client_sock))
                continue;

            // WSAEventSelect()
            // client_sock은 클라이언트에서 send()하여 recv()해야 할 경우와 클라이언트가 종료되어 closesocket()을 해야할 경우만 이벤트를 받도록 한다.
            retval = WSAEventSelect(client_sock, arrEvent[g_nTotalSockets - 1], FD_READ | FD_CLOSE);

            if (SOCKET_ERROR == retval)
                err_quit("WSAEventSelect()");
        } // FD_ACCEPT 이벤트

        // FD_READ 이벤트 처리
        if (NetworkEvents.lNetworkEvents & FD_READ)
        {
            if (0 != NetworkEvents.iErrorCode[FD_READ_BIT])
            {
                err_display(NetworkEvents.iErrorCode[FD_READ_BIT]);
                continue;
            }


            //TODO::서버 도착 부분 검수
            //1.버퍼 {0}으로 초기화, ? 같은 쓰레기값 들지 않게

            SOCKETINFO* ptr = arrSocketInfo[index];
            retval = recv(ptr->sock, ptr->buf, BUFSIZE, 0);
            if (SOCKET_ERROR == retval)
            {
                if (WSAEWOULDBLOCK != WSAGetLastError())
                {
                    err_display("recv()");
                    RemoveSocketInfo(index);
                }
                continue;
            }

            ptr->buf[retval] = '\0';
            getpeername(ptr->sock, (SOCKADDR*)&clientaddr, &addlen);
            printf("[TCP/%s:%d]%s\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port), ptr->buf);
            int sendbyte = retval;
            for (int i = 1; g_nTotalSockets > i; i++)
            {
                retval = send(arrSocketInfo[i]->sock, ptr->buf, sendbyte, 0);
                if (SOCKET_ERROR == retval)
                {
                    if (WSAEWOULDBLOCK != WSAGetLastError())
                    {
                        err_display("send()");
                        RemoveSocketInfo(index);
                    }
                    continue;
                }
            }

        }
    } // FD_READ 이벤트

    // FD_READ 이벤트 처리
    if (NetworkEvents.lNetworkEvents & FD_CLOSE)
    {
        if (0 != NetworkEvents.iErrorCode[FD_CLOSE_BIT])
        {
            err_display(NetworkEvents.iErrorCode[FD_CLOSE_BIT]);
        }
        RemoveSocketInfo(index);
    }


    // closesocket(listen_socket)
    closesocket(listen_socket);
    // 윈속 사용이 끝났다.


    WSACleanup();
    return 0;
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
