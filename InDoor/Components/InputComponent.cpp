#include "InputComponent.h"
#include "../InputManager.h"
#include <cassert>

namespace ENGINE
{
	//Ư�� Ű�� ���� �Է� ������ ����
	//EventListener �̺�Ʈ�� �߻����� �� ����Ǵ� �Լ��� ��Ÿ���� �Լ� ������ �Ǵ� �Լ� ��ü
	BOOL InputComponent::AddBinding(char key, EventListener action_start, EventListener action_cancle)
	{
		// action�� NULL�� �� ����.
		assert((NULL != action_start) && (NULL != action_cancle));

		if (mappings.find(key) != mappings.end()) 
			return FALSE;

		//Ư�� Ű�� �������� ����Ǵ� �Լ��� �̺�Ʈ �����ʷ� ����Ѵ�.
		//�ش� �Լ� �������� Ű �Է¿� ���� ó�� ������ ����
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
				//nowKeyState.currentKey = iter->first; //����% //������'
				//nowKeyState.currentState = '0';
				iter->second[1](); //State idle ����
			}
		}

		for (auto iter = mappings.begin(); iter != mappings.end(); iter++)
		{
			if (ENGINE::InputMgr->GetKeyPressed(iter->first)) //pressed�� ���� ���� + ������ ���� �� �����
			{
				/*nowKeyState.currentKey = iter->first;
				nowKeyState.currentState = '1';*/
				iter->second[0](); //State Move ����
			}
		}
	}
}