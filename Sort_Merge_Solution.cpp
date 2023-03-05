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

void MergeResult(int Array[MAX], int left, int mid, int right, int Type)
{
	int leftindex = left;
	int rightindex = mid + 1;

	int TempArray[MAX] = { 0 };
	int index = 0;
	while (leftindex <= mid && rightindex <= right)
	{
		if ((Type == ASC && Array[leftindex] <= Array[rightindex])
			||
			(Type == DESC && Array[leftindex] >= Array[rightindex]))
			TempArray[index++] = Array[leftindex++];
		else
			TempArray[index++] = Array[rightindex++];
	}
	if (leftindex > mid)
	{
		while (rightindex <= right)
		{
			TempArray[index++] = Array[rightindex++];
		}
	}
	else
	{
		while (leftindex <= mid)
		{
			TempArray[index++] = Array[leftindex++];
		}
	}
	int size = right - left;
	for (int i = 0; i <= size; i++)
	{
		Array[left + i] = TempArray[i];
	}
}

void Sort(int Arr[MAX], int left, int right, int Type)
{
	if (left >= right)
		return;
	int mid = (left + right) / 2;
	Sort(Arr, left, mid, Type);
	Sort(Arr, mid + 1, right, Type);

	MergeResult(Arr, left, mid, right, Type);
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
		printf("1. 번호 생성\n");
		printf("2. 오름차순 정렬\n");
		printf("3. 내림차순 정렬\n");
		printf("4. 종료\n");
		printf("선택 : ");
		scanf("%d", &Select);
		switch (Select)
		{
		case 1:
			SetArray(Arr);
			break;
		case 2:
			Sort(Arr, 0, MAX - 1, ASC);
			break;
		case 3:
			Sort(Arr, 0, MAX - 1, DESC);
			break;
		case 4:
			return;
		}
	}
}