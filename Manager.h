//Block���� ��ȣ�ۿ� ����
//Blcok���� �������� �ο��ϰ� ���������� �̿��� �ϴ� �� Manager
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
	void RandomCreate(BlockCheck block); //��ֹ�, ���� ���� ����
	bool RepetitionCheck(Block block, list<Block> List); //�ߺ� üũ
	bool SnakeInteraction(SREACHLIST enList); //�� �Ӹ��� ��ǥ ��ĥ �� > ��ֹ�.���� : true ���ӿ��� / ����: ture ����Ʈ ����

	Manager();
	~Manager();
};