#pragma once
#include "Item.h"

class Key : public Item
{
protected:
public:
	Key()
	{
		itemType = NONE;
		name = "열쇠";

		//음식류 아니면 다 0 으로 고정
		m_health = 0;
		m_hunger = 0;
		m_thirst = 0;
		m_fatigue = 0;
	}
	~Key()
	{

	}
};

