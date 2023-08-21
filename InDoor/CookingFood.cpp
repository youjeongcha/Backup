#include "CookingFood.h"
#include "GameManager.h"

CookingFood::CookingFood(ITEM_DETAIL itemDetail, ITEM_ID _itemID)
{
	itemID = _itemID;
	itemType = FOOD;


	switch (itemID)
	{
	case COOKING_ALLFRUIT:
		//name = "��� ����";
		//ImageBmp = "Fruit_Red.bmp";
		//detailInfo = "��� ������ �Ƴ��� �ʰ� �־� ���� Ư���� ����";
		itemUseTxt = USE_COOKING_ALLFRIUT;

		////��ġ ����
		//m_health = 10;
		//m_hunger = -40;
		//m_thirst = -20;
		//m_fatigue = 0;
		break;
	case COOKING_YELLOW:
		//name = "��� ����";
		//ImageBmp = "Fruit_Orange.bmp";
		//detailInfo = "��� ���� ���ϵ鸸 �ְ� ���� ����";
		itemUseTxt = USE_COOKING_YELLOW_OR_BERRIES;

		//��ġ ����
		//m_health = 0;
		//m_hunger = -20;
		//m_thirst = -10;
		//m_fatigue = 0;
		break;
	case COOKING_BERRIES:
		//name = "���� ����";
		//ImageBmp = "Fruit_Yellow.bmp";
		//detailInfo = "������ ���ϵ��� �ְ� ���� ����.";
		itemUseTxt = USE_COOKING_YELLOW_OR_BERRIES;

		//��ġ ����
		//m_health = 0;
		//m_hunger = -20;
		//m_thirst = -10;
		//m_fatigue = 0;
		break;
	}

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

CookingFood::~CookingFood()
{

}