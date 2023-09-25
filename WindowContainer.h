#pragma once
#include <memory>
#include "Window.h"
#include "Input/Input.h"
#include "Timer.h"
#include <hidusage.h> // HID ��ũ�θ� �������� �߰�. �ݵ�� #include <Windows.h>���� �Ʒ� ���ο� �ۼ�.
#include "Graphics.h"

class WindowContainer abstract
{
protected:
	//unique_ptr ����Ʈ ������. �ش� ��ü �Ǵ� �迭�� �ʿ� ������ �ڵ����� �޸𸮸� �����Ѵ�.
	std::unique_ptr<Window> window;
	std::unique_ptr<Timer> timer;
	std::unique_ptr<Graphics> gfx;

public:
	WindowContainer()
	{
		//Setup Raw Input
		// WM_INPUT�� ȣ���� �Ϸ��� �ݵ�� ������ �Ͽ��� �Ѵ�.
		static bool rawInputInitialized = false;

		if (!rawInputInitialized)
		{
			RAWINPUTDEVICE ridev; // RAWINPUTDEVICE : https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-rawinputdevice
			ridev.usUsagePage = HID_USAGE_PAGE_GENERIC;  // �Ϲ� ����ũž ��Ʈ��, https://learn.microsoft.com/en-us/windows-hardware/drivers/hid/hid-usages#usage-page
			ridev.usUsage = HID_USAGE_GENERIC_MOUSE; // ���콺, https://learn.microsoft.com/en-us/windows-hardware/drivers/hid/hid-usages#usage-id
			ridev.dwFlags = 0; 
			ridev.hwndTarget = NULL; // NULL�̸� Ű���� ��Ŀ���� ������.

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