#include "Water.h"
#include "GameManager.h"

Water::Water(ITEM_DETAIL itemDetail, ITEM_ID _itemID)
{
	itemID = _itemID;
	itemType = DRINK;

	itemUseTxt = USE_WATER;
	//ENGINE::ResourceMgr->Load(ImageBmp);

	useCount = USE_ONE;
	isUsing = true;

	name = itemDetail.name;
	ImageBmp = itemDetail.ImageBmp;
	detailInfo = itemDetail.detailInfo;
	ENGINE::ResourceMgr->Load(ImageBmp);

	//음식류 아니면 다 0 으로 고정
	m_health = itemDetail.m_health;
	m_hunger = itemDetail.m_hunger;
	m_thirst = itemDetail.m_thirst;
	m_fatigue = itemDetail.m_fatigue;
}

Water::~Water()
{

}