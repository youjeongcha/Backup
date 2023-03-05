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
	int tmp;
	for (int i = TEN - 1; i > 0; i--)//��ü ��ȸ �ݺ�
	{
		for (int j = 0; j < i; j++)//��ȸ
		{
			if (type == ASC && (sort[j] > sort[j + 1]) || type == DESC && (sort[j] < sort[j + 1]))
			{
				tmp = sort[j];
				sort[j] = sort[j+1];
				sort[j+1] = tmp;
			}	
		}
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