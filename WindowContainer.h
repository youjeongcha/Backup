#pragma once
#include <memory>
#include "Window.h"
#include "Input/Input.h"
#include "Timer.h"
#include <hidusage.h> // HID 매크로를 쓰기위해 추가. 반드시 #include <Windows.h>보다 아래 라인에 작성.
#include "Graphics.h"

class WindowContainer abstract
{
protected:
	//unique_ptr 스마트 포인터. 해당 객체 또는 배열이 필요 없을때 자동으로 메모리를 해제한다.
	std::unique_ptr<Window> window;
	std::unique_ptr<Timer> timer;
	std::unique_ptr<Graphics> gfx;

public:
	WindowContainer()
	{
		//Setup Raw Input
		// WM_INPUT을 호출을 하려면 반드시 세팅을 하여야 한다.
		static bool rawInputInitialized = false;

		if (!rawInputInitialized)
		{
			RAWINPUTDEVICE ridev; // RAWINPUTDEVICE : https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-rawinputdevice
			ridev.usUsagePage = HID_USAGE_PAGE_GENERIC;  // 일반 데스크탑 컨트롤, https://learn.microsoft.com/en-us/windows-hardware/drivers/hid/hid-usages#usage-page
			ridev.usUsage = HID_USAGE_GENERIC_MOUSE; // 마우스, https://learn.microsoft.com/en-us/windows-hardware/drivers/hid/hid-usages#usage-id
			ridev.dwFlags = 0; 
			ridev.hwndTarget = NULL; // NULL이면 키보드 포커스에 따른다.

			// RegisterRawInputDevices : https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-registerrawinputdevices
			if (!RegisterRawInputDevices(&ridev, 1, sizeof(ridev)))
			{
				Log::ErrorMsg(GetLastError(), "Failed to register raw input devices.");
				exit(-1);
			}
		}
	}

	virtual LRESULT CALLBACK MessageHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		assert("WindowContainer::MessageHandler must be overridden." && 0);
		return 0;
	}

	virtual bool Update()
	{
		assert("WindowContainer::Update must be overridden." && 0);
		return false;
	}

	virtual void RenderFrame()
	{
		assert("WindowContainer::RenderFrame must be overridden." && 0);
	}

	Window* GetWindow() const { return window.get(); }
	Timer* GetTimer() const { return timer.get(); }
};