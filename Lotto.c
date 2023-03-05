#include <stdio.h>
#include <stdlib.h>
#include <time.h> // 시간 값 사용하는 헤더파일
/// 반복문 안에 들어가서 srand 면 비슷한 값이 나올 가능성이 커진다.
//1~45
#define LOTTO_NUM 6

void main()
{
	int RNum;
	int Lotto[LOTTO_NUM] = { 0 };
	srand((unsigned)time(NULL)); //srand시드값 들고온다
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