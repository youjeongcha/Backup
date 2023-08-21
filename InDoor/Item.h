#pragma once
#include "EngineMecro.h"

enum ITEM_ID
{
	ITEM_START,

	//Drink
	WATER = ITEM_START,

	//Food

	//Light Object
	//����
	KEY,//����
	SEED_RED,//����
	SEED_ORANGE,//����
	SEED_YELLOW,//����
	SEED_BLUE,//����
	FRUIT_RED,//����
	FRUIT_ORANGE,//����
	FRUIT_YELLOW,//����
	FRUIT_BLUE,//����

	//�丮
	COOKING_ALLFRUIT,//��Ұ�������
	COOKING_YELLOW,//�����������
	COOKING_BERRIES,//����������

	//Heavy Object
	//����
	//�絿��
	//�д�

	ITEM_COUNT,
	ITEM_NONE,
};

enum TYPE
{
	NONE,
	OBJECT,
	FOOD,
	DRINK,
};

enum USECOUNT
{
	USE_NONE, //��� �Ұ�
	USE_ONE, //��ȸ��
	//USE_PERMANENT, //���� ��� //���� ���������� ���� ����� �Ұ����ϴ�.
};

struct ITEM_DETAIL
{
	std::string name; //������ �̸�
	std::string ImageBmp; //������ �̹���
	std::string detailInfo; //������ ������

	//���� ���� ��ġ
	int m_health, m_hunger, m_thirst, m_fatigue;

	//ITEM_ID itemID; //������ ����
	//TYPE itemType; //������ Ÿ��
	//USECOUNT useCount; //��� Ƚ��
};

class Item abstract
{
protected:
	//������ ����� �� �ؽ�Ʈ
	//UNDERTXT itemUseTxt;
	//ITEM_DETAIL item_Detail;
	int itemUseTxt; //UNDERTXT ������ GameManager.h�� ��� �޾� ����ϸ� ��� ��ħ���� int������ ���
	//int itemCount; //�������� ���� ����

	bool isUsing; //��� ���� üũ

	std::string name; //������ �̸�
	std::string ImageBmp; //������ �̹���
	std::string detailInfo; //������ ������

	//���� ���� ��ġ
	int m_health, m_hunger, m_thirst, m_fatigue;

	ITEM_ID itemID; //������ ����
	TYPE itemType; //������ Ÿ��
	USECOUNT useCount; //��� Ƚ��

public:
	Item();
	Item(ITEM_DETAIL itemDetail, ITEM_ID _itemID);
	~Item();

	//virtual void Use();
	void Use();

	std::string GetName() { return name; }
	std::string GetDetailInfo() { return detailInfo; }
	std::string GetImageBmp() { return ImageBmp; }
	bool GetisUsing() { return isUsing; }
	ITEM_ID GetItemID() { return itemID; }
};

