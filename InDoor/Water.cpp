#include "Water.h"
#include "GameManager.h"

Water::Water()
{
	itemID = WATER;
	itemType = DRINK;

	itemUseTxt = USE_WATER;
	name = "물";
	ImageBmp = "WaterCup.bmp";
	detailInfo = "시원한 물. 갈증 30이 해소된다.";
	ENGINE::ResourceMgr->Load(ImageBmp);

	useCount = USE_ONE;
	isUsing = true;

	m_health = 0;
	m_hunger = 0;
	m_thirst = -30;
	m_fatigue = 0;
}

Water::~Water()
{

}