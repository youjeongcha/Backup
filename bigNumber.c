//�� ���� �Է� �޾� ū ���� ����ϴ� �Լ��� ����ÿ�
#include <stdio.h>

int Calculation(int first, int second);

int main() {
	int first, second;

	printf("���� �ΰ��� �Է����ֽʽÿ� >> ");
	scanf_s("%d%d", &first, &second);

	first = Calculation(first, second);

	printf("\nū �� >> %d", first);

	return 0;
}

int Calculation(int first, int second) {
	if (first < second) {
		first = second;
	}

	return first;
}