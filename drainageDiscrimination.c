//1 ~ �Է� ���� ���� �� 3�� ����� �Ǻ��ϴ� �Լ��� ����� 3�� ����� ��� ����Ͻÿ�
#include <stdio.h>

int Calculation(int input, int list[]);

#define MAX 1000

int main() {
	int input;
	int list[MAX];

	do {
		printf("1 �̻��� ������ �Է��Ͻʽÿ� >> ");
		scanf_s("%d", &input);
	} while (input <= 0);

	int j = Calculation(input, list);

	printf("\n3�� ��� >>");
	for (int i = 0; i < j; i++) {
		printf(" %d,", list[i]);
	}
	printf("\b");

	return 0;
}

int Calculation(int input, int list[]) {
	int j = 0;
	for (int i = 3; i <= input; i++) {
		if (i % 3 == 0) { // 3 ��� �Ǻ�
			list[j] = i;
			j++;
		}		
	}

	return j;
}