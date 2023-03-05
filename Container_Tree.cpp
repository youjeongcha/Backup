#include<stdio.h>
#include<map> // red black tree
#include<time.h> // 시간 값 사용하는 헤더파일

typedef struct Student
{
	char Name[256];
	int Age;
}Student;


Student CreateStudent()
{//학생 이름이랑, 나이 랜덤으로 생성
	Student student;
	int age = rand() % 10 + 20;
	student.Age = age;

	switch (rand() % 6 + 1)
	{
	case 1:
		strcpy(student.Name, "홍길동");
		break;
	case 2:
		strcpy(student.Name, "김길동");
		break;
	case 3:
		strcpy(student.Name, "고길동");
		break;
	case 4:
		strcpy(student.Name, "임길동");
		break;
	case 5:
		strcpy(student.Name, "황길동");
		break;
	case 6:
		strcpy(student.Name, "송길동");
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
	srand(time(NULL)); //srand시드값 들고온다
	int StudentNumber = 20220001;
	std::map<int, Student> StudentMap;

	//1
	for(int i = 0 ; i < 5 ; i++)
		StudentMap[StudentNumber++] = CreateStudent();
	//2 둘 중 하나 하면 된다.
	StudentMap.insert(std::make_pair(StudentNumber++, CreateStudent()));


	PrintStudentMap(StudentMap);

	//StudentMap[20220001] = CreateStudent();
	//StudentMap.insert(std::make_pair(20220001, CreateStudent()));
	//PrintStudentMap(StudentMap);

	//StudentMap.find(20220001); //킷값으로 해당 학번으로 해당 학번이 있으면 iter 리턴, 없으면 end리턴
	//StudentMap.at(20220001);
	//StudentMap[20220001];
	StudentMap.erase(20220001);
	PrintStudentMap(StudentMap);

	//StudentMap. //? 시간 없어서 패스했던 거
}


