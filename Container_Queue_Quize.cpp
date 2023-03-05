#include<stdio.h>
#include<queue>
//���Լ���

//inqueue > push //dequeue > pop ��Ī ����
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
	printf("�Է� : ");
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
				printf("������ �����Ͱ� �����ϴ�.\n");
				break;
			}
			printf("Front : %d\tRear : %d\n", iQueue.front(), iQueue.back());
			iQueue.pop();
			break;
		case 3:
			while (!iQueue.empty())//�� ��� ���� �� ������
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