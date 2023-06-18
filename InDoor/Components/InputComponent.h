#include "../Component.h"

#ifndef LR_INPUT_H
#define LR_INPUT_H

namespace ENGINE
{
	//���� ������Ʈ�� �Է� ������ �����Ͽ� �Է¿� ���� ������ ������ �� �ֵ��� �Ѵ�. 
	class InputComponent : public Component
	{
	protected:
		std::map<char, EventListener[2]> mappings; //TODO::

	public:
		virtual ~InputComponent() { }

		//Ư�� Ű�� ���� �Է� ������ ����
		BOOL AddBinding(char key, EventListener action_start, EventListener action_cancle);

		// Component��(��) ���� ��ӵ�
		virtual VOID Operate(GameObject* Owner) override;
		virtual VOID Reset() override { mappings.clear(); }
		virtual ComponentType GetType() const override { return ComponentType::Input; }
	};
}

#endif // !LR_INPUT_H