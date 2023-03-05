#pragma once
#include "Mecro.h"
#include "MapDraw.h"
#include "Player.h"
#include "MonsterManager.h"
#include "WeaponShop.h"
#include "Battle.h"
#include "Interface.h"
//#include <time.h>

//#define MAINMENUPRINT_LOBBYSELECT 4

// ★ 나중에 하겠지만. Print 함수에서 저장할 필요 없는 구문은 저장 못하는 Print 함수로 대체
// 인트로쪽에 이름정하고 무기정하는 쪽까지. 보상 수여 부분. 등

struct PrintXY
{
	//int Print_X;
	int Print_Y;
};

enum MENUSELECT
{
	MENUSELECT_NEW = 1,
	MENUSELECT_CONTINUE,
	MENUSELECT_HELP,
	MENUSELECT_EXIT //END로 명칭 변경 고려
};

enum SCENE
{
	SCENE_INTRO,
	SCENE_PICKUPWEAPON,
	SCENE_NAME,//Name은 한번 정하면 끝. 다시 정할 일 없다.
	SCENE_WEAPONSHOP,
	SCENE_SPRINGOFRECOVERY,
	SCENE_MONSTER,
};




class GameManager
{
private:
	Player player;
	MonsterManager monsterManager;
	WeaponShop weaponShop;
	Battle* battle;

	SCENE mSceneCheck;
	//게임 이어하기 선택지 개방
	bool mShowContinueMenu;

public:
	GameManager();
	~GameManager();
	void CallMainMenu();
private: //메인에서 호출하는 함수 말고는 접근할 수 없도록 막아야 한다. 캡슐화
	bool MainMenu();
	//도움말
	void Help(); 

	//새게임 세팅 + 시작
	void NewGame();
	//이어하기 세팅 +시작
	void ContinueGame();
	void GameStart(SCENE mSceneCheck = SCENE_INTRO, MENUSELECT startType = MENUSELECT_NEW);
	//player 정보,몬스터 도감 + Load 해도 여기서에 시작
	void Menu();
	void Save();
	void Intro();
	void PickUpWeapon();
	void Name();
	void WeaponShop();
	void SpringOfRecovery();
	bool Monster();
	//승자 보상
	void WinnerReward(WINCHECK whoWin, Character* winner, Character* loser);

	//저장 가능 + 화면에 출력되는 텍스트
	void SavePrint(string _string); 
	//게임 이어하기 선택지 개방
	void SaveContinueCheck();
};