#include "Fruit.h"

#include "GameManager.h"

Fruit::Fruit(ITEM_DETAIL itemDetail, ITEM_ID _itemID)
{
	itemID = _itemID;
	itemType = FOOD;

	itemUseTxt = USE_FRUIT;

	/*switch (itemID)
	{
	case FRUIT_RED:
		name = "빨강 열매";
		ImageBmp = "Fruit_Red.bmp";
		detailInfo = "단 열매다.";
		break;
	case FRUIT_ORANGE:
		name = "주황 열매";
		ImageBmp = "Fruit_Orange.bmp";
		detailInfo = "시그러운 열매다.";
		break;
	case FRUIT_YELLOW:
		name = "노랑 열매";
		ImageBmp = "Fruit_Yellow.bmp";
		detailInfo = "새큼한 맛의 열매다.";
		break;
	case FRUIT_BLUE:
		name = "파랑 열매";
		ImageBmp = "Fruit_Blue.bmp";
		detailInfo = "상큼한 맛의 열매다.";
		break;
	}*/

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

Fruit::~Fruit()
{
}