#include "Key.h"
#include "GameManager.h"

Key::Key()
{
	//itemID = KEY;
	//itemType = NONE;

	//itemUseTxt = UNDERTXT_NONE;
	//name = "����";
	//ImageBmp = "Key.bmp";
	//detailInfo = "���� ���� ����. ��� �´� �����ϱ�.";
	//ENGINE::ResourceMgr->Load(ImageBmp);

	//useCount = USE_ONE;
	//isUsing = false;

	////���ķ� �ƴϸ� �� 0 ���� ����
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

	useCount = USE_NONE; //���� ��� �Ұ� ������
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
}

Key::~Key()
{
}
