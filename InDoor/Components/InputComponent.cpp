#include "InputComponent.h"
#include "../InputManager.h"
#include <cassert>

namespace ENGINE
{
	//특정 키에 대한 입력 동작을 설정
	//EventListener 이벤트가 발생했을 때 실행되는 함수를 나타내는 함수 포인터 또는 함수 객체
	BOOL InputComponent::AddBinding(char key, EventListener action_start, EventListener action_cancle)
	{
		// action은 NULL일 수 없다.
		assert((NULL != action_start) && (NULL != action_cancle));

		if (mappings.find(key) != mappings.end()) 
			return FALSE;

		//특정 키를 눌렀을때 실행되는 함수를 이벤트 리스너로 등록한다.
		//해당 함수 내에서는 키 입력에 대한 처리 로직을 구현
		mappings[key][0] = action_start;
		mappings[key][1] = action_cancle;
		return TRUE;
	}

	VOID InputComponent::Operate(GameObject* Owner)
	{
		for (auto iter = mappings.begin(); iter != mappings.end(); iter++)
		{
			if (ENGINE::InputMgr->GetKeyUp(iter->first))
			{
				//nowKeyState.currentKey = iter->first; //왼쪽% //오른쪽'
				//nowKeyState.currentState = '0';
				iter->second[1](); //State idle 상태
			}
		}

		for (auto iter = mappings.begin(); iter != mappings.end(); iter++)
		{
			if (ENGINE::InputMgr->GetKeyPressed(iter->first)) //pressed가 누른 순간 + 눌러진 상태 다 고려함
			{
				/*nowKeyState.currentKey = iter->first;
				nowKeyState.currentState = '1';*/
				iter->second[0](); //State Move 상태
			}
		}
	}
}