#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <stdlib.h>
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
#define CHARACTER 7
#define EXIT 100 //출구
#define POTAL_MAX 9 //포탈 갯수
#define ENTRY_START 10
#define EXIT_START 20
#define OBSTACLE 1 //장애물
#define OBSTACLE_STACK 4
#define WEAPON 5
#define DOOR_START 50 //문
#define SWITCH_START 60 //스위치 
#define SWITCH_MAX 3 //스위치 갯수
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define WIDTH 20
#define HEIGHT 20
//10~13까지 입구 //20~23까지 출구 //30~33까지 장애물 //50~52까지 문 //60~62까지 스위치
//포탈은 오른쪽과, 장애물은 출구 방향 스위치
int map[HEIGHT][WIDTH] = {
  { 1,	7,	1,	1,	1,	1,	1,	1,	1,	1,  1,	1,	1,	1,	1,	1,	1,	1,	1,	1 },
  { 1,	0,	0,	0,	0,	1,	23,	0,	0,	0,  14,  1,	0,	50,	0,	0,	0,	0,	0,	1 },
  { 1,	1,	1,	1,	0,	1,	0,  1,	1,	1,  1,  1,	0,	1,	1,	1,	1,	1,	0,	1 },
  { 1,	0,	25,	1,	0,	1,	0,	5,	1,	0,  0,  0,	0,	1,	24,	0,	0,	1,	22,	1 },
  { 1,  16,	0,	1,	0,	1,	1,	1,	1,	0,  1,  0,	1,	1,	1,	1,	0,	1,	1,	1 },
  { 1,	1,	1,	1,	0,	0,	0,	0,	0,	0,  1,  1,	1,	0,	0,	0,	2,	0,	0,	1 },
  { 1,	0,	0,	0,	0,	1,	1,  1,	1,	0, 11,  1,	20,	0,	1,	1,	0,	1,	0,	1 },
  { 1,	0,	1,	1,	1,	1,	60,	0,	1,	0,  1,  1,	0,	0,	62,	1,	0,	1,	11,	1 },
  { 1,	0,	1,	0,	0,	0,	0, 21,	1,	0,  4,  0,	0,	1,	1,	1,	0,	1,	1,	1 },
  { 1,	3,	1,	12,	1,	1,	1,	0,	5,	1,  1,  1,	1,	1,	0,	0,	0,	0,	0,	1 },
  { 1,	0,	1,	1,	1,	0,	1,	1,	1,	1,  5,  1,	13,	1,	0,  1,	1,	1,	0,	1 },
  { 1,	0,	0,	0,	0,	0,	0,	0,	0,	0,  0,  1,	0,	1,	0,	1,	0,	1,	0,	1 },
  { 1,	1,	1,	1,  1,	0,	1,  1,	1,	0,  1,  1,	0,	1,	0,	0,	0,	1,	0,	1 },
  { 1,	0,	0,	0,	1,	0,	0,	1,	1,	0,  0,  0,	0,	1,	1,	1,	10,	1,	0,	1 },
  { 1,	0,	1,	5,	1,  1,  0,	27,	1,	1,  1,  0,	0,	0,	0,	1,	0,	1,	0,	1 },
  { 1,	52,  1,	0,	0,	1,	4,  1,	1,  0, 1,  1,	1,	1,	4,	1,	26,	1,	0,	1 },
  { 1,	0,	1,	1,	0,	1,	0,	0,	1,	0,  0,  0,	61,	0,	0,	1,	3,	1,	17,	1 },
  { 1,	0,	0,	1,	0,	0,	0, 28,	1,	18,  1,  1,	1,	1,	1,	1,	0,	1,	1,	1 },
  { 1,	0,	15,	1,	1,	0,	1,	0,	1,	0,  0,  3,	0,	0,	0,	0,	51,	0,	0,	100 },
  { 1,	1,	1,	1,	1,	1,	1,	1,	1,	1,  1,	1,	1,	1,	1,	1,	1,	1,	1,	1 } };
int character[2]; //x,y좌표 저장하기 위해
int Entry_Potal[POTAL_MAX][2]; //[포탈 개수를 이용][x,y 좌표]
int Exit_Potal[POTAL_MAX][2];
int Obstacle[OBSTACLE][2];
int Obstacle_stack = 3;
int Weapon_stack = 0;
int Door[SWITCH_MAX][2]; //문의 좌표
int Switch[SWITCH_MAX][2]; //스위치 좌표
int LastObjectIndex = NULL;
int start_end = 1; //반복문

