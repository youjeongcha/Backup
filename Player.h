#pragma once
#include "Character.h"
#include "Weapon.h"
#include "MonsterBook.h"
//Player�� ���� Static ���� ���� ���ƾ� ��

//GameManager�� �����ؼ� ����� �� ����, �ʿ��� enum�� �߰������� ����

class Player : public Character //private? protected?
{ 
private:
	Weapon* weapon; //���ĸ� �����ϰ�. ��ĳ�����ؼ� ������ �ݵ�� �����ͷ� �޾ƾ��� //��ü�� �����Ϸ��� �����Ҵ����
	MonsterBook monsterBook;
	__int64 mSaveSeed; //long������ �־ �ȴ�. //seed���� ������ ���� ������ ���� ����� ���´�.
	bool mPlayerGameOverCheck;

public:
	Player();
	~Player();

	int Recover();
	
	//GameManager�ʿ� ���� SCENE���� ��ȯ�ȴ�.
	int PlayeInitialSetting(bool newStart = true); //�÷��̾� ���� �ʱ�ȭ�ϴ� �Լ�(�̸� ���� GameOver ���� ���� true�� false��)
	void SavePlayerInfo(int mSceneNum, bool weaponSaveCheck = false);
	void SaveGameOverPlayerInfo();
	//GameManager�ʿ� ���� SCENE���� ��ȯ�ȴ�.
	int LoadPlayerInfo();

	//virtual -  ���� ���� ��±��� �߰��ؾ� �ϹǷ�. override ǥ��.
	//[ctrl] + [.] ������ .cpp�� �ٷ� �ۼ��� ����
	virtual void PrintInfo(int _Y = GAP_11, int _X = MAP_END_X / 2 - GAP_8) override; //���߿�
	void PrintMonsterBook(vector<Character*> monsterInfoList); //������ ��� ���͵� ���

	void SetName(string _Name) { mName = _Name; }
	void SetWeapon(Weapon* _weapon) { weapon = _weapon; }
	void SetSeed(__int64 _Seed) { mSaveSeed = _Seed; }
	//void SetPlayerGameOverCheck(bool _playerGameOverCheck) { mPlayerGameOverCheck = _playerGameOverCheck; }

	MonsterBook* GetMonsterBook() { return &monsterBook; } //monsterBook�� �Ұ��� �����ϱ� ���ؼ�.
	Weapon* GetWeapon() { return weapon; }
	__int64 GetSeed() { return mSaveSeed; }
	bool GetPlayerGameOverCheck() { return mPlayerGameOverCheck; }
};