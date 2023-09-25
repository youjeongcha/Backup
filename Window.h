#pragma once
#define WIN32_LEAN_AND_MEAN // 자주 사용되지 않는 WinAPI 코드를 제외
#include <Windows.h>
#include "Log.h"

struct WINDOW_DESC
{
	LPCWSTR title;
	int x, y;
	UINT width, height;
	DWORD dwStyle;
};

class WindowContainer;

class Window
{
private:
	HINSTANCE hInstance; // 인스턴스 핸들
	HWND hWnd; // 윈도우 핸들(애플리캐이션 창을 식별하는데 사용)
	WINDOW_DESC windowDesc; // 윈도우를 생성할 때 필요한 설정(창 크기, 제목, 스타일)
	bool fullScreen; // 윈도우 전체 화면모드 식별
	int screenWidth, screenHeight; // 화면 가로 및 세로 해상도(전체 화면 모드)
	WindowContainer* pContainer; //윈도우와 관련된 다른 데이터 또는 구조체를 가리키는 포인터. 애플리케이션에서 윈도우와 관련된 데이터를 구조화하고 관리하는 데 사용될 수 있다.

public:
	Window();
	~Window();

	//윈도우를 초기화하는 함수입니다. 필요한 정보인 윈도우 컨테이너(WindowContainer), 인스턴스 핸들(hInstance), 제목(title), 너비(width), 높이(height), 및 전체 화면 모드 여부(fullScreen)를 전달하여 윈도우를 초기화합니다.
	bool Intialize(WindowContainer* pContainer, HINSTANCE hInstance, LPCWSTR title, UINT width, UINT height, bool fullScreen = false);

	//윈도우 이벤트 루프를 시작하고, 윈도우 이벤트를 처리하는 함수입니다. 윈도우를 실행하고 사용자 입력을 처리합니다.
	void Processing();

	// 윈도우 핸들을 반환하는 함수입니다.
	HWND GetHWND();
	int GetWidth();
	int GetHeight();
	int GetScreenWidth();
	int GetScreenHeight();
	bool IsFullScreen();

private:
	// 윈도우의 제목과 크기를 설정하는 내부 함수입니다.
	void DescriptionWindow(LPCWSTR title, UINT width, UINT height);
	// 윈도우 클래스를 등록하는 내부 함수입니다.
	void RegisterWindowClass();
	// 윈도우를 생성하고 표시하는 내부 함수입니다.
	bool CreateAndShowWindow(WindowContainer* pContainer);
};

//윈도우 프로시저 콜백 함수입니다. 윈도우 이벤트를 처리하고 윈도우 객체와 관련된 정보를 전달합니다.
static LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM Iparam);