#include "Item.h"
#include "GameManager.h"

Item::Item()
{
	itemType = NONE;
	name = "임시";

	//음식류 아니면 다 0 으로 고정
	m_health = 0;
	m_hunger = 0;
	m_thirst = 0;
	m_fatigue = 0;
}

Item::~Item()
{
}

void Item::Use()
{
	if (itemType != NONE)
	{
		GameMgr->PlusHealth(m_health);
		GameMgr->PlusThirst(m_thirst);
		GameMgr->PlusFatigue(m_fatigue);
		GameMgr->PlusHunger(m_hunger);
	}
}
