#include "ItemManager.h"

ItemManager::ItemManager()
{
	//1,�������� �����Ͱ� �ʿ� (Food && Drink)
	itemList.insert({ WATER, new Water() });

	//2.�����ϱ⸸ �ص� �Ǵ� ������ (ex.Key, match  �ٸ� �������̳� ������ ��ȣ�ۿ�)
	itemList.insert({ KEY, new Key() });

}

ItemManager::~ItemManager()
{
}