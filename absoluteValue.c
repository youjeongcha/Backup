// 절댓값을 구하는 함수를 만드시오
#include <stdio.h>

int Calculation(int input);

int main() {
	int input;
	int output;

	printf("정수를 입력해주십시오 >> ");
	scanf_s("%d", &input);

	output = Calculation(input);

	printf("\n%d의 절댓값 >> %d", input, output);

	return 0;
}

int Calculation(int input) {
	int output = input;
	if (input < 0) { // 음수 > 양수 전환
		output = -output;
	}

	return output;
}