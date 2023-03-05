#include<stdio.h>
#include<conio.h>
#include<Windows.h>
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
#define FLAG 2 // 문 스위치 온오프
#define ENTRY_MAX 18 //입구 갯수
#define EXIT_MAX 18 // 출구 갯수
#define CHARACTER 2
#define ENTRY_START 10
#define EXIT_START 30
#define DOOR_MAX 7 // 문 갯수
#define DOOR_START 60
#define SWITCH_MAX 7// 스위치 갯수
#define SWITCH_START 50
#define EXIT 99
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define WIDTH 20
#define HEIGHT 20
int map[HEIGHT][WIDTH] = {
	{ 1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1 },
	{ 1,	2,	1,	0,	0,	0,	1,	0,	0,	0,	1,	21,	62,	0,	0,	0,	0,	64,	23,	1 },
	{ 1,	0,	1,	12,	1,	0,	0,	0,	1,	0,	1,	1,	1,	0,	0,	0,	0,	1,	1,	1 },
	{ 1,	0,	1,	1,	1,	1,	1,	1,	1,	31,	1,	0,	0,	0,	44,	42,	0,	0,	0,	1 },
	{ 1,	0,	0,	11,	1,	10,	0,	0,	33,	0,	1,	0,	0,	0,	40,	38,	0,	0,	0,	1 },
	{ 1,	0,	1,	1,	1,	0,	1,	61,	1,	1,	1,	0,	0,	0,	0,	0,	0,	1,	0,	1 },
	{ 1,	0,	0,	30,	1,	0,	1,	0,	1,	46,	1,	0,	0,	0,	0,	0,	0,	1,	25,	1 },
	{ 1,	0,	1,	1,	1,	0,	1,	0,	1,	0,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1 },
	{ 1,	0,	0,	0,	0,	0,	1,	14,	1,	0,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1 },
	{ 1,	1,	1,	1,	1,	1,	1,	1,	1,	27,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1 },
	{ 1,	19,	0,	0,	0,	0,	0,	0,	1,	1,	1,	1,	1,	0,	47,	0,	0,	60,	0,	99 },
	{ 1,	1,	1,	1,	1,	0,	0,	0,	0,	45,	0,	34,	1,	1,	1,	1,	1,	1,	1,	1 },
	{ 1,	15,	0,	0,	0,	0,	0,	0,	1,	37,	1,	1,	1,	41,	0,	0,	63,	0,	54,	1 },
	{ 1,	1,	1,	1,	1,	1,	1,	1,	1,	0,	1,	24,	1,	1,	1,	1,	1,	1,	22,	1 },
	{ 1,	1,	1,	1,	1,	26,	50,	0,	66,	0,	1,	0,	1,	43,	1,	17,	0,	1,	1,	1 },
	{ 1,	0,	0,	51,	1,	1,	1,	1,	1,	55,	1,	56,	1,	0,	1,	1,	36,	1,	52,	1 },
	{ 1,	0,	0,	13,	1,	0,	0,	0,	1,	1,	1,	0,	65,	0,	1,	18,	0,	1,	0,	1 },
	{ 1,	0,	1,	1,	1,	0,	1,	0,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	35,	1 },
	{ 1,	0,	0,	0,	0,	0,	1,	32,	1,	39,	0,	0,	0,	53,	0,	0,	20,	1,	16,	1 },
	{ 1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1 } };
int character[2];
int Entry_Potal[ENTRY_MAX][2];
int Exit_Potal[EXIT_MAX][2];
int Exit[2];
int Door[DOOR_MAX][3];
int Switch[SWITCH_MAX][3];
int GameClear = 0;
void Init()
{
	int Width = (WIDTH * 2) + 1;
	int Height = HEIGHT + 2;
	char buf[256];
	sprintf(buf, "mode con: lines=%d cols=%d", Height, Width);
	system(buf);
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (map[y][x] == CHARACTER)
			{
				character[X] = x;
				character[Y] = y;
			}
			else if (map[y][x] >= ENTRY_START && map[y][x] <= ENTRY_MAX + ENTRY_START)
			{
				Entry_Potal[map[y][x] - ENTRY_START][X] = x;
				Entry_Potal[map[y][x] - ENTRY_START][Y] = y;
			}
			else if (map[y][x] >= EXIT_START && map[y][x] <= EXIT_MAX + EXIT_START)
			{
				Exit_Potal[map[y][x] - EXIT_START][X] = x;
				Exit_Potal[map[y][x] - EXIT_START][Y] = y;
			}
			else if (map[y][x] >= DOOR_START && map[y][x] <= DOOR_START + DOOR_MAX)
			{
				Door[map[y][x] - DOOR_START][X] = x;
				Door[map[y][x] - DOOR_START][Y] = y;
				Door[map[y][x] - DOOR_START][FLAG] = 1;
			}
			else if (map[y][x] >= SWITCH_START && map[y][x] <= SWITCH_START + SWITCH_MAX)
			{
				Switch[map[y][x] - SWITCH_START][Y] = y;
				Switch[map[y][x] - SWITCH_START][X] = x;
				Switch[map[y][x] - SWITCH_START][FLAG] = 1;
			}
			else if (map[y][x] == EXIT)
			{
				Exit[X] = x;
				Exit[Y] = y;
			}
		}
	}
}

