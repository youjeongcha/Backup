#pragma once
#include"Mecro.h"

#define ASC 0
#define DESC 1
#define MAX 5


class Third
{
public:
	void Test3(int iA[]);
	void Test3(char cB[]);

	void QuickSort(int sort[], int start, int end, int type); //오름
	int Quick(int sort[], int left, int right, int pivot, int type);
	void Swap(int sort[], int low, int pivot);

	void QuickSort(char sort[], int start = 0, int end = 4, int type = 1); //내림
	int Quick(char sort[], int left, int right, int pivot, int type);
	void Swap(char sort[], int low, int pivot);
};

