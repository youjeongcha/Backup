#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#define MAX 50

typedef struct student
{
	char Name[10];
	int Age;
	int Class;
	int Number;
	char Gender[10];
}Student;

void ShowStudent(Student* St)
{
	printf("======%s�л�(%d��)======\n", St->Name, St->Number);
	printf("���� : %d,  ���� : %s,  �г� : %d\n", St->Age, St->Gender, St->Class);
	printf("======================\n");
}
int SetStudent(Student* St, int StudentCount)
{
	St->Number = ++StudentCount;
	printf("======%d�� �л�======\n", St->Number);
	printf("�̸� �Է� : ");
	scanf("%s", St->Name);
	printf("���� �Է� : ");
	scanf("%d", &St->Age);
	printf("���� �Է� : ");
	scanf("%s", St->Gender);
	printf("�г� �Է� : ");
	scanf("%d", &St->Class);
	return StudentCount;
}

void main()
{
	Student* Student_List[MAX]; //�����Ҵ� ���� �ڸ��� ����
	int Select;
	int StudentCount = 0;

	while (1)
	{
		system("cls");
		printf("=====�л��������α׷�=====(�� �ο� : %d)\n", StudentCount);
		printf("1.�л� ���\n");
		printf("2.�л� ���\n");
		printf("3.����\n");
		printf("�Է� : ");
		scanf("%d", &Select);
		switch (Select)
		{
		case 1:
			if (StudentCount + 1 >= MAX)
			{
				printf("�л�����(50��)�� ��� á���ϴ�.\n");
				break;
			}
			Student_List[StudentCount] = (Student*)malloc(sizeof(Student)); //�����Ҵ� ���� ��ŭ �����Ҵ� ������ ����� �� 71
			//�ٸ� ���� ��� ���Ѹ�ŭ ����Ʈ �޾Ƽ�
			StudentCount = SetStudent(Student_List[StudentCount], StudentCount);
			break;
		case 2:
			for (int i = 0; i < StudentCount; i++)
				ShowStudent(Student_List[i]);
			break;
		case 3:
			for (int i = 0; i < StudentCount; i++)
			{
				printf("%s�л� �����Ҵ� ���� �Ϸ�\n", Student_List[i]->Name);
				free(Student_List[i]); //�����Ҵ� ���� ��ŭ �����Ҵ� ������ ����� �� 59
			}
			return;
		}
		system("pause");
	}
}