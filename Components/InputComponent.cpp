#include "InputComponent.h"
#include "../InputManager.h"
#include <cassert>

namespace ENGINE
{
	BOOL InputComponent::AddBinding(char key, EventListener action_start, EventListener action_cancle)
	{
		// action은 NULL일 수 없다.
		assert((NULL != action_start) && (NULL != action_cancle));

		if (mappings.find(key) != mappings.end()) return FALSE;
		mappings[key][0] = action_start;
		mappings[key][1] = action_cancle;
		return TRUE;
	}

	VOID InputComponent::Operate(GameObject* Owner)
	{
		for (auto iter = mappings.begin(); iter != mappings.end(); iter++)
		{
			if (ENGINE::InputMgr->GetKeyUp(iter->first)) iter->second[1]();
		}

		for (auto iter = mappings.begin(); iter != mappings.end(); iter++)
		{
			if (ENGINE::InputMgr->GetKeyDown(iter->first)) iter->second[0]();
		}
	}
}