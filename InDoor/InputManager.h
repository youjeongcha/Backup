#pragma once
#include "Singleton.h"
#include <unordered_map>

#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

/*
	InputManager 클랙스의 생성자가 private이기 때문에 Singleton class를 friend로 만들어 준다
	Input 전용 프로시저를 만들어 인풋 관련 처리를 한다
*/

namespace ENGINE
{
	class InputManager : public Singleton<InputManager>
	{
	private:
		enum class InputState
		{
			NONE, DOWN, PRESSED, UP
		};

		//map보다 더 빠른 탐색을 위한 자료구조, 중복 데이터를 허용하지 않는다.
		//map보다 더 많은 데이터를 관리할 때 높은 성능을 발휘한다.
		std::unordered_map<UINT, InputState> keys; //key 입력 상태 정보.
		std::map<UINT, InputState> mouse; //마우스 버튼 상태 정보.
		POINT mousePosition; //현재 마우스 커서의 위치.

		std::string str; //입력된 키의 문자 정보.

		InputManager() : mousePosition({ 0,0 }) {}
	public:
		~InputManager();
		void Initialize() {}
		void Release();
		void Update();
		//?
		void InputProc(UINT message, WPARAM wParam, LPARAM IParam); //Input Procedure 
		LPCSTR GetChar() { return str.c_str(); } //입력한 키의 문자 정보를 알아온다.

		//키
		BOOL GetKeyDown(UINT keyID) { return KeyCheck(keyID, InputState::DOWN); } //확인하려는 Key가 현재 프레임에서 눌러졌는가?
		BOOL GetKeyPressed(UINT keyID) { return KeyCheck(keyID, InputState::PRESSED) || KeyCheck(keyID, InputState::DOWN); } //확인하려는 Key가 현재 프레임에서 눌러진 상태인가?
		BOOL GetKeyUp(UINT keyID) { return KeyCheck(keyID, InputState::UP); } //확인하려는 Key가 현재 프레임에서 눌러 지지 않았는가?
		BOOL PressedAnyKey();

		//마우스
		BOOL GetMouseButtonDown(UINT keyID) { return ButtonCheck(keyID, InputState::DOWN); }
		BOOL GetMouseButtonPressed(UINT keyID) { return ButtonCheck(keyID, InputState::PRESSED) || ButtonCheck(keyID, InputState::DOWN); }
		BOOL GetMouseButtonUp(UINT keyID) { return ButtonCheck(keyID, InputState::UP); }
		POINT GetMousePosition() const { return mousePosition; }

	private:
		//마우스 커서
		//마우스 커서 이동 범위 제한.
		void StartCapture(); 
		//마우스 커서 이동 제한 종료.
		void EndCapture(); 

		//키
		void SetKeyDown(UINT keyID) { keys[keyID] = InputState::DOWN; } //현재 입력된 키를 누른 상태로 변경.
		void SetKeyUp(UINT keyID) { keys[keyID] = InputState::UP; } //현재 입력된 키를 누르지 않은 상태로 변경.

		//마우스 버튼
		void SetMouseButtonDown(UINT keyID);
		void SetMouseButtonUp(UINT keyID);
		void SetMousePosition(LPARAM IParam) { mousePosition = { LOWORD(IParam), HIWORD(IParam) }; }

		bool KeyCheck(UINT keyID, CONST InputState& state);
		bool ButtonCheck(UINT keyID, CONST InputState& state);
		friend Singleton;
	};

#define InputMgr InputManager::GetInstance()
} //namespace ENGINE

#endif // !INPUT_MANAGER_H