#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<string.h>
#define MAX 50

typedef struct student
{
	char Name[10];
	int Age;
	int Class;
	int Number;
	char Gender[10];
}Student;


void ShowStudent(Student* St) //�ش� �ּ��� ���� ������ �ȴ�.
{
	printf("    ======%s�л�(%d��)======\n", St->Name, St->Number);
	printf("    ���� : %d,  ���� : %s,  �г� : %d\n", St->Age, St->Gender, St->Class);
	printf("    ======================\n");
}

void ShowClass(Student* St[], int Class, int StudentCount)
{
	printf("��������������������%d �г⦡������������������\n", Class);
	for (int i = 0; i < StudentCount; i++)
	{
		if (St[i]->Class == Class)
			ShowStudent(St[i]); //�ٷ� [i]�� �޾Ҵ�
	}
	printf("����������������������������������������������\n");
}

int SetStudent(Student* St, int Number)
{
	St->Number = ++Number;
	printf("======%d�� �л�======\n", St->Number);
	printf("�̸� �Է� : ");
	scanf("%s", St->Name);
	printf("���� �Է� : ");
	scanf("%d", &St->Age);
	printf("���� �Է� : ");
	scanf("%s", St->Gender);
	while (1)
	{
		printf("�г� �Է�(1~3) : ");
		scanf("%d", &St->Class);
		if (St->Class <= 3 && St->Class >= 1)
			break;
		printf("�г� �߸� �Է�(���� 1~3�г�)\n");
		system("pause");
	}
	return Number;
}


void main()
{
	int StudentCount = 0;
	Student* Student_List[MAX] = { 0, };
	int Select;
	char tmp[10]; //

	while (1)
	{
		system("cls");
		printf("=====�л��������α׷�=====(�� �ο� : %d)\n", StudentCount);
		printf("   1.�л� ���\n");
		printf("   2.�л� ���(��ȣ��)\n");
		printf("   3.�л� ���(�г��)\n");
		printf("   4.�г� �˻�\n");
		printf("   5.�л� �˻�\n");
		printf("   6.������ �л� ����\n");
		printf("   7.�л� ��ü ����\n");
		printf("   8.�л����� ����\n");
		printf("   9.�л����� �ҷ�����\n");
		printf("   10.����\n");
		printf("   �Է� : ");
		scanf("%d", &Select);
		switch (Select)
		{
		case 1:
			system("cls");
			if (StudentCount + 1 >= MAX)
			{
				printf("�л�����(%d��)�� ��� á���ϴ�.\n", MAX);
				break;
			}
			Student_List[StudentCount] = (Student*)malloc(sizeof(Student));
			StudentCount = SetStudent(Student_List[StudentCount], StudentCount);
			break;
		case 2:
			system("cls");
			for (int i = 0; i < StudentCount; i++)
				ShowStudent(Student_List[i]);
			break;
		case 3:
			system("cls");
			for (int i = 1; i <= 3; i++)
				ShowClass(Student_List, i, StudentCount);
			break;
		case 4:
			system("cls");
			while (1)
			{
				printf("�˻��� �г� �Է�(1~3) : ");
				scanf("%d", &Select);
				if (Select <= 3 && Select >= 1)
					break;
				printf("�г� �߸� �Է�(���� 1~3�г�)\n");
			}
			ShowClass(Student_List, Select, StudentCount);
			break;
		case 5:
			system("cls");
			printf("�˻��� �̸� �Է� : ");
			scanf("%s", tmp);
			for (int i = 0; i < StudentCount; i++)
			{
				if (strcmp(Student_List[i]->Name, tmp) == 0)
					ShowStudent(Student_List[i]);
			}
			break;
		case 6:
			system("cls");
			if (StudentCount - 1 < 0)
			{
				printf("�� �̻� ������ �л��� �����ϴ�.\n");
				break;
			}
			StudentCount--;
			ShowStudent(Student_List[StudentCount]);
			printf("���� �Ϸ�");
			free(Student_List[StudentCount]);
			Student_List[StudentCount] = NULL;
			break;
		case 7:
			system("cls");
			for (int i = 0; i < StudentCount; i++)
			{
				ShowStudent(Student_List[i]);
				printf("���� �Ϸ�");
				free(Student_List[i]);
				Student_List[i] = NULL;
			}
			StudentCount = 0;
			break;
		case 8:
		{
			FILE* f = fopen("�л�����.txt", "w");
			fprintf(f, "%d\n", StudentCount);
			for (int i = 0; i < StudentCount; i++)
			{
				fprintf(f, "%s %d %s %d\n", Student_List[i]->Name, Student_List[i]->Age, Student_List[i]->Gender, Student_List[i]->Class);
			}
			printf("���� �Ϸ�!!\n");
			fclose(f);
			break;
		}
		case 9:
		{//������ �л� ������ �޸𸮸� �޾� �޸� ũ�⸦ �����ߴ�
			//������ ������ �޸𸮰� ���� ��� �ҷ����⸦ �ϸ�

			FILE* f = fopen("�л�����.txt", "r"); 
			if (f != NULL)
			{//�������� ���� ��� ����ó�� �ݵ�� ���־�� �ԡ�
				for (int i = 0; i < StudentCount; i++)
				{//�����Ҵ� ������ ���� �ʰ� ������ �����Ҵ� �ϱ� ���� �޸� �ּҸ� ã�� �� ���� �ȴ�.
					printf("%s�л� �����Ҵ� ���� �Ϸ�\n", Student_List[i]->Name);
					free(Student_List[i]);
				}

				fscanf(f, "%d", &StudentCount);

				if (StudentCount > MAX)
				{//��� 50���� �ʰ��� ���
					printf("���̻� �л��� �ҷ��� �� �����ϴ�.\n");
					//int overData = StudentCount - MAX; //��ģ ������
					//StudentCount -= overData;
					StudentCount = MAX; //�ٷ� �̷��� �ص� ����
				}

				for (int i = 0; i < StudentCount; i++)
				{
					Student_List[i] = (Student*)malloc(sizeof(Student));
					Student_List[i]->Number = i + 1;
					fscanf(f, "%s", Student_List[i]->Name);
					fscanf(f, "%d", &Student_List[i]->Age);
					fscanf(f, "%s", Student_List[i]->Gender);
					fscanf(f, "%d", &Student_List[i]->Class);
				}
			}
			fclose(f);
			break;
		}
		case 10:
			for (int i = 0; i < StudentCount; i++)
			{
				printf("%s�л� �����Ҵ� ���� �Ϸ�\n", Student_List[i]->Name);
				free(Student_List[i]);
			}
			return;
		}
		system("pause");
	}
}