#include "MonsterBook.h"

MonsterBook::MonsterBook()
{
	//이차원배열 초기화
	//메모리 주소 이름, 저장할 값, 인자 종류 * 행 * 렬
	ZeroMemory(bSituation, sizeof(bool) * SITUATION_END * MONSTER_COUNT);
}
MonsterBook::~MonsterBook()
{
}

void MonsterBook::ReadMonsterBook()
{//"SaveMonsterBook.txt" 파일 읽어오기
	ifstream load;

	load.open("SaveMonsterBook.txt");

	if (load.is_open())
	{
		for (int i = 0; i < MONSTER_COUNT; i++) // ★ 파일에 해당만큼의 인자가 존재하지 않는 경우 쓰레기 값이 들어갈 수 있다. 그래서 어떻게? 
		{
			//몬스터 조우 시 알 수 있는 정보
			load >> bSituation[SITUATION_MEET][i];
			//전투 시 알 수 있는 정보
			load >> bSituation[SITUATION_FIGHT][i];
			//승리 시 알 수 있는 정보
			load >> bSituation[SITUATION_WIN][i];
		}
		load.close();
	}
}

//MonsterManager의 원본 MonsterList이용. enum을 통해 플레이어가 처한 현재 상황 파악
//Character MonsterInfo는 MonsterManager에서 넘어온 몬스터 정보, 스테이터스를 "SaveMonsterBook.txt"에 덮어쓰기.
//덮어쓰기 되니까 전부 buff에 받아뒀다가
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

	//load.seekg(0, ios::end); //seekg 파일 안에 있는 데이터를 들고 올 때. 메모장도 커서를 이용 //메모장의 커서를 옮겨주려는 목적 //오프셋이라는 타입값. 속성값 보통 0을 넣는다. end는 way값 커서 위치를 의미한다. 메모장 끝부분으로 이동.
	//int size = load.tellg(); //tellg 현재 메모장에 있는 커서의 위치 앞에 있는 글자수를 가져온다.
	//load.read(&buff[0], size); //read는 내가 원언하는 글자수만큼을 파일에서 바로 들고온다. c언어의 전체 복사 fread와 동일
	//load.seekg(0, ios::beg); //seekg 파일 안에 있는 데이터를 들고 올 때. 메모장도 커서를 이용 //메모장의 커서를 옮겨주려는 목적 //beg 다시 커서를 맨처음으로 돌린다.

	/*
	//고블린 0,2,4 //오크 6,8,10 //웨어울프 12, 14, 16
	if (load.is_open())
	{
		//getline(load, buff); //개행 단위로 가져오는 코드

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
		//몬스터 조우 시 알 수 있는 정보
		save << bSituation[SITUATION_MEET][i] << " ";
		//전투 시 알 수 있는 정보
		save << bSituation[SITUATION_FIGHT][i] << " ";
		//승리 시 알 수 있는 정보
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