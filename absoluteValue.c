// ������ ���ϴ� �Լ��� ����ÿ�
#include <stdio.h>

int Calculation(int input);

int main() {
	int input;
	int output;

	printf("������ �Է����ֽʽÿ� >> ");
	scanf_s("%d", &input);

	output = Calculation(input);

	printf("\n%d�� ���� >> %d", input, output);

	return 0;
}

int Calculation(int input) {
	int output = input;
	if (input < 0) { // ���� > ��� ��ȯ
		output = -output;
	}

	return output;
}