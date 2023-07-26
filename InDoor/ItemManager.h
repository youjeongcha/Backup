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
	//성냥
	KEY,//열쇠
	//꽃

	//Heavy Object
	//장작
	//양동이
	//촛대

	ITEM_COUNT,
};

class ItemManager : public Singleton<ItemManager>
{
private:
	std::map<ITEM, Item*> itemList;

	ItemManager();
public:
	~ItemManager();

	//ITEM이란 enum을 통해서 해당 아이템에 접근하는 함수
	std::map<ITEM, Item*> GetItemList() { return itemList; }
	friend Singleton;
};
#define ItemMgr ItemManager::GetInstance()