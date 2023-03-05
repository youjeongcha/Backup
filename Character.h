 #pragma once
#include "Mecro.h"
#include "MapDraw.h"

enum MONSTER
{
	MONSTER_NONE = 'p', //player가 가지고 있을 것. 몬스터가 아니다.
	MONSTER_GOBLIN = 0,
	MONSTER_OAK,
	MONSTER_WEREWOLVES,
	//AUGGLE,
	//SKELETON,
	//RICHIE
	MONSTER_COUNT
};
enum ENTITYTYPE
{//비행형, 인간형, 동물형, 물질형, 고스트, 본, 등
	ENTITYTYPE_HUMANS,
	ENTITYTYPE_ANIMALS,
	ENTITYTYPE_FLIGHT,
	ENTITYTYPE_GHOSTS,
	ENTITYTYPE_BONES,
	ENTITYTYPE_COUNT,
};
enum LEVELUP_STAT
{
	PLAYER_PLUS_MAXHP = 5,
	PLAYER_PLUS_MAXEXP = 5,
	PLAYER_PLUS_ATTACK = 5,
	MONSTER_PLUS_MAXHP = 20,
	MONSTER_PLUS_MAXEXP = 5,
	MONSTER_PLUS_ATTACK = 10,
};
enum Print
{
	PRINT_START_Y = 12,
	PRINT_START_X = MAP_END_X / 2 - GAP_8
};

class Character
{
protected: //private 으로 하면 자식에서 접근 불가 > protected
	string mName; //이름
	int mLevel;
	int mAttack;
	int mMax_HP;
	int mMax_EXP; //레벨 한 단에 채울 수 있는 경험치
	int mGetEXP; //몬스터를 죽이면 얻을 수 있는 경험치
	int mGold;
	int mNow_HP;
	int mNow_EXP; //경험치 차면 레벨업
	ENTITYTYPE mEntityType;
	MONSTER mMonsterType;
public:
	Character();
	Character(const Character& monster); //복사 연산은 수정불가능하게 const로 참조해서 사용
	~Character();
	//로드는 virtual로 해야 한다. moster쪽에서랑 player에서 하는 형태 달라질 수 있음
	//무기의 정보도 출력을 해줘야하기 때문에. 그래야 추가 코드 작성 가능

	Character NewCharacter() { Character charater; return charater; }

	void LevelUp(int plus_MaxHP, int plus_MaxEXP, int plus_Attack);
	
	void Print_Name_Attack_HP(string name, string level, string attack, string nowHP, string maxHP, int* _Y, int* _X);
	void Print_EXP_Gold(string now_EXP, string max_EXP, string getEXP, string gold, int* _Y, int* _X);
	virtual void PrintInfo(int _Y = PRINT_START_Y, int _X = PRINT_START_X); //얘가 이 함수 들고 있는 거 맞음★ 중요

	void PrintMonsterBookInfo(MONSTER monster, bool(*bSituation)[MONSTER_COUNT], int _Y = PRINT_START_Y, int _X = PRINT_START_X);
	string PrintMeet(string name) { return name; };



	string Get_Name() const { return mName; }
	int Get_Level() const { return mLevel; } //virtual일 필요가 없다. 자식쪽에서 오버라이드 할 필요 없으므로
	int Get_Attack() { return mAttack; }
	int Get_MaxHP() { return mMax_HP; }
	int Get_NowHP() { return mNow_HP; }
	int Get_MaxEXP() { return mMax_EXP; }
	int Get_NowEXP() { return mNow_EXP; }
	int Get_GetEXP() { return mGetEXP; }
	int Get_Gold() { return mGold; }
	ENTITYTYPE Get_EntityType() { return mEntityType; }
	MONSTER Get_MonsterType() { return mMonsterType; }

	void Set_Gold(int _gold) { mGold = _gold; } //패자의 골드를 다 들고 올 때 쓴다.
	void Set_NowHP(int _now_HP) { mNow_HP = _now_HP; }
	void Set_NowEXP(int _now_EXP) { mNow_EXP = _now_EXP; }

	void Set_Status(std::ifstream& load)
	{// ★ lfstream load를 인자로 받아서 내부에서 처리. 은닉화//가 안되고 있는 상황이었다.(완)

		//전투 시 알 수 있는 정보
		load >> mAttack;
		load >> mMax_HP;
		load >> mNow_HP;
		load >> mLevel;

		//승리 시 알 수 있는 정보
		load >> mMax_EXP;
		load >> mNow_EXP;
		load >> mGetEXP;
		load >> mGold;
	}
};

