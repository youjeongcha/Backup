#include "Oak.h"

Oak::Oak()
{
	mEntityType = ENTITYTYPE_HUMANS;
	mMonsterType = MONSTER_OAK;
	mName = "��ũ"; // �� name ����(�ʿ�)
}
Oak::Oak(Character monster) : Character(monster) //<�θ��� Charcter�� monster ����>�� ȣ���ϴ� ���
{
	//Character(const Character & monster);
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
Oak::~Oak() { }