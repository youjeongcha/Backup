#pragma once
#include "Character.h"
#include "Weapon.h"
#include "MonsterBook.h"
//Player는 절대 Static 선언 하지 말아야 함

//GameManager에 선언해서 사용할 수 없는, 필요한 enum만 추가적으로 선언

class Player : public Character //private? protected?
{ 
private:
	Weapon* weapon; //형식만 존재하고. 업캐스팅해서 쓰려면 반드시 포인터로 받아야함 //실체가 존재하려면 동적할당까지
	MonsterBook monsterBook;
	__int64 mSaveSeed; //long형으로 넣어도 된다. //seed값이 같으면 랜덤 돌려도 같은 결과가 나온다.
	bool mPlayerGameOverCheck;

public:
	Player();
	~Player();

	int Recover();
	
	//GameManager쪽에 가면 SCENE으로 변환된다.
	int PlayeInitialSetting(bool newStart = true); //플레이어 스텟 초기화하는 함수(이름 유지 GameOver 여부 따라 true와 false로)
	void SavePlayerInfo(int mSceneNum, bool weaponSaveCheck = false);
	void SaveGameOverPlayerInfo();
	//GameManager쪽에 가면 SCENE으로 변환된다.
	int LoadPlayerInfo();

	//virtual -  무기 정보 출력까지 추가해야 하므로. override 표시.
	//[ctrl] + [.] 누르면 .cpp에 바로 작성도 가능
	virtual void PrintInfo(int _Y = GAP_11, int _X = MAP_END_X / 2 - GAP_8) override; //★중요
	void PrintMonsterBook(vector<Character*> monsterInfoList); //도감의 모든 몬스터들 출력

	void SetName(string _Name) { mName = _Name; }
	void SetWeapon(Weapon* _weapon) { weapon = _weapon; }
	void SetSeed(__int64 _Seed) { mSaveSeed = _Seed; }
	//void SetPlayerGameOverCheck(bool _playerGameOverCheck) { mPlayerGameOverCheck = _playerGameOverCheck; }

	MonsterBook* GetMonsterBook() { return &monsterBook; } //monsterBook의 불값을 관리하기 위해서.
	Weapon* GetWeapon() { return weapon; }
	__int64 GetSeed() { return mSaveSeed; }
	bool GetPlayerGameOverCheck() { return mPlayerGameOverCheck; }
};