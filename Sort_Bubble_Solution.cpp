#include <stdio.h>
#include <time.h>
#include <Windows.h>
#include <stdlib.h>
#define MAX 10
#define DESC 1
#define ASC 2

void Print(int Arr[MAX])
{
	for (int i = 0; i < MAX; i++)
		printf("%d ", Arr[i]);
	printf("\n");
}

void SetArray(int Arr[MAX])
{
	for (int i = 0; i < MAX; i++)
		Arr[i] = rand() % 100 + 1;
}

void Swap(int* num1, int* num2)
{
	int tmp = *num1;
	*num1 = *num2;
	*num2 = tmp;
}
void Sort(int Arr[MAX], int Type)
{
	for (int i = MAX - 1; i > 0; i--)
	{
		for (int j = 0; j < i; j++)
		{
			if ((Type == ASC && Arr[j] > Arr[j + 1]) || (Type == DESC && Arr[j] < Arr[j + 1]))
				Swap(&Arr[j], &Arr[j + 1]);
		}
	}
}

void main()
{
	int Number;
	int Arr[MAX] = { 0 };

	srand(time(NULL));

	int Select;
	while (1)
	{
		system("cls");
		Print(Arr);
		printf("1. ��ȣ ����\n");
		printf("2. �������� ����\n");
		printf("3. �������� ����\n");
		printf("4. ����\n");
		printf("���� : ");
		scanf("%d", &Select);
		switch (Select)
		{
		case 1:
			SetArray(Arr);
			break;
		case 2:
			Sort(Arr, ASC);
			break;
		case 3:
			Sort(Arr, DESC);
			break;
		case 4:
			return;
		}
	}
}