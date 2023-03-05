#include "MonsterManager.h"

MonsterManager::MonsterManager()
{
	// ★ vector로 처리 바람. 
	// ★ 이거 생성 여기서 할게 아니라 LOAD에서 모든 몬스터 정보를 가져오고 생성 바로.
	monsterInfoList.push_back(new Goblin);
	monsterInfoList.push_back(new Oak);
	monsterInfoList.push_back(new Werewolves);
	ReadMonsterStatus();//파일의 기본 몬스터 스테이더스 가져오기
}


MonsterManager::~MonsterManager()
{//동적할당 해제
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
	for (list<Character*>::iterator iter = monsterList.begin(); iter != monsterList.end();) // ★ vector로 변경
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
		{ // ★ 이것도 은닉화. 한번에 처리하는 함수로
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

// ★ 원본 몬스터 list 정보, 생성된 몬스터(살아있는) 불러오기 처리하는 함수
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

			if (_Name == "고블린")
				tmpMonster = new Goblin;
			else if (_Name == "오크")
				tmpMonster = new Oak;
			else if (_Name == "늑대인간")
				tmpMonster = new Werewolves;


			// ★ ifstream load;를 받아오는 구성 // ★ 한번에 처리

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

			// ★ 위에서 여기까지 수정

			monsterList.push_back(tmpMonster);
		}
		load.close();
	}
}

// ★ 이거 생성 여기서 할게 아니라 LOAD에서 모든 몬스터 정보를 가져오고 생성 바로.
// ★ 함수 삭제
//원본 몬스터 스테이더스 가져오기 : 새로 시작을 눌렀을 경우 원본 스테이터스를
void MonsterManager::ReadMonsterStatus() {
	ifstream load;
	int MonstersCount;
	string _Name; 
	int _Attack, _Max_HP, _Now_HP, _Level, _Max_EXP, _Now_EXP, _GetEXP, _Gold;

	//TODO :: 새로 시작을 눌렀을 경우 원본 스테이터스를. 다회차의 경우 이전 몬스터 파일 받아오도록 추후 수정 바람 
	load.open("SaveOriginalMonster.txt");
	if (!load.eof())
	{
		load >> MonstersCount;

		for (int i = 1; i <= MonstersCount; i++)
		{
			load >> _Name;
			for (Character* character : monsterInfoList)
			{//해당 이름의 list가 나오면 그곳에 스테이터스 저장
				if (character->Get_Name() == _Name)
				{
					// ★ 한번에 처리
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

	//tmpMonster = monsterInfoList[monster]; //이거는 monsterInfoList의 주소를 복사해와서. tmpMonster의 고유 주소값이 바뀌어버림(얕은 복사 사용X)
	/*
	for (list<Character*>::iterator iter = monsterInfoList.begin(); iter != monsterInfoList.end(); iter++)
	{//InfoList와 List 구분 잘하기
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