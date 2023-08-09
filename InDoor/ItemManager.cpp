#include "ItemManager.h"

ItemManager::ItemManager()
{
	//1,�������� �����Ͱ� �ʿ� (Food && Drink)
	//itemList.insert({ WATER, new Water() });
	itemList.push_back(new Water());

	//2.�����ϱ⸸ �ص� �Ǵ� ������ (ex.Key, match  �ٸ� �������̳� ������ ��ȣ�ۿ�)
	//itemList.insert({ KEY, new Key() });
	itemList.push_back(new Key());

	//����
	itemList.push_back(new Seed(SEED_RED));
	itemList.push_back(new Seed(SEED_ORANGE));
	itemList.push_back(new Seed(SEED_YELLOW));
	itemList.push_back(new Seed(SEED_BLUE));
	//����
	itemList.push_back(new Fruit(FRUIT_RED));
	itemList.push_back(new Fruit(FRUIT_ORANGE));
	itemList.push_back(new Fruit(FRUIT_YELLOW));
	itemList.push_back(new Fruit(FRUIT_BLUE));

}

ItemManager::~ItemManager()
{
}