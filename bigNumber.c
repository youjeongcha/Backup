//두 수를 입력 받아 큰 수를 출력하는 함수를 만드시오
#include <stdio.h>

int Calculation(int first, int second);

int main() {
	int first, second;

	printf("정수 두개를 입력해주십시오 >> ");
	scanf_s("%d%d", &first, &second);

	first = Calculation(first, second);

	printf("\n큰 수 >> %d", first);

	return 0;
}

int Calculation(int first, int second) {
	if (first < second) {
		first = second;
	}

	return first;
}