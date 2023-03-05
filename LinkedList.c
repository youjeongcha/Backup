#include<stdio.h>
#include<Windows.h> //system("cls")
#include<stdlib.h> //동적할당 malloc

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
	printf("<<<==== 메뉴 ====>>>\n\n");
	printf("1.학생 등록\n");
	printf("2.학생 검색\n");
	printf("3.학생 목록\n");
	printf("4.학생 수정\n");
	printf("5.학생 삭제\n");
	printf("6.종료\n");
	printf("선택 : ");
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
	{//처음 들어갈때
		info = (Infomation*)malloc(sizeof(Infomation));
		printf("학생 이름 입력 : ");
		scanf("%s", info->name);
		printf("%s 학생 나이 입력 : ", info->name);
		scanf("%d", &info->age);
		printf("%s 학생 주소 입력 : ", info->name);
		scanf("%s", info->address);
		printf("%s 학생 국어 점수 : ", info->name);
		scanf("%d", &info->Korean);
		printf("%s 학생 영어 점수 : ", info->name);
		scanf("%d", &info->English);
		printf("%s 학생 수학 점수 : ", info->name);
		scanf("%d", &info->math);
		info->sum = (info->Korean + info->English + info->math);
		info->average = (info->Korean + info->English + info->math) / 3;
		info->grade = Grade(info->average);
		printf("학생 정보 입력 완료\n");
		info->Next = NULL;
	}
	else
		info->Next = Insert(info->Next);
	return info;
}

Infomation* SelfSearch(Infomation* info, char* input) //어떠한 경우에도 리턴 받아야 함
{
	if (info == NULL)
	{//검색대상이 없을 때
		return info;
	}
	else if (strcmp(input, info->name) == 0)
	{//문자열 비교 < 음수 반횐 양수 반환 == 0 반환
		return info;
	}
	else
	{
		return SelfSearch(info->Next, input); //리턴
	}
}

void information(Infomation* info)
{
	printf("<<<===== information =====>>>\n");
	printf("학생 이름 : %s\n", info->name);
	printf("학생 나이 : %d 세\n", info->age);
	printf("학생 주소 : %s\n", info->address);
	printf("국어 점수 : %d 점\n", info->Korean);
	printf("영어 점수 : %d 점\n", info->English);
	printf("수학 점수 : %d 점\n", info->math);
	printf("합계 점수 : %d 점\n", info->sum);
	printf("평균 점수 : %.2f 점\n", info->average);
	printf("학생 등급 : %c 등급\n", info->grade);
}

void Search(Infomation* info)
{
	char input[10];
	scanf("%s", input);

	info = SelfSearch(info, input);

	if (info == NULL)
	{
		printf("검색하고자 하는 학생이 존재하지 않습니다.\n");
		return;
	}

	printf("학생 정보 검색 완료\n");
	information(info);
}

void SelfList(Infomation* info)
{
	if (info == NULL)
	{//검색대상이 없을 때
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
	printf("\t 학생이름\t 학생나이\t 학생주소\n");
	SelfList(info);
	printf("(학생 개개인의 점수는 검색을 이용하세요 !!)\n");
}

void Modify(Infomation* info)
{//주소를 변경하는 게 아니라 주소 안의 내용을 변경하는 것이기에 void로 사용. //중요
	char input[10];
	int select;
	char temp[10];
	Infomation* change = NULL;

	printf("수정할 학생 이름은?\n");
	scanf("%s", input);
	change = SelfSearch(info, input);
	//info의 주소와change의 주소가 동일하면 같이 바뀐다. //완전 중요

	system("cls");

	while (1)
	{
		if (change == NULL)
		{
			system("cls");
			printf("찾는 학생이 없습니다.\n");
			return;
		}
		information(change);
		printf("\n\n수정할 항목을 선택 하시오\n");
		printf("1.이름  2.나이  3.주소  4.점수  5.수정종료\n");
		printf("선택 : ");
		scanf("%d", &select);
		switch (select)
		{
		case 1:
		{
			strcpy(temp, info->name);
			printf("현재 이름 : %s\n", change->name);
			printf("수정할 이름 : ");
			scanf("%s", change->name);
			printf("%s -> %s 로 이름 수정 완료\n", temp, change->name);
			break;
		}
		case 2:
		{
			int temp = info->age;
			printf("현재 나이 : %d 세\n", change->age);
			printf("수정할 나이 : ");
			scanf("%d", &change->age);
			printf("\b세\n%d -> %d 세 로 나이 수정 완료\n", temp, change->age);
			//scanf 뒤에 세를 붙이는 방법????
			break;
		}
		case 3:
		{
			char temp[10];
			strcpy(temp, info->address);
			printf("현재 주소 : %s\n", change->address);
			printf("수정할 주소 : ");
			scanf("%s", change->address);
			printf("%s -> %s 로 주소 수정 완료\n", temp, change->address);
			break;
		}
		case 4:
		{
			printf("현재 점수\n");
			printf("국어 : %d 영어 : %d 수학 : %d\n", change->Korean, change->English, change->math);
			printf("수정할 국어 점수 : ");
			scanf("%d", &change->Korean);
			printf("수정할 영어 점수 : ");
			scanf("%d", &change->English);
			printf("수정할 수학 점수 : ");
			scanf("%d", &change->math);
			info->sum = (info->Korean + info->English + info->math);
			info->average = (info->Korean + info->English + info->math) / 3;
			printf("점수 수정 완료\n");
			break;
		}
		case 5:
		{
			printf("수정을 종료합니다\n");
			return;
		}
		}
		system("pause");
		system("cls");
	}
}

Infomation* SelfDelete(Infomation* info, char* input)
{//검색 대상 이후의 값을 리턴받아서
	//Infomation* temp = NULL; //입력 받는 거 뒤의 것들 받아온다.
	if (info != NULL)
	{//검색대상이 있을 때
		if (strcmp(input, info->name) == 0) //맨 앞
		{//문자열 비교 < 음수 반횐 양수 반환 == 0 반환
			info = info->Next;
			return info;
		}
		info->Next = SelfDelete(info->Next, input);
		return info;
	}
	else
	{
		printf("해당 학생이 존재하지 않습니다.\n");
		return info;
	}
}

Infomation* Delete(Infomation* info)
{
	char input[10];
	if (info == NULL)
	{//학생이 아예 존재하지 않을때
		printf("삭제할 학생이 존재하지 않습니다.\n");
		return info;
	}
	printf("삭제할 학생 이름 : ");
	scanf("%s", input);
	info = SelfDelete(info, input);
	return info;
}

void Exit(Infomation* info)
{
	if (info == NULL)
		return;
	Exit(info->Next);
	free(info); //맨 마지막 입력한 것부터 삭제
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
		case 1: //학생 등록
			info = Insert(info);
			system("pause");
			break;
		case 2: //학생 검색
			printf("검색할 이름 입력 : ");
			Search(info);
			system("pause");
			break;
		case 3: //학생 목록
			List(info);
			system("pause");
			break;
		case 4: //학생 수정
			Modify(info);
			system("pause");
			break;
		case 5: //학생 삭제
			info = Delete(info);
			system("pause");
			break;
		case 6: //종료
			Exit(info);
			return;
		}
	}
}