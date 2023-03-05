#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
//Stack�� ����Լ� ��� �� �Ѵ�
//���� �����ͷ� �����ϰ� Link �޾ƿ��� ����

typedef struct Stack
{
	int data;
	struct Stack* Link;
} Stack;

void Menu()
{
	printf("====Stack System====\n");
	printf("1.Push\n");
	printf("2.Pop\n");
	printf("3.Exit\n");
	printf("====================\n");
	printf("�Է� : ");
}

Stack* Push(Stack* top, int data)
{//���� ������ ��ſ� return�� �޾Ƽ� �϶��
	Stack* temp = NULL;
	temp = (Stack*)malloc(sizeof(Stack));
	temp->data = data;
	temp->Link = top; //�����ڵ�
	top = temp;
	return top; //���� ���� temp�� ���� �ص� ���� 
}

Stack* Pop(Stack* top)
{
	int data = 0;
	Stack* temp = NULL;
	if (top != NULL)
	{
		temp = top; //���� �ڵ�1
		data = temp->data;
		printf("Pop : %d\n", data);
		top = top->Link; //���� �ڵ�2
		free(temp);
	}
	return top;
}

Stack* Release(Stack* top)
{
	while (top != NULL)
	{
		Stack* temp = NULL;
		temp = top;
		top = top->Link;
		free(temp);
	}
	printf("�ʱ�ȭ �Ϸ�\n");
	return top;
}

void main()
{
	int input;
	int data;
	Stack* top = NULL; //pt�� �����°� top�̾�� ��
	while (1)
	{
		system("cls");
		Menu();
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			printf("������ �Է� : ");
			scanf("%d", &data);
			top = Push(top, data);
			break;
		case 2:
			if (top != NULL)
				top = Pop(top);
			else
				printf("������ �����Ͱ� �����ϴ�.\n");
			system("pause");
			break;
		case 3:
			top = Release(top);
			return;
		}
	}
}