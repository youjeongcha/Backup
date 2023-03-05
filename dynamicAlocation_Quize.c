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
	printf("  ======%s 학생(%d번)======\n", St[i]->Name, St[i]->Number);
	printf("  나이 : %d,  성별 : %s,  학년 : %d\n", St[i]->Age, St[i]->Gender, St[i]->Class);
	printf("  ======================\n");
}

void ShowClass(Student* St[], int StudentCount, int input)
{
	printf("┌─────────%d 학년─────────┐\n", input);
	for (int i = 0; i < StudentCount; i++)
	{
		if (St[i]->Class == input) {
			Show(St, i);
		}
	}
	printf("└─────────────────────┘\n");
}

void NumShowStudent(Student** St, int StudentCount) //or Student* St[MAX]로 똑 같은 형태로 받아도 되는것
{//Student List가 처음에 포인터로 주소를 받았기에 이중 포인터로 해야 한
	//일반 변수면 그냥 포인터/ 포인터로 받으면 이중 포인터/ 이중 포인터로 받으면 삼중
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
{//Student List[]로 인자 받았는데 그안에 주소값이 들어서 포인터
	St->Number = ++StudentCount;
	printf("======%d번 학생======\n", St->Number);
	printf("이름 입력 : ");
	scanf("%s", St->Name);
	printf("나이 입력 : ");
	scanf("%d", &St->Age);
	printf("성별 입력 : ");
	scanf("%s", St->Gender);
	do
	{
		printf("학년 입력(1~3) : ");
		scanf("%d", &St->Class);
		if (St->Class == 1 || St->Class == 2 || St->Class == 3)
		{
			break;
		}
		printf("학년 잘못 입력(범위 1~3학년)\n");
		system("pause");

	} while (St->Class <= 0 || St->Class > 3);

	return StudentCount;
}

void SarchGrade(Student** St, int StudentCount)
{
	int input = 0;
	do
	{
		printf("검색할 학년 입력(1~3) : ");
		scanf("%d", &input);
		if (input == 1 || input == 2 || input == 3)
		{
			break;
		}
		printf("학년 잘못 입력(범위 1~3학년)\n");
		system("pause");

	} while (input <=0 || input > 3);

	ShowClass(St, StudentCount, input);
}

void SarchStudent(Student** St, int StudentCount)
{
	char input[10];
	printf("검색할 이름 입력 : ");
	scanf("%s", &input);

	for (int i = 0; i < StudentCount; i++)
	{
		if (strcmp(St[i]->Name, input) == 0)
		{
			printf("┌─────────%d 학년─────────┐\n", i + 1);
			Show(St, i);
			printf("└─────────────────────┘\n");
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
	printf("삭제 완료\n");
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
	printf("삭제 완료\n");
	return 0;
}


void main()
{
	Student* Student_List[MAX]; //동적할당 받을 자리만 마련 //배열 안에 주소가 들어있다.
	int Select;
	int StudentCount = 0;

	while (1)
	{
		system("cls");
		printf("=====학생관리프로그램=====(총 인원 : %d)\n", StudentCount);
		printf("  1.학생 등록\n");
		printf("  2.학생 목록(번호순)\n");
		printf("  3.학생 목록(학년순)\n");
		printf("  4.학년 검색\n");
		printf("  5.학생 검색\n");
		printf("  6.마지막 학생 삭제\n");
		printf("  7.전체 학생 삭제\n");
		printf("  8.종료\n");
		printf("  입력 : ");
		scanf("%d", &Select);

		switch (Select)
		{
		case 1: //학생 등록
			system("cls");
			if (StudentCount + 1 >= MAX)
			{ 
				printf("학생정원(50명)이 모두 찼습니다.\n");
				break;
			}
			Student_List[StudentCount] = (Student*)malloc(sizeof(Student)); //동적할당 받은 만큼 동적할당 해제도 해줘야 함 71
			StudentCount = SetStudent(Student_List[StudentCount], StudentCount); //
			system("pause");
			break;
		case 2: //학생 목록(번호순)
			system("cls");
			NumShowStudent(Student_List, StudentCount);
			system("pause");
			break;
		case 3: //학생 목록(학년순)
			system("cls");
			ClassShowStudent(Student_List, StudentCount);
			system("pause");
			break;
		case 4: //학년 검색
			system("cls");
			SarchGrade(Student_List, StudentCount);
			system("pause");
			break;
		case 5: //학생 검색
			system("cls");
			SarchStudent(Student_List, StudentCount);
			system("pause");
			break;
		case 6: //마지막 학생 삭제
			StudentCount = DeletFinal(Student_List, StudentCount);
			system("pause"); //
			break;
		case 7: //전체 학생 삭제
			StudentCount = DeletTotal(Student_List, StudentCount);
			system("pause"); //
			break;
		case 8: //종료
			for (int i = 0; i < StudentCount; i++)
			{
				free(Student_List[i]); //동적할당 받은 만큼 동적할당 해제도 해줘야 함
				Student_List[i] = NULL;
			}
			return;
		}
	}
}