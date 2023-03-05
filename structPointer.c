#include <stdio.h>

typedef struct people
{
	char Name[10];
	int Age;
	float Height;
} People;

void ShowPeople(People P)
{
	printf("======================\n");
	printf("1.이름 : %s\n", P.Name);
	printf("2.나이 : %d\n", P.Age);
	printf("3.키 : %.2f\n", P.Height);
	printf("======================\n");
}

void SefPeople(People* P)
{
	printf("======================\n");
	printf("이름 입력 : ");
	scanf("%s", P->Name); //주소로 따라가라*인데 (*p).Name 도 틀린 건 아니지만 줄인게 ->
	printf("나이 입력 : ");
	scanf("%d", &P->Age); //&
	printf("키 입력 : ");
	scanf("%f", &P->Height);
	printf("======================\n");
}

void main()
{
	People P1;
	SefPeople(&P1);
	ShowPeople(P1);
}