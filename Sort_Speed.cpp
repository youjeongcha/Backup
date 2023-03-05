#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>

#define COLOR_HANDLE GetStdHandle(STD_OUTPUT_HANDLE)
#define RED SetConsoleTextAttribute(COLOR_HANDLE,0x000c)
#define BLUE SetConsoleTextAttribute(COLOR_HANDLE,0x0009)
#define PUPPLE SetConsoleTextAttribute(COLOR_HANDLE,0x0005)
#define WHITE SetConsoleTextAttribute(COLOR_HANDLE,0x0007)

#define ARRAY_MAX 15
#define PRINT_DELAY 50
#define ESC 27

void PrintArray(int Array[ARRAY_MAX], int index1, int index2, int StartTime)
{
	system("cls");
	for (int i = 0; i < ARRAY_MAX; i++)
	{//배열 길이
		if (i == index1)//index1 기준 //밖에서 들고온 i
			RED;
		else if (i == index2)//index2 기준이랑 비교하는 애 //밖에서 들고온 j
			BLUE;
		else
			WHITE;
		for (int j = 0; j < Array[i]; j++) //배열 안의 수 -> ▩
			printf("▩");
		printf("\n");
	}
	if (StartTime != -1) //StartTime을 -1로 설정한 이유?
	{
		WHITE;
		printf("\n걸린 시간 : %.4f초", (clock() - StartTime) / 1000.0f); //1000.0f ?
	}
	Sleep(PRINT_DELAY);//0.2초 50 //1초 250
}

void Swap(int* Num1, int* Num2)
{
	int tmp = *Num1;
	*Num1 = *Num2;
	*Num2 = tmp;
}

void Shuffle(int Array[ARRAY_MAX]) //셔플
{
	for (int i = 0; i < 1000; i++)
	{
		int index1 = rand() % ARRAY_MAX;//0 ~ 9 //ARRAY_MAX가 15로 아는데 왜 0~9? 0~14
		int index2 = rand() % ARRAY_MAX;
		Swap(&Array[index1], &Array[index2]);
	}
}

void SelectSort(int Array[ARRAY_MAX], int StartTime)
{
	for (int i = 0; i < ARRAY_MAX - 1; i++)
	{
		for (int j = i + 1; j < ARRAY_MAX; j++)
		{
			PrintArray(Array, i, j, StartTime);
			if (Array[i] > Array[j])
			{
				Swap(&Array[i], &Array[j]);
				PrintArray(Array, i, j, StartTime);
			}
		}
	}
}

void PrintArray_Insert(int Array[ARRAY_MAX], int index, int Temp, int StartTime)
{
	system("cls");
	for (int i = 0; i < ARRAY_MAX; i++)
	{
		if (i == index)
			BLUE;
		else
			WHITE;
		for (int j = 0; j < Array[i]; j++)
			printf("▩");
		printf("\n");
	}
	printf("\n\n");
	//
	RED;
	for (int i = 0; i < Temp; i++)
		printf("▩");
	//
	if (StartTime != -1)
	{
		WHITE;
		printf("\n\n걸린 시간 : %.4f초", (clock() - StartTime) / 1000.0f);
	}
	Sleep(PRINT_DELAY);//0.2초
}

void InsertSort(int Array[ARRAY_MAX], int StartTime)
{
	for (int i = 1; i < ARRAY_MAX; i++)
	{
		int Temp = Array[i], j;
		for (j = i - 1; j >= 0 && Array[j] > Temp; j--)
		{
			PrintArray_Insert(Array, j, Temp, StartTime);
			Array[j + 1] = Array[j]; //검사하는 수보다 크면 //검사하는 수 다음 인덱스에 전달
			PrintArray_Insert(Array, j, Temp, StartTime);
		}
		PrintArray_Insert(Array, j, Temp, StartTime);
		Array[j + 1] = Temp; //인덱스0에 닿거나, Array[j]의 값이 temp보다 작은 경우 반복을 끝내고  Array[j+1]에 temp 넣음
		PrintArray_Insert(Array, j, -1, StartTime);
	}
}

void BubbleSort(int Array[ARRAY_MAX], int StartTime)
{
	for (int i = 0; i < ARRAY_MAX - 1; i++) //배열 맨 끝 값 제외
	{
		for (int j = 0; j < ARRAY_MAX - i - 1; j++) //i만큼 i가 돌아야 할 반복이 줄어든다.
		{
			PrintArray(Array, j, j + 1, StartTime);
			if (Array[j] > Array[j + 1])
			{
				Swap(&Array[j], &Array[j + 1]);
				PrintArray(Array, j + 1, j, StartTime);
			}
		}
	}
}

