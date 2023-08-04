#include "Component.h"
#include "EngineMecro.h"

namespace ENGINE
{
	VOID Transform::Reset()
	{
		position.x = position.y = 0.0f;
		scale.x = scale.y = 1.0f;
	}

	GameObject::GameObject()
	{
		transform = new Transform;
		AddComponent(transform);
	}
	GameObject::~GameObject()
	{
		for (std::pair<ComponentType, Component*> c : components) 
			DEL(c.second);
	}
	Component* GameObject::GetComponent(CONST ComponentType& type)
	{
		//조건자는 람다 함수, 찾고자 하는 조건을 검사하여 true 또는 false를 반환
		auto iter = std::find_if(components.begin(), components.end(),
			[&](const std::pair<ComponentType, Component*>& pair) {
				return pair.first == type;
			});

		return (iter != components.end()) ? iter->second : nullptr;

		//auto iter = std::find_if(components.begin(), components.end(),
		//	[&](const std::pair<ComponentType, Component*>& pair) {
		//		return pair.second;
		//	});

		//return nullptr;

		//auto iter = components.find(type);
		//if (components.end() != iter) 
		//	return iter->second;

		//return nullptr;
	}
	BOOL GameObject::AddComponent(Component* component)
	{
		//if (!component || GetComponent(component->GetType()))
		//	return FALSE;

		//components.push_back(std::make_pair(component->GetType(), component));
		//return TRUE;

		if (!component || GetComponent(component->GetType())) 
			return FALSE;

		components.insert(std::make_pair(component->GetType(), component));
		return TRUE;
	}
	VOID GameObject::Operate(GameObject* Owner)
	{
		for (std::pair<ComponentType, Component*> c : components) 
			c.second->Operate(this); //해당 부분 확인
	}
	VOID GameObject::Reset()
	{
		for (std::pair<ComponentType, Component*> c : components) 
			c.second->Reset();
	}

	VOID AnimationComponent::SetSpeed(FLOAT speed)
	{
		isReverse = (0 > speed);
		this->speed = std::abs(speed);
	}
}