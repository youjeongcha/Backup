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
#define CHARACTER 2
#define POTAL_MAX 4 //포탈 갯수
#define ENTRY_START 10
#define EXIT_START 20
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define WIDTH 10
#define HEIGHT 10
int map[HEIGHT][WIDTH] = {
  { 1,	1,	1,	1,	1,	1,	1,	1,	1,	1 },
  { 1,	0,	0,	0,	0,	0,	0,	0,	0,	1 },
  { 1,	0,	10,	0,	12,	0,	0,	11,	0,	1 },
  { 1,	23,	0,	0,	0,	0,	0,	0,	0,	1 },
  { 1,	0,	0,	0,	0,	2,	0,	0,	0,	1 },
  { 1,	22,	0,	0,	0,	0,	0,	13,	0,	1 },
  { 1,	0,	0,	0,	0,	0,	0,	0,	0,	1 },
  { 1,	0,	21,	0,	0,	0,	0,	20,	0,	1 },
  { 1,	0,	0,	0,	0,	0,	0,	0,	0,	1 },
  { 1,	1,	1,	1,	1,	1,	1,	1,	1,	1 } };
int character[2]; //x,y좌표 저장하기 위해
int Entry_Potal[POTAL_MAX][2]; //[포탈 개수를 이용][x,y 좌표]
int Exit_Potal[POTAL_MAX][2];
int LastObjectIndex = NULL;
void Init()
{ // 좌표 저장
	int Width = (WIDTH * 2) + 1; //*2는 특수문자는 두칸을 사용하기 때문
	int Height = HEIGHT + 1; //+1은 딱 맞게 띄우면 잘리기 때문
	char buf[256];
	sprintf(buf, "mode con: lines=%d cols=%d", Height, Width);
	system(buf); // 창 조절하는 명령어
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (map[y][x] == CHARACTER)
			{ //캐릭터 위치 좌표
				character[X] = x;
				character[Y] = y;
			}
			else if (map[y][x] >= ENTRY_START && map[y][x] < ENTRY_START + POTAL_MAX)
			{ // 10 >= (입장 포탈 번호 시작점) && map < 14 (입장 포탈의 번호 끝)
				Entry_Potal[map[y][x] - ENTRY_START][X] = x; // -10 포탈의 인덱스 번호
				Entry_Potal[map[y][x] - ENTRY_START][Y] = y;
			}
			else if (map[y][x] >= EXIT_START && map[y][x] < EXIT_START + POTAL_MAX)
			{ // 20 >= (출구 포탈 번호 시작점) && map < 24 (출구 포탈의 번호 끝)
				Exit_Potal[map[y][x] - EXIT_START][X] = x; // -20 포탈의 인덱스 번호
				Exit_Potal[map[y][x] - EXIT_START][Y] = y;
			}
		}
	}
}
void MapDraw()
{ // 맵 그리기
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
			else if (map[y][x] >= ENTRY_START && map[y][x] < ENTRY_START + POTAL_MAX)
			{ // 10 >= (입장 포탈 번호 시작점) && map < 14 (입장 포탈의 번호 끝)
				BLUE
					printf("◎");
				ORIGINAL
			}
			else if (map[y][x] >= EXIT_START && map[y][x] < EXIT_START + POTAL_MAX)
			{ // 20 >= (출구 포탈 번호 시작점) && map < 24 (출구 포탈의 번호 끝)
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
{ // 포탈 입구 > 포탈 출구
	int index = map[character[Y]][character[X]]; // 캐릭터가 있던 위치 == 포탈 입구
	if (index >= ENTRY_START && index < ENTRY_START + POTAL_MAX)
	{ // 입장 포탈 자리에 있으면(포탈의 인덱스 번호와 동일하면)
	  // ENTRY_START == 10 포탈 번호 -10 Exit_Potal[0~4][x,y 좌표 1,0에 저장]
		character[X] = Exit_Potal[index - ENTRY_START][X];
		character[Y] = Exit_Potal[index - ENTRY_START][Y];
	}
}

void Move()
{
	char ch;
	ch = _getch();
	system("cls"); //창 초기화
	map[character[Y]][character[X]] = LastObjectIndex; 
	// 처음엔 LastObjectIndex == 0 지나간 자리 초기화
	// 두번째 반복부터는 LastObjectIndex 캐릭터가 있었던 자리가 저장된다. 151줄
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
	MoveCheck(); //입장 포털 > 출구 포털
	LastObjectIndex = map[character[Y]][character[X]]; // 바뀌기 전의 캐릭터 위치 저장
	map[character[Y]][character[X]] = CHARACTER; // 현재 캐릭터 위치 저장
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