void PrintArray_Merge(int Array[ARRAY_MAX], int left, int mid, int right, int StartTime)
{
	system("cls");
	for (int i = 0; i < ARRAY_MAX; i++)
	{
		if (i >= left && i <= mid)
			RED;
		else if (i >= mid + 1 && i <= right)
			BLUE;
		else
			WHITE;
		for (int j = 0; j < Array[i]; j++)
			printf("▩");
		printf("\n");
	}
	if (StartTime != -1)
	{
		WHITE;
		printf("\n걸린 시간 : %.4f초", (clock() - StartTime) / 1000.0f);
	}
	Sleep(PRINT_DELAY);//0.2초
}

void Merge(int Array[ARRAY_MAX], int left, int mid, int right)
{ //temp로 배열 하나를 더 생성해야 한다
	int LeftIndex = left;
	int RightIndex = mid + 1;
	int TempArray[ARRAY_MAX] = { 0 };
	int index = 0;
	while (LeftIndex <= mid && RightIndex <= right)
	{
		if (Array[LeftIndex] <= Array[RightIndex])
			TempArray[index++] = Array[LeftIndex++];
		else
			TempArray[index++] = Array[RightIndex++];
	}
	//
	// 조건식 i와 k가 지정된 배열 범위를 초과하는 상황이 생길 경우
		//> 한쪽 배열이 다 끝남
	if (LeftIndex > mid)
	{//왼쪽 배열 끝 LeftIndex
		while (RightIndex <= right)
			TempArray[index++] = Array[RightIndex++];
	}
	else
	{//오른쪽 배열 끝
		while (LeftIndex <= mid)
			TempArray[index++] = Array[LeftIndex++];
	}
	//
	int size = right - left + 1;
	for (int i = 0; i < size; i++)
	{//원 배열로 옮긴다
		Array[left + i] = TempArray[i];
	}
}

void MergeSort(int Array[ARRAY_MAX], int left, int right, int StartTime)
{//재귀로 나누고 돌아오면서 정렬
	if (left >= right) //재귀로 나눈게 하나가 되면
		return;
	int mid = (left + right) / 2;
	MergeSort(Array, left, mid, StartTime);
	MergeSort(Array, mid + 1, right, StartTime);

	PrintArray_Merge(Array, left, mid, right, StartTime);
	Merge(Array, left, mid, right);
	PrintArray_Merge(Array, left, mid, right, StartTime);
}

void PrintArray_Quick(int Array[ARRAY_MAX], int low, int high, int pivot, int StartTime)
{
	system("cls");
	for (int i = 0; i < ARRAY_MAX; i++)
	{
		if (i == low)
			RED;
		else if (i == high)
			BLUE;
		//
		else if (i == pivot)
			PUPPLE;
		//
		else
			WHITE;
		for (int j = 0; j < Array[i]; j++)
			printf("▩");
		printf("\n");
	}
	if (StartTime != -1)
	{
		WHITE;
		printf("\n걸린 시간 : %.4f초", (clock() - StartTime) / 1000.0f);
	}
	Sleep(PRINT_DELAY);//0.2초
}

int Patition(int Array[ARRAY_MAX], int left, int right, int StartTime)
{
	int low = left;
	int high = right - 1;
	int pivot = right;
	PrintArray_Quick(Array, low, high, pivot, StartTime);
	while (low <= high)
	{
		while (Array[low] <= Array[pivot] && low < right)
			low++;
		while (Array[high] >= Array[pivot] && high >= left)
			high--;
		if (low <= high) //역전 되지 않은 경우 정렬
			Swap(&Array[low], &Array[high]);
	}
	Swap(&Array[low], &Array[pivot]); //pivot과 low
	PrintArray_Quick(Array, left, right, low, StartTime);
	return low;
}

void QuickSort(int Array[ARRAY_MAX], int left, int right, int StartTime)
{ //정렬하고 pivot기준으로 나눠서 재귀하면서 정렬. 재귀 풀고 합치면서 재정렬
	if (left >= right)
		return;
	int pivot = Patition(Array, left, right, StartTime);
	QuickSort(Array, left, pivot - 1, StartTime);
	QuickSort(Array, pivot + 1, right, StartTime);

}

void main()
{
	srand(time(NULL));
	//Sleep(3000);//프로그램을 ms 단위로 잠시 멈춰주는 기능(1000 : 1초)

	int Array[ARRAY_MAX];
	for (int i = 0; i < ARRAY_MAX; i++)
		Array[i] = i + 1;
	while (TRUE)
	{
		Shuffle(Array);
		PrintArray(Array, -1, -1, -1);
		printf("\n\n1.SelectSort  2.InsertSort  3.BubbleSort  4.MergeSort  5.QuickSort\n");
		switch (getch())//키보드 입력함수( 키보드 입력할때까지 대기하려는 목적)
		{
		case '1':
			SelectSort(Array, clock());
			break;
		case '2':
			InsertSort(Array, clock());
			break;
		case '3':
			BubbleSort(Array, clock());
			break;
		case '4':
			MergeSort(Array, 0, ARRAY_MAX - 1, clock());
			break;
		case '5':
			QuickSort(Array, 0, ARRAY_MAX - 1, clock());
			break;
		case ESC:
			return;
		}
		getch();
	}
}