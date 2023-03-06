#include <Windows.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "GameManager.h"
#include "WndClassCreate.h"
#include "resource.h"

//개선할 수 있는 것들 - 조언 기록(치명적이진 않은)
//개선 : m_BitmapRect을 xy까지 클래스 커스텀 해서 상속
//개선 : BG IMG 출력 함수 삭제
//개선 : 0 인자 변경

#define GMMgr GameManager::Get_Instance()

LRESULT CALLBACK WndProc_Main(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProc_Sub(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst; //어플리케이션의 핸들값
LPCTSTR lpszClassMain = TEXT("CardGame");
LPCTSTR lpszClassSub = TEXT("†");

BitMapManager BitMapMgr_Main;
BitMapManager BitMapMgr_Sub;

//HDC g_hBackBuffer; //배경 비트맵 DC : 전역변수 선언

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPervlnstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	HWND hWndSub;
	MSG Message;
	WndClassCreate WndClassMain(hInstance, lpszClassMain, WHITE_BRUSH);
	WndClassCreate WndClassSub(hInstance, lpszClassSub, BLACK_BRUSH);
	g_hInst = hInstance;

	//클래스로 객체 생성 //디폴트에서 함수로 되어 있던걸 이렇게 해둔 것
	//메인 창 등록
	WndClassMain.WndClass.lpfnWndProc = WndProc_Main;	//프로세스 함수 호출
	RegisterClass(&WndClassMain.WndClass);

	//서브 창 등록
	WndClassSub.WndClass.lpfnWndProc = WndProc_Sub;
	RegisterClass(&WndClassSub.WndClass);
 

	//WS_SYSMENU(시스템 메뉴를 가진 윈도우를 만든다) | 
	//WS_MINIMIZEBOX(최소화 버튼을 만든다, WS_CONTEXTHELP 스타일과 결합할 수 없다. WS_SYSTEM 스타일로 지정해야 한다.)
	//예전에는 WS_MINIMIZEBOX에 창 조절 함수가 포함되어 있었는데 현재는 빠져있어서. 창조절까지 하려면 이걸 사용해야 한다.


	//윈도우 창의 핸들 값
	//메인
	hWnd = CreateWindow(lpszClassMain, lpszClassMain, WS_SYSMENU | WS_MINIMIZEBOX, MAIN_X, MAIN_Y, MAIN_W, MAIN_H,
		NULL, (HMENU)NULL, hInstance, NULL);

	//서브 일정 단계가 지나고 출력하도록
	hWndSub = CreateWindow(lpszClassSub, lpszClassSub, WS_OVERLAPPED | WS_MINIMIZEBOX, SUB_X, SUB_Y, SUB_W, SUB_H,
		NULL, (HMENU)NULL, hInstance, NULL);  //부모 클래스를 받으면 부모 클래스가 상위 노출이 안된다.

	//메인 and 서브 창 초기화는 여기서
	GMMgr->Init(&BitMapMgr_Main, &BitMapMgr_Sub, hWnd, hWndSub);

	ShowWindow(hWndSub, nCmdShow);
	ShowWindow(hWnd, nCmdShow);
	
	SetForegroundWindow(hWnd); //컴퓨터 그래픽스 ppt 확인


	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	
	GMMgr->Kill_AllTimer();

	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc_Main(HWND hWnd_Main, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	POINT Point;

	switch (iMessage)
	{
	case WM_LBUTTONDOWN:
		Point.x = LOWORD(lParam);
		Point.y = HIWORD(lParam);

		if (GMMgr->ColliderCheck(Point))
			InvalidateRect(hWnd_Main, NULL, true); //이미지를 클릭하면 화면 지우고 다시 그려야. 데이터 상 뒤집힘 > 시각화
	
		return 0;
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd_Main, &ps);
		GMMgr->Draw(hdc, g_hInst);
		EndPaint(hWnd_Main, &ps);

		return 0;
	}
	case WM_TIMER:
		if (GMMgr->Timer(wParam))
		{
			InvalidateRect(hWnd_Main, NULL, true);
			//서브 화면 배경그림 깔아주기 위해 비활성화
		}

		if (GMMgr->Get_Scene() >= SEQUENCE_SHOWCARD)
			InvalidateRect(GMMgr->Get_HWND_Sub(), NULL, true);

		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd_Main, iMessage, wParam, lParam));
}

LRESULT CALLBACK WndProc_Sub(HWND hWnd_Sub, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	POINT Point;


	switch (iMessage)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd_Sub, &ps);
		GMMgr->SubDraw(hdc);
		EndPaint(hWnd_Sub, &ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return(DefWindowProc(hWnd_Sub, iMessage, wParam, lParam));
}