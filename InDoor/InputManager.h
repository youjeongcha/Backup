#pragma once
#include "Singleton.h"
#include <unordered_map>

#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

/*
	InputManager Ŭ������ �����ڰ� private�̱� ������ Singleton class�� friend�� ����� �ش�
	Input ���� ���ν����� ����� ��ǲ ���� ó���� �Ѵ�
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

		//map���� �� ���� Ž���� ���� �ڷᱸ��, �ߺ� �����͸� ������� �ʴ´�.
		//map���� �� ���� �����͸� ������ �� ���� ������ �����Ѵ�.
		std::unordered_map<UINT, InputState> keys; //key �Է� ���� ����.
		std::map<UINT, InputState> mouse; //���콺 ��ư ���� ����.
		POINT mousePosition; //���� ���콺 Ŀ���� ��ġ.

		std::string str; //�Էµ� Ű�� ���� ����.

		InputManager() : mousePosition({ 0,0 }) {}
	public:
		~InputManager();
		void Initialize() {}
		void Release();
		void Update();
		//?
		void InputProc(UINT message, WPARAM wParam, LPARAM IParam); //Input Procedure 
		LPCSTR GetChar() { return str.c_str(); } //�Է��� Ű�� ���� ������ �˾ƿ´�.

		//Ű
		BOOL GetKeyDown(UINT keyID) { return KeyCheck(keyID, InputState::DOWN); } //Ȯ���Ϸ��� Key�� ���� �����ӿ��� �������°�?
		BOOL GetKeyPressed(UINT keyID) { return KeyCheck(keyID, InputState::PRESSED) || KeyCheck(keyID, InputState::DOWN); } //Ȯ���Ϸ��� Key�� ���� �����ӿ��� ������ �����ΰ�?
		BOOL GetKeyUp(UINT keyID) { return KeyCheck(keyID, InputState::UP); } //Ȯ���Ϸ��� Key�� ���� �����ӿ��� ���� ���� �ʾҴ°�?
		BOOL PressedAnyKey();

		//���콺
		BOOL GetMouseButtonDown(UINT keyID) { return ButtonCheck(keyID, InputState::DOWN); }
		BOOL GetMouseButtonPressed(UINT keyID) { return ButtonCheck(keyID, InputState::PRESSED) || ButtonCheck(keyID, InputState::DOWN); }
		BOOL GetMouseButtonUp(UINT keyID) { return ButtonCheck(keyID, InputState::UP); }
		POINT GetMousePosition() const { return mousePosition; }

	private:
		//���콺 Ŀ��
		//���콺 Ŀ�� �̵� ���� ����.
		void StartCapture(); 
		//���콺 Ŀ�� �̵� ���� ����.
		void EndCapture(); 

		//Ű
		void SetKeyDown(UINT keyID) { keys[keyID] = InputState::DOWN; } //���� �Էµ� Ű�� ���� ���·� ����.
		void SetKeyUp(UINT keyID) { keys[keyID] = InputState::UP; } //���� �Էµ� Ű�� ������ ���� ���·� ����.

		//���콺 ��ư
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