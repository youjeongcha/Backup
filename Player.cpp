#include "Player.h"
#include "MonsterManager.h"
#include "WeaponShop.h"

Player::Player()
{
	mEntityType = ENTITYTYPE_HUMANS;
	mMonsterType = MONSTER_NONE;
	weapon = NULL;  //NULL로 판단한다면 초깃값 NULL 설정 필수
}
Player::~Player()
{
}

int Player::Recover()
{
	int RecoveryHP = mMax_HP / 3;

	//HP가 오버힐 되지 않게
	mNow_HP = min(mMax_HP, mNow_HP + RecoveryHP);

	//MAX HP 회복 안되도록
	if (mNow_HP == mMax_HP)
		return 0;

	return RecoveryHP;
}

int Player::PlayeInitialSetting(bool newStart)
{ //플레이어 태초 상태로 초기화하는 함수(이름은 GameOver 여부 따라)
	bool tmp;
	//이름 설정 케이스 구별

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

	// ★ 다시 받아오는 것보다 bool 값으로 ContinueCheck == true 이런 식으로 변경(완)
	if (newStart)
		mName = "???";
	else
	{
		ifstream load;
		load.open("SavePlayerInfo.txt");

		if (load.is_open())
		{
			load >> tmp; //필요 없는 과정.
			load >> mName;
		}
		load.close();
	}

	return 0; //GameManager쪽에 가면 SCENE으로 변환된다.
}

void Player::SavePlayerInfo(int mSceneNum, bool weaponSaveCheck)
{
	ofstream save;
	save.open("SavePlayerInfo.txt");

	if (save.is_open())
	{
		save << mPlayerGameOverCheck << endl;
		save << mName << endl;

		save << mSaveSeed << endl; //seed값 플레이어가 들고 있어야 한다.
		save << mSceneNum << endl << endl;

		save << mLevel << endl;

		save << mAttack << endl;
		save << mMax_HP << endl;
		save << mNow_HP << endl;

		save << mMax_EXP << endl;
		save << mNow_EXP << endl;

		save << mGetEXP << endl;
		save << mGold << endl;

		//if (mSceneNum > SCENE__PICKUPWEAPON) // bool 값으로 판단
		if (weaponSaveCheck)
		{
			save << weapon->GetWeaponEnum() << endl; //DoubleSword의 enum을 받아온다.
			save << weapon->GetName() << endl;
		}
		save.close();
	}
}

void Player::SaveGameOverPlayerInfo()
{
	//플레이어가 저장을 하지 않았어도 죽으면 저장해줘야 한다.
	//캐릭터 파일에 이름만 덮어씌우기
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
	int _sceneCheck; // 초기값 세팅 - 로드가 안되었을 경우 /
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

	return _sceneCheck; //GameManager쪽에 가면 SCENE으로 변환된다.
}


void Player::PrintInfo(int _Y, int _X)
{
	MapDraw::BoxDraw(MAP_START, MAP_START, MAP_END_X, MAP_END_Y);
	Character::PrintInfo(_Y, _X); //중요★

	// 무기 정보 출력
	if (weapon != NULL) //NULL로 판단한다면 초깃값 NULL 설정 필수
		weapon->SimpleInfo(_Y + GAP_4);
}

void Player::PrintMonsterBook(vector<Character*> monsterInfoList)//, string searchName)
{ //전투와 도감 완전히 분리해서 관리 //도감	//전체 몬스터 한 화면에 출력
  //몬스터(자식) > 캐릭터(부모)로 :: 업캐스팅 //캐릭터에 필요한게 있어서 업캐스팅 사용. 몬스터에 있었다면 dynamic_cast<> 으로 강제 다운캐스팅
	int i = 0, y = GAP_2;

	for (Character* character : monsterInfoList)
	{
		character->PrintMonsterBookInfo(MONSTER(i++), monsterBook.GetSituation(), y);
		y += GAP_4;
	}
}