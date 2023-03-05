#include <stdio.h>
#include <stdlib.h> //rand srand �Լ�
#include <time.h>
#include <Windows.h> //system("cls")
#include <conio.h> //getch() //ĳ���� �̵��� ��� //kibhit //Ű���带 �Է� ���� ��� ���� ��ȯ�ϴ� �Լ�

//--���̵� ����--
#define EASY 1
#define NORMAL 2
#define HARD 3
#define HELL 4
#define RETURN 5
//---------------
#define MOVE1 1000 //1
#define GENERATION1 2000
#define MOVE2 900 //2
#define GENERATION2 1800
#define MOVE3 500 //3
#define GENERATION3 1000
#define MOVE4 300 //4
#define GENERATION4 550
//----�̵� ����-----
#define Y 0
#define X 1
#define LEFT 75
#define RIGHT 77
//--���� ����--
#define WIDTH 10
#define HEIGHT 20
#define NULL 0
#define WALL 1
#define CHARACTER 2
#define STAR 3


void Menu()
{
	system("cls");
	printf("========���˺� ���ϱ�========\n");
	printf("\t1.���� ����\n");
	printf("\t2.���̵� ����\n");
	printf("\t3.����\n");
}

//-----------------------------------------------------
void Init(int map[HEIGHT][WIDTH], int character[])
{
	/*
	int Width = (WIDTH * 2);
	int Height = HEIGHT + 4;
	char buf[256];
	sprintf(buf, "mode con: lines=%d cols=%d", Height, Width);
	system(buf);
	*/

	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (map[y][x] == CHARACTER)
			{
				character[X] = x;
				character[Y] = y;
			}
		}
	}
}

void MapDraw(int map[HEIGHT][WIDTH], int score, int level, double mSpeed, double gSpeed)
{ //�� �׸���
	char level_check[5][10] = { "Easy", "Normal", "Hard", "Hell", "Return" };

	system("cls");
	printf("====%s====\n", level_check[level - 1]);

	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (map[y][x] == WALL)
			{
				printf("��");
			}
			else if (map[y][x] == CHARACTER)
			{
				printf("��");
			}
			else if (map[y][x] == STAR)
			{
				printf("��");
			}
			else if (map[y][x] == NULL)
			{
				printf("  ");
			}
		}
		printf("\n");
	}
	printf("\nScore : %d", score);
	printf("\nmSpeed : %.0f", mSpeed);
	printf("\ngSpeed : %.0f", gSpeed);
}

void Move(int map[HEIGHT][WIDTH], int character[], int score, int level, double mSpeed, double gSpeed)
{
	if (kbhit()) //Ű���带 �Է� ������
	{
		char ch = getch();
		//�ѹ� �� �Է� �޾ƾ� ������ ���� �ƴϸ� �ݺ��� �ѹ� �� ���ƹ���
		if (ch == -32)
		{ //����
			ch = getch();
		}
		system("cls");
		map[character[Y]][character[X]] = NULL;
		switch (ch)
		{
		case LEFT:
			if (map[character[Y]][character[X] - 1] != WALL)
				character[X]--;
			break;
		case RIGHT:
			if (map[character[Y]][character[X] + 1] != WALL)
				character[X]++;
			break;
		}
		map[character[Y]][character[X]] = CHARACTER;
		MapDraw(map, score, level, mSpeed, gSpeed); //ȭ�� �� ��ȭ�� ���� ���� ����ϵ��� ����
	}
}

void MakeStar(int map[HEIGHT][WIDTH], int level)
{//level ���� �ӵ� ������
	int maxStar = 0;
	for (int x = 1; x < WIDTH - 1; x++) //1~8
	{
		int makeStar = rand() % 100; //0~99

		if (maxStar > 2)
		{ //���ٿ� �ִ� 3��
			break;
		}
		else
		{
			if (level == EASY && makeStar >= 95 && makeStar < 100)
			{//5
				map[0][x] = STAR;
				maxStar++;
			}
			else if (level == NORMAL && makeStar >= 80 && makeStar < 90)
			{//10
				map[0][x] = STAR;
				maxStar++;
			}
			else if (level == HARD && makeStar >= 40 && makeStar < 70)
			{//30
				map[0][x] = STAR;
				maxStar++;
			}
			else if (level == HELL && makeStar >= 0 && makeStar < 40)
			{//40
				map[0][x] = STAR;
				maxStar++;
			}
		}
	}
}

int Update(int map[HEIGHT][WIDTH], int score)
{	//���� �ε���(������) �����ϴٺ��� ���ӵ� ���� ������� ������ ����
	//0��1�� ���� �����ϸ� 1�� ���� ������� ��ó�� ������ ��������.
	for (int x = WIDTH - 2; x >= 1; x--) //8~1
	{
		for (int y = HEIGHT - 1; y >= 0; y--) //19~0
		{
			if (map[y][x] == STAR)
			{ //������ ���� �־��� ��ġ
				if (y != HEIGHT - 1)
				{
					map[y + 1][x] = STAR; //y�� 19�϶� 20�� �ǹǷ�
				}
				map[y][x] = NULL;
			}
		}
		if (map[HEIGHT - 1][x] == STAR)
		{ //socre ������Ʈ 
			score++;
		}
	}
	return score;
}

int GameOver(int map[HEIGHT][WIDTH], int start_end)
{
	for (int x = WIDTH - 2; x >= 1; x--) //8~1
	{//113���� �ش��ڵ� ���̵��� �����ؼ� ���� ���� //���� �� ���� ĳ���Ͱ� �ִ���
		if (map[HEIGHT - 1][x] == CHARACTER && map[HEIGHT - 2][x] == STAR)
		{ //���� ����
			start_end = 1;
			return start_end;
		}
	}
	return;
}

