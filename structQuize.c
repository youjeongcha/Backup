#include <stdio.h>
#include <Windows.h>v //system�Լ� ����

#define FIVE 5

typedef struct people
{
	char Name[10];
	int Age;
	float Height;
} People;

void ShowPeople(People* P)
{
	for (int i = 0; i < FIVE; i++)
	{
		printf("=======%d=======\n", i + 1);
		printf("�̸� : %s\n", P[i].Name);
		printf("���� : %d\n", P[i].Age);
		printf("Ű : %.2f\n", P[i].Height);
		printf("===============\n");
	}
}

void Arr(People* P)
{
	People temp; //P�� �Է��� ���� ����ִ� �Ű�. temp�� �� ����ü?

	//���� ����, ���� ������ Ű ����
	for (int i = 0; i < FIVE; i++) //1~4
	{
		for (int j = 0; j < i; j++) //0~3
		{
			if ((P[i].Age > P[j].Age) || (P[i].Age == P[j].Age && P[i].Height > P[j].Height))
			{//�̸� ó�� �Ұ�,//ũ�� ���ؼ� ��¸� ���ĵǰ� �ϴ� ��� ��������? ����
				temp = P[i];
				P[i] = P[j];
				P[j] = temp;
			}
		}
	}
}

void main()
{
	People P_List[FIVE];

	for (int i = 0; i < FIVE; i++)
	{
		printf("=======%d=======\n", i + 1);
		printf("�̸� �Է� : ");
		scanf("%s", P_List[i].Name); //�迭�̱⿡ ������
		printf("���� �Է� : ");
		scanf("%d", &P_List[i].Age);
		printf("Ű �Է� : ");
		scanf("%f", &P_List[i].Height);
		printf("===============\n");
	}
	system("cls");

	printf("���� �� ����\n");
	ShowPeople(P_List); //���� �� ���
	system("pause");
	system("cls");

	Arr(P_List); //�������� ����
	ShowPeople(P_List); //���� �� ���
}