#include "MonsterManager.h"

MonsterManager::MonsterManager()
{
	// �� vector�� ó�� �ٶ�. 
	// �� �̰� ���� ���⼭ �Ұ� �ƴ϶� LOAD���� ��� ���� ������ �������� ���� �ٷ�.
	monsterInfoList.push_back(new Goblin);
	monsterInfoList.push_back(new Oak);
	monsterInfoList.push_back(new Werewolves);
	ReadMonsterStatus();//������ �⺻ ���� �����̴��� ��������
}


MonsterManager::~MonsterManager()
{//�����Ҵ� ����
	CreateMonsterReset();

	for (vector<Character*>::iterator iter = monsterInfoList.begin(); iter != monsterInfoList.end();)
	{
		Character* c = *iter;
		iter = monsterInfoList.erase(iter);
		delete c;
	}
}

void MonsterManager::CreateMonsterReset()
{
	for (list<Character*>::iterator iter = monsterList.begin(); iter != monsterList.end();) // �� vector�� ����
	{
		Character* c = *iter;
		iter = monsterList.erase(iter);
		delete c;
	}
}

void MonsterManager::ResetSaveMonstersTxt()
{
	ofstream save;

	save.open("SaveMonsters.txt");

	save << 0;

	save.close();
}

void MonsterManager::SaveMonsters()
{
	if (!monsterList.size() == 0)
	{
		ofstream save;

		save.open("SaveMonsters.txt");

		save << monsterList.size() << endl;

		for (Character* character : monsterList)
		{ // �� �̰͵� ����ȭ. �ѹ��� ó���ϴ� �Լ���
			save << character->Get_Name() << " ";
			save << character->Get_Attack() << " ";
			save << character->Get_MaxHP() << " ";
			save << character->Get_NowHP() << " ";
			save << character->Get_Level() << " ";
			save << character->Get_MaxEXP() << " ";
			save << character->Get_NowEXP() << " ";
			save << character->Get_GetEXP() << " ";
			save << character->Get_Gold() << endl;
		}
		save.close();
	}
}

// �� ���� ���� list ����, ������ ����(����ִ�) �ҷ����� ó���ϴ� �Լ�
void MonsterManager::LoadMonsters()
{
	ifstream load;
	Character* tmpMonster;
	string _Name;
	int monstersCount,_Attack, _Max_HP, _Now_HP, _Level, _Max_EXP, _Now_EXP, _GetEXP, _Gold;

	load.open("SaveMonsters.txt");

	if (load.is_open())
	{
		load >> monstersCount;

		for (int i = 1; i <= monstersCount; i++)
		{
			load >> _Name;

			if (_Name == "���")
				tmpMonster = new Goblin;
			else if (_Name == "��ũ")
				tmpMonster = new Oak;
			else if (_Name == "�����ΰ�")
				tmpMonster = new Werewolves;


			// �� ifstream load;�� �޾ƿ��� ���� // �� �ѹ��� ó��

			tmpMonster->Set_Status(load);

			//load >> _Attack;
			//load >> _Max_HP;
			//load >> _Now_HP;
			//load >> _Level;
			//load >> _Max_EXP;
			//load >> _Now_EXP;
			//load >> _GetEXP;
			//load >> _Gold;
			
			//tmpMonster->Set_Status(_Name, _Attack, _Max_HP, _Now_HP, _Level, _Max_EXP, _Now_EXP, _GetEXP, _Gold);

			// �� ������ ������� ����

			monsterList.push_back(tmpMonster);
		}
		load.close();
	}
}

// �� �̰� ���� ���⼭ �Ұ� �ƴ϶� LOAD���� ��� ���� ������ �������� ���� �ٷ�.
// �� �Լ� ����
//���� ���� �����̴��� �������� : ���� ������ ������ ��� ���� �������ͽ���
void MonsterManager::ReadMonsterStatus() {
	ifstream load;
	int MonstersCount;
	string _Name; 
	int _Attack, _Max_HP, _Now_HP, _Level, _Max_EXP, _Now_EXP, _GetEXP, _Gold;

	//TODO :: ���� ������ ������ ��� ���� �������ͽ���. ��ȸ���� ��� ���� ���� ���� �޾ƿ����� ���� ���� �ٶ� 
	load.open("SaveOriginalMonster.txt");
	if (!load.eof())
	{
		load >> MonstersCount;

		for (int i = 1; i <= MonstersCount; i++)
		{
			load >> _Name;
			for (Character* character : monsterInfoList)
			{//�ش� �̸��� list�� ������ �װ��� �������ͽ� ����
				if (character->Get_Name() == _Name)
				{
					// �� �ѹ��� ó��
					//load >> _Attack;
					//load >> _Max_HP;
					//load >> _Now_HP;
					//load >> _Level;
					//load >> _Max_EXP;
					//load >> _Now_EXP;
					//load >> _GetEXP;
					//load >> _Gold;

					character->Set_Status(load);
					//character->Set_Status(_Name, _Attack, _Max_HP, _Now_HP, _Level, _Max_EXP, _Now_EXP, _GetEXP, _Gold);
				}
			}
		}
	load.close();
	}
}

void MonsterManager::MonsterCreate(MONSTER monster)
{
	Character* tmpMonster;
	//string _Name;
	//int _Attack, _Max_HP, _Now_HP, _Level, _Max_EXP, _Now_EXP, _GetEXP, _Gold;

	//monsterInfoList[monster];

	switch (monster)
	{
	case MONSTER_GOBLIN:
		tmpMonster = new Goblin(*monsterInfoList[monster]);
		break;
	case MONSTER_OAK:
		tmpMonster = new Oak(*monsterInfoList[monster]);
		break;
	case MONSTER_WEREWOLVES:
		tmpMonster = new Werewolves(*monsterInfoList[monster]);
		break;
	default:
		break;
	}
	monsterList.push_back(tmpMonster);

	//tmpMonster = monsterInfoList[monster]; //�̰Ŵ� monsterInfoList�� �ּҸ� �����ؿͼ�. tmpMonster�� ���� �ּҰ��� �ٲ�����(���� ���� ���X)
	/*
	for (list<Character*>::iterator iter = monsterInfoList.begin(); iter != monsterInfoList.end(); iter++)
	{//InfoList�� List ���� ���ϱ�
		if ((*iter)->Get_Name() == _Name)
		{
			_Attack = (*iter)->Get_Attack();
			_Max_HP = (*iter)->Get_MaxHP();
			_Max_EXP = (*iter)->Get_MaxEXP();
			_GetEXP = (*iter)->Get_GetEXP();
			_Level = (*iter)->Get_Level();
			_Gold = (*iter)->Get_Gold();
			_Now_HP = (*iter)->Get_NowHP();
			_Now_EXP = (*iter)->Get_NowEXP();
			tmpMonster->Set_Status(_Name, _Attack, _Max_HP, _Now_HP, _Level, _Max_EXP, _Now_EXP, _GetEXP, _Gold);
		}
	}*/
}