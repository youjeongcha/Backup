#include <stdio.h>

struct people
{
	char Name[10]; //��� ����
	int Age;
	float Height;
};

void main()
{
	struct people P1 = { "����ȣ",20,185.7f}; //�ڷ����� ������ �ٿ��� ����.//�Ҽ����׳� ���� double�� �Ǳ� ������ f�ٿ���� float
	printf("�̸� = %s\n���� = %d\nŰ = %.2f\n", P1.Name, P1.Age, P1.Height); //������� ���� ������
}