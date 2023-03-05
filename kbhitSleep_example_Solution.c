#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include<time.h>
//kbhit
//키보드를 입력 했을 경우 참을 반환하는 함수
//필요 헤더파일 <conio.h>

#define LEFT -1 //왼
#define RIGHT 1 //오
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
				printf("☆");
			else
				printf("  ");
		}
		printf("\n");
	}
	printf("별 멈추기 = d");
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
	int Derection = LEFT; //Derection 변수 유의
	for (int y = 0; y < HEIGHT; y++)
		Map[y][WIDTH - 1] = MOVESTAR;
	while (1)
	{//순서도 다름
		Stop_Y = Stop(Map, Stop_Y);
		Update(Map, Stop_Y, Derection);
		Derection = DirectionCheck(Map, Derection); //DirectionCheck 함수를 만들어서 별 이동 방향 조절
		Draw(Map); 
		Sleep(SPEED); 
	}
}