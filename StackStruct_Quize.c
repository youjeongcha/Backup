#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
//Stack은 재귀함수 사용 안 한다
//단일 포인터로 변경하고 Link 받아오지 말기

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
	printf("입력 : ");
}

Stack* Push(Stack* top, int data)
{//이중 포인터 대신에 return을 받아서 하라고
	Stack* temp = NULL;
	temp = (Stack*)malloc(sizeof(Stack));
	temp->data = data;
	temp->Link = top; //메인코드
	top = temp;
	return top; //윗줄 없이 temp를 리턴 해도 가능 
}

Stack* Pop(Stack* top)
{
	int data = 0;
	Stack* temp = NULL;
	if (top != NULL)
	{
		temp = top; //메인 코드1
		data = temp->data;
		printf("Pop : %d\n", data);
		top = top->Link; //메인 코드2
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
	printf("초기화 완료\n");
	return top;
}

void main()
{
	int input;
	int data;
	Stack* top = NULL; //pt에 들어오는게 top이어야 함
	while (1)
	{
		system("cls");
		Menu();
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			printf("데이터 입력 : ");
			scanf("%d", &data);
			top = Push(top, data);
			break;
		case 2:
			if (top != NULL)
				top = Pop(top);
			else
				printf("삭제할 데이터가 없습니다.\n");
			system("pause");
			break;
		case 3:
			top = Release(top);
			return;
		}
	}
}