#include<stdio.h>
//#include<list>//Linked Type List
#include<map> // red black tree
#include<time.h> // 시간 값 사용하는 헤더파일
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
	printf("< < < = = = = 메뉴 = = = = > > >\n\n");
	printf("1. 학생 등록\n");
	printf("2. 학생 검색\n");
	printf("3. 학생 목록\n");
	printf("4. 학생 수정\n");
	printf("5. 학생 삭제\n");
	printf("6. 종료\n");
	printf("선택 : ");
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
{//학생 이름이랑, 나이 랜덤으로 생성
	Student student;
	int age = rand() % 10 + 20;
	student.age = age;

	switch (rand() % 6 + 1)
	{
	case 1:
		strcpy(student.name, "가");
		break;
	case 2:
		strcpy(student.name, "나");
		break;
	case 3:
		strcpy(student.name, "다");
		break;
	case 4:
		strcpy(student.name, "라");
		break;
	case 5:
		strcpy(student.name, "마");
		break;
	case 6:
		strcpy(student.name, "바");
		break;
	}
	printf("%s 학생 주소 입력 : ", student.name);
	scanf("%s", student.address);
	printf("%s 학생 국어 점수 : ", student.name);
	scanf("%d", &student.kor);
	printf("%s 학생 영어 점수 : ", student.name);
	scanf("%d", &student.eng);
	printf("%s 학생 수학 점수 : ", student.name);
	scanf("%d", &student.mat);
	SetGrade(&student);
	return student;
}

std::map<int, Student>::iterator Search(std::map<int, Student>* StudentMap, int StudentNumber)
{//지역변수로 하면 함수가 종료되었을 경우 사라지기 때문에 -> 주소값을 받아서 진행
	//for (std::map<int, Student>::iterator iter = StudentMap->begin(); iter != StudentMap->end(); iter++)
	//{
	//	if (strcmp(iter->name, name) == 0)
	//		return iter;
	//}
	//return StudentMap->end(); //뭐든 받아오면 된다
	// 
	// 
	//StudentMap.find(StudentNumber); 
	//킷값으로 해당 학번으로 해당 학번이 있으면 iter 리턴, 없으면 end리턴
	return StudentMap->find(StudentNumber);
}

void Information(std::map<int, Student>::iterator iter)
{
	printf("<<<===== information =====>>>\n");
	printf("학생 학번 : %d\n", iter->first);
	printf("학생 이름 : %s\n", iter->second.name);
	printf("학생 나이 : %d 세\n", iter->second.age);
	printf("학생 주소 : %s\n", iter->second.address);
	printf("국어 점수 : %d 점\n", iter->second.kor);
	printf("영어 점수 : %d 점\n", iter->second.eng);
	printf("수학 점수 : %d 점\n", iter->second.mat);
	printf("합계 점수 : %d 점\n", iter->second.sum);
	printf("평균 점수 : %.2f 점\n", iter->second.average);
	printf("학생 등급 : %c 등급\n", iter->second.grade);
}

void SearchData(std::map<int, Student> StudentMap, int StudentNumber)
{
	std::map<int, Student>::iterator iter = Search(&StudentMap, StudentNumber);//주소값 안 받고 StudentMap으로 받음

	if (iter == StudentMap.end())
		printf("학생 %d이 존재하지 않습니다.\n", StudentNumber);
	else
	{
		printf("%d 정보 검색 완료.\n", StudentNumber);
		Information(iter);
	}
}

void PrintStudentMap(std::map<int, Student> StudentMap)
{
	printf("<<<===== information =====>>>\n\n");
	printf("\t  학생이름\t\t학생학번\t  학생나이\t 학생주소\n");
	//foreach
	//StudentMap.find(StudentNumber);
	//(std::map<int, Student>::iterator iter = iList.begin(); iter != iList.end(); iter++)
	for (auto iter : StudentMap)
	{
		printf("\t\t%s\t\t%d\t\t%d\t\t%s\n", iter.second.name, iter.first, iter.second.age, iter.second.address);
	}
	printf("=========================\n");
	printf("(학생 개개인의 점수는 검색을 이용하세요 !!)\n");
}

