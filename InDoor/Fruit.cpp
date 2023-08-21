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
		name = "���� ����";
		ImageBmp = "Fruit_Red.bmp";
		detailInfo = "�� ���Ŵ�.";
		break;
	case FRUIT_ORANGE:
		name = "��Ȳ ����";
		ImageBmp = "Fruit_Orange.bmp";
		detailInfo = "�ñ׷��� ���Ŵ�.";
		break;
	case FRUIT_YELLOW:
		name = "��� ����";
		ImageBmp = "Fruit_Yellow.bmp";
		detailInfo = "��ŭ�� ���� ���Ŵ�.";
		break;
	case FRUIT_BLUE:
		name = "�Ķ� ����";
		ImageBmp = "Fruit_Blue.bmp";
		detailInfo = "��ŭ�� ���� ���Ŵ�.";
		break;
	}*/

	//ENGINE::ResourceMgr->Load(ImageBmp);

	useCount = USE_ONE;
	isUsing = true;

	name = itemDetail.name;
	ImageBmp = itemDetail.ImageBmp;
	detailInfo = itemDetail.detailInfo;
	ENGINE::ResourceMgr->Load(ImageBmp);

	//���ķ� �ƴϸ� �� 0 ���� ����
	m_health = itemDetail.m_health;
	m_hunger = itemDetail.m_hunger;
	m_thirst = itemDetail.m_thirst;
	m_fatigue = itemDetail.m_fatigue;
}

Fruit::~Fruit()
{
}