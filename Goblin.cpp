#include "Goblin.h"

Goblin::Goblin()
{ //mLevel = 1; mNow_EXP = 0; �� Character �����ڿ��� �ʱ�ȭ >>> �����ؾ���
	mEntityType = ENTITYTYPE_HUMANS;
	mMonsterType = MONSTER_GOBLIN;
	mName = "���"; // �� name ����(�ʿ�)
}
Goblin::Goblin(Character monster) : Character(monster) //<�θ��� Charcter�� monster ����>�� ȣ���ϴ� ���
{//�� ���� �ϳ��ϳ��� cpp�� �ۼ� �ʰ� Character���� ��� �޾Ƽ� ���.(��)
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
Goblin::~Goblin() { }