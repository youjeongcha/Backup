#include "ItemManager.h"

ItemManager::ItemManager()
{
	//1,아이템의 데이터가 필요 (Food && Drink)
	//itemList.insert({ WATER, new Water() });
	itemList.push_back(new Water());

	//2.존재하기만 해도 되는 아이템 (ex.Key, match  다른 아이템이나 가구와 상호작용)
	//itemList.insert({ KEY, new Key() });
	itemList.push_back(new Key());

	//씨앗
	itemList.push_back(new Seed(SEED_RED));
	itemList.push_back(new Seed(SEED_ORANGE));
	itemList.push_back(new Seed(SEED_YELLOW));
	itemList.push_back(new Seed(SEED_BLUE));
	//열매
	itemList.push_back(new Fruit(FRUIT_RED));
	itemList.push_back(new Fruit(FRUIT_ORANGE));
	itemList.push_back(new Fruit(FRUIT_YELLOW));
	itemList.push_back(new Fruit(FRUIT_BLUE));

}

ItemManager::~ItemManager()
{
}