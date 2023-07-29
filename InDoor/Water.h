#pragma once
#include "Item.h"

class Water : public Item
{
private:
public:
	Water()
	{
		itemType = DRINK;
		name = "¹°";

		m_health = 0;
		m_hunger = 0;
		m_thirst = 30;
		m_fatigue = 0;
	}

	~Water()
	{
	}
	//virtual void Use() override;
};

