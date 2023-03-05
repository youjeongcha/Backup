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
{//�ߺ� �� ������ ���� ����
	int low = left;
	int high = right - 1;
	int tmp;
	while (low <= high)
	{
		while (((type == ASC && (sort[high] >= sort[pivot]))
			|| (type == DESC && (sort[high] <= sort[pivot])))
			&& high > left)
		{//high�� left���� �۾����� 0���Ϸ� �ȴٴ� ��	
			high--;
		}
		while (((type == ASC && (sort[low] <= sort[pivot]))
			|| (type == DESC && (sort[low] >= sort[pivot])))
			&& low < pivot)
		{//low�� pivot���� Ŀ�� �� ����
			low++;
		}
		if (low >= high) //low�� high�� �������� ��� //pivot���� low high �� �۰ų� ū
			break;
		if ((type == ASC && (sort[low] > sort[high]))
			|| (type == DESC && (sort[low] < sort[high])))
		{//
			tmp = sort[low];
			sort[low] = sort[high];
			sort[high] = tmp;
		}
	}
	//while ����� low > high
	//low�� pivot ��ȯ
	Swap(sort, low, pivot);

	return low;
}


void Third::QuickSort(int sort[], int left, int right, int type)
{//pivot ����
	if (left < right)
	{
		int pivot;
		pivot = Quick(sort, left, right, right, type);//�ι�° right�� pivot�� ����
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
{//�ߺ� �� ������ ���� ����
	int low = left;
	int high = right - 1;
	int tmp;
	while (low <= high)
	{
		while (((type == ASC && (sort[high] >= sort[pivot]))
			|| (type == DESC && (sort[high] <= sort[pivot])))
			&& high > left)
		{//high�� left���� �۾����� 0���Ϸ� �ȴٴ� ��	
			high--;
		}
		while (((type == ASC && (sort[low] <= sort[pivot]))
			|| (type == DESC && (sort[low] >= sort[pivot])))
			&& low < pivot)
		{//low�� pivot���� Ŀ�� �� ����
			low++;
		}
		if (low >= high) //low�� high�� �������� ��� //pivot���� low high �� �۰ų� ū
			break;
		if ((type == ASC && (sort[low] > sort[high]))
			|| (type == DESC && (sort[low] < sort[high])))
		{//
			tmp = sort[low];
			sort[low] = sort[high];
			sort[high] = tmp;
		}
	}
	//while ����� low > high
	//low�� pivot ��ȯ
	Swap(sort, low, pivot);

	return low;
}

void Third::QuickSort(char sort[], int left, int right, int type)
{//pivot ����
	if (left < right)
	{
		int pivot;
		pivot = Quick(sort, left, right, right, type);//�ι�° right�� pivot�� ����
		QuickSort(sort, left, pivot - 1, type);
		QuickSort(sort, pivot + 1, right, type);
	}
}