#include<stdio.h>
#include<queue>
//선입선출

//inqueue > push //dequeue > pop 명칭 통일
//front //rear
//pop(); //dequeue

int Manu()
{
	int input;
	printf("====Queue System====\n");
	printf("1. Enqueue\n");
	printf("2. Dequeue\n");
	printf("3. Exit\n");
	printf("====================\n");
	printf("입력 : ");
	scanf("%d", &input);
	return input;
}

void main()
{
	std::queue<int> iQueue;
	int input;

	while (true)
	{
		switch (Manu())
		{
		case 1:
			printf("Push : ");
			scanf("%d", &input);
			iQueue.push(input);
			printf("Front : %d\tRear : %d\n", iQueue.front(), iQueue.back());
			break;
		case 2:
			if (iQueue.empty())
			{
				printf("삭제할 데이터가 없습니다.\n");
				break;
			}
			printf("Front : %d\tRear : %d\n", iQueue.front(), iQueue.back());
			iQueue.pop();
			break;
		case 3:
			while (!iQueue.empty())//안 비어 있을 때 돌린다
			{
				printf("Front : %d\tRear : %d\n", iQueue.front(), iQueue.back());
				iQueue.pop();
			}
			return;
		}
		system("pause");
		system("cls");
	}
}