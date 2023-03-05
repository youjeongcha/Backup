//1 ~ 입력 받은 숫자 중 3의 배수를 판별하는 함수를 만들어 3의 배수를 모두 출력하시오
#include <stdio.h>

int Calculation(int input, int list[]);

#define MAX 1000

int main() {
	int input;
	int list[MAX];

	do {
		printf("1 이상의 정수를 입력하십시오 >> ");
		scanf_s("%d", &input);
	} while (input <= 0);

	int j = Calculation(input, list);

	printf("\n3의 배수 >>");
	for (int i = 0; i < j; i++) {
		printf(" %d,", list[i]);
	}
	printf("\b");

	return 0;
}

int Calculation(int input, int list[]) {
	int j = 0;
	for (int i = 3; i <= input; i++) {
		if (i % 3 == 0) { // 3 배수 판별
			list[j] = i;
			j++;
		}		
	}

	return j;
}