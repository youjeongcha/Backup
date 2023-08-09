#include "Item.h"
#include "GameManager.h"

Item::Item()
{
	itemID = ITEM_NONE;
	itemType = OBJECT;

	name = "�ӽ�";
	itemUseTxt = UNDERTXT_NONE;
	useCount = USE_NONE;
	isUsing = false;

	//itemCount = 0;

	//���ķ� �ƴϸ� �� 0 ���� ����
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

	//��ȸ�� ������ ����ϰ� ���� ����ߴٰ� ����.
	if (useCount == USE_ONE)
	{
		isUsing = false;

		if (!GameMgr->MinusPlayerItem(itemID)) //��ȸ�� �������� ������ ���� ���� ó������ �ʵ��� �ؾ��Ѵ�.
			GameMgr->SetShowUnder(DONTHAVE_ITEM); //����
	}

	GameMgr->SetShowUnder((UNDERTXT)itemUseTxt);
}
