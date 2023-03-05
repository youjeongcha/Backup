#pragma once
#include "Interface.h"
#include "Player.h"
#include "WordManager.h"
#include "Rank.h"
#include <map>

//�� �ڵ�ȭ, �ܺο��� �޾ƿͼ� ó���ؾ� �ϴ� ���鿡 ����

//�������� Ŭ���� ���� //word ���ڴ� 3�� ���
enum CLEARSTAGE
{
	CLEARSTAGE_1 = 300,
	CLEARSTAGE_2 = 350,
	CLEARSTAGE_3 = 400,
	CLEARSTAGE_4 = 450,
	CLEARSTAGE_5 = 500,
	////CLEARSTAGE_6 = 10, //6���������� �����簡 ����. ��ŷ ��� �����ϰ� Ŭ���� �Ѱ� ���� x
	
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
	Interface UI; //�� ui�� ��Ī �ٲٱ�
	WordManager wordManager;
	Rank rank;
	STAGESETTING mStageSetting[STAGELEVEL_6];
	int mStoryLineCount;
	std::map<STORYTYPE, std::vector<std::string>> storyList; //�� into,stage, gameOver�� enum���� �Ǵ��ؼ�. ���� �迭�� ȣ���ؼ� ��� 
	
	//---------------
	void GameStart();
	void PrintStory(int printLineCount, int oldClock); //�������� �������� �޸𸮰� �׿��� ū ������ ���� ��� �����÷ο찡 �����⵵ �Ѵ�. //������ ������ ������ �Ǹ� ���. ���� ���� ����� �ϸ� ����
	void PrintStageStory(int level);
	//���� ������ �Ǹ� false ����
	bool Stage(int level);
	//���丮 �� ���� ���Ϲ޴´�
	int LoadStory();
	//���������� �ܾ� ���� �ӵ�, �ܾ� ��� �ӵ�, Ŭ���� ���� �迭�� �޾Ƶα�
	void StageSettingList();

public:
	GameManager();
	~GameManager();
	void Menu();
};

