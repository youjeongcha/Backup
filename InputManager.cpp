#include "InputManager.h"
#include "SceneManager.h"

namespace ENGINE
{
	InputManager::~InputManager() { Release(); }

	/*�Է� ������ ��ü�� ���ҽ��� �����մϴ�. ���ڿ�(str)�� ����, Ű(keys)�� ���콺 ��ư(mouse) ���� ������ ��� �ʱ�ȭ�մϴ�. ����, ���콺 ĸó(Capture)�� �����մϴ�.*/
	void InputManager::Release()
	{
		str = "";
		keys.clear();
		mouse.clear();
		EndCapture();
	}

	/*�Է� �����ڸ� ������Ʈ�մϴ�. Ű�� ���콺 ��ư�� ���¸� �����ϰ�, ���� ������ ��쿡�� ���� ����(InputState::PRESSED)�� �����ϰ�, ���� ������ ��쿡�� ���¸� �ʱ�ȭ(InputState::NONE)�մϴ�.*/
	void InputManager::Update()
	{
		str = " ";

		for (std::pair<CONST UINT, InputState>& key : keys)
		{
			switch (key.second)
			{
			case InputState::DOWN:
				key.second = InputState::PRESSED;
				break;
			case InputState::UP:
				key.second = InputState::NONE;
				break;
			}
		}

		for (std::pair<CONST UINT, InputState>& button : mouse)
		{
			switch (button.second)
			{
			case InputState::DOWN:
				button.second = InputState::PRESSED;
				break;
			case InputState::UP:
				button.second = InputState::NONE;
				break;
			}
		}
	}

	/*������ �޽����� �޾Ƽ� ó���մϴ�. �ֿ��� ������ �޽����� ���� Ű���� �Է� �� ���콺 �Է��� ó���ϰ�, ���� ������ ������Ʈ�մϴ�.*/
	void InputManager::InputProc(UINT message, WPARAM wParam, LPARAM IParam)
	{
		switch (message)
		{
		case WM_CHAR: 
			str = wParam; 
			break;
		case WM_KEYDOWN: 
		case WM_SYSKEYDOWN: 
			SetKeyDown(wParam); 
			break;
		case WM_KEYUP: 
		case WM_SYSKEYUP: 
			SetKeyUp(wParam); 
			break;
		case WM_LBUTTONDOWN: 
			SetMouseButtonDown(VK_LBUTTON); 
			break;
		case WM_RBUTTONDOWN: 
			SetMouseButtonDown(VK_RBUTTON); 
			break;
		case WM_MBUTTONDOWN: 
			SetMouseButtonDown(VK_MBUTTON); 
			break;
		case WM_XBUTTONDOWN:
		{
			switch (wParam)
			{
			case XBUTTON1: 
				SetMouseButtonDown(VK_XBUTTON1);  // ���콺 ���� �� ��ư.
				break; 
			case XBUTTON2: 
				SetMouseButtonDown(VK_XBUTTON2); // ���콺 ���� �� ��ư.
				break; 
			}
		}
		break;
		case WM_LBUTTONUP: 
			SetMouseButtonUp(VK_LBUTTON); 
			break;
		case WM_RBUTTONUP: 
			SetMouseButtonUp(VK_RBUTTON); 
			break;
		case WM_MBUTTONUP: 
			SetMouseButtonUp(VK_MBUTTON); 
			break;
		case WM_XBUTTONUP:
		{
			switch (wParam)
			{
			case XBUTTON1: 
				SetMouseButtonUp(VK_XBUTTON1); // ���콺 ���� �� ��ư.
				break; 
			case XBUTTON2: 
				SetMouseButtonUp(VK_XBUTTON2); // ���콺 ���� �� ��ư.
				break; 
			}
		}
		break;
		case WM_MOUSEMOVE: SetMousePosition(wParam);
			break;
		}
	}

	/*���� ���� ���³� ���� ���·� ���� ���� Ű�� �ִ��� Ȯ���մϴ�. ���� �ϳ��� �ִ� ��쿡�� true�� ��ȯ�ϰ�, �׷��� ���� ��쿡�� false�� ��ȯ�մϴ�.*/
	BOOL InputManager::PressedAnyKey()
	{
		for (std::pair<const UINT, InputState>& key : keys)
		{
			switch (key.second)
			{
			case InputState::DOWN:
			case InputState::PRESSED:
				return true;
			}
		}
		return false;
	}

	/* ���콺 �Է��� ĸó�Ͽ� ������ �������� ��ȿ�� ��ǥ�� ��ȯ�ϰ�, ���콺�� ȭ���� ����� �ʵ��� �����մϴ�. ĸó�� ���� ������ ���콺 �̵� �� Ŭ�� �̺�Ʈ�� ó���մϴ�.*/
	void InputManager::StartCapture() //?
	{ //ĸ�� ��ǥ ����?
		HWND hWnd = SceneMgr->GetHWND();

		SetCapture(hWnd);
		POINT leftTop = { 0,0 };
		POINT rightBottom = { SceneMgr->GetWidth() + 1, SceneMgr->GetHeight() + 1 };

		ClientToScreen(hWnd, &leftTop);
		ClientToScreen(hWnd, &rightBottom);

		RECT clip = { leftTop.x, leftTop.y, rightBottom.x, rightBottom.y };
		ClipCursor(&clip);
	}

	/*���콺 ĸó�� �����ϰ�, ���콺�� �̵� ������ �����մϴ�.*/
	void InputManager::EndCapture()
	{
		ClipCursor(NULL);
		ReleaseCapture();
	}

	/*Ư�� ���콺 ��ư(keyID)�� ���� ���·� �����մϴ�. �̶�, ���콺 �Է� ĸó�� �����մϴ�.*/
	void InputManager::SetMouseButtonDown(UINT keyID)
	{
		StartCapture();
		mouse[keyID] = InputState::DOWN;
	}

	/*Ư�� ���콺 ��ư(keyID)�� ���� ���·� �����մϴ�. �̶�, ���콺 �Է� ĸó�� �����մϴ�.*/
	void InputManager::SetMouseButtonUp(UINT keyID)
	{
		mouse[keyID] = InputState::UP;
		EndCapture();
	}

	/*Ư�� Ű(keyID)�� �־��� ����(state)���� Ȯ���մϴ�. �Էµ� ���°� ����� keys �ʿ��� �ش� Ű�� ã�Ƽ� ���ϰ�, ��ġ�ϴ� ��� true�� ��ȯ�մϴ�. ��ġ�ϴ� Ű�� ã�� ���� ��쿡�� keys �ʿ� �ش� Ű�� �ʱ� ����(InputState::NONE)�� �߰��ϰ�, false�� ��ȯ�մϴ�.*/
	bool InputManager::KeyCheck(UINT keyID, const InputState& state)
	{
		std::unordered_map<UINT, InputState>::iterator iter = keys.find(keyID);

		if (keys.end() != iter)
			return (state == iter->second);
		
		keys.insert(std::make_pair(keyID, InputState::NONE));
		return false;
	}

	/*Ư�� ���콺 ��ư(keyID)�� �־��� ����(state)���� Ȯ���մϴ�*/
	bool InputManager::ButtonCheck(UINT keyID, const InputState& state)
	{
		std::map<UINT, InputState>::iterator iter = mouse.find(keyID);

		if (mouse.end() != iter)
			return (state == iter->second);

		mouse.insert(std::make_pair(keyID, InputState::NONE));
		return false;
	}

} //namespace ENGINE