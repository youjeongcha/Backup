#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include<time.h>
//kbhit
//Ű���带 �Է� ���� ��� ���� ��ȯ�ϴ� �Լ�
//�ʿ� ������� <conio.h>

#define LEFT -1 //��
#define RIGHT 1 //��
#define WIDTH 10
#define HEIGHT 10
#define MOVESTAR 1
#define STOPSTAR 2
#define SPEED 100

void Draw(int Map[][WIDTH]) //
{
	system("cls");
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (Map[y][x] == MOVESTAR || Map[y][x] == STOPSTAR)
				printf("��");
			else
				printf("  ");
		}
		printf("\n");
	}
	printf("�� ���߱� = d");
}

int DirectionCheck(int Map[][WIDTH], int Direction)
{
	if (Map[0][0] == MOVESTAR && Direction == LEFT)
		Direction = RIGHT;
	else if (Map[0][WIDTH - 1] == MOVESTAR && Direction == RIGHT)
		Direction = LEFT;
	return Direction;
}


void Update(int Map[HEIGHT][WIDTH], int Stop_y, int Direction)
{
	for (int x = 0; x < WIDTH; x++)
	{
		if (Map[0][x] == MOVESTAR)
		{
			for (int y = 0; y <= Stop_y; y++)
			{
				Map[y][x] = NULL;
				Map[y][x + Direction] = MOVESTAR;
			}
			break;
		}
	}
}

int Stop(int Map[HEIGHT][WIDTH], int y)
{
	if (kbhit())
	{
		char ch = getch();
		if (ch == 'd' || ch == 'D')
		{
			for (int x = 0; x < WIDTH; x++)
			{
				if (Map[y][x] == MOVESTAR)
				{
					Map[y][x] = STOPSTAR;
					break;
				}
			}
			y--;
		}
	}
	return y;
}


void main()
{
	int Stop_Y = HEIGHT - 1;
	int Map[HEIGHT][WIDTH] = { 0 };
	int Derection = LEFT; //Derection ���� ����
	for (int y = 0; y < HEIGHT; y++)
		Map[y][WIDTH - 1] = MOVESTAR;
	while (1)
	{//������ �ٸ�
		Stop_Y = Stop(Map, Stop_Y);
		Update(Map, Stop_Y, Derection);
		Derection = DirectionCheck(Map, Derection); //DirectionCheck �Լ��� ���� �� �̵� ���� ����
		Draw(Map); 
		Sleep(SPEED); 
	}
}