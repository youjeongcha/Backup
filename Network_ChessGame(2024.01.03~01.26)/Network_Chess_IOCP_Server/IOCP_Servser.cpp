// IOCP_Servser.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//


#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define MAX_BUFFER_SIZE 256

#pragma comment(lib, "ws2_32.lib")  //원속 라이브러리 사용을 알린다.
#include <WinSock2.h>              //윈속 사용을 위하여 헤더 파일 추가

#include <iostream>
#include <map>
#include <vector>
#include <process.h>
#include <mutex>
#include "packet.h"

enum class OverlappedType { Invalied = -1, Recv, Send, };
struct Overlapped
{
    WSAOVERLAPPED wsaOverlapped;
    WSABUF wsaBuf;
    OverlappedType type;
};

// WSAOVERLAPPED 객체의 포인터를 이용하여 ClientInfo 객체를 얻기 때문에,
// 반드시 WSAOVERLAPPED는 가장 첫 라인에 있어야 한다.
struct ClientInfo
{
    Overlapped overlapped;
    SOCKET socket;
    char buf[MAX_BUFFER_SIZE];
    int prevBytes;

    ClientInfo()
    {
        prevBytes = 0;
        overlapped.wsaBuf.buf = buf;
        overlapped.type = OverlappedType::Invalied;
    }
};

std::mutex g_acceptLock;
std::mutex g_lock;
HANDLE g_hIOCP;
SOCKET g_listenSocket;
std::map<ULONG_PTR, ClientInfo> g_sockInfoList;  // 클라이언트의 SOCKET을 DWORD(ULONG_PTR)로 변경해 Key로 사용


bool isPlaying = false; //게임 플레이 중인지
//bool isEndTurn = true; //해당 턴이 끝난 상태인지(시작할때는 턴이 끝난상태인걸로 취급
//bool isEndTurn = false;
CAMP playerTurn = CAMP_WHITE; //현재 턴 플레이어가 누구인지



unsigned int WINAPI ThreadMain(LPVOID);
bool CreateWorkerThread();
bool Recv(ClientInfo* info);
void Send(ClientInfo* info);
void CloseSocket(SOCKET socket);


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


