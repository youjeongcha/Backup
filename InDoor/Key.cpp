#include "Key.h"
#include "GameManager.h"

Key::Key()
{
	itemID = KEY;
	itemType = NONE;

	itemUseTxt = UNDERTXT_NONE;
	name = "����";
	ImageBmp = "Key.bmp";
	detailInfo = "���� ����. ��� �´� �����ϱ�.";
	ENGINE::ResourceMgr->Load(ImageBmp);

	useCount = USE_NONE;
	isUsing = false;

	//���ķ� �ƴϸ� �� 0 ���� ����
	m_health = 0;
	m_hunger = 0;
	m_thirst = 0;
	m_fatigue = 0;
}

Key::~Key()
{
}
