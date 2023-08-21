#pragma once
#include "Singleton.h"
#include "Item.h"
#include "Water.h"
#include "Key.h"
#include "Seed.h"
#include "Fruit.h"
#include "CookingFood.h"



struct InventoryItem
{
	ITEM_ID itemID;
	int itemCount;
};

class ItemManager : public Singleton<ItemManager>
{
private:
	//std::map<ITEM_ID, Item*> itemList;
	std::vector<ITEM_DETAIL> itemData; //���Ͽ��� �о�� ������ ����
	std::vector<Item*> itemList;

	ItemManager();
	void LoadItem();
public:
	~ItemManager();

	//ITEM�̶� enum�� ���ؼ� �ش� �����ۿ� �����ϴ� �Լ�
	//std::map<ITEM_ID, Item*> GetItemList() { return itemList; }
	std::vector<Item*> GetItemList() { return itemList; }
	friend Singleton;
};
#define ItemMgr ItemManager::GetInstance()