void Init()
{ // 좌표 저장
	int Width = (WIDTH * 2) + 1; //*2는 특수문자는 두칸을 사용하기 때문
	int Height = HEIGHT + 4; //+1은 딱 맞게 띄우면 잘리기 때문
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
			{ // 10 >= (입장 포탈 번호 시작점) && map < 16 (입장 포탈의 번호 끝)
				Entry_Potal[map[y][x] - ENTRY_START][X] = x; // [10~16 - 10][x] 입장 포탈의 인덱스 번호와 x좌표
				Entry_Potal[map[y][x] - ENTRY_START][Y] = y;
			} //포털 이동할때 입출구 매치를 위해 인덱스 번호를 이용
			else if (map[y][x] >= EXIT_START && map[y][x] < EXIT_START + POTAL_MAX)
			{ // 20 >= (출구 포탈 번호 시작점) && map < 26 (출구 포탈의 번호 끝)
				Exit_Potal[map[y][x] - EXIT_START][X] = x; //[20~6 - 20][x] 출구 포탈의 인덱스 번호와 x좌표
				Exit_Potal[map[y][x] - EXIT_START][Y] = y;
			}
			else if (map[y][x] >= DOOR_START && map[y][x] < DOOR_START + SWITCH_MAX)
			{ // 50 >= (문 번호 시작점) && map < 53 (문 번호 끝)
				Door[map[y][x] - DOOR_START][X] = x; //[50~3 - 50][x] 출구 포탈의 인덱스 번호와 x좌표
				Door[map[y][x] - DOOR_START][Y] = y;
			}
			//이게 필요한가?
			else if (map[y][x] >= SWITCH_START && map[y][x] < SWITCH_START + SWITCH_MAX)
			{ // 60 >= (스위치 번호 시작점) && map < 63 (스위치 번호 끝)
				Switch[map[y][x] - SWITCH_START][X] = x; //[60~3 - 60][x] 출구 포탈의 인덱스 번호와 x좌표
				Switch[map[y][x] - SWITCH_START][Y] = y;
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
			{
				printf("▩");
			}
			else if (map[y][x] == EXIT)
			{
				printf("☞");
			}
			else if (map[y][x] == CHARACTER)
			{
				SKY_BLUE
					printf("◇");
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
			else if (map[y][x] == OBSTACLE_STACK) //4
			{ // 장애물 번호
				PUPPLE
					printf("▦");
				ORIGINAL
			}
			else if (map[y][x] == OBSTACLE_STACK - 1) //3
			{
				PUPPLE
					printf("▤");
				ORIGINAL
			}
			else if (map[y][x] == OBSTACLE_STACK - 2) //2
			{
				PUPPLE
					printf("□");
				ORIGINAL
			}
			else if (map[y][x] == WEAPON)
			{ // 40 무기 번호
				RED
					printf("メ");
				ORIGINAL
			}
			else if (map[y][x] >= DOOR_START && map[y][x] < DOOR_START + SWITCH_MAX)
			{ // 50 문 번호
				YELLOW
					printf("▒");
				ORIGINAL
			}
			else if (map[y][x] >= SWITCH_START && map[y][x] < SWITCH_START + SWITCH_MAX)
			{ // 60 스위치 번호
				GOLD
					printf("⊙");
				ORIGINAL
			}
			else if (map[y][x] == NULL)
				printf("  ");
		}
		printf("\n");
	}
	//아래에 프린트 하는 방법
	BLUE printf("입구 : ◎  ");
	YELLOW printf("출구 : ●\n");
	PUPPLE printf("장애물 : ▦▤□  ");
	RED printf("무기 : メ\n");
	YELLOW
	printf("문 : ▒   ");
	GOLD
	printf("스위치 : ⊙");
	ORIGINAL
	printf("\n무기 갯수 : %d", Weapon_stack);
}

