#pragma once
#include "MapDraw.h"
#include "Rank.h"
#include "Player.h"


//inline void test(std::vector<Ranking>) {};

enum MAPSIZE
{
	MAPSIZE_SART_X = 0,
	MAPSIZE_SART_Y = 2,
	MAPSIZE_END_X = 78,
	MAPSIZE_END_Y = 32
};
enum PLAYERINTERFACE
{
	PLAYERINTERFACE_Y = MAPSIZE_SART_Y - 1,

	PLAYERINTERFACE_X_LIFE = 2,
	PLAYERINTERFACE_X_SCORE = MAPSIZE_END_X / 2,
	PLAYERINTERFACE_X_NAME = MAPSIZE_END_X - 10
};
enum GAP
{
	GAP_4 = 4,
};
enum STARTMENU
{
	STARTMENU_START = 1,
	STARTMENU_RANK,
	STARTMENU_EXIT,

	STARTMENU_SELECT_X = MAPSIZE_END_X / 2 - 6,
};
enum STARTMENU_Y
{
	STARTMENU_Y_GAMENAME = MAPSIZE_SART_Y + 8,
	STARTMENU_Y_START = STARTMENU_Y_GAMENAME + GAP_4,
	STARTMENU_Y_RANK = STARTMENU_Y_START + GAP_4,
	STARTMENU_Y_EXIT = STARTMENU_Y_RANK + GAP_4,
};
//�Է� �ڽ�
enum INPUTBOX
{
	INPUTBOX_START_X = MAPSIZE_END_X,
	INPUTBOX_START_Y = MAPSIZE_END_Y - 8,
	INPUTBOX_WIDTH = 20,
	INPUTBOX_HEIGHT = 5,

	INPUTBOX_PRINT = INPUTBOX_START_Y + 2,

	INPUTBOX_PRINTNAME_MAXCOUNT = 10,
	INPUTBOX_PRINTWORD_MAXCOUNT = 20,

	INPUTBOX_SPACE = 32,
	INPUTBOX_BACKSPACE = 8,
	INPUTBOX_ENTER = 13,

	INPUTBOX_DELAY = 3000,
};
//��ŵ ��ư ������ ���丮 ���
enum STORYLINE
{
	STRORYLINE_MAX = 10, //�ִ� ��� ��

	STORYLINE_Y = MAPSIZE_SART_Y + 6,
};
//�÷��̾ �������� �ö󰡴� �� �׸�
enum STAGEPRINT
{
	//�������� ���� ��µǴ� ����
	STAGE_TEXTPRINT_Y = MAPSIZE_END_Y / 2, 

	//���丮 ���൵ �׸�(��� ǥ��) "��" ��� ���� X��
	STAGEPRINT_STAIRS_X = PLAYERINTERFACE_X_SCORE + 20,

	//���丮 ���൵ �׸�(�÷��̾�) "��" ��� ���� X��
	STAGEPRINT_PLAYER_ODD_X = STAGEPRINT_STAIRS_X + 4,
	STAGEPRINT_PLAYER_EVEN_X = STAGEPRINT_STAIRS_X + 4 + 12,

	STAGEPRINT_PLAYER_LEVEL1_Y = MAPSIZE_END_Y - 1,
	STAGEPRINT_PLAYER_LEVEL2_Y = MAPSIZE_END_Y - 4 - 1,
	STAGEPRINT_PLAYER_LEVEL3_Y = MAPSIZE_END_Y - 4 * 2 - 2,
	STAGEPRINT_PLAYER_LEVEL4_Y = MAPSIZE_END_Y - 4 * 3 - 2,
	STAGEPRINT_PLAYER_LEVEL5_Y = MAPSIZE_END_Y - 4 * 4 - 3,
	STAGEPRINT_PLAYER_LEVEL6_Y = MAPSIZE_END_Y - 4 * 5 - 3,

	//���丮 ���൵ �׸�(�÷��̾�) "��" ��� ���� Y��
};
enum PRINTDELAY
{
	PRINTDELAY = 1000,
	PRINTDELAY_PLAYER = 500,
};

enum STAGELEVEL
{
	STAGELEVEL_1 = 1,
	STAGELEVEL_2 = 2,
	STAGELEVEL_3 = 3,
	STAGELEVEL_4 = 4,
	STAGELEVEL_5 = 5,
	STAGELEVEL_6 = 6,
};

enum STAGESTROY
{
	STAGESTROY_LINECOUNT = 4,
	STAGESTROY_PRINTGAP_Y = 6,
};

enum GAMEOVERSTORY
{
	GAMEOVERSTORY_1_5 = 7,
	GAMEOVERSTORY_6 = 14,
	GAMEOVERSTORY_6_REALITY = 8, //6������ ���丮 8��° ��. ���丮 ������ 7���� �ش���
};

enum RANKINGPRINT_X
{
	RANKINGPRINT_X_NAME = 26,
	RANKINGPRINT_X_SCORE = 38,
	RANKINGPRINT_X_LEVEL = 51,
};

enum STORYTYPE
{
	STORYTYPE_INTRO,
	STORYTYPE_STAGELEVEL,
	STORYTYPE_GAMEOVER,
};

class Interface
{ //���� ȭ��ǥ ���� �͵� ���� Interface �Լ����� ó���ؼ� GameManager���� ȣ���ϰ� ���Ϲ޴� �͸�
private:
	//Ranking k;
public:
	//���ͷ� ���� ȭ�� �Ѿ��
	void EnterNext();
	//���� ���� ȭ��
	int StartInterface(const Player& player);
	//���� �� �׸���
	void MapInterface();
	//��ŵ�ڽ� �׸���
	void SkipBox();
	//void MapInterface(int playerLife);
	//�÷��̾� ���� �������̽� ���
	void PlayerInfoInterface(const Player& player);
	//��ŷ �������̽� ���
	void RankingInterface(const std::vector<Ranking>& rankingList, int maxRanking);
	//�ϴ� �Է� â �ڽ�(�̸� �Է� + ���� Word �Է�)
	//(while) ture�� �̻� ���� ��� ����. false�� input�� Word ��
	bool InputBox(INPUTBOX sMaxCount, std::string& sInput, int failed_OldClock);
	
	//���൵ ���
	void PrintStageStairs(STAGELEVEL stageLevel);
};