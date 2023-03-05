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


int Patition(int Array[], int left, int right, int Type)
{
	int pivot = Array[right]; //값을 받아서 사용
	int low = left;
	int high = right - 1;
	while (low <= high)
	{
		switch (Type)
		{
		case ASC:
			while (Array[low] <= pivot && low <= right - 1) low++;
			while (Array[high] >= pivot && high >= left) high--;
			break;
		case DESC:
			while (Array[low] >= pivot && low <= right - 1) low++;
			while (Array[high] <= pivot && high >= left) high--;
			break;
		}
		if (low < high) Swap(&Array[low], &Array[high]); //역전 되지 않은 경우 정렬
	}
	//low와 high가 역전
	Swap(&Array[right], &Array[low]); //pivot과 low
	return low;
}

void Sort(int Array[], int left, int right, int Type)
{
	if (left <= right)
	{
		int pivot = Patition(Array, left, right, Type);
		Sort(Array, left, pivot - 1, Type);
		Sort(Array, pivot + 1, right, Type);
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