void Modify(std::map<int, Student>* StudentMap, int StudentNumber)
{
	std::map<int, Student>::iterator iter = Search(StudentMap, StudentNumber);
	if (iter == StudentMap->end())
		printf("학생 %d를 찾지 못했습니다.\n", StudentNumber);
	else
	{//학생 존재
		int i, ag;
		char na[20], ad[20];
		while (1)
		{
			system("cls");
			Information(iter);
			printf("\n\n수정할 항목을 선택 하시오 \n");
			printf("1.이름\t2.나이\t3.주소\t4.점수\t5.수정종료\n선택 : ");
			scanf("%d", &i);
			switch (i)
			{
			case 1:
				printf("현재 이름 : %s\n", iter->second.name);
				strcpy(na, iter->second.name);
				printf("수정할 이름 : ");
				scanf("%s", &iter->second.name);
				printf("%s -> %s 로 이름 수정 완료\n", na, iter->second.name);
				break;
			case 2:
				printf("현재 나이 : %d\n", iter->second.age);
				ag = iter->second.age;
				printf("수정할 나이 : ");
				scanf("%d", &iter->second.age);
				printf("%d -> %d 로 이름 수정 완료\n", ag, iter->second.age);
				break;
			case 3:
				printf("현재 주소 : %s\n", iter->second.address);
				strcpy(ad, iter->second.address);
				printf("수정할 주소 : ");
				scanf("%s", iter->second.address);
				printf("%s -> %s 로 주소 수정 완료\n", ad, iter->second.address);
				break;
			case 4:
				printf("현재 점수\n");
				printf("국어 : %d\t영어 : %d\t수학 : %d\n", iter->second.kor, iter->second.eng, iter->second.mat);
				printf("수정할 국어 점수 : ");
				scanf("%d", &iter->second.kor);
				printf("수정할 영어 점수 : ");
				scanf("%d", &iter->second.eng);
				printf("수정할 수학 점수 : ");
				scanf("%d", &iter->second.mat);
				SetGrade(&iter->second);
				///질문 SetGrade(&(*iter));
				//*iter를 쓰면 iter가 가리키는 데이터로 향한다.
				//&(*iter)를 쓰면 데이터의 주소를 받는다.
				//->second 

				printf("점수 수정 완료\n");
				break;
			case 5:
				printf("수정을 종료합니다\n");
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
		printf("%d를 찾지못했습니다.\n", StudentNumber);
	else
	{
		StudentMap->erase(iter);
		printf("삭제완료\n");
	}
}


void main()
{
	srand(time(NULL)); //srand시드값 들고온다
	int StudentNumber = 20220001; //킷값은 구조체에 들어갈 필요X
	std::map<int, Student> StudentMap;
	char name[20];

	while (true)
	{
		system("cls");
		switch (Menu())
		{
		case 1://학생 등록
			StudentMap[StudentNumber++] = CreateStudent(); //[StudentNumber]에서 학번 1씩 키워주려고
			//++안해도 tree 정상적으로 저장된다. //배열에서  ++해줘야 했던거랑 다름
			//StudentMap.insert(std::make_pair(StudentNumber++, CreateStudent()));
			break;
		case 2://학생 검색
			printf("검색할 학번 입력 : ");
			scanf("%d", &StudentNumber);
			SearchData(StudentMap, StudentNumber);

			//StudentMap.find(StudentNumber); //킷값으로 해당 학번으로 해당 학번이 있으면 iter 리턴, 없으면 end리턴
			break;
		case 3://학생 목록
			PrintStudentMap(StudentMap);
			break;
		case 4://학생 수정 //SetGrade() 질문
			printf("수정할 학번 입력 : ");
			scanf("%d", &StudentNumber);
			Modify(&StudentMap, StudentNumber);
			break;
		case 5://학생 삭제
			printf("삭제할 학생 학번 입력 : ");
			scanf("%d", &StudentNumber);
			Delete(&StudentMap, StudentNumber);
			break;
		case 6://종료
			StudentMap.clear();
			return;
		}
		system("pause");
	}
}