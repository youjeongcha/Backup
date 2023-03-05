#pragma once
#include "Interface.h"
#include "Player.h"
#include "WordManager.h"
#include "Rank.h"
#include <map>

//★ 자동화, 외부에서 받아와서 처리해야 하는 값들에 주의

//스테이지 클리어 점수 //word 한자당 3점 취급
enum CLEARSTAGE
{
	CLEARSTAGE_1 = 300,
	CLEARSTAGE_2 = 350,
	CLEARSTAGE_3 = 400,
	CLEARSTAGE_4 = 450,
	CLEARSTAGE_5 = 500,
	////CLEARSTAGE_6 = 10, //6스테이지는 마법사가 나옴. 랭킹 대결 가능하게 클리어 한계 두지 x
	
	//CLEARSTAGE_1 = 5,
	//CLEARSTAGE_2 = 4,
	//CLEARSTAGE_3 = 5,
	//CLEARSTAGE_4 = 6,
	//CLEARSTAGE_5 = 7,
	////CLEARSTAGE_6 = 80,
};

struct STAGESETTING
{
	int createSpeed;
	int dropSpeed;
	int clearStage;
};

class GameManager final//sealed
{
private:
	Player player;
	Interface UI; //★ ui로 명칭 바꾸기
	WordManager wordManager;
	Rank rank;
	STAGESETTING mStageSetting[STAGELEVEL_6];
	int mStoryLineCount;
	std::map<STORYTYPE, std::vector<std::string>> storyList; //★ into,stage, gameOver를 enum으로 판단해서. 백터 배열로 호출해서 사용 
	
	//---------------
	void GameStart();
	void PrintStory(int printLineCount, int oldClock); //루프문은 돌때마다 메모리가 쌓여서 큰 범위를 돌릴 경우 오버플로우가 터지기도 한다. //범위가 넓지만 느려도 되면 재귀. 범위 좁고 빨라야 하면 루프
	void PrintStageStory(int level);
	//게임 오버가 되면 false 리턴
	bool Stage(int level);
	//스토리 줄 수를 리턴받는다
	int LoadStory();
	//스테이지별 단어 생성 속도, 단어 드롭 속도, 클리어 점수 배열에 받아두기
	void StageSettingList();

public:
	GameManager();
	~GameManager();
	void Menu();
};

