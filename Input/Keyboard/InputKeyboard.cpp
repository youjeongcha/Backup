#include "InputKeyboard.h"
#include <algorithm>

InputKeyboard::InputKeyboard()
{
	for (int i = 0; 256 > i; i++) keySates[i] = KeyState::None;
	pressedAnyKey = false;
}

void InputKeyboard::Update()
{
	for (int i = 0; 256 > i; i++)
	{
		switch (keySates[i])
		{
		case KeyState::Down: keySates[i] = KeyState::Pressed; break;
		case KeyState::Up: keySates[i] = KeyState::None; break;
		}
	}

	pressedAnyKey = false;

	while (!charBuffer.empty()) charBuffer.pop();
}

bool InputKeyboard::IsDown(const unsigned char key) const
{
	return (KeyState::Down == keySates[key]);
}

bool InputKeyboard::IsPressed(const unsigned char key) const
{
	switch (keySates[key])
	{
	case KeyState::Down:
	case KeyState::Pressed:
		return true;
	}
	return false;
}

bool InputKeyboard::IsUp(const unsigned char key) const
{
	return (KeyState::Up == keySates[key]);
}

bool InputKeyboard::PressedAnyKey() const
{
	return pressedAnyKey;
}

unsigned char InputKeyboard::ReadChar()
{
	if (charBuffer.empty()) 	return '\0';

	unsigned char ch = charBuffer.front();
	charBuffer.pop();
	return ch;
}

bool InputKeyboard::MessageHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_KEYDOWN:
		{
			// lParam : https://learn.microsoft.com/ko-kr/windows/win32/inputdev/wm-char
			if (!(lParam & 0x40000000/*30*/))
			{
				unsigned char keycode = static_cast<unsigned char>(wParam);
				OnDown(keycode);
				pressedAnyKey = true;
			}
			return true;
		}
		case WM_KEYUP:
		{
			unsigned char keycode = static_cast<unsigned char>(wParam);
			OnUp(keycode);
			return true;
		}
		case WM_CHAR:
		{
			unsigned char ch = static_cast<unsigned char>(wParam);
			OnChar(ch);
			return true;
		}
		default: return false;
	}
}

void InputKeyboard::OnDown(const unsigned char key)
{
	keySates[key] = KeyState::Down;
}

void InputKeyboard::OnUp(const unsigned char key)
{
	keySates[key] = KeyState::Up;
}

void InputKeyboard::OnChar(const unsigned char ch)
{
	charBuffer.push(ch);
}