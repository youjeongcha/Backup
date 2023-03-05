#include <stdio.h>
#include <Windows.h>v //system함수 쓸때

#define FIVE 5

typedef struct people
{
	char Name[10];
	int Age;
	float Height;
} People;

void ShowPeople(People* P)
{
	for (int i = 0; i < FIVE; i++)
	{
		printf("=======%d=======\n", i + 1);
		printf("이름 : %s\n", P[i].Name);
		printf("나이 : %d\n", P[i].Age);
		printf("키 : %.2f\n", P[i].Height);
		printf("===============\n");
	}
}

void Arr(People* P)
{
	People temp; //P는 입력한 값이 들어있는 거고. temp는 빈 구조체?

	//나이 내림, 나이 같을시 키 내림
	for (int i = 0; i < FIVE; i++) //1~4
	{
		for (int j = 0; j < i; j++) //0~3
		{
			if ((P[i].Age > P[j].Age) || (P[i].Age == P[j].Age && P[i].Height > P[j].Height))
			{//이름 처리 불가,//크기 비교해서 출력만 정렬되게 하는 방법 가능한지? 였던
				temp = P[i];
				P[i] = P[j];
				P[j] = temp;
			}
		}
	}
}

void main()
{
	People P_List[FIVE];

	for (int i = 0; i < FIVE; i++)
	{
		printf("=======%d=======\n", i + 1);
		printf("이름 입력 : ");
		scanf("%s", P_List[i].Name); //배열이기에 포인터
		printf("나이 입력 : ");
		scanf("%d", &P_List[i].Age);
		printf("키 입력 : ");
		scanf("%f", &P_List[i].Height);
		printf("===============\n");
	}
	system("cls");

	printf("정렬 전 정보\n");
	ShowPeople(P_List); //정렬 전 출력
	system("pause");
	system("cls");

	Arr(P_List); //내림차순 정렬
	ShowPeople(P_List); //정렬 후 출력
}