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
//입력 박스
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
//스킵 버튼 적용한 스토리 출력
enum STORYLINE
{
	STRORYLINE_MAX = 10, //최대 출력 줄

	STORYLINE_Y = MAPSIZE_SART_Y + 6,
};
//플레이어가 스테이지 올라가는 거 그림
enum STAGEPRINT
{
	//스테이지 따라 출력되는 문구
	STAGE_TEXTPRINT_Y = MAPSIZE_END_Y / 2, 

	//스토리 진행도 그림(계단 표시) "─" 출력 시작 X축
	STAGEPRINT_STAIRS_X = PLAYERINTERFACE_X_SCORE + 20,

	//스토리 진행도 그림(플레이어) "●" 출력 시작 X축
	STAGEPRINT_PLAYER_ODD_X = STAGEPRINT_STAIRS_X + 4,
	STAGEPRINT_PLAYER_EVEN_X = STAGEPRINT_STAIRS_X + 4 + 12,

	STAGEPRINT_PLAYER_LEVEL1_Y = MAPSIZE_END_Y - 1,
	STAGEPRINT_PLAYER_LEVEL2_Y = MAPSIZE_END_Y - 4 - 1,
	STAGEPRINT_PLAYER_LEVEL3_Y = MAPSIZE_END_Y - 4 * 2 - 2,
	STAGEPRINT_PLAYER_LEVEL4_Y = MAPSIZE_END_Y - 4 * 3 - 2,
	STAGEPRINT_PLAYER_LEVEL5_Y = MAPSIZE_END_Y - 4 * 4 - 3,
	STAGEPRINT_PLAYER_LEVEL6_Y = MAPSIZE_END_Y - 4 * 5 - 3,

	//스토리 진행도 그림(플레이어) "●" 출력 시작 Y축
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
	GAMEOVERSTORY_6_REALITY = 8, //6스테이 스토리 8번째 줄. 스토리 마지막 7줄이 해당함
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
{ //선택 화살표 같은 것들 전부 Interface 함수에서 처리해서 GameManager에는 호출하고 리턴받는 것만
private:
	//Ranking k;
public:
	//엔터로 다음 화면 넘어가기
	void EnterNext();
	//게임 시작 화면
	int StartInterface(const Player& player);
	//게임 맵 그리기
	void MapInterface();
	//스킵박스 그리기
	void SkipBox();
	//void MapInterface(int playerLife);
	//플레이어 정보 인터페이스 출력
	void PlayerInfoInterface(const Player& player);
	//랭킹 인터페이스 출력
	void RankingInterface(const std::vector<Ranking>& rankingList, int maxRanking);
	//하단 입력 창 박스(이름 입력 + 게임 Word 입력)
	//(while) ture면 이상 없이 계속 진행. false면 input과 Word 비교
	bool InputBox(INPUTBOX sMaxCount, std::string& sInput, int failed_OldClock);
	
	//진행도 출력
	void PrintStageStairs(STAGELEVEL stageLevel);
};