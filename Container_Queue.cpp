#include<stdio.h>
#include<queue>
//queue ���Լ���
void main()
{
	std::queue<int> iQueue;

	for (int i = 1; i <= 5; i++)
	{
		//inqueue > push //dequeue > pop ��Ī ����
		//front //rear > back
		iQueue.push(i);
		printf("Front : %d\tRear : %d\n", iQueue.front(), iQueue.back());
	}

	printf("\nSize : %d\n\n", iQueue.size());

	while (!iQueue.empty())
	{
		printf("Front : %d\tRear : %d\n", iQueue.front(), iQueue.back());
		iQueue.pop(); //dequeue
	}
}