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
	USE_PERMANENT, //���� ���
};

class Item abstract
{
protected:
	//������ ����� �� �ؽ�Ʈ
	//UNDERTXT itemUseTxt;
	int itemUseTxt; //UNDERTXT ������ GameManager.h�� ��� �޾� ����ϸ� ��� ��ħ���� int������ ���
	//int itemCount; //�������� ���� ����
	ITEM_ID itemID; //������ ����
	TYPE itemType; //������ Ÿ��
	USECOUNT useCount; //��� Ƚ��
	bool isUsing; //��� ���� üũ
	
	std::string name; //������ �̸�
	std::string detailInfo; //������ ������
	std::string ImageBmp; //������ �̹���

	//���� ���� ��ġ
	int m_health, m_hunger, m_thirst, m_fatigue;
public:
	Item();
	~Item();

	//virtual void Use();
	void Use();

	std::string GetName() { return name; }
	std::string GetDetailInfo() { return detailInfo; }
	std::string GetImageBmp() { return ImageBmp; }
	bool GetisUsing() { return isUsing; }
	ITEM_ID GetItemID() { return itemID; }
};

