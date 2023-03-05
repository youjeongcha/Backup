#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>

typedef struct Node
{
	int data;
	struct Node* next;
}Node;

void Menu()
{
	system("cls");
	printf("====Queue System====\n");
	printf("1. Enqueue\n");
	printf("2. Dequeue\n");
	printf("3. Exit\n");
	printf("====================\n");
	printf("�Է� : ");
}

Node* Insert(Node* rear)//�ּ� �ٷ�� �� �ȵǰ� �־���.
{//�ּҷ� ������ �Ǿ��ֱ� ������ front�� rear�� �޴� ������ ����
	Node* NewNode = (Node*)malloc(sizeof(Node));
	printf("������ �Է� : ");
	scanf("%d", &NewNode->data);
	NewNode->next = NULL;
	if (rear != NULL)
	{
		rear->next = NewNode;
	}
	//rear = NewNode; //��� ���� �̰� ������ �Ǵ� ��ó�� ���̴µ� �ʿ���//return�� NewNode�� ������ ���� ����
	//return rear;
	return NewNode;
}

Node* Delete(Node* front)
{
	//Node* DeleteNode = (Node*)malloc(sizeof(Node)); //�̰� ���� �ٷ� front�ٿ������� �Ǵµ�
	//DeleteNode = front;
	Node* DeleteNode = front;
	front = front->next;
	free(DeleteNode);
	system("pause");
	return front;
}

void Show(Node* front, Node* rear)
{
	printf("Front : %d\t", front->data);
	printf("Rear : %d\n", rear->data);
}

void main()
{
	Node* front = NULL;	//���� �Էµ� 
	Node* rear = NULL;	//���߿� �Էµ�

	while (1)
	{
		Menu();
		int select;
		scanf("%d", &select);
		switch (select)
		{
		case 1: //front�� rear�� �����ؾ� �Ѵ�.x �ڵ�
				//�ּҷ� ������ �Ǿ��ֱ� ������ front�� rear�� �޴� ������ ����
			rear = Insert(rear);
			if (front == NULL)
			{
				front = rear;
			}
			Show(front, rear);
			system("pause");
			break;
		case 2:
			if (front == NULL)
			{
				printf("������ �����Ͱ� �����ϴ�.\n");
				system("pause");
				break;
			}
			Show(front, rear);
			front = Delete(front);
			if (front == NULL)
			{
				rear = NULL;
			}
			break;
		case 3:
			while (front != NULL)
			{
				Show(front, rear);
				front = Delete(front);
			}
			printf("������ �����Ͱ� �����ϴ�.\n");
			rear = NULL;
			return;
		}
	}
}