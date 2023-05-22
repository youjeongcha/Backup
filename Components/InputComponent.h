#include "../Component.h"

#ifndef LR_INPUT_H
#define LR_INPUT_H

namespace ENGINE
{
	class InputComponent : public Component
	{
	protected:
		std::map<char, EventListener[2]> mappings;

	public:
		virtual ~InputComponent() { }

		BOOL AddBinding(char key, EventListener action_start, EventListener action_cancle);

		// Component을(를) 통해 상속됨
		virtual VOID Operate(GameObject* Owner) override;
		virtual VOID Reset() override { mappings.clear(); }
		virtual ComponentType GetType() const override { return ComponentType::Input; }
	};
}

#endif // !LR_INPUT_H