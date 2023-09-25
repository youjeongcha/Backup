#pragma once
#include <memory>
#include "Keyboard/InputKeyboard.h"
#include "Mouse/InputMouse.h"

class Input
{
private:
	static std::unique_ptr<InputKeyboard> keyboard;
	static std::unique_ptr<InputMouse> mouse;

public:
	static void Initialize(UINT screenWidth, UINT screenHeight = 0);

	static InputKeyboard* GetKeyboard() { return keyboard.get(); }
	static InputMouse* GetMouse() { return mouse.get(); }

	static void Update();
	static void MessageHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};