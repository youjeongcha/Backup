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
#define GOLD SetConsoleTextAttribute( col,0x0006 );			//���� ����
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
#define EXIT 100 //�ⱸ
#define POTAL_MAX 9 //��Ż ����
#define ENTRY_START 10
#define EXIT_START 20
#define OBSTACLE 1 //��ֹ�
#define OBSTACLE_STACK 4
#define WEAPON 5
#define DOOR_START 50 //��
#define SWITCH_START 60 //����ġ 
#define SWITCH_MAX 3 //����ġ ����
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define WIDTH 20
#define HEIGHT 20
//10~13���� �Ա� //20~23���� �ⱸ //30~33���� ��ֹ� //50~52���� �� //60~62���� ����ġ
//��Ż�� �����ʰ�, ��ֹ��� �ⱸ ���� ����ġ
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
int character[2]; //x,y��ǥ �����ϱ� ����
int Entry_Potal[POTAL_MAX][2]; //[��Ż ������ �̿�][x,y ��ǥ]
int Exit_Potal[POTAL_MAX][2];
int Obstacle[OBSTACLE][2];
int Obstacle_stack = 3;
int Weapon_stack = 0;
int Door[SWITCH_MAX][2]; //���� ��ǥ
int Switch[SWITCH_MAX][2]; //����ġ ��ǥ
int LastObjectIndex = NULL;
int start_end = 1; //�ݺ���

void Init()
{ // ��ǥ ����
	int Width = (WIDTH * 2) + 1; //*2�� Ư�����ڴ� ��ĭ�� ����ϱ� ����
	int Height = HEIGHT + 4; //+1�� �� �°� ���� �߸��� ����
	char buf[256];
	sprintf(buf, "mode con: lines=%d cols=%d", Height, Width);
	system(buf); // â �����ϴ� ��ɾ�
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (map[y][x] == CHARACTER)
			{ //ĳ���� ��ġ ��ǥ
				character[X] = x;
				character[Y] = y;
			}
			else if (map[y][x] >= ENTRY_START && map[y][x] < ENTRY_START + POTAL_MAX)
			{ // 10 >= (���� ��Ż ��ȣ ������) && map < 16 (���� ��Ż�� ��ȣ ��)
				Entry_Potal[map[y][x] - ENTRY_START][X] = x; // [10~16 - 10][x] ���� ��Ż�� �ε��� ��ȣ�� x��ǥ
				Entry_Potal[map[y][x] - ENTRY_START][Y] = y;
			} //���� �̵��Ҷ� ���ⱸ ��ġ�� ���� �ε��� ��ȣ�� �̿�
			else if (map[y][x] >= EXIT_START && map[y][x] < EXIT_START + POTAL_MAX)
			{ // 20 >= (�ⱸ ��Ż ��ȣ ������) && map < 26 (�ⱸ ��Ż�� ��ȣ ��)
				Exit_Potal[map[y][x] - EXIT_START][X] = x; //[20~6 - 20][x] �ⱸ ��Ż�� �ε��� ��ȣ�� x��ǥ
				Exit_Potal[map[y][x] - EXIT_START][Y] = y;
			}
			else if (map[y][x] >= DOOR_START && map[y][x] < DOOR_START + SWITCH_MAX)
			{ // 50 >= (�� ��ȣ ������) && map < 53 (�� ��ȣ ��)
				Door[map[y][x] - DOOR_START][X] = x; //[50~3 - 50][x] �ⱸ ��Ż�� �ε��� ��ȣ�� x��ǥ
				Door[map[y][x] - DOOR_START][Y] = y;
			}
			//�̰� �ʿ��Ѱ�?
			else if (map[y][x] >= SWITCH_START && map[y][x] < SWITCH_START + SWITCH_MAX)
			{ // 60 >= (����ġ ��ȣ ������) && map < 63 (����ġ ��ȣ ��)
				Switch[map[y][x] - SWITCH_START][X] = x; //[60~3 - 60][x] �ⱸ ��Ż�� �ε��� ��ȣ�� x��ǥ
				Switch[map[y][x] - SWITCH_START][Y] = y;
			}
		}
	}
}
void MapDraw()
{ // �� �׸���
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (map[y][x] == WALL)
			{
				printf("��");
			}
			else if (map[y][x] == EXIT)
			{
				printf("��");
			}
			else if (map[y][x] == CHARACTER)
			{
				SKY_BLUE
					printf("��");
				ORIGINAL
			}
			else if (map[y][x] >= ENTRY_START && map[y][x] < ENTRY_START + POTAL_MAX)
			{ // 10 >= (���� ��Ż ��ȣ ������) && map < 14 (���� ��Ż�� ��ȣ ��)
				BLUE
					printf("��");
				ORIGINAL
			}
			else if (map[y][x] >= EXIT_START && map[y][x] < EXIT_START + POTAL_MAX)
			{ // 20 >= (�ⱸ ��Ż ��ȣ ������) && map < 24 (�ⱸ ��Ż�� ��ȣ ��)
				YELLOW
					printf("��");
				ORIGINAL
			}
			else if (map[y][x] == OBSTACLE_STACK) //4
			{ // ��ֹ� ��ȣ
				PUPPLE
					printf("��");
				ORIGINAL
			}
			else if (map[y][x] == OBSTACLE_STACK - 1) //3
			{
				PUPPLE
					printf("��");
				ORIGINAL
			}
			else if (map[y][x] == OBSTACLE_STACK - 2) //2
			{
				PUPPLE
					printf("��");
				ORIGINAL
			}
			else if (map[y][x] == WEAPON)
			{ // 40 ���� ��ȣ
				RED
					printf("��");
				ORIGINAL
			}
			else if (map[y][x] >= DOOR_START && map[y][x] < DOOR_START + SWITCH_MAX)
			{ // 50 �� ��ȣ
				YELLOW
					printf("��");
				ORIGINAL
			}
			else if (map[y][x] >= SWITCH_START && map[y][x] < SWITCH_START + SWITCH_MAX)
			{ // 60 ����ġ ��ȣ
				GOLD
					printf("��");
				ORIGINAL
			}
			else if (map[y][x] == NULL)
				printf("  ");
		}
		printf("\n");
	}
	//�Ʒ��� ����Ʈ �ϴ� ���
	BLUE printf("�Ա� : ��  ");
	YELLOW printf("�ⱸ : ��\n");
	PUPPLE printf("��ֹ� : �ˢǡ�  ");
	RED printf("���� : ��\n");
	YELLOW
	printf("�� : ��   ");
	GOLD
	printf("����ġ : ��");
	ORIGINAL
	printf("\n���� ���� : %d", Weapon_stack);
}

