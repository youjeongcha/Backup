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

//void Swap(int* num1, int* num2)
//{
//	int tmp = *num1;
//	*num1 = *num2;
//	*num2 = tmp;
//}
void Sort(int Arr[MAX], int Type)
{
	for (int i = 1; i < MAX; i++)
	{
		int Tmp = Arr[i];
		int j;
		for (int j = i - 1; ; j--)
		{
			if (j < 0 || (Type == ASC && Arr[j] < Tmp) || (Type == DESC && Arr[j] > Tmp))
			{//j�� 0���� �۴� == ��ȸ�� ���� ����
				Arr[j + 1] = Tmp;
				break;
			}
			Arr[j + 1] = Arr[j];
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