#include "MonsterBook.h"

MonsterBook::MonsterBook()
{
	//�������迭 �ʱ�ȭ
	//�޸� �ּ� �̸�, ������ ��, ���� ���� * �� * ��
	ZeroMemory(bSituation, sizeof(bool) * SITUATION_END * MONSTER_COUNT);
}
MonsterBook::~MonsterBook()
{
}

void MonsterBook::ReadMonsterBook()
{//"SaveMonsterBook.txt" ���� �о����
	ifstream load;

	load.open("SaveMonsterBook.txt");

	if (load.is_open())
	{
		for (int i = 0; i < MONSTER_COUNT; i++) // �� ���Ͽ� �ش縸ŭ�� ���ڰ� �������� �ʴ� ��� ������ ���� �� �� �ִ�. �׷��� ���? 
		{
			//���� ���� �� �� �� �ִ� ����
			load >> bSituation[SITUATION_MEET][i];
			//���� �� �� �� �ִ� ����
			load >> bSituation[SITUATION_FIGHT][i];
			//�¸� �� �� �� �ִ� ����
			load >> bSituation[SITUATION_WIN][i];
		}
		load.close();
	}
}

//MonsterManager�� ���� MonsterList�̿�. enum�� ���� �÷��̾ ó�� ���� ��Ȳ �ľ�
//Character MonsterInfo�� MonsterManager���� �Ѿ�� ���� ����, �������ͽ��� "SaveMonsterBook.txt"�� �����.
//����� �Ǵϱ� ���� buff�� �޾Ƶ״ٰ�
void MonsterBook::RecodeMonsterBook(SITUATION situation, MONSTER monster)
{
	bSituation[situation][monster] = '1';
	/*

	switch (situation)
	{
	case SITUATION_MEET:
		if (monster == MONSTER_GOBLIN)
			bSituation[SITUATION_MEET][MONSTER_GOBLIN] = '1';
		else if (monster == MONSTER_OAK)
			bSituation[SITUATION_MEET][MONSTER_OAK] = '1';
		else if (monster == MONSTER_WEREWOLVES)
			bSituation[SITUATION_MEET][MONSTER_WEREWOLVES] = '1';
		break;
	case SITUATION_FIGHT:
		if (monster == MONSTER_GOBLIN)
			bSituation[SITUATION_FIGHT][MONSTER_GOBLIN] = '1';
		else if (monster == MONSTER_OAK)
			bSituation[SITUATION_FIGHT][MONSTER_OAK] = '1';
		else if (monster == MONSTER_WEREWOLVES)
			bSituation[SITUATION_FIGHT][MONSTER_WEREWOLVES] = '1';
		break;
	case SITUATION_WIN:
		if (monster == MONSTER_GOBLIN)
			bSituation[SITUATION_WIN][MONSTER_GOBLIN] = '1';
		else if (monster == MONSTER_OAK)
			bSituation[SITUATION_WIN][MONSTER_OAK] = '1';
		else if (monster == MONSTER_WEREWOLVES)
			bSituation[SITUATION_WIN][MONSTER_WEREWOLVES] = '1';
		break;
	}*/

	//return (bool*)bSituation;

	//load.open("SaveMonsterBook.txt");

	//load.seekg(0, ios::end); //seekg ���� �ȿ� �ִ� �����͸� ��� �� ��. �޸��嵵 Ŀ���� �̿� //�޸����� Ŀ���� �Ű��ַ��� ���� //�������̶�� Ÿ�԰�. �Ӽ��� ���� 0�� �ִ´�. end�� way�� Ŀ�� ��ġ�� �ǹ��Ѵ�. �޸��� ���κ����� �̵�.
	//int size = load.tellg(); //tellg ���� �޸��忡 �ִ� Ŀ���� ��ġ �տ� �ִ� ���ڼ��� �����´�.
	//load.read(&buff[0], size); //read�� ���� �����ϴ� ���ڼ���ŭ�� ���Ͽ��� �ٷ� ���´�. c����� ��ü ���� fread�� ����
	//load.seekg(0, ios::beg); //seekg ���� �ȿ� �ִ� �����͸� ��� �� ��. �޸��嵵 Ŀ���� �̿� //�޸����� Ŀ���� �Ű��ַ��� ���� //beg �ٽ� Ŀ���� ��ó������ ������.

	/*
	//��� 0,2,4 //��ũ 6,8,10 //������� 12, 14, 16
	if (load.is_open())
	{
		//getline(load, buff); //���� ������ �������� �ڵ�

		switch (situation)
		{
		case SITUATION_MEET:
			//load >> bCheck;
			if (((monster == MONSTER_GOBLIN)) && (bCheck == false))
			{
				buff[MONSTER_GOBLIN] = '1';
				bSituation[MONSTER_GOBLIN][SITUATION_MEET]
				//save << buff;
				return;
			}
			else if ((monster == MONSTER_OAK) && (bCheck == false))
			{
				buff[MONSTER_OAK + GAP_5] = '1';
				save << buff;
				return;
			}
			else if ((monster == MONSTER_WEREWOLVES) && (bCheck == false))
			{
				buff[MONSTER_WEREWOLVES + GAP_10] = '1';
				save << buff;
				return;
			}
			break;
		case SITUATION_FIGHT:
			load >> bCheck;
			if ((monster == MONSTER_GOBLIN) && (bCheck == false))
			{
				buff[MONSTER_GOBLIN + GAP_2] = '1';
				save << buff;
				return;
			}
			else if ((monster == MONSTER_OAK) && (bCheck == false))
			{
				buff[MONSTER_OAK + GAP_7] = '1';
				save << buff;
				return;
			}
			else if ((monster == MONSTER_WEREWOLVES) && (bCheck == false))
			{
				buff[MONSTER_WEREWOLVES + GAP_12] = '1';
				save << buff;
				return;
			}
			break;
		case SITUATION_WIN:
			load >> bCheck;
			if ((monster == MONSTER_GOBLIN) && (bCheck == false))
			{
				buff[MONSTER_GOBLIN + GAP_4] = '1';
				save << buff;
				return;
			}
			else if ((monster == MONSTER_OAK) && (bCheck == false))
			{
				buff[MONSTER_OAK + GAP_9] = '1';
				save << buff;
				return;
			}
			else if ((monster == MONSTER_WEREWOLVES) && (bCheck == false))
			{
				buff[MONSTER_WEREWOLVES + GAP_12 + GAP_2] = '1';
				save << buff;
				return;
			}
			break;
		}
		load.close();
		save.close();
	}*/
}

void MonsterBook::SaveMonsterBook()
{
	ofstream save;
	save.open("SaveMonsterBook.txt");

	for (int i = 0; i < MONSTER_COUNT; i++)
	{
		//���� ���� �� �� �� �ִ� ����
		save << bSituation[SITUATION_MEET][i] << " ";
		//���� �� �� �� �ִ� ����
		save << bSituation[SITUATION_FIGHT][i] << " ";
		//�¸� �� �� �� �ִ� ����
		save << bSituation[SITUATION_WIN][i] << " ";
	}
	save.close();
}

void MonsterBook::ResetMonsterBook()
{
	ofstream save;
	save.open("SaveMonsterBook.txt");
	save << "0 0 0 0 0 0 0 0 0";
	save.close();
}