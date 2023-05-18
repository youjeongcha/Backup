#include "InputManager.h"
#include "SceneManager.h"

namespace ENGINE
{
	InputManager::~InputManager() { Release(); }

	/*입력 관리자 객체의 리소스를 해제합니다. 문자열(str)을 비우고, 키(keys)와 마우스 버튼(mouse) 관련 정보를 모두 초기화합니다. 또한, 마우스 캡처(Capture)를 종료합니다.*/
	void InputManager::Release()
	{
		str = "";
		keys.clear();
		mouse.clear();
		EndCapture();
	}

	/*입력 관리자를 업데이트합니다. 키와 마우스 버튼의 상태를 갱신하고, 눌린 상태인 경우에는 눌림 상태(InputState::PRESSED)로 변경하고, 놓인 상태인 경우에는 상태를 초기화(InputState::NONE)합니다.*/
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

	/*윈도우 메시지를 받아서 처리합니다. 주요한 윈도우 메시지에 따라서 키보드 입력 및 마우스 입력을 처리하고, 관련 정보를 업데이트합니다.*/
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
				SetMouseButtonDown(VK_XBUTTON1);  // 마우스 왼쪽 뒤 버튼.
				break; 
			case XBUTTON2: 
				SetMouseButtonDown(VK_XBUTTON2); // 마우스 왼쪽 앞 버튼.
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
				SetMouseButtonUp(VK_XBUTTON1); // 마우스 왼쪽 뒤 버튼.
				break; 
			case XBUTTON2: 
				SetMouseButtonUp(VK_XBUTTON2); // 마우스 왼쪽 앞 버튼.
				break; 
			}
		}
		break;
		case WM_MOUSEMOVE: SetMousePosition(wParam);
			break;
		}
	}

	/*현재 눌린 상태나 눌린 상태로 유지 중인 키가 있는지 확인합니다. 만약 하나라도 있는 경우에는 true를 반환하고, 그렇지 않은 경우에는 false를 반환합니다.*/
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

	/* 마우스 입력을 캡처하여 윈도우 내에서만 유효한 좌표로 변환하고, 마우스가 화면을 벗어나지 않도록 설정합니다. 캡처된 영역 내에서 마우스 이동 및 클릭 이벤트를 처리합니다.*/
	void InputManager::StartCapture() //?
	{ //캡쳐 좌표 관리?
		HWND hWnd = SceneMgr->GetHWND();

		SetCapture(hWnd);
		POINT leftTop = { 0,0 };
		POINT rightBottom = { SceneMgr->GetWidth() + 1, SceneMgr->GetHeight() + 1 };

		ClientToScreen(hWnd, &leftTop);
		ClientToScreen(hWnd, &rightBottom);

		RECT clip = { leftTop.x, leftTop.y, rightBottom.x, rightBottom.y };
		ClipCursor(&clip);
	}

	/*마우스 캡처를 종료하고, 마우스의 이동 제한을 해제합니다.*/
	void InputManager::EndCapture()
	{
		ClipCursor(NULL);
		ReleaseCapture();
	}

	/*특정 마우스 버튼(keyID)이 눌린 상태로 설정합니다. 이때, 마우스 입력 캡처를 시작합니다.*/
	void InputManager::SetMouseButtonDown(UINT keyID)
	{
		StartCapture();
		mouse[keyID] = InputState::DOWN;
	}

	/*특정 마우스 버튼(keyID)이 놓인 상태로 설정합니다. 이때, 마우스 입력 캡처를 종료합니다.*/
	void InputManager::SetMouseButtonUp(UINT keyID)
	{
		mouse[keyID] = InputState::UP;
		EndCapture();
	}

	/*특정 키(keyID)가 주어진 상태(state)인지 확인합니다. 입력된 상태가 저장된 keys 맵에서 해당 키를 찾아서 비교하고, 일치하는 경우 true를 반환합니다. 일치하는 키를 찾지 못한 경우에는 keys 맵에 해당 키와 초기 상태(InputState::NONE)를 추가하고, false를 반환합니다.*/
	bool InputManager::KeyCheck(UINT keyID, const InputState& state)
	{
		std::unordered_map<UINT, InputState>::iterator iter = keys.find(keyID);

		if (keys.end() != iter)
			return (state == iter->second);
		
		keys.insert(std::make_pair(keyID, InputState::NONE));
		return false;
	}

	/*특정 마우스 버튼(keyID)이 주어진 상태(state)인지 확인합니다*/
	bool InputManager::ButtonCheck(UINT keyID, const InputState& state)
	{
		std::map<UINT, InputState>::iterator iter = mouse.find(keyID);

		if (mouse.end() != iter)
			return (state == iter->second);

		mouse.insert(std::make_pair(keyID, InputState::NONE));
		return false;
	}

} //namespace ENGINE