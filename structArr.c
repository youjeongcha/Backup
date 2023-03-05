#include <stdio.h>

typedef struct people
{
	char Name[10]; //멤버변수
	int Age;
	float Height;
} People;

void ShowPeople(People P)
{
	printf("======================\n");
	printf("1.이름 : %s\n", P.Name); //멤버 변수 접근 지정자
	printf("2.나이 : %d\n", P.Age);
	printf("3.키 : %.2f\n", P.Height);
	printf("======================\n");
}

void main()
{
	People P_List[3];
	for (int i = 0; i < 3; i++)
	{
		printf("=====%d번째 사람=====\n", i+1);
		printf("이름 입력 : ");
		scanf("%s", P_List[i].Name); //& 배열이기 때문에 포인터
		printf("나이 입력 : ");
		scanf("%d", &P_List[i].Age); //&
		printf("키 입력 : ");
		scanf("%f", &P_List[i].Height);
		printf("======================\n");
	}
	for (int i = 0; i < 3; i++)
	{
		ShowPeople(P_List[i]);
	}
}