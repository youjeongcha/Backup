#include <stdio.h>
#include <Windows.h> //system("cls");
#include <stdlib.h> //�����Ҵ� malloc

typedef struct Point
{
	int number;
	int x, y;
	struct Point* Next; //next�� �ּ� *Point�� �ϸ� ���� ������ //����ü��� ���ĸ�� ����ü �̸��� �ϳ��� ���
}Point;

void Menu(int icount)
{
	printf("��ǥ ���� = %d\n", icount);
	printf("1.��ǥ�߰�\n");
	printf("2.��ǥ����\n");
	printf("3.����\n");
	printf("�Է� = ");
}

void Release(Point* Node)
{//1234321�� ���ƿ��� ������ 4���� �����Ҵ� ����. 1���� �ϸ� �ڿ� �ּ� �� ����
	if (Node == NULL)
		return;
	Release(Node->Next); //1234�� ��

	printf("%d��° ��ǥ �޸� ����\n", Node->number);
	free(Node); //4321������ �濡 ����
}

Point* Insert(Point* pt, int count) //�Լ� ������ ����ü�� �ϰ� *������ ���̴°� - �����ͷ� �޴� �� �°� Next�� ���� ������?
{//�ڹ�ȯ�ڷ������� ������ �ޱ� �������� Point* pt�� �ޱ� ���ؼ��� �����ؾ� ��
	if (pt == NULL)
	{
		pt = (Point*)malloc(sizeof(Point)); //�����Ҵ��� �� ��ǥ����
		printf("x = ");
		scanf("%d", &pt->x); //&pt->x�� �ּҿ� �޴� �� ���� ���ڴ� �ּҸ� �����ؼ� �޴´�.
		printf("y = ");
		scanf("%d", &pt->y);
		pt->number = count;
		pt->Next = NULL; //���� pt�� �ּҿ� �ִ� ������ ���� ����ش�
	}
	else //next�� ���� pt�� �ּҸ� �����ϴµ�. ������ �Է¹��� �ּҰ� ������ ���� �ּҷ� �Ѿ�� �ڵ�
		pt->Next = Insert(pt->Next, count);
	return pt;
}

void Print(Point* pt)
{
	if (pt == NULL)
		return;
	printf("%d��° ��ǥ\nx = %d\ny = %d\n", pt->number, pt->x, pt->y);
	printf("=======================\n\n");
	Print(pt->Next);
}

void main()
{
	int icount = 0; //��ǥ�� ��
	int num;
	Point* pt = NULL; //��ǥ ���� //Point �̸����� �޴� �� ����
	while (1)
	{
		system("cls");
		Menu(icount);
		scanf("%d", &num);
		switch (num)
		{
		case 1: //��ǥ �߰�
			icount++;
			pt = Insert(pt, icount);
			break;
		case 2: //��ǥ����
			Print(pt);
			system("pause");
			break;
		case 3: //����
			Release(pt);
			return;
		}
	}
}

/* 31��° ��
count 1
1�� next�� null

count12
1�� next�� 2�� �ּ�
2�� next�� null

����Լ� ���� �����°�
123�̷��� ���� �������� next�� ����ִ� null�� ������
if������ ���� ���� �ް�
����Լ� Ǯ�鼭 �����µ�
3�� null
2�� 3�� �ּ�
1�� 2�� �ּҸ�
return���� �����鼭 ���´�.*/