void MoveCheck()
{
	int index = map[character[Y]][character[X]]; // 캐릭터가 있던 위치 == 포탈 입구
	if (index >= ENTRY_START && index < ENTRY_START + POTAL_MAX)
	{ // 포탈 입구 > 포탈 출구
	  // 입장 포탈 자리에 있으면(포탈의 인덱스 번호와 동일하면)
	  // ENTRY_START == 10 포탈 번호 -10 Exit_Potal[0~4][x,y 좌표 1,0에 저장]
		character[X] = Exit_Potal[index - ENTRY_START][X];
		character[Y] = Exit_Potal[index - ENTRY_START][Y];
	}

} 

int MoveObstacleCheck(int y, int x)
{ // 벽인지 장애물인지 구분. 이동 가능 불가능 구분 // ||인 이유는 내가 부딪히는 곳은 하나인데 그 하나는 or로 헤당.and면 내가 해당하는 모든곳에 부딪혀야 하기에 실행x
	if (map[y][x] == WALL)
	{ // 벽 이동 불가
		return FALSE;
	}
	else if (map[y][x] == OBSTACLE_STACK -2 || map[y][x] == OBSTACLE_STACK - 1 || map[y][x] == OBSTACLE_STACK)
	{ // 장애물 존재
		if (Weapon_stack > 0)
		{
			if (map[y][x] == OBSTACLE_STACK - 2)
			{ // 장애물 스택 2일때
				map[y][x] = NULL;
			}
			else
			{ // 장애물 스택 4,3일때
				map[y][x]--;
			}
			Weapon_stack--;
		}
		return FALSE;
	}
	else if (map[y][x] >= DOOR_START && map[y][x] < DOOR_START + SWITCH_MAX)
	{ // 문 이동 불가
		return FALSE;
	}
	else
	{ // 아무것도 없음 이동 가능
		return TRUE;
	}
}

void MoveElementCheck()
{
	if (map[character[Y]][character[X]] == WEAPON)
	{ //무기 먹기
		LastObjectIndex = 0;
		Weapon_stack += 2;
	}
	else if (map[character[Y]][character[X]] >= SWITCH_START && map[character[Y]][character[X]] < SWITCH_START + SWITCH_MAX)
	{ //스위치 누르기 > 스위치 사라짐 , 문 사라짐
		LastObjectIndex = 0; //스위치 사라짐
		int temp = map[character[Y]][character[X]] - SWITCH_START; //현재 스위치의 인덱스 번호
		map[Door[temp][Y]][Door[temp][X]] = 0; //문의 y와 x좌표를 알아내서. 현재 맵에서 문을 없앤다

	}
	else if (map[character[Y]][character[X]] == EXIT)
	{ //출구 //exit(1); 강제종료. 프로그램 흐름 고려 x 사용 x //메인을 종료시켜야 함
		start_end = 0;
	}
}

// 무기 스텍을 리턴 값으로 받을 수가 없어서
void Move()
{
	char ch;
	ch = getch();
	if (ch == -32)
	{
		ch = getch();
	}
	system("cls"); //창 초기화
	map[character[Y]][character[X]] = LastObjectIndex;
	// 처음엔 LastObjectIndex == 0 지나간 자리 초기화
	// 두번째 반복부터는 LastObjectIndex 캐릭터가 있었던 자리가 저장된다. 151줄
	switch (ch)
	{
	case LEFT:
		if (MoveObstacleCheck(character[Y],character[X] - 1) == TRUE)
		{
			character[X]--;
		}
		break;
	case RIGHT:
		if (MoveObstacleCheck(character[Y],character[X] + 1) == TRUE)
		{
			character[X]++;
		}
		break;
	case UP:
		if (MoveObstacleCheck(character[Y] - 1,character[X]) == TRUE)
		{
			character[Y]--;
		}
		break;
	case DOWN:
		if (MoveObstacleCheck(character[Y] + 1,character[X]) == TRUE)
		{
			character[Y]++;
		}
		break;
	}
	MoveCheck(); //입장 포털 > 출구 포털
	LastObjectIndex = map[character[Y]][character[X]]; // 캐릭터가 오기 전에 있던 요소 저장
	MoveElementCheck(); //무기, 스위치, 출구
	map[character[Y]][character[X]] = CHARACTER; // 현재 위치에 캐릭터 값 저장

}

void main()
{
	Init();
	while (start_end)
	{
		MapDraw();
 		Move();
	}
}