int FindDoor(int x, int y)
{
	for (int i = 0; i < DOOR_MAX; i++)
	{
		if (Door[i][X] == x && Door[i][Y] == y && Door[i][FLAG])
			return i;
	}
	return -1;
}
int FindSwitch(int x, int y)
{
	for (int i = 0; i < SWITCH_MAX; i++)
	{
		if (Switch[i][X] == x && Switch[i][Y] == y && Switch[i][FLAG])
			return i;
	}
	return -1;
}
int FindEntryPotal(int x, int y)
{
	for (int i = 0; i < ENTRY_MAX; i++)
	{
		if (Entry_Potal[i][X] == x && Entry_Potal[i][Y] == y)
			return i;
	}
	return -1;
}
int FindExitPotal(int x, int y)
{
	for (int i = 0; i < EXIT_MAX; i++)
	{
		if (Exit_Potal[i][X] == x && Exit_Potal[i][Y] == y)
			return i;
	}
	return -1;
}

void MapDraw()
{
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (map[y][x] == WALL)
				printf("▩");
			else if (map[y][x] == CHARACTER)
			{
				RED
					printf("♠");
				ORIGINAL
			}
			else if (map[y][x] == EXIT)
				printf("☞");
			else if (FindEntryPotal(x, y) != -1)
			{
				BLUE
					printf("◎");
				ORIGINAL
			}
			else if (FindExitPotal(x, y) != -1)
			{
				YELLOW
					printf("●");
				ORIGINAL
			}
			else if (FindDoor(x, y) != -1)
			{
				GOLD
					printf("▒");
				ORIGINAL
			}
			else if (FindSwitch(x, y) != -1)
			{
				PUPPLE
					printf("⊙");
				ORIGINAL
			}
			else
				printf("  ");
		}
		printf("\n");
	}
	BLUE printf("입구 : ◎  ");
	YELLOW printf("출구 : ●\n");
	GOLD printf("문 : ▒  ");
	PUPPLE printf("스위치 : ⊙");
	ORIGINAL
}

void SwitchOnCheck()
{
	int index = FindSwitch(character[X], character[Y]);
	if (index != -1)
	{
		Switch[index][X] = -1;
		Switch[index][Y] = -1;
		Switch[index][FLAG] = 0;
		Door[index][X] = -1;
		Door[index][Y] = -1;
		Door[index][FLAG] = 0;
	}
}

void MoveCheck()
{
	int index = FindEntryPotal(character[X], character[Y]);
	if (index != -1)
	{
		character[X] = Exit_Potal[index][X];
		character[Y] = Exit_Potal[index][Y];
	}
}

void ExitCheck()
{
	if (map[character[Y]][character[X]] == EXIT)
		GameClear = 1;
}

void Move()
{
	char ch;
	ch = getch();
	system("cls");
	map[character[Y]][character[X]] = NULL;
	switch (ch)
	{
	case LEFT:
		if (map[character[Y]][character[X] - 1] != WALL && FindDoor(character[X] - 1, character[Y]) == -1)
			character[X]--;
		break;
	case RIGHT:
		if (map[character[Y]][character[X] + 1] != WALL && FindDoor(character[X] + 1, character[Y]) == -1)
			character[X]++;
		break;
	case UP:
		if (map[character[Y] - 1][character[X]] != WALL && FindDoor(character[X], character[Y] - 1) == -1)
			character[Y]--;
		break;
	case DOWN:
		if (map[character[Y] + 1][character[X]] != WALL && FindDoor(character[X], character[Y] + 1) == -1)
			character[Y]++;
		break;
	}
	MoveCheck();
	SwitchOnCheck();
	ExitCheck();
	map[character[Y]][character[X]] = CHARACTER;
}
void main()
{
	Init();
	while (!GameClear)
	{
		MapDraw();
		Move();
	}
	system("cls");
	printf("탈출성공!!");
}