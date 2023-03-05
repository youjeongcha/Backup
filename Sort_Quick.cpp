#include<stdio.h>
#include<stdlib.h> //rand���
#include<time.h>
#include<Windows.h>

#define TEN 10
#define ASC 2
#define DESC 1

int Print(int sort[])
{
	int select;
	for (int i = 0; i < TEN; i++)
	{
		printf("%d ", sort[i]);
	}
	printf("\n1. ��ȣ ����\n");
	printf("2. �������� ����\n");
	printf("3. �������� ����\n");
	printf("4. ����\n");
	printf("���� : ");
	scanf("%d", &select);

	return select;
}

void Createsort(int sort[])
{//�ߺ� �� ����
	for (int i = 0; i < TEN; i++)
	{
		sort[i] = rand() % 100 + 1;
	}
}

void Swap(int sort[], int low, int pivot)
{
	int tmp;
	tmp = sort[pivot];
	sort[pivot] = sort[low];
	sort[low] = tmp;
}

int Quick(int sort[], int left, int right, int pivot, int type)
{//�ߺ� �� ������ ���� ����
	int low = left;
	int high = right - 1;
	int tmp;
	while (low <= high)
	{
		while ( ((type == ASC && (sort[high] >= sort[pivot]))
			|| (type == DESC && (sort[high] <= sort[pivot])))
			&& high > left  )
		{//high�� left���� �۾����� 0���Ϸ� �ȴٴ� ��	
			high--;
		}
		while (  ((type == ASC && (sort[low] <= sort[pivot]))
			|| (type == DESC && (sort[low] >= sort[pivot])))
			&& low < pivot  )
		{//low�� pivot���� Ŀ�� �� ����
			low++;
		}
		if (low >= high) //low�� high�� �������� ��� //pivot���� low high �� �۰ų� ū
			break;
		if (  (type == ASC && (sort[low] > sort[high]))
			|| (type == DESC && (sort[low] < sort[high]))  )
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

void QuickSort(int sort[], int left, int right, int type)
{//pivot ����
	if (left < right)
	{
		int pivot;
		pivot = Quick(sort, left, right, right, type);//�ι�° right�� pivot�� ����
		QuickSort(sort, left, pivot - 1, type);
		QuickSort(sort, pivot + 1, right, type);
	}
}

void main()
{
	srand(time(NULL));
	int sort[TEN] = { 0 };

	while (true)
	{
		switch (Print(sort))
		{
		case 1://��ȣ ����
			Createsort(sort);
			break;
		case 2://�������� ����
			QuickSort(sort, 0, TEN - 1, ASC);
			break;
		case 3://�������� ����
			QuickSort(sort, 0, TEN - 1, DESC);
			break;
		case 4://����
			return;
		}
		system("cls");
	}
}