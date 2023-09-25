#pragma once
#include <Windows.h>
#include <queue>

enum class ButtonType { Left = 0, Right, Middle, X1, X2, Count, Invalid };
enum class MouseEventType { ButtonDown, ButtonUp, WheelVertical, WheelHorizontal, Move, RawMove, Invalid };
struct MouseEvent
{
	ButtonType button;
	MouseEventType eventType;
	int x, y;

	MouseEvent() : button(ButtonType::Invalid), eventType(MouseEventType::Invalid), x(0), y(0) {}
	MouseEvent(MouseEventType eventType, int x, int y, ButtonType button = ButtonType::Invalid) : button(button), eventType(eventType), x(x), y(y) {}
};
class InputMouse
{
private:
	enum class ButtonState { None, Down, Pressed, Up };

	ButtonState buttonStates[(int)ButtonType::Count];
	std::queue<MouseEvent> mouseEvents;
	int x, y;
	POINT screenHalfSize;

	InputMouse();
public:
	InputMouse(UINT screenWidth, UINT screenHeight = 0);
	~InputMouse();

	void Update();

	bool IsDown(ButtonType button) const;
	bool IsUp(ButtonType button) const;
	MouseEvent ReadEvent();

	int X() const;
	int Y() const;

	bool MessageHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	void OnDown(HWND hWnd, ButtonType button, int x, int y);
	void OnUp(HWND hWnd, ButtonType button, int x, int y);
	void OnWheelVertical(int val);
	void OnWheelHorizontal(int val);
	void OnMove(int x, int y);
	void OnRawMove(int x, int y);

	void StartCapture(HWND hWnd);
	void EndCapture();
};