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
#define WEPONCOUNT 2
#define WEPON 5
#define LIFE 2
#define WALL 1
#define NULL 0
#define Y 0
#define X 1
#define CHARACTER 2
#define POTAL_MAX 2//포탈 갯수
#define ENTRY_START 10
#define EXIT_START 20
#define BLEAK_WALL 3
#define BLEAK_WALL_MAX 4
#define WALL_LIFE_MAX 3
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define WIDTH 10
#define HEIGHT 10
int map[HEIGHT][WIDTH] = {
	{ 1,	1,	1,	1,	1,	1,	1,	1,	1,	1 },
	{ 1,	0,	0,	0,	3,	0,	0,	0,	0,	1 },
	{ 1,	0,	10,	0,	0,	5,	0,	11,	0,	1 },
	{ 1,	0,	0,	0,	3,	0,	0,	0,	0,	1 },
	{ 1,	0,	3,	0,	0,	2,	0,	5,	0,	1 },
	{ 1,	0,	0,	0,	0,	0,	0,	0,	0,	1 },
	{ 1,	0,	0,	0,	5,	0,	3,	0,	0,	1 },
	{ 1,	0,	21,	0,	0,	0,	0,	20,	0,	1 },
	{ 1,	0,	0,	0,	0,	0,	0,	0,	0,	1 },
	{ 1,	1,	1,	1,	1,	1,	1,	1,	1,	1 } };
int character[3];
int Entry_Potal[POTAL_MAX][2];
int Exit_Potal[POTAL_MAX][2];
int Break_Wall[BLEAK_WALL_MAX][3];

int Find_BreakWall(int x, int y) //부숴야 하는 벽 //i는 해당 요소 인덱스 번호
{
	for (int i = 0; i < BLEAK_WALL_MAX; i++)
	{
		if (Break_Wall[i][LIFE] != 0 && Break_Wall[i][Y] == y && Break_Wall[i][X] == x)
			return i;
	}
	return -1;
}

int Find_Entry(int x, int y)
{
	for (int i = 0; i < POTAL_MAX; i++)
	{
		if (Entry_Potal[i][Y] == y && Entry_Potal[i][X] == x)
			return i;
	}
	return -1;
}
int Find_Exit(int x, int y)
{
	for (int i = 0; i < POTAL_MAX; i++)
	{
		if (Exit_Potal[i][Y] == y && Exit_Potal[i][X] == x)
			return i;
	}
	return -1;
}
void Init()
{
	int BleakWallCount = 0;
	int Width = (WIDTH * 2) + 1;
	int Height = HEIGHT + 1;
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
				character[WEPONCOUNT] = 0;
			}
			else if (map[y][x] >= ENTRY_START && map[y][x] < ENTRY_START + POTAL_MAX)
			{
				Entry_Potal[map[y][x] - ENTRY_START][X] = x;
				Entry_Potal[map[y][x] - ENTRY_START][Y] = y;
			}
			else if (map[y][x] >= EXIT_START && map[y][x] < EXIT_START + POTAL_MAX)
			{
				Exit_Potal[map[y][x] - EXIT_START][X] = x;
				Exit_Potal[map[y][x] - EXIT_START][Y] = y;
			}
			else if (map[y][x] == BLEAK_WALL)
			{
				Break_Wall[BleakWallCount][X] = x;
				Break_Wall[BleakWallCount][Y] = y;
				Break_Wall[BleakWallCount][LIFE] = WALL_LIFE_MAX;
				BleakWallCount++;
			}
		}
	}
}
void MapDraw()
{
	int index;
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			index = Find_BreakWall(x, y);
			if (map[y][x] == WALL)
				printf("▩");
			else if (map[y][x] == CHARACTER)
			{
				RED
					printf("♧");
				ORIGINAL
			}
			else if (map[y][x] == WEPON)
			{
				RED
					printf("メ");
				ORIGINAL
			}
			else if (Find_Entry(x, y) != -1) //포탈 위에 있는 경우
			{
				BLUE
					printf("◎");
				ORIGINAL
			}
			else if (Find_Exit(x, y) != -1)
			{
				YELLOW
					printf("●");
				ORIGINAL
			}
			else if (index != -1) //이런 방식도 있다는것 유의
			{
				PUPPLE
					switch (Break_Wall[index][LIFE])
					{
					case 3:
						printf("▦");
						break;
					case 2:
						printf("▤");
						break;
					case 1:
						printf("□");
						break;
					}
				ORIGINAL
			}
			else if (map[y][x] == NULL)
				printf("  ");
		}
		printf("\n");
	}
	printf("무기 갯수 : %d", character[WEPONCOUNT]);
}

void MoveCheck()
{
	int index = Find_Entry(character[X], character[Y]);
	if (index != -1) //캐릭터가 포탈 위에 있는 경우
	{//입구>출구
		character[X] = Exit_Potal[index][X];
		character[Y] = Exit_Potal[index][Y];
	}
	if (map[character[Y]][character[X]] == WEPON)
		character[WEPONCOUNT] += 2;
}

int BreakWall(int x, int y)
{
	int index = Find_BreakWall(x, y);
	if (index != -1)
	{
		if (character[WEPONCOUNT] != 0)
		{//무기 있는 경우에는 스텍 하나 감소
			Break_Wall[index][LIFE]--;
			if (Break_Wall[index][LIFE] == 0) // 스텍 다 닳은 경우 사라지는 것
				map[Break_Wall[index][Y]][Break_Wall[index][X]] = NULL;
			character[WEPONCOUNT]--;
		}
	}
	return index;
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
		if (map[character[Y]][character[X] - 1] != WALL)
		{
			if (BreakWall(character[X] - 1, character[Y]) == -1) //-1이라는 건 존재 X //아무것도 없을때
				character[X]--;
		}
		break;
	case RIGHT:
		if (map[character[Y]][character[X] + 1] != WALL)
		{
			if (BreakWall(character[X] + 1, character[Y]) == -1)
				character[X]++;
		}
		break;
	case UP:
		if (map[character[Y] - 1][character[X]] != WALL)
		{
			if (BreakWall(character[X], character[Y] - 1) == -1)
				character[Y]--;
		}
		break;
	case DOWN:
		if (map[character[Y] + 1][character[X]] != WALL)
		{
			if (BreakWall(character[X], character[Y] + 1) == -1)
				character[Y]++;
		}
		break;
	}
	MoveCheck();
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