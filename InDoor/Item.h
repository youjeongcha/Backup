#pragma once
#include "EngineMecro.h"

enum TYPE
{
	NONE,
	FOOD,
	DRINK,
};

class Item abstract
{
protected:
	//������ Ÿ��
	TYPE itemType;
	//������ �̸�
	std::string name;
	//���� �������ͽ�
	int m_health, m_hunger, m_thirst, m_fatigue;
public:
	Item();
	~Item();

	//virtual void Use();
	void Use();
	std::string GetName() { return name; }
};

