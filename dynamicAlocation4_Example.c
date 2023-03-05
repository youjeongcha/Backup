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

void ShowStudent(Student* St)
{
	printf("======%s학생(%d번)======\n", St->Name, St->Number);
	printf("나이 : %d,  성별 : %s,  학년 : %d\n", St->Age, St->Gender, St->Class);
	printf("======================\n");
}
int SetStudent(Student* St, int StudentCount)
{
	St->Number = ++StudentCount;
	printf("======%d번 학생======\n", St->Number);
	printf("이름 입력 : ");
	scanf("%s", St->Name);
	printf("나이 입력 : ");
	scanf("%d", &St->Age);
	printf("성별 입력 : ");
	scanf("%s", St->Gender);
	printf("학년 입력 : ");
	scanf("%d", &St->Class);
	return StudentCount;
}

void main()
{
	Student* Student_List[MAX]; //동적할당 받을 자리만 마련
	int Select;
	int StudentCount = 0;

	while (1)
	{
		system("cls");
		printf("=====학생관리프로그램=====(총 인원 : %d)\n", StudentCount);
		printf("1.학생 등록\n");
		printf("2.학생 목록\n");
		printf("3.종료\n");
		printf("입력 : ");
		scanf("%d", &Select);
		switch (Select)
		{
		case 1:
			if (StudentCount + 1 >= MAX)
			{
				printf("학생정원(50명)이 모두 찼습니다.\n");
				break;
			}
			Student_List[StudentCount] = (Student*)malloc(sizeof(Student)); //동적할당 받은 만큼 동적할당 해제도 해줘야 함 71
			//다른 변수 모두 합한만큼 바이트 받아서
			StudentCount = SetStudent(Student_List[StudentCount], StudentCount);
			break;
		case 2:
			for (int i = 0; i < StudentCount; i++)
				ShowStudent(Student_List[i]);
			break;
		case 3:
			for (int i = 0; i < StudentCount; i++)
			{
				printf("%s학생 동적할당 해제 완료\n", Student_List[i]->Name);
				free(Student_List[i]); //동적할당 받은 만큼 동적할당 해제도 해줘야 함 59
			}
			return;
		}
		system("pause");
	}
}