#pragma once
#define WIN32_LEAN_AND_MEAN // ���� ������ �ʴ� WinAPI �ڵ带 ����
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
	HINSTANCE hInstance; // �ν��Ͻ� �ڵ�
	HWND hWnd; // ������ �ڵ�(���ø�ĳ�̼� â�� �ĺ��ϴµ� ���)
	WINDOW_DESC windowDesc; // �����츦 ������ �� �ʿ��� ����(â ũ��, ����, ��Ÿ��)
	bool fullScreen; // ������ ��ü ȭ���� �ĺ�
	int screenWidth, screenHeight; // ȭ�� ���� �� ���� �ػ�(��ü ȭ�� ���)
	WindowContainer* pContainer; //������� ���õ� �ٸ� ������ �Ǵ� ����ü�� ����Ű�� ������. ���ø����̼ǿ��� ������� ���õ� �����͸� ����ȭ�ϰ� �����ϴ� �� ���� �� �ִ�.

public:
	Window();
	~Window();

	//�����츦 �ʱ�ȭ�ϴ� �Լ��Դϴ�. �ʿ��� ������ ������ �����̳�(WindowContainer), �ν��Ͻ� �ڵ�(hInstance), ����(title), �ʺ�(width), ����(height), �� ��ü ȭ�� ��� ����(fullScreen)�� �����Ͽ� �����츦 �ʱ�ȭ�մϴ�.
	bool Intialize(WindowContainer* pContainer, HINSTANCE hInstance, LPCWSTR title, UINT width, UINT height, bool fullScreen = false);

	//������ �̺�Ʈ ������ �����ϰ�, ������ �̺�Ʈ�� ó���ϴ� �Լ��Դϴ�. �����츦 �����ϰ� ����� �Է��� ó���մϴ�.
	void Processing();

	// ������ �ڵ��� ��ȯ�ϴ� �Լ��Դϴ�.
	HWND GetHWND();
	int GetWidth();
	int GetHeight();
	int GetScreenWidth();
	int GetScreenHeight();
	bool IsFullScreen();

private:
	// �������� ����� ũ�⸦ �����ϴ� ���� �Լ��Դϴ�.
	void DescriptionWindow(LPCWSTR title, UINT width, UINT height);
	// ������ Ŭ������ ����ϴ� ���� �Լ��Դϴ�.
	void RegisterWindowClass();
	// �����츦 �����ϰ� ǥ���ϴ� ���� �Լ��Դϴ�.
	bool CreateAndShowWindow(WindowContainer* pContainer);
};

//������ ���ν��� �ݹ� �Լ��Դϴ�. ������ �̺�Ʈ�� ó���ϰ� ������ ��ü�� ���õ� ������ �����մϴ�.
static LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM Iparam);