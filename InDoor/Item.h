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
	//아이템 타입
	TYPE itemType;
	//아이템 이름
	std::string name;
	//조정 스테이터스
	int m_health, m_hunger, m_thirst, m_fatigue;
public:
	Item();
	~Item();

	//virtual void Use();
	void Use();
	std::string GetName() { return name; }
};

