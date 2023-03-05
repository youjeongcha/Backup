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

void Merge(int sort[], int left, int right, int mid, int type)
{
	int i = left, j = mid + 1, k = 0;
	int tmp[TEN] = { 0 };
	while (i <= mid && j <= right)
	{//�񱳴�� ������ ��������� ����
		if ((type == ASC && sort[i] < sort[j]) || (type == DESC && sort[i] > sort[j]))
			tmp[k++] = sort[i++];
		else
			tmp[k++] = sort[j++];
	}
	while (i <= mid || j <= right) 
		//���ǽ� i�� k�� ������ �迭 ������ �ʰ��ϴ� ��Ȳ�� ���� ���
		//> ���� �迭�� �� ����
	{//���� ���� �� tmp�� ����
		//type�� �� �ص� �Ǵ� ����
		// : ����,����������� ���� ��� 1�� while���� �����صξ��� ������ �״�� tmp��
		if (i > mid)//������ �̹� ���ĵ� ���
			tmp[k++] = sort[j++];
		else//��������
			tmp[k++] = sort[i++];
	}
	for (int i = 0; i < k; i++)
		sort[left++] = tmp[i];
}

void MergeSort(int sort[], int left, int right, int type)
{
	if (left < right)
	{
		//�ּ� ������ ������.
		int mid = (left + right) / 2;
		MergeSort(sort, left, mid, type);
		MergeSort(sort, mid + 1, right, type);
		//�����Ͽ� ��ģ��.
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
		case 1://��ȣ ����
			Createsort(sort);
			break;
		case 2://�������� ����
			MergeSort(sort, 0, TEN - 1, ASC);
			break;
		case 3://�������� ����
			MergeSort(sort, 0, TEN - 1, DESC);
			break;
		case 4://����
			return;
		}
		system("cls");
	}
}