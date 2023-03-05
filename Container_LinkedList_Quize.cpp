#include<stdio.h>
#include<list>//Linked Type List
#include<Windows.h>
//#include<malloc.h>
//#include<string.h>//stringCat stringCpy


typedef struct Node//typedef struct Member 왜 안 하는지 //typedef는 c에서만 필요했다. //typedef 없앰
{
	char name[20];
	char address[20];
	int sum, kor, eng, mat, age;
	float average;
	char grade;
	//struct Node* link;
}Node; //Node 없애도 된다

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

Node Insert()//구조체 동적할당(주소) 포인터. //포인터.
{//먼저 세팅을 하고 저장을 하는 게 깔끔하다.
	Node temp;// = (Node*)malloc(sizeof(Node));

	printf("학생 이름 입력 : ");
	scanf("%s", temp.name);
	printf("%s 학생 나이 입력 : ", temp.name);
	scanf("%d", &temp.age);
	printf("%s 학생 주소 입력 : ", temp.name);
	scanf("%s", temp.address);
	printf("%s 학생 국어 점수 : ", temp.name);
	scanf("%d", &temp.kor);
	printf("%s 학생 영어 점수 : ", temp.name);
	scanf("%d", &temp.eng);
	printf("%s 학생 수학 점수 : ", temp.name);
	scanf("%d", &temp.mat);
	SetGrade(&temp);
	printf("학생 정보 입력 완료\n");

	//temp.link = NULL;
	return temp;
}

void Information(std::list<Node>::iterator iter)
{
	printf("<<<===== information =====>>>\n");
	printf("학생 이름 : %s\n", iter->name);
	printf("학생 나이 : %d 세\n", iter->age);
	printf("학생 주소 : %s\n", iter->address);
	printf("국어 점수 : %d 점\n", iter->kor);
	printf("영어 점수 : %d 점\n", iter->eng);
	printf("수학 점수 : %d 점\n", iter->mat);
	printf("합계 점수 : %d 점\n", iter->sum);
	printf("평균 점수 : %.2f 점\n", iter->average);
	printf("학생 등급 : %c 등급\n", iter->grade);
}

std::list<Node>::iterator Search(std::list<Node>* iList, char* name)
{//주소로 받는 이유는 함수 안에서 리턴되어도 함수 끝나면 지역변수로 사라지기 때문에
	for (std::list<Node>::iterator iter = iList->begin(); iter != iList->end(); iter++)
	{
		if (strcmp(iter->name, name) == 0)
			return iter;
	}
	return iList->end(); //뭐든 받아오면 된다
}

void SearchData(std::list<Node> iList, char* name)
{
	//std::list<Node>::iterator iter = std::find(iList.begin(), iList.end(), name);
	//find 정확하게 어떤걸로 할지 아는 상황 ex>구조체같은 건 불가 C++로 가능
	std::list<Node>::iterator iter = Search(&iList, name);

	if (iter == iList.end())
		printf("학생 %s이 존재하지 않습니다.\n", name);
	else //if (strcmp(iter->name, name) == 0)
	{
		printf("%s 정보 검색 완료.\n", name);
		Information(iter);
	}
}

void PrintList(std::list<Node> iList)
{
	printf("<<<===== information =====>>>\n\n");
	printf("\t 학생이름\t 학생나이\t 학생주소\n");
	for (std::list<Node>::iterator iter = iList.begin(); iter != iList.end(); iter++)
	{
		printf("\t %s ", iter->name);//포인터와 비슷한 느낌 저장한 주소를 따라가라 같은
		printf("\t\t %d ", iter->age);
		printf("\t\t %s\n", iter->address);
	}	
	printf("\n");
	printf("(학생 개개인의 점수는 검색을 이용하세요 !!)\n");
}

void Modify(std::list<Node>* iList, char* name)
{
	std::list<Node>::iterator iter = Search(iList, name);
	if (iter == iList->end())
		printf("학생 %s을 찾지 못했습니다.\n", name);
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
				printf("현재 이름 : %s\n", iter->name);
				strcpy(na, iter->name);
				printf("수정할 이름 : ");
				scanf("%s", &iter->name);
				printf("%s -> %s 로 이름 수정 완료\n", na, iter->name);
				break;
			case 2:
				printf("현재 나이 : %d\n", iter->age);
				ag = iter->age;
				printf("수정할 나이 : ");
				scanf("%d", &iter->age);
				printf("%d -> %d 로 이름 수정 완료\n", ag, iter->age);
				break;
			case 3:
				printf("현재 주소 : %s\n", iter->address);
				strcpy(ad, iter->address);
				printf("수정할 주소 : ");
				scanf("%s", iter->address);
				printf("%s -> %s 로 주소 수정 완료\n", ad, iter->address);
				break;
			case 4:
				printf("현재 점수\n");
				printf("국어 : %d\t영어 : %d\t수학 : %d\n", iter->kor, iter->eng, iter->mat);
				printf("수정할 국어 점수 : ");
				scanf("%d", &iter->kor);
				printf("수정할 영어 점수 : ");
				scanf("%d", &iter->eng);
				printf("수정할 수학 점수 : ");
				scanf("%d", &iter->mat);
				SetGrade(&(*iter));
				//*iter를 쓰면 iter가 가리키는 데이터로 향한다.
				//&(*iter)를 쓰면 데이터의 주소를 받는다.

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

void Delete(std::list<Node>* iList, char* name)
{
	std::list<Node>::iterator iter = Search(iList, name);
	if (iter == iList->end())
		printf("%s을 찾지못했습니다.\n", name);
	else
	{
		iList->erase(iter);
		printf("삭제완료\n");
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
		case 1://학생 등록
			iList.push_back(Insert());
			break;
		case 2://학생 검색
			printf("검색할 이름 입력 : ");
			scanf("%s", name);
			SearchData(iList, name);
			break;
		case 3://학생 목록
			PrintList(iList);
			break;
		case 4://학생 수정
			printf("수정할 이름 입력 : ");
			scanf("%s", name);
			Modify(&iList, name);
			break;
		case 5://학생 삭제
			printf("학생 이름 입력 : ");
			scanf("%s", name);
			Delete(&iList, name);
			break;
		case 6://종료
			iList.clear();
			return;
		}
		system("pause");
	}
}