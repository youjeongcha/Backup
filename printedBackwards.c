// �Է� ���� ���� �Ųٷ� ����ϴ� �Լ��� ����ÿ�
#include <stdio.h>

int share_10(int input);
int division_10(int input);

int main() {
	int input, temp; // temp - �̿��ϴ� ����

	printf("�ϳ��� ������ �Է��Ͻÿ� >> ");
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