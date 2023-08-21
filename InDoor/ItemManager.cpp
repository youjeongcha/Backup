#include "ItemManager.h"
#include "GameManager.h"

ItemManager::ItemManager()
{
	int i = 0;
	//1,아이템의 데이터가 필요 (Food && Drink)
	//itemList.insert({ WATER, new Water() });
	LoadItem();

	itemList.push_back(new Water(itemData[i++], WATER));

	//2.존재하기만 해도 되는 아이템 (ex.Key, match  다른 아이템이나 가구와 상호작용)
	//itemList.insert({ KEY, new Key() });
	itemList.push_back(new Key(itemData[i++], KEY));

	//씨앗
	itemList.push_back(new Seed(itemData[i++], SEED_RED));
	itemList.push_back(new Seed(itemData[i++], SEED_ORANGE));
	itemList.push_back(new Seed(itemData[i++], SEED_YELLOW));
	itemList.push_back(new Seed(itemData[i++], SEED_BLUE));
	//열매
	itemList.push_back(new Fruit(itemData[i++], FRUIT_RED));
	itemList.push_back(new Fruit(itemData[i++], FRUIT_ORANGE));
	itemList.push_back(new Fruit(itemData[i++], FRUIT_YELLOW));
	itemList.push_back(new Fruit(itemData[i++], FRUIT_BLUE));


	//요리
	itemList.push_back(new CookingFood(itemData[i++], COOKING_ALLFRUIT));
	itemList.push_back(new CookingFood(itemData[i++], COOKING_YELLOW));
	itemList.push_back(new CookingFood(itemData[i++], COOKING_BERRIES));

}

void ItemManager::LoadItem()
{
	std::ifstream load("Data/Item.txt");


	// 파일이 성공적으로 열렸는지 확인
	if (load.is_open()) {

		 for (int i = 0; i < ITEM_COUNT; i++) 
		 {
			ITEM_DETAIL tmp_ItemDetail;
			std::string tmp;
			
			if (i != 0)
				load.ignore();
			//load.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 개행 문자 무시
			std::getline(load, tmp_ItemDetail.name); // 개행 문자 처리
			std::getline(load, tmp_ItemDetail.ImageBmp);
			std::getline(load, tmp_ItemDetail.detailInfo);

			load >> tmp_ItemDetail.m_health;
			load >> tmp_ItemDetail.m_hunger;
			load >> tmp_ItemDetail.m_thirst;
			load >> tmp_ItemDetail.m_fatigue;

			itemData.push_back(tmp_ItemDetail);
		 }

		// 파일 스트림 닫기
		load.close();
	}
}

ItemManager::~ItemManager()
{
}