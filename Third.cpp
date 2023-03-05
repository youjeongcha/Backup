#include "Third.h"

void Third::Test3(int iA[])
{
	/*	int tmp;
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			if (iarr[i] > iarr[j])
			{
				tmp = iarr[i];
				iarr[i] = iarr[j];
				iarr[j] = tmp;
			}
		}
	}*/
	QuickSort(iA, 0, 4, ASC);
	cout << "=============iarr=============\n";
	for (int i = 0; i < MAX; i++)
		cout << "iarr[" << i << "]" << " : " << iA[i] << "\n";
	cout << "\n";
}

void Third::Test3(char cB[])
{
	QuickSort(cB, 0, 4, DESC);

	cout << "=============charr=============\n";
	for (int i = 0; i < MAX; i++)
		cout << "charr[" << i << "]" << " : " << cB[i] << "\n";
	cout << "\n";
}

void Third::Swap(int sort[], int low, int pivot)
{
	int tmp;
	tmp = sort[pivot];
	sort[pivot] = sort[low];
	sort[low] = tmp;
}

int Third::Quick(int sort[], int left, int right, int pivot, int type)
{//중복 수 있으면 무한 루프
	int low = left;
	int high = right - 1;
	int tmp;
	while (low <= high)
	{
		while (((type == ASC && (sort[high] >= sort[pivot]))
			|| (type == DESC && (sort[high] <= sort[pivot])))
			&& high > left)
		{//high가 left보다 작아지면 0이하로 된다는 거	
			high--;
		}
		while (((type == ASC && (sort[low] <= sort[pivot]))
			|| (type == DESC && (sort[low] >= sort[pivot])))
			&& low < pivot)
		{//low는 pivot보다 커질 수 없다
			low++;
		}
		if (low >= high) //low와 high가 같아지는 경우 //pivot보다 low high 다 작거나 큰
			break;
		if ((type == ASC && (sort[low] > sort[high]))
			|| (type == DESC && (sort[low] < sort[high])))
		{//
			tmp = sort[low];
			sort[low] = sort[high];
			sort[high] = tmp;
		}
	}
	//while 벗어나면 low > high
	//low와 pivot 교환
	Swap(sort, low, pivot);

	return low;
}


void Third::QuickSort(int sort[], int left, int right, int type)
{//pivot 설정
	if (left < right)
	{
		int pivot;
		pivot = Quick(sort, left, right, right, type);//두번째 right는 pivot과 동일
		QuickSort(sort, left, pivot - 1, type);
		QuickSort(sort, pivot + 1, right, type);
	}
}

///////

void Third::Swap(char sort[], int low, int pivot)
{
	char tmp;
	tmp = sort[pivot];
	sort[pivot] = sort[low];
	sort[low] = tmp;
}

int Third::Quick(char sort[], int left, int right, int pivot, int type)
{//중복 수 있으면 무한 루프
	int low = left;
	int high = right - 1;
	int tmp;
	while (low <= high)
	{
		while (((type == ASC && (sort[high] >= sort[pivot]))
			|| (type == DESC && (sort[high] <= sort[pivot])))
			&& high > left)
		{//high가 left보다 작아지면 0이하로 된다는 거	
			high--;
		}
		while (((type == ASC && (sort[low] <= sort[pivot]))
			|| (type == DESC && (sort[low] >= sort[pivot])))
			&& low < pivot)
		{//low는 pivot보다 커질 수 없다
			low++;
		}
		if (low >= high) //low와 high가 같아지는 경우 //pivot보다 low high 다 작거나 큰
			break;
		if ((type == ASC && (sort[low] > sort[high]))
			|| (type == DESC && (sort[low] < sort[high])))
		{//
			tmp = sort[low];
			sort[low] = sort[high];
			sort[high] = tmp;
		}
	}
	//while 벗어나면 low > high
	//low와 pivot 교환
	Swap(sort, low, pivot);

	return low;
}

void Third::QuickSort(char sort[], int left, int right, int type)
{//pivot 설정
	if (left < right)
	{
		int pivot;
		pivot = Quick(sort, left, right, right, type);//두번째 right는 pivot과 동일
		QuickSort(sort, left, pivot - 1, type);
		QuickSort(sort, pivot + 1, right, type);
	}
}