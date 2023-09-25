#include "InputMouse.h"
#include <memory>

InputMouse::InputMouse(UINT screenWidth, UINT screenHeight)
{
	x = y = 0;
	screenHalfSize.x = screenWidth / 2;
	screenHalfSize.y = ((0 < screenHeight) ? (screenHeight / 2) : screenHalfSize.x);

	for (int i = 0; (int)ButtonType::Count > i; i++) buttonStates[i] = ButtonState::None;
}

InputMouse::~InputMouse()
{
	EndCapture();
}

void InputMouse::Update()
{
	for (int i = 0; (int)ButtonType::Count > i; i++)
	{
		switch (buttonStates[i])
		{
		case ButtonState::Down: buttonStates[i] = ButtonState::Pressed; break;
		case ButtonState::Up: buttonStates[i] = ButtonState::None; break;
		}
	}

	while (!mouseEvents.empty()) mouseEvents.pop();
}

bool InputMouse::IsDown(ButtonType button) const
{
	switch (buttonStates[(int)button])
	{
	case ButtonState::Down:
	case ButtonState::Pressed: return true;
	}
	return false;
}

bool InputMouse::IsUp(ButtonType button) const
{
	return (ButtonState::Up == buttonStates[(int)button]);
}

MouseEvent InputMouse::ReadEvent()
{
	if (mouseEvents.empty()) return MouseEvent();

	MouseEvent currEvent = mouseEvents.front();
	mouseEvents.pop();
	return currEvent;
}

int InputMouse::X() const
{
	return x;
}

int InputMouse::Y() const
{
	return y;
}

bool InputMouse::MessageHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_MOUSEMOVE:			OnMove(LOWORD(lParam), HIWORD(lParam)); return true;

		case WM_LBUTTONDOWN:		OnDown(hWnd, ButtonType::Left, LOWORD(lParam), HIWORD(lParam)); return true;
		case WM_LBUTTONUP:			OnUp(hWnd, ButtonType::Left, LOWORD(lParam), HIWORD(lParam)); return true;

		case WM_RBUTTONDOWN:		OnDown(hWnd, ButtonType::Right, LOWORD(lParam), HIWORD(lParam)); return true;
		case WM_RBUTTONUP:			OnUp(hWnd, ButtonType::Right, LOWORD(lParam), HIWORD(lParam)); return true;

		case WM_MBUTTONDOWN:	OnDown(hWnd, ButtonType::Middle, LOWORD(lParam), HIWORD(lParam)); return true;
		case WM_MBUTTONUP:			OnUp(hWnd, ButtonType::Middle, LOWORD(lParam), HIWORD(lParam)); return true;

		case WM_XBUTTONDOWN:
		{
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);
			switch (GET_XBUTTON_WPARAM(wParam))
			{
			case XBUTTON1: OnDown(hWnd, ButtonType::X1, LOWORD(lParam), HIWORD(lParam)); break;
			case XBUTTON2: OnDown(hWnd, ButtonType::X2, LOWORD(lParam), HIWORD(lParam)); break;
			}
			return true;
		}
		case WM_XBUTTONUP:
		{
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);
			switch (GET_XBUTTON_WPARAM(wParam))
			{
			case XBUTTON1: OnUp(hWnd, ButtonType::X1, LOWORD(lParam), HIWORD(lParam)); break;
			case XBUTTON2: OnUp(hWnd, ButtonType::X2, LOWORD(lParam), HIWORD(lParam)); break;
			}
			return true;
		}
		case WM_MOUSEWHEEL:
		{
			short delta = GET_WHEEL_DELTA_WPARAM(wParam);
			if(0 < delta) OnWheelVertical(1);
			else OnWheelVertical(-1);
			return true;
		}
		case WM_MOUSEHWHEEL:
		{
			short delta = GET_WHEEL_DELTA_WPARAM(wParam);
			if (0 < delta) OnWheelHorizontal(1);
			else OnWheelHorizontal(-1);
			return true;
		}
		case WM_INPUT:
		{
			unsigned int dataSize = 0u;
			// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getrawinputdata
			GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, NULL, &dataSize, sizeof(RAWINPUTHEADER));
			if (0 < dataSize)
			{
				std::unique_ptr<BYTE[]> rawdata = std::make_unique<BYTE[]>(dataSize);
				if (GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, rawdata.get(), &dataSize, sizeof(RAWINPUTHEADER)) == dataSize)
				{
					// https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-rawinput
					RAWINPUT* raw = reinterpret_cast<RAWINPUT*>(rawdata.get());
					if (RIM_TYPEMOUSE == raw->header.dwType) // https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-rawinputheader
					{
						// https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-rawmouse
						OnRawMove(raw->data.mouse.lLastX, raw->data.mouse.lLastY);
					}
				}
			}
			return true;
		}
	}

	return false;
}

void InputMouse::OnDown(HWND hWnd, ButtonType button, int x, int y)
{
	buttonStates[(int)button] = ButtonState::Down;
	mouseEvents.push(MouseEvent(MouseEventType::ButtonDown, x, y, button));
	this->x = x;
	this->y = y;

	StartCapture(hWnd);
}

void InputMouse::OnUp(HWND hWnd, ButtonType button, int x, int y)
{
	buttonStates[(int)button] = ButtonState::Up;
	mouseEvents.push(MouseEvent(MouseEventType::ButtonUp, x, y, button));
	this->x = x;
	this->y = y;

	EndCapture();
}

void InputMouse::OnWheelVertical(int val)
{
	mouseEvents.push(MouseEvent(MouseEventType::WheelVertical, 0, val));
}

void InputMouse::OnWheelHorizontal(int val)
{
	mouseEvents.push(MouseEvent(MouseEventType::WheelHorizontal, val, 0));
}

void InputMouse::OnMove(int x, int y)
{
	mouseEvents.push(MouseEvent(MouseEventType::Move, x, y));
	this->x = x;
	this->y = y;
}

void InputMouse::OnRawMove(int x, int y)
{
	mouseEvents.push(MouseEvent(MouseEventType::RawMove, x, y));
}

void InputMouse::StartCapture(HWND hWnd)
{
	RECT window;
	GetWindowRect(hWnd, &window);
	int center_x = window.left + (window.right - window.left) / 2;
	int center_y = window.top + (window.bottom - window.top) / 2;
	POINT leftTop = { center_x - screenHalfSize.x, center_y - screenHalfSize.y };
	POINT rightBottom = { center_x + screenHalfSize.x, center_y + screenHalfSize.y };
	RECT rcClip = { leftTop.x, leftTop.y, rightBottom.x, rightBottom.y };
	
	SetCapture(hWnd);
	ClientToScreen(hWnd, &leftTop);
	ClientToScreen(hWnd, &rightBottom);
	ClipCursor(&rcClip);
}

void InputMouse::EndCapture()
{
	ClipCursor(NULL);
	ReleaseCapture();
}