#include "Key.h"
#include "GameManager.h"

Key::Key()
{
	//itemID = KEY;
	//itemType = NONE;

	//itemUseTxt = UNDERTXT_NONE;
	//name = "열쇠";
	//ImageBmp = "Key.bmp";
	//detailInfo = "낡은 은색 열쇠. 어디에 맞는 열쇠일까.";
	//ENGINE::ResourceMgr->Load(ImageBmp);

	//useCount = USE_ONE;
	//isUsing = false;

	////음식류 아니면 다 0 으로 고정
	//m_health = 0;
	//m_hunger = 0;
	//m_thirst = 0;
	//m_fatigue = 0;
}

Key::Key(ITEM_DETAIL itemDetail, ITEM_ID _itemID)
{
	itemID = _itemID;
	itemType = NONE;

	itemUseTxt = UNDERTXT_NONE;

	useCount = USE_NONE; //직접 사용 불가 아이템
	isUsing = false;

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

Key::~Key()
{
}
