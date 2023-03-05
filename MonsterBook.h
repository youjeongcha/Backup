#pragma once
#include "Character.h"
//#include "Goblin.h"
//#include "Oak.h"
//#include "Werewolves.h"

// �� monsterBook�� monsterManager�� ��� ������ �����ϰ� player�� �̰����� �޾ƿ� �ʿ䰡 ���������� �𸥴�.
// �� �������� ���� ���

enum SITUATION
{//���� ��Ͽ�
	SITUATION_MEET,
	SITUATION_FIGHT,
	SITUATION_WIN,
	SITUATION_END
};

class MonsterBook
{
private:
	bool bSituation[SITUATION_END][MONSTER_COUNT];// = { 0, };
	//list<Character*> monsterBookList;//���ͺ� ���� �����͸� �����Ѵ�
public:
	MonsterBook();
	~MonsterBook();
	void ReadMonsterBook(); //"SaveMonsterBook.txt" ���� �о����
	//bool* RecodeMonsterBook(SITUATION situation, MONSTER monster); //���� ����� ��� ���� ���� �� bSituation�� ���
	void RecodeMonsterBook(SITUATION situation, MONSTER monster); //���� ����� ��� ���� ���� �� bSituation�� ���
	void SaveMonsterBook(); //���� ���� ������ ���
	//situation(1~3)�� enum�� ���� �÷��̾ � ���Ϳ� ������ �ϴ��� ��Ȳ �ľ��� ���Ͽ� ���
	//1.����� �� �� �ִ� ���� 
	//2.������ �� �� �ִ� ���� 
	//3.�¸��� �� �� �ִ� ����
	void ResetMonsterBook();

	bool (*GetSituation())[MONSTER_COUNT] { return bSituation; } //������ �迭�� �����͸� �̿��� �Ѱ��ִ� ���
	//list<Character*> Get_MonsterBookList() { return monsterBookList; }
};

