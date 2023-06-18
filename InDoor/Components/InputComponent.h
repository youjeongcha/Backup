#include "../Component.h"

#ifndef LR_INPUT_H
#define LR_INPUT_H

namespace ENGINE
{
	//게임 오브젝트와 입력 동작을 연결하여 입력에 따라 동작을 수행할 수 있도록 한다. 
	class InputComponent : public Component
	{
	protected:
		std::map<char, EventListener[2]> mappings; //TODO::

	public:
		virtual ~InputComponent() { }

		//특정 키에 대한 입력 동작을 설정
		BOOL AddBinding(char key, EventListener action_start, EventListener action_cancle);

		// Component을(를) 통해 상속됨
		virtual VOID Operate(GameObject* Owner) override;
		virtual VOID Reset() override { mappings.clear(); }
		virtual ComponentType GetType() const override { return ComponentType::Input; }
	};
}

#endif // !LR_INPUT_H