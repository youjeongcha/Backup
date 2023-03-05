#include "Character.h"
#include "MonsterBook.h" //enum과 ReadMonsterBook(); "SaveMonsterBook.txt" 파일 읽어오기 사용 위해

Character::Character()
{
}

Character::Character(const Character& monster) //복사 연산은 수정불가능하게 const로 참조해서 사용
{//Charcter경유해서 monster 복사
	mName = monster.mName; //이름
	mLevel = monster.mLevel;
	mAttack = monster.mAttack;
	mMax_HP = monster.mMax_HP;
	mMax_EXP = monster.mMax_EXP; //레벨 한 단에 채울 수 있는 경험치
	mGetEXP = monster.mGetEXP; //몬스터를 죽이면 얻을 수 있는 경험치
	mGold = monster.mGold;
	mNow_HP = monster.mNow_HP;
	mNow_EXP = monster.mNow_EXP; //경험치 차면 레벨업

	mEntityType = monster.mEntityType;
	mMonsterType = monster.mMonsterType;
}

Character::~Character()
{
}

void Character::LevelUp(int plus_MaxHP, int plus_MaxEXP, int plus_Attack)
{
	mNow_EXP -= mMax_EXP;
	mLevel++;

	mMax_HP += plus_MaxHP;
	mMax_EXP += plus_MaxEXP;
	mAttack += plus_Attack;
}


void Character::Print_Name_Attack_HP(string name, string level, string attack, string nowHP, string maxHP, int* _Y, int* _X)
{
	string str;

	str = "======" + name + "(" + level + "Lv)======";
	MapDraw::DrawMidText("                                        ", MAP_END_X, (*_Y));
	MapDraw::DrawMidText(str, MAP_END_X, (*_Y)++);

	MapDraw::DrawMidText("                                              ", *_X, (*_Y));
	str = "공격력 = " + attack;
	MapDraw::DrawPoint(str, *_X, *_Y);
	str = "생명력 = " + nowHP + "/" + maxHP;
	MapDraw::DrawPoint(str, *_X + GAP_9, (*_Y)++);

}

void Character::Print_EXP_Gold(string now_EXP, string max_EXP, string getEXP, string gold, int* _Y, int* _X)
{
	string str;

	MapDraw::DrawMidText("                                              ", *_X, (*_Y));
	str = "경험치 = " + now_EXP + "/" + max_EXP;
	MapDraw::DrawPoint(str, *_X, *_Y);
	str = "GetEXP : " + getEXP;
	MapDraw::DrawPoint(str, *_X + GAP_9, (*_Y)++);
	str = "Gold = " + gold;
	MapDraw::DrawMidText("                                              ", *_X, (*_Y));
	MapDraw::DrawPoint(str, *_X, *_Y);
}

void Character::PrintInfo(int _Y, int _X)
{//xy축 효율적으로 배치 필요
	Print_Name_Attack_HP(mName, to_string(mLevel), to_string(mAttack), to_string(mNow_HP), to_string(mMax_HP), &_Y, &_X);
	Print_EXP_Gold(to_string(mNow_EXP), to_string(mMax_EXP), to_string(mGetEXP), to_string(mGold), &_Y, &_X);
}

void Character::PrintMonsterBookInfo(MONSTER monster, bool(*bSituation)[MONSTER_COUNT], int _Y, int _X)
{//to_string 정수를 문자열로 바꿔주는 함수
	string printName;
	string sFalse = "???";

	//몬스터 조우 시 알 수 있는 정보
	if (bSituation[SITUATION_MEET][monster] == TRUE) // ★ 이거 어떻게 하는 게 더 좋다고 했었지...?
		printName = PrintMeet(mName);
	else
		printName = PrintMeet(sFalse);

	//전투 시 알 수 있는 정보
	if (bSituation[SITUATION_FIGHT][monster] == TRUE)
		Print_Name_Attack_HP(mName, to_string(mLevel), to_string(mAttack), to_string(mNow_HP), to_string(mMax_HP), &_Y, &_X);
		//PrintFight(printName, to_string(mLevel), to_string(mAttack), to_string(mNow_HP), to_string(mMax_HP), &_Y, &_X);
	else
		Print_Name_Attack_HP(printName, sFalse, sFalse, sFalse, sFalse, &_Y, &_X);

	//승리 시 알 수 있는 정보
	if (bSituation[SITUATION_WIN][monster] == TRUE)
		Print_EXP_Gold(to_string(mNow_EXP), to_string(mMax_EXP), to_string(mGetEXP), to_string(mGold), &_Y, &_X);
	else
		Print_EXP_Gold(sFalse, sFalse, sFalse, sFalse, &_Y, &_X);
}