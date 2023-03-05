#include<stdio.h>
#include<list>//Linked Type List
#include<Windows.h>
//#include<malloc.h>
//#include<string.h>//stringCat stringCpy


typedef struct Node//typedef struct Member �� �� �ϴ��� //typedef�� c������ �ʿ��ߴ�. //typedef ����
{
	char name[20];
	char address[20];
	int sum, kor, eng, mat, age;
	float average;
	char grade;
	//struct Node* link;
}Node; //Node ���ֵ� �ȴ�

int Menu()
{
	int input;
	system("cls");
	printf("< < < = = = = �޴� = = = = > > >\n\n");
	printf("1. �л� ���\n");
	printf("2. �л� �˻�\n");
	printf("3. �л� ���\n");
	printf("4. �л� ����\n");
	printf("5. �л� ����\n");
	printf("6. ����\n");
	printf("���� : ");
	scanf("%d", &input);
	printf("\n");
	return input;
}

void SetGrade(Node* temp)
{
	temp->sum = (temp->eng) + (temp->kor) + (temp->mat);
	temp->average = temp->sum / 3;
	if (temp->average > 90)
		temp->grade = 'A';
	else if (temp->average > 80)
		temp->grade = 'B';
	else if (temp->average > 70)
		temp->grade = 'C';
	else if (temp->average > 60)
		temp->grade = 'D';
	else
		temp->grade = 'F';
}

Node Insert()//����ü �����Ҵ�(�ּ�) ������. //������.
{//���� ������ �ϰ� ������ �ϴ� �� ����ϴ�.
	Node temp;// = (Node*)malloc(sizeof(Node));

	printf("�л� �̸� �Է� : ");
	scanf("%s", temp.name);
	printf("%s �л� ���� �Է� : ", temp.name);
	scanf("%d", &temp.age);
	printf("%s �л� �ּ� �Է� : ", temp.name);
	scanf("%s", temp.address);
	printf("%s �л� ���� ���� : ", temp.name);
	scanf("%d", &temp.kor);
	printf("%s �л� ���� ���� : ", temp.name);
	scanf("%d", &temp.eng);
	printf("%s �л� ���� ���� : ", temp.name);
	scanf("%d", &temp.mat);
	SetGrade(&temp);
	printf("�л� ���� �Է� �Ϸ�\n");

	//temp.link = NULL;
	return temp;
}

void Information(std::list<Node>::iterator iter)
{
	printf("<<<===== information =====>>>\n");
	printf("�л� �̸� : %s\n", iter->name);
	printf("�л� ���� : %d ��\n", iter->age);
	printf("�л� �ּ� : %s\n", iter->address);
	printf("���� ���� : %d ��\n", iter->kor);
	printf("���� ���� : %d ��\n", iter->eng);
	printf("���� ���� : %d ��\n", iter->mat);
	printf("�հ� ���� : %d ��\n", iter->sum);
	printf("��� ���� : %.2f ��\n", iter->average);
	printf("�л� ��� : %c ���\n", iter->grade);
}

std::list<Node>::iterator Search(std::list<Node>* iList, char* name)
{//�ּҷ� �޴� ������ �Լ� �ȿ��� ���ϵǾ �Լ� ������ ���������� ������� ������
	for (std::list<Node>::iterator iter = iList->begin(); iter != iList->end(); iter++)
	{
		if (strcmp(iter->name, name) == 0)
			return iter;
	}
	return iList->end(); //���� �޾ƿ��� �ȴ�
}

void SearchData(std::list<Node> iList, char* name)
{
	//std::list<Node>::iterator iter = std::find(iList.begin(), iList.end(), name);
	//find ��Ȯ�ϰ� ��ɷ� ���� �ƴ� ��Ȳ ex>����ü���� �� �Ұ� C++�� ����
	std::list<Node>::iterator iter = Search(&iList, name);

	if (iter == iList.end())
		printf("�л� %s�� �������� �ʽ��ϴ�.\n", name);
	else //if (strcmp(iter->name, name) == 0)
	{
		printf("%s ���� �˻� �Ϸ�.\n", name);
		Information(iter);
	}
}

