// 입력 받은 수를 거꾸로 출력하는 함수를 만드시오
#include <stdio.h>

int share_10(int input);
int division_10(int input);

int main() {
	int input, temp; // temp - 이용하는 숫자

	printf("하나의 정수를 입력하시오 >> ");
	scanf_s("%d", &input);

	while(input > 0) {

		temp = share_10(input);
		printf("%d", temp);
		input = division_10(input);
	}

	return 0;
}

int share_10(int input) {
	int temp;
	temp = input % 10;

	return temp;
}

int division_10(int input) {
	input /= 10;

	return input;
}