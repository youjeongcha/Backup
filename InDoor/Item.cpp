#include "Item.h"
#include "GameManager.h"

Item::Item()
{
	//itemID = ITEM_NONE;
	//itemType = OBJECT;

	//name = "�ӽ�";
	//itemUseTxt = UNDERTXT_NONE;
	//useCount = USE_NONE;
	//isUsing = false;

	////itemCount = 0;

	////���ķ� �ƴϸ� �� 0 ���� ����
	//m_health = 0;
	//m_hunger = 0;
	//m_thirst = 0;
	//m_fatigue = 0;
}

Item::Item(ITEM_DETAIL itemDetail, ITEM_ID _itemID)
{
	//name = itemDetail.name;
	//ImageBmp = itemDetail.ImageBmp;
	//detailInfo = itemDetail.detailInfo;
	//ENGINE::ResourceMgr->Load(ImageBmp);

	////���ķ� �ƴϸ� �� 0 ���� ����
	//m_health = itemDetail.m_health;
	//m_hunger = itemDetail.m_hunger;
	//m_thirst = itemDetail.m_thirst;
	//m_fatigue = itemDetail.m_fatigue;
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
