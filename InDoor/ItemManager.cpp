#include "ItemManager.h"
#include "GameManager.h"

ItemManager::ItemManager()
{
	int i = 0;
	//1,�������� �����Ͱ� �ʿ� (Food && Drink)
	//itemList.insert({ WATER, new Water() });
	LoadItem();

	itemList.push_back(new Water(itemData[i++], WATER));

	//2.�����ϱ⸸ �ص� �Ǵ� ������ (ex.Key, match  �ٸ� �������̳� ������ ��ȣ�ۿ�)
	//itemList.insert({ KEY, new Key() });
	itemList.push_back(new Key(itemData[i++], KEY));

	//����
	itemList.push_back(new Seed(itemData[i++], SEED_RED));
	itemList.push_back(new Seed(itemData[i++], SEED_ORANGE));
	itemList.push_back(new Seed(itemData[i++], SEED_YELLOW));
	itemList.push_back(new Seed(itemData[i++], SEED_BLUE));
	//����
	itemList.push_back(new Fruit(itemData[i++], FRUIT_RED));
	itemList.push_back(new Fruit(itemData[i++], FRUIT_ORANGE));
	itemList.push_back(new Fruit(itemData[i++], FRUIT_YELLOW));
	itemList.push_back(new Fruit(itemData[i++], FRUIT_BLUE));


	//�丮
	itemList.push_back(new CookingFood(itemData[i++], COOKING_ALLFRUIT));
	itemList.push_back(new CookingFood(itemData[i++], COOKING_YELLOW));
	itemList.push_back(new CookingFood(itemData[i++], COOKING_BERRIES));

}

void ItemManager::LoadItem()
{
	std::ifstream load("Data/Item.txt");


	// ������ ���������� ���ȴ��� Ȯ��
	if (load.is_open()) {

		 for (int i = 0; i < ITEM_COUNT; i++) 
		 {
			ITEM_DETAIL tmp_ItemDetail;
			std::string tmp;
			
			if (i != 0)
				load.ignore();
			//load.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ���� ���� ����
			std::getline(load, tmp_ItemDetail.name); // ���� ���� ó��
			std::getline(load, tmp_ItemDetail.ImageBmp);
			std::getline(load, tmp_ItemDetail.detailInfo);

			load >> tmp_ItemDetail.m_health;
			load >> tmp_ItemDetail.m_hunger;
			load >> tmp_ItemDetail.m_thirst;
			load >> tmp_ItemDetail.m_fatigue;

			itemData.push_back(tmp_ItemDetail);
		 }

		// ���� ��Ʈ�� �ݱ�
		load.close();
	}
}

ItemManager::~ItemManager()
{
}