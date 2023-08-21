#pragma once
#include "EngineMecro.h"

enum ITEM_ID
{
	ITEM_START,

	//Drink
	WATER = ITEM_START,

	//Food

	//Light Object
	//성냥
	KEY,//열쇠
	SEED_RED,//씨앗
	SEED_ORANGE,//씨앗
	SEED_YELLOW,//씨앗
	SEED_BLUE,//씨앗
	FRUIT_RED,//열매
	FRUIT_ORANGE,//열매
	FRUIT_YELLOW,//열매
	FRUIT_BLUE,//열매

	//요리
	COOKING_ALLFRUIT,//모둠과일조림
	COOKING_YELLOW,//노랑과일조림
	COOKING_BERRIES,//베리류조림

	//Heavy Object
	//장작
	//양동이
	//촛대

	ITEM_COUNT,
	ITEM_NONE,
};

enum TYPE
{
	NONE,
	OBJECT,
	FOOD,
	DRINK,
};

enum USECOUNT
{
	USE_NONE, //사용 불가
	USE_ONE, //일회성
	//USE_PERMANENT, //영구 사용 //현재 구조에서는 영구 사용이 불가능하다.
};

struct ITEM_DETAIL
{
	std::string name; //아이템 이름
	std::string ImageBmp; //아이템 이미지
	std::string detailInfo; //아이템 상세정보

	//스텟 조정 수치
	int m_health, m_hunger, m_thirst, m_fatigue;

	//ITEM_ID itemID; //아이템 종류
	//TYPE itemType; //아이템 타입
	//USECOUNT useCount; //사용 횟수
};

class Item abstract
{
protected:
	//아이템 사용후 뜰 텍스트
	//UNDERTXT itemUseTxt;
	//ITEM_DETAIL item_Detail;
	int itemUseTxt; //UNDERTXT 형식을 GameManager.h를 상속 받아 사용하면 헤더 겹침으로 int형으로 사용
	//int itemCount; //아이템의 수량 저장

	bool isUsing; //사용 가능 체크

	std::string name; //아이템 이름
	std::string ImageBmp; //아이템 이미지
	std::string detailInfo; //아이템 상세정보

	//스텟 조정 수치
	int m_health, m_hunger, m_thirst, m_fatigue;

	ITEM_ID itemID; //아이템 종류
	TYPE itemType; //아이템 타입
	USECOUNT useCount; //사용 횟수

public:
	Item();
	Item(ITEM_DETAIL itemDetail, ITEM_ID _itemID);
	~Item();

	//virtual void Use();
	void Use();

	std::string GetName() { return name; }
	std::string GetDetailInfo() { return detailInfo; }
	std::string GetImageBmp() { return ImageBmp; }
	bool GetisUsing() { return isUsing; }
	ITEM_ID GetItemID() { return itemID; }
};

