#include <iostream>
#include <vector>
#include <algorithm>

// Component
__interface Component //__interface 공용 순수 가상함수만 선언된 클래스. 일반적으로 추상 클래스가 상속을 받아 사용한다.
{//인터페이스는 무조건 접근제한 퍼블릭
	void Operation(); //질문:: 얘가 순수 가상함수? virtual을 붙이지 않아도 되는가?
	//널이나 0하고 버츄얼 표시는. 클래스의 함수일때만
};

// Composite
class GameObject : public Component
{
private:
	std::vector<Component*> components;

public:
	void Operation() override
	{
		for (Component* component : components)
		{
			component->Operation(); //한번에 다 실행시킨다.
		}
	}
	void AddComponent(Component* component) { if (NULL != component) components.push_back(component); }
	void RemoveComponent(Component* component)
	{
		if (NULL == component) return;
		auto iter = std::find(components.begin(), components.end(), component); //찾는 객체가 없다면 end()를 리턴한다.
		if (components.end() != iter) components.erase(iter);
	}
};

// Leaf
class PlayerInput : public Component
{
public: //부모의 함수와 이름이 같다면 override를 해야 부모가 호출되지 않는다.
	void Operation() override { std::cout << "User Input" << std::endl; }
};
class EnemyInput : public Component
{
public:
	void Operation() override { std::cout << "AI Processing" << std::endl; }
};
class Physics : public Component
{
public:
	void Operation() override { std::cout << "Physics Processing" << std::endl; }
};
class Graphics : public Component
{
public:
	void Operation() override { std::cout << "Graphics Processing" << std::endl; }
};


void main()
{
	PlayerInput playerInput;
	EnemyInput enemyInput;
	Physics physics;
	Graphics graphics;

	std::cout << "=== Set Player Components ===" << std::endl;
	GameObject player;
	player.AddComponent(&playerInput);
	player.AddComponent(&physics);
	player.AddComponent(&graphics);
	player.Operation();

	std::cout << std::endl << "=== Set Enemy Components ===" << std::endl;
	GameObject enemy;
	enemy.AddComponent(&enemyInput);
	enemy.AddComponent(&physics);
	enemy.AddComponent(&graphics);
	enemy.RemoveComponent(&physics);
	enemy.Operation();
}
