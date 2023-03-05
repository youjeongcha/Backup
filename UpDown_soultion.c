#include<stdio.h>
#include<stdlib.h>
#include<Windows.h> //Sleep 함수 //system("cls")
#include<time.h>

#define GAMESTART 1
#define MAXORMIN 1
#define SETTING 2
#define MAXTURN 2
#define EXIT 3


int GameMenu()
{
	int Select;
	system("cls");
	printf("=========UpDown=========\n");
	printf("\t1.게임시작\n");
	printf("\t2.범위설정\n");
	printf("\t3.종료\n");
	printf("입력 : ");
	scanf("%d", &Select);
	return Select;
}

void GamePlay(int Max, int Min, int MaxTurn)
{
	int RandomNum = (rand() % ((Max + 1) - Min)) + Min;
	int Num, Turn = 0;
	while (Turn < MaxTurn)
	{
		Turn++;
		system("cls");
		printf("범위  : %d ~ %d\n", Min, Max);
		printf("제한 Turn : %d\n", MaxTurn);
		printf("========%d턴========\n", Turn);
		printf("입력 : ");
		scanf("%d", &Num);
		if (Num > RandomNum)
			printf("Down!!\n");
		else if (Num < RandomNum)
			printf("Up!!\n");
		else
		{
			system("cls");
			printf("정답!!\t턴수 : %d\n", Turn);
			system("pause");
			return;
		}
		system("pause");
	}
	system("cls");	//반복문 밖에 빼내면 자연스럽게 턴 수 초과 조건 성립
	printf("GameOver : Trun수 초과!!\n");
	system("pause");
	return;
}

int SetMin(int Min)
{
	printf(" (현재 : %d)최소 값 변경 : ", Min);
	scanf("%d", &Min);
	return Min;
}
int SetMax(int Max, int Min)
{
	printf(" (현재 : %d)최대 값 변경 : ", Max);
	scanf("%d", &Max);
	if (Max <= Min) //최소가 최대보다 클 경우
	{
		return -1;
	}
	return Max;
}

int SetMaxTurn(int MaxTurn)
{
	printf(" (현재 : %d)최대 Turn 값 변경 : ", MaxTurn);
	scanf("%d", &MaxTurn);
	if (MaxTurn <= 0) //턴값 최소치도 지정해뒀다
		return 0;
	return MaxTurn;
}

void main()
{
	int Max = 100, TmpMax;
	int Min = 1, TmpMin;
	int MaxTurn = 10, TmpMaxTurn;
	int Select;
	int SetState = 1;
	srand(time(NULL));
	while (1)
	{
		switch (GameMenu()) //주의
		{
		case GAMESTART:
			GamePlay(Max, Min, MaxTurn);
			break;
		case SETTING:
			SetState = 1;
			while (SetState)
			{
				system("cls");
				printf("=======게임 설정=======\n");
				printf("  1.최대,최소범위 설정\n");
				printf("  2.최대 Turn수 설정\n");
				printf("  3.돌아가기\n");
				printf("입력 : ");
				scanf("%d", &Select);
				switch (Select)
				{
				case MAXORMIN:
					while (1)
					{
						system("cls");
						TmpMin = SetMin(Min);
						TmpMax = SetMax(Max, TmpMin);
						if (TmpMax == -1) //최소가 더 클 경우 오류 표시도
							printf("오류 : 최소값이 최대값 보다 큽니다 다시 입력하세요.\n");
						else
						{
							Max = TmpMax;
							Min = TmpMin;
							break;
						}
						system("pause");
					}
					break;
				case MAXTURN:
					while (1)
					{
						system("cls");
						TmpMaxTurn = SetMaxTurn(MaxTurn);
						if (TmpMaxTurn != 0)
						{
							MaxTurn = TmpMaxTurn;
							break;
						}
						printf("오류 : 최대 턴수가 0보다 작거나 같습니다 다시입력하세요.\n");
						system("pause");
					}
					break;
				case EXIT:
					SetState = 0; //반복문의 조건을 건들여 빠져나오는 방식
					break;
				}
			}
			break;
		case EXIT:
			return;
		}
	}
}
