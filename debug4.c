// F5. F9
#include <stdio.h>

int show(int num1, int num2)
{
	int sum = 0;
	int temp;

	if (num1 < num2) { //num1에 큰수가 들어가게
		temp = num2;
		num2 = num1;
		num1 = temp;
	}

	while (num1 >= num2)
	{ // 수정 들어감
		sum += num2++;
		printf("%d\n", sum);

	}
	return sum;
}

void main()
{
	int num1, num2;
	printf("num1 정수 입력 : ");
	scanf("%d", &num1);
	printf("num2 정수 입력 : ");
	scanf("%d", &num2);
	printf("sum : %d", show(num1, num2));

}