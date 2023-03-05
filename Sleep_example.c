#include <stdio.h>
#include <Windows.h>
#include <conio.h>
//kibhit
//키보드를 입력 했을 경우 참을 반환하는 함수
//필요 헤더파일 <conio.h>

//Sleep 예제 코드 > 별 좌우 이동 코드
//이제 전역 변수 사용 x 객체 지향언어를 사용하기 위해서

#define WIDTH 10
#define HEIGHT 10
//#define STAR 1
#define MOVE_STAR 1
#define STOP_STAR 2
#define NULL 0
#define SPEED 100

void Draw(int Map[HEIGHT][WIDTH])
{
	system("cls");
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (Map[y][x] == MOVE_STAR)
			{
				printf("☆");
			}
			else if (Map[y][x] == STOP_STAR)
			{
				printf("★");
			}
			else
			{
				printf("  ");
			}
		}
		printf("\n");
	}
}

int Update(int Map[HEIGHT][WIDTH], int Stop_y, int location_star)
{
	//int locate = WIDTH - 1;
	for (int x = 0; x < WIDTH; x++)
	{
		if (Map[0][x] == MOVE_STAR)
		{ //x줄 첫번째 별만 찾으면 아래 별들은 따라오는 것
			///첫번째 별이 없는데 아래 별들이 출력되는 경우에는 무엇?
			for (int y = 0; y <= Stop_y; y++)
			{
				Map[y][x] = NULL;
				if (0 <= location_star && location_star < WIDTH - 1) //맨 오른쪽 > 별을 왼쪽으로 한칸씩 이동 > 맨 왼쪽 도착
				{//locate가 0이 되면 왼쪽으로 가는 것을 멈춘다. 
					Map[y][x - 1] = MOVE_STAR;
				}
				else if (WIDTH - 1 <= location_star && location_star < WIDTH * 2 - 1) //별이 맨 왼쪽에 있을때 >  오른쪽으로 한칸씩 > 맨오른쪽 도착
				{//locate가 WIDTH - 1 이 되면 이제 오른쪽으로 가는 것 끝낸다.
					Map[y][x + 1] = MOVE_STAR;

				}
			}
			break; //y 한줄에 별이 다 출력되고 나면 반복문을 끝내는데 조건문은 해당 안되기 때문에 x반복문이 끝난다.
		}
	}
	if (0 <= location_star && location_star < WIDTH * 2 - 1)
	{//제자리로 돌아오오는 것까지 해서 location_star 18을 1세트
		location_star++; //별 한줄 다 출력 되면 location_star 상승 //0~18
		if (location_star == 18)
		{//한 세트가 끝나면 다시 반복
			location_star = 0;
		}
	}

	//printf("확인 : %d", location_star);
	return location_star;
}

int Stop(int Map[HEIGHT][WIDTH], int y)
{//getch()로 입력을 받으면 입력 될때까지 멈춰있기 때문에
	if (kbhit()) //키보드 입력했는지 kbhit()으로 입력 버퍼를 통해 확인 한 다음에. 입력 버퍼 화면에 출력되기 전에 임시 저장소
	{
		char ch = getch(); //키보드 하나씩 받는
		if (ch == 'd' || ch == 'D')
		{
			for (int x = 0; x < WIDTH; x++)
			{
				if (Map[y][x] == MOVE_STAR)
				{
					Map[y][x] = STOP_STAR;
					break;
				}
			}
			y--; //별이 하나 멈추면 그 위의 별이 멈출 차례가 되는 것
		}
	}
	return y;
}

void main()
{
	int Stop_Y = HEIGHT - 1; //멈출 별의 순서는 정해져있다. 밑에서 부터 하나씩
	int Map[HEIGHT][WIDTH] = { NULL };
	int location_star = 0;

	for (int y = 0; y < HEIGHT; y++)
	{ //오른쪽 맨 끝에 한줄로 별 생성
		Map[y][WIDTH - 1] = MOVE_STAR;
	}
	while (1)
	{
		Draw(Map);
		Stop_Y = Stop(Map, Stop_Y); //별이 멈출시에 다음 별이 멈출 수 있게 조정
		Sleep(SPEED);
		location_star = Update(Map, Stop_Y, location_star);
	}
}