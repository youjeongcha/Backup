//Block들의 상호작용 관리
//Blcok에서 성질까지 부여하고 본격적으로 이용을 하는 게 Manager
#pragma once
#include "Block.h"
#include "Snake.h"

#define MAXOBSTACLE 60
#define MAXFOOD 10
#define ONEFOOD 1
#define FOODCLCOK 1500

enum SREACHLIST
{
	FOODLIST,
	OBSTACLELIST,
	SNAKELIST
};

class Manager
{
private:
	list<Block> obstacleList;
	list<Block> foodList;
public:
	void Menu();
	int MenuDraw();
	void GameStart();
	void PrintScore(int score);
	void GameOver(int score);

	void ObstacleBorder();
	void RandomCreate(BlockCheck block); //장애물, 먹이 랜덤 생성
	bool RepetitionCheck(Block block, list<Block> List); //중복 체크
	bool SnakeInteraction(SREACHLIST enList); //뱀 머리랑 좌표 겹칠 시 > 장애물.꼬리 : true 게임오버 / 먹이: ture 리스트 지움

	Manager();
	~Manager();
};