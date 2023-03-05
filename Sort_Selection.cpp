#include<stdio.h>
#include <stdlib.h> //rand사용
#include<time.h>
#include<Windows.h>

#define TEN 10

int Print(int sort[])
{
	int select;
	for (int i = 0; i < TEN; i++)
	{
		printf("%d ", sort[i]);
	}
	printf("\n1. 번호 생성\n");
	printf("2. 오름차순 정렬\n");
	printf("3. 내림차순 정렬\n");
	printf("4. 종료\n");
	printf("선택 : ");
	scanf("%d", &select);

	return select;
}

void Createsort(int sort[])
{//중복 수 무관
	for (int i = 0; i < TEN; i++)
	{
		int temp = rand() % 100 + 1;
		sort[i] = temp;
	}
}

void AscendingOrder(int sort[])
{
	for (int i = 0; i < TEN - 1; i++)
	{
		for (int j = i + 1; j < TEN; j++)
		{
			if (sort[i] > sort[j])
			{
				int temp = sort[j];
				sort[j] = sort[i];
				sort[i] = temp;
			}
		}
	}
}

void DescendingOrder(int sort[])
{
	for (int i = 0; i < TEN - 1; i++)
	{
		for (int j = i + 1; j < TEN; j++)
		{
			if (sort[i] < sort[j])
			{
				int temp = sort[j];
				sort[j] = sort[i];
				sort[i] = temp;
			}
		}
	}
}

void main()
{
	srand(time(NULL));
	int sort[TEN] = { 0,0,0,0,0,0,0,0,0,0 };

	while (true)
	{
		switch (Print(sort))
		{
		case 1://번호 생성
			Createsort(sort);
			break;
		case 2://오름차순 정렬
			AscendingOrder(sort);
			break;
		case 3://내림차순 정렬
			DescendingOrder(sort);
			break;
		case 4://종료
			return;
		}
		system("cls");
	}
}