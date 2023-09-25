#include "Input.h"

std::unique_ptr<InputKeyboard> Input::keyboard = nullptr;
std::unique_ptr<InputMouse> Input::mouse = nullptr;

void Input::Initialize(UINT screenWidth, UINT screenHeight)
{
	keyboard = std::make_unique<InputKeyboard>();
	mouse = std::make_unique<InputMouse>(screenWidth, screenHeight);
}

void Input::Update()
{
	keyboard->Update();
	mouse->Update();
}

void Input::MessageHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	keyboard->MessageHandler(hWnd, uMsg, wParam, lParam);
	mouse->MessageHandler(hWnd, uMsg, wParam, lParam);
}