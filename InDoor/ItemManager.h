#pragma once
#include "Singleton.h"
#include "Item.h"
#include "Water.h"
#include "Key.h"

enum ITEM
{
	ITEM_START,

	//Drink
	WATER = ITEM_START,

	//Food

	//Light Object
	//����
	KEY,//����
	//��

	//Heavy Object
	//����
	//�絿��
	//�д�

	ITEM_COUNT,
};

class ItemManager : public Singleton<ItemManager>
{
private:
	std::map<ITEM, Item*> itemList;

	ItemManager();
public:
	~ItemManager();

	//ITEM�̶� enum�� ���ؼ� �ش� �����ۿ� �����ϴ� �Լ�
	std::map<ITEM, Item*> GetItemList() { return itemList; }
	friend Singleton;
};
#define ItemMgr ItemManager::GetInstance()