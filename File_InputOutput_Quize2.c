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


void ShowStudent(Student* St) //해당 주소의 값만 받으면 된다.
{
	printf("    ======%s학생(%d번)======\n", St->Name, St->Number);
	printf("    나이 : %d,  성별 : %s,  학년 : %d\n", St->Age, St->Gender, St->Class);
	printf("    ======================\n");
}

void ShowClass(Student* St[], int Class, int StudentCount)
{
	printf("┌─────────%d 학년─────────┐\n", Class);
	for (int i = 0; i < StudentCount; i++)
	{
		if (St[i]->Class == Class)
			ShowStudent(St[i]); //바로 [i]로 받았다
	}
	printf("└─────────────────────┘\n");
}

int SetStudent(Student* St, int Number)
{
	St->Number = ++Number;
	printf("======%d번 학생======\n", St->Number);
	printf("이름 입력 : ");
	scanf("%s", St->Name);
	printf("나이 입력 : ");
	scanf("%d", &St->Age);
	printf("성별 입력 : ");
	scanf("%s", St->Gender);
	while (1)
	{
		printf("학년 입력(1~3) : ");
		scanf("%d", &St->Class);
		if (St->Class <= 3 && St->Class >= 1)
			break;
		printf("학년 잘못 입력(범위 1~3학년)\n");
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
		printf("=====학생관리프로그램=====(총 인원 : %d)\n", StudentCount);
		printf("   1.학생 등록\n");
		printf("   2.학생 목록(번호순)\n");
		printf("   3.학생 목록(학년순)\n");
		printf("   4.학년 검색\n");
		printf("   5.학생 검색\n");
		printf("   6.마지막 학생 삭제\n");
		printf("   7.학생 전체 삭제\n");
		printf("   8.학생정보 저장\n");
		printf("   9.학생정보 불러오기\n");
		printf("   10.종료\n");
		printf("   입력 : ");
		scanf("%d", &Select);
		switch (Select)
		{
		case 1:
			system("cls");
			if (StudentCount + 1 >= MAX)
			{
				printf("학생정원(%d명)이 모두 찼습니다.\n", MAX);
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
				printf("검색할 학년 입력(1~3) : ");
				scanf("%d", &Select);
				if (Select <= 3 && Select >= 1)
					break;
				printf("학년 잘못 입력(범위 1~3학년)\n");
			}
			ShowClass(Student_List, Select, StudentCount);
			break;
		case 5:
			system("cls");
			printf("검색할 이름 입력 : ");
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
				printf("더 이상 삭제할 학생이 없습니다.\n");
				break;
			}
			StudentCount--;
			ShowStudent(Student_List[StudentCount]);
			printf("삭제 완료");
			free(Student_List[StudentCount]);
			Student_List[StudentCount] = NULL;
			break;
		case 7:
			system("cls");
			for (int i = 0; i < StudentCount; i++)
			{
				ShowStudent(Student_List[i]);
				printf("삭제 완료");
				free(Student_List[i]);
				Student_List[i] = NULL;
			}
			StudentCount = 0;
			break;
		case 8:
		{
			FILE* f = fopen("학생정보.txt", "w");
			fprintf(f, "%d\n", StudentCount);
			for (int i = 0; i < StudentCount; i++)
			{
				fprintf(f, "%s %d %s %d\n", Student_List[i]->Name, Student_List[i]->Age, Student_List[i]->Gender, Student_List[i]->Class);
			}
			printf("저장 완료!!\n");
			fclose(f);
			break;
		}
		case 9:
		{//위에는 학생 정보를 메모리를 받아 메모리 크기를 마련했다
			//하지만 마련한 메모리가 없을 경우 불러오기를 하면

			FILE* f = fopen("학생정보.txt", "r"); 
			if (f != NULL)
			{//★파일이 없을 경우 예외처리 반드시 해주어야 함★
				for (int i = 0; i < StudentCount; i++)
				{//동적할당 해제가 되지 않고 덮어씌우면 동적할당 하기 위한 메모리 주소를 찾을 수 없게 된다.
					printf("%s학생 동적할당 해제 완료\n", Student_List[i]->Name);
					free(Student_List[i]);
				}

				fscanf(f, "%d", &StudentCount);

				if (StudentCount > MAX)
				{//명부 50명을 초과할 경우
					printf("더이상 학생을 불러올 수 없습니다.\n");
					//int overData = StudentCount - MAX; //넘친 데이터
					//StudentCount -= overData;
					StudentCount = MAX; //바로 이렇게 해도 무관
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
				printf("%s학생 동적할당 해제 완료\n", Student_List[i]->Name);
				free(Student_List[i]);
			}
			return;
		}
		system("pause");
	}
}