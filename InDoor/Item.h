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
	USE_PERMANENT, //영구 사용
};

class Item abstract
{
protected:
	//아이템 사용후 뜰 텍스트
	//UNDERTXT itemUseTxt;
	int itemUseTxt; //UNDERTXT 형식을 GameManager.h를 상속 받아 사용하면 헤더 겹침으로 int형으로 사용
	//int itemCount; //아이템의 수량 저장
	ITEM_ID itemID; //아이템 종류
	TYPE itemType; //아이템 타입
	USECOUNT useCount; //사용 횟수
	bool isUsing; //사용 가능 체크
	
	std::string name; //아이템 이름
	std::string detailInfo; //아이템 상세정보
	std::string ImageBmp; //아이템 이미지

	//스텟 조정 수치
	int m_health, m_hunger, m_thirst, m_fatigue;
public:
	Item();
	~Item();

	//virtual void Use();
	void Use();

	std::string GetName() { return name; }
	std::string GetDetailInfo() { return detailInfo; }
	std::string GetImageBmp() { return ImageBmp; }
	bool GetisUsing() { return isUsing; }
	ITEM_ID GetItemID() { return itemID; }
};