void MoveCheck()
{
	int index = map[character[Y]][character[X]]; // ĳ���Ͱ� �ִ� ��ġ == ��Ż �Ա�
	if (index >= ENTRY_START && index < ENTRY_START + POTAL_MAX)
	{ // ��Ż �Ա� > ��Ż �ⱸ
	  // ���� ��Ż �ڸ��� ������(��Ż�� �ε��� ��ȣ�� �����ϸ�)
	  // ENTRY_START == 10 ��Ż ��ȣ -10 Exit_Potal[0~4][x,y ��ǥ 1,0�� ����]
		character[X] = Exit_Potal[index - ENTRY_START][X];
		character[Y] = Exit_Potal[index - ENTRY_START][Y];
	}

} 

int MoveObstacleCheck(int y, int x)
{ // ������ ��ֹ����� ����. �̵� ���� �Ұ��� ���� // ||�� ������ ���� �ε����� ���� �ϳ��ε� �� �ϳ��� or�� ���.and�� ���� �ش��ϴ� ������ �ε����� �ϱ⿡ ����x
	if (map[y][x] == WALL)
	{ // �� �̵� �Ұ�
		return FALSE;
	}
	else if (map[y][x] == OBSTACLE_STACK -2 || map[y][x] == OBSTACLE_STACK - 1 || map[y][x] == OBSTACLE_STACK)
	{ // ��ֹ� ����
		if (Weapon_stack > 0)
		{
			if (map[y][x] == OBSTACLE_STACK - 2)
			{ // ��ֹ� ���� 2�϶�
				map[y][x] = NULL;
			}
			else
			{ // ��ֹ� ���� 4,3�϶�
				map[y][x]--;
			}
			Weapon_stack--;
		}
		return FALSE;
	}
	else if (map[y][x] >= DOOR_START && map[y][x] < DOOR_START + SWITCH_MAX)
	{ // �� �̵� �Ұ�
		return FALSE;
	}
	else
	{ // �ƹ��͵� ���� �̵� ����
		return TRUE;
	}
}

void MoveElementCheck()
{
	if (map[character[Y]][character[X]] == WEAPON)
	{ //���� �Ա�
		LastObjectIndex = 0;
		Weapon_stack += 2;
	}
	else if (map[character[Y]][character[X]] >= SWITCH_START && map[character[Y]][character[X]] < SWITCH_START + SWITCH_MAX)
	{ //����ġ ������ > ����ġ ����� , �� �����
		LastObjectIndex = 0; //����ġ �����
		int temp = map[character[Y]][character[X]] - SWITCH_START; //���� ����ġ�� �ε��� ��ȣ
		map[Door[temp][Y]][Door[temp][X]] = 0; //���� y�� x��ǥ�� �˾Ƴ���. ���� �ʿ��� ���� ���ش�

	}
	else if (map[character[Y]][character[X]] == EXIT)
	{ //�ⱸ //exit(1); ��������. ���α׷� �帧 ��� x ��� x //������ ������Ѿ� ��
		start_end = 0;
	}
}

// ���� ������ ���� ������ ���� ���� ���
void Move()
{
	char ch;
	ch = getch();
	if (ch == -32)
	{
		ch = getch();
	}
	system("cls"); //â �ʱ�ȭ
	map[character[Y]][character[X]] = LastObjectIndex;
	// ó���� LastObjectIndex == 0 ������ �ڸ� �ʱ�ȭ
	// �ι�° �ݺ����ʹ� LastObjectIndex ĳ���Ͱ� �־��� �ڸ��� ����ȴ�. 151��
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
	MoveCheck(); //���� ���� > �ⱸ ����
	LastObjectIndex = map[character[Y]][character[X]]; // ĳ���Ͱ� ���� ���� �ִ� ��� ����
	MoveElementCheck(); //����, ����ġ, �ⱸ
	map[character[Y]][character[X]] = CHARACTER; // ���� ��ġ�� ĳ���� �� ����

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