#include <stdio.h>
//typedef
struct people
{
	char Name[10]; //��� ����
	int Age;
	float Height;
};

typedef struct people People; //define�� �޶� ;����� �� define�� ;���� ���� ����

void main()
{
	People P1 = { "����ȣ",20,185.7f }; //�ڷ����� ������ �ٿ��� ����.//�Ҽ����׳� ���� double�� �Ǳ� ������ f�ٿ���� float
	printf("�̸� = %s\n���� = %d\nŰ = %.2f\n", P1.Name, P1.Age, P1.Height); //������� ���� ������
}