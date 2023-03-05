 #pragma once
#include "Mecro.h"
#include "MapDraw.h"

enum MONSTER
{
	MONSTER_NONE = 'p', //player�� ������ ���� ��. ���Ͱ� �ƴϴ�.
	MONSTER_GOBLIN = 0,
	MONSTER_OAK,
	MONSTER_WEREWOLVES,
	//AUGGLE,
	//SKELETON,
	//RICHIE
	MONSTER_COUNT
};
enum ENTITYTYPE
{//������, �ΰ���, ������, ������, ��Ʈ, ��, ��
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
protected: //private ���� �ϸ� �ڽĿ��� ���� �Ұ� > protected
	string mName; //�̸�
	int mLevel;
	int mAttack;
	int mMax_HP;
	int mMax_EXP; //���� �� �ܿ� ä�� �� �ִ� ����ġ
	int mGetEXP; //���͸� ���̸� ���� �� �ִ� ����ġ
	int mGold;
	int mNow_HP;
	int mNow_EXP; //����ġ ���� ������
	ENTITYTYPE mEntityType;
	MONSTER mMonsterType;
public:
	Character();
	Character(const Character& monster); //���� ������ �����Ұ����ϰ� const�� �����ؼ� ���
	~Character();
	//�ε�� virtual�� �ؾ� �Ѵ�. moster�ʿ����� player���� �ϴ� ���� �޶��� �� ����
	//������ ������ ����� ������ϱ� ������. �׷��� �߰� �ڵ� �ۼ� ����

	Character NewCharacter() { Character charater; return charater; }

	void LevelUp(int plus_MaxHP, int plus_MaxEXP, int plus_Attack);
	
	void Print_Name_Attack_HP(string name, string level, string attack, string nowHP, string maxHP, int* _Y, int* _X);
	void Print_EXP_Gold(string now_EXP, string max_EXP, string getEXP, string gold, int* _Y, int* _X);
	virtual void PrintInfo(int _Y = PRINT_START_Y, int _X = PRINT_START_X); //�갡 �� �Լ� ��� �ִ� �� ������ �߿�

	void PrintMonsterBookInfo(MONSTER monster, bool(*bSituation)[MONSTER_COUNT], int _Y = PRINT_START_Y, int _X = PRINT_START_X);
	string PrintMeet(string name) { return name; };



	string Get_Name() const { return mName; }
	int Get_Level() const { return mLevel; } //virtual�� �ʿ䰡 ����. �ڽ��ʿ��� �������̵� �� �ʿ� �����Ƿ�
	int Get_Attack() { return mAttack; }
	int Get_MaxHP() { return mMax_HP; }
	int Get_NowHP() { return mNow_HP; }
	int Get_MaxEXP() { return mMax_EXP; }
	int Get_NowEXP() { return mNow_EXP; }
	int Get_GetEXP() { return mGetEXP; }
	int Get_Gold() { return mGold; }
	ENTITYTYPE Get_EntityType() { return mEntityType; }
	MONSTER Get_MonsterType() { return mMonsterType; }

	void Set_Gold(int _gold) { mGold = _gold; } //������ ��带 �� ��� �� �� ����.
	void Set_NowHP(int _now_HP) { mNow_HP = _now_HP; }
	void Set_NowEXP(int _now_EXP) { mNow_EXP = _now_EXP; }

	void Set_Status(std::ifstream& load)
	{// �� lfstream load�� ���ڷ� �޾Ƽ� ���ο��� ó��. ����ȭ//�� �ȵǰ� �ִ� ��Ȳ�̾���.(��)

		//���� �� �� �� �ִ� ����
		load >> mAttack;
		load >> mMax_HP;
		load >> mNow_HP;
		load >> mLevel;

		//�¸� �� �� �� �ִ� ����
		load >> mMax_EXP;
		load >> mNow_EXP;
		load >> mGetEXP;
		load >> mGold;
	}
};

