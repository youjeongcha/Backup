#include "Seed.h"
#include "GameManager.h"

Seed::Seed(ITEM_DETAIL itemDetail, ITEM_ID _itemID)
{
	itemID = _itemID;
	itemType = NONE;

	itemUseTxt = UNDERTXT_NONE;

	//switch (itemID)
	//{
	//case SEED_RED:
	//	name = "���� ����";
	//	ImageBmp = "Seed_Red.bmp";
	//	detailInfo = "���� ���� �����̴�.";
	//	break;
	//case SEED_ORANGE:
	//	name = "��Ȳ ����";
	//	ImageBmp = "Seed_Orange.bmp";
	//	detailInfo = "��Ȳ ���� �����̴�.";
	//	break;
	//case SEED_YELLOW:
	//	name = "��� ����";
	//	ImageBmp = "Seed_Yellow.bmp";
	//	detailInfo = "��� ���� �����̴�.";
	//	break;
	//case SEED_BLUE:
	//	name = "�Ķ� ����";
	//	ImageBmp = "Seed_Blue.bmp";
	//	detailInfo = "�Ķ� ���� �����̴�.";
	//	break;
	//}

	//ENGINE::ResourceMgr->Load(ImageBmp);

	useCount = USE_NONE;
	isUsing = false;

	name = itemDetail.name;
	ImageBmp = itemDetail.ImageBmp;
	detailInfo = itemDetail.detailInfo;
	ENGINE::ResourceMgr->Load(ImageBmp);

	//���ķ� �ƴϸ� �� 0 ���� ����
	m_health = itemDetail.m_health;
	m_hunger = itemDetail.m_hunger;
	m_thirst = itemDetail.m_thirst;
	m_fatigue = itemDetail.m_fatigue;

	//���ķ� �ƴϸ� �� 0 ���� ����
	//m_health = 0;
	//m_hunger = 0;
	//m_thirst = 0;
	//m_fatigue = 0;
}

Seed::~Seed()
{
}