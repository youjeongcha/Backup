#pragma once
#include "Goblin.h"
#include "Oak.h"
#include "Werewolves.h"

class MonsterManager //����� �ʿ䰡 ����. monster �����ϴ� �Լ��� character�� �ƴ�
{
private:
	//TODO::��ȸ���� ���� ���Ͱ� ������ �����ϱ� �ٶ��ٸ� ���� ����� ó�� �ʿ�
	// �� �̰� vector�� �ٲٱ⸦ ��õ. �����Ҷ��� iter ������ ã�� ���� iter ������ ���� ����
	//���� ���� ��� list�� �ϳ��ϳ� �޴� �͵� ��������. ��� ���� ���ܼ� ���� ���Ͱ� ������ �޾��� �� �ֱ� ������, �ִ� ���� �� �ɾ�ΰ� ������ list�� �ִ� ���͵鸸 ������ �����ϴ� ���� �� ����.
	list<Character*> monsterList; //���� ��������� monsterList�� ����ִ�. 
	vector<Character*> monsterInfoList; //������ ������ ���� "SaveMonster.txt" ���Ͽ��� �޾ƿ�.
	//�����Ҵ��� �ϴ� ���� : �Լ������� bind�� ����ؼ� timer���� ������ �ϴµ� �����Ͱ� ���ư������Ƿ� �����Ҵ� �̿� �ʼ�
public:
	MonsterManager();
	~MonsterManager();

	//���� ���� �Լ� - ���ο� �������� ������ ������ ���������ؼ�. list(vector)���� ����
	void MonsterCreate(MONSTER monster);
	//void MonsterStatusSetting(Character* tmpMonster);
	void ReadMonsterStatus(); //"SaveMonster.txt" ���� ���� �������ͽ� ��������
	// �� �Լ� ����.����ȭ ����. Character���� ó��
	//������ ���� ���� (���� ��ü�� ���� ����� �ؽ�Ʈ�� ���� �־��ִ� ���̶� ����Ʈ �ʱ�ȭ ���ϸ� ���� ���� ���� x2)
	void CreateMonsterReset();

	//���� ���� ���� ����
	void ResetSaveMonstersTxt();
	void SaveMonsters();
	void LoadMonsters(); // �� ���� ���� list ����, ������ ����(����ִ�) �ҷ����� ó���ϴ� �Լ�


	// �� list ���� ���� �ʿ��� �ش� ���͸� ���� �޾ư� �� �ֵ��� �Լ� ����
	list<Character*>* Get_MonsterList() { return &monsterList; } //���� �������ͽ� Player���� ����.
	vector<Character*> Get_MonsterInfoList() { return monsterInfoList; } //bool�� ���� ���� ���� ��¿�.
};