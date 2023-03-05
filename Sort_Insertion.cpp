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

void Insertion(int sort[], int type)
{
	int tmp, j;
	for (int i = 1; i < TEN; i++)//Tmp����
	{
		tmp = sort[i];
		for (j = i - 1; j >= 0; j--)
		{
			if (type == ASC && (tmp < sort[j]) || type == DESC && (tmp >sort[j]))
				sort[j + 1] = sort[j];//j+1
			else
				break;
		}
		sort[j + 1] = tmp;
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
			Insertion(sort, ASC);
			break;
		case 3://�������� ����
			Insertion(sort, DESC);
			break;
		case 4://����
			return;
		}
		system("cls");
	}
}