int main()
{
    std::string playerTeam[2] = { "흑", "백" };
    int waitCount = 1; //대기열 2까지만 컨트롤 (이외에는 튕기게)



    // 윈속 초기화 (2.2 버전)
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
        return -1;
   

    // socket() 소켓 생성.
    // IOCP(Io Completion Port) 객체 생성.
    g_hIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
    g_listenSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
    if (INVALID_SOCKET == g_listenSocket) err_quit("socket");

    //계속 작업 진행
    //서버 정보 객체 설정.
    //INADDR_ANY : 자신의 IP를 알아와 주는 메크로 함수
    SOCKADDR_IN serveraddr;
    ZeroMemory(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(9000);
    serveraddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);


    // bind() 소켓 설정.
    //bind 함수는 소켓에 IP 주소와 포트 번호를 할당하는 역할을 합니다.
    //서버는 특정 IP 주소와 포트 번호에 바인딩되어야 클라이언트가 연결할 수 있습니다.
    if (bind(g_listenSocket, (SOCKADDR*)&serveraddr, sizeof(serveraddr)) == SOCKET_ERROR)
    {
        closesocket(g_listenSocket);
        WSACleanup();
        err_quit("bind");
    }


    //listen() 수신 대기열 생성.
    //listen 함수는 소켓을 수신 대기 상태로 만들어 클라이언트의 연결을 받아들일 수 있게 합니다.
    if (listen(g_listenSocket, SOMAXCONN) == SOCKET_ERROR)
    {
        closesocket(g_listenSocket);
        WSACleanup();
        err_quit("listen");
    }

    // Worker Thread 생성.
    if (!CreateWorkerThread()) 
        return -1;


    // 데이터 통신에 사용할 변수
    SOCKADDR_IN clientaddr;
    int addrlen = sizeof(SOCKADDR_IN);
    ZeroMemory(&clientaddr, addrlen);


    while (1) {
        g_acceptLock.lock();

        // WSAAccept() : Winsock2에서 지원하는 accept()
        // 새로운 클라이언트가 연결될 때 WSAAccept 함수가 호출되어 연결을 수락합니다.
        //클라이언트 주소에 대한 정보(IP 및 포트)는 clientaddr 구조체에 저장됩니다.
        
        /*
         WSAAccept 함수가 호출될 때마다 clientaddr이 갱신되어 다음 대기 중인 클라이언트의 정보를 가지게 됩니다.
        */
        SOCKET clientSocket = WSAAccept(g_listenSocket, (SOCKADDR*)&clientaddr, &addrlen, NULL, NULL);
        g_acceptLock.unlock();

        if (INVALID_SOCKET == clientSocket) 
            continue;

        //printf("\n[IOCP 서버] 클라이언트 접속 : IP 주소=%s, 포트 번호=%d\n ", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));



        //--- Chess 네트워크 추가 ---
        //게임 플레이중일때 > 클라이언트 접속을 일단 못하게 해둔다. //1 0만 아래 코드 실행하도록 -1이하면 튕김
        //게임 끝나면 +2 해줄것 //1(백),0(흑)으로 한다.
        if (waitCount < 0)
            continue;

        
        //std::string 타입인데, %s는 C 스타일 문자열(const char*)을 기대하기 때문입니다. 
        //std::string 객체에서 C 스타일 문자열을 얻기 위해 c_str() 함수를 사용
        printf("\n[IOCP 서버] 클라이언트 접속 : IP 주소=%s, 포트 번호=%d, Player=%s\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port), playerTeam[waitCount].c_str()); //대기 순서 waitCount

        //흑-백 설정 데이터 보내기.
        SETTEAMPACKET send_packet;
        //발송할 데이터 패킷에 적용
        send_packet.packetType = PacketType_SetTeam;
        send_packet.playerTeam = (CAMP)waitCount; //1-백 / 0-흑 (백 흑 순서로 진행된다.)
        send_packet.packetSize = sizeof(SETTEAMPACKET); //enum과 int는 4로 같은 사이즈
        send(clientSocket, (char*)&send_packet, sizeof(SETTEAMPACKET), 0);
        
        



        //---------------------------


        //클라이언트의 정보 저장
        g_lock.lock();
        ClientInfo* info = &g_sockInfoList[(ULONG_PTR)clientSocket];
        info->socket = clientSocket;
        info->overlapped.type = OverlappedType::Recv;
        g_lock.unlock();





        //플레이어가 두명이 차면 한 번만 실행
        if (waitCount == 0) //흑백 플레이어 모두 입장 완료
        {
            isPlaying = true;

            //흑-백 설정 데이터 보내기.
            SETTURNPACKET send_packet;
            //발송할 데이터 패킷에 적용
            send_packet.packetType = PacketType_SetTurn;
            send_packet.packetSize = sizeof(SETTURNPACKET);
            send_packet.setTurn = playerTurn; //백 먼저 시작 ------------- 흑 전환 

            for (auto& clientInfo : g_sockInfoList)
                send(clientInfo.second.socket, (char*)&send_packet, sizeof(SETTURNPACKET), 0);
        }

        waitCount--;


        // 클라이언트의 SOCKET을 IOCP의 HANDLE과 CompletionKey로 사용.
        // SOCKET은 CreateIoCompletionPort를 사용하여 I/O 완료 포트(IOCP)와 연결됩니다.
        if (g_hIOCP != CreateIoCompletionPort((HANDLE)info->socket, g_hIOCP, (ULONG_PTR)info->socket, 0)) 
            break;

        // Recv 함수가 호출되어 연결된 클라이언트에 대한 비동기 수신 작업이 시작됩니다.
        if (!Recv(info)) 
            break;
    }
    closesocket(g_listenSocket);

    //윈속 사용이 끝났다.
    WSACleanup();
    
    return 0;
}

bool CreateWorkerThread()
{
    //시스템 정보 가져온다.
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);

    // CPU 갯수 확인
    printf_s("[IOCP 서버] CPU : %d개\n", sysInfo.dwNumberOfProcessors);

    // 적절한 작업 스레드의 갯수 = (CPU * 2) + 1
    const int numThread = sysInfo.dwNumberOfProcessors * 2 + 1;
    unsigned int threadId;
    HANDLE hThread;
    for (int i = 0; numThread > i; i++)
    {
        hThread = (HANDLE)_beginthreadex(NULL, 0, &ThreadMain, NULL, CREATE_SUSPENDED, &threadId);

        if (!hThread)
            return false;

        ResumeThread(hThread);
    }

    return true;
}

