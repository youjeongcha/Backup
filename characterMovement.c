#include<stdio.h>
#include<conio.h>	//getch()에 사용 읽은 문자 하나를 반환(입력받음)
#include<Windows.h> //system("cls"); //화면 전체 지워주는 //색상 지정
//////////////////////////////////////////////////////
#define col GetStdHandle(STD_OUTPUT_HANDLE) 
#define BLACK SetConsoleTextAttribute( col,0x0000 );
#define DARK_BLUE SetConsoleTextAttribute( col,0x0001 );
#define GREEN SetConsoleTextAttribute( col,0x0002 );
#define BLUE_GREEN SetConsoleTextAttribute( col,0x0003 );
#define BLOOD SetConsoleTextAttribute( col,0x0004 );
#define PUPPLE SetConsoleTextAttribute( col,0x0005 );
#define GOLD SetConsoleTextAttribute( col,0x0006 );			//색상 지정
#define ORIGINAL SetConsoleTextAttribute( col,0x0007 );
#define GRAY SetConsoleTextAttribute( col,0x0008 );
#define BLUE SetConsoleTextAttribute( col,0x0009 );
#define HIGH_GREEN SetConsoleTextAttribute( col,0x000a );
#define SKY_BLUE SetConsoleTextAttribute( col,0x000b );
#define RED SetConsoleTextAttribute( col,0x000c );
#define PLUM SetConsoleTextAttribute( col,0x000d );
#define YELLOW SetConsoleTextAttribute( col,0x000e );
//////////////////////////////////////////////////////
#define WALL 1
#define NULL 0
#define Y 0
#define X 1
#define CHARACTER 2
#define ENTRY_POTAL 10
#define EXIT_POTAL 20
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define WIDTH 10
#define HEIGHT 10
int map[HEIGHT][WIDTH] = {
	{ 1,	1,	1,	1,	1,	1,	1,	1,	1,	1 },
	{ 1,	0,	0,	0,	0,	0,	0,	0,	0,	1 },
	{ 1,	0,	0,	0,	0,	0,	0,	0,	0,	1 },
	{ 1,	0,	0,	0,	0,	0,	0,	0,	0,	1 },
	{ 1,	0,	0,	0,	0,	0,	0,	0,	0,	1 },
	{ 1,	0,	0,	0,	0,	0,	0,	0,	0,	1 },
	{ 1,	0,	2,	0,	0,	0,	0,	0,	0,	1 },
	{ 1,	0,	10,	0,	0,	0,	0,	20,	0,	1 },
	{ 1,	0,	0,	0,	0,	0,	0,	0,	0,	1 },
	{ 1,	1,	1,	1,	1,	1,	1,	1,	1,	1 } };
int character[2];
int Entry_Potal[2];
int Exit_Potal[2];
int LastObjectIndex = NULL;
void Init()
{
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (map[y][x] == CHARACTER)
			{
				character[X] = x;
				character[Y] = y;
			}
			else if (map[y][x] == ENTRY_POTAL)
			{
				Entry_Potal[X] = x;
				Entry_Potal[Y] = y;
			}
			else if (map[y][x] == EXIT_POTAL)
			{
				Exit_Potal[X] = x;
				Exit_Potal[Y] = y;
			}
		}
	}
}
void MapDraw()
{
	system("cls"); //콘솔 화면 전체 지워주
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (map[y][x] == WALL)
				printf("▩");
			else if (map[y][x] == CHARACTER)
			{
				RED
					printf("♧");
				ORIGINAL
			}
			else if (map[y][x] == ENTRY_POTAL)
			{
				BLUE
					printf("◎");
				ORIGINAL
			}
			else if (map[y][x] == EXIT_POTAL)
			{
				YELLOW
					printf("●");
				ORIGINAL
			}
			else if (map[y][x] == NULL)
				printf("  ");
		}
		printf("\n");
	}
}

void MoveCheck()
{
	if (map[character[Y]][character[X]] == ENTRY_POTAL)
	{
		character[X] = Exit_Potal[X];
		character[Y] = Exit_Potal[Y];
	}
}

void Move()
{
	char ch;
	ch = _getch();
	if (ch == -32) //특수키, 방향키, f1 같은 키는 키값을 2개를 들고 온다. 그래서 getch()를 두번 받는 것
				   //getch 첫번째 어떤 키를 눌렀는지가 들어온다.(방향키) -32가 방향키인지 알 수 있는 것
				   //getch 두번째는 어떤 방향키인지.
		ch = _getch();
	map[character[Y]][character[X]] = LastObjectIndex; //지나간 자리에 null을 대신 넣어버리면 출구나 입구 가 지나간 후에 사라진다. 0이 되기 때문
													   //지나간 자리가 0이 안 되도록. 지나가기 전에 맵 값을 저장 해두고. 지나간 후에 다시 가져와서 복원
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
	case UP:
		if (map[character[Y] - 1][character[X]] != WALL)
			character[Y]--;
		break;
	case DOWN:
		if (map[character[Y] + 1][character[X]] != WALL)
			character[Y]++;
		break;
	}

	MoveCheck();
	LastObjectIndex = map[character[Y]][character[X]];
	map[character[Y]][character[X]] = CHARACTER;
}
void main()
{
	Init();
	while (1)
	{
		MapDraw();
		Move();
	}
}