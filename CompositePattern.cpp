#include <iostream>
#include <vector>
#include <algorithm>

// Component
__interface Component //__interface ���� ���� �����Լ��� ����� Ŭ����. �Ϲ������� �߻� Ŭ������ ����� �޾� ����Ѵ�.
{//�������̽��� ������ �������� �ۺ�
	void Operation(); //����:: �갡 ���� �����Լ�? virtual�� ������ �ʾƵ� �Ǵ°�?
	//���̳� 0�ϰ� ����� ǥ�ô�. Ŭ������ �Լ��϶���
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
			component->Operation(); //�ѹ��� �� �����Ų��.
		}
	}
	void AddComponent(Component* component) { if (NULL != component) components.push_back(component); }
	void RemoveComponent(Component* component)
	{
		if (NULL == component) return;
		auto iter = std::find(components.begin(), components.end(), component); //ã�� ��ü�� ���ٸ� end()�� �����Ѵ�.
		if (components.end() != iter) components.erase(iter);
	}
};

// Leaf
class PlayerInput : public Component
{
public: //�θ��� �Լ��� �̸��� ���ٸ� override�� �ؾ� �θ� ȣ����� �ʴ´�.
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
