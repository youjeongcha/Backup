#include<stdio.h>
#include<map> // red black tree
#include<time.h> // �ð� �� ����ϴ� �������

typedef struct Student
{
	char Name[256];
	int Age;
}Student;


Student CreateStudent()
{//�л� �̸��̶�, ���� �������� ����
	Student student;
	int age = rand() % 10 + 20;
	student.Age = age;

	switch (rand() % 6 + 1)
	{
	case 1:
		strcpy(student.Name, "ȫ�浿");
		break;
	case 2:
		strcpy(student.Name, "��浿");
		break;
	case 3:
		strcpy(student.Name, "��浿");
		break;
	case 4:
		strcpy(student.Name, "�ӱ浿");
		break;
	case 5:
		strcpy(student.Name, "Ȳ�浿");
		break;
	case 6:
		strcpy(student.Name, "�۱浿");
		break;
	}
	return student;
}

void PrintStudentMap(std::map<int, Student> StudentMap)
{
	//foreach
	for (auto iter : StudentMap)
	{
		printf("%s\t%d\t%d\n", iter.second.Name, iter.first, iter.second.Age);
	}
	printf("=========================\n");
}

void main()
{
	srand(time(NULL)); //srand�õ尪 ���´�
	int StudentNumber = 20220001;
	std::map<int, Student> StudentMap;

	//1
	for(int i = 0 ; i < 5 ; i++)
		StudentMap[StudentNumber++] = CreateStudent();
	//2 �� �� �ϳ� �ϸ� �ȴ�.
	StudentMap.insert(std::make_pair(StudentNumber++, CreateStudent()));


	PrintStudentMap(StudentMap);

	//StudentMap[20220001] = CreateStudent();
	//StudentMap.insert(std::make_pair(20220001, CreateStudent()));
	//PrintStudentMap(StudentMap);

	//StudentMap.find(20220001); //Ŷ������ �ش� �й����� �ش� �й��� ������ iter ����, ������ end����
	//StudentMap.at(20220001);
	//StudentMap[20220001];
	StudentMap.erase(20220001);
	PrintStudentMap(StudentMap);

	//StudentMap. //? �ð� ��� �н��ߴ� ��
}


