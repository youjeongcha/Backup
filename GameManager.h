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

// �� ���߿� �ϰ�����. Print �Լ����� ������ �ʿ� ���� ������ ���� ���ϴ� Print �Լ��� ��ü
// ��Ʈ���ʿ� �̸����ϰ� �������ϴ� �ʱ���. ���� ���� �κ�. ��

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
	MENUSELECT_EXIT //END�� ��Ī ���� ���
};

enum SCENE
{
	SCENE_INTRO,
	SCENE_PICKUPWEAPON,
	SCENE_NAME,//Name�� �ѹ� ���ϸ� ��. �ٽ� ���� �� ����.
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
	//���� �̾��ϱ� ������ ����
	bool mShowContinueMenu;

public:
	GameManager();
	~GameManager();
	void CallMainMenu();
private: //���ο��� ȣ���ϴ� �Լ� ����� ������ �� ������ ���ƾ� �Ѵ�. ĸ��ȭ
	bool MainMenu();
	//����
	void Help(); 

	//������ ���� + ����
	void NewGame();
	//�̾��ϱ� ���� +����
	void ContinueGame();
	void GameStart(SCENE mSceneCheck = SCENE_INTRO, MENUSELECT startType = MENUSELECT_NEW);
	//player ����,���� ���� + Load �ص� ���⼭�� ����
	void Menu();
	void Save();
	void Intro();
	void PickUpWeapon();
	void Name();
	void WeaponShop();
	void SpringOfRecovery();
	bool Monster();
	//���� ����
	void WinnerReward(WINCHECK whoWin, Character* winner, Character* loser);

	//���� ���� + ȭ�鿡 ��µǴ� �ؽ�Ʈ
	void SavePrint(string _string); 
	//���� �̾��ϱ� ������ ����
	void SaveContinueCheck();
};