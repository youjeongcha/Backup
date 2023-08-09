#include "Key.h"
#include "GameManager.h"

Key::Key()
{
	itemID = KEY;
	itemType = NONE;

	itemUseTxt = UNDERTXT_NONE;
	name = "열쇠";
	ImageBmp = "Key.bmp";
	detailInfo = "은색 열쇠. 어디에 맞는 열쇠일까.";
	ENGINE::ResourceMgr->Load(ImageBmp);

	useCount = USE_NONE;
	isUsing = false;

	//음식류 아니면 다 0 으로 고정
	m_health = 0;
	m_hunger = 0;
	m_thirst = 0;
	m_fatigue = 0;
}

Key::~Key()
{
}
