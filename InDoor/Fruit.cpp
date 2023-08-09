#include "Fruit.h"

#include "GameManager.h"

Fruit::Fruit(ITEM_ID _itemID)
{
	itemID = _itemID;
	itemType = FOOD;

	itemUseTxt = USE_FRUIT;

	switch (itemID)
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
	}

	ENGINE::ResourceMgr->Load(ImageBmp);

	useCount = USE_ONE;
	isUsing = true;

	//���ķ� �ƴϸ� �� 0 ���� ����
	m_health = 0;
	m_hunger = -10;
	m_thirst = -10;
	m_fatigue = 0;
}

Fruit::~Fruit()
{
}