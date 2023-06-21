#include "../Component.h"

#ifndef LR_INPUT_H
#define LR_INPUT_H

namespace ENGINE
{
	//게임 오브젝트와 입력 동작을 연결하여 입력에 따라 동작을 수행할 수 있도록 한다. 
	class InputComponent : public Component
	{
	protected: //TODO::키 추가는 해당 변수 수정
		//첫번째 인자:키. 두번째 인자:작동 중일때,작동 끝났을때의 상태
		std::map<char, EventListener[2]> mappings; 

	public:
		virtual ~InputComponent() { }

		//특정 키에 대한 입력 동작을 설정
		BOOL AddBinding(char key, EventListener action_start, EventListener action_cancle);

		// Component을(를) 통해 상속됨
		virtual VOID Operate(GameObject* Owner) override;
		virtual VOID Reset() override { mappings.clear(); }
		virtual ComponentType GetType() const override { return ComponentType::Input; }

		//NowKeyState GetKeyCheck() { return nowKeyState; } //왼쪽% //오른쪽'
	};
}

#endif // !LR_INPUT_H