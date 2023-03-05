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
	printf("데이터 입력 : ");
	scanf("%d", &NewNode->Data); //& -> 사용한거. //나는 함수 밖에서 data 끌고왔음
	NewNode->Next = node; //메인코드
	return NewNode;
}

Node* Pop(Node* node)
{
	if (node == NULL)
	{
		printf("삭제할 데이터가 없습니다.\n");
		return node;
	}
	printf("Pop : %d\n", node->Data);
	Node* DeleteNode = node;
	node = node->Next; //메인코드
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
		printf("입력 :");
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
			while (Top != NULL) //pop을 계속 돌림
				Top = Pop(Top);
			return;
		}
	}
}