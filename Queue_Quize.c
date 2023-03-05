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
	printf("입력 : ");
}

Node* Insert(Node* rear)//주소 다루는 게 안되고 있었다.
{//주소로 연결이 되어있기 때문에 front와 rear가 받는 정보가 같음
	Node* NewNode = (Node*)malloc(sizeof(Node));
	printf("데이터 입력 : ");
	scanf("%d", &NewNode->data);
	NewNode->next = NULL;
	if (rear != NULL)
	{
		rear->next = NewNode;
	}
	//rear = NewNode; //답안 보면 이거 지워도 되는 거처럼 보이는데 필요함//return을 NewNode로 받으면 생략 가능
	//return rear;
	return NewNode;
}

Node* Delete(Node* front)
{
	//Node* DeleteNode = (Node*)malloc(sizeof(Node)); //이거 없이 바로 front붙여버려도 되는듯
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
	Node* front = NULL;	//먼저 입력된 
	Node* rear = NULL;	//나중에 입력된

	while (1)
	{
		Menu();
		int select;
		scanf("%d", &select);
		switch (select)
		{
		case 1: //front와 rear를 연결해야 한다.x 자동
				//주소로 연결이 되어있기 때문에 front와 rear가 받는 정보가 같음
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
				printf("삭제할 데이터가 없습니다.\n");
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
			printf("삭제할 데이터가 없습니다.\n");
			rear = NULL;
			return;
		}
	}
}