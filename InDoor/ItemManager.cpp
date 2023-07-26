#include "ItemManager.h"

ItemManager::ItemManager()
{
	//1,아이템의 데이터가 필요 (Food && Drink)
	itemList.insert({ WATER, new Water() });

	//2.존재하기만 해도 되는 아이템 (ex.Key, match  다른 아이템이나 가구와 상호작용)
	itemList.insert({ KEY, new Key() });

}

ItemManager::~ItemManager()
{
}