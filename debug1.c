// F10
#include <stdio.h>

int big(int x, int y)
{
	if (x > y) {
		return x;
	}
	else {
		return y;
	}
}

void main()
{
	int num1 = 10;
	int num2 = 20;
	printf("num1 = %\tnum2 = %d\n", num1, num2);
		int bigNum = big(num1, num2);
	printf("가장 큰 수 : %d\n", bigNum);
}