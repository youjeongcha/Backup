#include <stdio.h>
//재귀함수 퀴즈 1,2
//int로 할거면 if와 else 둘다 return 받을 수 있게 //함수가 저절로 끝나는 것은 X

int While(int n)
{//int 함수에는 return 값을 무조건 받아야한다
	if (n <= 0)
	{
		return 0;
	}
	//★귀여운 별 중요
	return n + While(n - 1);
	// While(n-1)이 0부터 해서 누적/ while의 return 값이 다시 return으로 이어짐
}

void Binary(int n)
{
	int i;
	if (n < 2)
	{
		printf("%d", n);
		return;
	}
	else
	{
		//i = n % 2;
		//n /= 2;
		//Binary(n);
		//printf("%d", i);

		//n /= 2;	<-	이게 먼저 반절 깎어버려서 n%2 사용 불가능 이었던거
		Binary(n / 2);
		printf("%d", n % 2);
	}
}

void main()
{
	int input;
	printf("1. 정수 입력 : ");
	scanf("%d", &input);
	printf("1 ~ %d : %d\n", input, While(input));

	//------------
	printf("\n2. 정수 입력 : ");
	scanf("%d", &input);
	printf("%d -> ", input);
	Binary(input);

	return;
}