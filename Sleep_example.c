#include <stdio.h>
#include <Windows.h>
#include <conio.h>
//kibhit
//Ű���带 �Է� ���� ��� ���� ��ȯ�ϴ� �Լ�
//�ʿ� ������� <conio.h>

//Sleep ���� �ڵ� > �� �¿� �̵� �ڵ�
//���� ���� ���� ��� x ��ü ����� ����ϱ� ���ؼ�

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
				printf("��");
			}
			else if (Map[y][x] == STOP_STAR)
			{
				printf("��");
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
		{ //x�� ù��° ���� ã���� �Ʒ� ������ ������� ��
			///ù��° ���� ���µ� �Ʒ� ������ ��µǴ� ��쿡�� ����?
			for (int y = 0; y <= Stop_y; y++)
			{
				Map[y][x] = NULL;
				if (0 <= location_star && location_star < WIDTH - 1) //�� ������ > ���� �������� ��ĭ�� �̵� > �� ���� ����
				{//locate�� 0�� �Ǹ� �������� ���� ���� �����. 
					Map[y][x - 1] = MOVE_STAR;
				}
				else if (WIDTH - 1 <= location_star && location_star < WIDTH * 2 - 1) //���� �� ���ʿ� ������ >  ���������� ��ĭ�� > �ǿ����� ����
				{//locate�� WIDTH - 1 �� �Ǹ� ���� ���������� ���� �� ������.
					Map[y][x + 1] = MOVE_STAR;

				}
			}
			break; //y ���ٿ� ���� �� ��µǰ� ���� �ݺ����� �����µ� ���ǹ��� �ش� �ȵǱ� ������ x�ݺ����� ������.
		}
	}
	if (0 <= location_star && location_star < WIDTH * 2 - 1)
	{//���ڸ��� ���ƿ����� �ͱ��� �ؼ� location_star 18�� 1��Ʈ
		location_star++; //�� ���� �� ��� �Ǹ� location_star ��� //0~18
		if (location_star == 18)
		{//�� ��Ʈ�� ������ �ٽ� �ݺ�
			location_star = 0;
		}
	}

	//printf("Ȯ�� : %d", location_star);
	return location_star;
}

int Stop(int Map[HEIGHT][WIDTH], int y)
{//getch()�� �Է��� ������ �Է� �ɶ����� �����ֱ� ������
	if (kbhit()) //Ű���� �Է��ߴ��� kbhit()���� �Է� ���۸� ���� Ȯ�� �� ������. �Է� ���� ȭ�鿡 ��µǱ� ���� �ӽ� �����
	{
		char ch = getch(); //Ű���� �ϳ��� �޴�
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
			y--; //���� �ϳ� ���߸� �� ���� ���� ���� ���ʰ� �Ǵ� ��
		}
	}
	return y;
}

void main()
{
	int Stop_Y = HEIGHT - 1; //���� ���� ������ �������ִ�. �ؿ��� ���� �ϳ���
	int Map[HEIGHT][WIDTH] = { NULL };
	int location_star = 0;

	for (int y = 0; y < HEIGHT; y++)
	{ //������ �� ���� ���ٷ� �� ����
		Map[y][WIDTH - 1] = MOVE_STAR;
	}
	while (1)
	{
		Draw(Map);
		Stop_Y = Stop(Map, Stop_Y); //���� ����ÿ� ���� ���� ���� �� �ְ� ����
		Sleep(SPEED);
		location_star = Update(Map, Stop_Y, location_star);
	}
}