//SetRecv라고 보는게 알맞다. 이벤트가 발생하면 recv 받겠다고 설정하는 함수
bool Recv(ClientInfo* info)
{
    //TODO::MAX_BUFFER_SIZE 말고 상황에 따라 Packet의 크기가 달라지고 있으니까 상황마다 맞춰서 해야한다.
    info->overlapped.wsaBuf.len = MAX_BUFFER_SIZE;
    ZeroMemory(info->buf, MAX_BUFFER_SIZE);
    ZeroMemory(&info->overlapped.wsaOverlapped, sizeof(info->overlapped.wsaOverlapped));

    DWORD flags = 0;
    DWORD recvBytes;
    
    int retval = WSARecv(
        info->socket,
        &info->overlapped.wsaBuf,
        1,
        &recvBytes,
        &flags,
        &info->overlapped.wsaOverlapped,
        NULL);
   
    // WSA_IO_PENDIG : 겹치는 작업이 성공적으로 시작되었으며 나중에 완료가 표시
    if ((SOCKET_ERROR == retval) && (WSAGetLastError() != WSA_IO_PENDING))
    {
        err_display("WSARcev");
        info->overlapped.type = OverlappedType::Invalied;
        return false;
    }
    return true;
}


void Send(ClientInfo* info)
{
    info->overlapped.type = OverlappedType::Send;
    DWORD sendBytes, flags = 0;
    int retval;
    //SETTURNPACKET send_packet;
    //memcpy()
    //info->buf = send_packet;

    //info->buf에 클라이언트에서 보낸 데이터가 들어있다.
    BASEPACKET* recv_packet = (BASEPACKET*)&info->buf;
    BASEPACKET* send_packet = {};

    //플레이어 턴 설정 - 플레이어가 데이터를 보내면 무조건 턴이 끝난것으로 취급함
    playerTurn = (playerTurn == CAMP_WHITE) ? CAMP_BLACK : CAMP_WHITE;

    //클라이언트 > 서버 전송용
    switch (recv_packet->packetType)
    {
    case PacketType_MoveObject:
    { //TODO::데이터 전달확인함
        //이제 클라이언트에 전달되는지 확인하고
        //클라이언트에서  말 움직이기.
        //+자기가 한 거 아닐때만
        MOVEOBJECTPACKET* packet = (MOVEOBJECTPACKET*)info->buf;
        packet->packetType = PacketType_MoveObject;
        packet->packetSize = sizeof(MOVEOBJECTPACKET);
        packet->setTurn = playerTurn; //백 먼저 시작 ------------- 흑 전환 
        int check_X = packet->m_iX;
        int check_Y = packet->m_iY;
        send_packet = packet;
    }
        break;
    default: //이외 서버 > 클라이언트 전송용
        break;
    }




    for (auto& clientInfo : g_sockInfoList)
    {
        send(clientInfo.second.socket, (char*)send_packet, send_packet->packetSize, 0);

/*
        retval = WSASend(
            clientInfo.second.socket,
            &info->overlapped.wsaBuf,
            1,
            &sendBytes, flags,
            NULL, NULL);

        //예외처리
        if ((SOCKET_ERROR == retval) && (WSAGetLastError() != WSA_IO_PENDING))
        {
            err_display("WSASend");
            clientInfo.second.overlapped.type = OverlappedType::Invalied;
        }
*/
    }

    if (OverlappedType::Invalied != info->overlapped.type)
        info->overlapped.type = OverlappedType::Recv;

    Recv(info);
}

void CloseSocket(SOCKET socket)
{
    g_sockInfoList.erase((ULONG_PTR)socket);
    closesocket(socket);
}


unsigned int __stdcall ThreadMain(LPVOID)
{
    DWORD bytesTrans;
    SOCKET completionKey;
    ClientInfo* clientInfo;

    while (true)
    {
        bool result = GetQueuedCompletionStatus(
            g_hIOCP,
            &bytesTrans,
            (PULONG_PTR)&completionKey,
            (LPOVERLAPPED*)&clientInfo,
            INFINITE);

        int error = GetLastError();

        if ((!result && WAIT_TIMEOUT != error) ||
            (OverlappedType::Invalied == clientInfo->overlapped.type) ||
            0 == bytesTrans)
        {
            g_lock.lock();
            printf_s("[IOCP 서버] socket(%lu)클라이언트 접속 종료\n", completionKey);
            CloseSocket(completionKey);
            g_lock.unlock();
            continue;
        }

        if (OverlappedType::Recv == clientInfo->overlapped.type)
        {
            g_lock.lock();
            clientInfo->overlapped.wsaBuf.len = bytesTrans;

            printf_s("[수신 socket:%lu] Msg : %s(%d byte)]\n",
                clientInfo->socket,
                clientInfo->overlapped.wsaBuf.buf,
                clientInfo->overlapped.wsaBuf.len);

            // 받은 패킷 그대로 모든 클라이언트에게 보내기.
            Send(clientInfo);
            g_lock.unlock();
        }
    } // while()

    return 0;
} // ThreadMain()