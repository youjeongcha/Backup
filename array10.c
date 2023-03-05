#include <stdio.h>

#define MAX 10

int main()
{
	int num[MAX], temp;
	float sum = 0;

	for (int i = 0; i < MAX; i++)
	{
		printf("[%d]번째 정수 입력 : ", i + 1);
		scanf_s("%d", &num[i]);
		sum += num[i];
	}
	for (int i = 0; i < MAX- 1; i++)
	{
		if (num[i] > num[i + 1])
		{
			temp = num[i + 1];
			num[i + 1] = num[i];
			num[i] = temp;
		}
	}

	printf("최대값 = %d  총합 = %.0f  평균 = %.3f", num[MAX - 1], sum, sum / MAX);

	return 0;
}