// ¦������ Ȧ������ �Ǻ��ϴ� �Լ��� ����ÿ�
#include <stdio.h>

int Calculation(int input);

#define MAX 100000

int main() {
	int input;

	printf("������ �Է��Ͻʽÿ� >> "); // 0 ¦���� ���
	scanf_s("%d", &input);

	int Discri = Calculation(input);

	Discri ? printf("\n¦���Դϴ�") : printf("\nȦ���Դϴ�");

	return 0;
}

int Calculation(int input) {
	int Discri = 0;
	if (input % 2 == 1) { // ¦��
		Discri = 1;
	}

	return Discri;
}