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

void Show(Student* St[], int i)
{
	printf("  ======%s �л�(%d��)======\n", St[i]->Name, St[i]->Number);
	printf("  ���� : %d,  ���� : %s,  �г� : %d\n", St[i]->Age, St[i]->Gender, St[i]->Class);
	printf("  ======================\n");
}

void ShowClass(Student* St[], int StudentCount, int input)
{
	printf("��������������������%d �г⦡������������������\n", input);
	for (int i = 0; i < StudentCount; i++)
	{
		if (St[i]->Class == input) {
			Show(St, i);
		}
	}
	printf("����������������������������������������������\n");
}

void NumShowStudent(Student** St, int StudentCount) //or Student* St[MAX]�� �� ���� ���·� �޾Ƶ� �Ǵ°�
{//Student List�� ó���� �����ͷ� �ּҸ� �޾ұ⿡ ���� �����ͷ� �ؾ� ��
	//�Ϲ� ������ �׳� ������/ �����ͷ� ������ ���� ������/ ���� �����ͷ� ������ ����
	for (int i = 0; i < StudentCount; i++)
	{
		Show(St, i);
	}
}

void ClassShowStudent(Student** St, int StudentCount)
{
	Student tmp;
	for (int j = 0; j < 3; j++)
	{
		ShowClass(St, StudentCount, j + 1);
	}
}

int SetStudent(Student* St, int StudentCount)
{//Student List[]�� ���� �޾Ҵµ� �׾ȿ� �ּҰ��� �� ������
	St->Number = ++StudentCount;
	printf("======%d�� �л�======\n", St->Number);
	printf("�̸� �Է� : ");
	scanf("%s", St->Name);
	printf("���� �Է� : ");
	scanf("%d", &St->Age);
	printf("���� �Է� : ");
	scanf("%s", St->Gender);
	do
	{
		printf("�г� �Է�(1~3) : ");
		scanf("%d", &St->Class);
		if (St->Class == 1 || St->Class == 2 || St->Class == 3)
		{
			break;
		}
		printf("�г� �߸� �Է�(���� 1~3�г�)\n");
		system("pause");

	} while (St->Class <= 0 || St->Class > 3);

	return StudentCount;
}

void SarchGrade(Student** St, int StudentCount)
{
	int input = 0;
	do
	{
		printf("�˻��� �г� �Է�(1~3) : ");
		scanf("%d", &input);
		if (input == 1 || input == 2 || input == 3)
		{
			break;
		}
		printf("�г� �߸� �Է�(���� 1~3�г�)\n");
		system("pause");

	} while (input <=0 || input > 3);

	ShowClass(St, StudentCount, input);
}

void SarchStudent(Student** St, int StudentCount)
{
	char input[10];
	printf("�˻��� �̸� �Է� : ");
	scanf("%s", &input);

	for (int i = 0; i < StudentCount; i++)
	{
		if (strcmp(St[i]->Name, input) == 0)
		{
			printf("��������������������%d �г⦡������������������\n", i + 1);
			Show(St, i);
			printf("����������������������������������������������\n");
		}
	}
}

int DeletFinal(Student** St, int StudentCount)
{
	printf("\n\n");
	StudentCount--;
	Show(St, StudentCount);
	free(St[StudentCount]);
	St[StudentCount] = NULL;
	printf("���� �Ϸ�\n");
	return StudentCount;
}

int DeletTotal(Student** St, int StudentCount)
{
	int tempStudent = StudentCount;
	printf("\n\n");
	for (int i = 0; i < tempStudent; i++)
	{
		Show(St, i);
		free(St[i]);
		St[i] = NULL;
	}
	printf("���� �Ϸ�\n");
	return 0;
}


void main()
{
	Student* Student_List[MAX]; //�����Ҵ� ���� �ڸ��� ���� //�迭 �ȿ� �ּҰ� ����ִ�.
	int Select;
	int StudentCount = 0;

	while (1)
	{
		system("cls");
		printf("=====�л��������α׷�=====(�� �ο� : %d)\n", StudentCount);
		printf("  1.�л� ���\n");
		printf("  2.�л� ���(��ȣ��)\n");
		printf("  3.�л� ���(�г��)\n");
		printf("  4.�г� �˻�\n");
		printf("  5.�л� �˻�\n");
		printf("  6.������ �л� ����\n");
		printf("  7.��ü �л� ����\n");
		printf("  8.����\n");
		printf("  �Է� : ");
		scanf("%d", &Select);

		switch (Select)
		{
		case 1: //�л� ���
			system("cls");
			if (StudentCount + 1 >= MAX)
			{ 
				printf("�л�����(50��)�� ��� á���ϴ�.\n");
				break;
			}
			Student_List[StudentCount] = (Student*)malloc(sizeof(Student)); //�����Ҵ� ���� ��ŭ �����Ҵ� ������ ����� �� 71
			StudentCount = SetStudent(Student_List[StudentCount], StudentCount); //
			system("pause");
			break;
		case 2: //�л� ���(��ȣ��)
			system("cls");
			NumShowStudent(Student_List, StudentCount);
			system("pause");
			break;
		case 3: //�л� ���(�г��)
			system("cls");
			ClassShowStudent(Student_List, StudentCount);
			system("pause");
			break;
		case 4: //�г� �˻�
			system("cls");
			SarchGrade(Student_List, StudentCount);
			system("pause");
			break;
		case 5: //�л� �˻�
			system("cls");
			SarchStudent(Student_List, StudentCount);
			system("pause");
			break;
		case 6: //������ �л� ����
			StudentCount = DeletFinal(Student_List, StudentCount);
			system("pause"); //
			break;
		case 7: //��ü �л� ����
			StudentCount = DeletTotal(Student_List, StudentCount);
			system("pause"); //
			break;
		case 8: //����
			for (int i = 0; i < StudentCount; i++)
			{
				free(Student_List[i]); //�����Ҵ� ���� ��ŭ �����Ҵ� ������ ����� ��
				Student_List[i] = NULL;
			}
			return;
		}
	}
}