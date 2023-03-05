#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h> //Sleep 함수 //system("cls")
//전역변수x return x 구조체x 포인터x
//함수는 전방 선언
//int 함수는 리턴되는 값이 있어야지만 사용 //배열은 int형으로 리턴 받을 수 x

#define MIN 0
#define MAX 1
#define TURN 2


void Gamestart(int element[])
{
	int input;
	int RNum;

	//srand((unsigned)time(NULL));  //unsigned?  부호가 없다 타임 값은 부호가 없으므로 필요 없다.
	srand(time(NULL));
	RNum = rand() % (element[MAX] - element[MIN] + 1) + element[MIN];
	printf("%d\n", RNum);

	for (int i = 1; i <= element[2]; i++)
	{
		printf("범위 : %d ~ %d\n", element[MIN], element[MAX]);
		printf("제한 Turn : %d\n", element[TURN]);
		printf("==========%d 턴==========\n", i);
		printf("입력 : ");
		scanf_s("%d", &input);

		if (input < RNum)
		{
			printf("Up\n");
		}
		else if (input > RNum)
		{
			printf("Down\n");
		}
		else if (input == RNum)
		{
			system("cls");
			printf("정답입니다  턴수 : %d\n", i);
			system("pause");
			break;
		}
		if (i == element[2])
		{
			system("cls");
			printf("GameOver : Trun수 초과\n");
			system("pause");
			break;
		}
		system("pause");
		system("cls"); //한턴 지나면 창 초기화
	}
	/*	
		system("cls");
		printf("GameOver : Trun수 초과\n");
		system("pause");
		break;
		*/
}

void SettingRange(int element[])
{ // return 받는 부분 주의
	int input;

	while (1)
	{
		system("cls");
		printf("==========게임 설정==========");
		printf("\n  1. 최대, 최소범위 설정");
		printf("\n  2. 최대 Turn수 설정");
		printf("\n  3. 돌아가기");
		printf("\n입력 : ");
		scanf_s("%d", &input);
		system("cls");

		if (input == 1)
		{
			printf(" 최소 값 변경 <현재 : %d> : ", element[MIN]);
			scanf_s("%d", &element[MIN]);
			printf(" 최대 값 변경 <현재 : %d> : ", element[MAX]);
			scanf_s("%d", &element[MAX]);
		}
		else if (input == 2)
		{
			printf(" 최대 Turn 값 변경 <현재 : %d> : ", element[TURN]);
			scanf_s("%d", &element[TURN]);
		}
		else if (input == 3)
		{
			break;
		}
	}
}

void main()
{
	int input;
	int element[3] = { 1 ,100, 10 };

	while(1)
	{
		system("cls");
		printf("==========UpDown==========");
		printf("\n	1. 게임시작");
		printf("\n	2. 범위설정");
		printf("\n	3. 종료");
		printf("\n입력 : ");
		scanf_s("%d", &input);
		system("cls");

		switch(input)
		{
		case 1:
			Gamestart(element);
			break;
		case 2:
			SettingRange(element); //배열 or 그냥 전체 코드
			break;
		case 3:
			return; //void 도 return 가능
		}
	}
}
