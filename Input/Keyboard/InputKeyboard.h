#pragma once
#include <Windows.h>
#include <queue>

class InputKeyboard
{
private:
	enum class KeyState { None, Down, Pressed, Up };

	KeyState keySates[256];
	bool pressedAnyKey;
	std::queue<unsigned char> charBuffer;

public:
	InputKeyboard();

	void Update();

	bool IsDown(const unsigned char key) const;
	bool IsPressed(const unsigned char key) const;
	bool IsUp(const unsigned char key) const;
	bool PressedAnyKey() const;
	unsigned char ReadChar();

	bool MessageHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	void OnDown(const unsigned char key);
	void OnUp(const unsigned char key);
	void OnChar(const unsigned char ch);
};

