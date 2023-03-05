#include "Character.h"
#include "MonsterBook.h" //enum�� ReadMonsterBook(); "SaveMonsterBook.txt" ���� �о���� ��� ����

Character::Character()
{
}

Character::Character(const Character& monster) //���� ������ �����Ұ����ϰ� const�� �����ؼ� ���
{//Charcter�����ؼ� monster ����
	mName = monster.mName; //�̸�
	mLevel = monster.mLevel;
	mAttack = monster.mAttack;
	mMax_HP = monster.mMax_HP;
	mMax_EXP = monster.mMax_EXP; //���� �� �ܿ� ä�� �� �ִ� ����ġ
	mGetEXP = monster.mGetEXP; //���͸� ���̸� ���� �� �ִ� ����ġ
	mGold = monster.mGold;
	mNow_HP = monster.mNow_HP;
	mNow_EXP = monster.mNow_EXP; //����ġ ���� ������

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
	str = "���ݷ� = " + attack;
	MapDraw::DrawPoint(str, *_X, *_Y);
	str = "����� = " + nowHP + "/" + maxHP;
	MapDraw::DrawPoint(str, *_X + GAP_9, (*_Y)++);

}

void Character::Print_EXP_Gold(string now_EXP, string max_EXP, string getEXP, string gold, int* _Y, int* _X)
{
	string str;

	MapDraw::DrawMidText("                                              ", *_X, (*_Y));
	str = "����ġ = " + now_EXP + "/" + max_EXP;
	MapDraw::DrawPoint(str, *_X, *_Y);
	str = "GetEXP : " + getEXP;
	MapDraw::DrawPoint(str, *_X + GAP_9, (*_Y)++);
	str = "Gold = " + gold;
	MapDraw::DrawMidText("                                              ", *_X, (*_Y));
	MapDraw::DrawPoint(str, *_X, *_Y);
}

void Character::PrintInfo(int _Y, int _X)
{//xy�� ȿ�������� ��ġ �ʿ�
	Print_Name_Attack_HP(mName, to_string(mLevel), to_string(mAttack), to_string(mNow_HP), to_string(mMax_HP), &_Y, &_X);
	Print_EXP_Gold(to_string(mNow_EXP), to_string(mMax_EXP), to_string(mGetEXP), to_string(mGold), &_Y, &_X);
}

void Character::PrintMonsterBookInfo(MONSTER monster, bool(*bSituation)[MONSTER_COUNT], int _Y, int _X)
{//to_string ������ ���ڿ��� �ٲ��ִ� �Լ�
	string printName;
	string sFalse = "???";

	//���� ���� �� �� �� �ִ� ����
	if (bSituation[SITUATION_MEET][monster] == TRUE) // �� �̰� ��� �ϴ� �� �� ���ٰ� �߾���...?
		printName = PrintMeet(mName);
	else
		printName = PrintMeet(sFalse);

	//���� �� �� �� �ִ� ����
	if (bSituation[SITUATION_FIGHT][monster] == TRUE)
		Print_Name_Attack_HP(mName, to_string(mLevel), to_string(mAttack), to_string(mNow_HP), to_string(mMax_HP), &_Y, &_X);
		//PrintFight(printName, to_string(mLevel), to_string(mAttack), to_string(mNow_HP), to_string(mMax_HP), &_Y, &_X);
	else
		Print_Name_Attack_HP(printName, sFalse, sFalse, sFalse, sFalse, &_Y, &_X);

	//�¸� �� �� �� �ִ� ����
	if (bSituation[SITUATION_WIN][monster] == TRUE)
		Print_EXP_Gold(to_string(mNow_EXP), to_string(mMax_EXP), to_string(mGetEXP), to_string(mGold), &_Y, &_X);
	else
		Print_EXP_Gold(sFalse, sFalse, sFalse, sFalse, &_Y, &_X);
}