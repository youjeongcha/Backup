#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>

typedef struct Node
{
	int Data;
	struct Node* Link;
}Node;

Node* Enqueue(Node* Rear)
{
	Node* NewNode = (Node*)malloc(sizeof(Node));
	printf("데이터 입력 : ");
	scanf("%d", &NewNode->Data);
	NewNode->Link = NULL;
	if (Rear != NULL)
		Rear->Link = NewNode;
	return NewNode;
}

Node* Dequeue(Node* Front)
{
	if (Front == NULL)
	{
		printf("삭제할 데이터가 없습니다.\n");
		return Front;
	}
	Node* DeleteNode = Front;
	Front = Front->Link;
	free(DeleteNode);
	return Front;

}

void main()
{
	Node* Front = NULL;
	Node* Rear = NULL;

	while (1)
	{
		system("cls");
		printf("====Queue System====\n");
		printf("1. Enqueue\n");
		printf("2. Dequeue\n");
		printf("3. Exit\n");
		printf("====================\n");
		printf("입력 :");
		int Select;
		scanf("%d", &Select);
		switch (Select)
		{
		case 1:
			Rear = Enqueue(Rear);
			if (Front == NULL)
				Front = Rear;
			printf("Front : %d\tRear : %d\n", Front->Data, Rear->Data);
			system("pause");
			break;
		case 2:
			Front = Dequeue(Front);
			if (Front == NULL)
				Rear = NULL;
			else
				printf("Front : %d\tRear : %d\n", Front->Data, Rear->Data);
			system("pause");
			break;
		case 3:
			while (Front != NULL)
				Front = Dequeue(Front);
			return;
		}
	}
}