#pragma once
#include "Singleton.h"
#include "Item.h"
#include "Water.h"
#include "Key.h"
#include "Seed.h"
#include "Fruit.h"



struct InventoryItem
{
	ITEM_ID itemID;
	int itemCount;
};

class ItemManager : public Singleton<ItemManager>
{
private:
	//std::map<ITEM_ID, Item*> itemList;
	std::vector<Item*> itemList;

	ItemManager();
public:
	~ItemManager();

	//ITEM이란 enum을 통해서 해당 아이템에 접근하는 함수
	//std::map<ITEM_ID, Item*> GetItemList() { return itemList; }
	std::vector<Item*> GetItemList() { return itemList; }
	friend Singleton;
};
#define ItemMgr ItemManager::GetInstance()