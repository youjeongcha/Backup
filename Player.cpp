#include "Player.h"
#include "MonsterManager.h"
#include "WeaponShop.h"

Player::Player()
{
	mEntityType = ENTITYTYPE_HUMANS;
	mMonsterType = MONSTER_NONE;
	weapon = NULL;  //NULL�� �Ǵ��Ѵٸ� �ʱ갪 NULL ���� �ʼ�
}
Player::~Player()
{
}

int Player::Recover()
{
	int RecoveryHP = mMax_HP / 3;

	//HP�� ������ ���� �ʰ�
	mNow_HP = min(mMax_HP, mNow_HP + RecoveryHP);

	//MAX HP ȸ�� �ȵǵ���
	if (mNow_HP == mMax_HP)
		return 0;

	return RecoveryHP;
}

int Player::PlayeInitialSetting(bool newStart)
{ //�÷��̾� ���� ���·� �ʱ�ȭ�ϴ� �Լ�(�̸��� GameOver ���� ����)
	bool tmp;
	//�̸� ���� ���̽� ����

	mEntityType = ENTITYTYPE_HUMANS;
	mPlayerGameOverCheck = false;

	weapon = NULL;

	mAttack = 5;
	mMax_HP = 50;
	mMax_EXP = 10;
	mGetEXP = 30;
	mGold = 2000;

	mNow_HP = mMax_HP;
	mMax_EXP = mMax_EXP;

	mLevel = 1;
	mNow_EXP = 0;

	// �� �ٽ� �޾ƿ��� �ͺ��� bool ������ ContinueCheck == true �̷� ������ ����(��)
	if (newStart)
		mName = "???";
	else
	{
		ifstream load;
		load.open("SavePlayerInfo.txt");

		if (load.is_open())
		{
			load >> tmp; //�ʿ� ���� ����.
			load >> mName;
		}
		load.close();
	}

	return 0; //GameManager�ʿ� ���� SCENE���� ��ȯ�ȴ�.
}

void Player::SavePlayerInfo(int mSceneNum, bool weaponSaveCheck)
{
	ofstream save;
	save.open("SavePlayerInfo.txt");

	if (save.is_open())
	{
		save << mPlayerGameOverCheck << endl;
		save << mName << endl;

		save << mSaveSeed << endl; //seed�� �÷��̾ ��� �־�� �Ѵ�.
		save << mSceneNum << endl << endl;

		save << mLevel << endl;

		save << mAttack << endl;
		save << mMax_HP << endl;
		save << mNow_HP << endl;

		save << mMax_EXP << endl;
		save << mNow_EXP << endl;

		save << mGetEXP << endl;
		save << mGold << endl;

		//if (mSceneNum > SCENE__PICKUPWEAPON) // bool ������ �Ǵ�
		if (weaponSaveCheck)
		{
			save << weapon->GetWeaponEnum() << endl; //DoubleSword�� enum�� �޾ƿ´�.
			save << weapon->GetName() << endl;
		}
		save.close();
	}
}

void Player::SaveGameOverPlayerInfo()
{
	//�÷��̾ ������ ���� �ʾҾ ������ ��������� �Ѵ�.
	//ĳ���� ���Ͽ� �̸��� ������
	mPlayerGameOverCheck = true;

	ofstream save;
	save.open("SavePlayerInfo.txt");
	save << mPlayerGameOverCheck << endl;
	save << mName;
	save.close();
}

int Player::LoadPlayerInfo()
{
	ifstream load;
	int _sceneCheck; // �ʱⰪ ���� - �ε尡 �ȵǾ��� ��� /
	int tmp_WeaponType;
	string tmp_WeaponName;
	WeaponShop weaponShop;

	load.open("SavePlayerInfo.txt");

	if (load.is_open())
	{
		load >> mPlayerGameOverCheck;
		load >> mName;

		load >> mSaveSeed;
		load >> _sceneCheck;

		load >> mLevel;

		load >> mAttack;
		load >> mMax_HP;
		load >> mNow_HP;

		load >> mMax_EXP;
		load >> mNow_EXP;

		load >> mGetEXP;
		load >> mGold;

		load >> tmp_WeaponType;
		load >> tmp_WeaponName;

		load.close();
	}

	weapon = weaponShop.Search_WeaponName((WEAPON)tmp_WeaponType, tmp_WeaponName);

	return _sceneCheck; //GameManager�ʿ� ���� SCENE���� ��ȯ�ȴ�.
}


void Player::PrintInfo(int _Y, int _X)
{
	MapDraw::BoxDraw(MAP_START, MAP_START, MAP_END_X, MAP_END_Y);
	Character::PrintInfo(_Y, _X); //�߿��

	// ���� ���� ���
	if (weapon != NULL) //NULL�� �Ǵ��Ѵٸ� �ʱ갪 NULL ���� �ʼ�
		weapon->SimpleInfo(_Y + GAP_4);
}

void Player::PrintMonsterBook(vector<Character*> monsterInfoList)//, string searchName)
{ //������ ���� ������ �и��ؼ� ���� //����	//��ü ���� �� ȭ�鿡 ���
  //����(�ڽ�) > ĳ����(�θ�)�� :: ��ĳ���� //ĳ���Ϳ� �ʿ��Ѱ� �־ ��ĳ���� ���. ���Ϳ� �־��ٸ� dynamic_cast<> ���� ���� �ٿ�ĳ����
	int i = 0, y = GAP_2;

	for (Character* character : monsterInfoList)
	{
		character->PrintMonsterBookInfo(MONSTER(i++), monsterBook.GetSituation(), y);
		y += GAP_4;
	}
}