#include<stdio.h>
//#include<list>//Linked Type List
#include<map> // red black tree
#include<time.h> // �ð� �� ����ϴ� �������
#include<Windows.h>

typedef struct Student
{
	char name[20];
	char address[20];
	int sum, kor, eng, mat, age;
	float average;
	char grade;
	//struct Node* link;
}Student;

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

void SetGrade(Student* temp)
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

Student CreateStudent()
{//�л� �̸��̶�, ���� �������� ����
	Student student;
	int age = rand() % 10 + 20;
	student.age = age;

	switch (rand() % 6 + 1)
	{
	case 1:
		strcpy(student.name, "��");
		break;
	case 2:
		strcpy(student.name, "��");
		break;
	case 3:
		strcpy(student.name, "��");
		break;
	case 4:
		strcpy(student.name, "��");
		break;
	case 5:
		strcpy(student.name, "��");
		break;
	case 6:
		strcpy(student.name, "��");
		break;
	}
	printf("%s �л� �ּ� �Է� : ", student.name);
	scanf("%s", student.address);
	printf("%s �л� ���� ���� : ", student.name);
	scanf("%d", &student.kor);
	printf("%s �л� ���� ���� : ", student.name);
	scanf("%d", &student.eng);
	printf("%s �л� ���� ���� : ", student.name);
	scanf("%d", &student.mat);
	SetGrade(&student);
	return student;
}

std::map<int, Student>::iterator Search(std::map<int, Student>* StudentMap, int StudentNumber)
{//���������� �ϸ� �Լ��� ����Ǿ��� ��� ������� ������ -> �ּҰ��� �޾Ƽ� ����
	//for (std::map<int, Student>::iterator iter = StudentMap->begin(); iter != StudentMap->end(); iter++)
	//{
	//	if (strcmp(iter->name, name) == 0)
	//		return iter;
	//}
	//return StudentMap->end(); //���� �޾ƿ��� �ȴ�
	// 
	// 
	//StudentMap.find(StudentNumber); 
	//Ŷ������ �ش� �й����� �ش� �й��� ������ iter ����, ������ end����
	return StudentMap->find(StudentNumber);
}

void Information(std::map<int, Student>::iterator iter)
{
	printf("<<<===== information =====>>>\n");
	printf("�л� �й� : %d\n", iter->first);
	printf("�л� �̸� : %s\n", iter->second.name);
	printf("�л� ���� : %d ��\n", iter->second.age);
	printf("�л� �ּ� : %s\n", iter->second.address);
	printf("���� ���� : %d ��\n", iter->second.kor);
	printf("���� ���� : %d ��\n", iter->second.eng);
	printf("���� ���� : %d ��\n", iter->second.mat);
	printf("�հ� ���� : %d ��\n", iter->second.sum);
	printf("��� ���� : %.2f ��\n", iter->second.average);
	printf("�л� ��� : %c ���\n", iter->second.grade);
}

void SearchData(std::map<int, Student> StudentMap, int StudentNumber)
{
	std::map<int, Student>::iterator iter = Search(&StudentMap, StudentNumber);//�ּҰ� �� �ް� StudentMap���� ����

	if (iter == StudentMap.end())
		printf("�л� %d�� �������� �ʽ��ϴ�.\n", StudentNumber);
	else
	{
		printf("%d ���� �˻� �Ϸ�.\n", StudentNumber);
		Information(iter);
	}
}

void PrintStudentMap(std::map<int, Student> StudentMap)
{
	printf("<<<===== information =====>>>\n\n");
	printf("\t  �л��̸�\t\t�л��й�\t  �л�����\t �л��ּ�\n");
	//foreach
	//StudentMap.find(StudentNumber);
	//(std::map<int, Student>::iterator iter = iList.begin(); iter != iList.end(); iter++)
	for (auto iter : StudentMap)
	{
		printf("\t\t%s\t\t%d\t\t%d\t\t%s\n", iter.second.name, iter.first, iter.second.age, iter.second.address);
	}
	printf("=========================\n");
	printf("(�л� �������� ������ �˻��� �̿��ϼ��� !!)\n");
}