int LevelMove(int level)
{	//�������� �� �̵� �ӵ� ���� ����
	int mSetting = 0;
	switch (level)
	{
	case EASY:
		mSetting = MOVE1;
		break;
	case NORMAL:
		mSetting = MOVE2;
		break;
	case HARD:
		mSetting = MOVE3;
		break;
	case HELL:
		mSetting = MOVE4;
		break;
	}
	return mSetting;
}

int LevelGeneration(int level)
{	//�������� �� ���� ���� �ӵ� ����
	int gSetting = 0;
	switch (level)
	{
	case EASY:
		gSetting = GENERATION1;
		break;
	case NORMAL:
		gSetting = GENERATION2;
		break;
	case HARD:
		gSetting = GENERATION3;
		break;
	case HELL:
		gSetting = GENERATION4;
		break;
	}
	return gSetting;
}

void GameStart(int level)
{
	int map[HEIGHT][WIDTH] = { //���� �迭�� �Լ��� �����ϴ� ���?
	{ 1, 0,	0,	0,	0,	0,	0,	0,	0,	1 },
	{ 1, 0,	0,	0,	0,	0,	0,	0,	0,	1 },
	{ 1, 0,	0,	0,	0,	0,	0,	0,	0,	1 },
	{ 1, 0,	0,	0,	0,	0,	0,	0,	0,	1 },
	{ 1, 0,	0,	0,	0,	0,	0,	0,	0,	1 },
	{ 1, 0,	0,	0,	0,	0,	0,	0,	0,	1 },
	{ 1, 0,	0,	0,	0,	0,	0,	0,	0,	1 },
	{ 1, 0,	0,	0,	0,	0,	0,	0,	0,	1 },
	{ 1, 0,	0,	0,	0,	0,	0,	0,	0,	1 },
	{ 1, 0,	0,	0,	0,	0,	0,	0,	0,	1 },
	{ 1, 0,	0,	0,	0,	0,	0,	0,	0,	1 },
	{ 1, 0,	0,	0,	0,	0,	0,	0,	0,	1 },
	{ 1, 0,	0,	0,	0,	0,	0,	0,	0,	1 },
	{ 1, 0,	0,	0,	0,	0,	0,	0,	0,	1 },
	{ 1, 0,	0,	0,	0,	0,	0,	0,	0,	1 },
	{ 1, 0,	0,	0,	0,	0,	0,	0,	0,	1 },
	{ 1, 0,	0,	0,	0,	0,	0,	0,	0,	1 },
	{ 1, 0,	0,	0,	0,	0,	0,	0,	0,	1 },
	{ 1, 0,	0,	0,	0,	0,	0,	0,	0,	1 },
	{ 1, 0,	0,	0,	0,	2,	0,	0,	0,	1 } };
	int score = 0;
	int starMove = clock();
	int starGeneration = clock();
	int character[2];
	int start_end = 0;
	double mSpeed = LevelMove(level);
	double gSpeed = LevelGeneration(level);
	int levelUp = 20;
	srand(time(NULL));

	Init(map, character); //��ȣ�ۿ� �� ��ȭ�ϴ� ���
	MapDraw(map, score, level, mSpeed, gSpeed);
	while (!start_end)
	{
		Move(map, character, score, level, mSpeed, gSpeed);

		if (clock() - starMove >= mSpeed)
		{ //���̵�
			start_end = GameOver(map, start_end);
			score = Update(map, score);
			starMove = clock();
			MapDraw(map, score, level, mSpeed, gSpeed); //ȭ�� �� ��ȭ�� ���� ���� ����ϵ��� ����
		}
		if (clock() - starGeneration >= gSpeed) // �̵� �ȿ� �־������ ������ ������ �Ұ���������. ������ �����ϴ°� �´�
		{ //������
			MakeStar(map, level);
			starGeneration = clock();
			MapDraw(map, score, level, mSpeed, gSpeed); //ȭ�� �� ��ȭ�� ���� ���� ����ϵ��� ����
		}
		//������ ���� ���̵� ���
		if (score >= levelUp)
		{ //��ǥ���� ������� ����
			mSpeed -= 50;
			gSpeed -= 120;
			levelUp += 20;
		}
	}
	printf("  --GAME OVER--  ");
	system("pause");
}

//-----------------------------------------------------
int SettingRange(int level)
{	//���� �迭 ������־�� �� //���� ���̸�ŭ ���
	int input;
	char level_check[5][10] = { "Easy", "Normal", "Hard", "Hell", "Return" };
	while (1)
	{
		system("cls");
		printf("====%s====\n", level_check[level - 1]);
		printf("========���̵� ����========\n");
		printf("1. Easy\n");
		printf("2. Normal\n");
		printf("3. Hard\n");
		printf("4. Hell\n");
		printf("5. Return\n");
		printf("�Է� : ");
		scanf("%d", &input);

		if (input >= 1 && input < 5)
		{
			level = input;
		}
		else if (input == 5)
		{
			return level;
		}
	}
}

void main()
{
	int input;
	int level = EASY;

	while (1)
	{
		Menu(); //����Ʈ�� ���� ���� �������� ����
		scanf("%d", &input);
		system("cls");

		switch (input)
		{
		case 1:
			GameStart(level);
			break;
		case 2:
			level = SettingRange(level);
			break;
		case 3:
			return;
		}
	}
}