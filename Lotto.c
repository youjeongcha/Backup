#include <stdio.h>
#include <stdlib.h>
#include <time.h> // �ð� �� ����ϴ� �������
/// �ݺ��� �ȿ� ���� srand �� ����� ���� ���� ���ɼ��� Ŀ����.
//1~45
#define LOTTO_NUM 6

void main()
{
	int RNum;
	int Lotto[LOTTO_NUM] = { 0 };
	srand((unsigned)time(NULL)); //srand�õ尪 ����´�
	while (1)
	{
		//system("cls");
		for (int i = 0; i < LOTTO_NUM; i++)
		{
			RNum = (rand() % 45) + 1;
			Lotto[i] = RNum;

			for (int j = 0; j < i; j++)
			{
				if (Lotto[i] == Lotto[j])
				{
					break;
					//i--;
				}
			}
		}
		for (int i = 0; i <  LOTTO_NUM; i++)
		{
			printf("%d. %d\n", i + 1, Lotto[i]);
		}
		printf("\b"); //?
		system("pause");
	}
}