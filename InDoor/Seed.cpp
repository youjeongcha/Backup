#include "Seed.h"
#include "GameManager.h"

Seed::Seed(ITEM_ID _itemID)
{
	itemID = _itemID;
	itemType = NONE;

	itemUseTxt = UNDERTXT_NONE;

	switch (itemID)
	{
	case SEED_RED:
		name = "»¡°­ ¾¾¾Ñ";
		ImageBmp = "Seed_Red.bmp";
		detailInfo = "»¡°­ ²ÉÀÇ ¾¾¾ÑÀÌ´Ù.";
		break;
	case SEED_ORANGE:
		name = "ÁÖÈ² ¾¾¾Ñ";
		ImageBmp = "Seed_Orange.bmp";
		detailInfo = "ÁÖÈ² ²ÉÀÇ ¾¾¾ÑÀÌ´Ù.";
		break;
	case SEED_YELLOW:
		name = "³ë¶û ¾¾¾Ñ";
		ImageBmp = "Seed_Yellow.bmp";
		detailInfo = "³ë¶û ²ÉÀÇ ¾¾¾ÑÀÌ´Ù.";
		break;
	case SEED_BLUE:
		name = "ÆÄ¶û ¾¾¾Ñ";
		ImageBmp = "Seed_Blue.bmp";
		detailInfo = "ÆÄ¶û ²ÉÀÇ ¾¾¾ÑÀÌ´Ù.";
		break;
	}

	ENGINE::ResourceMgr->Load(ImageBmp);

	useCount = USE_NONE;
	isUsing = false;

	//À½½Ä·ù ¾Æ´Ï¸é ´Ù 0 À¸·Î °íÁ¤
	m_health = 0;
	m_hunger = 0;
	m_thirst = 0;
	m_fatigue = 0;
}

Seed::~Seed()
{
}