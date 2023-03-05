#include "Werewolves.h"

Werewolves::Werewolves()
{
	mEntityType = ENTITYTYPE_ANIMALS;
	mMonsterType = MONSTER_WEREWOLVES;
	mName = "늑대인간"; // ★ name 삭제(필요)
}
Werewolves::Werewolves(Character monster) : Character(monster) //<부모인 Charcter의 monster 형태>를 호출하는 방법
{
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
Werewolves::~Werewolves() { }