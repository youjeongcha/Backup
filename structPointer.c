#include <stdio.h>

typedef struct people
{
	char Name[10];
	int Age;
	float Height;
} People;

void ShowPeople(People P)
{
	printf("======================\n");
	printf("1.�̸� : %s\n", P.Name);
	printf("2.���� : %d\n", P.Age);
	printf("3.Ű : %.2f\n", P.Height);
	printf("======================\n");
}

void SefPeople(People* P)
{
	printf("======================\n");
	printf("�̸� �Է� : ");
	scanf("%s", P->Name); //�ּҷ� ���󰡶�*�ε� (*p).Name �� Ʋ�� �� �ƴ����� ���ΰ� ->
	printf("���� �Է� : ");
	scanf("%d", &P->Age); //&
	printf("Ű �Է� : ");
	scanf("%f", &P->Height);
	printf("======================\n");
}

void main()
{
	People P1;
	SefPeople(&P1);
	ShowPeople(P1);
}