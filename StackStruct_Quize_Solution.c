#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>

typedef struct Node
{
	int Data;
	struct Node* Next;
}Node;

Node* Push(Node* node)
{
	Node* NewNode = (Node*)malloc(sizeof(Node));
	printf("������ �Է� : ");
	scanf("%d", &NewNode->Data); //& -> ����Ѱ�. //���� �Լ� �ۿ��� data ��������
	NewNode->Next = node; //�����ڵ�
	return NewNode;
}

Node* Pop(Node* node)
{
	if (node == NULL)
	{
		printf("������ �����Ͱ� �����ϴ�.\n");
		return node;
	}
	printf("Pop : %d\n", node->Data);
	Node* DeleteNode = node;
	node = node->Next; //�����ڵ�
	free(DeleteNode);
	return node;

}

void main()
{
	Node* Top = NULL;

	while (1)
	{
		system("cls");
		printf("====Stack System====\n");
		printf("1. Push\n");
		printf("2. Pop\n");
		printf("3. Exit\n");
		printf("====================\n");
		printf("�Է� :");
		int Select;
		scanf("%d", &Select);
		switch (Select)
		{
		case 1:
			Top = Push(Top);
			break;
		case 2:
			Top = Pop(Top);
			system("pause");
			break;
		case 3:
			while (Top != NULL) //pop�� ��� ����
				Top = Pop(Top);
			return;
		}
	}
}