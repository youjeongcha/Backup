#include<stdio.h>
#include<stdlib.h>
#include<time.h>//시간 값 사용하는 헤더파일
#define LOTTO_NUM 6
void main()
{
	int RNum;
	int Lotto[LOTTO_NUM] = { 0 };
	int Flag;
	srand((unsigned)time(NULL));
	while (1)
	{
		system("cls");
		for (int i = 0; i < LOTTO_NUM;)
		{
			Flag = 1;
			RNum = (rand() % 45) + 1;
			for (int j = 0; j < i; j++)
			{
				if (RNum == Lotto[j])
					Flag = 0; //Ture Flase 이용
			}
			if (Flag)
				Lotto[i++] = RNum;
		}
		for (int i = 0; i < LOTTO_NUM; i++)
			printf("%d.%d\n", i + 1, Lotto[i]);
		system("pause");
	}
}
