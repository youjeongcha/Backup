#include "Werewolves.h"

Werewolves::Werewolves()
{
	mEntityType = ENTITYTYPE_ANIMALS;
	mMonsterType = MONSTER_WEREWOLVES;
	mName = "�����ΰ�"; // �� name ����(�ʿ�)
}
Werewolves::Werewolves(Character monster) : Character(monster) //<�θ��� Charcter�� monster ����>�� ȣ���ϴ� ���
{
	/*
	mName = monster.Get_Name(); //�̸�
	mLevel = monster.Get_Level();
	mAttack = monster.Get_Attack();
	mMax_HP = monster.Get_MaxHP();
	mMax_EXP = monster.Get_MaxEXP(); //���� �� �ܿ� ä�� �� �ִ� ����ġ
	mGetEXP = monster.Get_GetEXP(); //���͸� ���̸� ���� �� �ִ� ����ġ
	mGold = monster.Get_Gold();
	mNow_HP = monster.Get_NowHP();
	mNow_EXP = monster.Get_NowEXP(); //����ġ ���� ������

	mEntityType = monster.Get_EntityType();
	mMonsterType = monster.Get_MonsterType();
	*/
}
Werewolves::~Werewolves() { }