void PrintList(std::list<Node> iList)
{
	printf("<<<===== information =====>>>\n\n");
	printf("\t �л��̸�\t �л�����\t �л��ּ�\n");
	for (std::list<Node>::iterator iter = iList.begin(); iter != iList.end(); iter++)
	{
		printf("\t %s ", iter->name);//�����Ϳ� ����� ���� ������ �ּҸ� ���󰡶� ����
		printf("\t\t %d ", iter->age);
		printf("\t\t %s\n", iter->address);
	}	
	printf("\n");
	printf("(�л� �������� ������ �˻��� �̿��ϼ��� !!)\n");
}

void Modify(std::list<Node>* iList, char* name)
{
	std::list<Node>::iterator iter = Search(iList, name);
	if (iter == iList->end())
		printf("�л� %s�� ã�� ���߽��ϴ�.\n", name);
	else
	{//�л� ����
		int i, ag;
		char na[20], ad[20];
		while (1)
		{
			system("cls");
			Information(iter);
			printf("\n\n������ �׸��� ���� �Ͻÿ� \n");
			printf("1.�̸�\t2.����\t3.�ּ�\t4.����\t5.��������\n���� : ");
			scanf("%d", &i);
			switch (i)
			{
			case 1:
				printf("���� �̸� : %s\n", iter->name);
				strcpy(na, iter->name);
				printf("������ �̸� : ");
				scanf("%s", &iter->name);
				printf("%s -> %s �� �̸� ���� �Ϸ�\n", na, iter->name);
				break;
			case 2:
				printf("���� ���� : %d\n", iter->age);
				ag = iter->age;
				printf("������ ���� : ");
				scanf("%d", &iter->age);
				printf("%d -> %d �� �̸� ���� �Ϸ�\n", ag, iter->age);
				break;
			case 3:
				printf("���� �ּ� : %s\n", iter->address);
				strcpy(ad, iter->address);
				printf("������ �ּ� : ");
				scanf("%s", iter->address);
				printf("%s -> %s �� �ּ� ���� �Ϸ�\n", ad, iter->address);
				break;
			case 4:
				printf("���� ����\n");
				printf("���� : %d\t���� : %d\t���� : %d\n", iter->kor, iter->eng, iter->mat);
				printf("������ ���� ���� : ");
				scanf("%d", &iter->kor);
				printf("������ ���� ���� : ");
				scanf("%d", &iter->eng);
				printf("������ ���� ���� : ");
				scanf("%d", &iter->mat);
				SetGrade(&(*iter));
				//*iter�� ���� iter�� ����Ű�� �����ͷ� ���Ѵ�.
				//&(*iter)�� ���� �������� �ּҸ� �޴´�.

				printf("���� ���� �Ϸ�\n");
				break;
			case 5:
				printf("������ �����մϴ�\n");
				return;
			}
			system("pause");
		}
	}
}

void Delete(std::list<Node>* iList, char* name)
{
	std::list<Node>::iterator iter = Search(iList, name);
	if (iter == iList->end())
		printf("%s�� ã�����߽��ϴ�.\n", name);
	else
	{
		iList->erase(iter);
		printf("�����Ϸ�\n");
	}
}

void main()
{
	std::list<Node> iList;
	char name[20];

	while (true)
	{
		system("cls");
		switch (Menu())
		{
		case 1://�л� ���
			iList.push_back(Insert());
			break;
		case 2://�л� �˻�
			printf("�˻��� �̸� �Է� : ");
			scanf("%s", name);
			SearchData(iList, name);
			break;
		case 3://�л� ���
			PrintList(iList);
			break;
		case 4://�л� ����
			printf("������ �̸� �Է� : ");
			scanf("%s", name);
			Modify(&iList, name);
			break;
		case 5://�л� ����
			printf("�л� �̸� �Է� : ");
			scanf("%s", name);
			Delete(&iList, name);
			break;
		case 6://����
			iList.clear();
			return;
		}
		system("pause");
	}
}