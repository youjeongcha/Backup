#pragma once
#include "Character.h"
//#include "Goblin.h"
//#include "Oak.h"
//#include "Werewolves.h"

// ★ monsterBook을 monsterManager가 들고 있으면 복잡하게 player가 이것저것 받아올 필요가 없었을지도 모른다.
// 맨 마지막에 수정 고려

enum SITUATION
{//도감 기록용
	SITUATION_MEET,
	SITUATION_FIGHT,
	SITUATION_WIN,
	SITUATION_END
};

class MonsterBook
{
private:
	bool bSituation[SITUATION_END][MONSTER_COUNT];// = { 0, };
	//list<Character*> monsterBookList;//몬스터별 원본 데이터를 저장한다
public:
	MonsterBook();
	~MonsterBook();
	void ReadMonsterBook(); //"SaveMonsterBook.txt" 파일 읽어오기
	//bool* RecodeMonsterBook(SITUATION situation, MONSTER monster); //게임 진행시 얻는 정보 게임 내 bSituation에 기록
	void RecodeMonsterBook(SITUATION situation, MONSTER monster); //게임 진행시 얻는 정보 게임 내 bSituation에 기록
	void SaveMonsterBook(); //얻어둔 정보 도감에 기록
	//situation(1~3)과 enum을 통해 플레이어가 어떤 몬스터와 무엇을 하는지 상황 파악후 파일에 기록
	//1.조우시 알 수 있는 정보 
	//2.전투시 알 수 있는 정보 
	//3.승리시 알 수 있는 정보
	void ResetMonsterBook();

	bool (*GetSituation())[MONSTER_COUNT] { return bSituation; } //이차원 배열을 포인터를 이용해 넘겨주는 방식
	//list<Character*> Get_MonsterBookList() { return monsterBookList; }
};

