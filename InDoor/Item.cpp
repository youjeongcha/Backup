#include "Item.h"
#include "GameManager.h"

Item::Item()
{
	itemID = ITEM_NONE;
	itemType = OBJECT;

	name = "임시";
	itemUseTxt = UNDERTXT_NONE;
	useCount = USE_NONE;
	isUsing = false;

	//itemCount = 0;

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
	if (itemType != OBJECT)
	{
		GameMgr->PlusHealth(m_health);
		GameMgr->PlusThirst(m_thirst);
		GameMgr->PlusFatigue(m_fatigue);
		GameMgr->PlusHunger(m_hunger);
	}

	//일회용 아이템 사용하고 나면 사용했다고 설정.
	if (useCount == USE_ONE)
	{
		isUsing = false;

		if (!GameMgr->MinusPlayerItem(itemID)) //다회용 아이템은 아이템 수량 감소 처리되지 않도록 해야한다.
			GameMgr->SetShowUnder(DONTHAVE_ITEM); //보험
	}

	GameMgr->SetShowUnder((UNDERTXT)itemUseTxt);
}
