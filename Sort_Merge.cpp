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

void Merge(int sort[], int left, int right, int mid, int type)
{
	int i = left, j = mid + 1, k = 0;
	int tmp[TEN] = { 0 };
	while (i <= mid && j <= right)
	{//비교대상 한쪽이 끝나기까지 정렬
		if ((type == ASC && sort[i] < sort[j]) || (type == DESC && sort[i] > sort[j]))
			tmp[k++] = sort[i++];
		else
			tmp[k++] = sort[j++];
	}
	while (i <= mid || j <= right) 
		//조건식 i와 k가 지정된 배열 범위를 초과하는 상황이 생길 경우
		//> 한쪽 배열이 다 끝남
	{//남은 한쪽 다 tmp로 정렬
		//type비교 안 해도 되는 이유
		// : 오름,내림차순대로 앞전 재귀 1번 while에서 정렬해두었기 때문에 그대로 tmp로
		if (i > mid)//왼쪽이 이미 정렬된 경우
			tmp[k++] = sort[j++];
		else//오른쪽이
			tmp[k++] = sort[i++];
	}
	for (int i = 0; i < k; i++)
		sort[left++] = tmp[i];
}

void MergeSort(int sort[], int left, int right, int type)
{
	if (left < right)
	{
		//최소 단위로 나눈다.
		int mid = (left + right) / 2;
		MergeSort(sort, left, mid, type);
		MergeSort(sort, mid + 1, right, type);
		//정렬하여 합친다.
		Merge(sort, left, right, mid, type);
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
			MergeSort(sort, 0, TEN - 1, ASC);
			break;
		case 3://내림차순 정렬
			MergeSort(sort, 0, TEN - 1, DESC);
			break;
		case 4://종료
			return;
		}
		system("cls");
	}
}