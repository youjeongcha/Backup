#include <stdio.h>
#include <stdlib.h> //rand srand 함수
#include <time.h>
#include <Windows.h> //system("cls")
#include <conio.h> //getch() //캐릭터 이동에 사용 //kibhit //키보드를 입력 했을 경우 참을 반환하는 함수

//--난이도 조절--
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
//----이동 관련-----
#define Y 0
#define X 1
#define LEFT 75
#define RIGHT 77
//--게임 시작--
#define WIDTH 10
#define HEIGHT 20
#define NULL 0
#define WALL 1
#define CHARACTER 2
#define STAR 3


void Menu()
{
	system("cls");
	printf("========별똥별 피하기========\n");
	printf("\t1.게임 시작\n");
	printf("\t2.난이도 조절\n");
	printf("\t3.종료\n");
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
{ //맵 그리기
	char level_check[5][10] = { "Easy", "Normal", "Hard", "Hell", "Return" };

	system("cls");
	printf("====%s====\n", level_check[level - 1]);

	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (map[y][x] == WALL)
			{
				printf("│");
			}
			else if (map[y][x] == CHARACTER)
			{
				printf("◇");
			}
			else if (map[y][x] == STAR)
			{
				printf("☆");
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
	if (kbhit()) //키보드를 입력 받으면
	{
		char ch = getch();
		//한번 더 입력 받아야 깜빡임 덜함 아니면 반복문 한번 더 돌아버림
		if (ch == -32)
		{ //주의
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
		MapDraw(map, score, level, mSpeed, gSpeed); //화면 상에 변화가 있을 때만 출력하도록 수정
	}
}

void MakeStar(int map[HEIGHT][WIDTH], int level)
{//level 따라 속도 차별성
	int maxStar = 0;
	for (int x = 1; x < WIDTH - 1; x++) //1~8
	{
		int makeStar = rand() % 100; //0~99

		if (maxStar > 2)
		{ //한줄에 최대 3개
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
{	//낮은 인덱스(위에서) 진행하다보니 연속된 별이 사라지는 것으로 보임
	//0과1에 별이 존재하면 1의 별이 사라지는 것처럼 보여서 역순으로.
	for (int x = WIDTH - 2; x >= 1; x--) //8~1
	{
		for (int y = HEIGHT - 1; y >= 0; y--) //19~0
		{
			if (map[y][x] == STAR)
			{ //이전에 별이 있었던 위치
				if (y != HEIGHT - 1)
				{
					map[y + 1][x] = STAR; //y가 19일때 20이 되므로
				}
				map[y][x] = NULL;
			}
		}
		if (map[HEIGHT - 1][x] == STAR)
		{ //socre 업데이트 
			score++;
		}
	}
	return score;
}

int GameOver(int map[HEIGHT][WIDTH], int start_end)
{
	for (int x = WIDTH - 2; x >= 1; x--) //8~1
	{//113번줄 해답코드 별이동과 병행해서 구분 가능 //별이 갈 곳에 캐릭터가 있는지
		if (map[HEIGHT - 1][x] == CHARACTER && map[HEIGHT - 2][x] == STAR)
		{ //게임 오버
			start_end = 1;
			return start_end;
		}
	}
	return;
}

int LevelMove(int level)
{	//레벨별로 별 이동 속도 세팅 조작
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
{	//레벨별로 별 생성 세팅 속도 조작
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
	int map[HEIGHT][WIDTH] = { //이중 배열을 함수에 전달하는 방법?
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

	Init(map, character); //상호작용 후 변화하는 요소
	MapDraw(map, score, level, mSpeed, gSpeed);
	while (!start_end)
	{
		Move(map, character, score, level, mSpeed, gSpeed);

		if (clock() - starMove >= mSpeed)
		{ //별이동
			start_end = GameOver(map, start_end);
			score = Update(map, score);
			starMove = clock();
			MapDraw(map, score, level, mSpeed, gSpeed); //화면 상에 변화가 있을 때만 출력하도록 수정
		}
		if (clock() - starGeneration >= gSpeed) // 이동 안에 넣어버리면 독자적 수저이 불가능해진다. 별도로 존재하는게 맞다
		{ //별생성
			MakeStar(map, level);
			starGeneration = clock();
			MapDraw(map, score, level, mSpeed, gSpeed); //화면 상에 변화가 있을 때만 출력하도록 수정
		}
		//점수에 따라 난이도 상승
		if (score >= levelUp)
		{ //목표점수 상승으로 조정
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
{	//이중 배열 취급해주어야 함 //글자 길이만큼 취급
	int input;
	char level_check[5][10] = { "Easy", "Normal", "Hard", "Hell", "Return" };
	while (1)
	{
		system("cls");
		printf("====%s====\n", level_check[level - 1]);
		printf("========난이도 조절========\n");
		printf("1. Easy\n");
		printf("2. Normal\n");
		printf("3. Hard\n");
		printf("4. Hell\n");
		printf("5. Return\n");
		printf("입력 : ");
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
		Menu(); //프린트와 값을 같이 받을수도 있음
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