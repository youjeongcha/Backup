// 짝수인지 홀수인지 판별하는 함수를 만드시오
#include <stdio.h>

int Calculation(int input);

#define MAX 100000

int main() {
	int input;

	printf("정수를 입력하십시오 >> "); // 0 짝수로 취급
	scanf_s("%d", &input);

	int Discri = Calculation(input);

	Discri ? printf("\n짝수입니다") : printf("\n홀수입니다");

	return 0;
}

int Calculation(int input) {
	int Discri = 0;
	if (input % 2 == 1) { // 짝수
		Discri = 1;
	}

	return Discri;
}