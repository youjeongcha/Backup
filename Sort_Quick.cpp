#include<stdio.h>
#include<stdlib.h> //rand사용
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
{//중복 수 있으면 무한 루프
	int low = left;
	int high = right - 1;
	int tmp;
	while (low <= high)
	{
		while ( ((type == ASC && (sort[high] >= sort[pivot]))
			|| (type == DESC && (sort[high] <= sort[pivot])))
			&& high > left  )
		{//high가 left보다 작아지면 0이하로 된다는 거	
			high--;
		}
		while (  ((type == ASC && (sort[low] <= sort[pivot]))
			|| (type == DESC && (sort[low] >= sort[pivot])))
			&& low < pivot  )
		{//low는 pivot보다 커질 수 없다
			low++;
		}
		if (low >= high) //low와 high가 같아지는 경우 //pivot보다 low high 다 작거나 큰
			break;
		if (  (type == ASC && (sort[low] > sort[high]))
			|| (type == DESC && (sort[low] < sort[high]))  )
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

void QuickSort(int sort[], int left, int right, int type)
{//pivot 설정
	if (left < right)
	{
		int pivot;
		pivot = Quick(sort, left, right, right, type);//두번째 right는 pivot과 동일
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
		case 1://번호 생성
			Createsort(sort);
			break;
		case 2://오름차순 정렬
			QuickSort(sort, 0, TEN - 1, ASC);
			break;
		case 3://내림차순 정렬
			QuickSort(sort, 0, TEN - 1, DESC);
			break;
		case 4://종료
			return;
		}
		system("cls");
	}
}