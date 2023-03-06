#include <Windows.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "GameManager.h"
#include "WndClassCreate.h"
#include "resource.h"

//������ �� �ִ� �͵� - ���� ���(ġ�������� ����)
//���� : m_BitmapRect�� xy���� Ŭ���� Ŀ���� �ؼ� ���
//���� : BG IMG ��� �Լ� ����
//���� : 0 ���� ����

#define GMMgr GameManager::Get_Instance()

LRESULT CALLBACK WndProc_Main(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProc_Sub(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst; //���ø����̼��� �ڵ鰪
LPCTSTR lpszClassMain = TEXT("CardGame");
LPCTSTR lpszClassSub = TEXT("��");

BitMapManager BitMapMgr_Main;
BitMapManager BitMapMgr_Sub;

//HDC g_hBackBuffer; //��� ��Ʈ�� DC : �������� ����

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPervlnstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	HWND hWndSub;
	MSG Message;
	WndClassCreate WndClassMain(hInstance, lpszClassMain, WHITE_BRUSH);
	WndClassCreate WndClassSub(hInstance, lpszClassSub, BLACK_BRUSH);
	g_hInst = hInstance;

	//Ŭ������ ��ü ���� //����Ʈ���� �Լ��� �Ǿ� �ִ��� �̷��� �ص� ��
	//���� â ���
	WndClassMain.WndClass.lpfnWndProc = WndProc_Main;	//���μ��� �Լ� ȣ��
	RegisterClass(&WndClassMain.WndClass);

	//���� â ���
	WndClassSub.WndClass.lpfnWndProc = WndProc_Sub;
	RegisterClass(&WndClassSub.WndClass);
 

	//WS_SYSMENU(�ý��� �޴��� ���� �����츦 �����) | 
	//WS_MINIMIZEBOX(�ּ�ȭ ��ư�� �����, WS_CONTEXTHELP ��Ÿ�ϰ� ������ �� ����. WS_SYSTEM ��Ÿ�Ϸ� �����ؾ� �Ѵ�.)
	//�������� WS_MINIMIZEBOX�� â ���� �Լ��� ���ԵǾ� �־��µ� ����� �����־. â�������� �Ϸ��� �̰� ����ؾ� �Ѵ�.


	//������ â�� �ڵ� ��
	//����
	hWnd = CreateWindow(lpszClassMain, lpszClassMain, WS_SYSMENU | WS_MINIMIZEBOX, MAIN_X, MAIN_Y, MAIN_W, MAIN_H,
		NULL, (HMENU)NULL, hInstance, NULL);

	//���� ���� �ܰ谡 ������ ����ϵ���
	hWndSub = CreateWindow(lpszClassSub, lpszClassSub, WS_OVERLAPPED | WS_MINIMIZEBOX, SUB_X, SUB_Y, SUB_W, SUB_H,
		NULL, (HMENU)NULL, hInstance, NULL);  //�θ� Ŭ������ ������ �θ� Ŭ������ ���� ������ �ȵȴ�.

	//���� and ���� â �ʱ�ȭ�� ���⼭
	GMMgr->Init(&BitMapMgr_Main, &BitMapMgr_Sub, hWnd, hWndSub);

	ShowWindow(hWndSub, nCmdShow);
	ShowWindow(hWnd, nCmdShow);
	
	SetForegroundWindow(hWnd); //��ǻ�� �׷��Ƚ� ppt Ȯ��


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
			InvalidateRect(hWnd_Main, NULL, true); //�̹����� Ŭ���ϸ� ȭ�� ����� �ٽ� �׷���. ������ �� ������ > �ð�ȭ
	
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
			//���� ȭ�� ���׸� ����ֱ� ���� ��Ȱ��ȭ
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