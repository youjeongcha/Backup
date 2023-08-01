#pragma once
#include "Singleton.h"
#include "Item.h"
#include "Water.h"
#include "Key.h"



struct InventoryItem
{
	ITEM_ID itemID;
	int itemCount;
};

class ItemManager : public Singleton<ItemManager>
{
private:
	std::map<ITEM_ID, Item*> itemList;

	ItemManager();
public:
	~ItemManager();

	//ITEM�̶� enum�� ���ؼ� �ش� �����ۿ� �����ϴ� �Լ�
	std::map<ITEM_ID, Item*> GetItemList() { return itemList; }
	friend Singleton;
};
#define ItemMgr ItemManager::GetInstance()