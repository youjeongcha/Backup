#include "Goblin.h"

Goblin::Goblin()
{ //mLevel = 1; mNow_EXP = 0; 는 Character 생성자에서 초기화 >>> 삭제해야함
	mEntityType = ENTITYTYPE_HUMANS;
	mMonsterType = MONSTER_GOBLIN;
	mName = "고블린"; // ★ name 삭제(필요)
}
Goblin::Goblin(Character monster) : Character(monster) //<부모인 Charcter의 monster 형태>를 호출하는 방법
{//★ 몬스터 하나하나의 cpp에 작성 않고 Character에서 상속 받아서 사용.(완)
	/*
		mName = monster.Get_Name(); //이름
		mLevel = monster.Get_Level();
		mAttack = monster.Get_Attack();
		mMax_HP = monster.Get_MaxHP();
		mMax_EXP = monster.Get_MaxEXP(); //레벨 한 단에 채울 수 있는 경험치
		mGetEXP = monster.Get_GetEXP(); //몬스터를 죽이면 얻을 수 있는 경험치
		mGold = monster.Get_Gold();
		mNow_HP = monster.Get_NowHP();
		mNow_EXP = monster.Get_NowEXP(); //경험치 차면 레벨업

		mEntityType = monster.Get_EntityType();
		mMonsterType = monster.Get_MonsterType();
		*/
}
Goblin::~Goblin() { }