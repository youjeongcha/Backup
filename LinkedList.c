#include<stdio.h>
#include<Windows.h> //system("cls")
#include<stdlib.h> //�����Ҵ� malloc

typedef struct Infomation
{
	char name[10];
	int age;
	char address[20];
	int Korean;
	int English;
	int math;
	int sum;
	float average;
	char grade;
	struct Infomation* Next;
}Infomation;

void Menu()
{
	printf("<<<==== �޴� ====>>>\n\n");
	printf("1.�л� ���\n");
	printf("2.�л� �˻�\n");
	printf("3.�л� ���\n");
	printf("4.�л� ����\n");
	printf("5.�л� ����\n");
	printf("6.����\n");
	printf("���� : ");
}

char Grade(float average)
{
	int grade = (int)average;
	if (grade >= 90)
	{
		return 'A';
	}
	else if (grade >= 80)
	{
		return 'B';
	}
	else if (grade >= 70)
	{
		return 'C';
	}
	else if (grade >= 60)
	{
		return 'D';
	}
	else
	{
		return 'F';
	}
}

Infomation* Insert(Infomation* info)
{
	if (info == NULL)
	{//ó�� ����
		info = (Infomation*)malloc(sizeof(Infomation));
		printf("�л� �̸� �Է� : ");
		scanf("%s", info->name);
		printf("%s �л� ���� �Է� : ", info->name);
		scanf("%d", &info->age);
		printf("%s �л� �ּ� �Է� : ", info->name);
		scanf("%s", info->address);
		printf("%s �л� ���� ���� : ", info->name);
		scanf("%d", &info->Korean);
		printf("%s �л� ���� ���� : ", info->name);
		scanf("%d", &info->English);
		printf("%s �л� ���� ���� : ", info->name);
		scanf("%d", &info->math);
		info->sum = (info->Korean + info->English + info->math);
		info->average = (info->Korean + info->English + info->math) / 3;
		info->grade = Grade(info->average);
		printf("�л� ���� �Է� �Ϸ�\n");
		info->Next = NULL;
	}
	else
		info->Next = Insert(info->Next);
	return info;
}

Infomation* SelfSearch(Infomation* info, char* input) //��� ��쿡�� ���� �޾ƾ� ��
{
	if (info == NULL)
	{//�˻������ ���� ��
		return info;
	}
	else if (strcmp(input, info->name) == 0)
	{//���ڿ� �� < ���� ��Ⱥ ��� ��ȯ == 0 ��ȯ
		return info;
	}
	else
	{
		return SelfSearch(info->Next, input); //����
	}
}

void information(Infomation* info)
{
	printf("<<<===== information =====>>>\n");
	printf("�л� �̸� : %s\n", info->name);
	printf("�л� ���� : %d ��\n", info->age);
	printf("�л� �ּ� : %s\n", info->address);
	printf("���� ���� : %d ��\n", info->Korean);
	printf("���� ���� : %d ��\n", info->English);
	printf("���� ���� : %d ��\n", info->math);
	printf("�հ� ���� : %d ��\n", info->sum);
	printf("��� ���� : %.2f ��\n", info->average);
	printf("�л� ��� : %c ���\n", info->grade);
}

void Search(Infomation* info)
{
	char input[10];
	scanf("%s", input);

	info = SelfSearch(info, input);

	if (info == NULL)
	{
		printf("�˻��ϰ��� �ϴ� �л��� �������� �ʽ��ϴ�.\n");
		return;
	}

	printf("�л� ���� �˻� �Ϸ�\n");
	information(info);
}

void SelfList(Infomation* info)
{
	if (info == NULL)
	{//�˻������ ���� ��
		return;
	}
	else
	{
		printf("\t\t%s\t\t%d\t\t%s\n", info->name, info->age, info->address);
		SelfList(info->Next);
	}
}

void List(Infomation* info)
{
	printf("<<<===== information =====>>>\n\n");
	printf("\t �л��̸�\t �л�����\t �л��ּ�\n");
	SelfList(info);
	printf("(�л� �������� ������ �˻��� �̿��ϼ��� !!)\n");
}

