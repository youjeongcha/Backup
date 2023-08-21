#include "CookingFood.h"
#include "GameManager.h"

CookingFood::CookingFood(ITEM_DETAIL itemDetail, ITEM_ID _itemID)
{
	itemID = _itemID;
	itemType = FOOD;


	switch (itemID)
	{
	case COOKING_ALLFRUIT:
		//name = "모둠 조림";
		//ImageBmp = "Fruit_Red.bmp";
		//detailInfo = "모든 과일을 아끼지 않고 넣어 졸인 특별한 조림";
		itemUseTxt = USE_COOKING_ALLFRIUT;

		////수치 조절
		//m_health = 10;
		//m_hunger = -40;
		//m_thirst = -20;
		//m_fatigue = 0;
		break;
	case COOKING_YELLOW:
		//name = "노랑 조림";
		//ImageBmp = "Fruit_Orange.bmp";
		//detailInfo = "노랑 빛깔 과일들만 넣고 졸인 조림";
		itemUseTxt = USE_COOKING_YELLOW_OR_BERRIES;

		//수치 조절
		//m_health = 0;
		//m_hunger = -20;
		//m_thirst = -10;
		//m_fatigue = 0;
		break;
	case COOKING_BERRIES:
		//name = "베리 조림";
		//ImageBmp = "Fruit_Yellow.bmp";
		//detailInfo = "베리류 과일들을 넣고 졸인 조림.";
		itemUseTxt = USE_COOKING_YELLOW_OR_BERRIES;

		//수치 조절
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

	//음식류 아니면 다 0 으로 고정
	m_health = itemDetail.m_health;
	m_hunger = itemDetail.m_hunger;
	m_thirst = itemDetail.m_thirst;
	m_fatigue = itemDetail.m_fatigue;
}

CookingFood::~CookingFood()
{

}