void Modify(std::map<int, Student>* StudentMap, int StudentNumber)
{
	std::map<int, Student>::iterator iter = Search(StudentMap, StudentNumber);
	if (iter == StudentMap->end())
		printf("�л� %d�� ã�� ���߽��ϴ�.\n", StudentNumber);
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
				printf("���� �̸� : %s\n", iter->second.name);
				strcpy(na, iter->second.name);
				printf("������ �̸� : ");
				scanf("%s", &iter->second.name);
				printf("%s -> %s �� �̸� ���� �Ϸ�\n", na, iter->second.name);
				break;
			case 2:
				printf("���� ���� : %d\n", iter->second.age);
				ag = iter->second.age;
				printf("������ ���� : ");
				scanf("%d", &iter->second.age);
				printf("%d -> %d �� �̸� ���� �Ϸ�\n", ag, iter->second.age);
				break;
			case 3:
				printf("���� �ּ� : %s\n", iter->second.address);
				strcpy(ad, iter->second.address);
				printf("������ �ּ� : ");
				scanf("%s", iter->second.address);
				printf("%s -> %s �� �ּ� ���� �Ϸ�\n", ad, iter->second.address);
				break;
			case 4:
				printf("���� ����\n");
				printf("���� : %d\t���� : %d\t���� : %d\n", iter->second.kor, iter->second.eng, iter->second.mat);
				printf("������ ���� ���� : ");
				scanf("%d", &iter->second.kor);
				printf("������ ���� ���� : ");
				scanf("%d", &iter->second.eng);
				printf("������ ���� ���� : ");
				scanf("%d", &iter->second.mat);
				SetGrade(&iter->second);
				///���� SetGrade(&(*iter));
				//*iter�� ���� iter�� ����Ű�� �����ͷ� ���Ѵ�.
				//&(*iter)�� ���� �������� �ּҸ� �޴´�.
				//->second 

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

void Delete(std::map<int, Student>* StudentMap, int StudentNumber)
{
	std::map<int, Student>::iterator iter = Search(StudentMap, StudentNumber);
	if (iter == StudentMap->end())
		printf("%d�� ã�����߽��ϴ�.\n", StudentNumber);
	else
	{
		StudentMap->erase(iter);
		printf("�����Ϸ�\n");
	}
}


void main()
{
	srand(time(NULL)); //srand�õ尪 ���´�
	int StudentNumber = 20220001; //Ŷ���� ����ü�� �� �ʿ�X
	std::map<int, Student> StudentMap;
	char name[20];

	while (true)
	{
		system("cls");
		switch (Menu())
		{
		case 1://�л� ���
			StudentMap[StudentNumber++] = CreateStudent(); //[StudentNumber]���� �й� 1�� Ű���ַ���
			//++���ص� tree ���������� ����ȴ�. //�迭����  ++����� �ߴ��Ŷ� �ٸ�
			//StudentMap.insert(std::make_pair(StudentNumber++, CreateStudent()));
			break;
		case 2://�л� �˻�
			printf("�˻��� �й� �Է� : ");
			scanf("%d", &StudentNumber);
			SearchData(StudentMap, StudentNumber);

			//StudentMap.find(StudentNumber); //Ŷ������ �ش� �й����� �ش� �й��� ������ iter ����, ������ end����
			break;
		case 3://�л� ���
			PrintStudentMap(StudentMap);
			break;
		case 4://�л� ���� //SetGrade() ����
			printf("������ �й� �Է� : ");
			scanf("%d", &StudentNumber);
			Modify(&StudentMap, StudentNumber);
			break;
		case 5://�л� ����
			printf("������ �л� �й� �Է� : ");
			scanf("%d", &StudentNumber);
			Delete(&StudentMap, StudentNumber);
			break;
		case 6://����
			StudentMap.clear();
			return;
		}
		system("pause");
	}
}