void Modify(Infomation* info)
{//�ּҸ� �����ϴ� �� �ƴ϶� �ּ� ���� ������ �����ϴ� ���̱⿡ void�� ���. //�߿�
	char input[10];
	int select;
	char temp[10];
	Infomation* change = NULL;

	printf("������ �л� �̸���?\n");
	scanf("%s", input);
	change = SelfSearch(info, input);
	//info�� �ּҿ�change�� �ּҰ� �����ϸ� ���� �ٲ��. //���� �߿�

	system("cls");

	while (1)
	{
		if (change == NULL)
		{
			system("cls");
			printf("ã�� �л��� �����ϴ�.\n");
			return;
		}
		information(change);
		printf("\n\n������ �׸��� ���� �Ͻÿ�\n");
		printf("1.�̸�  2.����  3.�ּ�  4.����  5.��������\n");
		printf("���� : ");
		scanf("%d", &select);
		switch (select)
		{
		case 1:
		{
			strcpy(temp, info->name);
			printf("���� �̸� : %s\n", change->name);
			printf("������ �̸� : ");
			scanf("%s", change->name);
			printf("%s -> %s �� �̸� ���� �Ϸ�\n", temp, change->name);
			break;
		}
		case 2:
		{
			int temp = info->age;
			printf("���� ���� : %d ��\n", change->age);
			printf("������ ���� : ");
			scanf("%d", &change->age);
			printf("\b��\n%d -> %d �� �� ���� ���� �Ϸ�\n", temp, change->age);
			//scanf �ڿ� ���� ���̴� ���????
			break;
		}
		case 3:
		{
			char temp[10];
			strcpy(temp, info->address);
			printf("���� �ּ� : %s\n", change->address);
			printf("������ �ּ� : ");
			scanf("%s", change->address);
			printf("%s -> %s �� �ּ� ���� �Ϸ�\n", temp, change->address);
			break;
		}
		case 4:
		{
			printf("���� ����\n");
			printf("���� : %d ���� : %d ���� : %d\n", change->Korean, change->English, change->math);
			printf("������ ���� ���� : ");
			scanf("%d", &change->Korean);
			printf("������ ���� ���� : ");
			scanf("%d", &change->English);
			printf("������ ���� ���� : ");
			scanf("%d", &change->math);
			info->sum = (info->Korean + info->English + info->math);
			info->average = (info->Korean + info->English + info->math) / 3;
			printf("���� ���� �Ϸ�\n");
			break;
		}
		case 5:
		{
			printf("������ �����մϴ�\n");
			return;
		}
		}
		system("pause");
		system("cls");
	}
}

Infomation* SelfDelete(Infomation* info, char* input)
{//�˻� ��� ������ ���� ���Ϲ޾Ƽ�
	//Infomation* temp = NULL; //�Է� �޴� �� ���� �͵� �޾ƿ´�.
	if (info != NULL)
	{//�˻������ ���� ��
		if (strcmp(input, info->name) == 0) //�� ��
		{//���ڿ� �� < ���� ��Ⱥ ��� ��ȯ == 0 ��ȯ
			info = info->Next;
			return info;
		}
		info->Next = SelfDelete(info->Next, input);
		return info;
	}
	else
	{
		printf("�ش� �л��� �������� �ʽ��ϴ�.\n");
		return info;
	}
}

Infomation* Delete(Infomation* info)
{
	char input[10];
	if (info == NULL)
	{//�л��� �ƿ� �������� ������
		printf("������ �л��� �������� �ʽ��ϴ�.\n");
		return info;
	}
	printf("������ �л� �̸� : ");
	scanf("%s", input);
	info = SelfDelete(info, input);
	return info;
}

void Exit(Infomation* info)
{
	if (info == NULL)
		return;
	Exit(info->Next);
	free(info); //�� ������ �Է��� �ͺ��� ����
}

void main()
{
	int input;
	Infomation* info = NULL;
	while (1)
	{
		system("cls");
		Menu();
		scanf("%d", &input);
		system("cls");
		switch (input)
		{
		case 1: //�л� ���
			info = Insert(info);
			system("pause");
			break;
		case 2: //�л� �˻�
			printf("�˻��� �̸� �Է� : ");
			Search(info);
			system("pause");
			break;
		case 3: //�л� ���
			List(info);
			system("pause");
			break;
		case 4: //�л� ����
			Modify(info);
			system("pause");
			break;
		case 5: //�л� ����
			info = Delete(info);
			system("pause");
			break;
		case 6: //����
			Exit(info);
			return;
		}
	}
}